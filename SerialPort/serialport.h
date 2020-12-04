#ifndef SERIALPORT_H
#define SERIALPORT_H

#include <QObject>
#include <QSerialPort>
#include <QSerialPortInfo>


class SerialPort : public QObject
{
    Q_OBJECT

    Q_PROPERTY(NOTIFY yearChanged)


public:
    explicit SerialPort(QObject *parent = nullptr);

    void writeData();

private:
    QSerialPort *serialPort = nullptr;

signals:
    void positionChanged(float x, float y, float z, float heading, float tilt, float roll);

private slots:
    void readData();


};

#endif // SERIALPORT_H
