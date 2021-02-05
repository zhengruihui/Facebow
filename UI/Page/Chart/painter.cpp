#include "painter.h"
#include "ui_painter.h"
#include <QDebug>
#include "devicesystem.h"

Painter::Painter(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Painter)
{
    ui->setupUi(this);
    paintThread = new QThread();
    moveToThread(paintThread);

    //QObject::connect(this, &Painter::paintE, this, &Painter::paint, Qt::QueuedConnection);
}

Painter::~Painter()
{
    delete ui;
}

void Painter::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    QPainter painter(this);

    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setWindow(-width()/2, height()/2, width(), -height());




    QPen pen;
    pen.setStyle(Qt::SolidLine);
    pen.setWidth(1);
    pen.setBrush(Qt::lightGray);
    pen.setCapStyle(Qt::RoundCap);
    pen.setJoinStyle(Qt::RoundJoin);

    painter.setPen(pen);


    //draw axis X,Y
    painter.drawLine(QPointF(-width()/2, 0), QPointF(width()/2, 0));
    painter.drawLine(QPointF(0, height()/2), QPointF(0, -height()/2 ));

    pen.setStyle(Qt::DotLine);
    pen.setBrush(Qt::yellow);
    painter.setPen(pen);
    painter.scale(width()/583, height()/570);

    for(int i=0; i< 257142/3; i++)
    {
       painter.drawLine(QPointF(i, 3), QPointF(4, 7));

    }
    painter.drawLine(QPointF(0, 3), QPointF(4, 7));
    painter.drawLine(QPointF(4, 7), QPointF(6, 9));
    painter.drawLine(QPointF(6, 9), QPointF(16, 39));
    painter.drawLine(QPointF(16, 39), QPointF(width()/2, height()/2));


    //painter.drawImage();

    qDebug() << "paintEvent: " << width() << height();
    emit paintE();

}

void Painter::paint()
{
    QPainter painter(this);

    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setWindow(-width()/2, height()/2, width(), -height());




    QPen pen;
    pen.setStyle(Qt::SolidLine);
    pen.setWidth(1);
    pen.setBrush(Qt::lightGray);
    pen.setCapStyle(Qt::RoundCap);
    pen.setJoinStyle(Qt::RoundJoin);

    painter.setPen(pen);


    //draw axis X,Y
    painter.drawLine(QPointF(-width()/2, 0), QPointF(width()/2, 0));
    painter.drawLine(QPointF(0, height()/2), QPointF(0, -height()/2 ));

    pen.setStyle(Qt::DotLine);
    pen.setBrush(Qt::yellow);
    painter.setPen(pen);
    painter.scale(width()/583, height()/570);

    for(int i=0; i< 257142/3; i++)
    {
       painter.drawLine(QPointF(i, 3), QPointF(4, 7));

    }
    painter.drawLine(QPointF(0, 3), QPointF(4, 7));
    painter.drawLine(QPointF(4, 7), QPointF(6, 9));
    painter.drawLine(QPointF(6, 9), QPointF(16, 39));
    painter.drawLine(QPointF(16, 39), QPointF(width()/2, height()/2));


    //painter.drawImage();

    qDebug() << "paintEvent: " << width() << height();
}
