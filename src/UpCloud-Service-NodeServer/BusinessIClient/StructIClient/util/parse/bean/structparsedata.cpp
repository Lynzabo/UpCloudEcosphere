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
QVariantMap StructParseData::getParams() const
{
    return params;
}

void StructParseData::setParams(const QVariantMap &value)
{
    params = value;
}

void StructParseData::setParamsArgs(const QString &key, const QString &value)
{
    params.insert(key, value);
}

void StructParseData::clear()
{
    ref = 0;
    type = Select;
    info = "";
    params.clear();
}





