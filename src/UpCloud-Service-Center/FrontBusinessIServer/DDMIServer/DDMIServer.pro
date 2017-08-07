#-------------------------------------------------
#
#   上云科技中心服务器端数据管理业务模块
#
#   版权:  C/C++ development team
#   时间:       2015-07-14 14:27:06
#
#-------------------------------------------------

TEMPLATE = subdirs

SUBDIRS += \
    UnstructOperaIServer \
    StructOperaIServer \
    ScheduleOperaIServer

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../../UpCloud-Core/BaseLib/release/ -lBaseLib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../../UpCloud-Core/BaseLib/debug/ -lBaseLib
else:unix: LIBS += -L$$OUT_PWD/../../../UpCloud-Core/BaseLib/ -lBaseLib

INCLUDEPATH += $$PWD/../../../UpCloud-Core/BaseLib
DEPENDPATH += $$PWD/../../../UpCloud-Core/BaseLib
