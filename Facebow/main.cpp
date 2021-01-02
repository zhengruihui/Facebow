#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
<<<<<<< HEAD
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
=======
    QApplication app(argc, argv);

    QSurfaceFormat format;
    format.setDepthBufferSize(24);
    QSurfaceFormat::setDefaultFormat(format);

    app.setApplicationName("Facebow");
    app.setApplicationVersion("0.1");

    MainWidget widget;
    widget.show();

    return app.exec();
>>>>>>> parent of 88bafca... 搭建好跨平台opengl
}
