#-------------------------------------------------
#
# Project created by QtCreator 2016-01-21T09:50:29
#
#-------------------------------------------------
QT      += core network
QT       -= gui

TARGET = ScheduleOperaIRemoteUI
TEMPLATE = lib

DEFINES += SCHEDULEOPERAIREMOTEUI_LIBRARY

SOURCES += \
    lstaskrunnable.cpp \
    ../../../../UpCloud-Service-Center/BusinessIServer/ScheduleIServer/bean/csrscsendaddr.cpp \
    ../../../../UpCloud-Service-Center/BusinessIServer/ScheduleIServer/bean/csrscsendfiles.cpp \
    ../../../../UpCloud-Service-Center/BusinessIServer/ScheduleIServer/bean/csrscsendstatus.cpp \
    ../../../../UpCloud-Service-Center/BusinessIServer/ScheduleIServer/bean/csrsctask.cpp \
    ../../../../UpCloud-Service-Center/BusinessIServer/ScheduleIServer/bean/cssscsendaddr.cpp \
    ../../../../UpCloud-Service-Center/BusinessIServer/ScheduleIServer/bean/cssscsendfiles.cpp \
    ../../../../UpCloud-Service-Center/BusinessIServer/ScheduleIServer/bean/csssctask.cpp \
    ../../../../UpCloud-Service-Center/FrontBusinessIServer/DDMIServer/ScheduleOperaIServer/util/scheduleutil.cpp \
    ustaskrunnable.cpp \
    istaskrunnable.cpp \
    lsaddrrunnable.cpp \
    ../../../../UpCloud-Service-Center/BusinessIServer/ScheduleIServer/bean/vcsascsendfiles.cpp \
    lvcscfilesrunnable.cpp \
    ustaskaddrrunnable.cpp \
    dstaskrunnable.cpp \
    dstaskaddrrunnable.cpp \
    astaskaddrrunable.cpp \
    dstaskfilerunnable.cpp

HEADERS += scheduleoperairemoteui.h\
        scheduleoperairemoteui_global.h \
    lstaskrunnable.h \
    ../../../../UpCloud-Service-Center/BusinessIServer/ScheduleIServer/bean/csrscsendaddr.h \
    ../../../../UpCloud-Service-Center/BusinessIServer/ScheduleIServer/bean/csrscsendfiles.h \
    ../../../../UpCloud-Service-Center/BusinessIServer/ScheduleIServer/bean/csrscsendstatus.h \
    ../../../../UpCloud-Service-Center/BusinessIServer/ScheduleIServer/bean/csrsctask.h \
    ../../../../UpCloud-Service-Center/BusinessIServer/ScheduleIServer/bean/cssscsendaddr.h \
    ../../../../UpCloud-Service-Center/BusinessIServer/ScheduleIServer/bean/cssscsendfiles.h \
    ../../../../UpCloud-Service-Center/BusinessIServer/ScheduleIServer/bean/csssctask.h \
    ../../../../UpCloud-Service-Center/FrontBusinessIServer/DDMIServer/ScheduleOperaIServer/util/scheduleutil.h \
    ustaskrunnable.h \
    istaskrunnable.h \
    lsaddrrunnable.h \
    ../../../../UpCloud-Service-Center/BusinessIServer/ScheduleIServer/bean/vcsascsendfiles.h \
    lvcscfilesrunnable.h \
    ustaskaddrrunnable.h \
    dstaskrunnable.h \
    dstaskaddrrunnable.h \
    astaskaddrrunable.h \
    dstaskfilerunnable.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../../../UpCloud-Core/BaseLib/release/ -lBaseLib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../../../UpCloud-Core/BaseLib/debug/ -lBaseLib
else:unix: LIBS += -L$$OUT_PWD/../../../../UpCloud-Core/BaseLib/ -lBaseLib

INCLUDEPATH += $$PWD/../../../../UpCloud-Core/BaseLib
DEPENDPATH += $$PWD/../../../../UpCloud-Core/BaseLib

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../../../UpCloud-Core/AvroLib/release/ -lAvroLib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../../../UpCloud-Core/AvroLib/debug/ -lAvroLib
else:unix: LIBS += -L$$OUT_PWD/../../../../UpCloud-Core/AvroLib/ -lAvroLib

INCLUDEPATH += $$PWD/../../../../UpCloud-Core/AvroLib
DEPENDPATH += $$PWD/../../../../UpCloud-Core/AvroLib

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../../../UpCloud-Core/DatabaseLib/release/ -lDatabaseLib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../../../UpCloud-Core/DatabaseLib/debug/ -lDatabaseLib
else:unix: LIBS += -L$$OUT_PWD/../../../../UpCloud-Core/DatabaseLib/ -lDatabaseLib

INCLUDEPATH += $$PWD/../../../../UpCloud-Core/DatabaseLib
DEPENDPATH += $$PWD/../../../../UpCloud-Core/DatabaseLib

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

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../../../UpCloud-Core/ERMLib/release/ -lERMLib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../../../UpCloud-Core/ERMLib/debug/ -lERMLib
else:unix: LIBS += -L$$OUT_PWD/../../../../UpCloud-Core/ERMLib/ -lERMLib

INCLUDEPATH += $$PWD/../../../../UpCloud-Core/ERMLib
DEPENDPATH += $$PWD/../../../../UpCloud-Core/ERMLib



win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../../BaseIRemoteLib/release/ -lBaseIRemoteLib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../../BaseIRemoteLib/debug/ -lBaseIRemoteLib
else:unix: LIBS += -L$$OUT_PWD/../../../BaseIRemoteLib/ -lBaseIRemoteLib

INCLUDEPATH += $$PWD/../../../BaseIRemoteLib
DEPENDPATH += $$PWD/../../../BaseIRemoteLib

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
