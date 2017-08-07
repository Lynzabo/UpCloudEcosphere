#ifndef REQMONITORINGINDICATORSTATUS_H
#define REQMONITORINGINDICATORSTATUS_H

#include "transmsglib_global.h"
#include "monitoringindicatorinfo.h"
#include "indicatorinfo.h"
#include "core/serializable.h"
#include "core/validation.h"
#include "core/messageinfo.h"

class TRANSMSGLIBSHARED_EXPORT ReqMonitoringIndicatorStatus : public MonitoringIndicatorInfo, public Validation, public MessageInfo
{
public:
    ReqMonitoringIndicatorStatus();
    ~ReqMonitoringIndicatorStatus();
public:
    void toXML(QXmlStreamWriter *writer = 0);
    void toEntity(QXmlStreamReader *reader = 0);
protected:
    void validate(TransException &tsExcep);
    quint8 messageType() const;
public:
    IndicatorInfo* indicatorInfo;
};

#endif // REQMONITORINGINDICATORSTATUS_H
