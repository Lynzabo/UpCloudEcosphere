#include "vcssendaddr.h"

VCsRStructSendAddr::VCsRStructSendAddr()
{

}

quint8 VCsRStructSendAddr::getState() const
{
    return state;
}

void VCsRStructSendAddr::setState(const quint8 &value)
{
    state = value;
}

QString VCsRStructSendAddr::getDescription() const
{
    return description;
}

void VCsRStructSendAddr::setDescription(const QString &value)
{
    description = value;
}

