#-------------------------------------------------
#
# Project created by QtCreator 2015-12-14T15:39:07
#
#-------------------------------------------------
QT      += core network sql
QT       -= gui

TARGET = BasalOperaIServer
TEMPLATE = lib

DEFINES += BASALOPERAISERVER_LIBRARY

SOURCES += \
    ../../BusinessIServer/BasalIServer/bean/csdict.cpp \
    ../../BusinessIServer/BasalIServer/dao/csdictdao.cpp \
    ldictservlet.cpp \
    adictservlet.cpp \
    udictservlet.cpp \
    util/dictutil.cpp \
    ddictservlet.cpp \
    ../../BusinessIServer/BasalIServer/bean/cscextendinfo.cpp \
    ../../BusinessIServer/BasalIServer/bean/cscgroup.cpp \
    ../../BusinessIServer/BasalIServer/bean/cscgroupassoc.cpp \
    ../../BusinessIServer/BasalIServer/dao/csgroupandclinetdao.cpp \
    util/csgroupandclientutil.cpp \
    acgroupservlet.cpp \
    ucgroupservlet.cpp \
    lcgroupservlet.cpp \
    acgroupassocservlet.cpp \
    dcgroupassocservlet.cpp \
    lcgroupassocservlet.cpp \
    dcgroupservlet.cpp \
    mgsequenceservlet.cpp \
    ucgroupassocservlet.cpp \
    lcextendinfoservlet.cpp \
    ../../BusinessIServer/BasalIServer/bean/vcscgroupassoc.cpp

HEADERS += basaloperaiserver.h\
        basaloperaiserver_global.h \
    ../../BusinessIServer/BasalIServer/bean/csdict.h \
    ../../BusinessIServer/BasalIServer/dao/csdictdao.h \
    ldictservlet.h \
    adictservlet.h \
    udictservlet.h \
    util/dictutil.h \
    ddictservlet.h \
    ../../BusinessIServer/BasalIServer/bean/cscextendinfo.h \
    ../../BusinessIServer/BasalIServer/bean/cscgroup.h \
    ../../BusinessIServer/BasalIServer/bean/cscgroupassoc.h \
    ../../BusinessIServer/BasalIServer/dao/csgroupandclinetdao.h \
    util/csgroupandclientutil.h \
    acgroupservlet.h \
    ucgroupservlet.h \
    lcgroupservlet.h \
    acgroupassocservlet.h \
    dcgroupassocservlet.h \
    lcgroupassocservlet.h \
    dcgroupservlet.h \
    mgsequenceservlet.h \
    ucgroupassocservlet.h \
    lcextendinfoservlet.h \
    ../../BusinessIServer/BasalIServer/bean/vcscgroupassoc.h

unix {
    CONFIG += c++11
    target.path = /usr/lib
    INSTALLS += target
}

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

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../../UpCloud-Core/BaseLib/release/ -lBaseLib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../../UpCloud-Core/BaseLib/debug/ -lBaseLib
else:unix: LIBS += -L$$OUT_PWD/../../../UpCloud-Core/BaseLib/ -lBaseLib

INCLUDEPATH += $$PWD/../../../UpCloud-Core/BaseLib
DEPENDPATH += $$PWD/../../../UpCloud-Core/BaseLib

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../../UpCloud-Core/NetLib/release/ -lNetLib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../../UpCloud-Core/NetLib/debug/ -lNetLib
else:unix: LIBS += -L$$OUT_PWD/../../../UpCloud-Core/NetLib/ -lNetLib

INCLUDEPATH += $$PWD/../../../UpCloud-Core/NetLib
DEPENDPATH += $$PWD/../../../UpCloud-Core/NetLib

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../../UpCloud-Core/TransMsgLib/release/ -lTransMsgLib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../../UpCloud-Core/TransMsgLib/debug/ -lTransMsgLib
else:unix: LIBS += -L$$OUT_PWD/../../../UpCloud-Core/TransMsgLib/ -lTransMsgLib

INCLUDEPATH += $$PWD/../../../UpCloud-Core/TransMsgLib
DEPENDPATH += $$PWD/../../../UpCloud-Core/TransMsgLib

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

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../DuplexLib/release/ -lDuplexLib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../DuplexLib/debug/ -lDuplexLib
else:unix: LIBS += -L$$OUT_PWD/../../DuplexLib/ -lDuplexLib

INCLUDEPATH += $$PWD/../../DuplexLib
DEPENDPATH += $$PWD/../../DuplexLib
