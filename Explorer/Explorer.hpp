#pragma once

#include <QObject>
#include <QDir>
#include <QIcon>
#include "History/History.hpp"
#include "ExplorerData.hpp"


class Explorer : public QObject
{
    Q_OBJECT

signals:
    void ContentsChanged(const ExplorerData::FileList dirContents);
    void CurrentDirChanged(const QString path);

public:
    void Cd(const QString path);
    void Cd(const ExplorerData::CdDirection direction);
    void Update();

private:
    QStringList            GetSystemDrivers() const;
    ExplorerData::FileList GetCurDirContents();
    void                   SetCurDir(const QString path);

private:
    QDir    mCurDir;
    History mHistory;
};
