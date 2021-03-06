﻿#include "serialport.h"
#include "QDebug"
#include <QList>
#include "CRC16.h"


SerialPort::SerialPort(QObject *parent) : QObject(parent)
{
    serialPort = new QSerialPort();

    timer = new QTimer();

    QObject::connect(timer, &QTimer::timeout, this, &SerialPort::on_timeout, Qt::QueuedConnection);

    QObject::connect(serialPort, &QSerialPort::readyRead, this, &SerialPort::readData, Qt::QueuedConnection);

    timer->start(2000);



}

SerialPort::~SerialPort()
{
    serialPort->close();
}




void SerialPort::writeData()
{
    QByteArray writeBuffer;

    uint8_t buffer[] = {0xA5, 0x5A, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0xB6, 0x6B};

    writeBuffer.setRawData((const char*)buffer, sizeof (buffer));

    serialPort->write(writeBuffer);

}



void SerialPort::readData()
{
    QByteArray readBuffer;

    readBuffer = serialPort->readAll();

    for(int i=0; i<readBuffer.size(); i++)
    {
        vector.append(readBuffer.at(i));

    }

    while(1)
    {
        if(vector.size()>0)
        {
            buffer[index] = vector.at(0);
            vector.pop_front();

            if(head == 0)
            {
                if(buffer[index] == 0xa5)
                {
                    head = 1;
                }
                else
                {
                    head = 0;
                }

            }
            else if(head == 1)
            {
                if(buffer[index] == 0x5a)
                {
                    head = 2;
                }
                else
                {
                    head = 0;
                }


            }
            else if(head == 2)
            {
                if(buffer[index] == 0x02)
                {
                    head = 3;
                }
                else
                {
                    head = 0;
                }
            }
            else if(head == 3)
            {
                if(buffer[index] == 0x02)
                {
                    head = 4;
                }
                else
                {
                    head = 0;
                }
            }
            else if(head == 4)
            {

                head = 5;

            }
            else if(head == 5)
            {
                index = -1;
                head = 0;
            }


            index ++;


            if(index == 46)
            {
                int32_t x_t = *(int32_t*)(buffer+18);  //单位0.0001mm
                int32_t y_t = *(int32_t*)(buffer+22);
                int32_t z_t = *(int32_t*)(buffer+26);
                int32_t ex_t = *(int32_t*)(buffer+30);  //单位0.0001°
                int32_t ey_t = *(int32_t*)(buffer+34);
                int32_t ez_t = *(int32_t*)(buffer+38);

                float x = x_t*0.0001;
                float y = y_t*0.0001;
                float z = z_t*0.0001;
                float ex = ex_t*0.0001;
                float ey = ey_t*0.0001;
                float ez = ez_t*0.0001;


                emit posDataChanged(x, y, z, ex, ey, ez);
            }

        }
        else
        {
            break;
        }

    }



}

void SerialPort::on_timeout()
{
    //查找可用的串口

    bool portAvailable = false;

    foreach(const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
    {
        QSerialPort serial;
        serial.setPort(info);

        if(info.manufacturer() == "FTDI")
        {
            portAvailable = true;
            serialPort->setPortName(info.portName());
            break;
        }

    }

    if(portAvailable)
    {

        if(!serialPort->isOpen())
        {

            if(serialPort->open(QIODevice::ReadWrite))
            {

                //设置波特率
                serialPort->setBaudRate(230400);
                //设置数据位数
                serialPort->setDataBits(QSerialPort::Data8);
                //设置奇偶校验
                serialPort->setParity(QSerialPort::NoParity);
                //设置停止位
                serialPort->setStopBits(QSerialPort::OneStop);
                //设置流控制
                serialPort->setFlowControl(QSerialPort::NoFlowControl);
                //连接信号槽

                qDebug() << "serialPort add";

            }
        }

    }
    else
    {
        if(serialPort->isOpen())
        {
            serialPort->close();
            qDebug() << "serialPort remove";
        }

    }
}
