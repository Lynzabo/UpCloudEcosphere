#include "csdict.h"

CsDict::CsDict()
{

}
QString CsDict::getUuid() const
{
    return uuid;
}

void CsDict::setUuid(const QString &value)
{
    uuid = value;
}
QString CsDict::getCode() const
{
    return code;
}

void CsDict::setCode(const QString &value)
{
    code = value;
}
QString CsDict::getName() const
{
    return name;
}

void CsDict::setName(const QString &value)
{
    name = value;
}
QString CsDict::getDescription() const
{
    return description;
}

void CsDict::setDescription(const QString &value)
{
    description = value;
}
qint32 CsDict::getSequence() const
{
    return sequence;
}

void CsDict::setSequence(const qint32 &value)
{
    sequence = value;
}

quint8 CsDict::getState() const
{
    return state;
}

void CsDict::setState(const quint8 &value)
{
    state = value;
}
QString CsDict::getInsertor() const
{
    return insertor;
}

void CsDict::setInsertor(const QString &value)
{
    insertor = value;
}
QString CsDict::getInsertTime() const
{
    return insertTime;
}

void CsDict::setInsertTime(const QString &value)
{
    insertTime = value;
}
QString CsDict::getOperater() const
{
    return operater;
}

void CsDict::setOperater(const QString &value)
{
    operater = value;
}
QString CsDict::getOperaTime() const
{
    return operaTime;
}

void CsDict::setOperaTime(const QString &value)
{
    operaTime = value;
}
QString CsDict::getSupUuid() const
{
    return supUuid;
}

void CsDict::setSupUuid(const QString &value)
{
    supUuid = value;
}













