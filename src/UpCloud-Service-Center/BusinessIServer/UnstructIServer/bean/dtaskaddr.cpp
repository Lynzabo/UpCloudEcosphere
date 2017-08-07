#include "dtaskaddr.h"

DTaskAddr::DTaskAddr()
{

}
QString DTaskAddr::getAddrUUID() const
{
    return addrUUID;
}

void DTaskAddr::setAddrUUID(const QString &value)
{
    addrUUID = value;
}
bool DTaskAddr::getIsGroup() const
{
    return isGroup;
}

void DTaskAddr::setIsGroup(bool value)
{
    isGroup = value;
}



