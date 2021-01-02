#ifndef QLWIDGET_H
#define QLWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLExtraFunctions>
#include <QOpenGLFunctions_3_3_Core>
#include <QOpenGLShader>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <QBasicTimer>

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

    void mousePressEvent(QMouseEvent *e) override;
    void mouseReleaseEvent(QMouseEvent *e) override;
    void timerEvent(QTimerEvent *e) override;

    void initializeGL()override;
    void paintGL()override;
    void resizeGL(int w, int h)override;
private:
    QOpenGLBuffer *m_vbo;             // 存储点数据
    QOpenGLBuffer *m_cbo;             // 存储颜色数据
    QOpenGLVertexArrayObject *m_vao;  // VAO对象
    QOpenGLShaderProgram *m_shader;   // 渲染器程序对象



private:
    Ui::QLWidget *ui;

    unsigned int ID;
    QOpenGLFunctions *glFunction;
    float aspectRatio;

    QBasicTimer timer;
    QMatrix4x4 projection;
    QVector2D mousePressPosition;
    QVector3D rotationAxis;
    qreal angularSpeed = 0;
    QQuaternion rotation;
};

#endif // QLWIDGET_H
