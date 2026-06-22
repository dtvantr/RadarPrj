#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QDebug>

#include "radarmodel.h"
#include "networkmanager.h"
#include "processmanager.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    // Core objects
    RadarModel radarModel;

    NetworkManager networkManager;

    ProcessManager processManager;

    // Connections
    QObject::connect(
        &networkManager,
        &NetworkManager::targetsParsed,
        &radarModel,
        &RadarModel::setTargets,
        Qt::QueuedConnection);

    // Start TCP server
    networkManager.startServer(5000);

    // Expose to QML
    engine.rootContext()->setContextProperty(
        "radarModel",
        &radarModel);

    engine.rootContext()->setContextProperty(
        "processManager",
        &processManager);

    // QML error handling
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        [](){
            QCoreApplication::exit(-1);
        },
        Qt::QueuedConnection);

    // Load QML
    engine.loadFromModule("RadarApp", "Main");

    if(engine.rootObjects().isEmpty())
    {
        qDebug() << "QML load failed!";
        return -1;
    }

    return app.exec();
}