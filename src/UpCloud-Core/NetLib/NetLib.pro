#-------------------------------------------------
#
#   上云科技应用支撑封装--网络传输相关封装
#
#   版权:  C/C++ development team
#   时间:       2015-07-14 14:27:06
#   注意:
#-----
#   功能:
#           1.支持FTP/Http同步/异步下载(具体使用方法看test.cpp代码片段)
#           2.支持FTP同步/异步上传(具体使用方法看test.cpp代码片段)
#-----
#-------------------------------------------------
QT       += core network serialport
QT       -= gui

TARGET = NetLib
TEMPLATE = lib

DEFINES += NETLIB_LIBRARY

SOURCES += \
    nettransclient.cpp \
    ftp/ftpmeta.cpp \
    ftpclientpool.cpp \
    httpcientpool.cpp \
    http/fileblockdownloadthread.cpp \
    http/filedownthread.cpp \
    http/httpdownloadmanager.cpp \
    http/httpasyncdownloadmanager.cpp \
    ftp/ftpdownloadmanager.cpp \
    ftp/ftpfiledownthread.cpp \
    ftp/core/qftp.cpp \
    ftp/core/qurlinfo.cpp \
    ftp/ftpasyncdownloadmanager.cpp \
#    test.cpp \
    socket/socketmeta.cpp \
    ftp/ftpcommonmanager.cpp \
    ftp/ftpasyncuploadmanager.cpp \
    ftp/ftpuploadmanager.cpp \
    ftp/ftpfileupthread.cpp \
    socket/client/tcpsocket.cpp \
    socket/server/tcpserver.cpp \
    socket/server/tcpserverlistenthread.cpp \
    socket/server/tcpservertransthread.cpp \
    tcpserverpool.cpp \
    serial/core/serialmeta.cpp \
    serial/serialconf.cpp \
    serial/serialmanager.cpp \
    serialpool.cpp \
    serial/core/serialdatagraminfo.cpp \
    serial/core/serialdatagramutil.cpp

HEADERS +=\
        netlib_global.h \
    nettransclient.h \
    ftp/ftpmeta.h \
    ftpclientpool.h \
    httpcientpool.h \
    http/fileblockdownloadthread.h \
    http/filedownthread.h \
    http/httpdownloadmanager.h \
    http/httpasyncdownloadmanager.h \
    ftp/ftpdownloadmanager.h \
    ftp/ftpfiledownthread.h \
    ftp/core/qftp.h \
    ftp/core/qurlinfo.h \
    ftp/ftpasyncdownloadmanager.h \
    socket/socketmeta.h \
    ftp/ftpcommonmanager.h \
    ftp/ftpasyncuploadmanager.h \
    ftp/ftpuploadmanager.h \
    ftp/ftpfileupthread.h \
    socket/client/tcpsocket.h \
    socket/server/tcpserver.h \
    socket/server/tcpserverlistenthread.h \
    socket/server/tcpservertransthread.h \
    tcpserverpool.h \
    serial/core/serialmeta.h \
    serial/serialconf.h \
    serial/serialmanager.h \
    serialpool.h \
    serial/core/serialdatagraminfo.h \
    net.h \
    serial/core/serialdatagramutil.h

unix {
    CONFIG += c++11
    target.path = /usr/lib
    INSTALLS += target
}

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../BaseLib/release/ -lBaseLib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../BaseLib/debug/ -lBaseLib
else:unix: LIBS += -L$$OUT_PWD/../BaseLib/ -lBaseLib

INCLUDEPATH += $$PWD/../BaseLib
DEPENDPATH += $$PWD/../BaseLib

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../TransMsgLib/release/ -lTransMsgLib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../TransMsgLib/debug/ -lTransMsgLib
else:unix: LIBS += -L$$OUT_PWD/../TransMsgLib/ -lTransMsgLib

INCLUDEPATH += $$PWD/../TransMsgLib
DEPENDPATH += $$PWD/../TransMsgLib
