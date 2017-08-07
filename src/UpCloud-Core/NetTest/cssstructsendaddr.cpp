#include "cssstructsendaddr.h"

CsSStructSendAddr::CsSStructSendAddr()
{

}
QString CsSStructSendAddr::getUuid() const
{
    return uuid;
}

void CsSStructSendAddr::setUuid(const QString &value)
{
    uuid = value;
}
QString CsSStructSendAddr::getClientUuid() const
{
    return clientUuid;
}

void CsSStructSendAddr::setClientUuid(const QString &value)
{
    clientUuid = value;
}
QChar CsSStructSendAddr::getState() const
{
    return state;
}

void CsSStructSendAddr::setState(const QChar &value)
{
    state = value;
}
QString CsSStructSendAddr::getError() const
{
    return error;
}

void CsSStructSendAddr::setError(const QString &value)
{
    error = value;
}
QString CsSStructSendAddr::getTaskUuid() const
{
    return taskUuid;
}

void CsSStructSendAddr::setTaskUuid(const QString &value)
{
    taskUuid = value;
}






