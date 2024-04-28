#include <QDebug>
#include "DeleteFilesTask.hpp"


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
    qInfo() << QThread::currentThreadId() << " DeleteFilesTask::run...";

    for (int i = 1; i <= 100; ++i) {
        if (mCanceled) {
            qInfo() << QThread::currentThreadId() << " DeleteFilesTask::run...canceled";
            emit Finished();
            return;
        }
        if (mPaused) {
            qInfo() << QThread::currentThreadId() << " DeleteFilesTask::run...paused";
            mWaitCondition.wait(&mWaitMutex);
        }

        emit Progress(i);
        QThread::msleep(50);
    }

    qInfo() << QThread::currentThreadId() << " DeleteFilesTask::run...done";

    emit Finished();
}
