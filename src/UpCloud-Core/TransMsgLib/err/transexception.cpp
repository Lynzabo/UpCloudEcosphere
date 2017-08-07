#include "transexception.h"

TransException::TransException()
{

}
quint8 TransException::getType() const
{
    return type;
}

void TransException::setType(const quint8 &value)
{
    type = value;
}
QString TransException::getText() const
{
    return text;
}

void TransException::setText(const QString &value)
{
    text = value;
}



