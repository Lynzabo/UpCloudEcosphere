#-------------------------------------------------
#
#   上云科技应用支撑封装--实体远程映射(Entity  Remote Mapping)
#
#   版权:  C/C++ development team
#   时间:       2015-07-14 14:27:06
#-----
#   功能:
#
#-----
#-------------------------------------------------

QT       -= gui

TARGET = ERMLib
TEMPLATE = lib

DEFINES += ERMLIB_LIBRARY

SOURCES += \    
    corepojo.cpp \
    page.cpp \
    util/pageutil.cpp \
    treenode.cpp

HEADERS +=\
        ermlib_global.h \    
    erm.h \
    corepojo.h \
    page.h \
    util/pageutil.h \
    treenode.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../BaseLib/release/ -lBaseLib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../BaseLib/debug/ -lBaseLib
else:unix: LIBS += -L$$OUT_PWD/../BaseLib/ -lBaseLib

INCLUDEPATH += $$PWD/../BaseLib
DEPENDPATH += $$PWD/../BaseLib

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../AvroLib/release/ -lAvroLib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../AvroLib/debug/ -lAvroLib
else:unix: LIBS += -L$$OUT_PWD/../AvroLib/ -lAvroLib

INCLUDEPATH += $$PWD/../AvroLib
DEPENDPATH += $$PWD/../AvroLib
