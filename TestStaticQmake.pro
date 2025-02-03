QT       += core gui multimedia
## remove
QMAKE_LIBS += -ltiff -ljpeg -ljbig -ldeflate -lzstd -llerc -llzma -lgraphite2 -lbz2 -lusp10 -lRpcrt4 -lsharpyuv

#explicit -lmng.dll
#tempremove -ltiff -ljpeg -ljbig -ldeflate -lzstd -llerc -llzma -lgraphite2 -lbz2 -lusp10 -lRpcrt4 -lsharpyuv

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17 static

QMAKE_CXXFLAGS += -Os
QMAKE_CFLAGS += -Os

QMAKE_CXXFLAGS += -fno-rtti -fno-exceptions

CONFIG += release
CONFIG -= debug

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mytrainer.cpp

HEADERS += \
    config.h \
    mytrainer.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
