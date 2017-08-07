#ifndef TASKREPLYINFO_H
#define TASKREPLYINFO_H

#include "replyinfo.h"

class  TaskReplyInfo : public ReplyInfo
{
public:
    TaskReplyInfo();
protected:
    void toXML(QXmlStreamWriter *writer = 0);
    void toEntity(QXmlStreamReader *reader = 0);
public:
    //计划任务编号
    quint32 TaskUUID;
};

#endif // TASKREPLYINFO_H
