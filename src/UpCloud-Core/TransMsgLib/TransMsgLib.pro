#-------------------------------------------------
#
#   上云科技应用支撑封装--报文解析/封装封装
#
#   版权:  C/C++ development team
#   时间:       2015-07-14 14:27:06
#   注意: 生成XML,参数传进去对象和模板,自动生成XML,XML生成对象,参数1传对象引用，参数2传XML字符串或者报文二进制
#       如果存在继承关系,在实体关系里写明
#-----
#   功能:
#-----
#-------------------------------------------------
QT       += core xml
QT       -= gui

TARGET = TransMsgLib
TEMPLATE = lib
#去掉Qt Creator问题页签输出警告
#CONFIG += warn_off

DEFINES += TRANSMSGLIB_LIBRARY

SOURCES += \
    core/serializable.cpp \
    basicinfo.cpp \
    taskinfo.cpp \
    filedownload.cpp \
    ftppush.cpp \
    httppush.cpp \
    commonfilesdownloadinfo.cpp \
    requnstructfilesdownloadinfo.cpp \
    err/transexception.cpp \
    core/validation.cpp \
    test.cpp \
    reqbridgeconn.cpp \
    respbridgeconn.cpp \
    replyinfo.cpp \
    reqheartthrobsconn.cpp \
    respheartthrobsconn.cpp \
    taskreplyinfo.cpp \
    respunstructfilesdownloadinfo.cpp \
    commonfilesexecstatus.cpp \
    requnstructfilesdownloadstatus.cpp \
    respunstructfilesdownloadstatus.cpp \
    commonfilesexecinfo.cpp \
    reqstructfilesdownloadinfo.cpp \
    respstructfilesdownloadinfo.cpp \
    reqstructfilesdownloadstatus.cpp \
    respstructfilesdownloadstatus.cpp \
    reqstructtaskexecstatus.cpp \
    respstructtaskexecstatus.cpp \
    reqscheduletaskdownloadinfo.cpp \
    respscheduletaskdownloadinfo.cpp \
    reqscheduletaskdownloadstatus.cpp \
    respscheduletaskdownloadstatus.cpp \
    reqscheduletaskexecstatus.cpp \
    respscheduletaskexecstatus.cpp \
    monitoringindicatorinfo.cpp \
    reqmonitoringindicatorinfo.cpp \
    respmonitoringindicatorinfo.cpp \
    indicator.cpp \
    indicatorinfo.cpp \
    reqmonitoringindicatorstatus.cpp \
    reqremoteuioperacentorconn.cpp \
    respmonitoringindicatorstatus.cpp \
    respremoteuioperacentorconn.cpp \
    remoteoperabaseinfo.cpp \
    reqremoteuioperacentorinfo.cpp \
    respremoteuioperacentorinfo.cpp \
    datagraminfo.cpp \
    core/messageinfo.cpp \
    resultinfo.cpp \
    result.cpp

HEADERS +=\
        transmsglib_global.h \
    core/serializable.h \
    basicinfo.h \
    taskinfo.h \
    filedownload.h \
    ftppush.h \
    httppush.h \
    commonfilesdownloadinfo.h \
    requnstructfilesdownloadinfo.h \
    err/transexception.h \
    core/validation.h \
    reqbridgeconn.h \
    respbridgeconn.h \
    replyinfo.h \
    reqheartthrobsconn.h \
    respheartthrobsconn.h \
    taskreplyinfo.h \
    respunstructfilesdownloadinfo.h \
    commonfilesexecstatus.h \
    requnstructfilesdownloadstatus.h \
    respunstructfilesdownloadstatus.h \
    commonfilesexecinfo.h \
    reqstructfilesdownloadinfo.h \
    respstructfilesdownloadinfo.h \
    reqstructfilesdownloadstatus.h \
    respstructfilesdownloadstatus.h \
    reqstructtaskexecstatus.h \
    respstructtaskexecstatus.h \
    reqscheduletaskdownloadinfo.h \
    respscheduletaskdownloadinfo.h \
    reqscheduletaskdownloadstatus.h \
    respscheduletaskdownloadstatus.h \
    reqscheduletaskexecstatus.h \
    respscheduletaskexecstatus.h \
    monitoringindicatorinfo.h \
    reqmonitoringindicatorinfo.h \
    respmonitoringindicatorinfo.h \
    indicator.h \
    indicatorinfo.h \
    reqmonitoringindicatorstatus.h \
    reqremoteuioperacentorconn.h \
    respmonitoringindicatorstatus.h \
    respremoteuioperacentorconn.h \
    remoteoperabaseinfo.h \
    reqremoteuioperacentorinfo.h \
    respremoteuioperacentorinfo.h \
    transmsg.h \
    datagraminfo.h \
    core/messageinfo.h \
    resultinfo.h \
    result.h

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



