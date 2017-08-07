#ifndef ACTIONREGISTRY_H
#define ACTIONREGISTRY_H
#include "base.h"
#include "baseiremote.h"
#include "heartthrobiremote.h"
#include "operairemote.h"
#include "duplex.h"
using namespace Environment::Datagram;
using namespace Environment::Net_Equip_MainType;

namespace RemoteUIRegistry
{
    /**
     * @brief registerSystemLogger  上云科技注册系统日志自定义格式
     */
    void registerSystemLogger()
    {
        //C:/UpCloud-package/conf/logger.conf
        QString logPath = QString(trs("%1/%2")).arg(RUAbstPath::getInstance().confAbst()).arg(trs("RemoteUI-logger.conf"));
        //注册系统日志自定义格式监听器
        LogInterceptor::registerSystemLogger(logPath);
    }
    /**
     * @brief registerActions    上云科技请求/响应远程UI服务动作类注册中心
     * 注意:该注册中心包括请求和响应两种动作,当要动作可用,必须在该接口内注册该类,//并引入该类头文件
     */
    void registerActions()
    {
        /*----------------------------------------------------------------------注册请求------------*/
        //返回UI请求参数
        ActionRegistryFactory::registerClass<RemoterRecOperaResponse>(UI_Ctrl::RESPREMOTEUIOPERACENTORINFO);
    }

    /**
     * @brief registerActions    上云科技远程UI服务定时执行计划注册中心
     * 注意:当要计划可用,必须在该接口内注册该类,//并引入该类头文件
     */
    void registerTimers()
    {
        //注册主动推送心跳服务
        TimerRegistryFactory::registerClass<HeartthrobRemoteExector>(TimerRegistryFactory::TYPE::Heartthrob);
    }
    /**
     * @brief registerDBService 上云科技远程UI服务注册数据库服务连接池
     */
    void registerDBPool()
    {
        //C:/UpCloud-package/conf/server.conf
//        QString confPath = QString(trs("%1/%2")).arg(AbstPath::confAbst()).arg(trs("NodeServer-db.conf"));
//        DatabaseConnectionPool::initialize(confPath);
    }
    /**
     * @brief releaseDBService  上云科技远程UI服务释放数据库服务连接池
     */
    void releaseDBPool()
    {
        //释放数据库连接
//        DatabaseConnectionPool::release();
    }
    /**
     * @brief registerGlobalThreadsPool  注册远程UI客户端线程池控制服务
     */
    void registerGlobalThreadsPool()
    {
        //初始化应用线程池,使用全局线程池维护每个具有优先级的线程在队列中执行顺序
        QThreadPool *threadPool = QThreadPool::globalInstance();
        //设置应用最多有50个工作线程正在运行,不包括调度器该线程
        threadPool->setMaxThreadCount(50);
        //设置工作线程运行前最大等待时间不超过40s(系统默认30s),假如超过40s,自动退出线程
        threadPool->setExpiryTimeout(40000);
    }
    /**
     * @brief registerDuplexFactory 注册远程UI全双工工作工厂
     */
    void registerDuplexFactory()
    {
        UpCloudDuplexFactory::getInstance();
    }
    /**
     * @brief releaseGlobalObject  上云科技远程UI服务释放全局对象
     */
    void releaseGlobalObject()
    {
//       DatabaseConf::release();
//       DatabaseConnectionPool::release();
    }
    /**
     * @brief releaseDuplexFactory 释放远程UI全双工工作工厂
     */
    void releaseDuplexFactory()
    {
        UpCloudDuplexFactory::release();
    }

}
#endif // ACTIONREGISTRY_H

