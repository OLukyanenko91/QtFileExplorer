#pragma once

#include <QQuickImageProvider>
#include <QFileIconProvider>
#include <QFileInfo>


class IconProvider : public QQuickImageProvider
{
public:
    IconProvider();

public:
    QPixmap requestPixmap(const QString& file,
                          QSize* size,
                          const QSize& requestedSize) override;
};
