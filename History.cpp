#include <QDebug>
#include "History.hpp"


History::History()
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

    return mDirs[mCurPosition];
}

bool History::IsEmpty()
{
    return mDirs.isEmpty();
}
