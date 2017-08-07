#include "csrunstructsendstatus.h"

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
quint32 CsRUnstructSendStatus::getClientUuid() const
{
    return clientUuid;
}

void CsRUnstructSendStatus::setClientUuid(const quint32 &value)
{
    clientUuid = value;
}
quint32 CsRUnstructSendStatus::getSendFileUuid() const
{
    return sendFileUuid;
}

void CsRUnstructSendStatus::setSendFileUuid(const quint32 &value)
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
quint32 CsRUnstructSendStatus::getTaskUuid() const
{
    return taskUuid;
}

void CsRUnstructSendStatus::setTaskUuid(const quint32 &value)
{
    taskUuid = value;
}






