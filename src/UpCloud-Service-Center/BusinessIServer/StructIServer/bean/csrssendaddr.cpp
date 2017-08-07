#include "csrssendaddr.h"



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


QString CsRStructSendAddr::getTaskUuid() const
{
    return taskUuid;
}

void CsRStructSendAddr::setTaskUuid(const QString &value)
{
    taskUuid = value;
}

QString CsRStructSendAddr::getGroupDesc() const
{
    return groupDesc;
}

void CsRStructSendAddr::setGroupDesc(const QString &value)
{
    groupDesc = value;
}




