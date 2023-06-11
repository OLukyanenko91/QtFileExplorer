#include "Controller.hpp"


Controller::Controller()
{
    connect(&mExplorer, &Explorer::ContentsChanged, this, &Controller::onDirContentsChanged);
    connect(&mExplorer, &Explorer::CurrentDirChanged, this, &Controller::onCurDirChanged);
}

QString Controller::rootDirectory() const
{
    return ExplorerData::ROOT_DIRECTORY;
}

void Controller::open(const QString path)
{
    mExplorer.Cd(path);
}

void Controller::goBack()
{
    mExplorer.Cd(ExplorerData::CD_DIRECTION::BACK);
}

void Controller::goForward()
{
    mExplorer.Cd(ExplorerData::CD_DIRECTION::FORWARD);
}

void Controller::onDirContentsChanged(const ExplorerData::FileList dirContents)
{
    emit updateUIContents(dirContents);
}

void Controller::onCurDirChanged(const QString path)
{
    emit updateUICurrentDirectory(path);
}

