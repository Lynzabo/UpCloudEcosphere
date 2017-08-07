#include "cscextendinfo.h"

CsClientExtendInfo::CsClientExtendInfo()
{

}

QString CsClientExtendInfo::getUUID() const
{
    return UUID;
}

void CsClientExtendInfo::setUUID(const QString &value)
{
    UUID = value;
}

quint64 CsClientExtendInfo::getTerminalUUID() const
{
    return terminalUUID;
}

void CsClientExtendInfo::setTerminalUUID(const quint64 &value)
{
    terminalUUID = value;
}

quint8 CsClientExtendInfo::getType() const
{
    return type;
}

void CsClientExtendInfo::setType(const quint8 &value)
{
    type = value;
}

QString CsClientExtendInfo::getDescription() const
{
    return description;
}

void CsClientExtendInfo::setDescription(const QString &value)
{
    description = value;
}

QString CsClientExtendInfo::getIP() const
{
    return IP;
}

void CsClientExtendInfo::setIP(const QString &value)
{
    IP = value;
}

QString CsClientExtendInfo::getMacAddr() const
{
    return macAddr;
}

void CsClientExtendInfo::setMacAddr(const QString &value)
{
    macAddr = value;
}

QString CsClientExtendInfo::getPubKey() const
{
    return pubKey;
}

void CsClientExtendInfo::setPubKey(const QString &value)
{
    pubKey = value;
}

QString CsClientExtendInfo::getPriKey() const
{
    return priKey;
}

void CsClientExtendInfo::setPriKey(const QString &value)
{
    priKey = value;
}

quint8 CsClientExtendInfo::getState() const
{
    return state;
}

void CsClientExtendInfo::setState(const quint8 &value)
{
    state = value;
}

quint8 CsClientExtendInfo::getRunState() const
{
    return runState;
}

void CsClientExtendInfo::setRunState(const quint8 &value)
{
    runState = value;
}

QString CsClientExtendInfo::getCreateTime() const
{
    return createTime;
}

void CsClientExtendInfo::setCreateTime(const QString &value)
{
    createTime = value;
}

QString CsClientExtendInfo::getOnlineTime() const
{
    return onlineTime;
}

void CsClientExtendInfo::setOnlineTime(const QString &value)
{
    onlineTime = value;
}

QString CsClientExtendInfo::getOfflineTime() const
{
    return offlineTime;
}

void CsClientExtendInfo::setOfflineTime(const QString &value)
{
    offlineTime = value;
}




