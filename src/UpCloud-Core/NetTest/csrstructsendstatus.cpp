#include "csrstructsendstatus.h"

CsRStructSendStatus::CsRStructSendStatus()
{

}
QString CsRStructSendStatus::getUuid() const
{
    return uuid;
}

void CsRStructSendStatus::setUuid(const QString &value)
{
    uuid = value;
}
QString CsRStructSendStatus::getClientUuid() const
{
    return clientUuid;
}

void CsRStructSendStatus::setClientUuid(const QString &value)
{
    clientUuid = value;
}
QString CsRStructSendStatus::getSendFileUuid() const
{
    return sendFileUuid;
}

void CsRStructSendStatus::setSendFileUuid(const QString &value)
{
    sendFileUuid = value;
}
QString CsRStructSendStatus::getError() const
{
    return error;
}

void CsRStructSendStatus::setError(const QString &value)
{
    error = value;
}
QString CsRStructSendStatus::getTaskUuid() const
{
    return taskUuid;
}

void CsRStructSendStatus::setTaskUuid(const QString &value)
{
    taskUuid = value;
}






