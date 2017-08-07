#include "upcloudduplexfactory.h"
SINGLETON_INITIALIZE(UpCloudDuplexFactory)
UpCloudDuplexFactory::UpCloudDuplexFactory()
{
    asyncWorker = new DuplexAsyncWorker;
    //同步服务端状态
    connect(asyncWorker,&DuplexAsyncWorker::evt_notice_sync_socks,this,&UpCloudDuplexFactory::evt_notice_sync_socks,Qt::DirectConnection);
    //广播客户端发送数据
    connect(asyncWorker,&DuplexAsyncWorker::evt_send,this,&UpCloudDuplexFactory::evt_send,Qt::DirectConnection);
    //发送最新客户端信息到异步工作线程
    connect(this,&UpCloudDuplexFactory::evt_sync_socks,asyncWorker,&DuplexAsyncWorker::on_sync_socks,Qt::DirectConnection);
    connect(this,&UpCloudDuplexFactory::evt_receive_duplex,asyncWorker,&DuplexAsyncWorker::on_receive_duplex,Qt::DirectConnection);

}
UpCloudDuplexFactory::~UpCloudDuplexFactory()
{
    delete asyncWorker;
    asyncWorker = NULL;
}
void UpCloudDuplexFactory::on_receive_duplex(RequestContext *request, ResponseContext *response)
{
    emit
        evt_receive_duplex(request,response);
}

DPSender *UpCloudDuplexFactory::createDPSender()
{
    if(!asyncWorker->isRunning())
        asyncWorker->start();
    return new DPSender;
}
