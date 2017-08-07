#ifndef INDICATORINFO_H
#define INDICATORINFO_H

#include "indicator.h"
#include "core/serializable.h"

class TRANSMSGLIBSHARED_EXPORT IndicatorInfo : public Serializable
{
    friend class ReqMonitoringIndicatorStatus;
public:
    IndicatorInfo();
    ~IndicatorInfo();
protected:
    void toXML(QXmlStreamWriter *writer = 0);
    void toEntity(QXmlStreamReader *reader = 0);
public:
    //存放一组指标信息
    QVector<Indicator*> Indicators;
};

#endif // INDICATORINFO_H
