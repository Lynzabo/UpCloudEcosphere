#include "csrunstructsendaddr.h"

CsRUnstructSendAddr::CsRUnstructSendAddr()
{

}
QString CsRUnstructSendAddr::getUuid() const
{
    return uuid;
}

void CsRUnstructSendAddr::setUuid(const QString &value)
{
    uuid = value;
}
quint32 CsRUnstructSendAddr::getClientUuid() const
{
    return clientUuid;
}

void CsRUnstructSendAddr::setClientUuid(const quint32 &value)
{
    clientUuid = value;
}
QChar CsRUnstructSendAddr::getState() const
{
    return state;
}

void CsRUnstructSendAddr::setState(const QChar &value)
{
    state = value;
}
QString CsRUnstructSendAddr::getError() const
{
    return error;
}

void CsRUnstructSendAddr::setError(const QString &value)
{
    error = value;
}
quint32 CsRUnstructSendAddr::getTaskUuid() const
{
    return taskUuid;
}

void CsRUnstructSendAddr::setTaskUuid(const quint32 &value)
{
    taskUuid = value;
}






