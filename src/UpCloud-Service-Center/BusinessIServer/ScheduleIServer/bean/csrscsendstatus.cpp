#include "csrscsendstatus.h"

CsRScheduleSendStatus::CsRScheduleSendStatus()
{

}
QString CsRScheduleSendStatus::getUuid() const
{
    return uuid;
}

void CsRScheduleSendStatus::setUuid(const QString &value)
{
    uuid = value;
}
QString CsRScheduleSendStatus::getClientUuid() const
{
    return clientUuid;
}

void CsRScheduleSendStatus::setClientUuid(const QString &value)
{
    clientUuid = value;
}
QString CsRScheduleSendStatus::getSendFileUuid() const
{
    return sendFileUuid;
}

void CsRScheduleSendStatus::setSendFileUuid(const QString &value)
{
    sendFileUuid = value;
}
QString CsRScheduleSendStatus::getError() const
{
    return error;
}

void CsRScheduleSendStatus::setError(const QString &value)
{
    error = value;
}
QString CsRScheduleSendStatus::getTaskUuid() const
{
    return taskUuid;
}

void CsRScheduleSendStatus::setTaskUuid(const QString &value)
{
    taskUuid = value;
}






