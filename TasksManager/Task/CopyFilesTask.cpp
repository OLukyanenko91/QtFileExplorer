#include <limits>
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
    qInfo() << QThread::currentThreadId() << "Run copying files task";

    for (int i = 0; i < mFiles.size(); ++i) {
        if (!CheckRunning()) {
            return;
        }

        qInfo() << QThread::currentThreadId() << "Copying file" << mFiles[i];

        bool copyResult = Task::CopyFile(mFiles[i], mDestPath, i);
        if (!copyResult) {
            continue;
        }
    }

    qInfo() << QThread::currentThreadId() << "Copy files task finished";

    emit Finished();
}
