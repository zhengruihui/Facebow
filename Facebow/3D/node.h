#ifndef NODE_H
#define NODE_H
#include <QString>
#include <QVector>
#include <QList>

struct Face
{
    float x;
    float y;
    float z;
    float w;

};


struct Material
{
    float ns;     //shinness
    float ka[3];
    float Kd[3];
    float ks[3];
    float d;
    float tr;

    QString textureName;
    int textureId;
};

struct Model
{
    QString modelName;
    QVector<float> vertexVector;
    QVector<float> normalVector;
    QVector<float> uvVector;

};

class Node
{
public:
    Node();
    void loadObjModel(QString fileName);
    void loadStlModel(QString fileName);
    QVector<struct Model*> modelVector;

    QVector<float> getVertexVector(QString modelName);
    QVector<float> getNormalData(QString modelName);
    QVector<float> getUvData(QString modelName);

};

#endif // NODE_H
