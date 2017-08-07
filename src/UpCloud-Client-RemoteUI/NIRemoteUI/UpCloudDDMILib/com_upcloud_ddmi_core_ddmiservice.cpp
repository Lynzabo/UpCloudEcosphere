#include "com_upcloud_ddmi_core_DDMIService.h"
#include "base.h"
#include "baseiremote.h"
#include <iostream>
#include "netiremoteui.h"
#include "../../StartRemoteUI/actionregistry.h"
#include "util.h"
static QThread *remoteUIWorkThread = new QThread;
void Java_com_upcloud_ddmi_core_DDMIService_startup(JNIEnv *env, jobject obj,jstring ddmiPath)
{
    Q_UNUSED(env)
    Q_UNUSED(obj)
    if(remoteUIWorkThread->isRunning())
        return;
    char* ddmiPathURL = jstringTostring(env,ddmiPath);
    int argc = 0;
    QCoreApplication* app = new QCoreApplication(argc, NULL);
    Q_UNUSED(app)
//    //初始化设置应用目录
    RUAbstPath::getInstance().setApplicationRootDir(QString(ddmiPathURL));
    //注册系统日志自定义格式监听器
    RemoteUIRegistry::registerSystemLogger();
    //动态注册请求响应
    RemoteUIRegistry::registerActions();
    //动态注册定时主推服务
    RemoteUIRegistry::registerTimers();
    //注册远程UI客户端线程池控制服务
    RemoteUIRegistry::registerGlobalThreadsPool();
    //注册远程UI全双工工作工厂
    RemoteUIRegistry::registerDuplexFactory();

    //初始化本机固定码
    TerminalUUIDUtil::getInstance().init();
    //初始化报文工具
    DatagramUtil::getInstance().init();

//    QEventLoop loop;
    RemoteUITaskScheduler *taskScheduler = new RemoteUITaskScheduler;
    QObject::connect(remoteUIWorkThread,&QThread::started,taskScheduler,&RemoteUITaskScheduler::startup);
    QObject::connect(remoteUIWorkThread,&QThread::finished,taskScheduler,&RemoteUITaskScheduler::deleteLater);
//    QObject::connect(remoteUIWorkThread,&QThread::finished,&loop,&QEventLoop::quit);
    //任务调度器与UI绑定广播

    taskScheduler->moveToThread(remoteUIWorkThread);
    remoteUIWorkThread->start();
//    loop.exec();
//    remoteUIWorkThread->deleteLater();
//    //释放远程UI全双工工作工厂
//    RemoteUIRegistry::releaseDuplexFactory();
//    //释放全局对象
//    RemoteUIRegistry::releaseGlobalObject();
//    qDebug() << trs("Exit Application");
}


void Java_com_upcloud_ddmi_core_DDMIService_destory(JNIEnv *env, jobject obj)
{
    qDebug() << "DESTORY";
    QMetaObject::invokeMethod(remoteUIWorkThread,"finished",Qt::DirectConnection);
}
