#pragma once


#include <QQuickImageProvider>
#include <QFileIconProvider>
#include <QFileInfo>


class FileIconProvider : public QQuickImageProvider
{
public:
    FileIconProvider();

public:
    QPixmap requestPixmap(const QString& file,
                          QSize *size,
                          const QSize &requestedSize) override;
};
