#include <QDir>
#include <QFileIconProvider>
#include "File.hpp"


File::File()
{}

File::File(const QFileInfo& fileInfo) {
    mType = Type::File;
    mPath = fileInfo.filePath();
    mName = fileInfo.fileName();
}

File::File(const QString& systemDriver) {
    mType = Type::Driver;
    mPath = systemDriver;
    mName = QString(systemDriver).remove(QChar('/'));
}

QString File::GetSize(const QString filePath)
{
    QFile file(filePath);
    if (file.open(QIODevice::ReadOnly)) {
        return ConvertBytesToString(file.size());
    }
    else {
        qWarning() << "Can't open file, path" << filePath;
        return QString();
    }
}

File::Type File::GetTypeByPath(const QString &path)
{
    if (QDir(path).exists()) {
        return Type::Folder;
    }
    else if (QFile::exists(path)) {
        return Type::File;
    }
    else {
        qWarning() << "Unknown file type, path: " << path;
        return Type::Unknown;
    }
}

QString File::ConvertBytesToString(const quint64 bytes)
{
    if (bytes < 1024) {
        return QString::number(bytes) + " bytes";
    }
    else if (bytes < (1024 * 1024)) {
        return QString::number(bytes / 1024.0, 'f', 1) + " KB";
    }
    else if (bytes < (1024 * 1024 * 1024)) {
        return QString::number(bytes / (1024 * 1024.0), 'f', 1) + " MB";
    }
    else if (bytes < (quint64(1024 * 1024 * 1024) * 1024)) {
        return QString::number(bytes / (1024 * 1024 * 1024.0), 'f', 1) + " GB";
    }
    else {
        qWarning() << "Can't convert so many bytes..." << bytes;
        return QString();
    }
}
