#ifndef MONITORINGINDICATORINFO_H
#define MONITORINGINDICATORINFO_H

#include "basicinfo.h"

class MonitoringIndicatorInfo : public BasicInfo
{
public:
    MonitoringIndicatorInfo();
protected:
    void toXML(QXmlStreamWriter *writer = 0);
    void toEntity(QXmlStreamReader *reader = 0);
public:
    //指标类型码
    quint16 IndicatorType;
};

#endif // MONITORINGINDICATORINFO_H
