#pragma once

#include <QObject>
#include <QDebug>


namespace TaskData
{
    const qint8 INCORRECT_TASK_ID = -1;

    enum class TaskType {
        Unknown = 0,
        CopyFiles,
        MoveFiles,
        DeleteFiles
    };

    static QString TaskTypeToStr(const TaskType type)
    {
        if (type == TaskType::CopyFiles) {
            return "CopyFiles";
        }
        else if (type == TaskType::DeleteFiles) {
            return "DeleteFiles";
        }
        else if (type == TaskType::MoveFiles) {
            return "MoveFiles";
        }
        else {
            qWarning() << "Undefined task type" << int(type);
            return "";
        }
    }
}
