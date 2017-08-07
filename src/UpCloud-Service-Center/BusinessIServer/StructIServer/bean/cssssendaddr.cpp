#include "cssssendaddr.h"

QString CsSStructSendAddr::getGroupDesc() const
{
    return groupDesc;
}

void CsSStructSendAddr::setGroupDesc(const QString &value)
{
    groupDesc = value;
}

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

QString CsSStructSendAddr::getTaskUuid() const
{
    return taskUuid;
}

void CsSStructSendAddr::setTaskUuid(const QString &value)
{
    taskUuid = value;
}






