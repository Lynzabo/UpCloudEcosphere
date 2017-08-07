#-------------------------------------------------
#
# Project created by QtCreator 2015-12-21T09:38:50
#
#-------------------------------------------------
QT      += core network sql
QT       -= gui

TARGET = StructOperaIServer
TEMPLATE = lib

DEFINES += STRUCTOPERAISERVER_LIBRARY

SOURCES += structoperaiserver.cpp \
    ../../../BusinessIServer/StructIServer/bean/csrssendaddr.cpp \
    ../../../BusinessIServer/StructIServer/bean/csrssendfiles.cpp \
    ../../../BusinessIServer/StructIServer/bean/csrssendstatus.cpp \
    ../../../BusinessIServer/StructIServer/bean/csrstask.cpp \
    ../../../BusinessIServer/StructIServer/bean/cssssendaddr.cpp \
    ../../../BusinessIServer/StructIServer/bean/cssssendfiles.cpp \
    ../../../BusinessIServer/StructIServer/bean/cssstask.cpp \
    ../../../BusinessIServer/StructIServer/dao/csstructdao.cpp \
    assendaddrservlet.cpp \
    assendfileservlet.cpp \
    astaskservlet.cpp \
    dssendaddrservlet.cpp \
    dssendfileservlet.cpp \
    dstaskservlet.cpp \
    lstaskservlet.cpp\
    util/structutil.cpp \
    ustaskservlet.cpp \
    lsfileservlet.cpp \
    lsaddrservlet.cpp \
    istaskservlet.cpp \
    ../../../BusinessIServer/StructIServer/bean/vcsassendfiles.cpp \
    ustaskaddrservlet.cpp \
    ../../../BusinessIServer/StructIServer/bean/vcssendaddr.cpp \
    lssendstatusservlet.cpp \
    ussendstatusservlet.cpp \
    ustasksendfilesservlet.cpp


HEADERS += structoperaiserver.h\
        structoperaiserver_global.h \
    ../../../BusinessIServer/StructIServer/bean/csrssendaddr.h \
    ../../../BusinessIServer/StructIServer/bean/csrssendfiles.h \
    ../../../BusinessIServer/StructIServer/bean/csrssendstatus.h \
    ../../../BusinessIServer/StructIServer/bean/csrstask.h \
    ../../../BusinessIServer/StructIServer/bean/cssssendaddr.h \
    ../../../BusinessIServer/StructIServer/bean/cssssendfiles.h \
    ../../../BusinessIServer/StructIServer/bean/cssstask.h \
    ../../../BusinessIServer/StructIServer/dao/csstructdao.h \
    assendaddrservlet.h \
    assendfileservlet.h \
    astaskservlet.h \
    dssendaddrservlet.h \
    dssendfileservlet.h \
    dstaskservlet.h \
    lstaskservlet.h\
    util/structutil.h \
    ustaskservlet.h \
    lsfileservlet.h \
    lsaddrservlet.h \
    istaskservlet.h \
    ../../../BusinessIServer/StructIServer/bean/vcsassendfiles.h \
    ustaskaddrservlet.h \
    ../../../BusinessIServer/StructIServer/bean/vcssendaddr.h \
    lssendstatusservlet.h \
    ussendstatusservlet.h \
    ustasksendfilesservlet.h


unix {
    CONFIG += c++11
    target.path = /usr/lib
    INSTALLS += target
}


OTHER_FILES += \
    astaskaddrservlet.cpp.autosave

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../../../UpCloud-Core/BaseLib/release/ -lBaseLib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../../../UpCloud-Core/BaseLib/debug/ -lBaseLib
else:unix: LIBS += -L$$OUT_PWD/../../../../UpCloud-Core/BaseLib/ -lBaseLib

INCLUDEPATH += $$PWD/../../../../UpCloud-Core/BaseLib
DEPENDPATH += $$PWD/../../../../UpCloud-Core/BaseLib



win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../../../UpCloud-Core/TransMsgLib/release/ -lTransMsgLib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../../../UpCloud-Core/TransMsgLib/debug/ -lTransMsgLib
else:unix: LIBS += -L$$OUT_PWD/../../../../UpCloud-Core/TransMsgLib/ -lTransMsgLib

INCLUDEPATH += $$PWD/../../../../UpCloud-Core/TransMsgLib
DEPENDPATH += $$PWD/../../../../UpCloud-Core/TransMsgLib

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../../../UpCloud-Core/ActionLib/release/ -lActionLib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../../../UpCloud-Core/ActionLib/debug/ -lActionLib
else:unix: LIBS += -L$$OUT_PWD/../../../../UpCloud-Core/ActionLib/ -lActionLib

INCLUDEPATH += $$PWD/../../../../UpCloud-Core/ActionLib
DEPENDPATH += $$PWD/../../../../UpCloud-Core/ActionLib

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


win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../../../UpCloud-Core/ERMLib/release/ -lERMLib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../../../UpCloud-Core/ERMLib/debug/ -lERMLib
else:unix: LIBS += -L$$OUT_PWD/../../../../UpCloud-Core/ERMLib/ -lERMLib

INCLUDEPATH += $$PWD/../../../../UpCloud-Core/ERMLib
DEPENDPATH += $$PWD/../../../../UpCloud-Core/ERMLib

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../../DuplexLib/release/ -lDuplexLib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../../DuplexLib/debug/ -lDuplexLib
else:unix: LIBS += -L$$OUT_PWD/../../../DuplexLib/ -lDuplexLib

INCLUDEPATH += $$PWD/../../../DuplexLib
DEPENDPATH += $$PWD/../../../DuplexLib

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../../BaseIServerLib/release/ -lBaseIServerLib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../../BaseIServerLib/debug/ -lBaseIServerLib
else:unix: LIBS += -L$$OUT_PWD/../../../BaseIServerLib/ -lBaseIServerLib

INCLUDEPATH += $$PWD/../../../BaseIServerLib
DEPENDPATH += $$PWD/../../../BaseIServerLib

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../../../UpCloud-Core/ERMLib/release/ -lERMLib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../../../UpCloud-Core/ERMLib/debug/ -lERMLib
else:unix: LIBS += -L$$OUT_PWD/../../../../UpCloud-Core/ERMLib/ -lERMLib

INCLUDEPATH += $$PWD/../../../../UpCloud-Core/ERMLib
DEPENDPATH += $$PWD/../../../../UpCloud-Core/ERMLib
