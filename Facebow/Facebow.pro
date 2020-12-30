QT       += core gui widgets

TARGET = Facebow
TEMPLATE = app

SOURCES += main.cpp

SOURCES += \
    mainwidget.cpp

HEADERS += \
    mainwidget.h




win32{
    DEFINES += WINDOWS
    LIBS += -lOpengl32 -lglu32
}
unix{
    LIBS += -framework opengl -framework glut
}

