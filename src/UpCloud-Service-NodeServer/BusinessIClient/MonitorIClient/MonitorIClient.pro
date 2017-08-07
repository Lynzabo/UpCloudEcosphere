#-------------------------------------------------
#
# Project created by QtCreator 2015-09-18T09:38:55
#
#-------------------------------------------------

QT       -= gui

TARGET = MonitorIClient
TEMPLATE = lib

DEFINES += MONITORICLIENT_LIBRARY

SOURCES += monitoriclient.cpp

HEADERS += monitoriclient.h\
        monitoriclient_global.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
