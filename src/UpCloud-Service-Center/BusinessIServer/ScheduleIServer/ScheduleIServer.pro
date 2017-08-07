#-------------------------------------------------
#
# Project created by QtCreator 2015-09-18T09:29:07
#
#-------------------------------------------------

QT       += core network sql
QT       -= gui

TARGET = ScheduleIServer
TEMPLATE = lib

DEFINES += SCHEDULEISERVER_LIBRARY

SOURCES += \
    bean/csrscsendaddr.cpp \
    bean/csrscsendfiles.cpp \
    bean/csrscsendstatus.cpp \
    bean/csrsctask.cpp \
    bean/cssscsendaddr.cpp \
    bean/cssscsendfiles.cpp \
    bean/csssctask.cpp \
    dao/csscheduledao.cpp \
    cscexector.cpp \
    crsctaskdownloadrequest.cpp \
    crsctaskdownstatusrequest.cpp \
    crsctaskparsestatusrequest.cpp \
    bean/vcsascsendfiles.cpp

HEADERS += scheduleiserver.h\
        scheduleiserver_global.h \
    bean/csrscsendaddr.h \
    bean/csrscsendfiles.h \
    bean/csrscsendstatus.h \
    bean/csrsctask.h \
    bean/cssscsendaddr.h \
    bean/cssscsendfiles.h \
    bean/csssctask.h \
    dao/csscheduledao.h \
    cscexector.h \
    crsctaskdownloadrequest.h \
    crsctaskdownstatusrequest.h \
    crsctaskparsestatusrequest.h \
    bean/vcsascsendfiles.h

unix {
    CONFIG += c++11
    target.path = /usr/lib
    INSTALLS += target
}

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../../UpCloud-Core/BaseLib/release/ -lBaseLib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../../UpCloud-Core/BaseLib/debug/ -lBaseLib
else:unix: LIBS += -L$$OUT_PWD/../../../UpCloud-Core/BaseLib/ -lBaseLib

INCLUDEPATH += $$PWD/../../../UpCloud-Core/BaseLib
DEPENDPATH += $$PWD/../../../UpCloud-Core/BaseLib

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

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../../UpCloud-Core/TimerLib/release/ -lTimerLib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../../UpCloud-Core/TimerLib/debug/ -lTimerLib
else:unix: LIBS += -L$$OUT_PWD/../../../UpCloud-Core/TimerLib/ -lTimerLib

INCLUDEPATH += $$PWD/../../../UpCloud-Core/TimerLib
DEPENDPATH += $$PWD/../../../UpCloud-Core/TimerLib

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../../UpCloud-Core/ActionLib/release/ -lActionLib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../../UpCloud-Core/ActionLib/debug/ -lActionLib
else:unix: LIBS += -L$$OUT_PWD/../../../UpCloud-Core/ActionLib/ -lActionLib

INCLUDEPATH += $$PWD/../../../UpCloud-Core/ActionLib
DEPENDPATH += $$PWD/../../../UpCloud-Core/ActionLib

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../../UpCloud-Core/ERMLib/release/ -lERMLib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../../UpCloud-Core/ERMLib/debug/ -lERMLib
else:unix: LIBS += -L$$OUT_PWD/../../../UpCloud-Core/ERMLib/ -lERMLib

INCLUDEPATH += $$PWD/../../../UpCloud-Core/ERMLib
DEPENDPATH += $$PWD/../../../UpCloud-Core/ERMLib

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../../UpCloud-Core/AvroLib/release/ -lAvroLib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../../UpCloud-Core/AvroLib/debug/ -lAvroLib
else:unix: LIBS += -L$$OUT_PWD/../../../UpCloud-Core/AvroLib/ -lAvroLib

INCLUDEPATH += $$PWD/../../../UpCloud-Core/AvroLib
DEPENDPATH += $$PWD/../../../UpCloud-Core/AvroLib

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../BaseIServerLib/release/ -lBaseIServerLib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../BaseIServerLib/debug/ -lBaseIServerLib
else:unix: LIBS += -L$$OUT_PWD/../../BaseIServerLib/ -lBaseIServerLib

INCLUDEPATH += $$PWD/../../BaseIServerLib
DEPENDPATH += $$PWD/../../BaseIServerLib
