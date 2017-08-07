#ifndef TASKINFO_H
#define TASKINFO_H

#include "basicinfo.h"

class  TaskInfo : public BasicInfo
{
public:
    TaskInfo();

protected:
    void toXML(QXmlStreamWriter *writer = 0);
    void toEntity(QXmlStreamReader *reader = 0);
public:
    //计划任务编号
    quint32 TaskUUID;
};

#endif // TASKINFO_H
