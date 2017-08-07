#ifndef ACTIONREGISTRY
#define ACTIONREGISTRY

#include "base.h"
#include "action.h"
#include "timer.h"
#include "db.h"

#include "unstructiserver.h"
#include "structiserver.h"
#include "scheduleiserver.h"
#include "baseiserver.h"
#include "hthrobsiserver.h"
#include "operaiserver.h"
using namespace Environment::Datagram;

namespace CenterRegistry
{
    /**
         * @brief registerSystemLogger  上云科技注册系统日志自定义格式
         */
    void registerSystemLogger()
    {
        //C:/UpCloud-package/conf/logger.conf
        QString logPath = QString(trs("%1/%2")).arg(CSAbstPath::getInstance().confAbst()).arg(trs("CenterServer-logger.conf"));
        //注册系统日志自定义格式监听器
        LogInterceptor::registerSystemLogger(logPath);
    }
    /**
         * @brief registerActions    上云科技请求/响应中心服务动作类注册中心
         * 注意:该注册中心包括请求和响应两种动作,当要动作可用,必须在该接口内注册该类,//并引入该类头文件
         */
    void registerActions()
    {
        /*----------------------------------------------------------------------注册请求------------*/
        //长连接   接收节点长连接动作
        ActionRegistryFactory::registerClass<AbstractRequest>(Bridge_Conn::REQBRIDGECONN);
        //心跳    接收节点心跳动作
        ActionRegistryFactory::registerClass<HeartthrobServerRequest>(Heartthrob_Conn::REQHEARTTHROBSCONN);

        //非结构化  接收任务回执
        ActionRegistryFactory::registerClass<CenterRecUnstructTaskDownloadRequest>(Unstru_Data_Trans::RESPUNSTRUCTFILESDOWNLOADINFO);
        //非结构化  接收下载状态并作响应
        ActionRegistryFactory::registerClass<CenterRecUnstructTaskStatusRequest>(Unstru_Data_Trans::REQUNSTRUCTFILESDOWNLOADSTATUS);

        //结构化   接收任务回执
        ActionRegistryFactory::registerClass<CenterRecStructTaskDownloadRequest>(Stru_Data_Trans::RESPSTRUCTFILESDOWNLOADINFO);
        //结构化   接收下载状态并作响应
        ActionRegistryFactory::registerClass<CenterRecStructTaskDownStatusRequest>(Stru_Data_Trans::REQSTRUCTFILESDOWNLOADSTATUS);
        //结构化   接收解析状态并作响应
        ActionRegistryFactory::registerClass<CenterRecStructTaskParseStatusRequest>(Stru_Data_Trans::REQSTRUCTTASKEXECSTATUS);

        //控制传输  接收任务回执
        ActionRegistryFactory::registerClass<CenterRecScheduleTaskDownloadRequest>(Sche_Data_Trans::RESPSCHEDULETASKDOWNLOADINFO);
        //控制传输  接收下载状态并作响应
        ActionRegistryFactory::registerClass<CenterRecScheduleTaskDownStatusRequest>(Sche_Data_Trans::REQSCHEDULETASKDOWNLOADSTATUS);
        //控制传输   接收执行状态并作响应
        ActionRegistryFactory::registerClass<CenterRecScheduleTaskParseStatusRequest>(Sche_Data_Trans::REQSCHEDULETASKEXECSTATUS);

        //远程UI操作    远程UI请求中心操作数据
        ActionRegistryFactory::registerClass<CenterRemoteUIOperaInterceptor>(UI_Ctrl::REQREMOTEUIOPERACENTORINFO);
        //...

        /*----------------------------------------------------------------------注册响应------------*/
        //注册响应动作
        //ActionRegistryFactory::registerClass<AbstractRequest>(Bridge_Conn::RESP_BRIDGE_CONN);
        //        ResponseFactory::registerClass<AbstractResponse>("AbstractResponse");
    }

    /**
         * @brief registerTimers    上云科技中心服务定时执行计划注册中心
         * 注意:当要计划可用,必须在该接口内注册该类,//并引入该类头文件
         */
    void registerTimers()
    {
        //非结构化  非结构化任务下发服务
        TimerRegistryFactory::registerClass<CenterUnstructExector>(TimerRegistryFactory::TYPE::Unstruct);
        //TimerRegistryFactory::registerClass<HeartthrobClientExector>(TimerRegistryFactory::TYPE::Heartthrob);

        //结构化 扫描结构化任务并向向节点服务器推送
        TimerRegistryFactory::registerClass<CenterStructExector>(TimerRegistryFactory::TYPE::Struct_down);

        //控制传输 扫描控制传输任务并向向节点服务器推送
        TimerRegistryFactory::registerClass<CenterScheduleExector>(TimerRegistryFactory::TYPE::Schedule_down);
    }
    /**
         * @brief registerDBPool 上云科技中心服务注册数据库服务连接池
         */
    void registerDBPool()
    {
        //C:/UpCloud-package/conf/server.conf
        QString confPath = QString(trs("%1/%2")).arg(CSAbstPath::getInstance().confAbst()).arg(trs("CenterServer-db.conf"));
        DatabaseConnectionPool::initialize(confPath);
    }
    /**
         * @brief releaseDBPool  上云科技中心服务释放数据库服务连接池
         */
    void releaseDBPool()
    {
        //释放数据库连接
        DatabaseConnectionPool::release();
    }
    /**
         * @brief releaseGlobalObject  上云科技中心服务释放全局对象
         */
    void releaseGlobalObject()
    {
        DatabaseConf::release();
        DatabaseConnectionPool::release();
    }
    /**
     * @brief registerGlobalThreadsPool  注册中心服务器线程池控制服务
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

