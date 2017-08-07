#-------------------------------------------------
#
# Project created by QtCreator 2015-09-01T15:21:59
#
#-------------------------------------------------
QT      += core network sql
QT       -= gui

TARGET = UnstructIServerLib
TEMPLATE = lib

DEFINES += UNSTRUCTISERVERLIB_LIBRARY

SOURCES += \
    bean/csrunstructtask.cpp \
    bean/csrusendstatus.cpp \
    bean/csrusendfiles.cpp \
    bean/csrusendaddr.cpp \
    dao/csunstructdao.cpp \
    centerunstructexector.cpp

HEADERS +=\
        unstructiserverlib_global.h \
    bean/csrunstructtask.h \
    bean/csrusendstatus.h \
    bean/csrusendfiles.h \
    bean/csrusendaddr.h \
    dao/csunstructdao.h \
    centerunstructexector.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../../UpCloud-Core/BaseLib/release/ -lBaseLib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../../UpCloud-Core/BaseLib/debug/ -lBaseLib
else:unix: LIBS += -L$$OUT_PWD/../../../UpCloud-Core/BaseLib/ -lBaseLib

INCLUDEPATH += $$PWD/../../../UpCloud-Core/BaseLib
DEPENDPATH += $$PWD/../../../UpCloud-Core/BaseLib

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../../UpCloud-Core/TimerLib/release/ -lTimerLib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../../UpCloud-Core/TimerLib/debug/ -lTimerLib
else:unix: LIBS += -L$$OUT_PWD/../../../UpCloud-Core/TimerLib/ -lTimerLib

INCLUDEPATH += $$PWD/../../../UpCloud-Core/TimerLib
DEPENDPATH += $$PWD/../../../UpCloud-Core/TimerLib

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../../UpCloud-Core/DatabaseLib/release/ -lDatabaseLib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../../UpCloud-Core/DatabaseLib/debug/ -lDatabaseLib
else:unix: LIBS += -L$$OUT_PWD/../../../UpCloud-Core/DatabaseLib/ -lDatabaseLib

INCLUDEPATH += $$PWD/../../../UpCloud-Core/DatabaseLib
DEPENDPATH += $$PWD/../../../UpCloud-Core/DatabaseLib

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../../UpCloud-Core/TransMsgLib/release/ -lTransMsgLib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../../UpCloud-Core/TransMsgLib/debug/ -lTransMsgLib
else:unix: LIBS += -L$$OUT_PWD/../../../UpCloud-Core/TransMsgLib/ -lTransMsgLib

INCLUDEPATH += $$PWD/../../../UpCloud-Core/TransMsgLib
DEPENDPATH += $$PWD/../../../UpCloud-Core/TransMsgLib
