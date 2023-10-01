#include "FileIconProvider.hpp"


namespace {
    static const quint8 ICON_SIZE = 50;
}


FileIconProvider::FileIconProvider()
    : QQuickImageProvider(QQuickImageProvider::Pixmap)
{}

QPixmap FileIconProvider::requestPixmap(const QString& file,
                                        QSize* size,
                                        const QSize &requestedSize)
{
    QFileInfo fileInfo(file);
    QIcon fileIcon(QFileIconProvider().icon(fileInfo));

    return fileIcon.pixmap(ICON_SIZE,
                           ICON_SIZE);
}
