#pragma once

#include <QObject>
#include "File/File.hpp"


namespace ExplorerData
{
    Q_NAMESPACE

    enum class CdDirection {
        Back,
        Forward,
        Up
    };

    Q_ENUM_NS(CdDirection)

    static const QString ROOT_DIRECTORY = ".";

    using FileList = QList<File>;
}
