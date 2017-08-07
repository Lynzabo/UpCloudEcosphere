#-------------------------------------------------
#
# Project created by QtCreator 2015-09-18T09:38:14
#
#-------------------------------------------------

QT       -= gui

TARGET = OperaIClient
TEMPLATE = lib

DEFINES += OPERAICLIENT_LIBRARY

SOURCES += operaiclient.cpp

HEADERS += operaiclient.h\
        operaiclient_global.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
