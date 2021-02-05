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
#include <QSqlQuery>
#include <QMouseEvent>

namespace Ui {
class GLChart;
}


#define SKULL1INDEX 0
#define SKULL2INDEX 1


class GLChart : public QOpenGLWidget , protected QOpenGLExtraFunctions
{
    Q_OBJECT

public:
    explicit GLChart(QWidget *parent = nullptr);
    ~GLChart();

    static void paintChart();

    void paintChartM(QOpenGLFunctions *glFunctions);
    void paintChartL(QOpenGLFunctions *glFunctions);
    void paintChartR(QOpenGLFunctions *glFunctions);
    void paintChartT(QOpenGLFunctions *glFunctions);

protected:

    void mouseMoveEvent(QMouseEvent *event)override;
    void mousePressEvent(QMouseEvent *event)override;
    void mouseReleaseEvent(QMouseEvent *event)override;
    void wheelEvent(QWheelEvent *event)override;


    void initializeGL()override;
    void resizeGL(int w, int h)override;
    void paintGL()override;


signals:
    void updatePage();

private:
    Ui::GLChart *ui;

    QVector<float> VertexAxisBuffer;
    QVector<float> VertexStaticBuffer;
    QVector<float> VertexDataBuffer;
    int vertexDataToothSize;
    int vertexLeftCondyleSize;
    int vertexRightCondyletSize;


    QOpenGLVertexArrayObject *m_vaoAxis;
    QOpenGLVertexArrayObject *m_vaoS;
    QOpenGLVertexArrayObject *m_vaoF;
    QOpenGLVertexArrayObject *m_vaoL;
    QOpenGLVertexArrayObject *m_vaoR;

    char chartFlag;

    QOpenGLBuffer *m_vboA, *m_vboS, *m_vboF, *m_vboL, *m_vboR;
    QOpenGLShaderProgram *m_shader;


    QVector3D lightPos;




    float aspectRatio;
    float scaleFactor;

    float scaleFactorX=1;
    float scaleFactorY=1;
    float scaleFactorZ=1;

    float offsetXF=0;
    float offsetYF=0;
    float offsetZF=0;

    float offsetXL=0;
    float offsetYL=0;
    float offsetZL=0;

    float offsetXR=0;
    float offsetYR=0;
    float offsetZR=0;


    float oldOffsetXF=0;
    float oldOffsetYF=0;
    float oldOffsetZF=0;

    float oldOffsetXL=0;
    float oldOffsetYL=0;
    float oldOffsetZL=0;

    float oldOffsetXR=0;
    float oldOffsetYR=0;
    float oldOffsetZR=0;

    bool pressed = false;
    int pressedX;
    int pressedY;

    QWidget *parent;

    bool start=true;


public slots:

    void on_vertexDataChanged(QString  step, QVector<float> vertexTooth, QVector<float> vertexLeftCondyle, QVector<float> vertexRightCondyle);

};

#endif // QLWIDGET_H
