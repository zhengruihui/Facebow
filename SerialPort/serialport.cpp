#include "serialport.h"
#include "QDebug"

SerialPort::SerialPort(QObject *parent) : QObject(parent)
{
    serialPort = new QSerialPort();

    //查找可用的串口
//    foreach(const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
//    {
//        QSerialPort serial;
//        serial.setPort(info);
//        if(serial.open(QIODevice::ReadWrite))
//        {
//            //设置串口名
//            serialPort->setPortName(serial.portName());
//            qDebug() << serial.portName();

//            serial.close();
//        }
//    }


    //设置串口名
    serialPort->setPortName("COM1");
    //打开串口
    serialPort->open(QIODevice::ReadWrite);
    //设置波特率
    serialPort->setBaudRate(QSerialPort::Baud115200);
    //设置数据位数
    serialPort->setDataBits(QSerialPort::Data8);
    //设置奇偶校验
    serialPort->setParity(QSerialPort::NoParity);
    //设置停止位
    serialPort->setStopBits(QSerialPort::OneStop);
    //设置流控制
    serialPort->setFlowControl(QSerialPort::NoFlowControl);
    //连接信号槽
    QObject::connect(serialPort, &QSerialPort::readyRead, this, &SerialPort::readData);

}

void SerialPort::writeData()
{
    QByteArray writeBuffer;
    writeBuffer.append("Hello Facebow!");
    serialPort->write(writeBuffer);

}

void SerialPort::readData()
{
    QByteArray readBuffer;
    readBuffer = serialPort->readAll();

    qDebug() << "readData";

    readBuffer.clear();

}
