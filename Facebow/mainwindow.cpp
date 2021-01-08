#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QGraphicsDropShadowEffect>
#include <QButtonGroup>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


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


    serialPort = new SerialPort();
    //connect(serialPort, &SerialPort::facebowPosChanged, ui->openGLWidget, &GLWidget::changeSkullPos);

}

MainWindow::~MainWindow()
{
    delete ui;
}

