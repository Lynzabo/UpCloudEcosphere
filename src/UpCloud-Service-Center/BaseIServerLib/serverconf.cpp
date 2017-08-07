#include "serverconf.h"
#include <QSettings>
#include "baseiserver.h"

ServerConf::ServerConf(QObject *parent)  : QObject(parent)
{
    m_set = new QSettings(CSAbstPath::getInstance().confAbst()+"CenterServer-server.conf", QSettings::IniFormat);
}

void ServerConf::getNodeMainPort(quint16 &nodeMainPort)
{
   nodeMainPort = (quint16)m_set->value("upCloud.server.connection.node.main.port").toUInt();
}

void ServerConf::getNodeMainTimeout(quint32 &nodeMainTimeout)
{
    nodeMainTimeout = m_set->value("upCloud.server.connection.node.main.timeout",1000).toUInt();
}

void ServerConf::getNodeMainBlockSize(quint32 &nodeMainBlockSize)
{
    nodeMainBlockSize = m_set->value("upCloud.server.connection.node.main.blockSize",4096).toUInt();
}

void ServerConf::getNOdeMainWriteTimeout(quint32 &nodeMainWriteTimeout)
{
    nodeMainWriteTimeout = m_set->value("upCloud.server.connection.node.main.writeTimeout",5000).toUInt();
}

void ServerConf::getNodeMainReadTimeout(quint32 &nodeMainReadTimeout)
{
    nodeMainReadTimeout = m_set->value("upCloud.server.connection.node.main.readTimeout",5000).toUInt();
}

void ServerConf::getUiMainPort(quint16 &uiMainPort)
{
    uiMainPort = m_set->value("upCloud.server.connection.ui.main.port").toUInt();
}

void ServerConf::getUiMainTimeout(quint32 &uiMainTimeout)
{
    uiMainTimeout = m_set->value("upCloud.server.connection.ui.main.timeout",1000).toUInt();
}

void ServerConf::getUiMainBlockSize(quint32 &uiMainBlockSize)
{
    uiMainBlockSize = m_set->value("upCloud.server.connection.ui.main.blockSize",4096).toUInt();
}

void ServerConf::getUiMainWriteTimeout(quint32 &uiMainWriteTimeout)
{
    uiMainWriteTimeout = m_set->value("upCloud.server.connection.ui.main.writeTimeout",5000).toUInt();
}

void ServerConf::getUiMainReadTimeout(quint32 &uiMainReadTimeout)
{
    uiMainReadTimeout = m_set->value("upCloud.server.connection.ui.main.readTimeout",5000).toUInt();
}

void ServerConf::getUnStructScanTaskCycle(quint32 &scanTaskCycle)
{
    scanTaskCycle = m_set->value("upCloud.server.connection.node.unStruct.scanTaskCycle",10000).toUInt();
}

void ServerConf::getStructScanTaskCycle(quint32 &scanTaskCycle)
{
    scanTaskCycle = m_set->value("upCloud.server.connection.node.struct.scanTaskCycle",5000).toUInt();
}

void ServerConf::getScheduleTaskScanTaskCycle(quint32 &scanTaskCycle)
{
    scanTaskCycle = m_set->value("upCloud.server.connection.node.scheduleTask.scanTaskCycle",3000).toUInt();
}

void ServerConf::getUnstructTaskTimeout(quint32 &timeout)
{
    timeout = m_set->value("upCloud.server.scanning.unstructTask.timeout", 5000).toUInt();
}

void ServerConf::getStructTaskTimeout(quint32 &timeout)
{
    timeout = m_set->value("upCloud.server.scanning.structTask.timeout", 5000).toUInt();
}

void ServerConf::getScheduleTaskTimeout(quint32 &timeout)
{
    timeout = m_set->value("upCloud.server.scanning.scheduleTask.timeout", 5000).toUInt();
}

void ServerConf::getFtpRootPath(QString &ftpRootPath)
{
    ftpRootPath = m_set->value("upCloud.server.ftp.rootPath").toString();
}

void ServerConf::getFtpAddr(QString &ftpAddr)
{
    ftpAddr = m_set->value("upCloud.server.ftp.addr").toString();
}
