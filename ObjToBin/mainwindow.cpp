#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QDebug>
#include <QFileInfo>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::loadObjModel()
{
    QVector<float> vPoints_t;
    QVector<float> tPoints_t;
    QVector<float> nPoints_t;

    QFileInfo fileInfo;
    QString file, fileName, fileSuffix, filePath;
    file = QFileDialog::getOpenFileName();
    fileInfo = QFileInfo(file);

    filePath = fileInfo.absolutePath().append("/");
    fileName = fileInfo.fileName().split(".").at(0);



    QFile vPointsFile(QString(filePath).append(fileName).append("_vPoints.bin"));
    QFile tPointsFile(QString(filePath).append(fileName).append("_tPoints.bin"));
    QFile nPointsFile(QString(filePath).append(fileName).append("_nPoints.bin"));

    QFile objFile(file);
    if(!objFile.open(QIODevice::ReadOnly)){
        qDebug() << "open" << file << "failed";
        return false;
    }

    QVector<float> vertextPoints,texturePoints,normalPoints;
    QVector<std::tuple<int,int,int>> facesIndexs;
    while (!objFile.atEnd()) {
        QByteArray lineData = objFile.readLine();
        lineData = lineData.remove(lineData.count() - 1,1);

        QList<QByteArray> strValues = lineData.split(' ');
        QString dataType = strValues.takeFirst();

        if(dataType == "v"){
            std::transform(strValues.begin(),strValues.end(),std::back_inserter(vertextPoints),[](QByteArray &str){
                return str.toFloat();
            });
        }else if(dataType == "vt"){
            std::transform(strValues.begin(),strValues.end(),std::back_inserter(texturePoints),[](QByteArray &str){
                return str.toFloat();
            });
        }else if(dataType == "vn"){
            std::transform(strValues.begin(),strValues.end(),std::back_inserter(normalPoints),[](QByteArray &str){
                return str.toFloat();
            });
        }else if(dataType == "f"){
            std::transform(strValues.begin(),strValues.end(),std::back_inserter(facesIndexs),[](QByteArray &str){
                QList<QByteArray> intStr = str.split('/');
                return std::make_tuple(intStr.first().toInt(),intStr.at(1).toInt(),intStr.last().toInt());
            });
        }
    }



    for(auto &verFaceInfo : facesIndexs){
        int vIndex = std::get<0>(verFaceInfo)-1;
        int tIndex = std::get<1>(verFaceInfo)-1;
        int nIndex = std::get<2>(verFaceInfo)-1;

        vPoints_t << vertextPoints.at(vIndex * 3 + 0);
        vPoints_t << vertextPoints.at(vIndex * 3 + 1);
        vPoints_t << vertextPoints.at(vIndex * 3 + 2);

        tPoints_t << texturePoints.at(tIndex * 2 + 0);
        tPoints_t << texturePoints.at(tIndex * 2 + 1);

        nPoints_t << normalPoints.at(nIndex * 3 + 0);
        nPoints_t << normalPoints.at(nIndex * 3 + 1);
        nPoints_t << normalPoints.at(nIndex * 3 + 2);
    }

    vertextPoints.clear();
    texturePoints.clear();
    normalPoints.clear();
    facesIndexs.clear();

    objFile.close();

    if(vPointsFile.open(QIODevice::WriteOnly))
    {
        vPointsFile.write((const char *)vPoints_t.data(), vPoints_t.size()*sizeof (float));
        vPointsFile.close();
    }


    if(tPointsFile.open(QIODevice::WriteOnly))
    {
        tPointsFile.write((const char *)tPoints_t.data(), tPoints_t.size()*sizeof (float));
        tPointsFile.close();
    }


    if(nPointsFile.open(QIODevice::WriteOnly))
    {
        nPointsFile.write((const char *)nPoints_t.data(), nPoints_t.size()*sizeof (float));
        nPointsFile.close();
    }


    return true;

}


void MainWindow::on_pushButton_clicked()
{
    loadObjModel();
}
