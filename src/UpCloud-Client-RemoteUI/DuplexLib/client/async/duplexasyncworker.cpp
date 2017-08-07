#include "duplexasyncworker.h"
#include "baseiremote.h"
DuplexAsyncWorker::DuplexAsyncWorker()
{
}

DuplexAsyncWorker::~DuplexAsyncWorker()
{
}

void DuplexAsyncWorker::run()
{
    while(1)
    {
        pullSender();
        QThread::msleep(20);
    }
}

void DuplexAsyncWorker::on_receive_duplex(RequestContext *request, ResponseContext *response)
{
    RespRemoteUIOperaCentorInfo *rspRemoteUIOperaCentorInfo = (RespRemoteUIOperaCentorInfo *)(response->getMsgInfo());
    if(!rspRemoteUIOperaCentorInfo)
        return;
    DeplexMessagesController::getInstance().pushResult2MQ(rspRemoteUIOperaCentorInfo);
}

void DuplexAsyncWorker::pullSender()
{
    DPSender *sender = 0;
    sender = DeplexMessagesController::getInstance().pullSenderFromMQ();
    if(sender)
    {
        //1.阻塞模式同步服务端网络状态
        emit
            evt_notice_sync_socks();
        //2.发送请求报文到服务端
        ReqRemoteUIOperaCentorInfo *reqOperaInfo = new ReqRemoteUIOperaCentorInfo;
        reqOperaInfo->ExecType = sender->getExecType();
        reqOperaInfo->Params = sender->getParams();

        if(this->m_socks.size() > 0)
        {
            QByteArray data;
            DatagramUtil::getInstance().packDatagram(reqOperaInfo,data);
            if(m_socks.size()==1)
            {
                QTcpSocket* sock = m_socks.keys().at(0);
                emit
                    evt_send((QObject*)(sock),data);
            }
        }
    }
}

