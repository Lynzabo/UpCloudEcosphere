#include "datagramutil.h"
#include "endecrypt.h"
#include "terminaluuidutil.h"
using namespace Environment::Net_Equip_MainType;

DatagramUtil* DatagramUtil::m_instance = new DatagramUtil;
DatagramUtil::DatagramUtil() {}
DatagramUtil::~DatagramUtil() {}

void DatagramUtil::MessageType(MessageInfo *dataIn, quint8 &msgType)
{
    msgType = dataIn->messageType();
}

void DatagramUtil::UUID(quint64 &_uuid)
{
    _uuid = TerminalUUIDUtil::getInstance().getTerminalUUID();
}

void DatagramUtil::RequestID(QString &_requestID)
{
    //生成随机请求码,格式为621229FA7117066DF3B50814A9FF5D81
    UuidUtil::nextUUID(_requestID);
}

void DatagramUtil::Timestamp(quint64 &_timestamp)
{
    TimerUtil *time = new TimerUtil;
    _timestamp = time->currentTimeMillis();
    delete time;
}

void DatagramUtil::packDatagram(MessageInfo *dataIn,
                                QByteArray &datagram,
                                const quint64 receiverUUID)
{
    QBuffer buffer(&datagram);
    buffer.open(QIODevice::WriteOnly);
    //输入
    QDataStream out(&buffer);
    out.setVersion(QDataStream::Qt_4_7);

    //1.文件开始标记-->2字节
    quint16 begin = 0x1010;
    out << begin;
    //2.报文类型-->1字节
    quint8 msgType;
    this->MessageType(dataIn,msgType);
    out << msgType;
    //3.固定码-->8字节
    quint64 UUID;
    this->UUID(UUID);
    out << UUID;
    //4.请求码-->32字节
    QString requestID;
    this->RequestID(requestID);
    out << requestID;
    //5.时间戳-->8字节
    quint64 timestamp;
    this->Timestamp(timestamp);
    out << timestamp;
    //6.报文体长度
    QString condram;
    //生成报文xml
    parseXML(dataIn,UUID,requestID,condram);

    //加密
    QString pubKey;pubKey.clear();
    QString cipherText;cipherText.clear();
    if(TerminalKeYUtil::getInstance().getTerminalPubKey(receiverUUID, pubKey) == true)
    {
        BotanEnDecrypt enDecrypt;
        enDecrypt.encryption(pubKey,condram,cipherText);
    }
    else
    {
        QString excep = trs("获取加密公钥失败");
        throw excep;
    }


    quint32 dataLength;
    dataLength = cipherText.size()*2;
    out << dataLength;
    //7.报文体
    out << cipherText;
    //8.文件结尾标示符-->2字节
    quint16 end = 0xffff;
    out << end;

    buffer.close();
}


void DatagramUtil::parseXML(MessageInfo *dataIn,quint64 &uuid,QString &requestID, QString &xml)
{
    using namespace Environment::Datagram;
    if(dataIn)
    {
        BasicInfo *entity = 0;
        quint8 msgType;
        this->MessageType(dataIn,msgType);
        QXmlStreamWriter writer(&xml);
        switch (msgType) {
        case Bridge_Conn::REQBRIDGECONN:
            entity = (ReqBridgeConn*)dataIn;
            break;
        case Bridge_Conn::RESPBRIDGECONN:
            entity = (RespBridgeConn*)dataIn;
            break;
        case Heartthrob_Conn::REQHEARTTHROBSCONN:
            entity = (ReqHeartthrobsConn*)dataIn;
            break;
        case Heartthrob_Conn::RESPHEARTTHROBSCONN:
            entity = (RespHeartthrobsConn*)dataIn;
            break;
        case Unstru_Data_Trans::REQUNSTRUCTFILESDOWNLOADINFO:
            entity = (ReqUnstructFilesDownloadInfo*)dataIn;
            break;
        case Unstru_Data_Trans::RESPUNSTRUCTFILESDOWNLOADINFO:
            entity = (RespUnstructFilesDownloadInfo*)dataIn;
            break;
        case Unstru_Data_Trans::REQUNSTRUCTFILESDOWNLOADSTATUS:
            entity = (ReqUnstructFilesDownloadStatus*)dataIn;
            break;
        case Unstru_Data_Trans::RESPUNSTRUCTFILESDOWNLOADSTATUS:
            entity = (RespUnstructFilesDownloadStatus*)dataIn;
            break;
        case Stru_Data_Trans::REQSTRUCTFILESDOWNLOADINFO:
            entity = (ReqStructFilesDownloadInfo*)dataIn;
            break;
        case Stru_Data_Trans::RESPSTRUCTFILESDOWNLOADINFO:
            entity = (RespStructFilesDownloadInfo*)dataIn;
            break;
        case Stru_Data_Trans::REQSTRUCTFILESDOWNLOADSTATUS:
            entity = (ReqStructFilesDownloadStatus*)dataIn;
            break;
        case Stru_Data_Trans::RESPSTRUCTFILESDOWNLOADSTATUS:
            entity = (RespStructFilesDownloadStatus*)dataIn;
            break;
        case Stru_Data_Trans::REQSTRUCTTASKEXECSTATUS:
            entity = (ReqStructTaskExecStatus*)dataIn;
            break;
        case Stru_Data_Trans::RESPSTRUCTTASKEXECSTATUS:
            entity = (RespStructTaskExecStatus*)dataIn;
            break;
        case Sche_Data_Trans::REQSCHEDULETASKDOWNLOADINFO:
            entity = (ReqScheduleTaskDownloadInfo*)dataIn;
            break;
        case Sche_Data_Trans::RESPSCHEDULETASKDOWNLOADINFO:
            entity = (RespScheduleTaskDownloadInfo*)dataIn;
            break;
        case Sche_Data_Trans::REQSCHEDULETASKDOWNLOADSTATUS:
            entity = (ReqScheduleTaskDownloadStatus*)dataIn;
            break;
        case Sche_Data_Trans::RESPSCHEDULETASKDOWNLOADSTATUS:
            entity = (RespScheduleTaskDownloadStatus*)dataIn;
            break;
        case Sche_Data_Trans::REQSCHEDULETASKEXECSTATUS:
            entity = (ReqScheduleTaskExecStatus*)dataIn;
            break;
        case Sche_Data_Trans::RESPSCHEDULETASKEXECSTATUS:
            entity = (RespScheduleTaskExecStatus*)dataIn;
            break;
        case Monit_Ctrl::REQMONITORINGINDICATORINFO:
            entity = (ReqMonitoringIndicatorInfo*)dataIn;
            break;
        case Monit_Ctrl::RESPMONITORINGINDICATORINFO:
            entity = (RespMonitoringIndicatorInfo*)dataIn;
            break;
        case Monit_Ctrl::REQMONITORINGINDICATORSTATUS:
            entity = (ReqMonitoringIndicatorStatus*)dataIn;
            break;
        case Monit_Ctrl::RESPMONITORINGINDICATORSTATUS:
            entity = (RespMonitoringIndicatorStatus*)dataIn;
            break;
        case UI_Ctrl::REQREMOTEUIOPERACENTORCONN:
            entity = (ReqRemoteUIOperaCentorConn*)dataIn;
            break;
        case UI_Ctrl::RESPREMOTEUIOPERACENTORCONN:
            entity = (RespRemoteUIOperaCentorConn*)dataIn;
            break;
        case UI_Ctrl::REQREMOTEUIOPERACENTORINFO:
            entity = (ReqRemoteUIOperaCentorInfo*)dataIn;
            break;
        case UI_Ctrl::RESPREMOTEUIOPERACENTORINFO:
            entity = (RespRemoteUIOperaCentorInfo*)dataIn;
            break;
            //不需要default,肯定是上面几个,因为只找继承与DatagramInfo子类
        }
        entity->MessageType = msgType;
        entity->UUID = uuid;
        entity->RequestID = requestID;
        try
        {
            ((Serializable *)entity)->toXML(&writer);
        }
        catch(TransException &excep)
        {
            throw excep;
        }
    }
    else
    {
        throw trs("实体对象为空");
    }
}

void DatagramUtil::validateMsgType(const quint8 &msgType)
{
    using namespace Environment::Datagram;
    if(msgType != Bridge_Conn::REQBRIDGECONN &&
            msgType != Bridge_Conn::RESPBRIDGECONN &&
            msgType != Heartthrob_Conn::REQHEARTTHROBSCONN &&
            msgType != Heartthrob_Conn::RESPHEARTTHROBSCONN &&
            msgType != Unstru_Data_Trans::REQUNSTRUCTFILESDOWNLOADINFO &&
            msgType != Unstru_Data_Trans::RESPUNSTRUCTFILESDOWNLOADINFO &&
            msgType != Unstru_Data_Trans::REQUNSTRUCTFILESDOWNLOADSTATUS &&
            msgType != Unstru_Data_Trans::RESPUNSTRUCTFILESDOWNLOADSTATUS &&
            msgType != Stru_Data_Trans::REQSTRUCTFILESDOWNLOADINFO &&
            msgType != Stru_Data_Trans::RESPSTRUCTFILESDOWNLOADINFO &&
            msgType != Stru_Data_Trans::REQSTRUCTFILESDOWNLOADSTATUS &&
            msgType != Stru_Data_Trans::RESPSTRUCTFILESDOWNLOADSTATUS &&
            msgType != Stru_Data_Trans::REQSTRUCTTASKEXECSTATUS &&
            msgType != Stru_Data_Trans::RESPSTRUCTTASKEXECSTATUS &&
            msgType != Sche_Data_Trans::REQSCHEDULETASKDOWNLOADINFO &&
            msgType != Sche_Data_Trans::RESPSCHEDULETASKDOWNLOADINFO &&
            msgType != Sche_Data_Trans::REQSCHEDULETASKDOWNLOADSTATUS &&
            msgType != Sche_Data_Trans::RESPSCHEDULETASKDOWNLOADSTATUS &&
            msgType != Sche_Data_Trans::REQSCHEDULETASKEXECSTATUS &&
            msgType != Sche_Data_Trans::RESPSCHEDULETASKEXECSTATUS &&
            msgType != Monit_Ctrl::REQMONITORINGINDICATORINFO &&
            msgType != Monit_Ctrl::RESPMONITORINGINDICATORINFO &&
            msgType != Monit_Ctrl::REQMONITORINGINDICATORSTATUS &&
            msgType != Monit_Ctrl::RESPMONITORINGINDICATORSTATUS &&
            msgType != UI_Ctrl::REQREMOTEUIOPERACENTORCONN &&
            msgType != UI_Ctrl::RESPREMOTEUIOPERACENTORCONN &&
            msgType != UI_Ctrl::REQREMOTEUIOPERACENTORINFO &&
            msgType != UI_Ctrl::RESPREMOTEUIOPERACENTORINFO)
        throw trs("未知报文类型");
}

void DatagramUtil::read(const quint8 msgType, const QString &condram, Serializable *entity)
{
    validateMsgType(msgType);
    QXmlStreamReader reader(condram);
    try
    {
        entity->toEntity(&reader);
    }
    catch(TransException &excep)
    {
       throw excep;
    }
}



