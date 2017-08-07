#-------------------------------------------------
#
#   上云科技应用支撑封装--面向服务体系的系统间交互
#
#   版权:  C/C++ development team
#   时间:       2015-07-14 14:27:06
#   注意:
#-----
#   功能:
#-----
#-------------------------------------------------

QT       -= gui

TARGET = SOALib
TEMPLATE = lib

DEFINES += SOALIB_LIBRARY

SOURCES += \
    access/syspermission.cpp

HEADERS += soalib.h\
        soalib_global.h \
    access/syspermission.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../BaseLib/release/ -lBaseLib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../BaseLib/debug/ -lBaseLib
else:unix: LIBS += -L$$OUT_PWD/../BaseLib/ -lBaseLib

INCLUDEPATH += $$PWD/../BaseLib
DEPENDPATH += $$PWD/../BaseLib

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../BaseLib/release/ -lBaseLib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../BaseLib/debug/ -lBaseLib
else:unix: LIBS += -L$$OUT_PWD/../BaseLib/ -lBaseLib

INCLUDEPATH += $$PWD/../BaseLib
DEPENDPATH += $$PWD/../BaseLib
