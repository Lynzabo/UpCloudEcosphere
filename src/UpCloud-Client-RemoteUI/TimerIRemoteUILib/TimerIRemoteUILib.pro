#-------------------------------------------------
#
#   上云科技远程UI的服务--定时执行服务
#
#   版权:  C/C++ development team
#   时间:       2015-07-28 18:09:06
#
#-------------------------------------------------

QT       += core network
QT       -= gui

TARGET = TimerIRemoteUILib
TEMPLATE = lib

DEFINES += TIMERIREMOTEUILIB_LIBRARY
SOURCES += \
    rutimercontroller.cpp

HEADERS +=\
        timeriremoteuilib_global.h \
    rutimercontroller.h \
    timeriremoteui.h

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



win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../BaseIRemoteLib/release/ -lBaseIRemoteLib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../BaseIRemoteLib/debug/ -lBaseIRemoteLib
else:unix: LIBS += -L$$OUT_PWD/../BaseIRemoteLib/ -lBaseIRemoteLib

INCLUDEPATH += $$PWD/../BaseIRemoteLib
DEPENDPATH += $$PWD/../BaseIRemoteLib

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../UpCloud-Core/TransMsgLib/release/ -lTransMsgLib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../UpCloud-Core/TransMsgLib/debug/ -lTransMsgLib
else:unix: LIBS += -L$$OUT_PWD/../../UpCloud-Core/TransMsgLib/ -lTransMsgLib

INCLUDEPATH += $$PWD/../../UpCloud-Core/TransMsgLib
DEPENDPATH += $$PWD/../../UpCloud-Core/TransMsgLib


win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../UpCloud-Core/TimerLib/release/ -lTimerLib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../UpCloud-Core/TimerLib/debug/ -lTimerLib
else:unix: LIBS += -L$$OUT_PWD/../../UpCloud-Core/TimerLib/ -lTimerLib

INCLUDEPATH += $$PWD/../../UpCloud-Core/TimerLib
DEPENDPATH += $$PWD/../../UpCloud-Core/TimerLib

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../UpCloud-Core/WorkThreadPool/release/ -lWorkThreadPool
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../UpCloud-Core/WorkThreadPool/debug/ -lWorkThreadPool
else:unix: LIBS += -L$$OUT_PWD/../../UpCloud-Core/WorkThreadPool/ -lWorkThreadPool

INCLUDEPATH += $$PWD/../../UpCloud-Core/WorkThreadPool
DEPENDPATH += $$PWD/../../UpCloud-Core/WorkThreadPool
