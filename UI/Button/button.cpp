#include "button.h"
#include "ui_button.h"

Button::Button(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Button)
{
    ui->setupUi(this);

    //设置阴影

}

Button::~Button()
{
    delete ui;
}

void Button::setImage(QString path)
{
    QImage img=QImage(path);
    ui->labelImage->setPixmap(QPixmap::fromImage(img));
}

void Button::setStep(QString step)
{
    ui->labelStep->setText(step);
}

QString Button::getStep()
{
    return ui->labelStep->text();
}

void Button::setText(QString text)
{
    ui->labelText->setText(text);
}


