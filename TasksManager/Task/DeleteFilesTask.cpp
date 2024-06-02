#include <QDebug>
#include <QDir>
#include <QFile>
#include "DeleteFilesTask.hpp"
#include "Explorer/File/File.hpp"


DeleteFilesTask::DeleteFilesTask(const qint64 id,
                                 const QList<QString>& files,
                                 QObject* parent)
    : Task(id,
           files,
           "",
           TaskData::TaskType::DeleteFiles,
           parent)
{}

void DeleteFilesTask::run()
{
    qInfo() << QThread::currentThreadId() << "DeleteFilesTask::run...";

    for (int i = 0; i < mFiles.size(); ++i) {
        if (mCanceled) {
            qInfo() << QThread::currentThreadId() << "DeleteFilesTask::run...canceled";
            emit Finished();
            return;
        }
        if (mPaused) {
            qInfo() << QThread::currentThreadId() << "DeleteFilesTask::run...paused";
            mWaitCondition.wait(&mWaitMutex);
        }

        bool result {false};
        auto type = File::GetTypeByPath(mFiles[i]);

        if (type == File::Type::File) {
            result = QFile::remove(mFiles[i]);
        }
        else if (type == File::Type::Folder) {
            QDir dir(mFiles[i]);
            result = dir.removeRecursively();
        }

        if (result) {
            qInfo() << QThread::currentThreadId()
                    << QString("DeleteFilesTask::run...file '%1' deleted").arg(mFiles[i]);
        }
        else {
            qWarning() << QThread::currentThreadId()
                       << "DeleteFilesTask::run...failed to delete " << mFiles[i];
        }

        emit Progress(float(i + 1) / mFiles.count() * 100);
    }

    qInfo() << QThread::currentThreadId() << "DeleteFilesTask::run...done";

    emit Finished();
}
