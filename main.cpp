#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtQuick3D/qquick3d.h>
#include "SerialPort/serialport.h"
#include <QTranslator>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QSurfaceFormat::setDefaultFormat(QQuick3D::idealSurfaceFormat());

    QTranslator *qtTranslator = new QTranslator();

    if(qtTranslator->load(":/Language/ChineseSimpilifed.qm")){
        app.installTranslator(qtTranslator);
    }


    qmlRegisterType<SerialPort>("SerialPort",1,0,"SerialPort");


    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;


    return app.exec();
}


