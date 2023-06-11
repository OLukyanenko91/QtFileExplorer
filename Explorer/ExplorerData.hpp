#ifndef EXPLORERDATA_HPP
#define EXPLORERDATA_HPP

#include <QObject>
#include "File.hpp"


namespace ExplorerData {
    enum class CD_DIRECTION {
        BACK,
        FORWARD,
        UP
    };

    static const QString ROOT_DIRECTORY = ".";

    using FileList = QList<File>;
}

#endif // EXPLORERDATA_HPP
