#include "abstractrequest.h"

AbstractRequest::AbstractRequest()
{

}

void AbstractRequest::doInit()
{
    qDebug() << "Request init";
}

void AbstractRequest::doValidate(RequestContext *request, ResponseContext *response)
{
    qDebug() << "Request validate";
}

void AbstractRequest::doRequest(RequestContext *request, ResponseContext *response)
{
    qDebug() << trs("处理请求:%1,%2").arg(request->getClientKey()).arg(request->getMsgType());
//    qDebug() << trs("Datagram Type:") << request->getMsgType() << trs(",Message:") << request->getMessage();
    //生成报文并进行装帧
    RespBridgeConn resp;
    resp.PubKey = 0x22345678;
    QByteArray data;
    try
    {
        //DatagramUtil::getInstance().packDatagram(&resp,data);
        //response->setDatagram(data);
    }
    catch(QString &excep)
    {
        qDebug() << trs("出错:%1").arg(excep);
        return;
    }
    catch(TransException &excep)
    {
       qDebug() << excep.getText();
       return;
    }
}

void AbstractRequest::doDestory()
{
    qDebug() << "Request destory";
}

