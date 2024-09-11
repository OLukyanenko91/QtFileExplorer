#include <QDir>
#include <QFileIconProvider>
#include "BaseFileInfo.hpp"


BaseFileInfo::BaseFileInfo()
{}

BaseFileInfo::BaseFileInfo(const Type type,
           const QString& path,
           const QString& name)
    : mType(type)
    , mPath(path)
    , mName(name)
{}

BaseFileInfo::BaseFileInfo(const QFileInfo& fileInfo) {
    mType = fileInfo.isFile() ? Type::File :
            fileInfo.isDir() ? Type::Folder : Type::Unknown;
    mPath = fileInfo.filePath();
    mName = fileInfo.fileName();
}

BaseFileInfo::BaseFileInfo(const QStorageInfo& storage) {
    mType = Type::Driver;
    mPath = storage.rootPath();
    mName = QString("%1 (%2)").arg(storage.name(),
                                   storage.rootPath().removeLast());
}
