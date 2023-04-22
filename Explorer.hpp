#ifndef EXPLORER_HPP
#define EXPLORER_HPP

#include <QObject>
#include <QDir>


class Explorer : public QObject
{
    Q_OBJECT

signals:
    void ContentsChanged(const QStringList dirContents);

public:
    QStringList GetSystemDrivers() const;
    void        Open(const QString fileName);

private:
    QDir mCurrentDir;
};

#endif // EXPLORER_HPP
