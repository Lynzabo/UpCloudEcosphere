#include "vcsascsendfiles.h"

VCsAScSendFiles::VCsAScSendFiles()
{

}
quint8 VCsAScSendFiles::getState() const
{
    return state;
}

void VCsAScSendFiles::setState(const quint8 &value)
{
    state = value;
}
QString VCsAScSendFiles::getErrMsg() const
{
    return errMsg;
}

void VCsAScSendFiles::setErrMsg(const QString &value)
{
    errMsg = value;
}



