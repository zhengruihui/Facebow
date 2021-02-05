#include "devicesystem.h"
#include <QDebug>
#include <QMutex>
#include "DLL/Get_LeftCondyle_StaticCoord/Get_LeftCondyle_StaticCoord.h"
#include "DLL/Get_rightCondyle_StaticCoord/Get_RightCondyle_StaticCoord.h"
#include "DLL/MoveProcess/MoveProcess.h"


DeviceSystem *DeviceSystem::self = nullptr;
SerialPort *DeviceSystem::serialPort = nullptr;
Database *DeviceSystem::dataBase = nullptr;

int DeviceSystem::step = 0;
bool DeviceSystem::measureStart = false;
QString DeviceSystem::dataBaseID = 0;
QThread *DeviceSystem::systemThread = nullptr;
QVector<float> *DeviceSystem::vertexTooth = nullptr;
QVector<float> *DeviceSystem::vertexLeftCondyle = nullptr;
QVector<float> *DeviceSystem::vertexRightCondyle = nullptr;
QVector<float> *DeviceSystem::vertexDataStaticForward = nullptr;
QVector<float> *DeviceSystem::vertexDataStaticLeft = nullptr;
QVector<float> *DeviceSystem::vertexDataStaticRight = nullptr;

QTime DeviceSystem::startTime = QTime();

float forwardStaticCoord[3] = {-2.8f, -7.9f, -65.67f};
float leftStaticCoord[3] = {0.0f, 0.0f, 0.0f};
float rightStaticCoord[3] = {0.0f, 0.0f, 0.0f};

DeviceSystem *DeviceSystem::getInstance()
{
    //判断是否是第一次调用
    //假如不为NULL,会直接return
    if (self == nullptr) {

        //防止多进程同时调用创建2个对象的问题
        //原理是因为是静态变量只会定义一次
        static QMutex mutex;

        //上锁  QMutexLocker会锁住mutex，当QMutexLocker 被释放的时候会自动解锁
        //locker是局部变量，所以getInstance（）函数结束之后会自动解锁
        QMutexLocker locker(&mutex);

        //在判断一次,防止其它进程抢先new过了
        if (self == nullptr) {
            self = new DeviceSystem;
            self->initDeviceSystem();
        }

    }

    return self; //返回指针

}

void DeviceSystem::setCurrentDatabaseID(QString value)
{
    dataBaseID = value;
}

QString DeviceSystem::getCurrentDatabaseID()
{
    return dataBaseID;
}

void DeviceSystem::initDeviceSystem()
{
    self->serialPort = new SerialPort();
    self->dataBase = new Database();
    self->systemThread = new QThread();

    self->vertexTooth = new QVector<float>();
    self->vertexLeftCondyle = new QVector<float>();
    self->vertexRightCondyle = new QVector<float>();
    self->vertexDataStaticForward = new QVector<float>();
    self->vertexDataStaticLeft = new QVector<float>();
    self->vertexDataStaticRight = new QVector<float>();

    self->serialPort->moveToThread(systemThread);
    self->dataBase->moveToThread(systemThread);


    self->moveToThread(systemThread);


    self->startTime = QTime::currentTime();

    QObject::connect(self->serialPort, &SerialPort::posDataChanged, self,  self->on_posDataChanged, Qt::QueuedConnection);

    QObject::connect(self->dataBase, &Database::queryPosChanged, self,  self->on_queryPosChanged, Qt::QueuedConnection);

    systemThread->start();
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
    dataBase->queryPos(dataBaseID.toInt(), 1);
    dataBase->queryPos(dataBaseID.toInt(), 2);
    dataBase->queryPos(dataBaseID.toInt(), 3);
    dataBase->queryPos(dataBaseID.toInt(), 4);
    dataBase->queryPos(dataBaseID.toInt(), 5);
    dataBase->queryPos(dataBaseID.toInt(), 6);
    dataBase->queryPos(dataBaseID.toInt(), 7);
}



void DeviceSystem::on_posDataChanged(float x, float y, float z, float c, float p, float r)
{
    if(measureStart)
    {       
        dataBase->insertPosition(QString(dataBaseID).toInt(), step, x, y, z, c, p, r);
    }


    if(startTime.msecsTo(QTime::currentTime()) > 100)
    {
        self->startTime = startTime = QTime::currentTime();
        emit DeviceSystem::getInstance()->facebowPosChanged(x, y, z, c, p, r);
    }




}
//画图时，左髁突取（Z,Y），右髁突取(-Z,Y)，前牙水平面取(-X,Z)
void DeviceSystem::on_queryPosChanged(int step, QSqlQuery query)
{
    if(step==1) //前牙静态坐标
    {
        vertexDataStaticForward->clear();
        while(query.next())
        {
            for(int i=0; i<6; i++)
            {
               vertexDataStaticForward->append(query.value(i+1).toFloat());
            }

        }

    }
    else if(step==2) //左髁突静态坐标
    {
        vertexDataStaticLeft->clear();
        while(query.next())
        {
            for(int i=0; i<6; i++)
            {
               vertexDataStaticLeft->append(query.value(i+1).toFloat());
            }

        }

        Get_LeftCondyle_StaticCoord(vertexDataStaticLeft->data(), vertexDataStaticForward->data(), vertexDataStaticLeft->size()/6,vertexDataStaticForward->size()/6, leftStaticCoord);



        //qDebug() << "leftStaticCoord" << leftStaticCoord[0] << leftStaticCoord[1] <<leftStaticCoord[2];
    }
    else if(step==3) //右髁突静态坐标
    {
        vertexDataStaticRight->clear();
        while(query.next())
        {
            for(int i=0; i<6; i++)
            {
               vertexDataStaticRight->append(query.value(i+1).toFloat());
            }

        }
        Get_RightCondyle_StaticCoord(vertexDataStaticRight->data(), vertexDataStaticForward->data(), vertexDataStaticRight->size()/6,vertexDataStaticForward->size()/6, rightStaticCoord);
        //qDebug() << "rightStaticCoord" << rightStaticCoord[0] << rightStaticCoord[1] <<rightStaticCoord[2];


    }
    else if(step==4) //前伸运动坐标
    {
        vertexTooth->clear();
        vertexLeftCondyle->clear();
        vertexRightCondyle->clear();
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


            vertexTooth->append(-P3_T[0]/200);
            vertexTooth->append(P3_T[1]/200);
            vertexTooth->append(-P3_T[2]/200);

            vertexLeftCondyle->append(P2_T[0]/200);
            vertexLeftCondyle->append(P2_T[1]/200);
            vertexLeftCondyle->append(P2_T[2]/200);

            vertexRightCondyle->append(P1_T[0]/200);
            vertexRightCondyle->append(P1_T[1]/200);
            vertexRightCondyle->append(-P1_T[2]/200);

        }

        emit DeviceSystem::getInstance()->vertexDataChanged("MoveForward", *vertexTooth, *vertexLeftCondyle, *vertexRightCondyle);


    }
    else if(step==5) //左侧方运动坐标
    {
        vertexTooth->clear();
        vertexLeftCondyle->clear();
        vertexRightCondyle->clear();
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


            vertexTooth->append(-P3_T[0]/200);
            vertexTooth->append(P3_T[1]/200);
            vertexTooth->append(-P3_T[2]/200);

            vertexLeftCondyle->append(P2_T[0]/200);
            vertexLeftCondyle->append(P2_T[1]/200);
            vertexLeftCondyle->append(P2_T[2]/200);

            vertexRightCondyle->append(P1_T[0]/200);
            vertexRightCondyle->append(P1_T[1]/200);
            vertexRightCondyle->append(-P1_T[2]/200);
        }

        emit DeviceSystem::getInstance()->vertexDataChanged("MoveLeft", *vertexTooth, *vertexLeftCondyle, *vertexRightCondyle);

    }
    else if(step==6) //右侧方运动坐标
    {
        vertexTooth->clear();
        vertexLeftCondyle->clear();
        vertexRightCondyle->clear();
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

            vertexTooth->append(-P3_T[0]/200);
            vertexTooth->append(P3_T[1]/200);
            vertexTooth->append(-P3_T[2]/200);

            vertexLeftCondyle->append(P2_T[0]/200);
            vertexLeftCondyle->append(P2_T[1]/200);
            vertexLeftCondyle->append(P2_T[2]/200);

            vertexRightCondyle->append(P1_T[0]/200);
            vertexRightCondyle->append(P1_T[1]/200);
            vertexRightCondyle->append(-P1_T[2]/200);
        }

        emit DeviceSystem::getInstance()->vertexDataChanged("MoveRight", *vertexTooth, *vertexLeftCondyle, *vertexRightCondyle);

    }
    else if(step==7)  //开闭口运动坐标
    {
        vertexTooth->clear();
        vertexLeftCondyle->clear();
        vertexRightCondyle->clear();
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



            for(int j=0; j<3; j++)
            {
                vertexTooth->append(P3_T[j]/200);
                vertexLeftCondyle->append(P2_T[j]/200);
                vertexRightCondyle->append(P1_T[j]/200);
            }
        }

        emit DeviceSystem::getInstance()->vertexDataChanged("OpenClosed", *vertexTooth, *vertexLeftCondyle, *vertexRightCondyle);

    }


}



