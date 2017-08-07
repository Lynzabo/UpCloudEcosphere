#-------------------------------------------------
#
# Project created by QtCreator 2015-07-14T14:46:19
#
#-------------------------------------------------

QT       += core sql network serialport

QT       -= gui

TARGET = UnitTest
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

unix {
    CONFIG += c++11
    target.path = /usr/lib
    INSTALLS += target
}

SOURCES += main.cpp \    

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../BaseLib/release/ -lBaseLib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../BaseLib/debug/ -lBaseLib
else:unix: LIBS += -L$$OUT_PWD/../BaseLib/ -lBaseLib

INCLUDEPATH += $$PWD/../BaseLib
DEPENDPATH += $$PWD/../BaseLib

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../DatabaseLib/release/ -lDatabaseLib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../DatabaseLib/debug/ -lDatabaseLib
else:unix: LIBS += -L$$OUT_PWD/../DatabaseLib/ -lDatabaseLib

INCLUDEPATH += $$PWD/../DatabaseLib
DEPENDPATH += $$PWD/../DatabaseLib

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../NetLib/release/ -lNetLib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../NetLib/debug/ -lNetLib
else:unix: LIBS += -L$$OUT_PWD/../NetLib/ -lNetLib

INCLUDEPATH += $$PWD/../NetLib
DEPENDPATH += $$PWD/../NetLib

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../TransMsgLib/release/ -lTransMsgLib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../TransMsgLib/debug/ -lTransMsgLib
else:unix: LIBS += -L$$OUT_PWD/../TransMsgLib/ -lTransMsgLib

INCLUDEPATH += $$PWD/../TransMsgLib
DEPENDPATH += $$PWD/../TransMsgLib


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
