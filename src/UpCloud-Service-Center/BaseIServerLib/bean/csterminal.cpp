#include "csterminal.h"

CsTerminal::CsTerminal()
{

}
QString CsTerminal::getUUID() const
{
    return UUID;
}

void CsTerminal::setUUID(const QString &value)
{
    UUID = value;
}
quint64 CsTerminal::getTerminalUUID() const
{
    return terminalUUID;
}

void CsTerminal::setTerminalUUID(const quint64 &value)
{
    terminalUUID = value;
}

quint8 CsTerminal::getType() const
{
    return type;
}

void CsTerminal::setType(const quint8 &value)
{
    type = value;
}

QString CsTerminal::getDescription() const
{
    return description;
}

void CsTerminal::setDescription(const QString &value)
{
    description = value;
}

QString CsTerminal::getIP() const
{
    return IP;
}

void CsTerminal::setIP(const QString &value)
{
    IP = value;
}

QString CsTerminal::getPubKey() const
{
    return pubKey;
}

void CsTerminal::setPubKey(const QString &value)
{
    pubKey = value;
}

QString CsTerminal::getPriKey() const
{
    return priKey;
}

void CsTerminal::setPriKey(const QString &value)
{
    priKey = value;
}

quint8 CsTerminal::getState() const
{
    return state;
}

void CsTerminal::setState(const quint8 &value)
{
    state = value;
}

quint8 CsTerminal::getRunState() const
{
    return runState;
}

void CsTerminal::setRunState(const quint8 &value)
{
    runState = value;
}

QString CsTerminal::getCreateTime() const
{
    return createTime;
}

void CsTerminal::setCreateTime(const QString &value)
{
    createTime = value;
}
QString CsTerminal::getOnlineTime() const
{
    return onlineTime;
}

void CsTerminal::setOnlineTime(const QString &value)
{
    onlineTime = value;
}
QString CsTerminal::getOfflineTime() const
{
    return offlineTime;
}

void CsTerminal::setOfflineTime(const QString &value)
{
    offlineTime = value;
}
QString CsTerminal::getMacAddr() const
{
    return macAddr;
}

void CsTerminal::setMacAddr(const QString &value)
{
    macAddr = value;
}

















