#pragma once

#include <QObject>
#include <QStringList>
#include "Explorer/Explorer.hpp"
#include "Explorer/ExplorerData.hpp"
#include "TasksManager/TasksManager.hpp"


class Controller : public QObject
{
    Q_OBJECT

public:
    Q_INVOKABLE qint64 copyFiles(const QList<QString>& files,
                                 const QString destPath);
    Q_INVOKABLE qint64 deleteFiles(const QList<QString>& files);
    Q_INVOKABLE qint64 moveFiles(const QList<QString>& files,
                                 const QString destPath);

    Q_INVOKABLE void    open(const QString path);
    Q_INVOKABLE void    goBack();
    Q_INVOKABLE void    goForward();
    Q_INVOKABLE QString getFilesSize(const QList<QString>& paths);

    Q_INVOKABLE void pauseBackgroundTask(const qint64 taskId);
    Q_INVOKABLE void resumeBackgroundTask(const qint64 taskId);
    Q_INVOKABLE void cancelBackgroundTask(const qint64 taskId);

    Q_INVOKABLE void createDirectory(const QString path);
    Q_INVOKABLE void renameFile(const QString filePath,
                                const QString newName);

    Q_PROPERTY(QString rootDirectory READ rootDirectory)

signals:
    void contentsChanged(const ExplorerData::FileList currentContents);
    void currentDirectoryChanged(const QString path);
    void backgroundTaskProgressChanged(const qint64 taskId,
                                       const quint8 taskProgress);
    void backgroundTaskFinished(const qint64 taskId);

private slots:
    void onDirContentsChanged(const ExplorerData::FileList dirContents);
    void onCurDirChanged(const QString path);
    void onTaskFinished(const qint64 taskId);

public:
    Controller();

public:
    QString rootDirectory() const;

private:
    qint64 runNewTask(Task* newTask);

private:
    Explorer     mExplorer;
    TasksManager mTasksManager;
};
