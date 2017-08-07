
HEADERS += \
    $$PWD/commonui.h \
    $$PWD/loading.h \
    $$PWD/uihelper.h \
    $$PWD/rmessagebox.h \
    $$PWD/headerview.h \
    $$PWD/nofocusframedelegate.h \
    $$PWD/tablewidget.h \
    $$PWD/toolbutton.h \
    $$PWD/mainmenu.h \
    $$PWD/funcsmenu.h \
    $$PWD/combobox.h \
    $$PWD/tree.h \
    $$PWD/treeglobal.h \
    $$PWD/treenode.h \
    $$PWD/grouptreewidget.h \
    $$PWD/dirnodefilewidget.h \
    $$PWD/createtaskwidget.h \
    $$PWD/createtaskinfo.h \
    $$PWD/filedialog.h \
    $$PWD/fileinfolist.h \
    $$PWD/filedirwidget.h \
    $$PWD/datetimeedit.h \
    $$PWD/datetimepicker.h \
    $$PWD/pagetablewidget.h \
    $$PWD/tablebodywidget.h

FORMS += \
    $$PWD/ui/loading.ui \
    $$PWD/ui/rmessagebox.ui \
    $$PWD/ui/grouptreewidget.ui \
    $$PWD/ui/grouptreewidget.ui \
    $$PWD/ui/dirnodefilewidget.ui \
    $$PWD/ui/createtaskwidget.ui \
    $$PWD/ui/fileinfolist.ui \
    $$PWD/ui/filedirwidget.ui \
    $$PWD/ui/datetimepicker.ui \
    $$PWD/ui/pagetablewidget.ui

SOURCES += \
    $$PWD/loading.cpp \
    $$PWD/uihelper.cpp \
    $$PWD/rmessagebox.cpp \
    $$PWD/headerview.cpp \
    $$PWD/nofocusframedelegate.cpp \
    $$PWD/tablewidget.cpp \
    $$PWD/toolbutton.cpp \
    $$PWD/mainmenu.cpp \
    $$PWD/funcsmenu.cpp \
    $$PWD/combobox.cpp \
    $$PWD/tree.cpp \
    $$PWD/treenode.cpp \
    $$PWD/grouptreewidget.cpp \
    $$PWD/dirnodefilewidget.cpp \
    $$PWD/createtaskwidget.cpp \
    $$PWD/createtaskinfo.cpp \
    $$PWD/filedialog.cpp \
    $$PWD/fileinfolist.cpp \
    $$PWD/filedirwidget.cpp \
    $$PWD/datetimeedit.cpp \
    $$PWD/datetimepicker.cpp \
    $$PWD/pagetablewidget.cpp \
    $$PWD/tablebodywidget.cpp

#TODO here is only windows environment,other system ,please to compile
#ssh
win32{
win32:CONFIG(release, debug|release): LIBS += -L$$PWD/ssh/lib/ -lQSshd
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/ssh/lib/ -lQSshd

INCLUDEPATH += $$PWD/ssh/include
DEPENDPATH += $$PWD/ssh/include
}

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../../../UpCloud-Core/ERMLib/release/ -lERMLib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../../../UpCloud-Core/ERMLib/debug/ -lERMLib
else:unix: LIBS += -L$$OUT_PWD/../../../../UpCloud-Core/ERMLib/ -lERMLib

INCLUDEPATH += $$PWD/../../../../UpCloud-Core/ERMLib
DEPENDPATH += $$PWD/../../../../UpCloud-Core/ERMLib
