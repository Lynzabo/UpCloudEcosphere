#include "cssunstructsendaddr.h"

CsSUnstructSendAddr::CsSUnstructSendAddr()
{

}
QString CsSUnstructSendAddr::getUuid() const
{
    return uuid;
}

void CsSUnstructSendAddr::setUuid(const QString &value)
{
    uuid = value;
}
QString CsSUnstructSendAddr::getClientUuid() const
{
    return clientUuid;
}

void CsSUnstructSendAddr::setClientUuid(const QString &value)
{
    clientUuid = value;
}
QChar CsSUnstructSendAddr::getState() const
{
    return state;
}

void CsSUnstructSendAddr::setState(const QChar &value)
{
    state = value;
}
QString CsSUnstructSendAddr::getError() const
{
    return error;
}

void CsSUnstructSendAddr::setError(const QString &value)
{
    error = value;
}
QString CsSUnstructSendAddr::getTaskUuid() const
{
    return taskUuid;
}

void CsSUnstructSendAddr::setTaskUuid(const QString &value)
{
    taskUuid = value;
}






