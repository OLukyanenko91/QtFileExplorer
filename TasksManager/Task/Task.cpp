#include <QDateTime>
#include "Task.hpp"


Task::Task(const qint64 id,
           const QList<QString>& files,
           const QString destPath,
           const TaskData::TaskType type,
           QObject* parent)
    : QThread(parent)
    , mId(id)
    , mFiles(files)
    , mDestPath(destPath)
    , mType(type)
{
    qInfo() << "Task with id" << id << "created";
}

Task::~Task()
{
    qInfo() << "Task with id" << GetId() << "deleted";
}

void Task::Pause()
{
    if (!mCanceled) {
        mPaused = true;
    }
}

void Task::Resume()
{
    if (!mCanceled) {
        mPaused = false;
        mWaitCondition.wakeAll();
    }
}

void Task::Cancel()
{
    mWaitCondition.wakeAll();
    mCanceled = true;
}

TaskData::TaskType Task::GetType() const
{
    return mType;
}

qint64 Task::GetId() const
{
    return mId;
}

qint64 Task::GenerateId()
{
    return QDateTime::currentMSecsSinceEpoch();
}
