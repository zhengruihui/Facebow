QT += core
QT += quick quick3d
QT += serialport

target.path = $$[QT_INSTALL_EXAMPLES]/quick3d/Facebow

TRANSLATIONS += \
    Language\English.ts \
    Language\ChineseSimpilifed.ts \
    Language\ChineseTraditional.ts \
    Language\German.ts \

INSTALLS += target

SOURCES += \
    SerialPort/serialport.cpp \
    main.cpp

RESOURCES += \
    Image.qrc \
    Language.qrc \
    Mesh.qrc \
    Qml.qrc

HEADERS += \
    SerialPort/serialport.h

DISTFILES +=
