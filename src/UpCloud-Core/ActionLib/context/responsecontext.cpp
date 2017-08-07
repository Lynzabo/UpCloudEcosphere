#include "responsecontext.h"

//ResponseContext::ResponseContext(QObject *parent) : QObject(parent)
//{

//}


ResponseContext::ResponseContext(QTcpSocket *client, const QString &clientKey)
    :client(client)
  ,clientKey(clientKey),canSend(true),canRedirect(false)
{
    datagram.clear();

}

ResponseContext::~ResponseContext()
{
}
QByteArray ResponseContext::getDatagram() const
{
    return datagram;
}

void ResponseContext::setDatagram(const QByteArray &value)
{
    datagram = value;
}
bool ResponseContext::getCanSend() const
{
    return canSend;
}

void ResponseContext::setCanSend(bool value)
{
    canSend = value;
}
bool ResponseContext::getCanRedirect() const
{
    return canRedirect;
}

void ResponseContext::setCanRedirect(bool value)
{
    canRedirect = value;
}
quint8 ResponseContext::getMsgType() const
{
    return msgType;
}

void ResponseContext::setMsgType(const quint8 &value)
{
    msgType = value;
}
MessageInfo *ResponseContext::getMsgInfo() const
{
    return msgInfo;
}

void ResponseContext::setMsgInfo(MessageInfo *value)
{
    msgInfo = value;
}






