#ifndef FILEICONPROVIDER_HPP
#define FILEICONPROVIDER_HPP


#include <QQuickImageProvider>
#include <QFileIconProvider>
#include <QFileInfo>


class FileIconProvider : public QQuickImageProvider
{
public:
    FileIconProvider();

public:

    QPixmap requestPixmap(const QString& file, QSize *size, const QSize &requestedSize) override
    {
        QFileInfo fileInfo(file);
        QIcon fileIcon(QFileIconProvider().icon(fileInfo));

        return fileIcon.pixmap(50, 50);
    }
};

#endif // FILEICONPROVIDER_HPP
