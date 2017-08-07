#include "csclientextendinfo.h"

CsClientExtendInfo::CsClientExtendInfo()
{

}
QString CsClientExtendInfo::getUuid() const
{
    return uuid;
}

void CsClientExtendInfo::setUuid(const QString &value)
{
    uuid = value;
}
QString CsClientExtendInfo::getClientUuid() const
{
    return clientUuid;
}

void CsClientExtendInfo::setClientUuid(const QString &value)
{
    clientUuid = value;
}
QString CsClientExtendInfo::getDescription() const
{
    return description;
}

void CsClientExtendInfo::setDescription(const QString &value)
{
    description = value;
}
QChar CsClientExtendInfo::getType() const
{
    return type;
}

void CsClientExtendInfo::setType(const QChar &value)
{
    type = value;
}
QString CsClientExtendInfo::getGroupUuid() const
{
    return groupUuid;
}

void CsClientExtendInfo::setGroupUuid(const QString &value)
{
    groupUuid = value;
}






