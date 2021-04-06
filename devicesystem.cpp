#include "devicesystem.h"
#include <QDebug>
#include <QMutex>
#include "DLL/Get_LeftCondyle_StaticCoord/Get_LeftCondyle_StaticCoord.h"
#include "DLL/Get_rightCondyle_StaticCoord/Get_RightCondyle_StaticCoord.h"
#include "DLL/MoveProcess/MoveProcess.h"
#include "DLL/MoveForward_Process/MoveForward_Process.h"
#include "DLL/MoveLeft_Process/MoveLeft_Process.h"
#include "DLL/MoveRight_Process/MoveRight_Process.h"
#include "DLL/Tooth_Coronal/Tooth_Coronal.h"
#include "DLL/Tooth_Horizontal/Tooth_Horizontal.h"
#include "DLL/Tooth_Sagittal/Tooth_Sagittal.h"
#include "DLL/OpenClosed_Process/OpenClosed_Process.h"
#include <QChart>
#include <QChartView>
#include <QtCharts>

#define N 101

DeviceSystem *DeviceSystem::self = nullptr;
SerialPort *DeviceSystem::serialPort = nullptr;
Database *DeviceSystem::dataBase = nullptr;

int DeviceSystem::step = 0;
int DeviceSystem::margin = 0;
bool DeviceSystem::measureStart = false;
QString DeviceSystem::patientDataBaseID = "-1";
QString DeviceSystem::patientName = "0";
QString DeviceSystem::patientBirthday = "0";
QString DeviceSystem::patientSex = "0";

QThread *DeviceSystem::systemThread = nullptr;
QVector<float> DeviceSystem::vertexForwardTooth;
QVector<float> DeviceSystem::vertexLeftCondyle;
QVector<float> DeviceSystem::vertexRightCondyle;
QVector<float> DeviceSystem::vertexDataStaticForward;
QVector<float> DeviceSystem::vertexDataStaticLeft;
QVector<float> DeviceSystem::vertexDataStaticRight;


QVector<float> DeviceSystem::MoveForward_Forward_In_X;
QVector<float> DeviceSystem::MoveForward_Forward_In_Y;
QVector<float> DeviceSystem::MoveForward_Forward_In_Z;
QVector<float> DeviceSystem::MoveForward_Left_In_X;
QVector<float> DeviceSystem::MoveForward_Left_In_Y;
QVector<float> DeviceSystem::MoveForward_Left_In_Z;
QVector<float> DeviceSystem::MoveForward_Right_In_X;
QVector<float> DeviceSystem::MoveForward_Right_In_Y;
QVector<float> DeviceSystem::MoveForward_Right_In_Z;

float* DeviceSystem::MoveForward_Forward_Out_X = nullptr;
float* DeviceSystem::MoveForward_Forward_Out_Y = nullptr;
float* DeviceSystem::MoveForward_Forward_Out_Z = nullptr;
float* DeviceSystem::MoveForward_Left_Out_X = nullptr;
float* DeviceSystem::MoveForward_Left_Out_Y = nullptr;
float* DeviceSystem::MoveForward_Left_Out_Z = nullptr;
float* DeviceSystem::MoveForward_Right_Out_X = nullptr;
float* DeviceSystem::MoveForward_Right_Out_Y = nullptr;
float* DeviceSystem::MoveForward_Right_Out_Z = nullptr;

QVector<float> DeviceSystem::MoveLeft_Forward_In_X;
QVector<float> DeviceSystem::MoveLeft_Forward_In_Y;
QVector<float> DeviceSystem::MoveLeft_Forward_In_Z;
QVector<float> DeviceSystem::MoveLeft_Left_In_X;
QVector<float> DeviceSystem::MoveLeft_Left_In_Y;
QVector<float> DeviceSystem::MoveLeft_Left_In_Z;
QVector<float> DeviceSystem::MoveLeft_Right_In_X;
QVector<float> DeviceSystem::MoveLeft_Right_In_Y;
QVector<float> DeviceSystem::MoveLeft_Right_In_Z;

float* DeviceSystem::MoveLeft_Forward_Out_X = nullptr;
float* DeviceSystem::MoveLeft_Forward_Out_Y = nullptr;
float* DeviceSystem::MoveLeft_Forward_Out_Z = nullptr;
float* DeviceSystem::MoveLeft_Left_Out_X = nullptr;
float* DeviceSystem::MoveLeft_Left_Out_Y = nullptr;
float* DeviceSystem::MoveLeft_Left_Out_Z = nullptr;
float* DeviceSystem::MoveLeft_Right_Out_X = nullptr;
float* DeviceSystem::MoveLeft_Right_Out_Y = nullptr;
float* DeviceSystem::MoveLeft_Right_Out_Z = nullptr;

QVector<float> DeviceSystem::MoveRight_Forward_In_X;
QVector<float> DeviceSystem::MoveRight_Forward_In_Y;
QVector<float> DeviceSystem::MoveRight_Forward_In_Z;
QVector<float> DeviceSystem::MoveRight_Left_In_X;
QVector<float> DeviceSystem::MoveRight_Left_In_Y;
QVector<float> DeviceSystem::MoveRight_Left_In_Z;
QVector<float> DeviceSystem::MoveRight_Right_In_X;
QVector<float> DeviceSystem::MoveRight_Right_In_Y;
QVector<float> DeviceSystem::MoveRight_Right_In_Z;

float* DeviceSystem::MoveRight_Forward_Out_X = nullptr;
float* DeviceSystem::MoveRight_Forward_Out_Y = nullptr;
float* DeviceSystem::MoveRight_Forward_Out_Z = nullptr;
float* DeviceSystem::MoveRight_Left_Out_X = nullptr;
float* DeviceSystem::MoveRight_Left_Out_Y = nullptr;
float* DeviceSystem::MoveRight_Left_Out_Z = nullptr;
float* DeviceSystem::MoveRight_Right_Out_X = nullptr;
float* DeviceSystem::MoveRight_Right_Out_Y = nullptr;
float* DeviceSystem::MoveRight_Right_Out_Z = nullptr;

QVector<float> DeviceSystem::OpenClosed_Forward_In_X;
QVector<float> DeviceSystem::OpenClosed_Forward_In_Y;
QVector<float> DeviceSystem::OpenClosed_Forward_In_Z;
QVector<float> DeviceSystem::OpenClosed_Left_In_X;
QVector<float> DeviceSystem::OpenClosed_Left_In_Y;
QVector<float> DeviceSystem::OpenClosed_Left_In_Z;
QVector<float> DeviceSystem::OpenClosed_Right_In_X;
QVector<float> DeviceSystem::OpenClosed_Right_In_Y;
QVector<float> DeviceSystem::OpenClosed_Right_In_Z;

float* DeviceSystem::OpenClosed_Forward_Out_X = nullptr;
float* DeviceSystem::OpenClosed_Forward_Out_Y = nullptr;
float* DeviceSystem::OpenClosed_Forward_Out_Z = nullptr;
float* DeviceSystem::OpenClosed_Left_Out_X = nullptr;
float* DeviceSystem::OpenClosed_Left_Out_Y = nullptr;
float* DeviceSystem::OpenClosed_Left_Out_Z = nullptr;
float* DeviceSystem::OpenClosed_Right_Out_X = nullptr;
float* DeviceSystem::OpenClosed_Right_Out_Y = nullptr;
float* DeviceSystem::OpenClosed_Right_Out_Z = nullptr;

int* DeviceSystem::out_len = nullptr;
QTime DeviceSystem::startTime = QTime();

float forwardStaticCoord[3] = {-2.8f, -7.9f, -65.67f};
float leftStaticCoord[3] = {62.00f, 1.00f, -132.00f};
float rightStaticCoord[3] = {-62.00f, 14.00f, -144.00f};

DeviceSystem *DeviceSystem::getInstance()
{
    if (self == nullptr) {

        static QMutex mutex;

        QMutexLocker locker(&mutex);

        if (self == nullptr) {
            self = new DeviceSystem;
            self->initDeviceSystem();
        }

    }

    return self;

}

void DeviceSystem::setCurrentPatientInfo(QString ID, QString name, QString birthday, QString sex)
{
    patientDataBaseID = ID;
    patientName = name;
    patientBirthday = birthday;
    patientSex = sex;

}

QString DeviceSystem::getCurrentDatabaseID()
{
    return patientDataBaseID;
}

QString DeviceSystem::getCurrentName()
{
    return patientName;
}

QString DeviceSystem::getCurrentBitrhday()
{
    return patientBirthday;
}

QString DeviceSystem::getCurrentSex()
{
    return patientSex;
}

QVector3D DeviceSystem::getLeftStaticCoord()
{
    return QVector3D(leftStaticCoord[0], leftStaticCoord[1], leftStaticCoord[2]);
}

QVector3D DeviceSystem::getRightStaticCoord()
{
    return QVector3D(rightStaticCoord[0], rightStaticCoord[1], rightStaticCoord[2]);
}

void DeviceSystem::initDeviceSystem()
{
    self->serialPort = new SerialPort();
    self->dataBase = new Database();
    self->systemThread = new QThread();


    self->serialPort->moveToThread(systemThread);
    self->dataBase->moveToThread(systemThread);
    self->moveToThread(systemThread);


    self->startTime = QTime::currentTime();

    systemThread->start();

    MoveForward_Forward_Out_X = new float[N];
    MoveForward_Forward_Out_Y = new float[N];
    MoveForward_Forward_Out_Z = new float[N];
    MoveForward_Left_Out_X = new float[N];
    MoveForward_Left_Out_Y = new float[N];
    MoveForward_Left_Out_Z = new float[N];
    MoveForward_Right_Out_X = new float[N];
    MoveForward_Right_Out_Y = new float[N];
    MoveForward_Right_Out_Z = new float[N];

    MoveLeft_Forward_Out_X = new float[N];
    MoveLeft_Forward_Out_Y = new float[N];
    MoveLeft_Forward_Out_Z = new float[N];
    MoveLeft_Left_Out_X = new float[N];
    MoveLeft_Left_Out_Y = new float[N];
    MoveLeft_Left_Out_Z = new float[N];
    MoveLeft_Right_Out_X = new float[N];
    MoveLeft_Right_Out_Y = new float[N];
    MoveLeft_Right_Out_Z = new float[N];

    MoveRight_Forward_Out_X = new float[N];
    MoveRight_Forward_Out_Y = new float[N];
    MoveRight_Forward_Out_Z = new float[N];
    MoveRight_Left_Out_X = new float[N];
    MoveRight_Left_Out_Y = new float[N];
    MoveRight_Left_Out_Z = new float[N];
    MoveRight_Right_Out_X = new float[N];
    MoveRight_Right_Out_Y = new float[N];
    MoveRight_Right_Out_Z = new float[N];

    OpenClosed_Forward_Out_X = new float[N];
    OpenClosed_Forward_Out_Y = new float[N];
    OpenClosed_Forward_Out_Z = new float[N];
    OpenClosed_Left_Out_X = new float[N];
    OpenClosed_Left_Out_Y = new float[N];
    OpenClosed_Left_Out_Z = new float[N];
    OpenClosed_Right_Out_X = new float[N];
    OpenClosed_Right_Out_Y = new float[N];
    OpenClosed_Right_Out_Z = new float[N];

    out_len = new int[3];

    QObject::connect(self->serialPort, &SerialPort::posDataChanged, self,  self->on_posDataChanged, Qt::QueuedConnection);

    QObject::connect(self->dataBase, &Database::queryPosChanged, self,  self->on_queryPosChanged, Qt::QueuedConnection);


}

void DeviceSystem::setMeasureStart(bool value)
{
    measureStart = value;
}

void DeviceSystem::setStep(int value)
{
    step = value;
}

int DeviceSystem::getStep()
{
    return step;
}

Database *DeviceSystem::getDatabase()
{
    return dataBase;
}

SerialPort *DeviceSystem::getSerialPort()
{
    return serialPort;
}

void DeviceSystem::paintChart()
{
        dataBase->queryPos(patientDataBaseID.toInt(), 1);
        dataBase->queryPos(patientDataBaseID.toInt(), 2);
        dataBase->queryPos(patientDataBaseID.toInt(), 3);
        dataBase->queryPos(patientDataBaseID.toInt(), 4);
        dataBase->queryPos(patientDataBaseID.toInt(), 5);
        dataBase->queryPos(patientDataBaseID.toInt(), 6);
        dataBase->queryPos(patientDataBaseID.toInt(), 7);
}

void DeviceSystem::generateChartIMage()
{


}

void DeviceSystem::test()
{


}



void DeviceSystem::on_posDataChanged(float x, float y, float z, float c, float p, float r)
{
    if(measureStart)
    {       
        dataBase->insertPosition(QString(patientDataBaseID).toInt(), step, x, y, z, c, p, r);
    }


    if(startTime.msecsTo(QTime::currentTime()) > 10)
    {
        self->startTime = startTime = QTime::currentTime();
        emit DeviceSystem::getInstance()->facebowPosChanged(x, y, z, c, p, r);
    }




}
//画图时，左髁突取（Z,Y），右髁突取(-Z,Y)，前牙水平面取(-X,Z)
void DeviceSystem::on_queryPosChanged(int step, QSqlQuery query)
{
    out_len[0] = 0;
    if(step==1) //前牙静态坐标
    {
        vertexDataStaticForward.clear();
        while(query.next())
        {
            for(int i=0; i<6; i++)
            {
               vertexDataStaticForward.append(query.value(i+1).toFloat());
            }

        }

    }
    else if(step==2) //左髁突静态坐标
    {
        vertexDataStaticLeft.clear();
        while(query.next())
        {
            for(int i=0; i<6; i++)
            {
               vertexDataStaticLeft.append(query.value(i+1).toFloat());
            }

        }

        if(vertexDataStaticLeft.size()>0)
        {
            Get_LeftCondyle_StaticCoord(vertexDataStaticLeft.data(), vertexDataStaticForward.data(), vertexDataStaticLeft.size()/6,vertexDataStaticForward.size()/6, leftStaticCoord);
        }
        else
        {
            leftStaticCoord[0] = 88.00f;
            leftStaticCoord[1] = 88.00f;
            leftStaticCoord[2] = 88.00f;
        }

        //qDebug() << "leftStaticCoord" << leftStaticCoord[0] << leftStaticCoord[1] <<leftStaticCoord[2];
    }
    else if(step==3) //右髁突静态坐标
    {
        vertexDataStaticRight.clear();
        while(query.next())
        {
            for(int i=0; i<6; i++)
            {
               vertexDataStaticRight.append(query.value(i+1).toFloat());
            }

        }
        if(vertexDataStaticRight.size()>0)
        {
            Get_RightCondyle_StaticCoord(vertexDataStaticRight.data(), vertexDataStaticForward.data(), vertexDataStaticRight.size()/6,vertexDataStaticForward.size()/6, rightStaticCoord);
        }
        else
        {
              rightStaticCoord[0] = 88.00f;
              rightStaticCoord[1] = 88.00f;
              rightStaticCoord[2] = 88.00f;
        }

        //qDebug() << "rightStaticCoord" << rightStaticCoord[0] << rightStaticCoord[1] <<rightStaticCoord[2];


    }
    else if(step==4) //前伸运动坐标
    {
        vertexForwardTooth.clear();
        vertexLeftCondyle.clear();
        vertexRightCondyle.clear();

        MoveForward_Forward_In_X.clear();
        MoveForward_Forward_In_Y.clear();
        MoveForward_Forward_In_Z.clear();
        MoveForward_Left_In_X.clear();
        MoveForward_Left_In_Y.clear();
        MoveForward_Left_In_Z.clear();
        MoveForward_Right_In_X.clear();
        MoveForward_Right_In_Y.clear();
        MoveForward_Right_In_Z.clear();

        while(query.next())
        {
            float Data_in[6] = { 0 };
            float P1_T[3] = { 0.0 };
            float P2_T[3] = { 0.0 };
            float P3_T[3] = { 0.0 };



            for(int i=0; i<6; i++)
            {
               Data_in[i] = query.value(i+1).toFloat();
            }

            MoveProcess(Data_in, rightStaticCoord, leftStaticCoord, forwardStaticCoord, P1_T, P2_T, P3_T);

            vertexForwardTooth.append(-P3_T[0]/200);
            vertexForwardTooth.append(P3_T[1]/200);
            vertexForwardTooth.append(-P3_T[2]/200);

            vertexLeftCondyle.append(P2_T[0]/200);
            vertexLeftCondyle.append(P2_T[1]/200);
            vertexLeftCondyle.append(P2_T[2]/200);

            vertexRightCondyle.append(P1_T[0]/200);
            vertexRightCondyle.append(P1_T[1]/200);
            vertexRightCondyle.append(-P1_T[2]/200);

            MoveForward_Forward_In_X.append(P3_T[0]);
            MoveForward_Forward_In_Y.append(P3_T[1]);
            MoveForward_Forward_In_Z.append(P3_T[2]);

            MoveForward_Left_In_X.append(P2_T[0]);
            MoveForward_Left_In_Y.append(P2_T[1]);
            MoveForward_Left_In_Z.append(P2_T[2]);

            MoveForward_Right_In_X.append(P1_T[0]);
            MoveForward_Right_In_Y.append(P1_T[1]);
            MoveForward_Right_In_Z.append(P1_T[2]);
        }
        //qDebug() << MoveForward_Left_In_X.size();
        //qDebug() << MoveForward_Right_In_X.size();


//        QString m_MoveForward_Left_In_X;
//        m_MoveForward_Left_In_X.append(QString("MoveForward_Left_In_X[%1] = {").arg(MoveForward_Left_In_X.size()));

//        for(int i=0; i< MoveForward_Left_In_X.size(); i++)
//        {

//            m_MoveForward_Left_In_X.append(QString("%1").arg(MoveForward_Left_In_X[i])).append(",");

//        }
//        m_MoveForward_Left_In_X.append("}");
//        qDebug() << m_MoveForward_Left_In_X;

        if(MoveForward_Forward_In_X.size())
        {
            MoveForward_Process(MoveForward_Left_In_X.data(), MoveForward_Left_In_Y.data(), MoveForward_Left_In_Z.data(),    MoveForward_Right_In_X.data(), MoveForward_Right_In_Y.data(), MoveForward_Right_In_Z.data(),   MoveForward_Left_In_X.size(), MoveForward_Right_In_X.size(),    MoveForward_Left_Out_X, MoveForward_Left_Out_Y, MoveForward_Right_Out_X, MoveForward_Right_Out_Y, out_len);

            Tooth_Sagittal(MoveForward_Forward_In_X.data(), MoveForward_Forward_In_Y.data(), MoveForward_Forward_In_Z.data(), MoveForward_Forward_In_X.size(), MoveForward_Forward_Out_X, MoveForward_Forward_Out_Y, out_len);
            drawImage("img_5.png",  QPixmap(1800,900));
            drawImage("img_6.png",  QPixmap(1800,900));
            drawImage("img_7.png",  QPixmap(1876,1428));





        }
        else
        {
            drawImage("img_5.png",  QPixmap(1800,900));
            drawImage("img_6.png",  QPixmap(1800,900));
            drawImage("img_7.png",  QPixmap(1876,1428));
        }

        emit DeviceSystem::getInstance()->vertexDataChanged("MoveForward", vertexForwardTooth, vertexLeftCondyle, vertexRightCondyle);

    }
    else if(step==5) //左侧方运动坐标
    {
        vertexForwardTooth.clear();
        vertexLeftCondyle.clear();
        vertexRightCondyle.clear();

        MoveLeft_Forward_In_X.clear();
        MoveLeft_Forward_In_Y.clear();
        MoveLeft_Forward_In_Z.clear();
        MoveLeft_Left_In_X.clear();
        MoveLeft_Left_In_Y.clear();
        MoveLeft_Left_In_Z.clear();
        MoveLeft_Right_In_X.clear();
        MoveLeft_Right_In_Y.clear();
        MoveLeft_Right_In_Z.clear();
        while(query.next())
        {
            float Data_in[6] = { 0 };
            float P1_T[3] = { 0.0 };
            float P2_T[3] = { 0.0 };
            float P3_T[3] = { 0.0 };

            for(int i=0; i<6; i++)
            {
               Data_in[i] = query.value(i+1).toFloat();
            }

            MoveProcess(Data_in, rightStaticCoord, leftStaticCoord, forwardStaticCoord, P1_T, P2_T, P3_T);


            vertexForwardTooth.append(-P3_T[0]/200);
            vertexForwardTooth.append(P3_T[1]/200);
            vertexForwardTooth.append(-P3_T[2]/200);

            vertexLeftCondyle.append(P2_T[0]/200);
            vertexLeftCondyle.append(P2_T[1]/200);
            vertexLeftCondyle.append(P2_T[2]/200);

            vertexRightCondyle.append(P1_T[0]/200);
            vertexRightCondyle.append(P1_T[1]/200);
            vertexRightCondyle.append(-P1_T[2]/200);

            MoveLeft_Forward_In_X.append(P3_T[0]);
            MoveLeft_Forward_In_Y.append(P3_T[1]);
            MoveLeft_Forward_In_Z.append(P3_T[2]);

            MoveLeft_Left_In_X.append(P2_T[0]);
            MoveLeft_Left_In_Y.append(P2_T[1]);
            MoveLeft_Left_In_Z.append(P2_T[2]);

            MoveLeft_Right_In_X.append(P1_T[0]);
            MoveLeft_Right_In_Y.append(P1_T[1]);
            MoveLeft_Right_In_Z.append(P1_T[2]);
        }

        if(MoveLeft_Forward_In_X.size())
        {
            MoveLeft_Process(MoveLeft_Right_In_X.data(), MoveLeft_Right_In_Y.data(), MoveLeft_Right_In_Z.data(), MoveLeft_Right_In_X.size(), MoveLeft_Left_Out_X, MoveLeft_Left_Out_Y,  MoveLeft_Right_Out_X, MoveLeft_Right_Out_Y, out_len);

            drawImage("img_2.png",  QPixmap(900,1800));



        }
        else
        {
            drawImage("img_2.png",  QPixmap(900,1800));
        }
        emit DeviceSystem::getInstance()->vertexDataChanged("MoveLeft", vertexForwardTooth, vertexLeftCondyle, vertexRightCondyle);


    }
    else if(step==6) //右侧方运动坐标
    {
        vertexForwardTooth.clear();
        vertexLeftCondyle.clear();
        vertexRightCondyle.clear();

        MoveRight_Forward_In_X.clear();
        MoveRight_Forward_In_Y.clear();
        MoveRight_Forward_In_Z.clear();
        MoveRight_Left_In_X.clear();
        MoveRight_Left_In_Y.clear();
        MoveRight_Left_In_Z.clear();
        MoveRight_Right_In_X.clear();
        MoveRight_Right_In_Y.clear();
        MoveRight_Right_In_Z.clear();
        while(query.next())
        {
            float Data_in[6] = { 0 };
            float P1_T[3] = { 0.0 };
            float P2_T[3] = { 0.0 };
            float P3_T[3] = { 0.0 };

            for(int i=0; i<6; i++)
            {
               Data_in[i] = query.value(i+1).toFloat();
            }

            MoveProcess(Data_in, rightStaticCoord, leftStaticCoord, forwardStaticCoord, P1_T, P2_T, P3_T);

            vertexForwardTooth.append(-P3_T[0]/200);
            vertexForwardTooth.append(P3_T[1]/200);
            vertexForwardTooth.append(-P3_T[2]/200);

            vertexLeftCondyle.append(P2_T[0]/200);
            vertexLeftCondyle.append(P2_T[1]/200);
            vertexLeftCondyle.append(P2_T[2]/200);

            vertexRightCondyle.append(P1_T[0]/200);
            vertexRightCondyle.append(P1_T[1]/200);
            vertexRightCondyle.append(-P1_T[2]/200);

            MoveRight_Forward_In_X.append(P3_T[0]);
            MoveRight_Forward_In_Y.append(P3_T[1]);
            MoveRight_Forward_In_Z.append(P3_T[2]);

            MoveRight_Left_In_X.append(P2_T[0]);
            MoveRight_Left_In_Y.append(P2_T[1]);
            MoveRight_Left_In_Z.append(P2_T[2]);

            MoveRight_Right_In_X.append(P1_T[0]);
            MoveRight_Right_In_Y.append(P1_T[1]);
            MoveRight_Right_In_Z.append(P1_T[2]);
        }

        if(MoveRight_Forward_In_X.size())
        {
            MoveRight_Process(MoveRight_Left_In_X.data(), MoveRight_Left_In_Y.data(), MoveRight_Left_In_Z.data(), MoveRight_Left_In_X.size(), MoveRight_Left_Out_X, MoveRight_Left_Out_Y,  MoveRight_Right_Out_X, MoveRight_Right_Out_Y, out_len);
            drawImage("img_1.png",  QPixmap(900,1800));

            Tooth_Coronal(MoveLeft_Forward_In_X.data(), MoveLeft_Forward_In_Y.data(), MoveLeft_Forward_In_Z.data(), MoveRight_Forward_In_X.data(), MoveRight_Forward_In_Y.data(), MoveRight_Forward_In_Z.data(), MoveLeft_Forward_In_X.size(), MoveRight_Forward_In_X.size(), MoveLeft_Forward_Out_X, MoveLeft_Forward_Out_Y, MoveRight_Forward_Out_X, MoveRight_Forward_Out_Y, out_len);
            drawImage("img_8.png",  QPixmap(1876,1428));

            Tooth_Horizontal(MoveForward_Forward_In_X.data(), MoveForward_Forward_In_Y.data(), MoveForward_Forward_In_Z.data(), MoveLeft_Forward_In_X.data(), MoveLeft_Forward_In_Y.data(), MoveLeft_Forward_In_Z.data(), MoveRight_Forward_In_X.data(), MoveRight_Forward_In_Y.data(), MoveRight_Forward_In_Z.data() , MoveForward_Forward_In_X.size(), MoveLeft_Forward_In_X.size(), MoveRight_Forward_In_X.size(), MoveForward_Forward_Out_X, MoveForward_Forward_Out_Y, MoveLeft_Forward_Out_X, MoveLeft_Forward_Out_Y, MoveRight_Forward_Out_X, MoveRight_Forward_Out_Y, out_len);
            drawImage("img_9.png",  QPixmap(1876,1428));

        }
        else
        {
            drawImage("img_1.png",  QPixmap(900,1800));
            drawImage("img_8.png",  QPixmap(1876,1428));
            drawImage("img_9.png",  QPixmap(1876,1428));
        }

        emit DeviceSystem::getInstance()->vertexDataChanged("MoveRight", vertexForwardTooth, vertexLeftCondyle, vertexRightCondyle);

    }
    else if(step==7)  //开闭口运动坐标
    {
        vertexForwardTooth.clear();
        vertexLeftCondyle.clear();
        vertexRightCondyle.clear();


        OpenClosed_Forward_In_X.clear();
        OpenClosed_Forward_In_Y.clear();
        OpenClosed_Forward_In_Z.clear();
        OpenClosed_Left_In_X.clear();
        OpenClosed_Left_In_Y.clear();
        OpenClosed_Left_In_Z.clear();
        OpenClosed_Right_In_X.clear();
        OpenClosed_Right_In_Y.clear();
        OpenClosed_Right_In_Z.clear();
        while(query.next())
        {
            float Data_in[6] = { 0.0f };
            float P1_T[3] = { 0.0f };
            float P2_T[3] = { 0.0f };
            float P3_T[3] = { 0.0f };

            for(int i=0; i<6; i++)
            {
               Data_in[i] = query.value(i+1).toFloat();
            }

            MoveProcess(Data_in, rightStaticCoord, leftStaticCoord, forwardStaticCoord, P1_T, P2_T, P3_T);


            vertexForwardTooth.append(-P3_T[0]/200);
            vertexForwardTooth.append(P3_T[1]/200);
            vertexForwardTooth.append(-P3_T[2]/200);

            vertexLeftCondyle.append(P2_T[0]/200);
            vertexLeftCondyle.append(P2_T[1]/200);
            vertexLeftCondyle.append(P2_T[2]/200);

            vertexRightCondyle.append(P1_T[0]/200);
            vertexRightCondyle.append(P1_T[1]/200);
            vertexRightCondyle.append(-P1_T[2]/200);


            OpenClosed_Forward_In_X.append(P3_T[0]);
            OpenClosed_Forward_In_Y.append(P3_T[1]);
            OpenClosed_Forward_In_Z.append(P3_T[2]);

            OpenClosed_Left_In_X.append(P2_T[0]);
            OpenClosed_Left_In_Y.append(P2_T[1]);
            OpenClosed_Left_In_Z.append(P2_T[2]);

            OpenClosed_Right_In_X.append(P1_T[0]);
            OpenClosed_Right_In_Y.append(P1_T[1]);
            OpenClosed_Right_In_Z.append(P1_T[2]);
        }

        if(OpenClosed_Left_In_X.size())
        {
            OpenClosed_Process(OpenClosed_Left_In_X.data(), OpenClosed_Left_In_Y.data(), OpenClosed_Left_In_Z.data(), OpenClosed_Right_In_X.data(), OpenClosed_Right_In_Y.data(), OpenClosed_Right_In_Z.data(), OpenClosed_Left_In_X.size(), OpenClosed_Right_In_X.size(), OpenClosed_Left_Out_X, OpenClosed_Left_Out_Y, OpenClosed_Right_Out_X, OpenClosed_Right_Out_Y, out_len);
            drawImage("img_3.png",  QPixmap(1800,900));
            drawImage("img_4.png",  QPixmap(1800,900));

        }
        else
        {
            drawImage("img_3.png",  QPixmap(1800,900));
            drawImage("img_4.png",  QPixmap(1800,900));
        }
        emit DeviceSystem::getInstance()->vertexDataChanged("OpenClosed", vertexForwardTooth, vertexLeftCondyle, vertexRightCondyle);


    }

    emit DeviceSystem::getInstance()->loadImage(step);

}


void DeviceSystem::drawImage(QString name, QPixmap pixmap)
{

    QPen pen;
    QVector<QPointF> points;

    float diffX;
    float diffY;

    float zoomX;
    float zoomY;

    margin = 80;

    pen.setColor(Qt::darkGray);
    pen.setWidth(8);


    QPainter painter(&pixmap);

    pixmap.fill(Qt::white);
    painter.setPen(pen);

    painter.translate(pixmap.width()/2, pixmap.height()/2-margin+pen.width());  //原点变换

    QRect rect(-pixmap.width()/2+margin, -pixmap.height()/2+margin, pixmap.width()-2*margin, pixmap.height()-2*margin);
    painter.drawRect(rect);

    QFont font = painter.font();
    font.setPixelSize(80);
    font.setBold(true);
    painter.setFont(font);

    painter.drawText(pixmap.width()/2-86, pixmap.height()/2-10, tr("mm"));
    painter.drawText(-20, pixmap.height()/2-10, tr("0"));
    painter.drawText(pixmap.width()/2-60, 30, tr("0"));

    //painter.drawImage(-pixmap.width()/2+margin+10, -pixmap.height()/2+margin+10, QImage(":/Resources/Chart/left.png"));

    pen.setColor(Qt::lightGray);
    pen.setWidth(4);
    painter.setPen(pen);
    QLine lineAxisX(-pixmap.width()/2+margin+6,0, pixmap.width()/2-margin-6, 0);
    painter.drawLine(lineAxisX);

    QLine lineAxisY(0,-pixmap.height()/2+margin+6, 0, pixmap.height()/2-margin-6);
    painter.drawLine(lineAxisY);


    if(name == "img_1.png")
    {
        points.clear();
        diffX = qAbs(MoveRight_Left_Out_X[out_len[0]-1] - MoveRight_Left_Out_X[0]);
        diffY = qAbs(MoveRight_Left_Out_Y[out_len[0]-1] - MoveRight_Left_Out_Y[0]);

        zoomX = rect.width()/diffX/2;
        zoomY = rect.height()/diffY/2;

        if(zoomX>zoomY)
        {
            zoomX = zoomY;
        }
        else
        {
            zoomY = zoomX;
        }


        for(int i=0; i<out_len[0]; i++)
        {
            points.append(QPoint((MoveRight_Left_Out_X[i] - MoveRight_Left_Out_X[0])*zoomX, -(MoveRight_Left_Out_Y[i] - MoveRight_Left_Out_Y[0])*zoomY));
        }


        pen.setColor(Qt::green);
        pen.setWidth(6);
        painter.setPen(pen);
        painter.drawPolyline(points.data(), points.size());

        pixmap.save(QDir::currentPath().append("/Html/image/").append(name));    //将画的图保存到指定位置
    }
    else if(name == "img_2.png")
    {

        points.clear();
        diffX = qAbs(MoveLeft_Right_Out_X[out_len[0]-1] - MoveLeft_Right_Out_X[0]);
        diffY = qAbs(MoveLeft_Right_Out_Y[out_len[0]-1] - MoveLeft_Right_Out_Y[0]);

        zoomX = rect.width()/diffX/2;
        zoomY = rect.height()/diffY/2;

        if(zoomX>zoomY)
        {
            zoomX = zoomY;
        }
        else
        {
            zoomY = zoomX;
        }


        for(int i=0; i<out_len[0]; i++)
        {
            points.append(QPoint((MoveLeft_Right_Out_X[i] - MoveLeft_Right_Out_X[0])*zoomX, -(MoveLeft_Right_Out_Y[i] - MoveLeft_Right_Out_Y[0])*zoomY));
        }



        pen.setColor(Qt::green);
        pen.setWidth(6);
        painter.setPen(pen);
        painter.drawPolyline(points.data(), points.size());

        pixmap.save(QDir::currentPath().append("/Html/image/").append(name));    //将画的图保存到指定位置
    }
    else if(name == "img_3.png")
    {

        points.clear();
        diffX = qAbs(OpenClosed_Left_Out_X[out_len[0]-1] - OpenClosed_Left_Out_X[0]);
        diffY = qAbs(OpenClosed_Left_Out_Y[out_len[0]-1] - OpenClosed_Left_Out_Y[0]);

        zoomX = rect.width()/diffX/2;
        zoomY = rect.height()/diffY/2;

        if(zoomX>zoomY)
        {
            zoomX = zoomY;
        }
        else
        {
            zoomY = zoomX;
        }


        for(int i=0; i<out_len[0]; i++)
        {
            points.append(QPoint((OpenClosed_Left_Out_X[i] - OpenClosed_Left_Out_X[0])*zoomX, -(OpenClosed_Left_Out_Y[i] - OpenClosed_Left_Out_Y[0])*zoomY));
        }


        pen.setColor(Qt::green);
        pen.setWidth(6);
        painter.setPen(pen);
        painter.drawPolyline(points.data(), points.size());

        pixmap.save(QDir::currentPath().append("/Html/image/").append(name));    //将画的图保存到指定位置
    }
    else if(name == "img_4.png")
    {

        points.clear();
        diffX = qAbs(OpenClosed_Right_Out_X[out_len[0]-1] - OpenClosed_Right_Out_X[0]);
        diffY = qAbs(OpenClosed_Right_Out_Y[out_len[0]-1] - OpenClosed_Right_Out_Y[0]);

        zoomX = rect.width()/diffX/2;
        zoomY = rect.height()/diffY/2;

        if(zoomX>zoomY)
        {
            zoomX = zoomY;
        }
        else
        {
            zoomY = zoomX;
        }


        for(int i=0; i<out_len[0]; i++)
        {
            points.append(QPoint((OpenClosed_Right_Out_X[i] - OpenClosed_Right_Out_X[0])*zoomX, -(OpenClosed_Right_Out_Y[i] - OpenClosed_Right_Out_Y[0])*zoomY));
        }

        pen.setColor(Qt::green);
        pen.setWidth(6);
        painter.setPen(pen);
        painter.drawPolyline(points.data(), points.size());

        pixmap.save(QDir::currentPath().append("/Html/image/").append(name));    //将画的图保存到指定位置
    }
    else if(name == "img_5.png")
    {

        points.clear();
        diffX = qAbs(MoveForward_Left_Out_X[out_len[0]-1] - MoveForward_Left_Out_X[0]);
        diffY = qAbs(MoveForward_Left_Out_Y[out_len[0]-1] - MoveForward_Left_Out_Y[0]);

        zoomX = rect.width()/diffX/2;
        zoomY = rect.height()/diffY/2;

        if(zoomX>zoomY)
        {
            zoomX = zoomY;
        }
        else
        {
            zoomY = zoomX;
        }


        for(int i=0; i<out_len[0]; i++)
        {
            points.append(QPoint((MoveForward_Left_Out_X[i] - MoveForward_Left_Out_X[0])*zoomX, -(MoveForward_Left_Out_Y[i] - MoveForward_Left_Out_Y[0])*zoomY));
        }


        pen.setColor(Qt::green);
        pen.setWidth(6);
        painter.setPen(pen);
        painter.drawPolyline(points.data(), points.size());

        pixmap.save(QDir::currentPath().append("/Html/image/").append(name));    //将画的图保存到指定位置
    }
    else if(name == "img_6.png")
    {

        points.clear();
        diffX = qAbs(MoveForward_Right_Out_X[out_len[0]-1] - MoveForward_Right_Out_X[0]);
        diffY = qAbs(MoveForward_Right_Out_Y[out_len[0]-1] - MoveForward_Right_Out_Y[0]);

        zoomX = rect.width()/diffX/2;
        zoomY = rect.height()/diffY/2;

        if(zoomX>zoomY)
        {
            zoomX = zoomY;
        }
        else
        {
            zoomY = zoomX;
        }


        for(int i=0; i<out_len[0]; i++)
        {
            points.append(QPoint((MoveForward_Right_Out_X[i] - MoveForward_Right_Out_X[0])*zoomX, -(MoveForward_Right_Out_Y[i] - MoveForward_Right_Out_Y[0])*zoomY));
        }


        pen.setColor(Qt::green);
        pen.setWidth(6);
        painter.setPen(pen);
        painter.drawPolyline(points.data(), points.size());

        pixmap.save(QDir::currentPath().append("/Html/image/").append(name));    //将画的图保存到指定位置
    }
    else if(name == "img_7.png")
    {

        points.clear();
        diffX = qAbs(MoveForward_Forward_Out_X[out_len[0]-1] - MoveForward_Forward_Out_X[0]);
        diffY = qAbs(MoveForward_Forward_Out_Y[out_len[0]-1] - MoveForward_Forward_Out_Y[0]);

        zoomX = rect.width()/diffX/2;
        zoomY = rect.height()/diffY/2;

        if(zoomX>zoomY)
        {
            zoomX = zoomY;
        }
        else
        {
            zoomY = zoomX;
        }


        for(int i=0; i<out_len[0]; i++)
        {
            points.append(QPoint((MoveForward_Forward_Out_X[i] - MoveForward_Forward_Out_X[0])*zoomX, -(MoveForward_Forward_Out_Y[i] - MoveForward_Forward_Out_Y[0])*zoomY));
        }


        pen.setColor(Qt::blue);
        pen.setWidth(6);
        painter.setPen(pen);
        painter.drawPolyline(points.data(), points.size());

        pixmap.save(QDir::currentPath().append("/Html/image/").append(name));    //将画的图保存到指定位置
    }
    else if(name == "img_8.png")
    {

        points.clear();
        diffX = qAbs(MoveLeft_Forward_Out_X[out_len[0]-1] - MoveLeft_Forward_Out_X[0]);
        diffY = qAbs(MoveLeft_Forward_Out_Y[out_len[0]-1] - MoveLeft_Forward_Out_Y[0]);

        zoomX = rect.width()/diffX/2;
        zoomY = rect.height()/diffY/2;

        if(zoomX>zoomY)
        {
            zoomX = zoomY;
        }
        else
        {
            zoomY = zoomX;
        }


        for(int i=0; i<out_len[0]; i++)
        {
            points.append(QPoint((MoveLeft_Forward_Out_X[i] - MoveLeft_Forward_Out_X[0])*zoomX, -(MoveLeft_Forward_Out_Y[i] - MoveLeft_Forward_Out_Y[0])*zoomY));
        }


        pen.setColor(Qt::green);
        pen.setWidth(6);
        painter.setPen(pen);
        painter.drawPolyline(points.data(), points.size());

        points.clear();

        diffX = qAbs(MoveRight_Forward_Out_X[out_len[0]-1] - MoveRight_Forward_Out_X[0]);
        diffY = qAbs(MoveRight_Forward_Out_Y[out_len[0]-1] - MoveRight_Forward_Out_Y[0]);

        zoomX = rect.width()/diffX/2;
        zoomY = rect.height()/diffY/2;
        if(zoomX>zoomY)
        {
            zoomX = zoomY;
        }
        else
        {
            zoomY = zoomX;
        }

        for(int i=0; i<out_len[0]; i++)
        {
            points.append(QPoint((MoveRight_Forward_Out_X[i] - MoveRight_Forward_Out_X[0])*zoomX, -(MoveRight_Forward_Out_Y[i] - MoveRight_Forward_Out_Y[0])*zoomY));
        }


        pen.setColor(Qt::red);
        pen.setWidth(6);
        painter.setPen(pen);
        painter.drawPolyline(points.data(), points.size());


        pixmap.save(QDir::currentPath().append("/Html/image/").append(name));    //将画的图保存到指定位置
    }
    else if(name == "img_9.png")
    {

        points.clear();
        diffX = qAbs(MoveForward_Forward_Out_X[out_len[0]-1] - MoveForward_Forward_Out_X[0]);
        diffY = qAbs(MoveForward_Forward_Out_Y[out_len[0]-1] - MoveForward_Forward_Out_Y[0]);

        zoomX = rect.width()/diffX/2;
        zoomY = rect.height()/diffY/2;

        if(zoomX>zoomY)
        {
            zoomX = zoomY;
        }
        else
        {
            zoomY = zoomX;
        }


        for(int i=0; i<out_len[0]; i++)
        {
            points.append(QPoint((MoveForward_Forward_Out_X[i] - MoveForward_Forward_Out_X[0])*zoomX, -(MoveForward_Forward_Out_Y[i] - MoveForward_Forward_Out_Y[0])*zoomY));
        }



        pen.setColor(Qt::blue);
        pen.setWidth(6);
        painter.setPen(pen);
        painter.drawPolyline(points.data(), points.size());

        points.clear();
        diffX = qAbs(MoveLeft_Forward_Out_X[out_len[0]-1] - MoveLeft_Forward_Out_X[0]);
        diffY = qAbs(MoveLeft_Forward_Out_Y[out_len[0]-1] - MoveLeft_Forward_Out_Y[0]);

        zoomX = rect.width()/diffX/2;
        zoomY = rect.height()/diffY/2;

        if(zoomX>zoomY)
        {
            zoomX = zoomY;
        }
        else
        {
            zoomY = zoomX;
        }


        for(int i=0; i<out_len[0]; i++)
        {
            points.append(QPoint((MoveLeft_Forward_Out_X[i] - MoveLeft_Forward_Out_X[0])*zoomX, -(MoveLeft_Forward_Out_Y[i] - MoveLeft_Forward_Out_Y[0])*zoomY));
        }


        pen.setColor(Qt::green);
        pen.setWidth(6);
        painter.setPen(pen);
        painter.drawPolyline(points.data(), points.size());


        points.clear();
        diffX = qAbs(MoveRight_Forward_Out_X[out_len[0]-1] - MoveRight_Forward_Out_X[0]);
        diffY = qAbs(MoveRight_Forward_Out_Y[out_len[0]-1] - MoveRight_Forward_Out_Y[0]);

        zoomX = rect.width()/diffX/2;
        zoomY = rect.height()/diffY/2;

        if(zoomX>zoomY)
        {
            zoomX = zoomY;
        }
        else
        {
            zoomY = zoomX;
        }


        for(int i=0; i<out_len[0]; i++)
        {
            points.append(QPoint((MoveRight_Forward_Out_X[i] - MoveRight_Forward_Out_X[0])*zoomX, -(MoveRight_Forward_Out_Y[i] - MoveRight_Forward_Out_Y[0])*zoomY));
        }
        pen.setColor(Qt::red);
        pen.setWidth(6);
        painter.setPen(pen);
        painter.drawPolyline(points.data(), points.size());


        pixmap.save(QDir::currentPath().append("/Html/image/").append(name));    //将画的图保存到指定位置
    }

}



