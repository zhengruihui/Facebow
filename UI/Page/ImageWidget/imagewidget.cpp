#include "imagewidget.h"
#include "ui_imagewidget.h"
#include <QPainter>

ImageWidget::ImageWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ImageWidget)
{
    ui->setupUi(this);
}

ImageWidget::~ImageWidget()
{
    delete ui;
}

void ImageWidget::setImage(QString value)
{
    imagePath = value;
    update();
}

void ImageWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setBrush(QBrush(QColor(0x45, 0x44, 0x49)));

    painter.drawRect(-1, -1, width()+1, height()+1);
    if(imagePath.size()>0)
    {
        QPixmap  image(imagePath);
        image = image.scaled(width(), height());
        painter.drawPixmap((width()-image.width())/2, (height()-image.height())/2, image);
    }




}
