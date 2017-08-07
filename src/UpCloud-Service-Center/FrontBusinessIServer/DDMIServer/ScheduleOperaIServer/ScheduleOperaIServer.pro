#-------------------------------------------------
#
# Project created by QtCreator 2016-01-21T10:18:37
#
#-------------------------------------------------
QT       += core network sql
QT       -= gui

TARGET = ScheduleOperaIServer
TEMPLATE = lib

DEFINES += SCHEDULEOPERAISERVER_LIBRARY

SOURCES += scheduleoperaiserver.cpp \
    util/scheduleutil.cpp \
    ../../../BusinessIServer/ScheduleIServer/bean/csrscsendaddr.cpp \
    ../../../BusinessIServer/ScheduleIServer/bean/csrscsendfiles.cpp \
    ../../../BusinessIServer/ScheduleIServer/bean/csrscsendstatus.cpp \
    ../../../BusinessIServer/ScheduleIServer/bean/csrsctask.cpp \
    ../../../BusinessIServer/ScheduleIServer/bean/cssscsendaddr.cpp \
    ../../../BusinessIServer/ScheduleIServer/bean/cssscsendfiles.cpp \
    ../../../BusinessIServer/ScheduleIServer/bean/csssctask.cpp \
    ../../../BusinessIServer/ScheduleIServer/dao/csscheduledao.cpp \
    lstaskservlet.cpp \
    ustaskservlet.cpp \
    istaskservlet.cpp \
    lsaddrservlet.cpp \
    ../../../BusinessIServer/ScheduleIServer/bean/vcsascsendfiles.cpp \
    lvscfilesservlet.cpp \
    ustaskaddrservlet.cpp \
    dstaskservlet.cpp \
    dstaskaddrservlet.cpp \
    astaskaddrservlet.cpp \
    dstaskfilesservlet.cpp

HEADERS += scheduleoperaiserver.h\
        scheduleoperaiserver_global.h \
    util/scheduleutil.h \
    ../../../BusinessIServer/ScheduleIServer/bean/csrscsendaddr.h \
    ../../../BusinessIServer/ScheduleIServer/bean/csrscsendfiles.h \
    ../../../BusinessIServer/ScheduleIServer/bean/csrscsendstatus.h \
    ../../../BusinessIServer/ScheduleIServer/bean/csrsctask.h \
    ../../../BusinessIServer/ScheduleIServer/bean/cssscsendaddr.h \
    ../../../BusinessIServer/ScheduleIServer/bean/cssscsendfiles.h \
    ../../../BusinessIServer/ScheduleIServer/bean/csssctask.h \
    ../../../BusinessIServer/ScheduleIServer/dao/csscheduledao.h \
    lstaskservlet.h \
    ustaskservlet.h \
    istaskservlet.h \
    lsaddrservlet.h \
    ../../../BusinessIServer/ScheduleIServer/bean/vcsascsendfiles.h \
    lvscfilesservlet.h \
    ustaskaddrservlet.h \
    dstaskservlet.h \
    dstaskaddrservlet.h \
    astaskaddrservlet.h \
    dstaskfilesservlet.h

unix {
    CONFIG += c++11
    target.path = /usr/lib
    INSTALLS += target
}

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../../../UpCloud-Core/DatabaseLib/release/ -lDatabaseLib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../../../UpCloud-Core/DatabaseLib/debug/ -lDatabaseLib
else:unix: LIBS += -L$$OUT_PWD/../../../../UpCloud-Core/DatabaseLib/ -lDatabaseLib

INCLUDEPATH += $$PWD/../../../../UpCloud-Core/DatabaseLib
DEPENDPATH += $$PWD/../../../../UpCloud-Core/DatabaseLib

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../../../UpCloud-Core/AvroLib/release/ -lAvroLib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../../../UpCloud-Core/AvroLib/debug/ -lAvroLib
else:unix: LIBS += -L$$OUT_PWD/../../../../UpCloud-Core/AvroLib/ -lAvroLib

INCLUDEPATH += $$PWD/../../../../UpCloud-Core/AvroLib
DEPENDPATH += $$PWD/../../../../UpCloud-Core/AvroLib

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../../../UpCloud-Core/NetLib/release/ -lNetLib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../../../UpCloud-Core/NetLib/debug/ -lNetLib
else:unix: LIBS += -L$$OUT_PWD/../../../../UpCloud-Core/NetLib/ -lNetLib

INCLUDEPATH += $$PWD/../../../../UpCloud-Core/NetLib
DEPENDPATH += $$PWD/../../../../UpCloud-Core/NetLib

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../../../UpCloud-Core/ActionLib/release/ -lActionLib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../../../UpCloud-Core/ActionLib/debug/ -lActionLib
else:unix: LIBS += -L$$OUT_PWD/../../../../UpCloud-Core/ActionLib/ -lActionLib

INCLUDEPATH += $$PWD/../../../../UpCloud-Core/ActionLib
DEPENDPATH += $$PWD/../../../../UpCloud-Core/ActionLib

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../../../UpCloud-Core/BaseLib/release/ -lBaseLib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../../../UpCloud-Core/BaseLib/debug/ -lBaseLib
else:unix: LIBS += -L$$OUT_PWD/../../../../UpCloud-Core/BaseLib/ -lBaseLib

INCLUDEPATH += $$PWD/../../../../UpCloud-Core/BaseLib
DEPENDPATH += $$PWD/../../../../UpCloud-Core/BaseLib

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../../../UpCloud-Core/ERMLib/release/ -lERMLib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../../../UpCloud-Core/ERMLib/debug/ -lERMLib
else:unix: LIBS += -L$$OUT_PWD/../../../../UpCloud-Core/ERMLib/ -lERMLib

INCLUDEPATH += $$PWD/../../../../UpCloud-Core/ERMLib
DEPENDPATH += $$PWD/../../../../UpCloud-Core/ERMLib

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../../../UpCloud-Core/TransMsgLib/release/ -lTransMsgLib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../../../UpCloud-Core/TransMsgLib/debug/ -lTransMsgLib
else:unix: LIBS += -L$$OUT_PWD/../../../../UpCloud-Core/TransMsgLib/ -lTransMsgLib

INCLUDEPATH += $$PWD/../../../../UpCloud-Core/TransMsgLib
DEPENDPATH += $$PWD/../../../../UpCloud-Core/TransMsgLib

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../../DuplexLib/release/ -lDuplexLib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../../DuplexLib/debug/ -lDuplexLib
else:unix: LIBS += -L$$OUT_PWD/../../../DuplexLib/ -lDuplexLib

INCLUDEPATH += $$PWD/../../../DuplexLib
DEPENDPATH += $$PWD/../../../DuplexLib
