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
    emit Progress(5);
    QThread::sleep(3);
    emit Progress(65);
    QThread::sleep(3);
    emit Progress(100);
    qInfo() << QThread::currentThreadId() << " MoveFilesTask::run...done";

    emit Finished();
}
