#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP

#include <QObject>
#include <QStringList>
#include "Explorer.hpp"


class Controller : public QObject
{
    Q_OBJECT

public:
    Q_INVOKABLE QStringList getDrivers() const;

private:
    Explorer mExplorer;
};

#endif // CONTROLLER_HPP
