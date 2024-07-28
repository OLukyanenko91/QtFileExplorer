#pragma once

#include <QObject>
#include <QString>
#include <QStringList>


namespace NHistory
{
    enum class GlobalPosition
    {
        UNKNOWN = 0,
        BEGIN,
        MIDDLE,
        END
    };
}


class History : public QObject
{
    Q_OBJECT

signals:
    void GlobalPositionNotification(const NHistory::GlobalPosition position);

public:
    History();

public:
    void    Add(const QString& path);
    QString MoveBack();
    QString MoveForward();
    bool    IsEmpty();

private:
    void DetermineGlobalPosition();

private:
    QStringList mDirs;
    int         mCurPosition;
};
