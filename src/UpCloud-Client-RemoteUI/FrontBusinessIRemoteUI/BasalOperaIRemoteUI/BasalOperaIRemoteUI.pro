#-------------------------------------------------
#
# Project created by QtCreator 2015-12-14T16:17:43
#
#-------------------------------------------------
QT       += core network
QT       -= gui

TARGET = BasalOperaIRemoteUI
TEMPLATE = lib

DEFINES += BASALOPERAIREMOTEUI_LIBRARY

SOURCES += \
    ../../../UpCloud-Service-Center/BusinessIServer/BasalIServer/bean/csdict.cpp \
    adictrunable.cpp \
    ldictrunnable.cpp \
    udictrunnable.cpp \
    ../../../UpCloud-Service-Center/FrontBusinessIServer/BasalOperaIServer/util/dictutil.cpp \
    ddictrunnable.cpp \
    ../../../UpCloud-Service-Center/BusinessIServer/BasalIServer/bean/cscextendinfo.cpp \
    ../../../UpCloud-Service-Center/BusinessIServer/BasalIServer/bean/cscgroup.cpp \
    ../../../UpCloud-Service-Center/BusinessIServer/BasalIServer/bean/cscgroupassoc.cpp \
    ../../../UpCloud-Service-Center/FrontBusinessIServer/BasalOperaIServer/util/csgroupandclientutil.cpp \
    acgrouprunnable.cpp \
    ucgrouprunnable.cpp \
    lcgrouprunnable.cpp \
    acgroupassocrunnable.cpp \
    dcgroupassocrunnable.cpp \
    lcgroupassocrunnable.cpp \
    mgsequencerunnable.cpp \
    dcgrouprunnable.cpp \
    ucgroupassocrunnable.cpp \
    lcextendinforunnable.cpp \
    ../../../UpCloud-Service-Center/BusinessIServer/BasalIServer/bean/vcscgroupassoc.cpp

HEADERS += basaloperairemoteui.h\
        basaloperairemoteui_global.h \
    ../../../UpCloud-Service-Center/BusinessIServer/BasalIServer/bean/csdict.h \
    adictrunable.h \
    ldictrunnable.h \
    udictrunnable.h \
    ../../../UpCloud-Service-Center/FrontBusinessIServer/BasalOperaIServer/util/dictutil.h \
    ddictrunnable.h \
    ../../../UpCloud-Service-Center/BusinessIServer/BasalIServer/bean/cscextendinfo.h \
    ../../../UpCloud-Service-Center/BusinessIServer/BasalIServer/bean/cscgroup.h \
    ../../../UpCloud-Service-Center/BusinessIServer/BasalIServer/bean/cscgroupassoc.h \
    ../../../UpCloud-Service-Center/FrontBusinessIServer/BasalOperaIServer/util/csgroupandclientutil.h \
    acgrouprunnable.h \
    ucgrouprunnable.h \
    lcgrouprunnable.h \
    acgroupassocrunnable.h \
    dcgroupassocrunnable.h \
    lcgroupassocrunnable.h \
    mgquencerunnable.h \
    dcgrouprunnable.h \
    ucgroupassocrunnable.h \
    lcextendinforunnable.h \
    ../../../UpCloud-Service-Center/BusinessIServer/BasalIServer/bean/vcscgroupassoc.h

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

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../BaseIRemoteLib/release/ -lBaseIRemoteLib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../BaseIRemoteLib/debug/ -lBaseIRemoteLib
else:unix: LIBS += -L$$OUT_PWD/../../BaseIRemoteLib/ -lBaseIRemoteLib

INCLUDEPATH += $$PWD/../../BaseIRemoteLib
DEPENDPATH += $$PWD/../../BaseIRemoteLib

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../../UpCloud-Core/NetLib/release/ -lNetLib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../../UpCloud-Core/NetLib/debug/ -lNetLib
else:unix: LIBS += -L$$OUT_PWD/../../../UpCloud-Core/NetLib/ -lNetLib

INCLUDEPATH += $$PWD/../../../UpCloud-Core/NetLib
DEPENDPATH += $$PWD/../../../UpCloud-Core/NetLib

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../DuplexLib/release/ -lDuplexLib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../DuplexLib/debug/ -lDuplexLib
else:unix: LIBS += -L$$OUT_PWD/../../DuplexLib/ -lDuplexLib

INCLUDEPATH += $$PWD/../../DuplexLib
DEPENDPATH += $$PWD/../../DuplexLib

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../../UpCloud-Core/ERMLib/release/ -lERMLib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../../UpCloud-Core/ERMLib/debug/ -lERMLib
else:unix: LIBS += -L$$OUT_PWD/../../../UpCloud-Core/ERMLib/ -lERMLib

INCLUDEPATH += $$PWD/../../../UpCloud-Core/ERMLib
DEPENDPATH += $$PWD/../../../UpCloud-Core/ERMLib
