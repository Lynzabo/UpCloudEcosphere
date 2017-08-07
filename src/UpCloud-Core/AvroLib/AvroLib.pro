#-------------------------------------------------
#
#   上云科技应用支撑封装--数据序列化和反序列化
#
#   版权:  C/C++ development team
#   时间:       2015-07-14 14:27:06
#-----
#   功能:
#-----
#-------------------------------------------------

QT       -= gui

TARGET = AvroLib
TEMPLATE = lib

DEFINES += AVROLIB_LIBRARY

SOURCES += \
    binary/binary.cpp \
#    binary/test/person/person.cpp \
#    binary/test/person/student.cpp \
    binary/test.cpp \
    json/json.cpp \
    json/test.cpp \
    json/test/person.cpp \
    json/excep/jsonexception.cpp

HEADERS +=\
        avrolib_global.h \
    binary/binary.h \
#    binary/test/person/person.h \
#    binary/test/person/student.h \
    json/json.h \
    json/test/person.h \
    avro.h \
    json/excep/jsonexception.h

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
