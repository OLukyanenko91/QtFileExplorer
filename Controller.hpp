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
    Q_INVOKABLE qint64 copyFiles(QList<QString> files,
                                 QString destPath);
    Q_INVOKABLE qint64 deleteFiles(QList<QString> files);
    Q_INVOKABLE qint64 moveFiles(QList<QString> files,
                                 QString destPath);

    Q_INVOKABLE void    open(const QString path);
    Q_INVOKABLE void    goBack();
    Q_INVOKABLE void    goForward();
    Q_INVOKABLE QString getFileSize(const QString path);

    Q_INVOKABLE void pauseBackgroundTask(const qint64 taskId);
    Q_INVOKABLE void resumeBackgroundTask(const qint64 taskId);
    Q_INVOKABLE void cancelBackgroundTask(const qint64 taskId);

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
