#include <QDebug>
#include "TasksManager.hpp"


TasksManager::TasksManager(QObject* parent)
    : QObject(parent)
{}

bool TasksManager::RunTask(Task* task)
{
    qInfo() << QThread::currentThreadId() << "Append task ->"
            << TaskData::TaskTypeToStr(task->GetType())
            << ", id" << task->GetId();

    if (mRunnedTasks.contains(task->GetId())) {
        qWarning() << "Task with id" << task->GetId() << " already exists";
        return false;
    }
    else {
        connect(task, &Task::Progress, this, &TasksManager::HandleTaskProgress);
        connect(task, &Task::Finished, this, &TasksManager::HandleFinishedTask);

        mRunnedTasks[task->GetId()] = task;
        task->start();
        return true;
    }
}

bool TasksManager::PauseTask(const qint64 taskId)
{
    qInfo() << QThread::currentThreadId() << "Pause task" << taskId;

    if (mRunnedTasks.contains(taskId)) {
        mRunnedTasks[taskId]->Pause();
        return true;
    }
    else {
        qWarning() << QThread::currentThreadId() << "Unable to stop the task, it wasn't found";
    }

    return false;
}

bool TasksManager::ResumeTask(const qint64 taskId)
{
    qInfo() << QThread::currentThreadId() << "Resume task" << taskId;

    if (mRunnedTasks.contains(taskId)) {
        mRunnedTasks[taskId]->Resume();
        return true;
    }
    else {
        qWarning() << QThread::currentThreadId() << "Unable to resume the task, it wasn't found";
    }

    return false;
}

bool TasksManager::CancelTask(const qint64 taskId)
{
    qInfo() << QThread::currentThreadId() << "Cancel task" << taskId;

    if (mRunnedTasks.contains(taskId)) {
        mRunnedTasks[taskId]->Cancel();
        return true;
    }
    else {
        qWarning() << QThread::currentThreadId() << "Unable to cancel the task, it wasn't found";
    }

    return false;
}

void TasksManager::HandleTaskProgress(const quint8 progress)
{
    auto task = qobject_cast<Task*>(sender());
    if (task) {
        qInfo() << "Task" << task->GetId() << ", progress" << progress << "%";
        emit TaskProgress(task->GetId(),
                          progress);
    }
    else {
        qWarning() << "Can't handle task progress, wrong sender type";
    }
}

void TasksManager::HandleFinishedTask()
{
    auto task = qobject_cast<Task*>(sender());
    if (task) {
        qInfo() << "Task" << task->GetId() << " completed";
        RemoveRunnedTask(task->GetId());

        emit TaskFinished(task->GetId());
    }
    else {
        qWarning() << "Can't handle task completion, wrong sender type";
    }
}

void TasksManager::RemoveRunnedTask(const qint64 taskId)
{
    if (mRunnedTasks.contains(taskId)) {
        auto runnedTask = mRunnedTasks.take(taskId);
        runnedTask->disconnect();
        runnedTask->deleteLater();

        qInfo() << "Task" << taskId << "has been removed from the running tasks map";
    }
    else {
        qWarning() << "Failed to delete running task" << taskId << ", it wasn't found";
    }
}
