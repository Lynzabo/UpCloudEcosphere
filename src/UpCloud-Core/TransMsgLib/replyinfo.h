#ifndef REPLYINFO_H
#define REPLYINFO_H

#include "basicinfo.h"

class  ReplyInfo : public BasicInfo
{
public:
    ReplyInfo();
protected:
    void toXML(QXmlStreamWriter *writer = 0);
    void toEntity(QXmlStreamReader *reader = 0);
public:
    //状态码
    quint8 State;
};

#endif // REPLYINFO_H
