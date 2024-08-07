#pragma once

#include "Task.hpp"


class DeleteFilesTask : public Task
{
    Q_OBJECT

public:
    explicit DeleteFilesTask(const qint64 id,
                             const QList<QString>& files,
                             QObject* parent = nullptr);

public:
    void run() override;
};
