#-------------------------------------------------
#
#   上云科技应用支撑封装--定时操作任务封装
#
#   版权:  C/C++ development team
#   时间:       2015-07-14 14:27:06
#   注意:
#-----
#   功能:
#-----
#-------------------------------------------------
QT       += core network
QT       -= gui

TARGET = TimerLib
TEMPLATE = lib

DEFINES += TIMERLIB_LIBRARY

SOURCES += exector/core/exector.cpp \
    timer/core/timercontroller.cpp \
    exector/abstractexector.cpp \
    context/pushcontext.cpp \
    timer/registry/timerregistryfactory.cpp \
    timer/timerthread.cpp

HEADERS +=  timerlib_global.h \
    exector/core/exector.h \
    timer/core/timercontroller.h \
    exector/abstractexector.h \
    context/pushcontext.h \
    timer.h \
    timer/registry/timerregistryfactory.h \
    timer/timerthread.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../BaseLib/release/ -lBaseLib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../BaseLib/debug/ -lBaseLib
else:unix: LIBS += -L$$OUT_PWD/../BaseLib/ -lBaseLib

INCLUDEPATH += $$PWD/../BaseLib
DEPENDPATH += $$PWD/../BaseLib

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../TransMsgLib/release/ -lTransMsgLib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../TransMsgLib/debug/ -lTransMsgLib
else:unix: LIBS += -L$$OUT_PWD/../TransMsgLib/ -lTransMsgLib

INCLUDEPATH += $$PWD/../TransMsgLib
DEPENDPATH += $$PWD/../TransMsgLib
