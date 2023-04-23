#include <iostream>
#include "Explorer.hpp"


void Explorer::Cd(const QString path) {
    if (QDir(path).exists()) { // Check if it's a folder
        // Open folder
        SetCurDir(path);
        mHistory.Add(mCurDir.path());
    }
    else if (QFile::exists(path)) { // Check if it's a file
        // Open file
    }
    else {
        qWarning() << "Incorrect path: " << path;
    }
}

void Explorer::Cd(const ExplorerData::CD_DIRECTION direction) {
    if (mHistory.IsEmpty()) {
        qWarning() << "History is empty";
        return;
    }

    if (direction == ExplorerData::CD_DIRECTION::BACK) {
        SetCurDir(mHistory.MoveBack());
    }
    else if (direction == ExplorerData::CD_DIRECTION::FORWARD) {
        SetCurDir(mHistory.MoveForward());
    }
}

QStringList Explorer::GetSystemDrivers() const {
    QStringList drivers;

    foreach (QFileInfo drive, QDir::drives()) {
        drivers << drive.path();
    }

    if (drivers.empty()) {
        std::cerr << "No drivers\n";
    }

    return drivers;
}

QStringList Explorer::GetCurDirContents() {
    const auto filters = QDir::Files | QDir::Dirs | QDir::QDir::NoDotAndDotDot;
    const auto sortFlags = QDir::DirsFirst | QDir::IgnoreCase;

    return mCurDir.entryList(filters, sortFlags);
}

void Explorer::SetCurDir(const QString path) {
    mCurDir.setPath(path);

    if (path == ExplorerData::ROOT_DIRECTORY) {
        emit CurrentDirChanged(QString());
        emit ContentsChanged(GetSystemDrivers());
    }
    else {
        emit CurrentDirChanged(mCurDir.path().replace("//", "/"));
        emit ContentsChanged(GetCurDirContents());
    }
}
