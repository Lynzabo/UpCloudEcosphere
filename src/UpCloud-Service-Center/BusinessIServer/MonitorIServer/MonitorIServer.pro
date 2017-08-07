#-------------------------------------------------
#
# Project created by QtCreator 2015-09-18T09:29:44
#
#-------------------------------------------------

QT       -= gui

TARGET = MonitorIServer
TEMPLATE = lib

DEFINES += MONITORISERVER_LIBRARY

SOURCES += monitoriserver.cpp

HEADERS += monitoriserver.h\
        monitoriserver_global.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
