#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QDir>
#include "Controller.hpp"
#include "Explorer/File/File.hpp"
#include "Explorer/File/FileIconProvider.hpp"


int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;
    const QUrl url("qrc:/QtFileExplorer/MainWindow.qml");

    Controller controller;
    engine.rootContext()->setContextProperty("controller", &controller);
    engine.addImageProvider("fileIconProvider", new FileIconProvider);

    qmlRegisterType<File>("CustomData", 0, 1, "FileType");

    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
        &app, [url](QObject *obj, const QUrl &objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
