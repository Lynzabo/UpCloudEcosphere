#include "cstimercontroller.h"
#include "baseiserver.h"
#include <QtConcurrent/QtConcurrent>

QMutex *CSTimerController::mutex = new QMutex;
CSTimerController::CSTimerController()
{
    timer_unstruct_task = 0;
    timer_struct_task = 0;
    timer_schedule_task = 0;
}

CSTimerController::~CSTimerController()
{
    delete mutex;
}


void CSTimerController::on_start()
{
    //读取配置文件 获得定时时间
    ServerConf serverconf;
    quint32 timer_unstruct_task_timeout;
    quint32 timer_struct_task_timeout;
    quint32 timer_schedule_task_timeout;

    serverconf.getUnstructTaskTimeout(timer_unstruct_task_timeout);
    serverconf.getStructTaskTimeout(timer_struct_task_timeout);
    serverconf.getScheduleTaskTimeout(timer_schedule_task_timeout);

    //定时扫描非结构任务准备下发
    timer_unstruct_task = startTimer(timer_unstruct_task_timeout);
    //定时扫描结构任务准备下发
    timer_struct_task = startTimer(timer_struct_task_timeout);
    //定时扫描控制传输任务准备下发
    timer_schedule_task = startTimer(timer_schedule_task_timeout);
}

void CSTimerController::on_stop()
{
    //kill  非结构任务扫描器
    killTimer(timer_unstruct_task);
    //kill  结构任务扫描器
    killTimer(timer_struct_task);
    //kill  控制传输任务扫描器
    killTimer(timer_schedule_task);
}

void CSTimerController::timerEvent(QTimerEvent *event)
{
    //1.阻塞模式同步服务端网络状态
    emit
    evt_notice_sync_socks(Environment::Net_Equip_MainType::DESKTOP_NODER);
    //执行者
    Exector *ector = 0;
    //定义各个报文对象并作响应处理
    if(event->timerId() == timer_unstruct_task)
    {
        //非结构化
        //扫描到每一个任务表后就需要单独对待每一条任务
        ector = (Exector *)TimerRegistryFactory::createObject(TimerRegistryFactory::TYPE::Unstruct);
    }
    else if(event->timerId() == timer_struct_task)
    {
        //结构化
        ector = (Exector *)TimerRegistryFactory::createObject(TimerRegistryFactory::TYPE::Struct_down);
    }
    else if(event->timerId() == timer_schedule_task)
    {
        //控制处理
        ector = (Exector *)TimerRegistryFactory::createObject(TimerRegistryFactory::TYPE::Schedule_down);
    }
    if(ector)
    {
        QtConcurrent::run(this,&CSTimerController::asyncWork,ector);
    }
}

void CSTimerController::on_write(PushContext *context)
{
    mutex->lock();
    //判断是否需要推送报文,对于不推送报文模块什么也不做
    if(context->getSocks().size() > 0 && context->getMessage() != NULL)
    {
        QByteArray data;
        QVector<quint64> sockUUIDs = context->getSocks();
        for(quint64 uuid : sockUUIDs)
        {
            DatagramUtil::getInstance().packDatagram(context->getMessage(),data, uuid);
            emit evt_write((QObject*)(m_socks.key(uuid)),data);
        }
    }
    mutex->unlock();
}

void CSTimerController::asyncWork(Exector *ector)
{
    qDebug() << qPrintable(tr("***Create***  Current threadID --"))
             << QThread::currentThreadId()
             << qPrintable(tr("-- , Now work thread nums is [%1 / %2]").arg(QThreadPool::globalInstance()->activeThreadCount())
                .arg(QThreadPool::globalInstance()->maxThreadCount()));
    connect(ector,&Exector::evt_write,this,&CSTimerController::on_write,Qt::QueuedConnection);
    connect(this,&CSTimerController::evt_RemoteHostClosed,ector,&Exector::on_RemoteHostClosed,Qt::QueuedConnection);
    ector->doInit();
    PushContext *context = new PushContext;
    ector->doExecute(m_socks,context);
    ector->deleteLater();
    qDebug() << qPrintable(tr("***Destory***  Current threadID --")) << QThread::currentThreadId() << qPrintable(tr("-- "));
}

