#ifndef MAINWIDGET_H
#define MAINWIDGET_H


#include <QOpenGLWidget>
#include <QOpenGLExtraFunctions>
#include <QOpenGLFunctions_3_3_Core>
#include <QOpenGLShader>
#include <QOpenGLShaderProgram>



class GLWidget : public QOpenGLWidget , protected QOpenGLExtraFunctions
{
    Q_OBJECT

public:
    using QOpenGLWidget::QOpenGLWidget;
    ~GLWidget();

protected:


    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;


private:

};

#endif // MAINWIDGET_H
