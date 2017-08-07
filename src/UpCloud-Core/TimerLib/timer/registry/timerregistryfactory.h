#ifndef TIMERREGISTRYFACTORY_H
#define TIMERREGISTRYFACTORY_H
#include <QtCore>
#include "timerlib_global.h"


class TIMERLIBSHARED_EXPORT TimerRegistryFactory
{
    //注册定时服务类型
public:
    enum TYPE{
        ////心跳
        //使用场景:节点定时发送心跳包给中心
        Heartthrob,
        ////非结构化
        //使用场景:
        //    1.中心定时扫描非结构化任务表,使用执行器下发;
        //    2.节点定时扫描非结构化任务表,使用执行器对非结构化任务文件下载
        Unstruct,
        ////结构化
        //使用场景:
        //    1.中心定时扫描结构化任务表,使用执行器下发;
        //    2.节点定时扫描结构化任务表,使用执行器对结构化任务文件下载
        Struct_down,
        //使用场景:
        //    1.节点定时扫描结构化任务表,使用执行器对结构化任务文件进行解析
        Struct_parse,
        ////控制传输
        //使用场景:
        //    1.中心定时扫描控制传输任务表,使用执行器下发;
        //    2.节点定时扫描控制传输任务表,使用执行器对非结构化任务文件下载
        Schedule_down,
        //    1.节点定时扫描控制传输任务表,使用执行器启动入口文件运行程序
        Schedule_exec,
        ////监控
        //    1.远程UI主动推送请求给中心,中心需要主动发送报文给节点获取监控数据
        Monitor,
        ////操作
        //  预留字段,待以后需要时添加
        Operate
    };
public:
    template<typename T>
    static void registerClass(const TYPE &type)
    {
        constructors().insert( type, &constructorHelper<T> );
    }
    static QObject* createObject( const TYPE &type )
    {
        Constructor constructor = constructors().value( type );
        if ( constructor == NULL )
            return NULL;
        return (*constructor)();
    }
private:
    typedef QObject* (*Constructor)();
    template<typename T>
    static QObject* constructorHelper()
    {
        return new T;
    }
    static QHash<TYPE, Constructor>& constructors()
    {
        static QHash<TYPE, Constructor> instance;
        return instance;
    }
};

#endif // TIMERREGISTRYFACTORY_H
