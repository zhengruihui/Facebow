QT       += core gui serialport sql


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    3D/glwidget.cpp \
    3D/node.cpp \
    Database/database.cpp \
    SerialPort/serialport.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    3D/glwidget.h \
    3D/node.h \
    Database/database.h \
    SerialPort/serialport.h \
    mainwindow.h

FORMS += \
    3D/glwidget.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Image.qrc \
    Model.qrc \
    Shader.qrc \
    Texture.qrc

