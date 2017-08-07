#include "cssschedulesendaddr.h"

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
QChar CsSScheduleSendAddr::getState() const
{
    return state;
}

void CsSScheduleSendAddr::setState(const QChar &value)
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






