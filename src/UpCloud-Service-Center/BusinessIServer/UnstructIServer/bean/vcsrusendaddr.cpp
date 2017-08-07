#include "vcsrusendaddr.h"

VCsRUnstructSendAddr::VCsRUnstructSendAddr()
{

}
quint8 VCsRUnstructSendAddr::getState() const
{
    return state;
}

void VCsRUnstructSendAddr::setState(const quint8 &value)
{
    state = value;
}
QString VCsRUnstructSendAddr::getDescritpion() const
{
    return descritpion;
}

void VCsRUnstructSendAddr::setDescritpion(const QString &value)
{
    descritpion = value;
}





