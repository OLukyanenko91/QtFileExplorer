#pragma once

#include <QObject>
#include <QList>
#include <QThread>
#include <QMutex>
#include <QWaitCondition>
#include "TaskData.hpp"


class Task : public QThread
{
    Q_OBJECT

signals:
    void Progress(const quint8 progress); // 0-100%
    void Finished();
    void Error();

public:
    explicit Task(const qint64 id,
                  const QList<QString>& files,
                  const QString destPath,
                  const TaskData::TaskType type,
                  QObject* parent = nullptr);
    virtual ~Task();

public:
    void Pause();
    void Resume();
    void Cancel();

    TaskData::TaskType GetType() const;
    qint64             GetId() const;

public:
    static qint64 GenerateId();

protected:
    bool CheckRunning();
    bool CopyFile(const QString& srcFilePath,
                  const QString& dstPath,
                  const quint16 index);

protected:
    qint64             mId;
    QList<QString>     mFiles;
    QString            mDestPath;
    TaskData::TaskType mType {TaskData::TaskType::Unknown};

    bool           mPaused {false};
    bool           mCanceled {false};
    QMutex         mWaitMutex;
    QWaitCondition mWaitCondition;
};
