#include <QDebug>
#include "History.hpp"


namespace
{
    const quint8 MAX_SIZE         = 10;
    const quint8 INVALID_POSITION = -1;
}

History::History()
    : mCurPosition(INVALID_POSITION)
{
    mDirs.reserve(sizeof(QString) * 10);
}

void History::Add(const QString& path)
{
    // Delete part of history if current position isn't at the end
    if (mDirs.count() && mCurPosition != mDirs.count() - 1) {
        mDirs.remove(mCurPosition + 1,
                     mDirs.count() - 1 - mCurPosition);
    }

    // Delete old item if history is full
    if (mDirs.count() == MAX_SIZE) {
        mDirs.pop_front();
    }

    mDirs.push_back(path);
    mCurPosition = mDirs.count() - 1;

    DetermineGlobalPosition();
}

QString History::MoveBack()
{
    // If history is empty
    if (IsEmpty()) {
        return QString();
    }

    // If current position isn't at the beginning
    if (mCurPosition > 0) {
        mCurPosition--;
    }

    DetermineGlobalPosition();

    return mDirs[mCurPosition];
}

QString History::MoveForward()
{
    // If history is empty
    if (IsEmpty()) {
        return QString();
    }

    // If current position isn't at the end
    if (mCurPosition < mDirs.length() - 1) {
        mCurPosition++;
    }

    DetermineGlobalPosition();

    return mDirs[mCurPosition];
}

bool History::IsEmpty()
{
    return mDirs.isEmpty();
}

void History::DetermineGlobalPosition()
{
    emit GlobalPositionNotification(IsEmpty() || mDirs.length() == 1   ? NHistory::GlobalPosition::UNKNOWN :
                                    mCurPosition == 0                  ? NHistory::GlobalPosition::BEGIN :
                                    mCurPosition == mDirs.length() - 1 ? NHistory::GlobalPosition::END :
                                                                         NHistory::GlobalPosition::MIDDLE);
}
