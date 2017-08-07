#-------------------------------------------------
#
#   上云科技节点服务器的服务--任务调度中心
#
#   版权:  C/C++ development team
#   时间:       2015-07-28 18:09:06
#
#-------------------------------------------------
QT       += core network
QT       -= gui

TARGET = NetIClientLib
TEMPLATE = lib

DEFINES += NETICLIENTLIB_LIBRARY

SOURCES += \
    bridge/bridgeclientmanager.cpp \
    clienttaskscheduler.cpp

HEADERS += neticlientlib_global.h \
    bridge/bridgeclientmanager.h \
    clienttaskscheduler.h

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

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../UpCloud-Core/NetLib/release/ -lNetLib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../UpCloud-Core/NetLib/debug/ -lNetLib
else:unix: LIBS += -L$$OUT_PWD/../../UpCloud-Core/NetLib/ -lNetLib

INCLUDEPATH += $$PWD/../../UpCloud-Core/NetLib
DEPENDPATH += $$PWD/../../UpCloud-Core/NetLib

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../UpCloud-Core/TransMsgLib/release/ -lTransMsgLib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../UpCloud-Core/TransMsgLib/debug/ -lTransMsgLib
else:unix: LIBS += -L$$OUT_PWD/../../UpCloud-Core/TransMsgLib/ -lTransMsgLib

INCLUDEPATH += $$PWD/../../UpCloud-Core/TransMsgLib
DEPENDPATH += $$PWD/../../UpCloud-Core/TransMsgLib

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../UpCloud-Core/ActionLib/release/ -lActionLib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../UpCloud-Core/ActionLib/debug/ -lActionLib
else:unix: LIBS += -L$$OUT_PWD/../../UpCloud-Core/ActionLib/ -lActionLib

INCLUDEPATH += $$PWD/../../UpCloud-Core/ActionLib
DEPENDPATH += $$PWD/../../UpCloud-Core/ActionLib

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../UpCloud-Core/TimerLib/release/ -lTimerLib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../UpCloud-Core/TimerLib/debug/ -lTimerLib
else:unix: LIBS += -L$$OUT_PWD/../../UpCloud-Core/TimerLib/ -lTimerLib

INCLUDEPATH += $$PWD/../../UpCloud-Core/TimerLib
DEPENDPATH += $$PWD/../../UpCloud-Core/TimerLib


win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../TimerIClientLib/release/ -lTimerIClientLib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../TimerIClientLib/debug/ -lTimerIClientLib
else:unix: LIBS += -L$$OUT_PWD/../TimerIClientLib/ -lTimerIClientLib

INCLUDEPATH += $$PWD/../TimerIClientLib
DEPENDPATH += $$PWD/../TimerIClientLib

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../BaseIClientLib/release/ -lBaseIClientLib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../BaseIClientLib/debug/ -lBaseIClientLib
else:unix: LIBS += -L$$OUT_PWD/../BaseIClientLib/ -lBaseIClientLib

INCLUDEPATH += $$PWD/../BaseIClientLib
DEPENDPATH += $$PWD/../BaseIClientLib

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../UpCloud-Core/EnDecryptLib/release/ -lEnDecryptLib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../UpCloud-Core/EnDecryptLib/debug/ -lEnDecryptLib
else:unix: LIBS += -L$$OUT_PWD/../../UpCloud-Core/EnDecryptLib/ -lEnDecryptLib

INCLUDEPATH += $$PWD/../../UpCloud-Core/EnDecryptLib
DEPENDPATH += $$PWD/../../UpCloud-Core/EnDecryptLib
