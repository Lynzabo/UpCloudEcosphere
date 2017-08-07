#include "csrscsendaddr.h"

CsRScheduleSendAddr::CsRScheduleSendAddr()
{

}
QString CsRScheduleSendAddr::getUuid() const
{
    return uuid;
}

void CsRScheduleSendAddr::setUuid(const QString &value)
{
    uuid = value;
}
QString CsRScheduleSendAddr::getClientUuid() const
{
    return clientUuid;
}

void CsRScheduleSendAddr::setClientUuid(const QString &value)
{
    clientUuid = value;
}
quint8 CsRScheduleSendAddr::getState() const
{
    return state;
}

void CsRScheduleSendAddr::setState(const quint8 &value)
{
    state = value;
}
QString CsRScheduleSendAddr::getError() const
{
    return error;
}

void CsRScheduleSendAddr::setError(const QString &value)
{
    error = value;
}
QString CsRScheduleSendAddr::getTaskUuid() const
{
    return taskUuid;
}

void CsRScheduleSendAddr::setTaskUuid(const QString &value)
{
    taskUuid = value;
}






