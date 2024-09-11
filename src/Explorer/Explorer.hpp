#pragma once

#include <QObject>
#include <QDir>
#include <QIcon>
#include <QFileSystemWatcher>
#include "History/History.hpp"
#include "ExplorerData.hpp"
#include "FileInfo/BaseFileInfo.hpp"


class Explorer : public QObject
{
    Q_OBJECT

signals:
    void ContentsChanged(const ExplorerData::BaseItemInfoList dirContents);
    void CurrentDirChanged(const QString path);
    void GlobalHistoryPositionChanged(const NHistory::GlobalPosition position);

public:
    Explorer();

public:
    void Cd(const QString path);
    void Cd(const ExplorerData::CdDirection direction);
    void Update();

public:
    static QString            CreateNewFileName(const QString& path,
                                                const QString& fileName);
    static void               CreateDirectory(const QString& path);
    static void               RenameFile(const QString& path,
                                         const QString& newName);
    static QString            GetFileName(const QString& path);
    static qint64             GetSize(const QList<QString>& filesPaths);
    static BaseFileInfo::Type GetTypeByPath(const QString& path);

private:
    ExplorerData::BaseItemInfoList GetSystemDrivers() const;
    ExplorerData::BaseItemInfoList GetCurDirContents();

    void SetCurDir(const QString path);
    void HandleSystemWatcherUpdate(const QString& path);

private:
    static QString ConvertBytesToString(const quint64 bytes);
    static quint16 FindNextCopyFileIndex(const QString& path,
                                         const QString& fileName);

private:
    QFileSystemWatcher mSystemWatcher;
    QDir               mCurDir;
    History            mHistory;
};
