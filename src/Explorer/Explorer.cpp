#include <iostream>
#include <QDesktopServices>
#include <QUrl>
#include <QStorageInfo>
#include <QRegularExpression>
#include "Explorer.hpp"


namespace
{
    const char*  COPY_FILE_NAME_REGEX_TEMPLATE = R"(^\Q%1\E - Copy \((\d+)\).*$)";
    const quint8 REGEX_FIRST_CAPTURED          = 1;
    const quint8 DEFAULT_NEXT_COPY_FILE_INDEX  = 2;
}


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

    auto type = GetTypeByPath(path);
    if (type == BaseFileInfo::Type::Folder ||
            type == BaseFileInfo::Type::Driver) {
        // Open folder
        SetCurDir(path);
        mHistory.Add(mCurDir.path());
    }
    else if (type == BaseFileInfo::Type::File) {
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

ExplorerData::BaseItemInfoList Explorer::GetSystemDrivers() const
{
    ExplorerData::BaseItemInfoList driverList;

    foreach (const QStorageInfo& driver, QStorageInfo::mountedVolumes()) {
        driverList << BaseFileInfo(driver);
    }

    if (driverList.empty()) {
        qWarning() << "No drivers\n";
    }

    return driverList;
}

ExplorerData::BaseItemInfoList Explorer::GetCurDirContents()
{
    auto filters = QDir::Files | QDir::Dirs | QDir::QDir::NoDotAndDotDot;
    auto sortFlags = QDir::DirsFirst | QDir::IgnoreCase;
    auto fileInfoList = mCurDir.entryInfoList(filters, sortFlags);

    ExplorerData::BaseItemInfoList fileList;
    foreach (const auto& fileInfo, fileInfoList) {
        fileList << BaseFileInfo(fileInfo);
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
        ExplorerData::BaseItemInfoList systemDrivers = GetSystemDrivers();
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

QString Explorer::CreateNewFileName(const QString& path,
                                    const QString& fileName)
{
    qInfo() << "Create new file name, path:" << path << ", file name:" << fileName;

    QFileInfo fileInfo(path + '/' + fileName);
    QString fileExt = fileInfo.suffix();
    QString baseFileName = fileInfo.baseName();

    QString newFileName = QString("%1 - Copy.%2").arg(baseFileName, fileExt);
    if (QFileInfo::exists(path + '/' + newFileName)) {
        newFileName = QString("%1 - Copy (2).%2").arg(baseFileName, fileExt);
        if (QFileInfo::exists(path + '/' + newFileName)) {
            auto nextIndex = FindNextCopyFileIndex(path, fileName);
            return QString("%1 - Copy (%2).%3").arg(baseFileName,
                                                    QString::number(nextIndex),
                                                    fileExt);
        }
        else {
            return newFileName;
        }
    }
    else {
        return newFileName;
    }
}

void Explorer::CreateDirectory(const QString& path)
{
    qInfo() << "Create directory, path" << path;

    if (QDir(path).exists()) {
        qWarning() << "Directory already exists";
    }
    else {
        bool result = QDir().mkdir(path);
        if (!result) {
            qWarning() << "Failed to create a directory";
        }
    }
}

void Explorer::RenameFile(const QString& path,
                          const QString& newName)
{
    qInfo() << "Rename file, path" << path << ", new name" << newName;
    Q_ASSERT(QFile::exists(path));

    QFileInfo fileInfo(path);
    QString newPath = fileInfo.absolutePath() + "/" + newName;

    bool result = QFile::rename(path, newPath);
    if (!result) {
        qWarning() << "Failed to rename the file";
    }
}

QString Explorer::GetFileName(const QString& path)
{
    auto splittedPath = path.split('/', Qt::SkipEmptyParts);

    Q_ASSERT(splittedPath.length() > 1);
    return splittedPath.last();
}

qint64 Explorer::GetSize(const QList<QString>& filesPaths)
{
    qint64 totalSize = 0;

    foreach (const auto& path, filesPaths) {
        QFile file(path);
        if (file.open(QIODevice::ReadOnly)) {
            totalSize += file.size();
        }
        else {
            totalSize = 0;
            break;
        }
    }

    return totalSize;
}

BaseFileInfo::Type Explorer::GetTypeByPath(const QString& path)
{
    if (path.endsWith('/')) {
        return BaseFileInfo::Type::Driver;
    }
    else if (QDir(path).exists()) {
        return BaseFileInfo::Type::Folder;
    }
    else if (QFile::exists(path)) {
        return BaseFileInfo::Type::File;
    }
    else {
        qWarning() << "Unknown file type, path: " << path;
        return BaseFileInfo::Type::Unknown;
    }
}

quint16 Explorer::FindNextCopyFileIndex(const QString& path,
                                        const QString& fileName)
{
    QDir dir(path);
    Q_ASSERT(dir.exists());

    auto nameWithoutExt = QFileInfo(path, fileName).baseName();
    auto filesInfoList = dir.entryInfoList(QDir::Files |
                                           QDir::Dirs |
                                           QDir::QDir::NoDotAndDotDot);

    // Convert file infos list to regex matches list
    QList<QRegularExpressionMatch> regexMatchesList;
    foreach (const auto& fileInfo, filesInfoList) {
        QRegularExpression re(QString(COPY_FILE_NAME_REGEX_TEMPLATE).arg(nameWithoutExt));
        auto match = re.match(fileInfo.fileName());

        if (match.hasMatch() && match.hasCaptured(REGEX_FIRST_CAPTURED)) {
            regexMatchesList.append(match);
        }
    }

    // Sort regex matches list
    std::sort(regexMatchesList.begin(), regexMatchesList.end(),
              [&](const auto& lRegexMatch, const auto& rRegexMatch){
                  return lRegexMatch.captured(REGEX_FIRST_CAPTURED).toInt() <
                         rRegexMatch.captured(REGEX_FIRST_CAPTURED).toInt();
              });

    // Determine next copy file index
    quint16 nextCopyFileIndex = DEFAULT_NEXT_COPY_FILE_INDEX;
    foreach (const auto& regexMatch, regexMatchesList) {
        auto curCopyFileIndex = regexMatch.captured(REGEX_FIRST_CAPTURED);

        if ((curCopyFileIndex.toInt() - nextCopyFileIndex) > 1) {
            return nextCopyFileIndex + 1;
        }
        else {
            nextCopyFileIndex = curCopyFileIndex.toInt();
        }
    }

    return nextCopyFileIndex + 1;
}
