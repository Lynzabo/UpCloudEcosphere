#-------------------------------------------------
#
#   上云科技应用支撑封装--加解密库
#
#   版权:  C/C++ development team
#   时间:       2015-07-14 14:27:06
#-----
#   功能:
#-----
#-------------------------------------------------

QT       -= gui

TARGET = EnDecryptLib
TEMPLATE = lib

DEFINES += ENDECRYPTLIB_LIBRARY

SOURCES += \
    Botan/rsadecryption.cpp \
    Botan/rsaencryption.cpp \
    Botan/rsageneratekey.cpp \
    botanendecrypt.cpp

HEADERS +=\
        endecryptlib_global.h \
    Botan/rsadecryption.h \
    Botan/rsaencryption.h \
    Botan/rsageneratekey.h \
    endecryptinterface.h \
    endecrypt.h \
    botanendecrypt.h

unix {
    CONFIG += c++11
    target.path = /usr/lib
    INSTALLS += target
}



#botan
unix {
LIBS += -lbotan-1.10
INCLUDEPATH += /usr/local/include/botan-1.10
#    EXTRA_BINFILES += \
#        $${THIRDPARTY_PATH}/gstreamer-0.10/linux/plugins/libgstrtp.so \
#        $${THIRDPARTY_PATH}/gstreamer-0.10/linux/plugins/libgstvideo4linux2.so
#    for(FILE,EXTRA_BINFILES){
#        QMAKE_POST_LINK += $$quote(cp $${FILE} $${DESTDIR}$$escape_expand(\n\t))
#    }
}

win32{
win32:CONFIG(release, debug|release): LIBS += -L$$PWD/Botan/lib/ -lbotan
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/Botan/lib/ -lbotand

INCLUDEPATH += $$PWD/Botan/include
DEPENDPATH += $$PWD/Botan/include
#copy botan.dll to compile directory

EXTRA_BINFILES +=  $$PWD/Botan/lib/botan.dll
EXTRA_BINFILES_WIN = $${EXTRA_BINFILES}
EXTRA_BINFILES_WIN ~= s,/,\\,g
CONFIG(release, debug|release): DESTDIR_WIN = $$OUT_PWD/release
else:CONFIG(debug, debug|release): DESTDIR_WIN = $$OUT_PWD/debug

DESTDIR_WIN ~= s,/,\\,g
for(FILE,EXTRA_BINFILES_WIN){
            QMAKE_POST_LINK +=$$quote(cmd /c copy /y $${FILE} $${DESTDIR_WIN}$$escape_expand(\n\t))
}
}






