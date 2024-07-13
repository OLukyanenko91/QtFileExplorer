#include <QDebug>
#include <QDir>
#include <QFile>
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
    qInfo() << QThread::currentThreadId() << "Run deleting files task";

    for (int i = 0; i < mFiles.size(); ++i) {
        if (!CheckRunning()) {
            return;
        }

        Task::DeleteFile(mFiles[i]);
        emit Progress(float(i + 1) / mFiles.count() * 100);
    }

    qInfo() << QThread::currentThreadId() << "Delete files task finished";

    emit Finished();
}
