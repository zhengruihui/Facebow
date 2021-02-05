#ifndef SERIALPORT_H
#define SERIALPORT_H

#include <QObject>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QThread>
#include <QVector>
#include <QMutex>
#include <QMutexLocker>
#include <QTimer>

struct Pos{
    float x;
    float y;
    float z;
    float c;
    float p;
    float r;
};

class SerialPort : public QObject
{
    Q_OBJECT

public:
    explicit SerialPort(QObject *parent = nullptr);
    ~SerialPort();

    bool getOneByte(uint8_t *value);

    void writeData();

    void setPosData(struct Pos pos);
    struct Pos getPosData();

private:
    QSerialPort *serialPort = nullptr;

    QVector<uint8_t> vector;

    QVector<struct Pos> posVector;

    QMutex mutex;

    int head = 0;
    int index = 0;
    uint8_t buffer[60] = {0};

    QTimer *timer;

signals:
    void posDataChanged(float x, float y, float z, float ex, float ey, float ez);

private slots:
    void readData();


};

#endif // SERIALPORT_H
