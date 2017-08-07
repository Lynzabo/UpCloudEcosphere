#include <QCoreApplication>
#include "actionregistry.h"
#include "remoteuioperaregistry.h"
#include "servertaskscheduler.h"
#include "baseiserver.h"
int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    //初始化设置应用目录
    QString rootPath;rootPath.clear();
#ifdef Q_OS_WIN
    rootPath = QString("c:/UpCloud-package/CenterServer");
#else
    rootPath = QString("/opt/UpCloud-package/CenterServer");
#endif
    CSAbstPath::getInstance().setApplicationRootDir(rootPath);

    //生中心服务随机数种子
    qsrand(TimerUtil::currentTimeMillis());
    //注册系统日志自定义格式监听器
    CenterRegistry::registerSystemLogger();
    //动态注册请求响应
    CenterRegistry::registerActions();
    //动态注册定时主推服务
    CenterRegistry::registerTimers();
    //注册中心服务器线程池控制服务
    CenterRegistry::registerGlobalThreadsPool();
    //动态注册远程UI操作服务
    CenterRemoteOperaServiceRegistry::registerOperaServices();
    //注册数据库服务连接池
    CenterRegistry::registerDBPool();

    try
    {
        TerminalUUIDUtil::getInstance().init();
        TerminalKeYUtil::getInstance().init();
        QEventLoop loop;
        ServerTaskScheduler scheduler;
        scheduler.startup();
        QObject::connect(&scheduler, SIGNAL(evt_finish()), &loop, SLOT(quit()));
        loop.exec();
    }
    catch(DBException &except)
    {
        qDebug() << except.getType() << except.getText();
        //释放数据库服务连接池
        CenterRegistry::releaseDBPool();
        //释放全局对象
        CenterRegistry::releaseGlobalObject();
    }
    catch(...)
    {
        //释放数据库服务连接池
        CenterRegistry::releaseDBPool();
        //释放全局对象
        CenterRegistry::releaseGlobalObject();
        qDebug() << trs("服务启动失败");
    }
    return 0;
}

