#include <iostream>
#include <QDir>
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

