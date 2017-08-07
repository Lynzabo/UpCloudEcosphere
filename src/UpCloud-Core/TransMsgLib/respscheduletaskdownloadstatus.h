#ifndef RESPSCHEDULETASKDOWNLOADSTATUS_H
#define RESPSCHEDULETASKDOWNLOADSTATUS_H

#include "transmsglib_global.h"
#include "taskreplyinfo.h"
#include "core/serializable.h"
#include "core/validation.h"
#include "core/messageinfo.h"

class TRANSMSGLIBSHARED_EXPORT RespScheduleTaskDownloadStatus  : public TaskReplyInfo, public Validation, public MessageInfo
{
public:
    RespScheduleTaskDownloadStatus();
    ~RespScheduleTaskDownloadStatus();
public:
    void toXML(QXmlStreamWriter *writer = 0);
    void toEntity(QXmlStreamReader *reader = 0);
protected:
    void validate(TransException &tsExcep);
    quint8 messageType() const;
};

#endif // RESPSCHEDULETASKDOWNLOADSTATUS_H
