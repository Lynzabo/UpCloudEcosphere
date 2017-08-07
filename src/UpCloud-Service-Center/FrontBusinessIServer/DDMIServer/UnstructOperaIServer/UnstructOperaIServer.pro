#-------------------------------------------------
#
# Project created by QtCreator 2015-11-30T14:53:30
#
#-------------------------------------------------
QT      += core network sql
QT       -= gui

TARGET = UnstructOperaIServer
TEMPLATE = lib

DEFINES += UNSTRUCTOPERAISERVER_LIBRARY

HEADERS += \
    autaskfileservlet.h \
    autasknodeservlet.h \
    dutaskfilesevlet.h \
    dutasknodeservlet.h \
    dutasksservlet.h \
    iutaskservlet.h \
    lutasksservlet.h \
    unstructoperaiserver.h \
    unstructoperaiserver_global.h \
    uutaskservlet.h \
    util/unstructutil.h \
    autaskservlet.h \
    ../../../BusinessIServer/UnstructIServer/bean/csrusendaddr.h \
    ../../../BusinessIServer/UnstructIServer/bean/csrusendfiles.h \
    ../../../BusinessIServer/UnstructIServer/bean/csrusendstatus.h \
    ../../../BusinessIServer/UnstructIServer/bean/csrutask.h \
    ../../../BusinessIServer/UnstructIServer/bean/cssusendaddr.h \
    ../../../BusinessIServer/UnstructIServer/bean/cssusendfiles.h \
    ../../../BusinessIServer/UnstructIServer/bean/cssutask.h \
    ../../../BusinessIServer/UnstructIServer/bean/dtask.h \
    ../../../BusinessIServer/UnstructIServer/bean/dtaskaddr.h \
    ../../../BusinessIServer/UnstructIServer/bean/dtaskfile.h \
    ../../../BusinessIServer/UnstructIServer/dao/csunstructdao.h \
    ddeditordelserverlet.h \
    ddeditorsendserverlet.h \
    ../../../BusinessIServer/StructIServer/bean/csrssendaddr.h \
    ../../../BusinessIServer/StructIServer/bean/csrssendfiles.h \
    ../../../BusinessIServer/StructIServer/bean/csrssendstatus.h \
    ../../../BusinessIServer/StructIServer/bean/csrstask.h \
    ../../../BusinessIServer/StructIServer/bean/cssssendaddr.h \
    ../../../BusinessIServer/StructIServer/bean/cssssendfiles.h \
    ../../../BusinessIServer/StructIServer/bean/cssstask.h \
    ../../../BusinessIServer/StructIServer/dao/csstructdao.h \
    lufileservlet.h \
    uutaskaddrservlet.h \
    ../../../BusinessIServer/UnstructIServer/bean/vcsrusendaddr.h \
    lsutasknodesevlet.h \
    uusendstatusservlet.h \
    lusendstatusservlet.h \
    ../../../BusinessIServer/UnstructIServer/bean/vcsrusendfiles.h \
    ../../../BusinessIServer/StructIServer/bean/vcsassendfiles.h \
    uutasksendfilesservlet.h \
    ../../../BusinessIServer/StructIServer/bean/vcssendaddr.h


SOURCES += \
    autaskfileservlet.cpp \
    autasknodeservlet.cpp \
    autaskservlet.cpp \
    dutaskfilesevlet.cpp \
    dutasknodeservlet.cpp \
    dutasksservlet.cpp \
    iutaskservlet.cpp \
    lutasksservlet.cpp \
    uutaskservlet.cpp \
    util/unstructutil.cpp \
    ../../../BusinessIServer/UnstructIServer/dao/csunstructdao.cpp \
    ../../../BusinessIServer/UnstructIServer/bean/csrusendaddr.cpp \
    ../../../BusinessIServer/UnstructIServer/bean/csrusendfiles.cpp \
    ../../../BusinessIServer/UnstructIServer/bean/csrusendstatus.cpp \
    ../../../BusinessIServer/UnstructIServer/bean/csrutask.cpp \
    ../../../BusinessIServer/UnstructIServer/bean/cssusendaddr.cpp \
    ../../../BusinessIServer/UnstructIServer/bean/cssusendfiles.cpp \
    ../../../BusinessIServer/UnstructIServer/bean/cssutask.cpp \
    ../../../BusinessIServer/UnstructIServer/bean/dtask.cpp \
    ../../../BusinessIServer/UnstructIServer/bean/dtaskaddr.cpp \
    ../../../BusinessIServer/UnstructIServer/bean/dtaskfile.cpp \
    ddeditordelserverlet.cpp \
    ddeditorsendserverlet.cpp \
    ../../../BusinessIServer/StructIServer/bean/csrssendaddr.cpp \
    ../../../BusinessIServer/StructIServer/bean/csrssendfiles.cpp \
    ../../../BusinessIServer/StructIServer/bean/csrssendstatus.cpp \
    ../../../BusinessIServer/StructIServer/bean/csrstask.cpp \
    ../../../BusinessIServer/StructIServer/bean/cssssendaddr.cpp \
    ../../../BusinessIServer/StructIServer/bean/cssssendfiles.cpp \
    ../../../BusinessIServer/StructIServer/bean/cssstask.cpp \
    ../../../BusinessIServer/StructIServer/dao/csstructdao.cpp \
    lufileservlet.cpp \
    uutaskaddrservlet.cpp \
    ../../../BusinessIServer/UnstructIServer/bean/vcsrusendaddr.cpp \
    lsutasknodesevlet.cpp \
    uusendstatusservlet.cpp \
    lusendstatusservlet.cpp \
    ../../../BusinessIServer/UnstructIServer/bean/vcsrusendfiles.cpp \
    ../../../BusinessIServer/StructIServer/bean/vcsassendfiles.cpp \
    uutasksendfilesservlet.cpp \
    ../../../BusinessIServer/StructIServer/bean/vcssendaddr.cpp

#适配csunstructdao.h中引入结构化头文��?,在这里手动设置include path包含UnStructIServer这个目录
INCLUDEPATH += $$PWD/../../../BusinessIServer/UnStructIServer


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
