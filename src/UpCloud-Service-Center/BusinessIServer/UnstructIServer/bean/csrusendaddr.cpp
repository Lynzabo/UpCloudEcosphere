#include "csrusendaddr.h"
CsRUnstructSendAddr::CsRUnstructSendAddr()
{

}
QString CsRUnstructSendAddr::getGroupDesc() const
{
    return groupDesc;
}

void CsRUnstructSendAddr::setGroupDesc(const QString &value)
{
    groupDesc = value;
}
QString CsRUnstructSendAddr::getUuid() const
{
    return uuid;
}

void CsRUnstructSendAddr::setUuid(const QString &value)
{
    uuid = value;
}
QString CsRUnstructSendAddr::getClientUuid() const
{
    return clientUuid;
}

void CsRUnstructSendAddr::setClientUuid(const QString &value)
{
    clientUuid = value;
}


QString CsRUnstructSendAddr::getTaskUuid() const
{
    return taskUuid;
}

void CsRUnstructSendAddr::setTaskUuid(const QString &value)
{
    taskUuid = value;
}
