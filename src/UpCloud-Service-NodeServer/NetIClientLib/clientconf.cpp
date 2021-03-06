#include "clientconf.h"
#include "base.h"

using namespace  AbstPath;
ClientConf::ClientConf(QObject *parent) : QObject(parent)
{
    m_set = new QSettings(AbstPath::confAbst()+"NodeServer-client.conf", QSettings::IniFormat);
}

void ClientConf::getLocalhost(QString &localhost)
{
    localhost = m_set->value("upCloud.server.address").toString();
}

void ClientConf::getMainPort(quint16 &mainPort)
{
    mainPort = (quint16)m_set->value("upCloud.server.connection.node.main.port").toUInt();
}

void ClientConf::getMainTimeout(quint32 &mainTimeout)
{
    mainTimeout = m_set->value("upCloud.client.connection.main.timeout",5000).toUInt();
}

void ClientConf::getMainBlockSize(quint32 &blockSize)
{
    blockSize = m_set->value("upCloud.client.connection.main.blockSize",4096).toUInt();
}

void ClientConf::getMainInterval(quint32 &interval)
{
    interval = m_set->value("upCloud.client.connection.main.interval",3).toUInt();
}

void ClientConf::getMainWriteTimeout(quint32 &writeTimeout)
{
    writeTimeout = m_set->value("upCloud.client.connection.main.writeTimeout",5000).toUInt();
}

void ClientConf::getMainReadTimeout(quint32 &readTimeout)
{
    readTimeout = m_set->value("upCloud.client.connection.main.readTimeout",5000).toUInt();
}

void ClientConf::getUnStructScanTaskCycle(quint32 &scanTaskCycle)
{
    scanTaskCycle = m_set->value("upCloud.client.connection.unStruct.scanTaskCycle",10000).toUInt();
}

void ClientConf::getStructScanTaskCycle(quint32 &scanTaskCycle)
{
    scanTaskCycle = m_set->value("upCloud.client.connection.struct.scanTaskCycle",5000).toUInt();
}

void ClientConf::getScheduleTaskScanTaskCycle(quint32 &scanTaskCycle)
{
    scanTaskCycle = m_set->value("upCloud.client.connection.scheduleTask.scanTaskCycle",3000).toUInt();
}

void ClientConf::getHeartthrobTimeout(quint32 &timeout)
{
    timeout = m_set->value("upCloud.client.connection.heartthrob.timeout", 5000).toUInt();
}

void ClientConf::getUnstructTaskTimeout(quint32 &timeout)
{
    timeout = m_set->value("upCloud.client.scanning.unstructTask.timeout", 5000).toUInt();
}

void ClientConf::getStructTaskTimeout(quint32 &timeout)
{
    timeout = m_set->value("upCloud.client.scanning.structTask.timeout", 5000).toUInt();
}

void ClientConf::getScheduleTaskTimeout(quint32 &timeout)
{
    timeout = m_set->value("upCloud.client.scanning.scheduleTask.timeout", 5000).toUInt();
}
