#include "requestcontext.h"

RequestContext::RequestContext(QTcpSocket *client,const QString &clientKey,DataGramInfo *gram)
    :client(client)
    ,clientKey(clientKey)
    ,gram(gram)
    ,msgType(gram->msgType)
    ,UUID(gram->UUID)
    ,requestID(gram->requestID)
    ,timestamp(gram->timestamp)
    ,dataLength(gram->dataLength)
    ,message(gram->message)
{
}

RequestContext::~RequestContext()
{
    //
//    delete gram;
}

const QTcpSocket *RequestContext::getClient() const
{
    return client;
}

const QString &RequestContext::getClientKey() const
{
    return clientKey;
}

const DataGramInfo *RequestContext::getGram() const
{
    return gram;
}

const quint8 &RequestContext::getMsgType() const
{
    return msgType;
}

const quint64 &RequestContext::getUUID() const
{
    return UUID;
}

const QString &RequestContext::getRequestID() const
{
    return requestID;
}

const quint64 &RequestContext::getTimestamp() const
{
    return timestamp;
}

const quint32 &RequestContext::getDataLength() const
{
    return dataLength;
}

const QString &RequestContext::getMessage() const
{
    return message;
}
