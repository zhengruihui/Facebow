#include "pagereport.h"
#include "ui_pagereport.h"
#include <QPainter>
#include <QPrinter>
#include <QDateTime>
#include <QtWebEngineWidgets/QtWebEngineWidgets>
#include <printhandler.h>
#include <QShortcut>
#include "devicesystem.h"
#include <QGraphicsDropShadowEffect>


PageReport::PageReport(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PageReport)
{
    ui->setupUi(this);


    currentPath = QDir::currentPath();

    ui->widget->page()->setBackgroundColor(QColor("#454449"));


//    QString pathToPDFjs = QString("C:/Users/zheng/Documents/Gitee/Facebow/Resources/Html/viewer.html");
//    QString pdfFileURL;
//    pdfFileURL = QString("report.pdf");
//    view->load(QUrl::fromUserInput(pathToPDFjs+QString("? file =") + pdfFileURL));

//     QWebEngineSettings::defaultSettings()->setAttribute(QWebEngineSettings::PluginsEnabled, true);

//     view->setUrl(QUrl("C:/Users/zheng/Documents/Gitee/build-Facebow-Desktop_Qt_5_15_2_MSVC2019_32bit-Debug/report.pdf"));
//     //view->resize(1024, 750);
//     view->show();

    QToolButton *buttonHandle[] = {ui->toolButtonPDF, ui->toolButtonPrint};


    for(int i=0; i<2; i++)
    {
        //设置阴影
        QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect(this);
        shadow->setOffset(2, 2);
        shadow->setColor(QColor(QRgb(0x0)));
        shadow->setBlurRadius(30);
        buttonHandle[i]->setGraphicsEffect(shadow);
    }



    series1 = new QSplineSeries();
    m_chart = new QChart();
    chartView = new QChartView();

}

PageReport::~PageReport()
{
    delete ui;
}

void PageReport::loadReport()
{
    ui->widget->setZoomFactor(0.48f+(ui->widget->width()-1228)*0.0004808f);

}

void PageReport::on_pdfPrintingFinished()
{
    qDebug() << "on_pdfPrintingFinished";
}


void PageReport::on_toolButtonZoomIn_clicked()
{

    ui->widget->setZoomFactor(ui->widget->zoomFactor()+0.05f);
    ui->widget->update();
}

void PageReport::on_toolButtonZoomOut_clicked()
{
    ui->widget->setZoomFactor(ui->widget->zoomFactor()-0.05f);
    ui->widget->update();
}

void PageReport::on_toolButtonNormal_clicked()
{
    ui->widget->setZoomFactor(0.48f+(ui->widget->width()-1228)*0.0004808f);
    ui->widget->update();
}

void PageReport::on_toolButtonPDF_clicked()
{
   QString path("report.pdf");

   QString fileName = QFileDialog::getSaveFileName(this,
           QString::fromLocal8Bit("文件另存为"),
           "",
           tr("Report Files (*.pdf)"));
   if(fileName != "")
   {
       ui->widget->page()->printToPdf(fileName, QPageLayout(QPageSize(QPageSize::A4), QPageLayout::Landscape, QMarginsF(0,0,0,0)));
   }


}

void PageReport::on_toolButtonPrint_clicked()
{

    PrintHandler handler;
    handler.setPage(ui->widget->page());

    handler.printPreview();

//    auto printPreviewShortCut = new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_P), view);
//    auto printShortCut = new QShortcut(QKeySequence(Qt::CTRL + Qt::SHIFT + Qt::Key_P), view);

//    QObject::connect(printPreviewShortCut, &QShortcut::activated, &handler, &PrintHandler::printPreview);
//    QObject::connect(printShortCut, &QShortcut::activated, &handler, &PrintHandler::print);

//    QPrinter printer(QPrinter::HighResolution);
//    printer.setDocName("report.pdf");
//    QPrintDialog dialog(&printer, this);
//    if (dialog.exec() != QDialog::Accepted)
//        return;


}



void PageReport::on_toolButton1_1_clicked()
{
    ui->widget->setZoomFactor(0.48f+(ui->widget->width()-1228)*0.0004808f);
    ui->widget->update();
}

void PageReport::on_toolButtonhorizontal_clicked()
{
    ui->widget->setZoomFactor(1.5f+(ui->widget->width()-1228)*0.0013f);
    ui->widget->update();
}

void PageReport::on_toolButtonFill_clicked()
{
    ui->widget->setZoomFactor(1.5f+(ui->widget->width()-1228)*0.0013f);
    ui->widget->update();
}

void PageReport::on_toolButtonLayout_clicked()
{
    ui->widget->setZoomFactor(1.5f+(ui->widget->width()-1228)*0.0013f);
    ui->widget->update();
}
