#ifndef RESPMONITORINGINDICATORINFO_H
#define RESPMONITORINGINDICATORINFO_H

#include "transmsglib_global.h"
#include "replyinfo.h"
#include "core/serializable.h"
#include "core/validation.h"
#include "core/messageinfo.h"

class TRANSMSGLIBSHARED_EXPORT RespMonitoringIndicatorInfo : public ReplyInfo, public Validation, public MessageInfo
{
public:
    RespMonitoringIndicatorInfo();
    ~RespMonitoringIndicatorInfo();
public:
    void toXML(QXmlStreamWriter *writer = 0);
    void toEntity(QXmlStreamReader *reader = 0);
protected:
    void validate(TransException &tsExcep);
    quint8 messageType() const;
};

#endif // RESPMONITORINGINDICATORINFO_H
