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
    QOpenGLBuffer *m_vbo;             // 存储点数据
    QOpenGLBuffer *m_cbo;             // 存储颜色数据
    QOpenGLBuffer *m_uvbo;             // 存储纹理坐标

    QOpenGLVertexArrayObject *m_vao;  // VAO对象
    QOpenGLShaderProgram *m_shader;   // 渲染器程序对象
    QOpenGLTexture *m_texture;


private:
    Ui::QLWidget *ui;

    unsigned int ID;
    QOpenGLFunctions *glFunction;
    float aspectRatio;


};

#endif // QLWIDGET_H
