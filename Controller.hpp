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
    Q_INVOKABLE void        openFile(const QString fileName);

public:
    Controller();

signals:
    void updateUIContents(const QStringList currentContents);

private slots:
    void onDirContentsChanged(const QStringList dirContents);

private:
    Explorer mExplorer;
};

#endif // CONTROLLER_HPP
