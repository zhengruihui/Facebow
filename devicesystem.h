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

    static void setCurrentPatientInfo(QString ID, QString name, QString birthday, QString sex);
    static QString getCurrentDatabaseID();
    static QString getCurrentName();
    static QString getCurrentBitrhday();
    static QString getCurrentSex();

    QVector3D getLeftStaticCoord();
    QVector3D getRightStaticCoord();

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

    static void generateChartIMage();


    //static void getStaticCoord(int id, int step);

    static void test();

    static void drawImage(QString name, QPixmap pixmap);


private slots:
    static void on_posDataChanged(float x, float y, float z, float c, float p, float r);
    static void on_queryPosChanged(int step, QSqlQuery query);


signals:
    void facebowPosChanged(float x, float y, float z, float c, float p, float r);

    void vertexDataChanged(QString step, QVector<float> vertexTooth, QVector<float> vertexLeftCondyle, QVector<float> vertexRightCondyle);

    void vertexStaticDataChanged(int step, float *forwardStaticCoord, float *leftStaticCoord, float *rightStaticCoord);

    void loadImage(int step);

private:
    DeviceSystem(){}
    static DeviceSystem *self;

    static int step;
    static bool measureStart;

    static QString patientDataBaseID;
    static QString patientName;
    static QString patientBirthday;
    static QString patientSex;

    static SerialPort *serialPort;

    static Database *dataBase;

    static QThread *systemThread;

    static QTime startTime;

    static int margin;

    static QVector<float> vertexForwardTooth;
    static QVector<float> vertexLeftCondyle;
    static QVector<float> vertexRightCondyle;
    static QVector<float> vertexDataStaticForward;
    static QVector<float> vertexDataStaticLeft;
    static QVector<float> vertexDataStaticRight;





    //MoveForward
    static QVector<float> MoveForward_Forward_In_X;
    static QVector<float> MoveForward_Forward_In_Y;
    static QVector<float> MoveForward_Forward_In_Z;
    static QVector<float> MoveForward_Left_In_X;
    static QVector<float> MoveForward_Left_In_Y;
    static QVector<float> MoveForward_Left_In_Z;
    static QVector<float> MoveForward_Right_In_X;
    static QVector<float> MoveForward_Right_In_Y;
    static QVector<float> MoveForward_Right_In_Z;

    static float* MoveForward_Forward_Out_X;
    static float* MoveForward_Forward_Out_Y;
    static float* MoveForward_Forward_Out_Z;
    static float* MoveForward_Left_Out_X;
    static float* MoveForward_Left_Out_Y;
    static float* MoveForward_Left_Out_Z;
    static float* MoveForward_Right_Out_X;
    static float* MoveForward_Right_Out_Y;
    static float* MoveForward_Right_Out_Z;

    //MoveLeft
    static QVector<float> MoveLeft_Forward_In_X;
    static QVector<float> MoveLeft_Forward_In_Y;
    static QVector<float> MoveLeft_Forward_In_Z;
    static QVector<float> MoveLeft_Left_In_X;
    static QVector<float> MoveLeft_Left_In_Y;
    static QVector<float> MoveLeft_Left_In_Z;
    static QVector<float> MoveLeft_Right_In_X;
    static QVector<float> MoveLeft_Right_In_Y;
    static QVector<float> MoveLeft_Right_In_Z;

    static float* MoveLeft_Forward_Out_X;
    static float* MoveLeft_Forward_Out_Y;
    static float* MoveLeft_Forward_Out_Z;
    static float* MoveLeft_Left_Out_X;
    static float* MoveLeft_Left_Out_Y;
    static float* MoveLeft_Left_Out_Z;
    static float* MoveLeft_Right_Out_X;
    static float* MoveLeft_Right_Out_Y;
    static float* MoveLeft_Right_Out_Z;

    //MoveRight
    static QVector<float> MoveRight_Forward_In_X;
    static QVector<float> MoveRight_Forward_In_Y;
    static QVector<float> MoveRight_Forward_In_Z;
    static QVector<float> MoveRight_Left_In_X;
    static QVector<float> MoveRight_Left_In_Y;
    static QVector<float> MoveRight_Left_In_Z;
    static QVector<float> MoveRight_Right_In_X;
    static QVector<float> MoveRight_Right_In_Y;
    static QVector<float> MoveRight_Right_In_Z;

    static float* MoveRight_Forward_Out_X;
    static float* MoveRight_Forward_Out_Y;
    static float* MoveRight_Forward_Out_Z;
    static float* MoveRight_Left_Out_X;
    static float* MoveRight_Left_Out_Y;
    static float* MoveRight_Left_Out_Z;
    static float* MoveRight_Right_Out_X;
    static float* MoveRight_Right_Out_Y;
    static float* MoveRight_Right_Out_Z;

    //OpenClosed
    static QVector<float> OpenClosed_Forward_In_X;
    static QVector<float> OpenClosed_Forward_In_Y;
    static QVector<float> OpenClosed_Forward_In_Z;
    static QVector<float> OpenClosed_Left_In_X;
    static QVector<float> OpenClosed_Left_In_Y;
    static QVector<float> OpenClosed_Left_In_Z;
    static QVector<float> OpenClosed_Right_In_X;
    static QVector<float> OpenClosed_Right_In_Y;
    static QVector<float> OpenClosed_Right_In_Z;

    static float* OpenClosed_Forward_Out_X;
    static float* OpenClosed_Forward_Out_Y;
    static float* OpenClosed_Forward_Out_Z;
    static float* OpenClosed_Left_Out_X;
    static float* OpenClosed_Left_Out_Y;
    static float* OpenClosed_Left_Out_Z;
    static float* OpenClosed_Right_Out_X;
    static float* OpenClosed_Right_Out_Y;
    static float* OpenClosed_Right_Out_Z;

    static int* out_len;


};


#endif // DEVICESYSTEM_H
