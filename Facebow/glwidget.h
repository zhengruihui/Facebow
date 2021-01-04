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

    void computeNormalVectors(size_t num_vertices);



    void initializeGL()override;
    void paintGL()override;
    void resizeGL(int w, int h)override;




private:
    Ui::QLWidget *ui;

    QOpenGLBuffer *m_vbo, *m_cbo, *m_uvbo;
    QOpenGLVertexArrayObject *m_vao;
    QOpenGLShaderProgram *m_shader;
    QOpenGLTexture *m_texture;

    float aspectRatio;
    GLfloat normalBuffer[4 * 3 *3];
    GLfloat vertexData[4 * 3 * 3];
    GLfloat uvData[4 * 3 * 2];
    QVector3D camera_pos, light_pos;


};

#endif // QLWIDGET_H
