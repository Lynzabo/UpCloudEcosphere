#-------------------------------------------------
#
#   上云科技应用支撑封装--数据库接口封装库
#
#   版权:  C/C++ development team
#   时间:       2015-07-14 14:27:06
#   注意:  
#           1.项目中只使用Oracle12c/MySQL6/SQLite3
#           2.SQL语句都不区分大小
#           3.尽量不用拼写SQL,使用占位符号:
#-----
#   功能:
#           以下4点功能对所有数据库都是有效,使用前请生成对应环境驱动
#           1.带有连接池的数据库的查询(看test.cpp和userdao.cpp代码)
#           2.带有连接池的数据库的事务操作(看test.cpp和userdao.cpp代码)
#           3.使用连接池的书写传统Qt封装库操作数据库(看test.cpp)
#           4.使用连接池的书写传统Qt数据库模型类 (看test.cpp)
#-----
#-------------------------------------------------
QT      += sql
QT       -= gui

TARGET = DatabaseLib
TEMPLATE = lib

DEFINES += DATABASELIB_LIBRARY

SOURCES += \
    dbquery.cpp \
    dbtransaction.cpp \
    db/conf/databaseconf.cpp \
    test.cpp \
    db/connectionpool.cpp \
    db/err/dbexecption.cpp \
    test/user/dao/userdao.cpp \
    test/user/bean/user.cpp \
    databasemeta.cpp

HEADERS +=\
        databaselib_global.h \
    dbquery.h \
    dbtransaction.h \
    db/conf/databaseconf.h \
    db/connectionpool.h \
    db/err/dbexecption.h \
    test/user/dao/userdao.h \
    test/user/bean/user.h \
    db.h \
    databasemeta.h

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

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../ERMLib/release/ -lERMLib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../ERMLib/debug/ -lERMLib
else:unix: LIBS += -L$$OUT_PWD/../ERMLib/ -lERMLib

INCLUDEPATH += $$PWD/../ERMLib
DEPENDPATH += $$PWD/../ERMLib

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../AvroLib/release/ -lAvroLib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../AvroLib/debug/ -lAvroLib
else:unix: LIBS += -L$$OUT_PWD/../AvroLib/ -lAvroLib

INCLUDEPATH += $$PWD/../AvroLib
DEPENDPATH += $$PWD/../AvroLib
