#include "csrstructsendaddr.h"

CsRStructSendAddr::CsRStructSendAddr()
{

}
QString CsRStructSendAddr::getUuid() const
{
    return uuid;
}

void CsRStructSendAddr::setUuid(const QString &value)
{
    uuid = value;
}
QString CsRStructSendAddr::getClientUuid() const
{
    return clientUuid;
}

void CsRStructSendAddr::setClientUuid(const QString &value)
{
    clientUuid = value;
}
QChar CsRStructSendAddr::getState() const
{
    return state;
}

void CsRStructSendAddr::setState(const QChar &value)
{
    state = value;
}
QString CsRStructSendAddr::getError() const
{
    return error;
}

void CsRStructSendAddr::setError(const QString &value)
{
    error = value;
}
QString CsRStructSendAddr::getTaskUuid() const
{
    return taskUuid;
}

void CsRStructSendAddr::setTaskUuid(const QString &value)
{
    taskUuid = value;
}






