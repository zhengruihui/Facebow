#include "dialoginfo.h"
#include "ui_dialoginfo.h"
#include <QButtonGroup>
#include <QThread>
#include <QDebug>

DialogInfo::DialogInfo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogInfo)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Window | Qt::FramelessWindowHint);

    //导航按键组
    QButtonGroup *buttonGroupPage = new QButtonGroup(this);
    buttonGroupPage->addButton(ui->pushButtonFemale);
    buttonGroupPage->addButton(ui->pushButtonMale);

//    connect(ui->pushButtonOK, &QPushButton::pressed, this, &DialogInfo::pushButtonOK_clicked);
//    connect(ui->pushButtonCancel, &QPushButton::pressed, this, &DialogInfo::pushButtonCancel_clicked);
}

DialogInfo::~DialogInfo()
{
    delete ui;
}

void DialogInfo::setPID(QString value)
{
    ui->lineEditPID->setText(value);
}

void DialogInfo::setPSex(QString value)
{

}

void DialogInfo::setPBirthday(QString value)
{
    ui->lineEditBirthday->setText(value);
}

void DialogInfo::setPName(QString value)
{
    ui->lineEditName->setText(value);
}

QString DialogInfo::getPID()
{
    return ui->lineEditPID->text();
}

QString DialogInfo::getPBirthday()
{
    return ui->lineEditBirthday->text();
}

QString DialogInfo::getPName()
{
    return ui->lineEditName->text();
}

QString DialogInfo::getPSex()
{
   if(ui->pushButtonMale->isChecked())
   {
       return QString(tr("Male"));
   }
   else
   {
       return  QString(tr("Female"));
   }
}

void DialogInfo::on_pushButtonOK_clicked()
{
    emit pushButtonOK_clicked();
}

void DialogInfo::on_pushButtonCancel_clicked()
{
    emit pushButtonCancel_clicked();
}
