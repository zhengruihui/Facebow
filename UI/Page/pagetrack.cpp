#include "pagetrack.h"
#include "ui_pagetrack.h"
#include "devicesystem.h"
#include <QButtonGroup>
#include <QGraphicsDropShadowEffect>
#include <QTimer>

PageTrack::PageTrack(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PageTrack)
{
    ui->setupUi(this);
    //导航按键组

    QToolButton *buttonHandle[] = {ui->toolButtonMeasureStart, ui->toolButtonPlay, ui->toolButtonDeviceSetting};


    for(int i=0; i<3; i++)
    {
        //设置阴影
        QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect(this);
        shadow->setOffset(2, 2);
        shadow->setColor(QColor(QRgb(0x0)));
        shadow->setBlurRadius(30);
        buttonHandle[i]->setGraphicsEffect(shadow);
    }

    QTimer *timer = new QTimer();

    timer->start(100);

    //connect(timer, &QTimer::timeout, this,  &PageTrack::updateDisplay);
}

PageTrack::~PageTrack()
{
    delete ui;
}

void PageTrack::paintChart()
{
    GLChart::paintChart();
}


void PageTrack::on_toolButtonMeasureStart_clicked(bool checked)
{
    DeviceSystem::getInstance()->setMeasureStart(checked);
}


void PageTrack::on_toolButtonDeviceSetting_pressed()
{

}

void PageTrack::updateDisplay()
{
    update();
}

void PageTrack::on_toolButtonPlay_clicked(bool checked)
{
    Q_UNUSED(checked);
}


