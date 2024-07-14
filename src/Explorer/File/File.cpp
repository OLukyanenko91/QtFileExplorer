#include <QDir>
#include <QFileIconProvider>
#include <QRegularExpression>
#include "File.hpp"


namespace
{
    const char*  COPY_FILE_NAME_REGEX_TEMPLATE = R"(^\Q%1\E - Copy \((\d+)\).*$)";
    const quint8 REGEX_FIRST_CAPTURED          = 1;
    const quint8 DEFAULT_NEXT_COPY_FILE_INDEX  = 2;
}


File::File()
{}

File::File(const QFileInfo& fileInfo) {
    mType = Type::File;
    mPath = fileInfo.filePath();
    mName = fileInfo.fileName();
}

File::File(const QStorageInfo& storage) {
    mType = Type::Driver;
    mPath = storage.rootPath();
    mName = QString("%1 (%2)").arg(storage.name(),
                                   storage.rootPath().removeLast());
}

QString File::CreateNewFileName(const QString& path,
                                const QString& fileName)
{
    qInfo() << "Create new file name, path:" << path << ", file name:" << fileName;

    QFileInfo fileInfo(path + '/' + fileName);
    QString fileExt = fileInfo.suffix();
    QString baseFileName = fileInfo.baseName();

    QString newFileName = QString("%1 - Copy.%2").arg(baseFileName, fileExt);
    if (QFileInfo::exists(path + '/' + newFileName)) {
        newFileName = QString("%1 - Copy (2).%2").arg(baseFileName, fileExt);
        if (QFileInfo::exists(path + '/' + newFileName)) {
            auto nextIndex = FindNextCopyFileIndex(path, fileName);
            return QString("%1 - Copy (%2).%3").arg(baseFileName,
                                                    QString::number(nextIndex),
                                                    fileExt);
        }
        else {
            return newFileName;
        }
    }
    else {
        return newFileName;
    }
}

void File::CreateDirectory(const QString& path)
{
    qInfo() << "Create directory, path" << path;

    if (QDir(path).exists()) {
        qWarning() << "Directory already exists";
    }
    else {
        bool result = QDir().mkdir(path);
        if (!result) {
            qWarning() << "Failed to create a directory";
        }
    }
}

QString File::GetFileName(const QString& path)
{
    auto splittedPath = path.split('/', Qt::SkipEmptyParts);

    Q_ASSERT(splittedPath.length() > 1);
    return splittedPath.last();
}

QString File::GetSize(const QList<QString>& filesPaths)
{
    qint64 totalSize = 0;

    foreach (const auto& path, filesPaths) {
        QFile file(path);
        if (file.open(QIODevice::ReadOnly)) {
            totalSize += file.size();
        }
        else {
            totalSize = 0;
            break;
        }
    }

    return ConvertBytesToString(totalSize);
}

File::Type File::GetTypeByPath(const QString& path)
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
    if (bytes == 0) {
        return "";
    }
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

quint16 File::FindNextCopyFileIndex(const QString& path,
                                    const QString& fileName)
{
    QDir dir(path);
    Q_ASSERT(dir.exists());

    auto nameWithoutExt = QFileInfo(path, fileName).baseName();
    auto filesInfoList = dir.entryInfoList(QDir::Files |
                                           QDir::Dirs |
                                           QDir::QDir::NoDotAndDotDot);

    // Convert file infos list to regex matches list
    QList<QRegularExpressionMatch> regexMatchesList;
    foreach (const auto& fileInfo, filesInfoList) {
        QRegularExpression re(QString(COPY_FILE_NAME_REGEX_TEMPLATE).arg(nameWithoutExt));
        auto match = re.match(fileInfo.fileName());

        if (match.hasMatch() && match.hasCaptured(REGEX_FIRST_CAPTURED)) {
            regexMatchesList.append(match);
        }
    }

    // Sort regex matches list
    std::sort(regexMatchesList.begin(), regexMatchesList.end(),
              [&](const auto& lRegexMatch, const auto& rRegexMatch){
        return lRegexMatch.captured(REGEX_FIRST_CAPTURED).toInt() <
               rRegexMatch.captured(REGEX_FIRST_CAPTURED).toInt();
    });

    // Determine next copy file index
    quint16 nextCopyFileIndex = DEFAULT_NEXT_COPY_FILE_INDEX;
    foreach (const auto& regexMatch, regexMatchesList) {
        auto curCopyFileIndex = regexMatch.captured(REGEX_FIRST_CAPTURED);

        if ((curCopyFileIndex.toInt() - nextCopyFileIndex) > 1) {
            return nextCopyFileIndex + 1;
        }
        else {
            nextCopyFileIndex = curCopyFileIndex.toInt();
        }
    }

    return nextCopyFileIndex + 1;
}
