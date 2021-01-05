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

namespace Ui {
class QLWidget;
}


class GLWidget : public QOpenGLWidget , protected QOpenGLExtraFunctions
{
    Q_OBJECT

public:
    explicit GLWidget(QWidget *parent = nullptr);
    ~GLWidget();

protected:

    void initializeGL()override;
    void paintGL()override;
    void resizeGL(int w, int h)override;




private:
    Ui::QLWidget *ui;

    QOpenGLBuffer *m_vbo, *m_cbo;
    QOpenGLVertexArrayObject *m_vao;
    QOpenGLShaderProgram *m_shader;


    float aspectRatio;

    Node *node;


};

#endif // QLWIDGET_H
