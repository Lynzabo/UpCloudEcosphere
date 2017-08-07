#include "terminalconnutil.h"
#include "terminaluuidutil.h"
using namespace Environment::Net_Equip_MainType;

SINGLETON_ALL_IN_ONE(TerminalConnUtil)
void TerminalConnUtil::insertTerminal(const QTcpSocket *terSock, const quint64 &terUUID)
{
    lock.lock();
    quint8 type = TerminalUUIDUtil::getInstance().getTerminalUUIDType(terUUID);
    if(type == DESKTOP_REMOTEUI)
    {
        desktopRemoteUIClients.insert(terSock, terUUID);
    }
    else if(type == DESKTOP_NODER)
    {
        desktopNodeUIClients.insert(terSock, terUUID);
    }
    else if(type == J2EE_REMOTEUI)
    {
        desktopRemoteUIClients.insert(terSock, terUUID);
    }
    lock.unlock();
}

void TerminalConnUtil::delTerminal(const QTcpSocket* &terSock)
{
    lock.lock();
    //三个肯定只有一个存在
    desktopRemoteUIClients.remove(terSock);
    j2EERemoteUIClients.remove(terSock);
    desktopNodeUIClients.remove(terSock);
    lock.unlock();
}

const QMap<const QTcpSocket *, quint64>& TerminalConnUtil::listTerminal(const quint8 &equipMainType) const
{
    if(equipMainType == DESKTOP_REMOTEUI)
    {
        return desktopRemoteUIClients;
    }
    else if(equipMainType == DESKTOP_NODER)
    {
        return desktopNodeUIClients;
    }
    else if(equipMainType == J2EE_REMOTEUI)
    {
        return j2EERemoteUIClients;
    }
}

