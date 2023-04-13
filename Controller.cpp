#include "Controller.hpp"


QStringList Controller::getDrivers() const
{
    return mExplorer.GetSystemDrivers();
}

