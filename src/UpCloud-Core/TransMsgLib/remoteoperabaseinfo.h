#ifndef REMOTEOPERABASEINFO_H
#define REMOTEOPERABASEINFO_H

#include "basicinfo.h"

class RemoteOperaBaseInfo : public BasicInfo
{
public:
    RemoteOperaBaseInfo();
protected:
    void toXML(QXmlStreamWriter *writer = 0);
    void toEntity(QXmlStreamReader *reader = 0);
public:
    //指标类型码
    quint16 ExecType;
    //参数列表
    QString Params;
};

#endif // REMOTEOPERABASEINFO_H
