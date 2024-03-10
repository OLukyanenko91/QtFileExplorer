#pragma once

#include "Task.hpp"


class CopyFilesTask : public Task
{
public:
    explicit CopyFilesTask(const qint64 id,
                           const QList<QString>& files,
                           const QString destPath,
                           QObject* parent = nullptr);

public:
    void run() override;
};

