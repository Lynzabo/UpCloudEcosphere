#-------------------------------------------------
#
#   上云科技应用支撑封装--消息队列
#
#   版权:  C/C++ development team
#   时间:       2015-07-14 14:27:06
#-----
#   功能:
#-----
#-------------------------------------------------

QT       -= gui

TARGET = MQLib
TEMPLATE = lib

DEFINES += MQLIB_LIBRARY

SOURCES += \
    core/producer.cpp \
    core/consumer.cpp \
    topic/messagetopic.cpp \
    mqpool.cpp \
    test.cpp

HEADERS +=\
        mqlib_global.h \
    core/producer.h \
    core/consumer.h \
    topic/messagetopic.h \
    mqpool.h \
    mq.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../BaseLib/release/ -lBaseLib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../BaseLib/debug/ -lBaseLib
else:unix: LIBS += -L$$OUT_PWD/../BaseLib/ -lBaseLib

INCLUDEPATH += $$PWD/../BaseLib
DEPENDPATH += $$PWD/../BaseLib
