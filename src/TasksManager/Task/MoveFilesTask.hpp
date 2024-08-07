#pragma once

#include "Task.hpp"


class MoveFilesTask : public Task
{
    Q_OBJECT

public:
    explicit MoveFilesTask(const qint64 id,
                           const QList<QString>& files,
                           const QString destPath,
                           QObject* parent = nullptr);

public:
    void run() override; // QThread
};
