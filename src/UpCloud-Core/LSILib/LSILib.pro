#-------------------------------------------------
#
#   上云科技应用支撑封装--本地服务接口类库
#
#   版权:  C/C++ development team
#   时间:       2015-07-14 14:27:06
#   注意:
#-----
#   功能:
#           1.提供本地文件系统操作常用功能
#           2.提供本地硬件操作功能
#           3.提供本地软件操作功能
#           4.提供本地常用设置功能
#           5.等等本地常用操作功能
#-----
#-------------------------------------------------

QT       -= gui

TARGET = LSILib
TEMPLATE = lib

DEFINES += LSILIB_LIBRARY

SOURCES += \
    fiopool.cpp \
    hardwareepool.cpp \
    softwareepool.cpp \
    fio/del/delpool.cpp \
    fio/del/core/delonegroupthread.cpp \
    fio/fiopoolimpl.cpp

HEADERS +=\
        lsilib_global.h \
    fiopool.h \
    hardwareepool.h \
    softwareepool.h \
    lsi.h \
    fio/del/delpool.h \
    fio/del/core/delonegroupthread.h \
    fio/fiopoolimpl.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../BaseLib/release/ -lBaseLib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../BaseLib/debug/ -lBaseLib
else:unix: LIBS += -L$$OUT_PWD/../BaseLib/ -lBaseLib

INCLUDEPATH += $$PWD/../BaseLib
DEPENDPATH += $$PWD/../BaseLib
