#-------------------------------------------------
#
#   上云科技应用支撑封装--动作接口封装
#
#   版权:  C/C++ development team
#   时间:       2015-07-14 14:27:06
#-----
#   功能:
#           1.待完成后书写
#-----
#-------------------------------------------------
QT       += core network
QT       -= gui

TARGET = ActionLib
TEMPLATE = lib

DEFINES += ACTIONLIB_LIBRARY

SOURCES += \
    request/core/request.cpp \
    response/core/response.cpp \
    request/abstractrequest.cpp \
    response/abstractresponse.cpp \
    response/factory/responsefactory.cpp \
    filter/core/filter.cpp \
    filter/taskschedulerfilter.cpp \
    filter/chain/taskschedulerchain.cpp \
    filter/chain/core/chain.cpp \
    context/requestcontext.cpp \
    context/responsecontext.cpp \
    filter/registry/actionregistryfactory.cpp

HEADERS +=\
        actionlib_global.h \
    request/core/request.h \
    response/core/response.h \
    request/abstractrequest.h \
    response/abstractresponse.h \
    response/factory/responsefactory.h \
    action.h \
    filter/core/filter.h \
    filter/taskschedulerfilter.h \
    filter/chain/taskschedulerchain.h \
    filter/chain/core/chain.h \
    context/requestcontext.h \
    context/responsecontext.h \
    filter/registry/actionregistryfactory.h

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
