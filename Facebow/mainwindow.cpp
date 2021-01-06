#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    serialPort = new SerialPort();

    connect(serialPort, &SerialPort::positionChanged, ui->openGLWidget, &GLWidget::on_facebow_pos_changed);

}

MainWindow::~MainWindow()
{
    delete ui;
}

