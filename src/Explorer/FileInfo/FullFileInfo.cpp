#include <QDirIterator>
#include "FullFileInfo.hpp"
#include "src/Explorer/Explorer.hpp"


FullFileInfo::FullFileInfo()
{}

FullFileInfo FullFileInfo::Create(const QString path)
{
    qInfo() << "Create, path" << path;

    auto fullInfo = FullFileInfo();
    auto type = Explorer::GetTypeByPath(path);
    auto timeFormat = "dd ddd yyyy, hh:mm:ss";

    if (type == BaseFileInfo::Type::Driver) {
        auto storage = QStorageInfo(path);

        fullInfo.SetName(storage.displayName());
        fullInfo.SetDiskType(storage.name());
        fullInfo.SetFileSystem(storage.fileSystemType());
        fullInfo.SetDiskLetter(path.first(1));
        fullInfo.SetCapacity(storage.bytesTotal());
        fullInfo.SetFreeSpace(storage.bytesFree());
        fullInfo.SetUsedSpace(storage.bytesTotal() - storage.bytesFree());
    }
    else if (type == BaseFileInfo::Type::File) {
        auto fileInfo = QFileInfo(path);

        fullInfo.SetPath(path);
        fullInfo.SetName(fileInfo.fileName());
        fullInfo.SetSuffix(fileInfo.suffix());
        fullInfo.SetLocation(fileInfo.absolutePath());
        fullInfo.SetOnlyReadingFlag(!fileInfo.isWritable());
        fullInfo.SetHiddenFlag(fileInfo.isHidden());
        fullInfo.SetSize(fileInfo.size());
        fullInfo.SetCreatedTime(fileInfo.birthTime().toString(timeFormat));
        fullInfo.SetLastReadTime(fileInfo.lastRead().toString(timeFormat));
        fullInfo.SetLastModifiedTime(fileInfo.lastModified().toString(timeFormat));
    }
    else if (type == BaseFileInfo::Type::Folder) {
        auto folderInfo = QFileInfo(path);

        fullInfo.SetName(folderInfo.fileName());
        fullInfo.SetLocation(folderInfo.absolutePath());
        fullInfo.SetCreatedTime(folderInfo.birthTime().toString(timeFormat));
        fullInfo.SetOnlyReadingFlag(!folderInfo.isWritable());
        fullInfo.SetHiddenFlag(folderInfo.isHidden());

        QDirIterator it(path,
                        QDir::Dirs | QDir::Files | QDir::NoDotAndDotDot,
                        QDirIterator::Subdirectories);
        qint64 totalSize = 0;
        qint64 subFilesCount = 0;
        qint64 subFoldersCount = 0;

        while (it.hasNext()) {
            QString path = it.next();
            auto type = Explorer::GetTypeByPath(path);
            if (type == BaseFileInfo::Type::File) {
                auto subFileInfo = QFileInfo(path);
                totalSize += subFileInfo.size();
                subFilesCount += 1;
            }
            else if (type == BaseFileInfo::Type::Folder) {
                subFoldersCount += 1;
            }
        }

        fullInfo.SetSize(totalSize);
        fullInfo.SetSubFilesCount(subFilesCount);
        fullInfo.SetSubFoldersCount(subFoldersCount);
    }
    else {
        return FullFileInfo();
    }

    return fullInfo;
}
