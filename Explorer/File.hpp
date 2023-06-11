#ifndef FILE_HPP
#define FILE_HPP

#include <QObject>
#include <QFileInfo>
#include <QIcon>


class File
{
    Q_GADGET

    Q_PROPERTY(QString name MEMBER mName)
    Q_PROPERTY(QString path MEMBER mPath)
    Q_PROPERTY(quint64 size MEMBER mSize)
    Q_PROPERTY(Type    type MEMBER mType)

public:
    enum class Type {
        UNKNOWN,
        FILE,
        FOLDER,
        DRIVER
    };
    Q_ENUM(Type)

    static Type GetTypeByPath(const QString& path);

public:
    File(const QFileInfo& fileInfo);
    File(const QString& systemDriver);
    File(){}

private:
    QString mName;
    QString mPath;
    quint64 mSize {0};
    Type    mType {File::Type::UNKNOWN};
};

Q_DECLARE_METATYPE(File)

#endif // FILE_HPP
