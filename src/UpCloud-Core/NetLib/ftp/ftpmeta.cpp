#include "ftpmeta.h"

FtpMeta::Builder::Builder()
{
    net = new FtpMeta;
}

FtpMeta::Builder::~Builder()
{
    delete net;
}

FtpMeta::Builder::Builder(const QString &hostname,
                                   const qint16 &port,
                                   const QString &username,
                                   const QString &password)
{
    net = new FtpMeta;
    net->hostname = hostname;
    net->port = port;
    net->username = username;
    net->password = password;
}


FtpMeta::Builder *FtpMeta::Builder::setHostname(const QString &hostname)
{
    net->hostname = hostname;
    return this;
}

FtpMeta::Builder *FtpMeta::Builder::setPort(const qint16 &port)
{
    net->port = port;
    return this;
}

FtpMeta::Builder *FtpMeta::Builder::setUsername(const QString &username)
{
    net->username = username;
    return this;
}

FtpMeta::Builder *FtpMeta::Builder::setPassword(const QString &password)
{
    net->password = password;
    return this;
}

FtpMeta *FtpMeta::Builder::build()
{
    return net;
}

QString FtpMeta::getHostname() const
{
    return hostname;
}
qint16 FtpMeta::getPort() const
{
    return port;
}
QString FtpMeta::getUsername() const
{
    return username;
}
QString FtpMeta::getPassword() const
{
    return password;
}



