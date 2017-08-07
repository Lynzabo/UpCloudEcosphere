#include "csrusendstatus.h"


QString CsRUnstructSendStatus::getSendAddrUuid() const
{
    return sendAddrUuid;
}

void CsRUnstructSendStatus::setSendAddrUuid(const QString &value)
{
    sendAddrUuid = value;
}

quint8 CsRUnstructSendStatus::getState() const
{
    return state;
}

void CsRUnstructSendStatus::setState(const quint8 &value)
{
    state = value;
}
CsRUnstructSendStatus::CsRUnstructSendStatus()
{
    
}
QString CsRUnstructSendStatus::getUuid() const
{
    return uuid;
}

void CsRUnstructSendStatus::setUuid(const QString &value)
{
    uuid = value;
}
QString CsRUnstructSendStatus::getClientUuid() const
{
    return clientUuid;
}

void CsRUnstructSendStatus::setClientUuid(const QString &value)
{
    clientUuid = value;
}
QString CsRUnstructSendStatus::getSendFileUuid() const
{
    return sendFileUuid;
}

void CsRUnstructSendStatus::setSendFileUuid(const QString &value)
{
    sendFileUuid = value;
}
QString CsRUnstructSendStatus::getError() const
{
    return error;
}

void CsRUnstructSendStatus::setError(const QString &value)
{
    error = value;
}
QString CsRUnstructSendStatus::getTaskUuid() const
{
    return taskUuid;
}

void CsRUnstructSendStatus::setTaskUuid(const QString &value)
{
    taskUuid = value;
}

