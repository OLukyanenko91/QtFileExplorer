#ifndef HISTORY_HPP
#define HISTORY_HPP

#include <QString>
#include <QStringList>


class History {
    static const int MAX_SIZE         = 10;
    static const int INVALID_POSITION = -1;

public:
    History();

public:
    void    Add(const QString& path);
    QString MoveBack();
    QString MoveForward();
    bool    IsEmpty();

private:
    QStringList mDirs;
    int         mCurPosition = INVALID_POSITION;
};

#endif // HISTORY_HPP
