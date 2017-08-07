#-------------------------------------------------
#
#   上云科技中心服务器的服务--任务调度中心
#
#   版权:  C/C++ development team
#   时间:       2015-07-28 18:09:06
#
#-------------------------------------------------
QT       += sql core network
QT       -= gui

TARGET = NetIServerLib
TEMPLATE = lib

DEFINES += NETISERVERLIB_LIBRARY

SOURCES += \
    bridge/bridgeservermanager.cpp \
    servertaskscheduler.cpp

HEADERS +=\
        netiserverlib_global.h \
    bridge/bridgeservermanager.h \
    servertaskscheduler.h

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


win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../TimerIServerLib/release/ -lTimerIServerLib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../TimerIServerLib/debug/ -lTimerIServerLib
else:unix: LIBS += -L$$OUT_PWD/../TimerIServerLib/ -lTimerIServerLib

INCLUDEPATH += $$PWD/../TimerIServerLib
DEPENDPATH += $$PWD/../TimerIServerLib



win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../DuplexLib/release/ -lDuplexLib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../DuplexLib/debug/ -lDuplexLib
else:unix: LIBS += -L$$OUT_PWD/../DuplexLib/ -lDuplexLib

INCLUDEPATH += $$PWD/../DuplexLib
DEPENDPATH += $$PWD/../DuplexLib

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../UpCloud-Core/EnDecryptLib/release/ -lEnDecryptLib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../UpCloud-Core/EnDecryptLib/debug/ -lEnDecryptLib
else:unix: LIBS += -L$$OUT_PWD/../../UpCloud-Core/EnDecryptLib/ -lEnDecryptLib

INCLUDEPATH += $$PWD/../../UpCloud-Core/EnDecryptLib
DEPENDPATH += $$PWD/../../UpCloud-Core/EnDecryptLib

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../UpCloud-Core/DatabaseLib/release/ -lDatabaseLib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../UpCloud-Core/DatabaseLib/debug/ -lDatabaseLib
else:unix: LIBS += -L$$OUT_PWD/../../UpCloud-Core/DatabaseLib/ -lDatabaseLib

INCLUDEPATH += $$PWD/../../UpCloud-Core/DatabaseLib
DEPENDPATH += $$PWD/../../UpCloud-Core/DatabaseLib



win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../BaseIServerLib/release/ -lBaseIServerLib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../BaseIServerLib/debug/ -lBaseIServerLib
else:unix: LIBS += -L$$OUT_PWD/../BaseIServerLib/ -lBaseIServerLib

INCLUDEPATH += $$PWD/../BaseIServerLib
DEPENDPATH += $$PWD/../BaseIServerLib

#win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../UpCloud-Core/ERMLib/release/ -lERMLib
#else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../UpCloud-Core/ERMLib/debug/ -lERMLib
#else:unix: LIBS += -L$$OUT_PWD/../../UpCloud-Core/ERMLib/ -lERMLib

INCLUDEPATH += $$PWD/../../UpCloud-Core/ERMLib
#DEPENDPATH += $$PWD/../../UpCloud-Core/ERMLib
