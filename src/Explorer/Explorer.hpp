#pragma once

#include <QObject>
#include <QDir>
#include <QIcon>
#include <QFileSystemWatcher>
#include "History/History.hpp"
#include "ExplorerData.hpp"


class Explorer : public QObject
{
    Q_OBJECT

signals:
    void ContentsChanged(const ExplorerData::FileList dirContents);
    void CurrentDirChanged(const QString path);
    void GlobalHistoryPositionChanged(const NHistory::GlobalPosition position);

public:
    Explorer();

public:
    void Cd(const QString path);
    void Cd(const ExplorerData::CdDirection direction);
    void Update();

private:
    ExplorerData::FileList GetSystemDrivers() const;
    ExplorerData::FileList GetCurDirContents();
    void                   SetCurDir(const QString path);

    void                   HandleSystemWatcherUpdate(const QString& path);

private:
    QFileSystemWatcher mSystemWatcher;
    QDir               mCurDir;
    History            mHistory;
};
