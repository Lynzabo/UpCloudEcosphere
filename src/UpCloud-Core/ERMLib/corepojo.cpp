#include "corepojo.h"

CorePOJO::CorePOJO()
{

}
quint16 CorePOJO::getState() const
{
    return state;
}

void CorePOJO::setState(const quint16 &value)
{
    state = value;
}
QString CorePOJO::getStateDesc() const
{
    return stateDesc;
}

void CorePOJO::setStateDesc(const QString &value)
{
    stateDesc = value;
}
QString CorePOJO::getContent() const
{
    return content;
}

void CorePOJO::setContent(const QString &value)
{
    content = value;
}




