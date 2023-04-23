#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP

#include <QObject>
#include <QStringList>
#include "Explorer.hpp"


class Controller : public QObject
{
    Q_OBJECT

public:
    Q_INVOKABLE void openDirectory(const QString path);
    Q_INVOKABLE void goBack();
    Q_INVOKABLE void goForward();

    Q_PROPERTY(QString rootDirectory READ rootDirectory)

public:
    Controller();

public:
    QString rootDirectory() const;

signals:
    void updateUIContents(const QStringList currentContents);
    void updateUICurrentDirectory(const QString path);

private slots:
    void onDirContentsChanged(const QStringList dirContents);
    void onCurDirChanged(const QString path);

private:
    Explorer mExplorer;
};

#endif // CONTROLLER_HPP
