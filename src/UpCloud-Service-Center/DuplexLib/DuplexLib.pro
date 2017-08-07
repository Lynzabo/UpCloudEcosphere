#-------------------------------------------------
#
#   上云科技应用支撑封装--中心节点远程UI客户端全双工工作封装
#
#   版权:  C/C++ development team
#   时间:       2015-07-14 14:27:06
#   注意:  所有应用关系到路径,都用"/",不能使用"\\"
#-----
#   功能:
#-----
#-------------------------------------------------
QT       += core network
QT       -= gui

TARGET = DuplexLib
TEMPLATE = lib

DEFINES += DUPLEXLIB_LIBRARY

SOURCES += \    
    server/interceptor/registry/fduplexregistryfactory.cpp \
    server/servlet/core/servlet.cpp \
    server/servlet/abstractservlet.cpp \
    server/context/drequestcontext.cpp \
    server/context/dresponsecontext.cpp \
    util/duplexutil.cpp \


HEADERS +=\
    duplexlib_global.h \
    duplex.h \    
    server/interceptor/registry/fduplexregistryfactory.h \
    server/servlet/core/servlet.h \
    server/servlet/abstractservlet.h \
    server/context/drequestcontext.h \
    server/context/dresponsecontext.h \
    util/duplexutil.h \


unix {
    CONFIG += c++11
    target.path = /usr/lib
    INSTALLS += target
}

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../UpCloud-Core/BaseLib/release/ -lBaseLib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../UpCloud-Core/BaseLib/debug/ -lBaseLib
else:unix: LIBS += -L$$OUT_PWD/../../UpCloud-Core/BaseLib/ -lBaseLib

INCLUDEPATH += $$PWD/../../UpCloud-Core/BaseLib
DEPENDPATH += $$PWD/../../UpCloud-Core/BaseLib

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../UpCloud-Core/ActionLib/release/ -lActionLib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../UpCloud-Core/ActionLib/debug/ -lActionLib
else:unix: LIBS += -L$$OUT_PWD/../../UpCloud-Core/ActionLib/ -lActionLib

INCLUDEPATH += $$PWD/../../UpCloud-Core/ActionLib
DEPENDPATH += $$PWD/../../UpCloud-Core/ActionLib


win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../UpCloud-Core/TransMsgLib/release/ -lTransMsgLib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../UpCloud-Core/TransMsgLib/debug/ -lTransMsgLib
else:unix: LIBS += -L$$OUT_PWD/../../UpCloud-Core/TransMsgLib/ -lTransMsgLib

INCLUDEPATH += $$PWD/../../UpCloud-Core/TransMsgLib
DEPENDPATH += $$PWD/../../UpCloud-Core/TransMsgLib


