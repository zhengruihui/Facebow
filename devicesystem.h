#ifndef DEVICESYSTEM_H
#define DEVICESYSTEM_H

#include <QObject>
#include <QThread>
#include "SerialPort/serialport.h"
#include "Database/database.h"
#include <QTime>

class DeviceSystem : public QObject
{
    Q_OBJECT
public:
    static DeviceSystem *getInstance();

    static void setCurrentDatabaseID(QString value);
    static QString getCurrentDatabaseID();

    static void initDeviceSystem();

    static void initDataBase();

    static void setMeasureStart(bool value);

    static void setStep(int value);

    static int getStep();

    static Database *getDatabase();

    static SerialPort *getSerialPort();


    static void paintChart();
//    static void paintChartMain();
//    static void paintChartMain();
//    static void paintChartMain();


    //static void getStaticCoord(int id, int step);


private slots:
    static void on_posDataChanged(float x, float y, float z, float c, float p, float r);
    static void on_queryPosChanged(int step, QSqlQuery query);


signals:
    void facebowPosChanged(float x, float y, float z, float c, float p, float r);

    void vertexDataChanged(QString step, QVector<float> vertexTooth, QVector<float> vertexLeftCondyle, QVector<float> vertexRightCondyle);

    void vertexStaticDataChanged(int step, float *forwardStaticCoord, float *leftStaticCoord, float *rightStaticCoord);



private:
    DeviceSystem(){}
    static DeviceSystem *self;

    static int step;
    static bool measureStart;

    static QString dataBaseID;

    static SerialPort *serialPort;

    static Database *dataBase;

    static QThread *systemThread;

    static QVector<float> *vertexTooth;
    static QVector<float> *vertexLeftCondyle;
    static QVector<float> *vertexRightCondyle;
    static QVector<float> *vertexDataStaticForward;
    static QVector<float> *vertexDataStaticLeft;
    static QVector<float> *vertexDataStaticRight;

    static QTime startTime;

};


#endif // DEVICESYSTEM_H
