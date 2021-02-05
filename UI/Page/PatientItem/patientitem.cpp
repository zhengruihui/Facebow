#include "patientitem.h"
#include "ui_patientitem.h"

PatientItem::PatientItem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PatientItem)
{
    ui->setupUi(this);
}

PatientItem::~PatientItem()
{
    delete ui;
}

void PatientItem::setID(QString value)
{
    ID = value;
}

void PatientItem::setPID(QString value)
{
    pID = value;
}

void PatientItem::setPName(QString value)
{
    ui->labelName->setText(value);
}

void PatientItem::setPSex(QString value)
{
    ui->labelSex->setText(value);
}

void PatientItem::setPBirthday(QString value)
{
    ui->labelAge->setText(value);
}

void PatientItem::setPDiagnosis(QString value)
{
    pDiagnosis = value;
}

void PatientItem::setPTimestamp(long long value)
{
    timestamp = value;
}



QString PatientItem::getID()
{
    return ID;
}

QString PatientItem::getPID()
{
    return pID;
}

QString PatientItem::getPName()
{
    return ui->labelName->text();
}

QString PatientItem::getPSex()
{
    return ui->labelSex->text();
}

QString PatientItem::getPBirthday()
{
    return ui->labelAge->text();
}

QString PatientItem::getPDiagnosis()
{
    return pDiagnosis;
}

long long PatientItem::getPTimestamp()
{
    return timestamp;
}
