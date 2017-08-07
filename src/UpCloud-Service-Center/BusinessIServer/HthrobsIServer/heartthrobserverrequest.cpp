#include "heartthrobserverrequest.h"
#include "baseiserver.h"
QMutex * HeartthrobServerRequest::mutex = new QMutex;
HeartthrobServerRequest::HeartthrobServerRequest()
{

}

HeartthrobServerRequest::~HeartthrobServerRequest()
{
    delete gramEntity;
}

void HeartthrobServerRequest::doRequest(RequestContext *request, ResponseContext *response)
{
    mutex->lock();

    QByteArray datagram;

    ////反序列化报文体到实体对象
    quint8 msgType = request->getMsgType();
    QString message = request->getMessage();
    //发送报文实体对象
    RespHeartthrobsConn *respEntity = new RespHeartthrobsConn;
    try
    {
        gramEntity = DatagramUtil::getInstance().parseMessageText(CallbackByHeartthrobsConn,msgType,message);
    }
    catch(TransException &excep)
    {
        qDebug() << trs("反序列化报文体到实体对象:ErrorCode:%1,ErrorMsg:%2").arg(excep.getType()).arg(excep.getText());
        respEntity->State = excep.getType();
        goto sendDatagram;
    }
    //TODO  记录当前客户端固定码


    sendDatagram:

    try
    {
        DatagramUtil::getInstance().packDatagram(respEntity,datagram, request->getUUID());
        delete respEntity;
    }
    catch(QString &excep)
    {
        qDebug() << trs("出错:%1").arg(excep);
        goto end;
    }
    catch(TransException &excep)
    {
        qDebug() << excep.getText();
        goto end;
    }
    response->setDatagram(datagram);
    ////结束
    end:
    mutex->unlock();
}

ReqHeartthrobsConn *HeartthrobServerRequest::CallbackByHeartthrobsConn(ReqHeartthrobsConn *unstructEntity)
{
    return unstructEntity;
}

