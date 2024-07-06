#include <QDateTime>
#include <QFile>
#include "Task.hpp"
#include "Explorer/File/File.hpp"


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
    // Open file input
    QFile fileInput(srcFilePath);
    if (!fileInput.open(QIODevice::ReadOnly)) {
        qWarning() << QThread::currentThreadId() << "Could not open bin file for reading";
        return false;
    }

    // Open file output
    auto fileName = File::GetFileName(srcFilePath);
    if (QFileInfo::exists(mDestPath + '/' + fileName)) {
        fileName = File::CreateNewFileName(mDestPath, fileName);
        qWarning() << fileName;
    }

    QFile fileOutput(mDestPath + '/' + fileName);
    if (!fileOutput.open(QIODevice::WriteOnly)) {
        qWarning() << QThread::currentThreadId() << "Could not open bin file for writing";
        return false;
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
