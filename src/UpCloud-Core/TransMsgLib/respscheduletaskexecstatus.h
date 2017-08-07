#ifndef RESPSCHEDULETASKEXECSTATUS_H
#define RESPSCHEDULETASKEXECSTATUS_H

#include "transmsglib_global.h"
#include "taskreplyinfo.h"
#include "core/serializable.h"
#include "core/validation.h"
#include "core/messageinfo.h"

class TRANSMSGLIBSHARED_EXPORT RespScheduleTaskExecStatus : public TaskReplyInfo, public Validation, public MessageInfo
{
public:
    RespScheduleTaskExecStatus();
    ~RespScheduleTaskExecStatus();
public:
    void toXML(QXmlStreamWriter *writer = 0);
    void toEntity(QXmlStreamReader *reader = 0);
protected:
    void validate(TransException &tsExcep);
    quint8 messageType() const;
};

#endif // RESPSCHEDULETASKEXECSTATUS_H
