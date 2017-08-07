#include "remoteuiframework.h"
#include "qtsingleapplication/QtSingleApplication"
#include "base.h"
#include <signal.h>
#include <QIcon>
#include "modules/common/uihelper.h"
#include "remoteui.h"
//如果不加该宏,启动浏览器时候同时启动客户端
#ifndef UPCLOUD_OCX
int main(int argc, char *argv[])
{
     QCoreApplication::addLibraryPath("./plugins");
    //校验应用唯一性方式1
    QtSingleApplication app(argc, argv);
    //加载本地汉语支持
    QTranslator m_apTranslator,m_qtTranslator;
    m_apTranslator.load(":/core/i18n/i18n/StartRemoteUI_zh_CN");
    m_qtTranslator.load(":/core/i18n/i18n/qt_zh_CN");
    qApp->installTranslator(&m_apTranslator);
    qApp->installTranslator(&m_qtTranslator);
    if (app.isRunning())
    {
        UIHelper::ShowMessageBoxError(QObject::tr("启动失败，应用已经启动!"));
        return 0;
    }
    //校验应用唯一性方式2
    /*
    QApplication app(argc, argv);
    //创建共享内存,判断是否已经运行程序
    QSharedMemory mem("UpCloud-client-RemoteUI");
    if (!mem.create(1)) {
        UIHelper::ShowMessageBoxError(QObject::tr("Dead start,Application has started!"));
        return 1;
    }*/
    RemoteUIFrameWork *remote = new RemoteUIFrameWork;
    remote->show();
    int result = app.exec();
    return result;
}
#endif
#include <QAxFactory>
QAXFACTORY_DEFAULT(RemoteUIFrameWork,
           "{0F1E777A-D8F0-441C-B749-E7B80840077B}",
           "{616F620B-91C5-4410-A74E-6B81C76FFFE0}",
           "{E1816BBA-BF5D-4A31-9855-D6BA432055FF}",
           "{EC08F8FC-2754-47AB-8EFE-56A54057F34E}",
           "{A095BA0C-224F-4933-A458-2DD7F6B85D8F}")
//#include "remoteui.h"
//#include "qtsingleapplication/QtSingleApplication"
//#include "base.h"
//#include <signal.h>
//#include "actionregistry.h"
//#include "baseiremote.h"
//#include <QIcon>
//#include <QAxFactory>
//#include "modules/common/uihelper.h"

//int main(int argc, char *argv[])
//{
//    //校验应用唯一性方式1
//    QtSingleApplication app(argc, argv);
//    if (app.isRunning())
//    {
//        UIHelper::ShowMessageBoxError(QObject::tr("Dead start,Application has started!"));
//        return 0;
//    }
//    //校验应用唯一性方式2
//    /*
//    QApplication app(argc, argv);
//    //创建共享内存,判断是否已经运行程序
//    QSharedMemory mem("UpCloud-client-RemoteUI");
//    if (!mem.create(1)) {
//        UIHelper::ShowMessageBoxError(QObject::tr("Dead start,Application has started!"));
//        return 1;
//    }*/
//    //初始化设置应用目录
//    RUAbstPath::getInstance().setApplicationRootDir(QString("c:/UpCloud-package/RemoteUI"));
//    //注册系统日志自定义格式监听器
//    RemoteUIRegistry::registerSystemLogger();
//    //动态注册请求响应
//    RemoteUIRegistry::registerActions();
//    //动态注册定时主推服务
//    RemoteUIRegistry::registerTimers();
//    //注册远程UI客户端线程池控制服务
//    RemoteUIRegistry::registerGlobalThreadsPool();
//    //注册远程UI全双工工作工厂
//    RemoteUIRegistry::registerDuplexFactory();

////    QCoreApplication::addLibraryPath(QCoreApplication::applicationDirPath());
////    QCoreApplication::addLibraryPath(QString("platforms"));
//    app.setOrganizationName(QString(UPCLOUD_REMOTEUI_ORGANIZATIONNAME));
//    app.setOrganizationDomain(QString(UPCLOUD_REMOTEUI_ORGANIZATIONDOMAIN));
//    app.setApplicationName(QString(UPCLOUD_REMOTEUI_APPLICATIONNAME));
//    app.setApplicationVersion(QString(UPCLOUD_REMOTEUI_APPLICATIONVERSION));
//    //加载本地汉语支持
//    QTranslator m_apTranslator,m_qtTranslator;
//    m_apTranslator.load(":/core/i18n/i18n/StartRemoteUI_zh_CN");
//    m_qtTranslator.load(":/core/i18n/i18n/qt_zh_CN");
//    QCoreApplication::installTranslator(&m_qtTranslator);
//    QCoreApplication::installTranslator(&m_apTranslator);

////    QIcon icon;
////    icon.addPixmap(QPixmap(":/logo_16.png"));
////    icon.addPixmap(QPixmap(":/logo_32.png"));
////    icon.addPixmap(QPixmap(":/logo_48.png"));
////    icon.addPixmap(QPixmap(":/logo_64.png"));
////    icon.addPixmap(QPixmap(":/logo_128.png"));
////    icon.addPixmap(QPixmap(":/logo_256.png"));
////    QApplication::setWindowIcon(icon);
//#ifdef Q_OS_WIN
////    QFontDatabase::addApplicationFont("://DejaVuSans.ttf");
//    QFont font;
//    if (QLocale::system().country() == QLocale::China)
//        font.setFamily(QString("Microsoft Yahei"));
//    else
//        font.setFamily(QString("Segoe UI"));
//    font.setPointSize(96);//DPI
//    font.setPixelSize(24);//font size
//    app.setFont(font);
//#endif
//    //设置Application主题
//    QFile *cssFile = new QFile(":/core/qss/qss/core");cssFile->open(QFile::ReadOnly);
//    app.setStyleSheet(QLatin1String(cssFile->readAll()));delete cssFile;
//    qApp->setPalette(QPalette(QColor("#F0F0F0")));
////  设置系统主题
//    //QIcon::setThemeSearchPaths(QStringList()<< QString(UPCLOUD_REMOTEUI_COMMON_IMGS_PATH));
//    //QIcon::setThemeName("WhiteFlat");//Use QIcon::fromTheme("exit") get a QIcon
//    RemoteUI remote;
//    remote.show();
//    //释放远程UI全双工工作工厂
//    RemoteUIRegistry::releaseDuplexFactory();
//    //释放全局对象
//    RemoteUIRegistry::releaseGlobalObject();
//    qDebug() << trs("Exit Application");
//    return 0;
//}

//QAXFACTORY_DEFAULT(RemoteUI,
//           "{552651BC-8FD4-4932-9889-932BCBF5EB63}",
//           "{616F620B-91C5-4410-A74E-6B81C76FFFE0}",
//           "{E1816BBA-BF5D-4A31-9855-D6BA432055FF}",
//           "{EC08F8FC-2754-47AB-8EFE-56A54057F34E}",
//           "{A095BA0C-224F-4933-A458-2DD7F6B85D8F}")

//#include "remoteuiframework.h"
//#include "qtsingleapplication/QtSingleApplication"
//#include "base.h"
//#include <signal.h>
//#include "actionregistry.h"
//#include "baseiremote.h"
//#include <QIcon>
//#include "modules/common/uihelper.h"
//RemoteUIFrameWork *window = nullptr;

//static void onSignalRecv(int sig)
//{
//#ifdef Q_OS_UNIX
//    if (sig == SIGUSR1) {
//        if (window) {
//            window->show();
//        }
//    }
//#endif
//    if (sig == SIGINT || sig == SIGTERM) qApp->quit();
//}

//int main(int argc, char *argv[])
//{
//    //校验应用唯一性方式1
//    QtSingleApplication app(argc, argv);
//    if (app.isRunning())
//    {
//        UIHelper::ShowMessageBoxError(QObject::tr("Dead start,Application has started!"));
//        return 0;
//    }
//    //校验应用唯一性方式2
//    /*
//    QApplication app(argc, argv);
//    //创建共享内存,判断是否已经运行程序
//    QSharedMemory mem("UpCloud-client-RemoteUI");
//    if (!mem.create(1)) {
//        UIHelper::ShowMessageBoxError(QObject::tr("Dead start,Application has started!"));
//        return 1;
//    }*/
//    //初始化设置应用目录
//    RUAbstPath::getInstance().setApplicationRootDir(QString("c:/UpCloud-package/RemoteUI"));
//    //注册系统日志自定义格式监听器
//    RemoteUIRegistry::registerSystemLogger();
//    //动态注册请求响应
//    RemoteUIRegistry::registerActions();
//    //动态注册定时主推服务
//    RemoteUIRegistry::registerTimers();
//    //注册远程UI客户端线程池控制服务
//    RemoteUIRegistry::registerGlobalThreadsPool();
//    //注册远程UI全双工工作工厂
//    RemoteUIRegistry::registerDuplexFactory();
//    //捕捉来自系统键盘的中断信号(Ctrl+C)
//    signal(SIGINT, onSignalRecv);
//    //捕捉来自kill命令发出的信号
//    signal(SIGTERM, onSignalRecv);
//#ifdef Q_OS_UNIX
//    //捕捉来自kill -usr1 PID
//    signal(SIGUSR1, onSignalRecv);
//#endif

////    QCoreApplication::addLibraryPath(QCoreApplication::applicationDirPath());
////    QCoreApplication::addLibraryPath(QString("platforms"));
//    app.setOrganizationName(QString(UPCLOUD_REMOTEUI_ORGANIZATIONNAME));
//    app.setOrganizationDomain(QString(UPCLOUD_REMOTEUI_ORGANIZATIONDOMAIN));
//    app.setApplicationName(QString(UPCLOUD_REMOTEUI_APPLICATIONNAME));
//    app.setApplicationVersion(QString(UPCLOUD_REMOTEUI_APPLICATIONVERSION));
//    //加载本地汉语支持
//    QTranslator m_apTranslator,m_qtTranslator;
//    m_apTranslator.load(":/core/i18n/i18n/StartRemoteUI_zh_CN");
//    m_qtTranslator.load(":/core/i18n/i18n/qt_zh_CN");
//    QCoreApplication::installTranslator(&m_qtTranslator);
//    QCoreApplication::installTranslator(&m_apTranslator);

////    QIcon icon;
////    icon.addPixmap(QPixmap(":/logo_16.png"));
////    icon.addPixmap(QPixmap(":/logo_32.png"));
////    icon.addPixmap(QPixmap(":/logo_48.png"));
////    icon.addPixmap(QPixmap(":/logo_64.png"));
////    icon.addPixmap(QPixmap(":/logo_128.png"));
////    icon.addPixmap(QPixmap(":/logo_256.png"));
////    QApplication::setWindowIcon(icon);
//#ifdef Q_OS_WIN
////    QFontDatabase::addApplicationFont("://DejaVuSans.ttf");
//    QFont font;
//    if (QLocale::system().country() == QLocale::China)
//        font.setFamily(QString("Microsoft Yahei"));
//    else
//        font.setFamily(QString("Segoe UI"));
//    font.setPointSize(96);//DPI
//    font.setPixelSize(24);//font size
//    app.setFont(font);
//#endif
//    //设置Application主题
//    QFile *cssFile = new QFile(":/core/qss/qss/core");cssFile->open(QFile::ReadOnly);
//    app.setStyleSheet(QLatin1String(cssFile->readAll()));delete cssFile;
//    qApp->setPalette(QPalette(QColor("#F0F0F0")));
////  设置系统主题
//    //QIcon::setThemeSearchPaths(QStringList()<< QString(UPCLOUD_REMOTEUI_COMMON_IMGS_PATH));
//    //QIcon::setThemeName("WhiteFlat");//Use QIcon::fromTheme("exit") get a QIcon
//    QEventLoop loop;
//    RemoteUIFrameWork w;
//    QObject::connect(&w, SIGNAL(destoryApp()), &loop, SLOT(quit()));
//    w.show();
//    loop.exec();
//    //释放远程UI全双工工作工厂
//    RemoteUIRegistry::releaseDuplexFactory();
//    //释放全局对象
//    RemoteUIRegistry::releaseGlobalObject();
//    qDebug() << trs("Exit Application");
//    return 0;
//}
