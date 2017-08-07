#include "terminaluuidutil.h"
using namespace Environment::Net_Equip_MainType;

TerminalUUIDUtil* TerminalUUIDUtil::m_instance = new TerminalUUIDUtil;

TerminalUUIDUtil::TerminalUUIDUtil()
{

}
TerminalUUIDUtil::~TerminalUUIDUtil()
{
    m_centerUUID = 0;
}

void TerminalUUIDUtil::init()
{
    m_centerUUID = quint64(0x1111111111);
}
void TerminalUUIDUtil::updateTerminalUUID(const quint64 &uuid)
{
    mutex.lock();
    m_centerUUID = uuid;
    mutex.unlock();
}
quint64 TerminalUUIDUtil::getTerminalUUID() const
{
    return m_centerUUID;
}

quint8 TerminalUUIDUtil::getTerminalUUIDType(const quint64 &UUID)
{
    Equip_Info* equipInfo = new Equip_Info;
    this->parseTerminalUUID(UUID, equipInfo);
    return equipInfo->EquipMainType;
}

void TerminalUUIDUtil::parseTerminalUUID(const quint64 &uuid, Equip_Info *equipInfo)
{
    equipInfo->SerialNumber = (quint16)uuid;
    equipInfo->Time = (quint32)(uuid  >> 2*8);//2byte * 8 bit
    equipInfo->EquipSubType = (quint8)(uuid  >> 6*8);
    equipInfo->EquipMainType = (quint8)(uuid  >> 7*8);
}

void TerminalUUIDUtil::genTerminalUUID(const Equip_Info &equipInfo, quint64 &descUUID)
{
    descUUID = equipInfo.EquipMainType;
    descUUID = descUUID << 1*8;
    descUUID +=equipInfo.EquipSubType;
    descUUID = descUUID << 4*8;
    descUUID +=equipInfo.Time;
    descUUID = descUUID << 2*8;
    descUUID +=equipInfo.SerialNumber;
}


