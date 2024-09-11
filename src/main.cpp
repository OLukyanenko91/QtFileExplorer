#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QDir>
#include <QQuickStyle>
#include "Controller.hpp"
#include "Explorer/IconProvider.hpp"
#include "src/Explorer/FileInfo/BaseFileInfo.hpp"


int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;
    const QUrl url("qrc:/QtFileExplorer/qml/MainWindow.qml");

    Controller controller;
    engine.rootContext()->setContextProperty("controller", &controller);
    engine.addImageProvider("fileIconProvider", new IconProvider);

    qmlRegisterType<BaseFileInfo>("CustomData", 0, 1, "ItemInfo");

    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
        &app, [url](QObject* obj, const QUrl& objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        }, Qt::QueuedConnection);

    QQuickStyle::setStyle("Fusion");
    engine.load(url);

    return app.exec();
}
