#include "node.h"
#include <QFile>
#include <QDebug>


Node::Node()
{

}

void Node::loadObjModel(QString fileName)
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

    qDebug() << "obj done!";
}

QVector<float> Node::getVertexVector(QString modelName)
{
    for(int i=0; i<modelVector.size(); i++)
    {
        if(modelVector.at(i)->modelName.contains(modelName))
        {
            return modelVector.at(i)->vertexVector;
        }
    }
}

QVector<float> Node::getNormalData(QString modelName)
{
    for(int i=0; i<modelVector.size(); i++)
    {
        if(modelVector.at(i)->modelName.contains(modelName))
        {
            return modelVector.at(i)->normalVector;
        }
    }

}

QVector<float> Node::getUvData(QString modelName)
{
    for(int i=0; i<modelVector.size(); i++)
    {
        if(modelVector.at(i)->modelName.contains(modelName))
        {
            return modelVector.at(i)->uvVector;
        }
    }

}
