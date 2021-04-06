#include "pagemeasure.h"
#include "ui_pagemeasure.h"
#include "devicesystem.h"
#include <QButtonGroup>
#include <QGraphicsDropShadowEffect>
#include "UI/Button/button.h"

PageMeasure::PageMeasure(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PageMeasure)
{
    ui->setupUi(this);
    //导航按键组
    QButtonGroup *buttonGroupSkull = new QButtonGroup(this);
    buttonGroupSkull->addButton(ui->toolButtonOblique);
    buttonGroupSkull->addButton(ui->toolButtonForward);
    buttonGroupSkull->addButton(ui->toolButtonLeft);
    buttonGroupSkull->addButton(ui->toolButtonTop);
    buttonGroupSkull->addButton(ui->toolButtonRight);


    QToolButton *buttonHandle[] = {ui->toolButtonMeasureStart, ui->toolButtonMeasureSetting, ui->toolButtonDeviceSetting};

    //ui->quickWidget->setSource(QUrl(QStringLiteral("qrc:/UI/Page/Qml/skull.qml")));

    for(int i=0; i<4; i++)
    {
        //设置阴影

        //buttonStep[i]->setGraphicsEffect(shadow);
    }

    for(int i=0; i<3; i++)
    {
        //设置阴影
        QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect(this);
        shadow->setOffset(2, 2);
        shadow->setColor(QColor(QRgb(0x0)));
        shadow->setBlurRadius(30);
        buttonHandle[i]->setGraphicsEffect(shadow);
    }

    ui->listWidgetButton->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->listWidgetButton->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    for(int i=0; i<7; i++)
    {
        Button * button = new Button();
        QListWidgetItem * newItem = new QListWidgetItem();


//        QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect(this);
//        shadow->setOffset(2, 2);
//        shadow->setColor(QColor(QRgb(0x0)));
//        shadow->setBlurRadius(30);
//        button->setGraphicsEffect(shadow);
        button->setImage(QString(":/Resources/Step/%1s.png").arg(i+1));
        button->setStep(QString("%1").arg(i+1));

        switch (i) {
            case 0:
                button->setText(tr("Tooth static position measurement"));
            break;
            case 1:
                button->setText(tr("left static position measurement"));
            break;
            case 2:
                button->setText(tr("right static position measurement"));
            break;
            case 3:
                button->setText(tr("Move forward"));
            break;
            case 4:
                button->setText(tr("Movement left "));
            break;
            case 5:
                button->setText(tr("Movement right"));
            break;
            case 6:
                button->setText(tr("Open Closed"));
            break;
        }



        ui->listWidgetButton->addItem(newItem);
        ui->listWidgetButton->setItemWidget(newItem, button);

    }
}

PageMeasure::~PageMeasure()
{
    delete ui;
}



void PageMeasure::on_toolButtonMeasureStart_clicked(bool checked)
{
    DeviceSystem::getInstance()->setMeasureStart(checked);
}

void PageMeasure::on_toolButtonMeasureSetting_pressed()
{

}

void PageMeasure::on_toolButtonDeviceSetting_pressed()
{

}



void PageMeasure::on_listWidgetButton_itemPressed(QListWidgetItem *item)
{
    QWidget *widget = ui->listWidgetButton->itemWidget(item);

    Button *button = static_cast<Button*>(widget);

    ui->imageWidget->setImage(QString(":/Resources/Step/%1B.png").arg(button->getStep()));
    DeviceSystem::getInstance()->setStep(button->getStep().toInt());
}

void PageMeasure::on_toolButtonZoomOut_clicked()
{
    ui->openGLWidget->zoomOut();
}

void PageMeasure::on_toolButtonZoomIn_clicked()
{
    ui->openGLWidget->zoomIn();
}

void PageMeasure::on_toolButtonNormal_clicked()
{
    ui->openGLWidget->normal();
}

void PageMeasure::on_toolButtonLeft_clicked(bool checked)
{
    Q_UNUSED(checked);
    ui->openGLWidget->cameraPerspectiveLookAt(90);
}

void PageMeasure::on_toolButtonRight_clicked(bool checked)
{
    Q_UNUSED(checked);
    ui->openGLWidget->cameraPerspectiveLookAt(-90);
}

void PageMeasure::on_toolButtonForward_clicked(bool checked)
{
    Q_UNUSED(checked);
    ui->openGLWidget->cameraPerspectiveLookAt(0);
}

void PageMeasure::on_toolButtonTop_clicked(bool checked)
{
    Q_UNUSED(checked);
    ui->openGLWidget->cameraPerspectiveLookAtTop();
}

void PageMeasure::on_toolButtonOblique_clicked(bool checked)
{
    Q_UNUSED(checked);
    ui->openGLWidget->cameraPerspectiveLookAt(-45);
}
