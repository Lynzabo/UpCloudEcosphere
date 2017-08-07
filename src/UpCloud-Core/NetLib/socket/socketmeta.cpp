#include "socketmeta.h"


SocketMeta::Protocol SocketMeta::getProtocol() const
{
    return protocol;
}

QString SocketMeta::getHostname() const
{
    return hostname;
}

qint16 SocketMeta::getPort() const
{
    return port;
}

quint32 SocketMeta::getTimeout() const
{
    return timeout;
}
quint32 SocketMeta::getBlockSize() const
{
    return blockSize;
}
quint32 SocketMeta::getInterval() const
{
    return interval;
}
int SocketMeta::getWriteTimeout() const
{
    return writeTimeout;
}
int SocketMeta::getReadTimeout() const
{
    return readTimeout;
}

SocketMeta::Builder::Builder()
{
    net = new SocketMeta;
}

SocketMeta::Builder::~Builder()
{
    delete net;
}

SocketMeta::Builder::Builder(const Protocol &protocol,
                             const QString &hostname,
                             const quint16 &port,
                             const quint32 &timeout,
                              const quint32 &blockSize,
                              const quint32 &interval)
{
    net = new SocketMeta;
    net->protocol = protocol;
    net->hostname = hostname;
    net->port = port;
    net->timeout = timeout;
    net->blockSize = blockSize;
    net->interval = interval;
}

SocketMeta::Builder *SocketMeta::Builder::setProtocol(const SocketMeta::Protocol &value)
{
    net->protocol = value;
    return this;
}

SocketMeta::Builder *SocketMeta::Builder::setHostname(const QString &value)
{
    net->hostname = value;
    return this;
}

SocketMeta::Builder *SocketMeta::Builder::setPort(const quint16 &value)
{
    net->port = value;
    return this;
}

SocketMeta::Builder *SocketMeta::Builder::setTimeout(const quint32 &value)
{
    net->timeout = value;
    return this;
}

SocketMeta::Builder *SocketMeta::Builder::setBlockSize(const quint32 &value)
{
    net->blockSize = value;
    return this;
}

SocketMeta::Builder *SocketMeta::Builder::setInterval(const quint32 &value)
{
    net->interval = value;
    return this;
}

SocketMeta::Builder *SocketMeta::Builder::setWriteTimeout(int value)
{
    net->writeTimeout = value;
    return this;
}

SocketMeta::Builder *SocketMeta::Builder::setReadTimeout(int value)
{
    net->readTimeout = value;
    return this;
}

SocketMeta *SocketMeta::Builder::build()
{
    return net;
}
