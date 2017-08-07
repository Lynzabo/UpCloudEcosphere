#ifndef RESPMONITORINGINDICATORSTATUS_H
#define RESPMONITORINGINDICATORSTATUS_H

#include "transmsglib_global.h"
#include "replyinfo.h"
#include "core/serializable.h"
#include "core/validation.h"
#include "core/messageinfo.h"

class TRANSMSGLIBSHARED_EXPORT RespMonitoringIndicatorStatus : public ReplyInfo, public Validation, public MessageInfo
{
public:
    RespMonitoringIndicatorStatus();
    ~RespMonitoringIndicatorStatus();
public:
    void toXML(QXmlStreamWriter *writer = 0);
    void toEntity(QXmlStreamReader *reader = 0);
protected:
    void validate(TransException &tsExcep);
    quint8 messageType() const;
};

#endif // RESPMONITORINGINDICATORSTATUS_H
