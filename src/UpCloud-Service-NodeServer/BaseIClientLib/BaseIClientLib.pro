#-------------------------------------------------
#
# Project created by QtCreator 2015-09-16T10:21:34
#
#-------------------------------------------------

QT       -= gui

TARGET = BaseIClientLib
TEMPLATE = lib

DEFINES += BASEICLIENTLIB_LIBRARY

SOURCES += \
    clientconf.cpp \
    netconf.cpp \
    nsabstpath.cpp \
    util/datagramutil.cpp \
    util/terminaluuidutil.cpp

HEADERS +=\
        baseiclientlib_global.h \
    clientconf.h \
    baseiclient.h \
    netconf.h \
    nsabstpath.h \
    util/datagramutil.h \
    util/terminaluuidutil.h

unix {
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
