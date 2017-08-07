#include "netconf.h"
#include "baseiremote.h"

NetConf::NetConf(QObject *parent) : QObject(parent)
{
    m_set = new QSettings(RUAbstPath::getInstance().confAbst()+"NodeServer-net.conf", QSettings::IniFormat);
}

NetConf::~NetConf()
{
    delete m_set;
    m_set = NULL;
}

void NetConf::getFtpHostname(QString &hostname)
{
    hostname = m_set->value("upCloud.net.transfer.binarystream.ftp.ip").toString();
}

void NetConf::getFtpPort(qint16 &port)
{
    port = (quint16)m_set->value("upCloud.net.transfer.binarystream.ftp.port").toUInt();
}

void NetConf::getFtpUsername(QString &username)
{
    username = m_set->value("upCloud.net.transfer.binarystream.ftp.username").toString();
}

void NetConf::getFtpPassword(QString &password)
{
    password = m_set->value("upCloud.net.transfer.binarystream.ftp.password").toString();
}

void NetConf::getFtpIIsNum(int &iisNum)
{
    iisNum = m_set->value("upCloud.net.transfer.binarystream.ftp.iisNum").toInt();
}

void NetConf::getFtpDownThreadsNum(int &downThreadsNum)
{
    downThreadsNum = m_set->value("upCloud.net.transfer.binarystream.ftp.downThreadsNum").toInt();
}

void NetConf::getHttpIIsNum(int &iisNum)
{
    iisNum = m_set->value("upCloud.net.transfer.binarystream.http.iisNum").toInt();
}

void NetConf::getHttpDownThreadsNum(int &downThreadsNum)
{
    downThreadsNum = m_set->value("upCloud.net.transfer.binarystream.http.downThreadsNum").toInt();
}

