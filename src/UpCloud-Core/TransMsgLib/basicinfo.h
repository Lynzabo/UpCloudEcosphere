#ifndef BASICINFO_H
#define BASICINFO_H
#include "core/serializable.h"
#include "base.h"

class BasicInfo : public Serializable
{
public:
    BasicInfo();
protected:
    void toXML(QXmlStreamWriter *writer = 0);
    void toEntity(QXmlStreamReader *reader = 0);
public:
    //报文类型
    quint8 MessageType;
    //固定码
    quint64 UUID;
    //请求码
    QString RequestID;

};

#endif // BASICINFO_H
