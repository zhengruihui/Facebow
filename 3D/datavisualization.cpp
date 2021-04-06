#include "datavisualization.h"
#include "ui_datavisualization.h"
#include <QtDataVisualization/QScatter3DSeries>
#include "devicesystem.h"

DataVisualization::DataVisualization(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DataVisualization)
{
    ui->setupUi(this);

    itemSkull1 = new QScatter3DSeries();
    itemSkull1->setMesh(QAbstract3DSeries::MeshUserDefined);
    itemSkull1->setUserDefinedMesh(":/Resources/Mesh/skull1.obj");
    itemSkull1->setItemSize(0.1f);
    itemSkull1->setBaseColor(QColor(128, 128, 128));

    itemSkull2 = new QScatter3DSeries();
    itemSkull2->setMesh(QAbstract3DSeries::MeshUserDefined);
    itemSkull2->setUserDefinedMesh(":/Resources/Mesh/skull2.obj");
    itemSkull2->setItemSize(0.1f);
    itemSkull2->setBaseColor(QColor(128, 128, 128));

    itemPoint = new QScatter3DSeries();
    itemPoint->setMesh(QAbstract3DSeries::MeshSphere);
    itemPoint->setMeshSmooth(true);
    itemPoint->setItemSize(0.02f);
    itemPoint->setBaseColor(QColor(255, 0, 0));

    m_graph = new Q3DScatter();

    m_graph->activeTheme()->setType(Q3DTheme::ThemeStoneMoss);
    m_graph->activeTheme()->setLabelBackgroundColor(QColor(QRgb(0x151550)));
    m_graph->activeTheme()->setLabelTextColor(Qt::lightGray);
    m_graph->activeTheme()->setFont(QFont("Arial Black", 1));


    m_graph->activeTheme()->setLabelBackgroundEnabled(false);
    m_graph->activeTheme()->setLabelBorderEnabled(false);
//    m_graph->activeTheme()->setGridEnabled(false);

    m_graph->axisX()->setRange(-200.0f, 200.0f);
    m_graph->axisY()->setRange(-200.0f, 200.0f);
    m_graph->axisZ()->setRange(-200.0f, 200.0f);

    m_graph->axisX()->setLabelFormat("%.2f mm X");
    m_graph->axisY()->setLabelFormat("%.2f mm Y");
    m_graph->axisZ()->setLabelFormat("%.2f mm Z");

//    m_graph->axisX()->setLabelFormat("");
//    m_graph->axisY()->setLabelFormat("");
//    m_graph->axisZ()->setLabelFormat("");



    m_graph->addSeries(itemSkull1);
    m_graph->addSeries(itemSkull2);
    m_graph->addSeries(itemPoint);

    QWidget *container = QWidget::createWindowContainer(m_graph);
    ui->verticalLayout->addWidget(container, 1);

    QScatterDataItem skull1;
    skull1.setPosition(QVector3D(0.0f, 0.0f, 0.0f));
    QScatterDataItem skull2;
    skull2.setPosition(QVector3D(0.0f, 0.0f, 0.0f));

    dataArraySkull1 = new QScatterDataArray;
    dataArraySkull1->append(skull1);


    dataArraySkull2 = new QScatterDataArray;
    dataArraySkull2->append(skull2);

    dataArrayPoint = new QScatterDataArray;

    itemSkull1->dataProxy()->resetArray(dataArraySkull1);
    itemSkull2->dataProxy()->resetArray(dataArraySkull2);
    itemPoint->dataProxy()->resetArray(dataArrayPoint);

    QObject::connect(DeviceSystem::getInstance(), &DeviceSystem::facebowPosChanged, this,  &DataVisualization::on_facebowPosChanged, Qt::QueuedConnection);
}

DataVisualization::~DataVisualization()
{
    delete ui;
}


void DataVisualization::on_facebowPosChanged(float x, float y, float z, float c, float p, float r)
{
    QScatterDataItem *ptr = &dataArraySkull2->first();
    ptr->setPosition(QVector3D(x, y, z));
    ptr->setRotation(QQuaternion::fromAxisAndAngle(QVector3D(0.0f, 1.0f, 0.0f), c));
    ptr->setRotation(QQuaternion::fromAxisAndAngle(QVector3D(1.0f, 0.0f, 0.0f), p));
    ptr->setRotation(QQuaternion::fromAxisAndAngle(QVector3D(0.0f, 0.0f, 1.0f), r));

    itemSkull2->dataProxy()->resetArray(dataArraySkull2);


//    QScatterDataItem point;
//    point.setPosition(QVector3D(x, y, z));

//    dataArrayPoint->append(point);
//    itemPoint->dataProxy()->resetArray(dataArrayPoint);


}
