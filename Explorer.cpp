#include <iostream>
#include "Explorer.hpp"


QStringList Explorer::GetSystemDrivers() const
{
    QStringList drivers;

    foreach (QFileInfo drive, QDir::drives()) {
        drivers << drive.path();
    }

    if (drivers.empty()) {
        std::cerr << "No drivers\n";
    }

    return drivers;
}

void Explorer::Open(const QString fileName)
{
    if (mCurrentDir.cd(fileName)) {
        const auto filters = QDir::Files | QDir::Dirs | QDir::QDir::NoDotAndDotDot;
        const auto sortFlags = QDir::DirsFirst | QDir::IgnoreCase;
        const auto dirContents = mCurrentDir.entryList(filters, sortFlags);

        emit ContentsChanged(dirContents);
    }
    else {
        // try to open the file with a default app
    }
}

