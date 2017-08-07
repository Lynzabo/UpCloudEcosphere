#-------------------------------------------------
#
# Project created by QtCreator 2015-12-18T18:33:09
#
#-------------------------------------------------

QT       -= gui

TARGET = SerialComm
TEMPLATE = lib

DEFINES += SERIALCOMM_LIBRARY

SOURCES += serialcomm.cpp

HEADERS += serialcomm.h\
        serialcomm_global.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
