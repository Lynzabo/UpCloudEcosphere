#ifndef REQMONITORINGINDICATORINFO_H
#define REQMONITORINGINDICATORINFO_H

#include "transmsglib_global.h"
#include "monitoringindicatorinfo.h"
#include "core/serializable.h"
#include "core/validation.h"
#include "core/messageinfo.h"

class TRANSMSGLIBSHARED_EXPORT ReqMonitoringIndicatorInfo : public MonitoringIndicatorInfo, public Validation, public MessageInfo
{
public:
    ReqMonitoringIndicatorInfo();
    ~ReqMonitoringIndicatorInfo();
public:
    void toXML(QXmlStreamWriter *writer = 0);
    void toEntity(QXmlStreamReader *reader = 0);
protected:
    void validate(TransException &tsExcep);
    quint8 messageType() const;
};

#endif // REQMONITORINGINDICATORINFO_H
