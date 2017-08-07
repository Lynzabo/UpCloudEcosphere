#-------------------------------------------------
#
# Project created by QtCreator 2015-09-18T09:38:29
#
#-------------------------------------------------

QT       += core network sql
QT       -= gui

TARGET = ScheduleIClient
TEMPLATE = lib

DEFINES += SCHEDULEICLIENT_LIBRARY

SOURCES += \
    bean/nsrscsendfiles.cpp \
    bean/nsrsctask.cpp \
    bean/nssscsendfiles.cpp \
    bean/nsssctask.cpp \
    dao/nsscheduledao.cpp \
    nrsctaskrequest.cpp \
    nscdownexector.cpp \
    nrsctaskdownstatusrequest.cpp \
    nscparseexector.cpp \
    nrsctaskparsestatusrequest.cpp \
    util/taskexecpool.cpp \
    util/taskexecpoolimpl.cpp \
    util/taskExec/taskexecmanager.cpp \
    util/taskExec/bean/taskinjson.cpp \
    util/taskExec/bean/taskoutjson.cpp

HEADERS += scheduleiclient.h\
        scheduleiclient_global.h \
    bean/nsrscsendfiles.h \
    bean/nsrsctask.h \
    bean/nssscsendfiles.h \
    bean/nsssctask.h \
    dao/nsscheduledao.h \
    nrsctaskrequest.h \
    nscdownexector.h \
    nrsctaskdownstatusrequest.h \
    nscparseexector.h \
    nrsctaskparsestatusrequest.h \    
    util/taskexecpool.h \
    util/taskexecpoolimpl.h \
    util/taskExec/taskexecmanager.h \
    util/taskExec/bean/taskinjson.h \
    util/taskExec/bean/taskoutjson.h

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


win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../../UpCloud-Core/ActionLib/release/ -lActionLib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../../UpCloud-Core/ActionLib/debug/ -lActionLib
else:unix: LIBS += -L$$OUT_PWD/../../../UpCloud-Core/ActionLib/ -lActionLib

INCLUDEPATH += $$PWD/../../../UpCloud-Core/ActionLib
DEPENDPATH += $$PWD/../../../UpCloud-Core/ActionLib

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../../UpCloud-Core/TimerLib/release/ -lTimerLib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../../UpCloud-Core/TimerLib/debug/ -lTimerLib
else:unix: LIBS += -L$$OUT_PWD/../../../UpCloud-Core/TimerLib/ -lTimerLib

INCLUDEPATH += $$PWD/../../../UpCloud-Core/TimerLib
DEPENDPATH += $$PWD/../../../UpCloud-Core/TimerLib

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../../UpCloud-Core/NetLib/release/ -lNetLib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../../UpCloud-Core/NetLib/debug/ -lNetLib
else:unix: LIBS += -L$$OUT_PWD/../../../UpCloud-Core/NetLib/ -lNetLib

INCLUDEPATH += $$PWD/../../../UpCloud-Core/NetLib
DEPENDPATH += $$PWD/../../../UpCloud-Core/NetLib

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../BaseIClientLib/release/ -lBaseIClientLib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../BaseIClientLib/debug/ -lBaseIClientLib
else:unix: LIBS += -L$$OUT_PWD/../../BaseIClientLib/ -lBaseIClientLib

INCLUDEPATH += $$PWD/../../BaseIClientLib
DEPENDPATH += $$PWD/../../BaseIClientLib

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../../UpCloud-Core/AvroLib/release/ -lAvroLib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../../UpCloud-Core/AvroLib/debug/ -lAvroLib
else:unix: LIBS += -L$$OUT_PWD/../../../UpCloud-Core/AvroLib/ -lAvroLib

INCLUDEPATH += $$PWD/../../../UpCloud-Core/AvroLib
DEPENDPATH += $$PWD/../../../UpCloud-Core/AvroLib

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../../UpCloud-Core/ERMLib/release/ -lERMLib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../../UpCloud-Core/ERMLib/debug/ -lERMLib
else:unix: LIBS += -L$$OUT_PWD/../../../UpCloud-Core/ERMLib/ -lERMLib

INCLUDEPATH += $$PWD/../../../UpCloud-Core/ERMLib
DEPENDPATH += $$PWD/../../../UpCloud-Core/ERMLib


