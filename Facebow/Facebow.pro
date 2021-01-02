QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    glwidget.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
<<<<<<< HEAD
    glwidget.h \
    mainwindow.h
=======
    mainwidget.h

RESOURCES += \
    shaders.qrc \
    textures.qrc

# install
target.path = $$[QT_INSTALL_EXAMPLES]/opengl/cube
INSTALLS += target
>>>>>>> parent of 88bafca... 搭建好跨平台opengl

FORMS += \
    glwidget.ui \
    mainwindow.ui

<<<<<<< HEAD
# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
=======
win32:LIBS += -lOpengl32 \
              -lglu32

unix:LIBS += -lglut -lGLU
>>>>>>> parent of 88bafca... 搭建好跨平台opengl

RESOURCES += \
    Image.qrc
