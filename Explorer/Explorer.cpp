#include <iostream>
#include "Explorer.hpp"


void Explorer::Cd(const QString path) {
    if (File::GetTypeByPath(path) == File::Type::FOLDER) { // Check if it's a folder
        // Open folder
        SetCurDir(path);
        mHistory.Add(mCurDir.path());
    }
    else if (File::GetTypeByPath(path) == File::Type::FILE) { // Check if it's a file
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

ExplorerData::FileList Explorer::GetCurDirContents() {
    auto filters = QDir::Files | QDir::Dirs | QDir::QDir::NoDotAndDotDot;
    auto sortFlags = QDir::DirsFirst | QDir::IgnoreCase;
    auto fileInfoList = mCurDir.entryInfoList(filters, sortFlags);

    ExplorerData::FileList fileList;
    foreach (const auto& fileInfo, fileInfoList) {
        fileList << fileInfo;
    }

    return fileList;
}

void Explorer::SetCurDir(const QString path) {
    mCurDir.setPath(path);

    if (path == ExplorerData::ROOT_DIRECTORY) {
        ExplorerData::FileList systemDrivers;
        foreach (const auto& systemDriver, GetSystemDrivers()) {
            systemDrivers << systemDriver;
        }

        emit CurrentDirChanged(QString());
        emit ContentsChanged(systemDrivers);
    }
    else {
        emit CurrentDirChanged(mCurDir.path().replace("//", "/"));
        emit ContentsChanged(GetCurDirContents());
    }
}
