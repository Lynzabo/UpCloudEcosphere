#include "structparsedata.h"

StructParseData::StructParseData()
{

}
quint32 StructParseData::getRef() const
{
    return ref;
}

void StructParseData::setRef(const quint32 &value)
{
    ref = value;
}
StructParseData::Type StructParseData::getType() const
{
    return type;
}

void StructParseData::setType(const Type &value)
{
    type = value;
}
QString StructParseData::getInfo() const
{
    return info;
}

void StructParseData::setInfo(const QString &value)
{
    info = value;
}




