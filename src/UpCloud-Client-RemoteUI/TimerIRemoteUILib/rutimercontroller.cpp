#include "rutimercontroller.h"
#include <QtConcurrent/QtConcurrent>

QMutex *RUTimerController::mutex = new QMutex;

RUTimerController::RUTimerController()
{
    timer_heartthrob = 0;
}

RUTimerController::~RUTimerController()
{
    delete mutex;
}

void RUTimerController::on_start()
{
    //读取配置文件 获得定时时间
    ClientConf clientconf;
    quint32 timer_heartthrob_timeout;
    clientconf.getHeartthrobTimeout(timer_heartthrob_timeout);
    //定时心跳
    timer_heartthrob = startTimer(timer_heartthrob_timeout);
}

void RUTimerController::on_stop()
{
    //kill  心跳
    killTimer(timer_heartthrob);
}

void RUTimerController::timerEvent(QTimerEvent *event)
{
    //1.阻塞模式同步服务端网络状态
    emit
    evt_notice_sync_socks(Environment::Net_Equip_MainType::DESKTOP_REMOTEUI);
    //执行者
    Exector *ector = 0;
    //定义各个报文对象并作响应处理
    if(event->timerId() == timer_heartthrob)
    {
        //心跳
        ector = (Exector *)TimerRegistryFactory::createObject(TimerRegistryFactory::TYPE::Heartthrob);
    }
    if(ector)
    {
        QtConcurrent::run(this,&RUTimerController::asyncWork,ector);
    }
}

void RUTimerController::on_write(PushContext *context)
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

void RUTimerController::asyncWork(Exector *ector)
{
    connect(ector,&Exector::evt_write,this,&RUTimerController::on_write,Qt::DirectConnection);
    connect(this,&RUTimerController::evt_RemoteHostClosed,ector,&Exector::on_RemoteHostClosed,Qt::DirectConnection);
    ector->doInit();
    PushContext *context = new PushContext;
    ector->doExecute(m_socks,context);
    ector->deleteLater();
}
