#ifndef QLWIDGET_H
#define QLWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLExtraFunctions>
#include <QOpenGLFunctions_3_3_Core>
#include <QOpenGLShader>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLTexture>
#include "3D/node.h"
#include <QMouseEvent>

namespace Ui {
class QLWidget;
}


#define SKULL1INDEX 0
#define SKULL2INDEX 1


class GLWidget : public QOpenGLWidget , protected QOpenGLExtraFunctions
{
    Q_OBJECT

public:
    explicit GLWidget(QWidget *parent = nullptr);
    ~GLWidget();

    void cameraPerspectiveLookAt(float angle);

protected:

    void initializeGL()override;
    void resizeGL(int w, int h)override;
    void paintGL()override;


   void wheelEvent(QWheelEvent *event)override;





public slots:
    void on_facebowPosChanged(float x, float y, float z, float c, float p, float r);
signals:
    void updatePage();

private:
    Ui::QLWidget *ui;

    QWidget *parent;


    QOpenGLVertexArrayObject *skull1_vao;
    QOpenGLVertexArrayObject *skull2_vao;

    QOpenGLBuffer *m_vbo, *m_nbo;
    QOpenGLShaderProgram *m_shader;


    QVector3D cameraEye;
    QVector3D cameraCenter;
    QVector3D cameraUp;

    QVector3D lightPos;

    float moveX;
    float moveY;
    float moveZ;
    float eulerRotationX;
    float eulerRotationY;
    float eulerRotationZ;
    QVector3D rotateVector;


    float aspectRatio;
    float scaleFactor;

    Node *node;


};

#endif // QLWIDGET_H
