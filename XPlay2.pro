QT       += core gui opengl openglextensions multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += console c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    XAudioPlay.cpp \
    XAudioThread.cpp \
    XDecode.cpp \
    XDemux.cpp \
    XResample.cpp \
    XVideoWidget.cpp \
    main.cpp \
    XPlay2.cpp

HEADERS += \
    XAudioPlay.h \
    XAudioThread.h \
    XDecode.h \
    XDemux.h \
    XPlay2.h \
    XResample.h \
    XVideoWidget.h

FORMS += \
    XPlay2.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

INCLUDEPATH += $$PWD/../../include


#区分32位和64位windows程序
opt = $$find(QMAKESPEC,"msvc2015_64")
isEmpty(opt){
message("win32 lib")
LIBS += -L$$PWD/../../lib/win32
}
!isEmpty(opt){
message("win64 lib")
LIBS += -L$$PWD/../../lib/win64
}
