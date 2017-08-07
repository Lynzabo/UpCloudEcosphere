
#include <QCoreApplication>
#include "actionregistry.h"
#include "clienttaskscheduler.h"
#include "baseiclient.h"
int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    //初始化设置应用目录
    QString rootPath;rootPath.clear();
#ifdef Q_OS_WIN
    rootPath = QString("c:/UpCloud-package/NoderServer");
#else
    rootPath = QString("/opt/UpCloud-package/NoderServer");
#endif
    NSAbstPath::getInstance().setApplicationRootDir(rootPath);
	//生节点服务随机数种子
    qsrand(TimerUtil::currentTimeMillis());
    //注册系统日志自定义格式监听器
    NoderRegistry::registerSystemLogger();
    //动态注册请求响应
    NoderRegistry::registerActions();
    //动态注册定时主推服务
    NoderRegistry::registerTimers();
    //注册节点服务器线程池控制服务
    NoderRegistry::registerGlobalThreadsPool();
    //注册数据库服务连接池
    NoderRegistry::registerDBPool();
    try
    {
        //初始化本机固定码
        TerminalUUIDUtil::getInstance().init();
        //初始化报文工具
        DatagramUtil::getInstance().init();


        QEventLoop loop;
        ClientTaskScheduler scheduler;
        scheduler.startup();
        QObject::connect(&scheduler, SIGNAL(evt_finish()), &loop, SLOT(quit()));
        loop.exec();
    }
    catch(QString &excep)
    {
        //释放数据库服务连接池
        NoderRegistry::releaseDBPool();
        //释放全局对象
        NoderRegistry::releaseGlobalObject();
        qDebug() << trs("节点服务启动失败:%1").arg(excep);
    }
    catch(...)
    {
        //释放数据库服务连接池
        NoderRegistry::releaseDBPool();
        //释放全局对象
        NoderRegistry::releaseGlobalObject();
        qDebug() << trs("服务启动失败");
    }
    return 0;
}

/*
//测试解析XML
#include <QCoreApplication>

#include "dao/structparsemanager.h"
int main(int argc, char *argv[])
{
    //注册系统日志自定义格式监听器
    QString logPath = QString(trs("%1/%2")).arg(AbstPath::confAbst()).arg(trs("NodeServer-logger.conf"));
    //注册系统日志自定义格式监听器
    Logger::registerSystemLogger(logPath);

    QCoreApplication a(argc, argv);
    QString fileName = "E:/Test/1.xml";
    StructParseManager parsemanager(fileName, true, 10);
    parsemanager.parse();

    return a.exec();
}
*/
/*
#include "bridgeclient.h"

int main(int argc, char *argv[])
{
    //注册系统日志自定义格式监听器
    Logger::registerSystemLogger();

    QCoreApplication a(argc, argv);
    BridgeClient::getInstance().ConnectToServer();
    return a.exec();
}
*/
