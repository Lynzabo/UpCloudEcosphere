#-------------------------------------------------
#
#   上云科技中心服务服务启动
#
#   版权:  C/C++ development team
#   时间:       2015-07-14 14:27:06
#
#-------------------------------------------------

QT       += core network sql

QT       -= gui

TARGET = StartServer
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

unix {
    CONFIG += c++11
    target.path = /usr/lib
    INSTALLS += target
}
SOURCES += main.cpp

HEADERS += \
    actionregistry.h \
    remoteuioperaregistry.h

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../UpCloud-Core/BaseLib/release/ -lBaseLib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../UpCloud-Core/BaseLib/debug/ -lBaseLib
else:unix: LIBS += -L$$OUT_PWD/../../UpCloud-Core/BaseLib/ -lBaseLib

INCLUDEPATH += $$PWD/../../UpCloud-Core/BaseLib
DEPENDPATH += $$PWD/../../UpCloud-Core/BaseLib

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

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../UpCloud-Core/TimerLib/release/ -lTimerLib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../UpCloud-Core/TimerLib/debug/ -lTimerLib
else:unix: LIBS += -L$$OUT_PWD/../../UpCloud-Core/TimerLib/ -lTimerLib

INCLUDEPATH += $$PWD/../../UpCloud-Core/TimerLib
DEPENDPATH += $$PWD/../../UpCloud-Core/TimerLib

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../UpCloud-Core/DatabaseLib/release/ -lDatabaseLib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../UpCloud-Core/DatabaseLib/debug/ -lDatabaseLib
else:unix: LIBS += -L$$OUT_PWD/../../UpCloud-Core/DatabaseLib/ -lDatabaseLib

INCLUDEPATH += $$PWD/../../UpCloud-Core/DatabaseLib
DEPENDPATH += $$PWD/../../UpCloud-Core/DatabaseLib


win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../BaseIServerLib/release/ -lBaseIServerLib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../BaseIServerLib/debug/ -lBaseIServerLib
else:unix: LIBS += -L$$OUT_PWD/../BaseIServerLib/ -lBaseIServerLib

INCLUDEPATH += $$PWD/../BaseIServerLib
DEPENDPATH += $$PWD/../BaseIServerLib

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../NetIServerLib/release/ -lNetIServerLib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../NetIServerLib/debug/ -lNetIServerLib
else:unix: LIBS += -L$$OUT_PWD/../NetIServerLib/ -lNetIServerLib

INCLUDEPATH += $$PWD/../NetIServerLib
DEPENDPATH += $$PWD/../NetIServerLib

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../TimerIServerLib/release/ -lTimerIServerLib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../TimerIServerLib/debug/ -lTimerIServerLib
else:unix: LIBS += -L$$OUT_PWD/../TimerIServerLib/ -lTimerIServerLib

INCLUDEPATH += $$PWD/../TimerIServerLib
DEPENDPATH += $$PWD/../TimerIServerLib

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../BusinessIServer/UnstructIServer/release/ -lUnstructIServer
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../BusinessIServer/UnstructIServer/debug/ -lUnstructIServer
else:unix: LIBS += -L$$OUT_PWD/../BusinessIServer/UnstructIServer/ -lUnstructIServer

INCLUDEPATH += $$PWD/../BusinessIServer/UnstructIServer
DEPENDPATH += $$PWD/../BusinessIServer/UnstructIServer

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../BusinessIServer/StructIServer/release/ -lStructIServer
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../BusinessIServer/StructIServer/debug/ -lStructIServer
else:unix: LIBS += -L$$OUT_PWD/../BusinessIServer/StructIServer/ -lStructIServer

INCLUDEPATH += $$PWD/../BusinessIServer/StructIServer
DEPENDPATH += $$PWD/../BusinessIServer/StructIServer

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../BusinessIServer/ScheduleIServer/release/ -lScheduleIServer
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../BusinessIServer/ScheduleIServer/debug/ -lScheduleIServer
else:unix: LIBS += -L$$OUT_PWD/../BusinessIServer/ScheduleIServer/ -lScheduleIServer

INCLUDEPATH += $$PWD/../BusinessIServer/ScheduleIServer
DEPENDPATH += $$PWD/../BusinessIServer/ScheduleIServer

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../BusinessIServer/HthrobsIServer/release/ -lHthrobsIServer
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../BusinessIServer/HthrobsIServer/debug/ -lHthrobsIServer
else:unix: LIBS += -L$$OUT_PWD/../BusinessIServer/HthrobsIServer/ -lHthrobsIServer

INCLUDEPATH += $$PWD/../BusinessIServer/HthrobsIServer
DEPENDPATH += $$PWD/../BusinessIServer/HthrobsIServer

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../BusinessIServer/OperaIServer/release/ -lOperaIServer
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../BusinessIServer/OperaIServer/debug/ -lOperaIServer
else:unix: LIBS += -L$$OUT_PWD/../BusinessIServer/OperaIServer/ -lOperaIServer

INCLUDEPATH += $$PWD/../BusinessIServer/OperaIServer
DEPENDPATH += $$PWD/../BusinessIServer/OperaIServer

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../FrontBusinessIServer/DDMIServer/UnstructOperaIServer/release/ -lUnstructOperaIServer
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../FrontBusinessIServer/DDMIServer/UnstructOperaIServer/debug/ -lUnstructOperaIServer
else:unix: LIBS += -L$$OUT_PWD/../FrontBusinessIServer/DDMIServer/UnstructOperaIServer/ -lUnstructOperaIServer

INCLUDEPATH += $$PWD/../FrontBusinessIServer/DDMIServer/UnstructOperaIServer
DEPENDPATH += $$PWD/../FrontBusinessIServer/DDMIServer/UnstructOperaIServer

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../UpCloud-Core/ERMLib/release/ -lERMLib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../UpCloud-Core/ERMLib/debug/ -lERMLib
else:unix: LIBS += -L$$OUT_PWD/../../UpCloud-Core/ERMLib/ -lERMLib

INCLUDEPATH += $$PWD/../../UpCloud-Core/ERMLib
DEPENDPATH += $$PWD/../../UpCloud-Core/ERMLib

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../UpCloud-Core/AvroLib/release/ -lAvroLib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../UpCloud-Core/AvroLib/debug/ -lAvroLib
else:unix: LIBS += -L$$OUT_PWD/../../UpCloud-Core/AvroLib/ -lAvroLib

INCLUDEPATH += $$PWD/../../UpCloud-Core/AvroLib
DEPENDPATH += $$PWD/../../UpCloud-Core/AvroLib

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../FrontBusinessIServer/BasalOperaIServer/release/ -lBasalOperaIServer
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../FrontBusinessIServer/BasalOperaIServer/debug/ -lBasalOperaIServer
else:unix: LIBS += -L$$OUT_PWD/../FrontBusinessIServer/BasalOperaIServer/ -lBasalOperaIServer

INCLUDEPATH += $$PWD/../FrontBusinessIServer/BasalOperaIServer
DEPENDPATH += $$PWD/../FrontBusinessIServer/BasalOperaIServer


win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../BusinessIServer/StructIServer/release/ -lStructIServer
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../BusinessIServer/StructIServer/debug/ -lStructIServer
else:unix: LIBS += -L$$OUT_PWD/../BusinessIServer/StructIServer/ -lStructIServer

INCLUDEPATH += $$PWD/../BusinessIServer/StructIServer
DEPENDPATH += $$PWD/../BusinessIServer/StructIServer

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../FrontBusinessIServer/DDMIServer/StructOperaIServer/release/ -lStructOperaIServer
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../FrontBusinessIServer/DDMIServer/StructOperaIServer/debug/ -lStructOperaIServer
else:unix: LIBS += -L$$OUT_PWD/../FrontBusinessIServer/DDMIServer/StructOperaIServer/ -lStructOperaIServer

INCLUDEPATH += $$PWD/../FrontBusinessIServer/DDMIServer/StructOperaIServer
DEPENDPATH += $$PWD/../FrontBusinessIServer/DDMIServer/StructOperaIServer

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../FrontBusinessIServer/DDMIServer/ScheduleOperaIServer/release/ -lScheduleOperaIServer
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../FrontBusinessIServer/DDMIServer/ScheduleOperaIServer/debug/ -lScheduleOperaIServer
else:unix: LIBS += -L$$OUT_PWD/../FrontBusinessIServer/DDMIServer/ScheduleOperaIServer/ -lScheduleOperaIServer

INCLUDEPATH += $$PWD/../FrontBusinessIServer/DDMIServer/ScheduleOperaIServer
DEPENDPATH += $$PWD/../FrontBusinessIServer/DDMIServer/ScheduleOperaIServer



win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../DuplexLib/release/ -lDuplexLib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../DuplexLib/debug/ -lDuplexLib
else:unix: LIBS += -L$$OUT_PWD/../DuplexLib/ -lDuplexLib

INCLUDEPATH += $$PWD/../DuplexLib
DEPENDPATH += $$PWD/../DuplexLib

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
