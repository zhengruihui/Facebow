#include "button.h"
#include "ui_button.h"

Button::Button(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Button)
{
    ui->setupUi(this);
}

Button::~Button()
{
    delete ui;
}
