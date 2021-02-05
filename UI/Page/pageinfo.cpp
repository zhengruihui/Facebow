#include "pageinfo.h"
#include "ui_pageinfo.h"
#include <QGraphicsDropShadowEffect>
#include "PatientItem/patientitem.h"
#include <QDebug>
#include "devicesystem.h"
#include <QDateTime>

PageInfo::PageInfo(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PageInfo)
{
    ui->setupUi(this);

    dialogInfo = new DialogInfo(this);

    //设置阴影
    QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect(this);
    shadow->setOffset(1, 0);
    shadow->setColor(QColor(QRgb(0x0)));
    shadow->setBlurRadius(20);
    ui->widgetSearch->setGraphicsEffect(shadow);

    connect(DeviceSystem::getInstance()->getDatabase(), &Database::queryByNameChanged, this,  &PageInfo::updateListWidget);


    connect(dialogInfo, &DialogInfo::pushButtonOK_clicked, this,  &PageInfo::dialogPushButtonOK_clicked, Qt::QueuedConnection);
    connect(dialogInfo, &DialogInfo::pushButtonCancel_clicked, this,  &PageInfo::dialogPushButtonCancel_clicked, Qt::QueuedConnection);

    DeviceSystem::getInstance()->getDatabase()->queryByName("");

}

PageInfo::~PageInfo()
{
    delete ui;
}


void PageInfo::on_pushButtonAdd_clicked()
{
    dialogInfo->setPID(ui->labelPID->text());
    dialogInfo->setPSex(ui->labelSex->text());
    dialogInfo->setPBirthday(ui->labelBirthday->text());
    dialogInfo->setPName(ui->labelName->text());

    dialogInfo->open();
    isAdd = true;
}

void PageInfo::on_pushButtonEditInfo_clicked()
{
    dialogInfo->setPID(ui->labelPID->text());
    dialogInfo->setPSex(ui->labelSex->text());
    dialogInfo->setPBirthday(ui->labelBirthday->text());
    dialogInfo->setPName(ui->labelName->text());

    dialogInfo->open();
    isAdd = false;
}

void PageInfo::on_listWidget_itemPressed(QListWidgetItem *item)
{
    QWidget *widget = ui->listWidget->itemWidget(item);

    PatientItem *patientItem = static_cast<PatientItem*>(widget);

    ui->labelPID->setText(patientItem->getPID());
    ui->labelSex->setText(patientItem->getPSex());
    ui->labelBirthday->setText(patientItem->getPBirthday());
    ui->labelName->setText(patientItem->getPName());
    ui->textEditDiagnosis->setText(patientItem->getPDiagnosis());

    DeviceSystem::getInstance()->setCurrentDatabaseID(patientItem->getID());

}


void PageInfo::on_lineEdit_textChanged(const QString &arg1)
{
    DeviceSystem::getInstance()->getDatabase()->queryByName(arg1);
}

void PageInfo::updateListWidget(QSqlQuery query)
{
    ui->listWidget->clear();

    while(query.next())
    {

        PatientItem * patientItem = new PatientItem();
        QListWidgetItem * newItem = new QListWidgetItem();


        patientItem->setID(query.value(0).toString());
        patientItem->setPTimestamp(query.value(1).toLongLong());
        patientItem->setPID(query.value(2).toString());
        patientItem->setPName(query.value(3).toString());
        patientItem->setPSex(query.value(4).toString());
        patientItem->setPBirthday(query.value(5).toString());
        patientItem->setPDiagnosis(query.value(6).toString());


        ui->listWidget->addItem(newItem);
        ui->listWidget->setItemWidget(newItem, patientItem);

        if(query.at() == 0)
        {
            ui->listWidget->setCurrentItem(newItem);
            on_listWidget_itemPressed(newItem);
        }
    }


}



void PageInfo::on_pushButtonSaveDiagnosis_clicked()
{
    DeviceSystem::getInstance()->getDatabase()->updateDiagnosisById(DeviceSystem::getInstance()->getCurrentDatabaseID(), QDateTime::currentMSecsSinceEpoch()/1000, ui->textEditDiagnosis->toPlainText());
    DeviceSystem::getInstance()->getDatabase()->queryByName(ui->lineEdit->text());
}

void PageInfo::dialogPushButtonOK_clicked()
{
    dialogInfo->close();
    if(isAdd)
    {
        DeviceSystem::getInstance()->getDatabase()->insert(QDateTime::currentMSecsSinceEpoch()/1000, dialogInfo->getPID(), dialogInfo->getPName(), dialogInfo->getPSex(), dialogInfo->getPBirthday());
    }
    else
    {
        DeviceSystem::getInstance()->getDatabase()->updateById(DeviceSystem::getInstance()->getCurrentDatabaseID(), QDateTime::currentMSecsSinceEpoch()/1000, dialogInfo->getPID(), dialogInfo->getPName(), dialogInfo->getPSex(),dialogInfo->getPBirthday());
    }

    DeviceSystem::getInstance()->getDatabase()->queryByName(ui->lineEdit->text());

}

void PageInfo::dialogPushButtonCancel_clicked()
{
    dialogInfo->close();
}
