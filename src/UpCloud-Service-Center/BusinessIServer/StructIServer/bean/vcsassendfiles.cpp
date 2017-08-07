#include "vcsassendfiles.h"

VCsRStructSendFiles::VCsRStructSendFiles()
{

}
quint8 VCsRStructSendFiles::getState() const
{
    return state;
}

void VCsRStructSendFiles::setState(const quint8 &value)
{
    state = value;
}



