QT       += core gui serialport sql charts #quickwidgets


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

TRANSLATIONS += \
    Language\English.ts \
    Language\ChineseSimpilifed.ts \
    Language\ChineseTraditional.ts \
    Language\German.ts \

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    3D/glwidget.cpp \
    3D/node.cpp \
    Database/database.cpp \
    SerialPort/CRC16.c \
    SerialPort/serialport.cpp \
    UI/Button/button.cpp \
    UI/Page/Chart/glchart.cpp \
    UI/Page/Chart/painter.cpp \
    UI/Page/Dialog/dialoginfo.cpp \
    UI/Page/ImageWidget/imagewidget.cpp \
    UI/Page/PatientItem/patientitem.cpp \
    UI/Page/pageinfo.cpp \
    UI/Page/pagemeasure.cpp \
    UI/Page/pagetrack.cpp \
    devicesystem.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    3D/glwidget.h \
    3D/node.h \
    DLL/Get_LeftCondyle_StaticCoord/Get_LeftCondyle_StaticCoord.h \
    DLL/Get_rightCondyle_StaticCoord/Get_RightCondyle_StaticCoord.h \
    DLL/MoveForward_Process/MoveForward_Process.h \
    DLL/MoveLeft_Process/MoveLeft_Process.h \
    DLL/MoveProcess/MoveProcess.h \
    DLL/MoveRight_Process/MoveRight_Process.h \
    DLL/OpenClosed_Process/OpenClosed_Process.h \
    DLL/Tooth_Coronal/Tooth_Coronal.h \
    DLL/Tooth_Horizontal/Tooth_Horizontal.h \
    DLL/Tooth_Sagittal/Tooth_Sagittal.h \
    Database/database.h \
    SerialPort/CRC16.h \
    SerialPort/serialport.h \
    UI/Button/button.h \
    UI/Page/Chart/glchart.h \
    UI/Page/Chart/painter.h \
    UI/Page/Dialog/dialoginfo.h \
    UI/Page/ImageWidget/imagewidget.h \
    UI/Page/PatientItem/patientitem.h \
    UI/Page/pageinfo.h \
    UI/Page/pagemeasure.h \
    UI/Page/pagetrack.h \
    devicesystem.h \
    mainwindow.h

FORMS += \
    3D/glwidget.ui \
    UI/Button/button.ui \
    UI/Page/Chart/glchart.ui \
    UI/Page/Chart/painter.ui \
    UI/Page/Dialog/dialoginfo.ui \
    UI/Page/ImageWidget/imagewidget.ui \
    UI/Page/PatientItem/patientitem.ui \
    UI/Page/pageinfo.ui \
    UI/Page/pagemeasure.ui \
    UI/Page/pagetrack.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Image.qrc \
    Language.qrc \
    Mesh.qrc \
    Model.qrc \
    Qml.qrc \
    Shader.qrc \
    Texture.qrc


unix|win32: LIBS += -L$$PWD/DLL/Get_LeftCondyle_StaticCoord/ -lGet_LeftCondyle_StaticCoord

INCLUDEPATH += $$PWD/DLL/Get_LeftCondyle_StaticCoord
DEPENDPATH += $$PWD/DLL/Get_LeftCondyle_StaticCoord

unix|win32: LIBS += -L$$PWD/DLL/Get_rightCondyle_StaticCoord/ -lGet_RightCondyle_StaticCoord

INCLUDEPATH += $$PWD/DLL/Get_rightCondyle_StaticCoord
DEPENDPATH += $$PWD/DLL/Get_rightCondyle_StaticCoord

unix|win32: LIBS += -L$$PWD/DLL/MoveForward_Process/ -lMoveForward_Process

INCLUDEPATH += $$PWD/DLL/MoveForward_Process
DEPENDPATH += $$PWD/DLL/MoveForward_Process

unix|win32: LIBS += -L$$PWD/DLL/MoveLeft_Process/ -lMoveLeft_Process

INCLUDEPATH += $$PWD/DLL/MoveLeft_Process
DEPENDPATH += $$PWD/DLL/MoveLeft_Process

unix|win32: LIBS += -L$$PWD/DLL/MoveProcess/ -lMoveProcess

INCLUDEPATH += $$PWD/DLL/MoveProcess
DEPENDPATH += $$PWD/DLL/MoveProcess

unix|win32: LIBS += -L$$PWD/DLL/MoveRight_Process/ -lMoveRight_Process

INCLUDEPATH += $$PWD/DLL/MoveRight_Process
DEPENDPATH += $$PWD/DLL/MoveRight_Process

unix|win32: LIBS += -L$$PWD/DLL/OpenClosed_Process/ -lOpenClosed_Process

INCLUDEPATH += $$PWD/DLL/OpenClosed_Process
DEPENDPATH += $$PWD/DLL/OpenClosed_Process

unix|win32: LIBS += -L$$PWD/DLL/Tooth_Coronal/ -lTooth_Coronal

INCLUDEPATH += $$PWD/DLL/Tooth_Coronal
DEPENDPATH += $$PWD/DLL/Tooth_Coronal

unix|win32: LIBS += -L$$PWD/DLL/Tooth_Horizontal/ -lTooth_Horizontal

INCLUDEPATH += $$PWD/DLL/Tooth_Horizontal
DEPENDPATH += $$PWD/DLL/Tooth_Horizontal

unix|win32: LIBS += -L$$PWD/DLL/Tooth_Sagittal/ -lTooth_Sagittal

INCLUDEPATH += $$PWD/DLL/Tooth_Sagittal
DEPENDPATH += $$PWD/DLL/Tooth_Sagittal
