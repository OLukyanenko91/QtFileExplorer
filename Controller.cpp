#include "Controller.hpp"


Controller::Controller()
{
    connect(&mExplorer, &Explorer::ContentsChanged, this, &Controller::onDirContentsChanged);
}

QStringList Controller::getDrivers() const
{
    return mExplorer.GetSystemDrivers();
}

void Controller::openFile(const QString fileName)
{
    mExplorer.Open(fileName);
}

void Controller::onDirContentsChanged(const QStringList dirContents)
{
    emit updateUIContents(dirContents);
}

