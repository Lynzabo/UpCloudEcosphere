#-------------------------------------------------
#
#   上云科技节点服务器端业务模块
#
#   版权:  C/C++ development team
#   时间:       2015-07-14 14:27:06
#
#-------------------------------------------------

TEMPLATE = subdirs

SUBDIRS += \
    HthrobsIClient \
    UnstructIClient \
#   OperaIClient \
    ScheduleIClient \
    StructIClient \
#   MonitorIClient
    SerialComm

