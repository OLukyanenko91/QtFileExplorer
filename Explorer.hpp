#ifndef EXPLORER_HPP
#define EXPLORER_HPP

#include <QObject>
#include <QDir>
#include "History.hpp"


namespace ExplorerData {
    enum class CD_DIRECTION {
        BACK,
        FORWARD,
        UP
    };

    static const QString ROOT_DIRECTORY = ".";
}

class Explorer : public QObject
{
    Q_OBJECT

signals:
    void ContentsChanged(const QStringList dirContents);
    void CurrentDirChanged(const QString path);

public:
    void Cd(const QString path);
    void Cd(const ExplorerData::CD_DIRECTION direction);

private:
    QStringList GetSystemDrivers() const;
    QStringList GetCurDirContents();
    void        SetCurDir(const QString path);

private:
    QDir    mCurDir;
    History mHistory;
};

#endif // EXPLORER_HPP
