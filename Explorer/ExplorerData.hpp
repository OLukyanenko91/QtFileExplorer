#pragma once

#include <QObject>
#include "File/File.hpp"


namespace ExplorerData
{
    enum class CD_DIRECTION {
        BACK,
        FORWARD,
        UP
    };

    static const QString ROOT_DIRECTORY = ".";

    using FileList = QList<File>;
}
