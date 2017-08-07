#-------------------------------------------------
#
# Project created by QtCreator 2015-09-18T09:28:25
#
#-------------------------------------------------
QT      += core network sql
QT       -= gui

TARGET = UnstructIServer
TEMPLATE = lib

DEFINES += UNSTRUCTISERVER_LIBRARY

SOURCES += \
    bean/csrusendaddr.cpp \
    bean/csrusendfiles.cpp \
    bean/csrusendstatus.cpp \
    bean/cssusendaddr.cpp \
    bean/cssusendfiles.cpp \
    bean/cssutask.cpp \
    dao/csunstructdao.cpp \
    cuexector.cpp \
    bean/csrutask.cpp \
    crutaskdownloadrequest.cpp \
  #  crutaskstatusrequest.cpp
    crutaskstatusrequest.cpp \
    bean/dtask.cpp \
    bean/dtaskfile.cpp \
    bean/dtaskaddr.cpp \
    ../StructIServer/bean/csrssendaddr.cpp \
    ../StructIServer/bean/csrssendfiles.cpp \
    ../StructIServer/bean/csrssendstatus.cpp \
    ../StructIServer/bean/csrstask.cpp \
    ../StructIServer/bean/cssssendaddr.cpp \
    ../StructIServer/bean/cssssendfiles.cpp \
    ../StructIServer/bean/cssstask.cpp \
    bean/vcsrusendaddr.cpp \
    bean/vcsrusendfiles.cpp


HEADERS +=\
        unstructiserver_global.h \
    bean/csrusendaddr.h \
    bean/csrusendfiles.h \
    bean/csrusendstatus.h \
    bean/cssusendaddr.h \
    bean/cssusendfiles.h \
    bean/cssutask.h \
    dao/csunstructdao.h \
    unstructiserver.h \
    cuexector.h \
    bean/csrutask.h \
    crutaskdownloadrequest.h \
   # crutaskstatusrequest.h
    crutaskstatusrequest.h \
    bean/dtask.h \
    bean/dtaskfile.h \
    bean/dtaskaddr.h \
    ../StructIServer/bean/csrssendaddr.h \
    ../StructIServer/bean/csrssendfiles.h \
    ../StructIServer/bean/csrssendstatus.h \
    ../StructIServer/bean/csrstask.h \
    ../StructIServer/bean/cssssendaddr.h \
    ../StructIServer/bean/cssssendfiles.h \
    ../StructIServer/bean/cssstask.h \
    bean/vcsrusendaddr.h \
    bean/vcsrusendfiles.h \
    bean/vcsrusendfiles.h


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

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../../UpCloud-Core/ActionLib/release/ -lActionLib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../../UpCloud-Core/ActionLib/debug/ -lActionLib
else:unix: LIBS += -L$$OUT_PWD/../../../UpCloud-Core/ActionLib/ -lActionLib

INCLUDEPATH += $$PWD/../../../UpCloud-Core/ActionLib
DEPENDPATH += $$PWD/../../../UpCloud-Core/ActionLib

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../../UpCloud-Core/AvroLib/release/ -lAvroLib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../../UpCloud-Core/AvroLib/debug/ -lAvroLib
else:unix: LIBS += -L$$OUT_PWD/../../../UpCloud-Core/AvroLib/ -lAvroLib

INCLUDEPATH += $$PWD/../../../UpCloud-Core/AvroLib
DEPENDPATH += $$PWD/../../../UpCloud-Core/AvroLib

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../../UpCloud-Core/DatabaseLib/release/ -lDatabaseLib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../../UpCloud-Core/DatabaseLib/debug/ -lDatabaseLib
else:unix: LIBS += -L$$OUT_PWD/../../../UpCloud-Core/DatabaseLib/ -lDatabaseLib

INCLUDEPATH += $$PWD/../../../UpCloud-Core/DatabaseLib
DEPENDPATH += $$PWD/../../../UpCloud-Core/DatabaseLib

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../../UpCloud-Core/ERMLib/release/ -lERMLib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../../UpCloud-Core/ERMLib/debug/ -lERMLib
else:unix: LIBS += -L$$OUT_PWD/../../../UpCloud-Core/ERMLib/ -lERMLib

INCLUDEPATH += $$PWD/../../../UpCloud-Core/ERMLib
DEPENDPATH += $$PWD/../../../UpCloud-Core/ERMLib

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../BaseIServerLib/release/ -lBaseIServerLib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../BaseIServerLib/debug/ -lBaseIServerLib
else:unix: LIBS += -L$$OUT_PWD/../../BaseIServerLib/ -lBaseIServerLib

INCLUDEPATH += $$PWD/../../BaseIServerLib
DEPENDPATH += $$PWD/../../BaseIServerLib
