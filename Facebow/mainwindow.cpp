#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    serialPort = new SerialPort();

    connect(serialPort, &SerialPort::facebowPosChanged, ui->openGLWidget, &GLWidget::changeSkullPos);

}

MainWindow::~MainWindow()
{
    delete ui;
}

