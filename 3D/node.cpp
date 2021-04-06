#include "node.h"
#include <QFile>
#include <QDebug>
#include <QDir>


Node::Node()
{

}

bool Node::loadObjModel(QString fileName, QVector<float> &vPoints,QVector<float> &tPoints,QVector<float> &nPoints)
{
    QVector<float> vPoints_t;
    QVector<float> tPoints_t;
    QVector<float> nPoints_t;

    QFile vPointsFile(QString().append(QDir::currentPath()).append("/vPoints.bin"));
    QFile tPointsFile(QString().append(QDir::currentPath()).append("/tPoints.bin"));
    QFile nPointsFile(QString().append(QDir::currentPath()).append("/nPoints.bin"));

    QFile objFile(fileName);
    if(!objFile.open(QIODevice::ReadOnly)){
        qDebug() << "open" << fileName << "failed";
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

        vPoints << vertextPoints.at(vIndex * 3 + 0);
        vPoints << vertextPoints.at(vIndex * 3 + 1);
        vPoints << vertextPoints.at(vIndex * 3 + 2);

        tPoints << texturePoints.at(tIndex * 2 + 0);
        tPoints << texturePoints.at(tIndex * 2 + 1);

        nPoints << normalPoints.at(nIndex * 3 + 0);
        nPoints << normalPoints.at(nIndex * 3 + 1);
        nPoints << normalPoints.at(nIndex * 3 + 2);
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

bool Node::loadBinModel(QString fileName, QByteArray &vPoints, QByteArray &tPoints, QByteArray &nPoints)
{
      QFile vPointsFile(QString(":/Resources/Mesh/").append(fileName).append("_vPoints.bin"));
      QFile tPointsFile(QString(":/Resources/Mesh/").append(fileName).append("_tPoints.bin"));
      QFile nPointsFile(QString(":/Resources/Mesh/").append(fileName).append("_nPoints.bin"));


      if(vPointsFile.open(QIODevice::ReadOnly))
      {
          vPoints = vPointsFile.readAll();
          vPointsFile.close();
      }


      if(tPointsFile.open(QIODevice::ReadOnly))
      {
          tPoints = tPointsFile.readAll();
          tPointsFile.close();
      }


      if(nPointsFile.open(QIODevice::ReadOnly))
      {
          nPoints = nPointsFile.readAll();
          nPointsFile.close();
      }

      return true;

}

bool Node::loadStlModel(QString fileName)
{
    QFile file(fileName);

    if(file.open(QIODevice::ReadOnly))
    {
        struct Model *model = new struct Model();
        model->modelName = "skull";

        QByteArray byteArray = file.readAll();

        char* allData = byteArray.data();

        uint32_t triangleFacet = *(uint32_t*)(allData+80);

        for(uint32_t i=0; i<triangleFacet; i++)
        {
            float nx = *(float*)(allData+84+50*i+0*4);
            float ny = *(float*)(allData+84+50*i+1*4);
            float nz = *(float*)(allData+84+50*i+2*4);
            for(uint32_t j=0; j<12; j++)
            {
                if(j<3){
                    model->normalVector.append(nx);
                    model->normalVector.append(ny);
                    model->normalVector.append(nz);
                }else{
                    model->vertexVector.append(*(float*)(allData+84+50*i+j*4));
                }

            }

        }

        modelVector.append(model);
        file.close();
        return true;
    }
    else
    {
        return false;
    }
}

QVector<float> Node::getVertexVector(uint8_t index)
{
    return modelVector.at(index)->vertexVector;
}

QVector<float> Node::getNormalVector(uint8_t index)
{
    return modelVector.at(index)->normalVector;
}

QVector<float> Node::getTextureVector(uint8_t index)
{
    return modelVector.at(index)->textureVector;
}
