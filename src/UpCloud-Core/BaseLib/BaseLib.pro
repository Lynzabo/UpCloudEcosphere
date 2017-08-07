#-------------------------------------------------
#
#   上云科技应用支撑封装--基本配置
#
#   版权:  C/C++ development team
#   时间:       2015-07-14 14:27:06
#   注意:  所有应用关系到路径,都用"/",不能使用"\\"
#-----
#   功能:
#           1.生态圈日志分级(具体使用方法看test.cpp代码片段)
#           2.生态圈tr编码统一(具体使用方法看test.cpp代码片段)
#           3.应用目录位置返回
#           4.多线程安全的单例模板定义,在core/singleton.h文件定义，使用方法参考computerinfo.h,所有单例使用完后release,并考虑多线程的安全
#-----
#-------------------------------------------------
QT      += network
QT      -= gui

TARGET = BaseLib
TEMPLATE = lib

DEFINES += BASELIB_LIBRARY

SOURCES += \
    unicode.cpp \
    logger.cpp \
    filemanager.cpp \
    test.cpp \
    util/timerutil.cpp \
    util/uuidutil.cpp \
    util/pathutil.cpp \
    util/i18nutil.cpp \
    util/styleutil.cpp \
    abstpath.cpp \
    util/mdutil.cpp \
    util/stringutil.cpp \
    util/computerinfo.cpp \
    util/hardlink.cpp \
    util/dirutil.cpp \
    util/macutil.cpp

HEADERS +=\
        baselib_global.h \
    unicode.h \
    constant.h \
    logger.h \
    filemanager.h \
    base.h \
    core/singleton.h \
    util/timerutil.h \
    util/uuidutil.h \
    util/pathutil.h \
    util/i18nutil.h \
    util/styleutil.h \
    abstpath.h \
    util/mdutil.h \
    util/stringutil.h \
    util/computerinfo.h \
    util/hardlink.h \
    util/dirutil.h \
    util/macutil.h

unix {
    CONFIG += c++11
    target.path = /usr/lib
    INSTALLS += target
}

DISTFILES += \
    C:/UpCloud-package/conf/CenterServer-db.conf \
    C:/UpCloud-package/conf/CenterServer-logger.conf \
    C:/UpCloud-package/conf/CenterServer-server.conf \
    C:/UpCloud-package/conf/NodeServer-client.conf \
    C:/UpCloud-package/conf/NodeServer-db.conf \
    C:/UpCloud-package/conf/NodeServer-logger.conf \
    C:/UpCloud-package/conf/NodeServer-serialport.conf \
    C:/UpCloud-package/conf/source.conf


