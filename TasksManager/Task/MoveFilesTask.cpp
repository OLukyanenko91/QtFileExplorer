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

    for (int i = 0; i < mFiles.size(); ++i) {
        if (!CheckRunning()) {
            return;
        }

        qInfo() << QThread::currentThreadId() << "Moving file" << mFiles[i];

        bool copyResult = Task::CopyFile(mFiles[i], mDestPath, i);
        if (copyResult) {
            Task::DeleteFile(mFiles[i]);
        }

        emit Progress(float(i + 1) / mFiles.count() * 100);
    }

    qInfo() << QThread::currentThreadId() << " Move files task finished";

    emit Finished();
}
