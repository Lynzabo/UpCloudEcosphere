#-------------------------------------------------
#
# Project created by QtCreator 2015-07-29T15:59:25
#
#-------------------------------------------------

QT       += core network sql

QT       -= gui

TARGET = StartClient
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

unix {
    CONFIG += c++11
    target.path = /usr/lib
    INSTALLS += target
}


SOURCES += main.cpp

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../UpCloud-Core/BaseLib/release/ -lBaseLib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../UpCloud-Core/BaseLib/debug/ -lBaseLib
else:unix: LIBS += -L$$OUT_PWD/../../UpCloud-Core/BaseLib/ -lBaseLib

INCLUDEPATH += $$PWD/../../UpCloud-Core/BaseLib
DEPENDPATH += $$PWD/../../UpCloud-Core/BaseLib

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../NetIClientLib/release/ -lNetIClientLib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../NetIClientLib/debug/ -lNetIClientLib
else:unix: LIBS += -L$$OUT_PWD/../NetIClientLib/ -lNetIClientLib

INCLUDEPATH += $$PWD/../NetIClientLib
DEPENDPATH += $$PWD/../NetIClientLib

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../UpCloud-Core/NetLib/release/ -lNetLib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../UpCloud-Core/NetLib/debug/ -lNetLib
else:unix: LIBS += -L$$OUT_PWD/../../UpCloud-Core/NetLib/ -lNetLib

INCLUDEPATH += $$PWD/../../UpCloud-Core/NetLib
DEPENDPATH += $$PWD/../../UpCloud-Core/NetLib

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../UpCloud-Core/TransMsgLib/release/ -lTransMsgLib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../UpCloud-Core/TransMsgLib/debug/ -lTransMsgLib
else:unix: LIBS += -L$$OUT_PWD/../../UpCloud-Core/TransMsgLib/ -lTransMsgLib

INCLUDEPATH += $$PWD/../../UpCloud-Core/TransMsgLib
DEPENDPATH += $$PWD/../../UpCloud-Core/TransMsgLib

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../UpCloud-Core/ActionLib/release/ -lActionLib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../UpCloud-Core/ActionLib/debug/ -lActionLib
else:unix: LIBS += -L$$OUT_PWD/../../UpCloud-Core/ActionLib/ -lActionLib

INCLUDEPATH += $$PWD/../../UpCloud-Core/ActionLib
DEPENDPATH += $$PWD/../../UpCloud-Core/ActionLib

HEADERS += \
    actionregistry.h


win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../UpCloud-Core/TimerLib/release/ -lTimerLib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../UpCloud-Core/TimerLib/debug/ -lTimerLib
else:unix: LIBS += -L$$OUT_PWD/../../UpCloud-Core/TimerLib/ -lTimerLib

INCLUDEPATH += $$PWD/../../UpCloud-Core/TimerLib
DEPENDPATH += $$PWD/../../UpCloud-Core/TimerLib


win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../BusinessIClient/HthrobsIClient/release/ -lHthrobsIClient
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../BusinessIClient/HthrobsIClient/debug/ -lHthrobsIClient
else:unix: LIBS += -L$$OUT_PWD/../BusinessIClient/HthrobsIClient/ -lHthrobsIClient

INCLUDEPATH += $$PWD/../BusinessIClient/HthrobsIClient
DEPENDPATH += $$PWD/../BusinessIClient/HthrobsIClient

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../TimerIClientLib/release/ -lTimerIClientLib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../TimerIClientLib/debug/ -lTimerIClientLib
else:unix: LIBS += -L$$OUT_PWD/../TimerIClientLib/ -lTimerIClientLib

INCLUDEPATH += $$PWD/../TimerIClientLib
DEPENDPATH += $$PWD/../TimerIClientLib



win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../UpCloud-Core/DatabaseLib/release/ -lDatabaseLib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../UpCloud-Core/DatabaseLib/debug/ -lDatabaseLib
else:unix: LIBS += -L$$OUT_PWD/../../UpCloud-Core/DatabaseLib/ -lDatabaseLib

INCLUDEPATH += $$PWD/../../UpCloud-Core/DatabaseLib
DEPENDPATH += $$PWD/../../UpCloud-Core/DatabaseLib

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../BaseIClientLib/release/ -lBaseIClientLib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../BaseIClientLib/debug/ -lBaseIClientLib
else:unix: LIBS += -L$$OUT_PWD/../BaseIClientLib/ -lBaseIClientLib

INCLUDEPATH += $$PWD/../BaseIClientLib
DEPENDPATH += $$PWD/../BaseIClientLib

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../BusinessIClient/UnstructIClient/release/ -lUnstructIClient
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../BusinessIClient/UnstructIClient/debug/ -lUnstructIClient
else:unix: LIBS += -L$$OUT_PWD/../BusinessIClient/UnstructIClient/ -lUnstructIClient

INCLUDEPATH += $$PWD/../BusinessIClient/UnstructIClient
DEPENDPATH += $$PWD/../BusinessIClient/UnstructIClient

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../BusinessIClient/StructIClient/release/ -lStructIClient
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../BusinessIClient/StructIClient/debug/ -lStructIClient
else:unix: LIBS += -L$$OUT_PWD/../BusinessIClient/StructIClient/ -lStructIClient

INCLUDEPATH += $$PWD/../BusinessIClient/StructIClient
DEPENDPATH += $$PWD/../BusinessIClient/StructIClient


win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../BusinessIClient/ScheduleIClient/release/ -lScheduleIClient
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../BusinessIClient/ScheduleIClient/debug/ -lScheduleIClient
else:unix: LIBS += -L$$OUT_PWD/../BusinessIClient/ScheduleIClient/ -lScheduleIClient

INCLUDEPATH += $$PWD/../BusinessIClient/ScheduleIClient
DEPENDPATH += $$PWD/../BusinessIClient/ScheduleIClient

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../UpCloud-Core/AvroLib/release/ -lAvroLib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../UpCloud-Core/AvroLib/debug/ -lAvroLib
else:unix: LIBS += -L$$OUT_PWD/../../UpCloud-Core/AvroLib/ -lAvroLib

INCLUDEPATH += $$PWD/../../UpCloud-Core/AvroLib
DEPENDPATH += $$PWD/../../UpCloud-Core/AvroLib

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../UpCloud-Core/ERMLib/release/ -lERMLib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../UpCloud-Core/ERMLib/debug/ -lERMLib
else:unix: LIBS += -L$$OUT_PWD/../../UpCloud-Core/ERMLib/ -lERMLib

INCLUDEPATH += $$PWD/../../UpCloud-Core/ERMLib
DEPENDPATH += $$PWD/../../UpCloud-Core/ERMLib

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../UpCloud-Core/EnDecryptLib/release/ -lEnDecryptLib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../UpCloud-Core/EnDecryptLib/debug/ -lEnDecryptLib
else:unix: LIBS += -L$$OUT_PWD/../../UpCloud-Core/EnDecryptLib/ -lEnDecryptLib

INCLUDEPATH += $$PWD/../../UpCloud-Core/EnDecryptLib
DEPENDPATH += $$PWD/../../UpCloud-Core/EnDecryptLib

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../UpCloud-Core/WorkThreadPool/release/ -lWorkThreadPool
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../UpCloud-Core/WorkThreadPool/debug/ -lWorkThreadPool
else:unix: LIBS += -L$$OUT_PWD/../../UpCloud-Core/WorkThreadPool/ -lWorkThreadPool

INCLUDEPATH += $$PWD/../../UpCloud-Core/WorkThreadPool
DEPENDPATH += $$PWD/../../UpCloud-Core/WorkThreadPool
