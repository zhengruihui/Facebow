#include "node.h"
#include <QFile>
#include <QDebug>


Node::Node()
{

}

bool Node::loadObjModel(QString fileName)
{
    QFile file(fileName);


    if(file.open(QIODevice::ReadOnly))
    {



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

QVector<float> Node::getNormalVector(uint8_t index)
{
    return modelVector.at(index)->normalVector;
}

QVector<float> Node::getTextureVector(uint8_t index)
{
    return modelVector.at(index)->textureVector;
}
