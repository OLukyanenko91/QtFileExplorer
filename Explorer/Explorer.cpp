#include <iostream>
#include <QDesktopServices>
#include <QUrl>
#include "Explorer.hpp"


void Explorer::Cd(const QString path)
{
    // Check if it's a folder
    if (File::GetTypeByPath(path) == File::Type::Folder) {
        // Open folder
        SetCurDir(path);
        mHistory.Add(mCurDir.path());
    }
    // Check if it's a file
    else if (File::GetTypeByPath(path) == File::Type::File) {
        // Open file
        bool result = QDesktopServices::openUrl(QUrl::fromLocalFile(path));
        if (!result) {
            qWarning() << "Can't open" << path;
        }
    }
    else {
        qWarning() << "Incorrect path: " << path;
    }
}

void Explorer::Cd(const ExplorerData::CdDirection direction)
{
    if (mHistory.IsEmpty()) {
        qWarning() << "History is empty";
        return;
    }

    if (direction == ExplorerData::CdDirection::Back) {
        SetCurDir(mHistory.MoveBack());
    }
    else if (direction == ExplorerData::CdDirection::Forward) {
        SetCurDir(mHistory.MoveForward());
    }
}

void Explorer::Update()
{
    qInfo() << "Update"
    SetCurDir(mCurDir.absolutePath());
}

QStringList Explorer::GetSystemDrivers() const
{
    QStringList drivers;

    foreach (QFileInfo drive, QDir::drives()) {
        drivers << drive.path();
    }

    if (drivers.empty()) {
        qWarning() << "No drivers\n";
    }

    return drivers;
}

ExplorerData::FileList Explorer::GetCurDirContents()
{
    auto filters = QDir::Files | QDir::Dirs | QDir::QDir::NoDotAndDotDot;
    auto sortFlags = QDir::DirsFirst | QDir::IgnoreCase;
    auto fileInfoList = mCurDir.entryInfoList(filters, sortFlags);

    ExplorerData::FileList fileList;
    foreach (const auto& fileInfo, fileInfoList) {
        fileList << fileInfo;
    }

    return fileList;
}

void Explorer::SetCurDir(const QString path)
{
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
