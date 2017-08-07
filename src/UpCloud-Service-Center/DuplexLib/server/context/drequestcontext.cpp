#include "drequestcontext.h"

DRequestContext::DRequestContext(const QString &clientKey, DataGramInfo *gram, const quint16 &ExecType, const QString &Params)
    :clientKey(clientKey)
    ,gram(gram)
    ,msgType(gram->msgType)
    ,UUID(gram->UUID)
    ,requestID(gram->requestID)
    ,timestamp(gram->timestamp)
    ,dataLength(gram->dataLength)
    ,message(gram->message)
    ,execType(ExecType)
    ,params(Params)
{
}
const quint16 &DRequestContext::getExecType() const
{
    return execType;
}
const QString &DRequestContext::getParams() const
{
    return params;
}
const QString &DRequestContext::getClientKey() const
{
    return clientKey;
}
const DataGramInfo *DRequestContext::getGram() const
{
    return gram;
}
const quint8 &DRequestContext::getMsgType() const
{
    return msgType;
}
const quint64 &DRequestContext::getUUID() const
{
    return UUID;
}
const QString &DRequestContext::getRequestID() const
{
    return requestID;
}
const quint64 &DRequestContext::getTimestamp() const
{
    return timestamp;
}
const quint32 &DRequestContext::getDataLength() const
{
    return dataLength;
}
const QString &DRequestContext::getMessage() const
{
    return message;
}












