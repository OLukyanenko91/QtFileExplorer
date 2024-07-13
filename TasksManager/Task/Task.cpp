#include <QDateTime>
#include <QFile>
#include "Task.hpp"
#include "Explorer/File/File.hpp"
#include "Common.hpp"


Task::Task(const qint64 id,
           const QList<QString>& files,
           const QString destPath,
           const TaskData::TaskType type,
           QObject* parent)
    : QThread(parent)
    , mId(id)
    , mFiles(files)
    , mDestPath(destPath)
    , mType(type)
{
    qInfo() << "Task with id" << id << "created";
}

Task::~Task()
{
    qInfo() << "Task with id" << GetId() << "deleted";
}

void Task::Pause()
{
    if (!mCanceled) {
        mPaused = true;
    }
}

void Task::Resume()
{
    if (!mCanceled) {
        mPaused = false;
        mWaitCondition.wakeAll();
    }
}

void Task::Cancel()
{
    mWaitCondition.wakeAll();
    mCanceled = true;
}

TaskData::TaskType Task::GetType() const
{
    return mType;
}

qint64 Task::GetId() const
{
    return mId;
}

qint64 Task::GenerateId()
{
    return QDateTime::currentMSecsSinceEpoch();
}

bool Task::CheckRunning()
{
    if (mCanceled) {
        qInfo() << QThread::currentThreadId() << "Canceled";
        emit Finished();

        return false;
    }
    if (mPaused) {
        qInfo() << QThread::currentThreadId() << "Paused";
        mWaitCondition.wait(&mWaitMutex);
    }

    return true;
}

bool Task::CopyFile(const QString& srcFilePath,
                    const QString& dstPath,
                    const quint16 index)
{
    qInfo() << QThread::currentThreadId()
            << "Copy file, src" << srcFilePath << ", dst" << dstPath;

    try {
        // Open file input
        QFile fileInput(srcFilePath);
        if (!fileInput.open(QIODevice::ReadOnly)) {
            throw NCommon::CException("Could not open bin file for reading");
        }

        // Open file output
        auto fileName = File::GetFileName(srcFilePath);
        if (QFileInfo::exists(mDestPath + '/' + fileName)) {
            fileName = File::CreateNewFileName(mDestPath, fileName);
            qWarning() << fileName;
        }

        QFile fileOutput(mDestPath + '/' + fileName);
        if (!fileOutput.open(QIODevice::WriteOnly)) {
            throw NCommon::CException("Could not open bin file for writing");
        }

        // Copy data
        QDataStream inputDataStream(&fileInput);
        QDataStream outputDataStream(&fileOutput);
        QByteArray byteArray(INT_MAX, 0);
        quint64 copiedBytes = 0;

        while(true) {
            auto bytes = inputDataStream.readRawData(byteArray.data(),
                                                     byteArray.size());

            if (!bytes) {
                break;
            }
            else {
                copiedBytes += bytes;
                outputDataStream.writeRawData(byteArray.data(),
                                              bytes);
            }

            auto curFileProgress = (float(copiedBytes) / fileInput.size() * 100) / 100;
            emit Progress((index + curFileProgress) / mFiles.count() * 100);
        }

        // Close files
        fileInput.close();
        fileOutput.close();

        return true;
    }
    catch (std::exception e) {
        qWarning() << QThread::currentThreadId()
                   << "Failed to copy the file," << e.what();
        return false;
    }
    catch (...) {
        qWarning() << QThread::currentThreadId()
                   << "Unrecognized error while copying a file";
        Q_ASSERT(false);
    }
}

bool Task::DeleteFile(const QString& filePath)
{
    qInfo() << QThread::currentThreadId()
            << "Delete file, path" << filePath;

    try {
        bool result = false;
        auto type = File::GetTypeByPath(filePath);

        if (type == File::Type::File) {
            result = QFile::remove(filePath);
        }
        else if (type == File::Type::Folder) {
            QDir dir(filePath);
            result = dir.removeRecursively();
        }

        if (!result) {
            throw NCommon::CException("The delete operation failed");
        }

        return true;
    }
    catch (std::exception e) {
        qWarning() << QThread::currentThreadId()
                   << "Failed to delete the file," << e.what();
        return false;
    }
    catch (...) {
        qWarning() << QThread::currentThreadId()
                   << "Unrecognized error while deleting a file";
        Q_ASSERT(false);
    }
}
