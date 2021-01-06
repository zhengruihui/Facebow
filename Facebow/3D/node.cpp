#include "node.h"
#include <QFile>
#include <QDebug>


Node::Node()
{

}

bool Node::loadObjModel(QString fileName)
{
    QFile file(fileName);
    struct Model *model;

    QVector<float> vVector;
    QVector<float> vtVector;
    QVector<float> vnVector;



    if(file.open(QIODevice::ReadOnly))
    {

        while(!file.atEnd())
        {
            QString line = file.readLine();
            QList<QString> lineList = line.split(" ");

            QString key = lineList.at(0);


            if(key == "v")
            {
                for(int i=0; i<3; i++)
                {
                    vVector.append(lineList.at(i+1).toFloat());
                }

            }else if(key == "vt")
            {
                for(int i=0; i<3; i++)
                {
                    vtVector.append(lineList.at(i+1).toFloat());
                }


            }else if(key == "vn")
            {

                for(int i=0; i<3; i++)
                {
                    vnVector.append(lineList.at(i+1).toFloat());
                }

            }else if(key == "f")
            {
                for(int i=0; i<4; i++)
                {
                    QList<QString> fList = lineList.at(i+1).split("/");
                    int vIndex = fList.at(0).toInt() - 1;
                    int vtIndex = fList.at(1).toInt() - 1;
                    int vnIndex = fList.at(2).toInt() - 1;

                    for(int j=0; j<3; j++)
                    {
                        model->vertexVector.append(vVector.at(vIndex*3+j));
                        model->uvVector.append(vVector.at(vtIndex*3+j));
                        model->normalVector.append(vVector.at(vnIndex*3+j));
                    }


                }



            }
            else if(key == "o")
            {
                model = new struct Model;
                model->modelName = lineList.at(1);
                modelVector.append(model);
            }



        }

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
            for(uint32_t j=0; j<12; j++)
            {
                if(j<3){
                    model->normalVector.append(*(float*)(allData+84+50*i+j*4));
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

QVector<float> Node::getNormalData(uint8_t index)
{
    return modelVector.at(index)->normalVector;
}

QVector<float> Node::getUvData(uint8_t index)
{
    return modelVector.at(index)->uvVector;
}
