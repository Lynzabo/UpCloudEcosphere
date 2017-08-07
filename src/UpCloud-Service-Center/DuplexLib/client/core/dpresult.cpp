#include "dpresult.h"

DPResult::DPResult(const DeplexDefs::Priority &sMPriority, const quint16 &sExecType, const QString &sParams, const quint8 &rState, const QString &rContent)
{
    this->sMPriority = sMPriority;
    this->sExecType = sExecType;
    this->sParams = sParams;
    this->rState = rState;
    this->rContent = rContent;
}

DeplexDefs::Priority DPResult::getSMPriority() const
{
    return sMPriority;
}

quint16 DPResult::getSExecType() const
{
    return sExecType;
}

QString DPResult::getSParams() const
{
    return sParams;
}

quint8 DPResult::getRState() const
{
    return rState;
}

QString DPResult::getRContent() const
{
    return rContent;
}
void DPResult::setRContent(const QString &value)
{
    rContent = value;
}
void DPResult::setRState(const quint8 &value)
{
    rState = value;
}








