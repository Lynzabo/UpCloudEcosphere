#include "syspermission.h"



QString SysPermission::getUserName(const QString userUUID)
{
    return QString();
}

QList<QString> SysPermission::getUserUUIDs(const QList<QString> userNames)
{
    return {};
}

SINGLETON_ALL_IN_ONE(SysPermission)

