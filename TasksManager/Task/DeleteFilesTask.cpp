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
    qInfo() << QThread::currentThreadId() << "Run deleting files task";

    for (int i = 0; i < mFiles.size(); ++i) {
        if (!CheckRunning()) {
            return;
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
            qInfo() << QThread::currentThreadId() << QString("File '%1' deleted").arg(mFiles[i]);
        }
        else {
            qWarning() << QThread::currentThreadId() << "Failed to delete " << mFiles[i];
        }

        emit Progress(float(i + 1) / mFiles.count() * 100);
    }

    qInfo() << QThread::currentThreadId() << "Delete files task finished";

    emit Finished();
}
