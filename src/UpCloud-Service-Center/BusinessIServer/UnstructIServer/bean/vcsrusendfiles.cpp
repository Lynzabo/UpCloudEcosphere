#include "vcsrusendfiles.h"

VCsRUnstructSendFiles::VCsRUnstructSendFiles()
{

}
quint8 VCsRUnstructSendFiles::getState() const
{
    return state;
}

void VCsRUnstructSendFiles::setState(const quint8 &value)
{
    state = value;
}


