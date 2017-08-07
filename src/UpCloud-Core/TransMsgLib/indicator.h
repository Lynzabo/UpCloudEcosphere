#ifndef INDICATOR_H
#define INDICATOR_H

#include "core/serializable.h"
#include "base.h"

class TRANSMSGLIBSHARED_EXPORT Indicator : public Serializable
{
    friend class IndicatorInfo;
public:
    Indicator();
    ~Indicator();
protected:
    void toXML(QXmlStreamWriter *writer = 0);
    void toEntity(QXmlStreamReader *reader = 0);
public:
    //指标码
    quint16 IndicatorKey;
    //指标内容
    QString IndicatorValue;
};

#endif // INDICATOR_H
