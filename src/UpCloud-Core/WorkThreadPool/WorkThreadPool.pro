#-------------------------------------------------
#
# Project created by QtCreator 2016-03-17T10:15:31
#
#-------------------------------------------------
QT       += core
QT       -= gui

TARGET = WorkThreadPool
TEMPLATE = lib

DEFINES += WORKTHREADPOOL_LIBRARY

SOURCES += \
    core/workthread.cpp \
    core/workthreadmanager.cpp

HEADERS += workthreadpool.h\
        workthreadpool_global.h \
    core/workthread.h \
    core/workthreadmanager.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
