#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP

#include <QObject>
#include <QStringList>
#include "Explorer/Explorer.hpp"
#include "Explorer/ExplorerData.hpp"


class Controller : public QObject
{
    Q_OBJECT

public:
    Q_INVOKABLE void open(const QString path);
    Q_INVOKABLE void goBack();
    Q_INVOKABLE void goForward();

    Q_PROPERTY(QString rootDirectory READ rootDirectory)

public:
    Controller();

public:
    QString rootDirectory() const;

signals:
    void updateUIContents(const ExplorerData::FileList currentContents);
    void updateUICurrentDirectory(const QString path);

private slots:
    void onDirContentsChanged(const ExplorerData::FileList dirContents);
    void onCurDirChanged(const QString path);

private:
    Explorer mExplorer;
};

#endif // CONTROLLER_HPP
