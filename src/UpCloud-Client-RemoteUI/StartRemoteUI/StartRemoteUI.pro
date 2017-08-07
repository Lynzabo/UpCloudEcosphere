#-------------------------------------------------
#
#   上云科技运维监控分发管理客户端UI启动
#
#   版权:  C/C++ development team
#   时间:       2015-07-14 14:27:06
#
#-------------------------------------------------

QT       += core gui network axserver

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

##Set Style.qss can online edit
DEFINES += STYLE_DEBUG
#DEFINES += UPCLOUD_OCX

TARGET = StartRemoteUI
TEMPLATE = app
##include Common Module
include(./modules/common/commonUI.pri)

###include Basal Module
#dict
include(./modules/basal/dictUI/dictUI.pri)
#nodeserver group
include(./modules/basal/nsgroupUI/nsgroupUI.pri)

##include DDMI Module
#unstruct
include(./modules/ddmi/unstructUI/unstructUI.pri)
#unstruct
include(./modules/ddmi/structUI/structUI.pri)
#unstruct
include(./modules/ddmi/scheduleUI/scheduleUI.pri)


##include OMMI Module

##include common config Files
sources.files = common/qss common/imgs
INSTALLS += sources


#CODECFORSRC = UTF-8 #or GBK
#Windows Characteristic
win32: {
    #Prevent use MingGW compile
    mingw*: error("Doesn't Support MinGW! Please use MSVC compile program.And Version is 5.4.2")
    #Prevent use msvc compile
#    win32-msvc*: error("Doesn't Support MSVC! Please use MinGW GCC compile program.")
    #windows characteristic use
#    LIBS += -L./ -lqrencode -lQtShadowsocks -lbotan-$$BOTAN_VER -lzbar -liconv
}
#Linux Characteristic
unix: {
}

#QT version<5.4.2, prohibited to execute qmake
QT_VERSION = $$[QT_VERSION]#5.4.2
QT_VERSION = $$split(QT_VERSION, ".")#[5,4,2]
QT_VER_MAJ = $$member(QT_VERSION, 0)#5
QT_VER_MIN = $$member(QT_VERSION, 1)#4

lessThan(QT_VER_MAJ, 5) | lessThan(QT_VER_MIN, 4) {
        error(UpCloudEcosphere Systemm is only compiled under Qt 5.4.2!)
}
#indicate link qt library,it's a multi thread project,reduced output warning
CONFIG += qt thread warn_off

#Define UpCloud Application Global Constant Information
#OrganizationName
ORGANIZATIONNAME = UpCloud
#OrganizationDomain
ORGANIZATIONDOMAIN = upCloud.com
#ApplicationName
APPLICATIONNAME = $$TARGET
#Application version
APPLICATIONVERSION = 1.0.0

#Define Global Constant Information let source code can use
DEFINES   += UPCLOUD_REMOTEUI_ORGANIZATIONNAME=\\\"$$ORGANIZATIONNAME\\\"
DEFINES   += UPCLOUD_REMOTEUI_ORGANIZATIONDOMAIN=\\\"$$ORGANIZATIONDOMAIN\\\"
DEFINES   += UPCLOUD_REMOTEUI_APPLICATIONNAME=\\\"$$APPLICATIONNAME\\\"
DEFINES   += UPCLOUD_REMOTEUI_APPLICATIONVERSION=\\\"$$APPLICATIONVERSION\\\"

#Define Client Constant Directoryd
#ROOT = $$PWD/
COMMON_PATH = common
COMMON_FONT_PATH = $${COMMON_PATH}/font
COMMON_HTML_PATH = $${COMMON_PATH}/html
COMMON_I18N_PATH = $$COMMON_PATH/i18n
COMMON_IMGS_PATH = $$COMMON_PATH/imgs
COMMON_QSS_PATH = $$COMMON_PATH/qss
COMMON_SCRIPT_PATH = $$COMMON_PATH/script
#Define Global Constant Directory let source code can use
DEFINES   += UPCLOUD_REMOTEUI_ROOT=\\\"$$ROOT\\\"
DEFINES   += UPCLOUD_REMOTEUI_COMMON_PATH=\\\"$$COMMON_PATH\\\"
DEFINES   += UPCLOUD_REMOTEUI_COMMON_FONT_PATH=\\\"$$COMMON_FONT_PATH\\\"
DEFINES   += UPCLOUD_REMOTEUI_COMMON_HTML_PATH=\\\"$$COMMON_HTML_PATH\\\"
DEFINES   += UPCLOUD_REMOTEUI_COMMON_I18N_PATH=\\\"$$COMMON_I18N_PATH\\\"
DEFINES   += UPCLOUD_REMOTEUI_COMMON_IMGS_PATH=\\\"$$COMMON_IMGS_PATH\\\"
DEFINES   += UPCLOUD_REMOTEUI_COMMON_QSS_PATH=\\\"$$COMMON_QSS_PATH\\\"
DEFINES   += UPCLOUD_REMOTEUI_COMMON_SCRIPT_PATH=\\\"$$COMMON_SCRIPT_PATH\\\"


#cout Constant Directory
!isEmpty(QMAKESPEC) {
  message("QMAKESPEC: $$QMAKESPEC")
}
message("Project Path: $$PWD")
message("Common Path: $$COMMON_PATH")
message("Common HTML Path: $${COMMON_HTML_PATH}")
message("Common I18N Path: $${COMMON_I18N_PATH}")
message("Common IMGS Path: $${COMMON_IMGS_PATH}")
message("Common QSS Path: $${COMMON_QSS_PATH}")
message("Common SCRIPT Path: $${COMMON_SCRIPT_PATH}")

!exists($$COMMON_I18N_PATH/$${TARGET}_zh_CN.ts) {
    error("$${TARGET}_zh_CN.ts is not exist,Please use the Qt Linguist tool to generate the TS file!")
}
TRANSLATIONS = $$COMMON_I18N_PATH/$${TARGET}_zh_CN.ts

win32:RC_FILE=StartRemoteUI.rc


SOURCES += main.cpp\
    qtsingleapplication/qtlocalpeer.cpp \
    qtsingleapplication/qtlockedfile.cpp \
    qtsingleapplication/qtlockedfile_unix.cpp \
    qtsingleapplication/qtlockedfile_win.cpp \
    qtsingleapplication/qtsingleapplication.cpp \
    qtsingleapplication/qtsinglecoreapplication.cpp \
    #window.cpp \
    ../../UpCloud-Service-Center/BusinessIServer/UnstructIServer/bean/csrusendaddr.cpp \
    ../../UpCloud-Service-Center/BusinessIServer/UnstructIServer/bean/csrusendfiles.cpp \
    ../../UpCloud-Service-Center/BusinessIServer/UnstructIServer/bean/csrusendstatus.cpp \
    ../../UpCloud-Service-Center/BusinessIServer/UnstructIServer/bean/csrutask.cpp \
    ../../UpCloud-Service-Center/BusinessIServer/UnstructIServer/bean/cssusendaddr.cpp \
    ../../UpCloud-Service-Center/BusinessIServer/UnstructIServer/bean/cssusendfiles.cpp \
    ../../UpCloud-Service-Center/BusinessIServer/UnstructIServer/bean/cssutask.cpp \
    ../../UpCloud-Service-Center/BusinessIServer/BasalIServer/bean/csdict.cpp \
    ../../UpCloud-Service-Center/BusinessIServer/BasalIServer/bean/cscextendinfo.cpp \
    ../../UpCloud-Service-Center/BusinessIServer/BasalIServer/bean/cscgroup.cpp \
    ../../UpCloud-Service-Center/BusinessIServer/BasalIServer/bean/cscgroupassoc.cpp \
    ../../UpCloud-Service-Center/BusinessIServer/StructIServer/bean/csrssendaddr.cpp \
    ../../UpCloud-Service-Center/BusinessIServer/StructIServer/bean/csrssendfiles.cpp \
    ../../UpCloud-Service-Center/BusinessIServer/StructIServer/bean/csrssendstatus.cpp \
    ../../UpCloud-Service-Center/BusinessIServer/StructIServer/bean/csrstask.cpp \
    ../../UpCloud-Service-Center/BusinessIServer/StructIServer/bean/vcsassendfiles.cpp\
    remoteuiframework.cpp \
    remoteui.cpp \
    ../../UpCloud-Service-Center/BusinessIServer/ScheduleIServer/bean/csrscsendfiles.cpp \
    ../../UpCloud-Service-Center/BusinessIServer/ScheduleIServer/bean/csrscsendstatus.cpp \
    ../../UpCloud-Service-Center/BusinessIServer/ScheduleIServer/bean/csrsctask.cpp \
    ../../UpCloud-Service-Center/BusinessIServer/ScheduleIServer/bean/csrscsendaddr.cpp \
    ../../UpCloud-Service-Center/BusinessIServer/ScheduleIServer/bean/cssscsendaddr.cpp \
    ../../UpCloud-Service-Center/BusinessIServer/ScheduleIServer/bean/cssscsendfiles.cpp \
    ../../UpCloud-Service-Center/BusinessIServer/ScheduleIServer/bean/csssctask.cpp \
    ../../UpCloud-Service-Center/BusinessIServer/ScheduleIServer/bean/vcsascsendfiles.cpp \
    ../../UpCloud-Service-Center/BusinessIServer/UnstructIServer/bean/dtask.cpp \
    ../../UpCloud-Service-Center/BusinessIServer/UnstructIServer/bean/dtaskaddr.cpp \
    ../../UpCloud-Service-Center/BusinessIServer/UnstructIServer/bean/dtaskfile.cpp \
    ../../UpCloud-Service-Center/BusinessIServer/UnstructIServer/bean/vcsrusendaddr.cpp \
    ../../UpCloud-Service-Center/BusinessIServer/UnstructIServer/bean/vcsrusendfiles.cpp \
    ../../UpCloud-Service-Center/BusinessIServer/StructIServer/bean/cssssendaddr.cpp \
    ../../UpCloud-Service-Center/BusinessIServer/StructIServer/bean/cssssendfiles.cpp \
    ../../UpCloud-Service-Center/BusinessIServer/StructIServer/bean/cssstask.cpp \
    ../../UpCloud-Service-Center/BusinessIServer/StructIServer/bean/vcssendaddr.cpp \
    ../../UpCloud-Service-Center/BusinessIServer/BasalIServer/bean/vcscgroupassoc.cpp \
    ommimoduleui.cpp \
    ddmimoduleui.cpp
#    remoteuiwindow.cpp \

HEADERS  += \
    qtsingleapplication/qtlocalpeer.h \
    qtsingleapplication/QtLockedFile \
    qtsingleapplication/qtlockedfile.h \
    qtsingleapplication/QtSingleApplication \
    qtsingleapplication/qtsingleapplication.h \
    qtsingleapplication/qtsinglecoreapplication.h \
    actionregistry.h \
    #window.h \
    ../../UpCloud-Service-Center/BusinessIServer/UnstructIServer/bean/csrusendaddr.h \
    ../../UpCloud-Service-Center/BusinessIServer/UnstructIServer/bean/csrusendfiles.h \
    ../../UpCloud-Service-Center/BusinessIServer/UnstructIServer/bean/csrusendstatus.h \
    ../../UpCloud-Service-Center/BusinessIServer/UnstructIServer/bean/csrutask.h \
    ../../UpCloud-Service-Center/BusinessIServer/UnstructIServer/bean/cssusendaddr.h \
    ../../UpCloud-Service-Center/BusinessIServer/UnstructIServer/bean/cssusendfiles.h \
    ../../UpCloud-Service-Center/BusinessIServer/UnstructIServer/bean/cssutask.h \
    ../../UpCloud-Service-Center/BusinessIServer/BasalIServer/bean/csdict.h \
    ../../UpCloud-Service-Center/BusinessIServer/BasalIServer/bean/cscextendinfo.h \
    ../../UpCloud-Service-Center/BusinessIServer/BasalIServer/bean/cscgroup.h \
    ../../UpCloud-Service-Center/BusinessIServer/BasalIServer/bean/cscgroupassoc.h \
    ../../UpCloud-Service-Center/BusinessIServer/StructIServer/bean/csrssendaddr.h \
    ../../UpCloud-Service-Center/BusinessIServer/StructIServer/bean/csrssendfiles.h \
    ../../UpCloud-Service-Center/BusinessIServer/StructIServer/bean/csrssendstatus.h \
    ../../UpCloud-Service-Center/BusinessIServer/StructIServer/bean/csrstask.h \
    ../../UpCloud-Service-Center/BusinessIServer/StructIServer/bean/vcsassendfiles.h\
    remoteuiframework.h \
    remoteui.h \
    ../../UpCloud-Service-Center/BusinessIServer/ScheduleIServer/bean/csrscsendfiles.h \
    ../../UpCloud-Service-Center/BusinessIServer/ScheduleIServer/bean/csrscsendstatus.h \
    ../../UpCloud-Service-Center/BusinessIServer/ScheduleIServer/bean/csrsctask.h \
    ../../UpCloud-Service-Center/BusinessIServer/ScheduleIServer/bean/csrscsendaddr.h \
    ../../UpCloud-Service-Center/BusinessIServer/ScheduleIServer/bean/cssscsendaddr.h \
    ../../UpCloud-Service-Center/BusinessIServer/ScheduleIServer/bean/cssscsendfiles.h \
    ../../UpCloud-Service-Center/BusinessIServer/ScheduleIServer/bean/csssctask.h \
    ../../UpCloud-Service-Center/BusinessIServer/ScheduleIServer/bean/vcsascsendfiles.h \
    ../../UpCloud-Service-Center/BusinessIServer/UnstructIServer/bean/dtask.h \
    ../../UpCloud-Service-Center/BusinessIServer/UnstructIServer/bean/dtaskaddr.h \
    ../../UpCloud-Service-Center/BusinessIServer/UnstructIServer/bean/dtaskfile.h \
    ../../UpCloud-Service-Center/BusinessIServer/UnstructIServer/bean/vcsrusendaddr.h \
    ../../UpCloud-Service-Center/BusinessIServer/UnstructIServer/bean/vcsrusendfiles.h \
    ../../UpCloud-Service-Center/BusinessIServer/StructIServer/bean/cssssendaddr.h \
    ../../UpCloud-Service-Center/BusinessIServer/StructIServer/bean/cssssendfiles.h \
    ../../UpCloud-Service-Center/BusinessIServer/StructIServer/bean/cssstask.h \
    ../../UpCloud-Service-Center/BusinessIServer/StructIServer/bean/vcssendaddr.h \
    ../../UpCloud-Service-Center/BusinessIServer/BasalIServer/bean/vcscgroupassoc.h \
    ommimoduleui.h \
    ddmimoduleui.h
#    remoteuiwindow.h \

FORMS    += \
    window.ui \
    remoteuiframework.ui \
    ommimoduleui.ui \
    ddmimoduleui.ui

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../UpCloud-Core/BaseLib/release/ -lBaseLib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../UpCloud-Core/BaseLib/debug/ -lBaseLib
else:unix: LIBS += -L$$OUT_PWD/../../UpCloud-Core/BaseLib/ -lBaseLib

INCLUDEPATH += $$PWD/../../UpCloud-Core/BaseLib
DEPENDPATH += $$PWD/../../UpCloud-Core/BaseLib

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../BaseIRemoteLib/release/ -lBaseIRemoteLib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../BaseIRemoteLib/debug/ -lBaseIRemoteLib
else:unix: LIBS += -L$$OUT_PWD/../BaseIRemoteLib/ -lBaseIRemoteLib

INCLUDEPATH += $$PWD/../BaseIRemoteLib
DEPENDPATH += $$PWD/../BaseIRemoteLib

RESOURCES += \
    common/core.qrc \
    common/ddmi.qrc \
    common/ommi.qrc \
    common/basal.qrc

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../BusinessIRemote/HthrobsIRemote/release/ -lHthrobsIRemote
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../BusinessIRemote/HthrobsIRemote/debug/ -lHthrobsIRemote
else:unix: LIBS += -L$$OUT_PWD/../BusinessIRemote/HthrobsIRemote/ -lHthrobsIRemote

INCLUDEPATH += $$PWD/../BusinessIRemote/HthrobsIRemote
DEPENDPATH += $$PWD/../BusinessIRemote/HthrobsIRemote

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../UpCloud-Core/TimerLib/release/ -lTimerLib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../UpCloud-Core/TimerLib/debug/ -lTimerLib
else:unix: LIBS += -L$$OUT_PWD/../../UpCloud-Core/TimerLib/ -lTimerLib

INCLUDEPATH += $$PWD/../../UpCloud-Core/TimerLib
DEPENDPATH += $$PWD/../../UpCloud-Core/TimerLib

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../UpCloud-Core/TransMsgLib/release/ -lTransMsgLib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../UpCloud-Core/TransMsgLib/debug/ -lTransMsgLib
else:unix: LIBS += -L$$OUT_PWD/../../UpCloud-Core/TransMsgLib/ -lTransMsgLib

INCLUDEPATH += $$PWD/../../UpCloud-Core/TransMsgLib
DEPENDPATH += $$PWD/../../UpCloud-Core/TransMsgLib


win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../TimerIRemoteUILib/release/ -lTimerIRemoteUILib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../TimerIRemoteUILib/debug/ -lTimerIRemoteUILib
else:unix: LIBS += -L$$OUT_PWD/../TimerIRemoteUILib/ -lTimerIRemoteUILib

INCLUDEPATH += $$PWD/../TimerIRemoteUILib
DEPENDPATH += $$PWD/../TimerIRemoteUILib

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../UpCloud-Core/NetLib/release/ -lNetLib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../UpCloud-Core/NetLib/debug/ -lNetLib
else:unix: LIBS += -L$$OUT_PWD/../../UpCloud-Core/NetLib/ -lNetLib

INCLUDEPATH += $$PWD/../../UpCloud-Core/NetLib
DEPENDPATH += $$PWD/../../UpCloud-Core/NetLib

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../UpCloud-Core/ActionLib/release/ -lActionLib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../UpCloud-Core/ActionLib/debug/ -lActionLib
else:unix: LIBS += -L$$OUT_PWD/../../UpCloud-Core/ActionLib/ -lActionLib

INCLUDEPATH += $$PWD/../../UpCloud-Core/ActionLib
DEPENDPATH += $$PWD/../../UpCloud-Core/ActionLib

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../NetIRemoteUILib/release/ -lNetIRemoteUILib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../NetIRemoteUILib/debug/ -lNetIRemoteUILib
else:unix: LIBS += -L$$OUT_PWD/../NetIRemoteUILib/ -lNetIRemoteUILib

INCLUDEPATH += $$PWD/../NetIRemoteUILib
DEPENDPATH += $$PWD/../NetIRemoteUILib

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../BusinessIRemote/OperaIRemote/release/ -lOperaIRemote
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../BusinessIRemote/OperaIRemote/debug/ -lOperaIRemote
else:unix: LIBS += -L$$OUT_PWD/../BusinessIRemote/OperaIRemote/ -lOperaIRemote

INCLUDEPATH += $$PWD/../BusinessIRemote/OperaIRemote
DEPENDPATH += $$PWD/../BusinessIRemote/OperaIRemote

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../UpCloud-Core/AvroLib/release/ -lAvroLib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../UpCloud-Core/AvroLib/debug/ -lAvroLib
else:unix: LIBS += -L$$OUT_PWD/../../UpCloud-Core/AvroLib/ -lAvroLib

INCLUDEPATH += $$PWD/../../UpCloud-Core/AvroLib
DEPENDPATH += $$PWD/../../UpCloud-Core/AvroLib

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../FrontBusinessIRemoteUI/DDMIRemoteUI/UnstructOperaIRemoteUI/release/ -lUnstructOperaIRemoteUI
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../FrontBusinessIRemoteUI/DDMIRemoteUI/UnstructOperaIRemoteUI/debug/ -lUnstructOperaIRemoteUI
else:unix: LIBS += -L$$OUT_PWD/../FrontBusinessIRemoteUI/DDMIRemoteUI/UnstructOperaIRemoteUI/ -lUnstructOperaIRemoteUI

INCLUDEPATH += $$PWD/../FrontBusinessIRemoteUI/DDMIRemoteUI/UnstructOperaIRemoteUI
DEPENDPATH += $$PWD/../FrontBusinessIRemoteUI/DDMIRemoteUI/UnstructOperaIRemoteUI


win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../FrontBusinessIRemoteUI/BasalOperaIRemoteUI/release/ -lBasalOperaIRemoteUI
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../FrontBusinessIRemoteUI/BasalOperaIRemoteUI/debug/ -lBasalOperaIRemoteUI
else:unix: LIBS += -L$$OUT_PWD/../FrontBusinessIRemoteUI/BasalOperaIRemoteUI/ -lBasalOperaIRemoteUI

INCLUDEPATH += $$PWD/../FrontBusinessIRemoteUI/BasalOperaIRemoteUI
DEPENDPATH += $$PWD/../FrontBusinessIRemoteUI/BasalOperaIRemoteUI

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../FrontBusinessIRemoteUI/DDMIRemoteUI/StructOperaIRemoteUI/release/ -lStructOperaIRemoteUI
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../FrontBusinessIRemoteUI/DDMIRemoteUI/StructOperaIRemoteUI/debug/ -lStructOperaIRemoteUI
else:unix: LIBS += -L$$OUT_PWD/../FrontBusinessIRemoteUI/DDMIRemoteUI/StructOperaIRemoteUI/ -lStructOperaIRemoteUI

INCLUDEPATH += $$PWD/../FrontBusinessIRemoteUI/DDMIRemoteUI/StructOperaIRemoteUI
DEPENDPATH += $$PWD/../FrontBusinessIRemoteUI/DDMIRemoteUI/StructOperaIRemoteUI

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../FrontBusinessIRemoteUI/DDMIRemoteUI/ScheduleOperaIRemoteUI/release/ -lScheduleOperaIRemoteUI
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../FrontBusinessIRemoteUI/DDMIRemoteUI/ScheduleOperaIRemoteUI/debug/ -lScheduleOperaIRemoteUI
else:unix: LIBS += -L$$OUT_PWD/../FrontBusinessIRemoteUI/DDMIRemoteUI/ScheduleOperaIRemoteUI/ -lScheduleOperaIRemoteUI

INCLUDEPATH += $$PWD/../FrontBusinessIRemoteUI/DDMIRemoteUI/ScheduleOperaIRemoteUI
DEPENDPATH += $$PWD/../FrontBusinessIRemoteUI/DDMIRemoteUI/ScheduleOperaIRemoteUI

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

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../UpCloud-Core/ERMLib/release/ -lERMLib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../UpCloud-Core/ERMLib/debug/ -lERMLib
else:unix: LIBS += -L$$OUT_PWD/../../UpCloud-Core/ERMLib/ -lERMLib

INCLUDEPATH += $$PWD/../../UpCloud-Core/ERMLib
DEPENDPATH += $$PWD/../../UpCloud-Core/ERMLib
