#ifndef DATAGRAMINFO_H
#define DATAGRAMINFO_H
#include <QtCore>
#include "transmsglib_global.h"
//固定码格式
#pragma pack (1)
struct Equip_Info {
    //设备主类型 1字节
  quint8 EquipMainType;
  //设备副类型 1字节
  quint8 EquipSubType;
  //时间  4字节
  quint32 Time;
  //流水号 2字节
  quint16 SerialNumber;
};
#pragma pack ()

/**
 * @brief The DataGramInfo class    返回报文结构
 */
class TRANSMSGLIBSHARED_EXPORT DataGramInfo
{
public:
    DataGramInfo();
    /**
     * @brief clear 清空所有属性值
     */
    void clear();
public:
    //文件开始标记-->2字节
    quint16 begin;bool begin_ISREAD;
    //报文类型-->1字节
    quint8 msgType;bool msgType_ISREAD;
    //固定码-->8字节
    quint64 UUID;bool UUID_ISREAD;
    //请求码-->32字节
    QString requestID;bool requestID_ISREAD;
    //时间戳-->8字节
    quint64 timestamp;bool timestamp_ISREAD;
    //报文体长度
    quint32 dataLength;bool dataLength_ISREAD;
    //报文体
    QString message;bool message_ISREAD;
    //文件结尾标示符-->2字节
    quint16 end;bool end_ISREAD;
    Equip_Info equip;
};

#endif // DATAGRAMINFO_H
