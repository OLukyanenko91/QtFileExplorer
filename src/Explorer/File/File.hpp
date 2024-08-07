#pragma once

#include <QObject>
#include <QFileInfo>
#include <QIcon>
#include <QStorageInfo>


class File
{
    Q_GADGET

    Q_PROPERTY(QString name MEMBER mName)
    Q_PROPERTY(QString path MEMBER mPath)
    Q_PROPERTY(quint64 size MEMBER mSize)
    Q_PROPERTY(Type    type MEMBER mType)

public:
    enum class Type {
        Unknown,
        File,
        Folder,
        Driver
    };
    Q_ENUM(Type)

public:
    File();
    File(const QFileInfo& fileInfo);
    File(const QStorageInfo& storage);

public:
    static QString CreateNewFileName(const QString& path,
                                     const QString& fileName);
    static void    CreateDirectory(const QString& path);
    static void    RenameFile(const QString& path,
                              const QString& newName);
    static QString GetFileName(const QString& path);
    static QString GetSize(const QList<QString>& filesPaths);
    static Type    GetTypeByPath(const QString& path);

private:
    static QString ConvertBytesToString(const quint64 bytes);
    static quint16 FindNextCopyFileIndex(const QString& path,
                                         const QString& fileName);

private:
    QString mName;
    QString mPath;
    quint64 mSize {0};
    Type    mType {File::Type::Unknown};
};

Q_DECLARE_METATYPE(File)
