#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QDir>
#include "Controller.hpp"


int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;
    const QUrl url("qrc:/QtFileExplorer/MainWindow.qml");

    Controller controller;
    engine.rootContext()->setContextProperty("controller", &controller);

    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
        &app, [url](QObject *obj, const QUrl &objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        }, Qt::QueuedConnection);
    engine.load(url);

//    QDir dir("D:/Qt");
//    qWarning() << dir.exists();
//    auto files = dir.entryList(QDir::Files | QDir::Dirs | QDir::QDir::NoDotAndDotDot,
//                               QDir::DirsFirst | QDir::IgnoreCase);
//    foreach(auto& file, files) {
//        qWarning() << file;
//    }

//    foreach(auto& drive, QDir::drives()) {
//        qWarning() << drive.path();
//    }


    return app.exec();
}
