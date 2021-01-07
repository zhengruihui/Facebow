#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    serialPort = new SerialPort();

    buttonGroup = new QButtonGroup(this);
    buttonGroup->addButton(ui->informationButton);
    buttonGroup->addButton(ui->measureButton);
    buttonGroup->addButton(ui->trackButton);
    buttonGroup->addButton(ui->reportButton);



    //connect(serialPort, &SerialPort::facebowPosChanged, ui->openGLWidget, &GLWidget::changeSkullPos);

}

MainWindow::~MainWindow()
{
    delete ui;
}

