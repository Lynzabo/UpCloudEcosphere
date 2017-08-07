#include "csclientgroup.h"


QString CsClientGroup::getUuid() const
{
    return uuid;
}

void CsClientGroup::setUuid(const QString &value)
{
    uuid = value;
}
CsClientGroup::CsClientGroup()
{

}

QString CsClientGroup::getName() const
{
    return name;
}

void CsClientGroup::setName(const QString &value)
{
    name = value;
}
QString CsClientGroup::getDescription() const
{
    return description;
}

void CsClientGroup::setDescription(const QString &value)
{
    description = value;
}
QString CsClientGroup::getParentUuid() const
{
    return parentUuid;
}

void CsClientGroup::setParentUuid(const QString &value)
{
    parentUuid = value;
}
quint32 CsClientGroup::getSequence() const
{
    return sequence;
}

void CsClientGroup::setSequence(const quint32 &value)
{
    sequence = value;
}






