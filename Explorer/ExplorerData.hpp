#pragma once

#include <QObject>
#include "File/File.hpp"


namespace ExplorerData
{
    enum class CdDirection {
        Back,
        Forward,
        Up
    };

    static const QString ROOT_DIRECTORY = ".";

    using FileList = QList<File>;
}
