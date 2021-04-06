#include "webview.h"
#include "ui_webview.h"
#include "devicesystem.h"

WebView::WebView(QWidget *parent) :
    QWebEngineView(parent),
    ui(new Ui::WebView)
{
    ui->setupUi(this);

    timer = new QTimer();

    connect(this->timer, &QTimer::timeout, this, &WebView::on_timeout);
    connect(this, &WebView::loadFinished, this, &WebView::on_loadFinished);
    connect(this, &WebView::loadProgress, this, &WebView::on_loadProgress);

    QObject::connect(DeviceSystem::getInstance(), &DeviceSystem::loadImage, this,  &WebView::on_loadImage, Qt::QueuedConnection);
}

WebView::~WebView()
{
    delete ui;
}

void WebView::loadHtml()
{
    QString currentPath = QDir::currentPath();

    QFile fileHtml(":/Resources/Html/index.html");

    if(fileHtml.open(QIODevice::ReadOnly))
    {
       html = fileHtml.readAll();

       fileHtml.close();
    }


    QString htmlPDF =  QString(html).arg(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"))  //时间
                                    .arg(DeviceSystem::getInstance()->getCurrentName()) //姓名
                                    .arg(DeviceSystem::getInstance()->getCurrentBitrhday()) //出生年月
                                    .arg(DeviceSystem::getInstance()->getCurrentSex()) //性别
                                    .arg(QString::number(DeviceSystem::getInstance()->getLeftStaticCoord().x(), 'f', 2)) //左髁突静态坐标X
                                    .arg(QString::number(DeviceSystem::getInstance()->getLeftStaticCoord().y(), 'f', 2))
                                    .arg(QString::number(DeviceSystem::getInstance()->getLeftStaticCoord().z(), 'f', 2))
                                    .arg(QString::number(DeviceSystem::getInstance()->getRightStaticCoord().x(), 'f', 2))
                                    .arg(QString::number(DeviceSystem::getInstance()->getRightStaticCoord().y(), 'f', 2))
                                    .arg(QString::number(DeviceSystem::getInstance()->getRightStaticCoord().z(), 'f', 2));


    QFile filePDF(QString().append(currentPath).append("/Html/pdf.html"));
    if(filePDF.open(QIODevice::WriteOnly))
    {
        filePDF.write(htmlPDF.toUtf8());
        filePDF.close();
    }



    load(QUrl(QString().append(currentPath).append("/Html/pdf.html")));
}

void WebView::on_timeout()
{
    update();
}

void WebView::on_loadFinished()
{
    static bool timerStart = true;
    if(timerStart)
    {
        timer->start(100);
    }
    update();
}

void WebView::on_loadProgress(int progress)
{
    //qDebug() << progress;
    Q_UNUSED(progress);
}

void WebView::on_loadImage(int step)
{
    if(step == 3)
    {
        loadHtml();
    }
    else if(step > 3)
    {
        reload();
    }

}


