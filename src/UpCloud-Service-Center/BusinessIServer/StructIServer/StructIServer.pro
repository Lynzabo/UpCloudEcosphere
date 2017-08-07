#-------------------------------------------------
#
# Project created by QtCreator 2015-09-18T09:29:23
#
#-------------------------------------------------

QT      += core network sql
QT       -= gui

TARGET = StructIServer
TEMPLATE = lib

DEFINES += STRUCTISERVER_LIBRARY

SOURCES += \
    dao/csstructdao.cpp \
    bean/csrssendaddr.cpp \
    bean/csrssendfiles.cpp \
    bean/csrssendstatus.cpp \
    bean/csrstask.cpp \
    bean/cssssendaddr.cpp \
    bean/cssssendfiles.cpp \
    bean/cssstask.cpp \
    csexector.cpp \
    crstaskdownloadrequest.cpp \
    crstaskdownstatusrequest.cpp \
    crstaskparsestatusrequest.cpp \
    bean/vcsassendfiles.cpp \
    bean/vcssendaddr.cpp

HEADERS += structiserver.h\
        structiserver_global.h \
    dao/csstructdao.h \
    bean/csrssendaddr.h \
    bean/csrssendfiles.h \
    bean/csrssendstatus.h \
    bean/csrstask.h \
    bean/cssssendaddr.h \
    bean/cssssendfiles.h \
    bean/cssstask.h \
    csexector.h \
    crstaskdownloadrequest.h \
    crstaskdownstatusrequest.h \
    crstaskparsestatusrequest.h \
    bean/vcsassendfiles.h \
    bean/vcssendaddr.h

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


win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../../UpCloud-Core/TimerLib/release/ -lTimerLib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../../UpCloud-Core/TimerLib/debug/ -lTimerLib
else:unix: LIBS += -L$$OUT_PWD/../../../UpCloud-Core/TimerLib/ -lTimerLib

INCLUDEPATH += $$PWD/../../../UpCloud-Core/TimerLib
DEPENDPATH += $$PWD/../../../UpCloud-Core/TimerLib

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
