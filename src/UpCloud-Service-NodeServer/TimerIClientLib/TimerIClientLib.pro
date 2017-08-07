#-------------------------------------------------
#
#   上云科技节点服务器的服务--定时执行服务
#
#   版权:  C/C++ development team
#   时间:       2015-07-28 18:09:06
#
#-------------------------------------------------
QT       += core network
QT       -= gui

TARGET = TimerIClientLib
TEMPLATE = lib

DEFINES += TIMERICLIENTLIB_LIBRARY

SOURCES += \
    nstimercontroller.cpp

HEADERS +=\
        timericlientlib_global.h \
    nstimercontroller.h \
    timericlient.h

unix {
    CONFIG += c++11
    target.path = /usr/lib
    INSTALLS += target
}

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../UpCloud-Core/BaseLib/release/ -lBaseLib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../UpCloud-Core/BaseLib/debug/ -lBaseLib
else:unix: LIBS += -L$$OUT_PWD/../../UpCloud-Core/BaseLib/ -lBaseLib

INCLUDEPATH += $$PWD/../../UpCloud-Core/BaseLib
DEPENDPATH += $$PWD/../../UpCloud-Core/BaseLib

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../UpCloud-Core/TimerLib/release/ -lTimerLib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../UpCloud-Core/TimerLib/debug/ -lTimerLib
else:unix: LIBS += -L$$OUT_PWD/../../UpCloud-Core/TimerLib/ -lTimerLib

INCLUDEPATH += $$PWD/../../UpCloud-Core/TimerLib
DEPENDPATH += $$PWD/../../UpCloud-Core/TimerLib

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../UpCloud-Core/TransMsgLib/release/ -lTransMsgLib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../UpCloud-Core/TransMsgLib/debug/ -lTransMsgLib
else:unix: LIBS += -L$$OUT_PWD/../../UpCloud-Core/TransMsgLib/ -lTransMsgLib

INCLUDEPATH += $$PWD/../../UpCloud-Core/TransMsgLib
DEPENDPATH += $$PWD/../../UpCloud-Core/TransMsgLib



win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../BaseIClientLib/release/ -lBaseIClientLib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../BaseIClientLib/debug/ -lBaseIClientLib
else:unix: LIBS += -L$$OUT_PWD/../BaseIClientLib/ -lBaseIClientLib

INCLUDEPATH += $$PWD/../BaseIClientLib
DEPENDPATH += $$PWD/../BaseIClientLib
