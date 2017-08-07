#include "cssusendaddr.h"


QString CsSUnstructSendAddr::getGroupUuuids() const
{
    return groupUuuids;
}

void CsSUnstructSendAddr::setGroupUuuids(const QString &value)
{
    groupUuuids = value;
}
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


QString CsSUnstructSendAddr::getTaskUuid() const
{
    return taskUuid;
}

void CsSUnstructSendAddr::setTaskUuid(const QString &value)
{
    taskUuid = value;
}






