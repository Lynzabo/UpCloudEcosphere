#-------------------------------------------------
#
# Project created by QtCreator 2015-12-07T19:17:42
#
#-------------------------------------------------
QT       += core network sql
QT       -= gui

TARGET = UnstructOperaIRemoteUI
TEMPLATE = lib

DEFINES += UNSTRUCTOPERAIREMOTEUI_LIBRARY

SOURCES += \
    dirunstructtaskrunnable.cpp \
    iutaskrunnable.cpp \
    ../../../../UpCloud-Service-Center/FrontBusinessIServer/DDMIServer/UnstructOperaIServer/util/unstructutil.cpp \
    dutaskrunnable.cpp \
    dutaskfilerunnable.cpp \
    autaskrunnable.cpp \
    autaskfilerunnable.cpp\
    uutaskrunnable.cpp \
    autaskaddrrunnable.cpp \
    ../../../../UpCloud-Service-Center/BusinessIServer/UnstructIServer/bean/csrusendaddr.cpp \
    ../../../../UpCloud-Service-Center/BusinessIServer/UnstructIServer/bean/csrusendfiles.cpp \
    ../../../../UpCloud-Service-Center/BusinessIServer/UnstructIServer/bean/csrusendstatus.cpp \
    ../../../../UpCloud-Service-Center/BusinessIServer/UnstructIServer/bean/csrutask.cpp \
    ../../../../UpCloud-Service-Center/BusinessIServer/UnstructIServer/bean/cssusendaddr.cpp \
    ../../../../UpCloud-Service-Center/BusinessIServer/UnstructIServer/bean/cssusendfiles.cpp \
    ../../../../UpCloud-Service-Center/BusinessIServer/UnstructIServer/bean/cssutask.cpp \
    ../../../../UpCloud-Service-Center/BusinessIServer/UnstructIServer/bean/dtask.cpp \
    ../../../../UpCloud-Service-Center/BusinessIServer/UnstructIServer/bean/dtaskaddr.cpp \
    ../../../../UpCloud-Service-Center/BusinessIServer/UnstructIServer/bean/dtaskfile.cpp \
    luaddrrunnable.cpp \
    lufilerunnable.cpp \
    uutaskaddrrunnable.cpp \
    ../../../../UpCloud-Service-Center/BusinessIServer/UnstructIServer/bean/vcsrusendaddr.cpp \
    uusendstatusrunnable.cpp \
    lusendstatusrunnable.cpp \
    ../../../../UpCloud-Service-Center/BusinessIServer/UnstructIServer/bean/vcsrusendfiles.cpp \
    uutasksendfilesrunnable.cpp \
    autasknoderunnable.cpp \
    dutasknoderunnable.cpp




HEADERS +=\
        unstructoperairemoteui_global.h \
    dirunstructtaskrunnable.h \
    iutaskrunnable.h \
    unstructoperairemoteui.h \
    ../../../../UpCloud-Service-Center/FrontBusinessIServer/DDMIServer/UnstructOperaIServer/util/unstructutil.h \
    dutaskrunnable.h \
    dutaskfilerunnable.h \
    autaskrunnable.h \
    autaskfilerunnable.h\
    uutaskrunnable.h \
    autaskaddrrunnable.h \
    ../../../../UpCloud-Service-Center/BusinessIServer/UnstructIServer/bean/csrusendaddr.h \
    ../../../../UpCloud-Service-Center/BusinessIServer/UnstructIServer/bean/csrusendfiles.h \
    ../../../../UpCloud-Service-Center/BusinessIServer/UnstructIServer/bean/csrusendstatus.h \
    ../../../../UpCloud-Service-Center/BusinessIServer/UnstructIServer/bean/csrutask.h \
    ../../../../UpCloud-Service-Center/BusinessIServer/UnstructIServer/bean/cssusendaddr.h \
    ../../../../UpCloud-Service-Center/BusinessIServer/UnstructIServer/bean/cssusendfiles.h \
    ../../../../UpCloud-Service-Center/BusinessIServer/UnstructIServer/bean/cssutask.h \
    ../../../../UpCloud-Service-Center/BusinessIServer/UnstructIServer/bean/dtask.h \
    ../../../../UpCloud-Service-Center/BusinessIServer/UnstructIServer/bean/dtaskaddr.h \
    ../../../../UpCloud-Service-Center/BusinessIServer/UnstructIServer/bean/dtaskfile.h \
    luaddrrunnable.h \
    lufilerunnable.h \
    uutaskaddrrunnable.h \
    ../../../../UpCloud-Service-Center/BusinessIServer/UnstructIServer/bean/vcsrusendaddr.h \
    uusendstatusrunnable.h \
    lusendstatusrunnable.h \
    ../../../../UpCloud-Service-Center/BusinessIServer/UnstructIServer/bean/vcsrusendfiles.h \
    autasknoderunnable.h \
    uutasksendfilesrunnable.h \
    dutasknoderunnable.h






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
