#include <iostream>
#include <QDesktopServices>
#include <QUrl>
#include <QStorageInfo>
#include "Explorer.hpp"


Explorer::Explorer()
{
    connect(&mSystemWatcher, &QFileSystemWatcher::directoryChanged,
            this, &Explorer::HandleSystemWatcherUpdate);
    connect(&mHistory, &History::GlobalPositionNotification,
            this, &Explorer::GlobalHistoryPositionChanged);
}

void Explorer::Cd(const QString path)
{
    qInfo() << "Cd, path:" << path;

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
    qInfo() << "Cd, direction:" << direction;

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
    qInfo() << "Update";
    SetCurDir(mCurDir.absolutePath());
}

ExplorerData::FileList Explorer::GetSystemDrivers() const
{
    ExplorerData::FileList driversList;

    foreach (const QStorageInfo& driver, QStorageInfo::mountedVolumes()) {
        driversList << driver;
    }

    if (driversList.empty()) {
        qWarning() << "No drivers\n";
    }

    return driversList;
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
    qInfo() << "Set cur dir, path:" << path;

    mSystemWatcher.removePath(mCurDir.path());
    mSystemWatcher.addPath(path);

    mCurDir.setPath(path);

    if (path == ExplorerData::ROOT_DIRECTORY) {
        ExplorerData::FileList systemDrivers = GetSystemDrivers();
        emit CurrentDirChanged(QString());
        emit ContentsChanged(systemDrivers);
    }
    else {
        emit CurrentDirChanged(mCurDir.path().replace("//", "/"));
        emit ContentsChanged(GetCurDirContents());
    }
}

void Explorer::HandleSystemWatcherUpdate(const QString& path)
{
    qInfo() << "Handle system watcher update";

    Q_ASSERT(mCurDir.path() == path);
    SetCurDir(path);
}
