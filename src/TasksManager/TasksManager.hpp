#pragma once

#include <QObject>
#include <QQueue>
#include "Task/Task.hpp"


class TasksManager : public QObject
{
    Q_OBJECT

public:
    explicit TasksManager(QObject *parent = nullptr);

public:
    bool RunTask(Task* task);
    bool PauseTask(const qint64 taskId);
    bool ResumeTask(const qint64 taskId);
    bool CancelTask(const qint64 taskId);

signals:
    void TaskProgress(const qint64 taskId,
                      const quint8 taskProgress);
    void TaskFinished(const qint64 taskId);

private slots:
    void HandleTaskProgress(const quint8 progress);
    void HandleFinishedTask();

private:
    void RemoveRunnedTask(const qint64 taskId);

private:
    QMap<qint64, Task*> mRunnedTasks;
};
