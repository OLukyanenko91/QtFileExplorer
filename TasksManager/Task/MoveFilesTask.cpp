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
    qInfo() << QThread::currentThreadId() << "Run moving files task";

    for (int i = 1; i <= 100; ++i) {
        if (!CheckRunning()) {
            return;
        }

        emit Progress(i);
        QThread::msleep(50);
    }

    qInfo() << QThread::currentThreadId() << " Move files task finished";

    emit Finished();
}
