#include "terminaluuidutil.h"

TerminalUUIDUtil* TerminalUUIDUtil::m_instance = new TerminalUUIDUtil;

using namespace Environment::Net_Equip_MainType;

TerminalUUIDUtil::TerminalUUIDUtil()
{

}
TerminalUUIDUtil::~TerminalUUIDUtil()
{

}

void TerminalUUIDUtil::init()
{
    QString profileName = QString(trs("%1/%2")).arg(RUAbstPath::getInstance().profileAbst()).arg("profile");

    ////[2]判断当前profile文件是否存在,如果不存在,新产生该文件
    QFileInfo fileinfo(profileName);
    if(fileinfo.exists() == false)
    {
        QFile file(profileName);
        if(file.open(QIODevice::WriteOnly) == false)
        {
            QString errMsg = trs("profile文件不存在，新创建时失败:%1!").arg(file.errorString());
            throw errMsg;
        }
        else
        {
            file.close();
        }
    }
    ////[3]如果存在,获取到固定码元数据
    quint64 tmpUUID = 0;
    Equip_Info* equipInfo = new Equip_Info;

    QFile profile(profileName);
    if(profile.open(QIODevice::ReadWrite) == true)
    {
        //读取数据
        QDataStream in(&profile);
        in.setVersion(QDataStream::Qt_4_7);
        in >> tmpUUID;
        //解析数据
        this->parseTerminalUUID(tmpUUID, equipInfo);
    }
    else
    {
        QString errMsg = trs("打开profile文件失败:%1!").arg(profile.errorString());
        throw errMsg;
    }
    ////[4]校验固定码元数据,
    // 如果数据不合法则重新生成UUID,并赋值给terminalUUID
    // 如果数据合法,则直接赋值给terminalUUID

    if(validateTerminalUUID(equipInfo) == false)
    {
        //生成新的UUID
        createTerminalUUID(equipInfo);
        //将新的UUID转化为quint64
        this->genTerminalUUID(*equipInfo, terminalUUID);
        //清空上次的数据
        profile.resize(0);
        //写入新的数据
        QDataStream out(&profile);
        out.setVersion(QDataStream::Qt_4_7);
        out << terminalUUID;
        profile.close();
    }
    else
    {
        terminalUUID = tmpUUID;
    }
    delete equipInfo;
}

void TerminalUUIDUtil::updateTerminalUUID(const QString &uuid)
{
    terminalUUID = uuid.toLongLong();
}
quint64 TerminalUUIDUtil::getTerminalUUID() const
{
    return terminalUUID;
}

bool TerminalUUIDUtil::validateTerminalUUID(const quint64 &UUID)
{
    Equip_Info* equipInfo = new Equip_Info;
    this->parseTerminalUUID(UUID, equipInfo);
    quint8 EquipMainType = equipInfo->EquipMainType;
    ////[1]先判断设备主类型是否为空
    if(EquipMainType == 0)
    {
        return false;
    }
    return true;
}

bool TerminalUUIDUtil::validateTerminalUUID(const Equip_Info *equipInfo)
{    
    quint8 EquipMainType = equipInfo->EquipMainType;
    ////[1]先判断设备主类型是否为空
    if(EquipMainType == 0)
    {
        QString errMsg = trs("设备主类型为空!");
        //throw errMsg;
        return false;
    }
    ////[2]判断设备主类型是否一致
    if(EquipMainType != DESKTOP_REMOTEUI)
    {
        QString errMsg = trs("设备主类型不匹配!");
        //throw errMsg;
        return  false;
    }

    return true;
}

void TerminalUUIDUtil::createTerminalUUID(Equip_Info *equipInfo)
{    
    //设备主类型
    equipInfo->EquipMainType = DESKTOP_REMOTEUI;

    //设备副类型
    //TODO
    equipInfo->EquipSubType = (quint8)1;
    //时间
    QString curtime;curtime.clear();
    QString format = "yyMMddHH";
    TimerUtil::toString(curtime, format);
    quint32 time = (quint32)curtime.toUInt();
    equipInfo->Time = time;
    //流水号
    quint16 SerialNumber = qrand()%(1 << 15);
    equipInfo->SerialNumber = SerialNumber;
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


