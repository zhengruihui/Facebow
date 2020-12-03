QT += quick quick3d
QT += serialport

target.path = $$[QT_INSTALL_EXAMPLES]/quick3d/Facebow

INSTALLS += target

SOURCES += \
    SerialPort/serialport.cpp \
    main.cpp

RESOURCES += \
    Image.qrc \
    mesh.qrc \
    qml.qrc

OTHER_FILES += \
    doc/src/*.*

HEADERS += \
    SerialPort/serialport.h
