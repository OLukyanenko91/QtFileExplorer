#pragma once

#include <QObject>
#include "FileInfo/BaseFileInfo.hpp"


namespace ExplorerData
{
    Q_NAMESPACE
    enum class CdDirection {
        Back,
        Forward,
        Up
    };
    Q_ENUM_NS(CdDirection)

    static const char* ROOT_DIRECTORY = ".";
    
    using BaseItemInfoList = QList<BaseFileInfo>;
}
