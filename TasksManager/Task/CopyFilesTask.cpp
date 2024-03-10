#include <QDebug>
#include "CopyFilesTask.hpp"


CopyFilesTask::CopyFilesTask(const qint64 id,
                             const QList<QString>& files,
                             const QString destPath,
                             QObject* parent)
    : Task(id,
           files,
           destPath,
           TaskData::TaskType::CopyFiles,
           parent)
{}

void CopyFilesTask::run()
{
    qInfo() << QThread::currentThreadId() << " CopyFilesTask::run...";

    for (int i = 1; i <= 100; ++i) {
        if (mCanceled) {
            qInfo() << QThread::currentThreadId() << " CopyFilesTask::run...canceled";
            emit Finished();
            return;
        }
        if (mPaused) {
            qInfo() << QThread::currentThreadId() << " CopyFilesTask::run...paused";
            mWaitCondition.wait(&mWaitMutex);
        }

        emit Progress(i);
        QThread::msleep(50);
    }

    qInfo() << QThread::currentThreadId() << " CopyFilesTask::run...done";

    emit Finished();
}
