#include "cscgroup.h"

CsClientGroup::CsClientGroup()
{

}
QString CsClientGroup::getUuid() const
{
    return uuid;
}

void CsClientGroup::setUuid(const QString &value)
{
    uuid = value;
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
QString CsClientGroup::getSupUuid() const
{
    return supUuid;
}

void CsClientGroup::setSupUuid(const QString &value)
{
    supUuid = value;
}
quint32 CsClientGroup::getSequence() const
{
    return sequence;
}

void CsClientGroup::setSequence(const quint32 &value)
{
    sequence = value;
}
quint8 CsClientGroup::getState() const
{
    return state;
}

void CsClientGroup::setState(const quint8 &value)
{
    state = value;
}
QString CsClientGroup::getInsertor() const
{
    return insertor;
}

void CsClientGroup::setInsertor(const QString &value)
{
    insertor = value;
}
QString CsClientGroup::getInsertTime() const
{
    return insertTime;
}

void CsClientGroup::setInsertTime(const QString &value)
{
    insertTime = value;
}
QString CsClientGroup::getOperater() const
{
    return operater;
}

void CsClientGroup::setOperater(const QString &value)
{
    operater = value;
}
QString CsClientGroup::getOperatTime() const
{
    return operatTime;
}

void CsClientGroup::setOperatTime(const QString &value)
{
    operatTime = value;
}

void CsClientGroup::clear()
{
    setUuid("");
    setName("");
    setDescription("");
    setSupUuid("");
    setSequence((qint32)-2);
    setState((quint8)0);
    setInsertor("");
    setInsertTime("");
    setOperater("");
    setOperatTime("");
}











