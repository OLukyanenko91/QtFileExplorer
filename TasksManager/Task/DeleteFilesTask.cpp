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
    emit Progress(5);
    QThread::sleep(2);
    emit Progress(65);
    QThread::sleep(2);
    emit Progress(100);
    qInfo() << QThread::currentThreadId() << " DeleteFilesTask::run...done";

    emit Finished();
}
