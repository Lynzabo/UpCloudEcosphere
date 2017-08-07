#include "cssscsendaddr.h"

CsSScheduleSendAddr::CsSScheduleSendAddr()
{

}
QString CsSScheduleSendAddr::getUuid() const
{
    return uuid;
}

void CsSScheduleSendAddr::setUuid(const QString &value)
{
    uuid = value;
}
QString CsSScheduleSendAddr::getClientUuid() const
{
    return clientUuid;
}

void CsSScheduleSendAddr::setClientUuid(const QString &value)
{
    clientUuid = value;
}
quint8 CsSScheduleSendAddr::getState() const
{
    return state;
}

void CsSScheduleSendAddr::setState(const quint8 &value)
{
    state = value;
}
QString CsSScheduleSendAddr::getError() const
{
    return error;
}

void CsSScheduleSendAddr::setError(const QString &value)
{
    error = value;
}
QString CsSScheduleSendAddr::getTaskUuid() const
{
    return taskUuid;
}

void CsSScheduleSendAddr::setTaskUuid(const QString &value)
{
    taskUuid = value;
}






