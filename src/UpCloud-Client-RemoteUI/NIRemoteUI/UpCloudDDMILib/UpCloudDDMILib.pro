#-------------------------------------------------
#
#   上云科技运维监控分发管理Native Interface客户端库--面向J2EE Web
#
#   版权:  C/C++ development team
#   时间:       2015-07-14 14:27:06
#
#-------------------------------------------------
QT       += core gui network
QT       -= gui

TARGET = UpCloudDDMILib
TEMPLATE = lib

DEFINES += UPCLOUDDDMILIB_LIBRARY

unix {
    CONFIG += c++11
    target.path = /usr/lib
    INSTALLS += target
}

SOURCES += \
    com_upcloud_ddmi_core_ddeditor.cpp \
    com_upcloud_ddmi_core_ddmiservice.cpp \
    util.cpp \
    ../../../UpCloud-Service-Center/BusinessIServer/UnstructIServer/bean/csrusendaddr.cpp \
    ../../../UpCloud-Service-Center/BusinessIServer/UnstructIServer/bean/csrusendfiles.cpp \
    ../../../UpCloud-Service-Center/BusinessIServer/UnstructIServer/bean/csrusendstatus.cpp \
    ../../../UpCloud-Service-Center/BusinessIServer/UnstructIServer/bean/csrutask.cpp \
    ../../../UpCloud-Service-Center/BusinessIServer/UnstructIServer/bean/cssusendaddr.cpp \
    ../../../UpCloud-Service-Center/BusinessIServer/UnstructIServer/bean/cssusendfiles.cpp \
    ../../../UpCloud-Service-Center/BusinessIServer/UnstructIServer/bean/cssutask.cpp \
    ../../../UpCloud-Service-Center/BusinessIServer/UnstructIServer/bean/dtask.cpp \
    ../../../UpCloud-Service-Center/BusinessIServer/UnstructIServer/bean/dtaskaddr.cpp \
    ../../../UpCloud-Service-Center/BusinessIServer/UnstructIServer/bean/dtaskfile.cpp \
    ../../../UpCloud-Service-Center/FrontBusinessIServer/DDMIServer/UnstructOperaIServer/util/unstructutil.cpp \
    ../../../UpCloud-Service-Center/BusinessIServer/UnstructIServer/bean/vcsrusendaddr.cpp \
    ../../../UpCloud-Service-Center/BusinessIServer/UnstructIServer/bean/vcsrusendfiles.cpp



HEADERS +=\
    jni.h \
    jni_md.h \
    com_upcloud_ddmi_core_DDEditor.h \
    com_upcloud_ddmi_core_DDMIService.h \
    ../../StartRemoteUI/actionregistry.h \
    util.h \
    ../../../UpCloud-Service-Center/BusinessIServer/UnstructIServer/bean/csrusendaddr.h \
    ../../../UpCloud-Service-Center/BusinessIServer/UnstructIServer/bean/csrusendfiles.h \
    ../../../UpCloud-Service-Center/BusinessIServer/UnstructIServer/bean/csrusendstatus.h \
    ../../../UpCloud-Service-Center/BusinessIServer/UnstructIServer/bean/csrutask.h \
    ../../../UpCloud-Service-Center/BusinessIServer/UnstructIServer/bean/cssusendaddr.h \
    ../../../UpCloud-Service-Center/BusinessIServer/UnstructIServer/bean/cssusendfiles.h \
    ../../../UpCloud-Service-Center/BusinessIServer/UnstructIServer/bean/cssutask.h \
    ../../../UpCloud-Service-Center/BusinessIServer/UnstructIServer/bean/dtask.h \
    ../../../UpCloud-Service-Center/BusinessIServer/UnstructIServer/bean/dtaskaddr.h \
    ../../../UpCloud-Service-Center/BusinessIServer/UnstructIServer/bean/dtaskfile.h \
    ../../../UpCloud-Service-Center/FrontBusinessIServer/DDMIServer/UnstructOperaIServer/util/unstructutil.h \
    ../../../UpCloud-Service-Center/BusinessIServer/UnstructIServer/bean/vcsrusendaddr.h \
    ../../../UpCloud-Service-Center/BusinessIServer/UnstructIServer/bean/vcsrusendfiles.h



unix {
    INCLUDEPATH+=/usr/java/jdk1.8.0_65/include/linux/
    INCLUDEPATH+=/usr/java/jdk1.8.0_65/include/
}

#DESTDIR = D:/111

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../../UpCloud-Core/BaseLib/release/ -lBaseLib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../../UpCloud-Core/BaseLib/debug/ -lBaseLib
else:unix: LIBS += -L$$OUT_PWD/../../../UpCloud-Core/BaseLib/ -lBaseLib

INCLUDEPATH += $$PWD/../../../UpCloud-Core/BaseLib
DEPENDPATH += $$PWD/../../../UpCloud-Core/BaseLib

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../BaseIRemoteLib/release/ -lBaseIRemoteLib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../BaseIRemoteLib/debug/ -lBaseIRemoteLib
else:unix: LIBS += -L$$OUT_PWD/../../BaseIRemoteLib/ -lBaseIRemoteLib

INCLUDEPATH += $$PWD/../../BaseIRemoteLib
DEPENDPATH += $$PWD/../../BaseIRemoteLib

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../BusinessIRemote/HthrobsIRemote/release/ -lHthrobsIRemote
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../BusinessIRemote/HthrobsIRemote/debug/ -lHthrobsIRemote
else:unix: LIBS += -L$$OUT_PWD/../../BusinessIRemote/HthrobsIRemote/ -lHthrobsIRemote

INCLUDEPATH += $$PWD/../../BusinessIRemote/HthrobsIRemote
DEPENDPATH += $$PWD/../../BusinessIRemote/HthrobsIRemote

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


win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../BusinessIRemote/OperaIRemote/release/ -lOperaIRemote
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../BusinessIRemote/OperaIRemote/debug/ -lOperaIRemote
else:unix: LIBS += -L$$OUT_PWD/../../BusinessIRemote/OperaIRemote/ -lOperaIRemote

INCLUDEPATH += $$PWD/../../BusinessIRemote/OperaIRemote
DEPENDPATH += $$PWD/../../BusinessIRemote/OperaIRemote

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

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../../UpCloud-Core/NetLib/release/ -lNetLib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../../UpCloud-Core/NetLib/debug/ -lNetLib
else:unix: LIBS += -L$$OUT_PWD/../../../UpCloud-Core/NetLib/ -lNetLib

INCLUDEPATH += $$PWD/../../../UpCloud-Core/NetLib
DEPENDPATH += $$PWD/../../../UpCloud-Core/NetLib

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../NetIRemoteUILib/release/ -lNetIRemoteUILib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../NetIRemoteUILib/debug/ -lNetIRemoteUILib
else:unix: LIBS += -L$$OUT_PWD/../../NetIRemoteUILib/ -lNetIRemoteUILib

INCLUDEPATH += $$PWD/../../NetIRemoteUILib
DEPENDPATH += $$PWD/../../NetIRemoteUILib

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../TimerIRemoteUILib/release/ -lTimerIRemoteUILib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../TimerIRemoteUILib/debug/ -lTimerIRemoteUILib
else:unix: LIBS += -L$$OUT_PWD/../../TimerIRemoteUILib/ -lTimerIRemoteUILib

INCLUDEPATH += $$PWD/../../TimerIRemoteUILib
DEPENDPATH += $$PWD/../../TimerIRemoteUILib

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../DuplexLib/release/ -lDuplexLib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../DuplexLib/debug/ -lDuplexLib
else:unix: LIBS += -L$$OUT_PWD/../../DuplexLib/ -lDuplexLib

INCLUDEPATH += $$PWD/../../DuplexLib
DEPENDPATH += $$PWD/../../DuplexLib

