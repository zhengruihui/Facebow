#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QGraphicsDropShadowEffect>
#include <QButtonGroup>
#include "devicesystem.h"
#include <QDebug>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowFlags(Qt::Window | Qt::FramelessWindowHint);

    //导航按键组
    QButtonGroup *buttonGroupPage = new QButtonGroup(this);
    buttonGroupPage->addButton(ui->buttonInfo);
    buttonGroupPage->addButton(ui->buttonMeasure);
    buttonGroupPage->addButton(ui->buttonTrack);
    buttonGroupPage->addButton(ui->buttonReport);
    buttonGroupPage->addButton(ui->buttonHelp);

    //设置阴影
    QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect(this);
    shadow->setOffset(2, 2);
    shadow->setColor(QColor(QRgb(0x0)));
    shadow->setBlurRadius(30);
    ui->stackedWidget->setGraphicsEffect(shadow);

    ui->stackedWidget->setCurrentIndex(0);

    //qDebug() << "mainwindow: " << QThread::currentThreadId();

    update();

}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_buttonInfo_pressed()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_buttonMeasure_pressed()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_buttonTrack_pressed()
{
    ui->stackedWidget->setCurrentIndex(2);
    ui->pageTrack->paintChart();
}

void MainWindow::on_buttonReport_pressed()
{
    ui->stackedWidget->setCurrentIndex(3);
}

void MainWindow::on_buttonHelp_pressed()
{
    ui->stackedWidget->setCurrentIndex(4);
}

void MainWindow::on_buttonMin_clicked()
{
    showMinimized();
}

void MainWindow::on_buttonMax_clicked(bool checked)
{
    if(checked)
    {
        showMaximized();
    }
    else
    {
        showNormal();
    }
}

void MainWindow::on_buttonClose_clicked()
{
    close();
}

void MainWindow::on_pushButtonLogo_clicked()
{
    DeviceSystem::getInstance()->getSerialPort()->writeData();
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        m_leftButtonPressed = true;
        m_start = event->globalPos();
    }
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    if(m_leftButtonPressed)
    {
        move(geometry().topLeft() + event->globalPos() - m_start);
        m_start = event->globalPos();
    }
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        m_leftButtonPressed = false;
    }

}

void MainWindow::mouseDoubleClickEvent(QMouseEvent *event)
{
    static bool noraml=true;
    Q_UNUSED(event);

    if(noraml)
    {
        showMaximized();
        noraml = false;
    }
    else
    {
        showNormal();
        noraml = true;
    }
}
