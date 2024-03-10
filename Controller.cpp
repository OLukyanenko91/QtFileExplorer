#include "Controller.hpp"
#include "TasksManager/Task/Task.hpp"
#include "TasksManager/Task/CopyFilesTask.hpp"
#include "TasksManager/Task/MoveFilesTask.hpp"
#include "TasksManager/Task/DeleteFilesTask.hpp"


Controller::Controller()
{
    connect(&mExplorer, &Explorer::ContentsChanged, this, &Controller::onDirContentsChanged);
    connect(&mExplorer, &Explorer::CurrentDirChanged, this, &Controller::onCurDirChanged);
    connect(&mTasksManager, &TasksManager::TaskProgress, this, &Controller::backgroundTaskProgressChanged);
    connect(&mTasksManager, &TasksManager::TaskFinished, this, &Controller::backgroundTaskFinished);
}

qint64 Controller::copyFiles(QList<QString> files,
                             QString destPath)
{
    return runNewTask(new CopyFilesTask(Task::GenerateId(),
                                        files,
                                        destPath));
}

qint64 Controller::deleteFiles(QList<QString> files)
{
    return runNewTask(new DeleteFilesTask(Task::GenerateId(),
                                          files));
}

qint64 Controller::moveFiles(QList<QString> files,
                             QString destPath)
{
    return runNewTask(new MoveFilesTask(Task::GenerateId(),
                                        files,
                                        destPath));
}

void Controller::open(const QString path)
{
    mExplorer.Cd(path);
}

void Controller::goBack()
{
    mExplorer.Cd(ExplorerData::CdDirection::Back);
}

void Controller::goForward()
{
    mExplorer.Cd(ExplorerData::CdDirection::Forward);
}

QString Controller::getFileSize(const QString path)
{
    return File::GetSize(path);
}

void Controller::pauseBackgroundTask(const qint64 taskId)
{
    mTasksManager.PauseTask(taskId);
}

void Controller::resumeBackgroundTask(const qint64 taskId)
{
    mTasksManager.ResumeTask(taskId);
}

void Controller::cancelBackgroundTask(const qint64 taskId)
{
    mTasksManager.CancelTask(taskId);
}

QString Controller::rootDirectory() const
{
    return ExplorerData::ROOT_DIRECTORY;
}

qint64 Controller::runNewTask(Task* newTask)
{
    if (!mTasksManager.RunTask(newTask)) {
        qWarning() << "Can't run new task, type" << TaskData::TaskTypeToStr(newTask->GetType())
                   << ", id" << newTask->GetId();

        return TaskData::INCORRECT_TASK_ID;
    }

    return newTask->GetId();
}

void Controller::onDirContentsChanged(const ExplorerData::FileList dirContents)
{
    emit contentsChanged(dirContents);
}

void Controller::onCurDirChanged(const QString path)
{
    emit currentDirectoryChanged(path);
}
