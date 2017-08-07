#include "cscgroupassoc.h"

CsClientGroupAssoc::CsClientGroupAssoc()
{

}
QString CsClientGroupAssoc::getUuid() const
{
    return uuid;
}

void CsClientGroupAssoc::setUuid(const QString &value)
{
    uuid = value;
}
QString CsClientGroupAssoc::getClientUuid() const
{
    return clientUuid;
}

void CsClientGroupAssoc::setClientUuid(const QString &value)
{
    clientUuid = value;
}
QString CsClientGroupAssoc::getGroupUuid() const
{
    return groupUuid;
}

void CsClientGroupAssoc::setGroupUuid(const QString &value)
{
    groupUuid = value;
}
QString CsClientGroupAssoc::getInsertor() const
{
    return insertor;
}

void CsClientGroupAssoc::setInsertor(const QString &value)
{
    insertor = value;
}
QString CsClientGroupAssoc::getInsertTime() const
{
    return insertTime;
}

void CsClientGroupAssoc::setInsertTime(const QString &value)
{
    insertTime = value;
}
qint32 CsClientGroupAssoc::getSequence() const
{
    return sequence;
}

void CsClientGroupAssoc::setSequence(const qint32 &value)
{
    sequence = value;
}
quint16 CsClientGroupAssoc::getState() const
{
    return state;
}

void CsClientGroupAssoc::setState(const quint16 &value)
{
    state = value;
}








