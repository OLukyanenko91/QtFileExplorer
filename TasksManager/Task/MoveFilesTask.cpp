#include <QDebug>
#include "MoveFilesTask.hpp"


MoveFilesTask::MoveFilesTask(const qint64 id,
                             const QList<QString>& files,
                             const QString destPath,
                             QObject* parent)
    : Task(id,
           files,
           destPath,
           TaskData::TaskType::MoveFiles,
           parent)
{}

void MoveFilesTask::run()
{
    qInfo() << QThread::currentThreadId() << " MoveFilesTask::run...";

    for (int i = 1; i <= 100; ++i) {
        if (mCanceled) {
            qInfo() << QThread::currentThreadId() << " MoveFilesTask::run...canceled";
            emit Finished();
            return;
        }
        if (mPaused) {
            qInfo() << QThread::currentThreadId() << " MoveFilesTask::run...paused";
            mWaitCondition.wait(&mWaitMutex);
        }

        emit Progress(i);
        QThread::msleep(50);
    }

    qInfo() << QThread::currentThreadId() << " MoveFilesTask::run...done";

    emit Finished();
}
