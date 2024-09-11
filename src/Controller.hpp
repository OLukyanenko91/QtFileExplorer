#pragma once

#include <QObject>
#include <QStringList>
#include "Explorer/Explorer.hpp"
#include "Explorer/ExplorerData.hpp"
#include "Explorer/FileInfo/FullFileInfo.hpp"
#include "TasksManager/TasksManager.hpp"


class Controller : public QObject
{
    Q_OBJECT

signals:
    void contentsChanged(const ExplorerData::BaseItemInfoList currentContents);
    void currentDirectoryChanged(const QString path);
    void setGoBackEnabled(const bool enabled);
    void setGoForwardEnabled(const bool enabled);
    void backgroundTaskProgressChanged(const qint64 taskId,
                                       const quint8 taskProgress);
    void backgroundTaskFinished(const qint64 taskId);

public:
    Q_INVOKABLE qint64       copyFiles(const QList<QString>& files,
                                       const QString destPath);
    Q_INVOKABLE qint64       deleteFiles(const QList<QString>& files);
    Q_INVOKABLE qint64       moveFiles(const QList<QString>& files,
                                       const QString destPath);
    Q_INVOKABLE void         renameFile(const QString filePath,
                                        const QString newName);
    Q_INVOKABLE qint64       getFilesSize(const QList<QString>& paths);
    Q_INVOKABLE FullFileInfo getFileProperties(const QString path);
    Q_INVOKABLE void         createDirectory(const QString path);

    Q_INVOKABLE void pauseBackgroundTask(const qint64 taskId);
    Q_INVOKABLE void resumeBackgroundTask(const qint64 taskId);
    Q_INVOKABLE void cancelBackgroundTask(const qint64 taskId);

    Q_INVOKABLE void open(const QString path);
    Q_INVOKABLE void goBack();
    Q_INVOKABLE void goForward();

    Q_PROPERTY(QString rootDirectory READ rootDirectory)

public:
    Controller();
    ~Controller();

public:
    QString rootDirectory() const;

private:
    void connectSignals();
    void disconnectSignals();

    qint64 runNewTask(Task* newTask);
    void   handleTaskFinished(const qint64 taskId);
    void   handleGlobalHistoryPosChanged(const NHistory::GlobalPosition position);

private:
    Explorer     mExplorer;
    TasksManager mTasksManager;
};
