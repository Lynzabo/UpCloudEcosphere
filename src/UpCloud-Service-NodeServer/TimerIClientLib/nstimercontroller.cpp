#include "nstimercontroller.h"
#include "baseiclient.h"
#include <QtConcurrent/QtConcurrent>

QMutex *NSTimerController::mutex = new QMutex;

NSTimerController::NSTimerController()
{
    timer_heartthrob = 0;
    timer_unstruct_task = 0;
    timer_struct_down_task = 0;
    timer_struct_parse_task = 0;
    timer_schedule_down_task = 0;
    timer_schedule_exec_task = 0;
}

NSTimerController::~NSTimerController()
{
    delete mutex;
}

void NSTimerController::on_start()
{
    //读取配置文件 获得定时时间
    ClientConf clientconf;
    quint32 timer_heartthrob_timeout;
    quint32 timer_unstruct_task_timeout;
    quint32 timer_struct_down_task_timeout,timer_struct_parse_task_timeout;
    quint32 timer_schedule_down_task_timeout,timer_schedule_exec_task_timeout;

    clientconf.getHeartthrobTimeout(timer_heartthrob_timeout);
    clientconf.getUnstructTaskTimeout(timer_unstruct_task_timeout);
    clientconf.getStructDownTaskTimeout(timer_struct_down_task_timeout);
    clientconf.getStructParseTaskTimeout(timer_struct_parse_task_timeout);
    clientconf.getScheduleDownTaskTimeout(timer_schedule_down_task_timeout);
    clientconf.getScheduleExecTaskTimeout(timer_schedule_exec_task_timeout);

    //定时心跳
    timer_heartthrob = startTimer(timer_heartthrob_timeout);

    //定时扫描非结构化任务
    timer_unstruct_task = startTimer(timer_unstruct_task_timeout);

    //定时扫描结构化任务
    timer_struct_down_task = startTimer(timer_struct_down_task_timeout);
    //定时解析结构化任务
    timer_struct_parse_task = startTimer(timer_struct_parse_task_timeout);

    //定时扫描控制传输任务
    timer_schedule_down_task = startTimer(timer_schedule_down_task_timeout);
    //定时执行控制传输任务
    timer_schedule_exec_task = startTimer(timer_schedule_exec_task_timeout);
}

void NSTimerController::on_stop()
{
    //kill  心跳
    killTimer(timer_heartthrob);
    //就算网断掉了,还继续执行处理任务,为避免回执会出问题,数据库添加字段代表发报文是否字段
    //kill  非结构任务扫描器
    killTimer(timer_unstruct_task);
    //kill  结构任务扫描器
    killTimer(timer_struct_down_task);
    //kill  结构解析扫描器
    killTimer(timer_struct_parse_task);
    //kill  控制传输扫描器
    killTimer(timer_schedule_down_task);
    //kill  控制传输执行扫描器
    killTimer(timer_schedule_exec_task);
}



void NSTimerController::timerEvent(QTimerEvent *event)
{
    //1.阻塞模式同步服务端网络状态
    emit
    evt_notice_sync_socks(Environment::Net_Equip_MainType::DESKTOP_NODER);
    //执行者
    Exector *ector = 0;
    //定义各个报文对象并作响应处理
    if(event->timerId() == timer_heartthrob)
    {
        //心跳
        ector = (Exector *)TimerRegistryFactory::createObject(TimerRegistryFactory::TYPE::Heartthrob);
    }
    else if(event->timerId() == timer_unstruct_task)
    {
        //非结构化
        //扫描到每一个任务表后就需要单独对待每一条任务
        ector = (Exector *)TimerRegistryFactory::createObject(TimerRegistryFactory::TYPE::Unstruct);
    }
    else if(event->timerId() == timer_struct_down_task)
    {
        //结构化扫描
        ector = (Exector *)TimerRegistryFactory::createObject(TimerRegistryFactory::TYPE::Struct_down);
    }
    else if(event->timerId() == timer_struct_parse_task)
    {
        //结构化解析
        ector = (Exector *)TimerRegistryFactory::createObject(TimerRegistryFactory::TYPE::Struct_parse);
    }
    else if(event->timerId() == timer_schedule_down_task)
    {
        //控制传输扫描
        ector = (Exector *)TimerRegistryFactory::createObject(TimerRegistryFactory::TYPE::Schedule_down);
    }
    else if(event->timerId() == timer_schedule_exec_task)
    {
        //控制传输执行
        ector = (Exector *)TimerRegistryFactory::createObject(TimerRegistryFactory::TYPE::Schedule_exec);
    }
    if(ector)
    {
        QtConcurrent::run(this,&NSTimerController::asyncWork,ector);
    }
}

void NSTimerController::on_write(PushContext *context)
{
    mutex->lock();
    if(context->getSocks().size() > 0 && context->getMessage() != NULL)
    {
        QByteArray data;
        QVector<quint64> sockUUIDs = context->getSocks();
        for(quint64 uuid : sockUUIDs)
        {
            DatagramUtil::getInstance().packDatagram(context->getMessage(),data);
            emit evt_write((QObject*)(m_socks.key(uuid)),data);
        }
    }
    mutex->unlock();
}


void NSTimerController::asyncWork(Exector *ector)
{
    qDebug() << qPrintable(tr("***Create***  Current threadID --"))
             << QThread::currentThreadId()
             << qPrintable(tr("-- , Now work thread nums is [%1 / %2]").arg(QThreadPool::globalInstance()->activeThreadCount())
                .arg(QThreadPool::globalInstance()->maxThreadCount()));
    connect(ector,&Exector::evt_write,this,&NSTimerController::on_write,Qt::DirectConnection);
    connect(this,&NSTimerController::evt_RemoteHostClosed,ector,&Exector::on_RemoteHostClosed,Qt::DirectConnection);
    ector->doInit();
    PushContext *context = new PushContext;
    ector->doExecute(m_socks,context);
    ector->deleteLater();
    qDebug() << qPrintable(tr("***Destory***  Current threadID --")) << QThread::currentThreadId() << qPrintable(tr("-- "));
}
