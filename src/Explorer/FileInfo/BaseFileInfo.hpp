#pragma once

#include <QObject>
#include <QFileInfo>
#include <QIcon>
#include <QStorageInfo>


class BaseFileInfo
{
        Q_GADGET

        Q_PROPERTY(QString name MEMBER mName)
        Q_PROPERTY(QString path MEMBER mPath)
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
    BaseFileInfo();
    BaseFileInfo(const Type type,
                 const QString& path,
                 const QString& name);
    BaseFileInfo(const QFileInfo& fileInfo);
    BaseFileInfo(const QStorageInfo& storage);

public:
    void SetName(const QString name) { mName = name; }
    void SetPath(const QString path) { mPath = path; }
    void SetType(const Type type) { mType = type; }

protected:
    QString mName;
    QString mPath;
    Type    mType {Type::Unknown};
};

Q_DECLARE_METATYPE(BaseFileInfo)
