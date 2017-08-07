#include "rroperaresponse.h"

QMutex * RemoterRecOperaResponse::mutex = new QMutex;

RemoterRecOperaResponse::RemoterRecOperaResponse()
{

}

RemoterRecOperaResponse::~RemoterRecOperaResponse()
{
    delete gramEntity;
}

void RemoterRecOperaResponse::doRequest(RequestContext *request, ResponseContext *response)
{
    mutex->lock();
    QByteArray datagram;
    ////反序列化报文体到实体对象
    quint8 msgType = request->getMsgType();
    QString message = request->getMessage();
    //发送报文实体对象
    RespRemoteUIOperaCentorInfo *respEntity = new RespRemoteUIOperaCentorInfo;

    try
    {
        gramEntity = DatagramUtil::getInstance().parseMessageText(CallbackByRespOpera,msgType,message);
    }
    catch(TransException &excep)
    {
        qDebug() << trs("反序列化报文体到实体对象:ErrorCode:%1,ErrorMsg:%2").arg(excep.getType()).arg(excep.getText());
        goto end;
    }
sendDatagram:
    ////仍然拼装中心返回远程UI请求数据报文,经过调度器转发给客户端调用
    respEntity = gramEntity;
    try
    {
        DatagramUtil::getInstance().packDatagram(respEntity,datagram);
//        delete respEntity;
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
    //设置当前报文不发送
    response->setCanSend(false);
    //设置转发该报文到系统其它业务,这个任务由过滤器和调度器共同完成
    response->setCanRedirect(true);
    //设置报文类型
    response->setMsgType(respEntity->MessageType);
    //传递自定义属性
    response->setMsgInfo(respEntity);
    response->setDatagram(datagram);
    ////结束
end:
    mutex->unlock();
}

RespRemoteUIOperaCentorInfo *RemoterRecOperaResponse::CallbackByRespOpera(RespRemoteUIOperaCentorInfo *operaRespEntity)
{
    return operaRespEntity;
}
