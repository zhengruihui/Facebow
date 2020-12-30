#ifndef MAINWIDGET_H
#define MAINWIDGET_H


#include <QOpenGLWidget>


class GLWidget : public QOpenGLWidget
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
