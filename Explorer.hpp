#ifndef EXPLORER_HPP
#define EXPLORER_HPP

#include <QObject>


class Explorer : public QObject
{
    Q_OBJECT

public:
    QStringList GetSystemDrivers() const;
};

#endif // EXPLORER_HPP
