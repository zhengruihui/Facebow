#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtQuick3D/qquick3d.h>
#include <QTranslator>

#include "SerialPort/serialport.h"
#include "patient.h"


//static QObject *singletontype_callback(QQmlEngine *engine, QJSEngine *scriptEngine)
//{
//    Q_UNUSED(engine)
//    Q_UNUSED(scriptEngine)

//    Patient *patient = new Patient();
//    return patient;
//}

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QSurfaceFormat::setDefaultFormat(QQuick3D::idealSurfaceFormat());

    QTranslator *qtTranslator = new QTranslator();

    if(qtTranslator->load(":/Language/ChineseSimpilifed.qm")){
        app.installTranslator(qtTranslator);
    }

    qmlRegisterType<Patient>("Patient",1,0,"Patient");
    qmlRegisterType<SerialPort>("SerialPort",1,0,"SerialPort");


    //qmlRegisterSingletonType<Patient>("Patient", 1, 0, "PatientApi", singletontype_callback);


    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;


    return app.exec();
}


