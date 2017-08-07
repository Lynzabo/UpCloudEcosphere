#-------------------------------------------------
#
# Project created by QtCreator 2015-09-16T10:18:14
#
#-------------------------------------------------
QT       += sql network
QT       -= gui

TARGET = BaseIServerLib
TEMPLATE = lib

DEFINES += BASEISERVERLIB_LIBRARY

SOURCES += \
    serverconf.cpp \
    csabstpath.cpp \
    util/datagramutil.cpp \
    bean/csterminal.cpp \
    dao/csterminaldao.cpp \
    util/terminalkeyutil.cpp \
    util/terminaluuidutil.cpp \
    createftpfileinfo.cpp

HEADERS +=\
        baseiserverlib_global.h \
    serverconf.h \
    baseiserver.h \
    csabstpath.h \
    util/datagramutil.h \
    bean/csterminal.h \
    dao/csterminaldao.h \
    util/terminalkeyutil.h \
    util/terminaluuidutil.h \
    createftpfileinfo.h

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

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../UpCloud-Core/TransMsgLib/release/ -lTransMsgLib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../UpCloud-Core/TransMsgLib/debug/ -lTransMsgLib
else:unix: LIBS += -L$$OUT_PWD/../../UpCloud-Core/TransMsgLib/ -lTransMsgLib

INCLUDEPATH += $$PWD/../../UpCloud-Core/TransMsgLib
DEPENDPATH += $$PWD/../../UpCloud-Core/TransMsgLib

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../UpCloud-Core/EnDecryptLib/release/ -lEnDecryptLib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../UpCloud-Core/EnDecryptLib/debug/ -lEnDecryptLib
else:unix: LIBS += -L$$OUT_PWD/../../UpCloud-Core/EnDecryptLib/ -lEnDecryptLib

INCLUDEPATH += $$PWD/../../UpCloud-Core/EnDecryptLib
DEPENDPATH += $$PWD/../../UpCloud-Core/EnDecryptLib

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../UpCloud-Core/DatabaseLib/release/ -lDatabaseLib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../UpCloud-Core/DatabaseLib/debug/ -lDatabaseLib
else:unix: LIBS += -L$$OUT_PWD/../../UpCloud-Core/DatabaseLib/ -lDatabaseLib

INCLUDEPATH += $$PWD/../../UpCloud-Core/DatabaseLib
DEPENDPATH += $$PWD/../../UpCloud-Core/DatabaseLib

#win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../UpCloud-Core/ERMLib/release/ -lERMLib
#else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../UpCloud-Core/ERMLib/debug/ -lERMLib
#else:unix: LIBS += -L$$OUT_PWD/../../UpCloud-Core/ERMLib/ -lERMLib

INCLUDEPATH += $$PWD/../../UpCloud-Core/ERMLib
#DEPENDPATH += $$PWD/../../UpCloud-Core/ERMLib

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../UpCloud-Core/AvroLib/release/ -lAvroLib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../UpCloud-Core/AvroLib/debug/ -lAvroLib
else:unix: LIBS += -L$$OUT_PWD/../../UpCloud-Core/AvroLib/ -lAvroLib

INCLUDEPATH += $$PWD/../../UpCloud-Core/AvroLib
DEPENDPATH += $$PWD/../../UpCloud-Core/AvroLib
