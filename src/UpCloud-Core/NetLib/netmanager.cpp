#include "netmanager.h"

NetManager::NetBuilder::NetBuilder()
{
    net = new NetManager;
}

NetManager::NetBuilder::~NetBuilder()
{
    delete net;
}

NetManager::NetBuilder::NetBuilder(const SERVICE &service,
                                   const QString &hostname,
                                   const qint16 &port,
                                   const QString &username,
                                   const QString &password,
                                   const qint16 &asyncnum)
{
    net = new NetManager;
    net->service = service;
    net->hostname = hostname;
    net->port = port;
    net->username = username;
    net->password = password;
    net->asyncnum = asyncnum;
}

NetManager::NetBuilder *NetManager::NetBuilder::setService(const NetManager::SERVICE &service)
{
    net->service = service;
    return this;
}

NetManager::NetBuilder *NetManager::NetBuilder::setHostname(const QString &hostname)
{
    net->hostname = hostname;
    return this;
}

NetManager::NetBuilder *NetManager::NetBuilder::setPort(const qint16 &port)
{
    net->port = port;
    return this;
}

NetManager::NetBuilder *NetManager::NetBuilder::setUsername(const QString &username)
{
    net->username = username;
    return this;
}

NetManager::NetBuilder *NetManager::NetBuilder::setPassword(const QString &password)
{
    net->password = password;
    return this;
}

NetManager::NetBuilder *NetManager::NetBuilder::setAsyncnum(const qint16 &asyncnum)
{
    net->asyncnum = asyncnum;
    return this;
}


NetManager *NetManager::NetBuilder::build()
{
    return net;
}
