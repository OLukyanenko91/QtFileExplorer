#include <QDir>
#include <QFileIconProvider>
#include "File.hpp"


qint8 File::INCORRECT_FILE_SIZE = -1;


File::File()
{}

File::File(const QFileInfo& fileInfo) {
    mType = Type::FILE;
    mPath = fileInfo.filePath();
    mName = fileInfo.fileName();
}

File::File(const QString& systemDriver) {
    mType = Type::DRIVER;
    mPath = systemDriver;
    mName = QString(systemDriver).remove(QChar('/'));
}

quint64 File::GetSize(const QString filePath)
{
    QFile file(filePath);
    if (file.open(QIODevice::ReadOnly)) {
        return file.size();
    }
    else {
        return INCORRECT_FILE_SIZE;
    }
}

File::Type File::GetTypeByPath(const QString &path)
{
    if (QDir(path).exists()) {
        return Type::FOLDER;
    }
    else if (QFile::exists(path)) {
        return Type::FILE;
    }
    else {
        qWarning() << "Unknown file type, path: " << path;
        return Type::UNKNOWN;
    }
}
