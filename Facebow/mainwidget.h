#ifndef MAINWIDGET_H
#define MAINWIDGET_H


#include <QOpenGLWidget>


class MainWidget : public QOpenGLWidget
{
    Q_OBJECT

public:
    using QOpenGLWidget::QOpenGLWidget;
    ~MainWidget();

protected:


    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;


private:

};

#endif // MAINWIDGET_H
