#pragma once

#include "BaseFileInfo.hpp"


class FullFileInfo : BaseFileInfo
{
    Q_GADGET

    // DISK INFO
    Q_PROPERTY(QString diskType   MEMBER mDiskType)
    Q_PROPERTY(QString diskLetter MEMBER mDiskLetter)
    Q_PROPERTY(QString fileSystem MEMBER mFileSystem)
    Q_PROPERTY(quint64 capacity   MEMBER mCapacity)
    Q_PROPERTY(quint64 freeSpace  MEMBER mFreeSpace)
    Q_PROPERTY(quint64 usedSpace  MEMBER mUsedSpace)

    // COMMON FILE/FOLDER INFO
    Q_PROPERTY(QString location    MEMBER mLocation)
    Q_PROPERTY(quint64 size        MEMBER mSize)
    Q_PROPERTY(QString createdTime MEMBER mCreatedTime)
    Q_PROPERTY(bool    onlyReading MEMBER mOnlyReading)
    Q_PROPERTY(bool    hidden      MEMBER mHidden)

    // FILE INFO
    Q_PROPERTY(QString suffix           MEMBER mSuffix)
    Q_PROPERTY(QString lastReadTime     MEMBER mLastReadTime)
    Q_PROPERTY(QString lastModifiedTime MEMBER mLastModifiedTime)

    // FOLDER INFO
    Q_PROPERTY(quint64 subFilesCount   MEMBER mSubFilesCount)
    Q_PROPERTY(quint64 subFoldersCount MEMBER mSubFoldersCount)

public:
    FullFileInfo();

public:
    // DISK INFO
    void SetDiskType(const QString diskType) { mDiskType = diskType; };
    void SetDiskLetter(const QString diskLetter) { mDiskLetter = diskLetter; };
    void SetFileSystem(const QString fileSystem) { mFileSystem = fileSystem; };
    void SetCapacity(const quint64 capacity) { mCapacity = capacity; };
    void SetFreeSpace(const quint64 freeSpace) { mFreeSpace = freeSpace; };
    void SetUsedSpace(const quint64 usedSpace) { mUsedSpace = usedSpace; };

    // COMMON FILE/FOLDER INFO
    void SetLocation(const QString location) { mLocation = location; };
    void SetSize(const quint64 size) { mSize = size; };
    void SetCreatedTime(const QString createdTime) { mCreatedTime = createdTime; };
    void SetOnlyReadingFlag(const bool onlyReading) { mOnlyReading = onlyReading; };
    void SetHiddenFlag(const bool hidden) { mHidden = hidden; };

    // FILE INFO
    void SetSuffix(const QString suffix) { mSuffix = suffix; };
    void SetLastReadTime(const QString lastReadTime) { mLastReadTime = lastReadTime; };
    void SetLastModifiedTime(const QString lastModifiedTime) { mLastModifiedTime = lastModifiedTime; };

    // FOLDER INFO
    void SetSubFilesCount(const quint64 subFilesCount) { mSubFilesCount = subFilesCount; };
    void SetSubFoldersCount(const quint64 subFoldersCount) { mSubFoldersCount = subFoldersCount; };

public:
    static FullFileInfo Create(const QString path);

private:
    // DISK INFO
    QString mDiskType;
    QString mDiskLetter;
    QString mFileSystem;
    quint64 mCapacity;
    quint64 mFreeSpace;
    quint64 mUsedSpace;

    // COMMON FILE/FOLDER INFO
    QString mLocation;
    quint64 mSize;
    QString mCreatedTime;
    bool    mOnlyReading;
    bool    mHidden;

    // FILE INFO
    QString mSuffix;
    QString mLastReadTime;
    QString mLastModifiedTime; 

    // FOLDER INFO
    quint64 mSubFilesCount;
    quint64 mSubFoldersCount;
};
