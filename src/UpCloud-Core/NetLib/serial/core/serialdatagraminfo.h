#ifndef SERIALDATAGRAMINFO_H
#define SERIALDATAGRAMINFO_H
#include <QtCore>
#include "netlib_global.h"

class NETLIBSHARED_EXPORT SerialDataGramInfo
{
public:
    SerialDataGramInfo();

    void clear();
public:
    //文件开始标记-->2字节
    quint16 begin;
    //报文类型-->1字节
    quint8 msgType;
    //时间戳-->8字节
    quint64 timestamp;
    //报文体长度-->4字节
    quint32 dataLength;
    //报文体
    QString message;
    //文件结尾标示符-->2字节
    quint16 end;
};

#endif // SERIALDATAGRAMINFO_H
