#ifndef ACTIONREGISTRY
#define ACTIONREGISTRY

#include "base.h"
#include "action.h"
#include "timer.h"
#include "db.h"
#include "heartthrobiclient.h"
#include "unstructiclient.h"
#include "structiclient.h"
#include "scheduleiclient.h"
#include "baseiclient.h"
#include "transmsg.h"

using namespace Environment::Datagram;
using namespace Environment::Net_Equip_MainType;

namespace NoderRegistry
{
    /**
     * @brief registerSystemLogger  上云科技注册系统日志自定义格式
     */
    void registerSystemLogger()
    {
        //C:/UpCloud-package/conf/logger.conf
        QString logPath = QString(trs("%1/%2")).arg(NSAbstPath::getInstance().confAbst()).arg(trs("NodeServer-logger.conf"));
        //注册系统日志自定义格式监听器
        LogInterceptor::registerSystemLogger(logPath);
    }
    /**
         * @brief registerActions    上云科技请求/响应节点服务动作类注册中心
         * 注意:该注册中心包括请求和响应两种动作,当要动作可用,必须在该接口内注册该类,//并引入该类头文件
         */
    void registerActions()
    {
        /*----------------------------------------------------------------------注册请求------------*/
        //注册请求动作
        ActionRegistryFactory::registerClass<AbstractRequest>(Bridge_Conn::RESPBRIDGECONN);

        //非结构化  接收任务并作响应
        ActionRegistryFactory::registerClass<NoderRecUnstructTaskRequest>(Unstru_Data_Trans::REQUNSTRUCTFILESDOWNLOADINFO);
        //非结构化  接收响应回执
        ActionRegistryFactory::registerClass<NoderRecUnstructTaskStatusRequest>(Unstru_Data_Trans::RESPUNSTRUCTFILESDOWNLOADSTATUS);

        //结构化  接收任务并作响应
        ActionRegistryFactory::registerClass<NoderRecStructTaskRequest>(Stru_Data_Trans::REQSTRUCTFILESDOWNLOADINFO);
        //结构化  接收下载响应回执
        ActionRegistryFactory::registerClass<NoderRecStructTaskDownStatusRequest>(Stru_Data_Trans::RESPSTRUCTFILESDOWNLOADSTATUS);
        //结构化  接收解析响应回执
        ActionRegistryFactory::registerClass<NoderRecStructTaskParseStatusRequest>(Stru_Data_Trans::RESPSTRUCTTASKEXECSTATUS);

        //控制传输  接收任务并作响应
        ActionRegistryFactory::registerClass<NoderRecScheduleTaskRequest>(Sche_Data_Trans::REQSCHEDULETASKDOWNLOADINFO);
        //控制传输  接收下载响应回执
        ActionRegistryFactory::registerClass<NoderRecScheduleTaskDownStatusRequest>(Sche_Data_Trans::RESPSCHEDULETASKDOWNLOADSTATUS);
        //控制传输  接收执行响应回执
        ActionRegistryFactory::registerClass<NoderRecScheduleTaskParseStatusRequest>(Sche_Data_Trans::RESPSCHEDULETASKEXECSTATUS);
        //...

        /*----------------------------------------------------------------------注册响应------------*/
        //注册响应动作
        //        RegistryFactory::registerClass<AbstractResponse>(Bridge_Conn::RESP_BRIDGE_CONN);
        //        ResponseFactory::registerClass<AbstractResponse>("AbstractResponse");
    }

    /**
         * @brief registerActions    上云科技节点服务定时执行计划注册中心
         * 注意:当要计划可用,必须在该接口内注册该类,//并引入该类头文件
         */
    void registerTimers()
    {


        //注册主动推送心跳服务
        TimerRegistryFactory::registerClass<HeartthrobClientExector>(TimerRegistryFactory::TYPE::Heartthrob);

        //非结构化  计划任务下载并反馈服务
        TimerRegistryFactory::registerClass<NoderUnstructExector>(TimerRegistryFactory::TYPE::Unstruct);

        //结构化  计划任务下载并反馈服务
        TimerRegistryFactory::registerClass<NoderStructDownExector>(TimerRegistryFactory::TYPE::Struct_down);
        //结构化  解析文件并反馈服务
        TimerRegistryFactory::registerClass<NoderStructParseExector>(TimerRegistryFactory::TYPE::Struct_parse);

        //控制传输  计划任务下载并反馈服务
        TimerRegistryFactory::registerClass<NoderScheduleDownExector>(TimerRegistryFactory::TYPE::Schedule_down);
        //控制传输  执行任务并反馈服务
        TimerRegistryFactory::registerClass<NoderScheduleParseExector>(TimerRegistryFactory::TYPE::Schedule_exec);

    }
    /**
         * @brief registerDBService 上云科技节点服务注册数据库服务连接池
         */
    void registerDBPool()
    {
        //C:/UpCloud-package/conf/server.conf
        QString confPath = QString(trs("%1/%2")).arg(NSAbstPath::getInstance().confAbst()).arg(trs("NodeServer-db.conf"));
        DatabaseConnectionPool::initialize(confPath);
    }
    /**
         * @brief releaseDBService  上云科技节点服务释放数据库服务连接池
         */
    void releaseDBPool()
    {
        //释放数据库连接
        DatabaseConnectionPool::release();
    }
    /**
     * @brief releaseGlobalObject  上云科技节点服务释放全局对象
     */
    void releaseGlobalObject()
    {
        DatabaseConf::release();
        DatabaseConnectionPool::release();
    }
    /**
     * @brief registerGlobalThreadsPool  注册节点服务器线程池控制服务
     */
    void registerGlobalThreadsPool()
    {
        //初始化应用线程池,使用全局线程池维护每个具有优先级的线程在队列中执行顺序
        QThreadPool *threadPool = QThreadPool::globalInstance();
        //设置应用最多有50个工作线程正在运行,不包括调度器该线程
        threadPool->setMaxThreadCount(3);
        //设置工作线程运行前最大等待时间不超过40s(系统默认30s),假如超过40s,自动退出线程
        threadPool->setExpiryTimeout(40000);
    }
}
#endif // ACTIONREGISTRY

