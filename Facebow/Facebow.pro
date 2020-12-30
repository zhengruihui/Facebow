QT       += core gui widgets

TARGET = Facebow
TEMPLATE = app

SOURCES += main.cpp

SOURCES += \
    mainwidget.cpp

HEADERS += \
    mainwidget.h

RESOURCES += \
    shaders.qrc \
    textures.qrc

# install
target.path = $$[QT_INSTALL_EXAMPLES]/opengl/cube
INSTALLS += target


win32:LIBS += -lOpengl32 \
              -lglu32

unix:LIBS += -lglut -lGLU

