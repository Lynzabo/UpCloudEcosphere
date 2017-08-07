#include "dresponsecontext.h"

DResponseContext::DResponseContext(const QString &clientKey, const quint16 &ExecType, const QString &Params)
    :clientKey(clientKey)
    ,execType(ExecType)
    ,params(Params)
{
    responseContent.clear();
    responseState = 0;
}
const quint16 &DResponseContext::getExecType() const
{
    return execType;
}
const QString &DResponseContext::getParams() const
{
    return params;
}
quint8 DResponseContext::getResponseState() const
{
    return responseState;
}

void DResponseContext::setResponseState(const quint8 &value)
{
    responseState = value;
}
QString DResponseContext::getResponseContent() const
{
    return responseContent;
}

void DResponseContext::setResponseContent(const QString &value)
{
    responseContent = value;
}






