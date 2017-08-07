#-------------------------------------------------
#
#   上云科技应用生态圈
#
#   版权:  C/C++ development team
#   时间:       2015-07-14 14:27:06
#
#-------------------------------------------------
TEMPLATE = subdirs

SUBDIRS += \
    UpCloud-Service-Center \
    UpCloud-Service-NodeServer \
    UpCloud-Core \
    UpCloud-Client-RemoteUI


message("Compile Environment Introduce:")
message("System Info: {$$QMAKE_HOST.name,$$QMAKE_HOST.os-$$QMAKE_HOST.arch,Ver$$QMAKE_HOST.version}")
message("Current:$$_DATE_")
!isEmpty(QMAKESPEC) {
  message("QMAKESPEC: $$QMAKESPEC")
}
#CONFIG += warn_off

#CODECFORSRC = UTF-8

CONFIG(debug, debug|release) {
    message("Building lib in debug mode")
}
CONFIG(release, debug|release) {
    message("Building lib in release mode")
}
