#-------------------------------------------------
#
# Project created by QtCreator 2015-12-21T09:41:50
#
#-------------------------------------------------
QT       += core network
QT       -= gui

TARGET = StructOperaIRemoteUI
TEMPLATE = lib

DEFINES += STRUCTOPERAIREMOTEUI_LIBRARY

SOURCES += structoperairemoteui.cpp \
    ../../../../UpCloud-Service-Center/BusinessIServer/StructIServer/bean/csrssendaddr.cpp \
    ../../../../UpCloud-Service-Center/BusinessIServer/StructIServer/bean/csrssendfiles.cpp \
    ../../../../UpCloud-Service-Center/BusinessIServer/StructIServer/bean/csrssendstatus.cpp \
    ../../../../UpCloud-Service-Center/BusinessIServer/StructIServer/bean/csrstask.cpp \
    ../../../../UpCloud-Service-Center/BusinessIServer/StructIServer/bean/cssssendaddr.cpp \
    ../../../../UpCloud-Service-Center/BusinessIServer/StructIServer/bean/cssssendfiles.cpp \
    ../../../../UpCloud-Service-Center/BusinessIServer/StructIServer/bean/cssstask.cpp \
    ../../../../UpCloud-Service-Center/FrontBusinessIServer/DDMIServer/StructOperaIServer/util/structutil.cpp \
    lstaskrunnable.cpp \
    dstaskrunnable.cpp \
    astaskaddrrunnable.cpp \
    dstaskaddrrunnable.cpp \
    astaskfilerunnable.cpp \
    dstaskfilerunnable.cpp \
    astaskrunnable.cpp \
    ustaskrunnable.cpp \
    lsfilerunnable.cpp \
    lsaddrrunnable.cpp \
    istaskrunnable.cpp \
    ../../../../UpCloud-Service-Center/BusinessIServer/StructIServer/bean/vcsassendfiles.cpp \
    ustaskaddrrunnable.cpp \
    ../../../../UpCloud-Service-Center/BusinessIServer/StructIServer/bean/vcssendaddr.cpp \
    lssendstatusrunnable.cpp \
    ussendstatusrunnable.cpp \
    ustaskfilerunnable.cpp

HEADERS += structoperairemoteui.h\
        structoperairemoteui_global.h \
    ../../../../UpCloud-Service-Center/BusinessIServer/StructIServer/bean/csrssendaddr.h \
    ../../../../UpCloud-Service-Center/BusinessIServer/StructIServer/bean/csrssendfiles.h \
    ../../../../UpCloud-Service-Center/BusinessIServer/StructIServer/bean/csrssendstatus.h \
    ../../../../UpCloud-Service-Center/BusinessIServer/StructIServer/bean/csrstask.h \
    ../../../../UpCloud-Service-Center/BusinessIServer/StructIServer/bean/cssssendaddr.h \
    ../../../../UpCloud-Service-Center/BusinessIServer/StructIServer/bean/cssssendfiles.h \
    ../../../../UpCloud-Service-Center/BusinessIServer/StructIServer/bean/cssstask.h \
    ../../../../UpCloud-Service-Center/FrontBusinessIServer/DDMIServer/StructOperaIServer/util/structutil.h \
    lstaskrunnable.h \
    dstaskrunnable.h \
    astaskaddrrunnable.h \
    dstaskaddrrunnable.h \
    astaskfilerunnable.h \
    dstaskfilerunnable.h \
    astaskrunnable.h \
    ustaskrunnable.h \
    lsfilerunnable.h \
    lsaddrrunnable.h \
    istaskrunnable.h \
    ../../../../UpCloud-Service-Center/BusinessIServer/StructIServer/bean/vcsassendfiles.h \
    ustaskaddrrunnable.h \
    ../../../../UpCloud-Service-Center/BusinessIServer/StructIServer/bean/vcssendaddr.h \
    lssendstatusrunnable.h \
    ussendstatusrunnable.h \
    ustaskfilerunnable.h

unix {
    CONFIG += c++11
    target.path = /usr/lib
    INSTALLS += target
}
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

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../../BaseIRemoteLib/release/ -lBaseIRemoteLib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../../BaseIRemoteLib/debug/ -lBaseIRemoteLib
else:unix: LIBS += -L$$OUT_PWD/../../../BaseIRemoteLib/ -lBaseIRemoteLib

INCLUDEPATH += $$PWD/../../../BaseIRemoteLib
DEPENDPATH += $$PWD/../../../BaseIRemoteLib

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../../../UpCloud-Core/NetLib/release/ -lNetLib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../../../UpCloud-Core/NetLib/debug/ -lNetLib
else:unix: LIBS += -L$$OUT_PWD/../../../../UpCloud-Core/NetLib/ -lNetLib

INCLUDEPATH += $$PWD/../../../../UpCloud-Core/NetLib
DEPENDPATH += $$PWD/../../../../UpCloud-Core/NetLib

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../../DuplexLib/release/ -lDuplexLib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../../DuplexLib/debug/ -lDuplexLib
else:unix: LIBS += -L$$OUT_PWD/../../../DuplexLib/ -lDuplexLib

INCLUDEPATH += $$PWD/../../../DuplexLib
DEPENDPATH += $$PWD/../../../DuplexLib

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../../../UpCloud-Core/ERMLib/release/ -lERMLib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../../../UpCloud-Core/ERMLib/debug/ -lERMLib
else:unix: LIBS += -L$$OUT_PWD/../../../../UpCloud-Core/ERMLib/ -lERMLib

INCLUDEPATH += $$PWD/../../../../UpCloud-Core/ERMLib
DEPENDPATH += $$PWD/../../../../UpCloud-Core/ERMLib
