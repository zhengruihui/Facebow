#ifndef SERIALPORT_H
#define SERIALPORT_H

#include <QObject>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QThread>
#include <QVector>
#include <QMutex>
#include <QMutexLocker>

class SerialPort : public QObject
{
    Q_OBJECT

public:
    explicit SerialPort(QObject *parent = nullptr);
    ~SerialPort();

    void writeData();

private:
    QSerialPort *serialPort = nullptr;

    QVector<uint8_t> vector;

    QMutex mutex;

    int head = 0;
    int index = 0;
    uint8_t buffer[60] = {0};

signals:
    void posDataChanged(float x, float y, float z, float ex, float ey, float ez);

private slots:
    void readData();


};

#endif // SERIALPORT_H
