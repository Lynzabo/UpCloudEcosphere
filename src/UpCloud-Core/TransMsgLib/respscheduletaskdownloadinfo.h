#ifndef RESPSCHEDULETASKDOWNLOADINFO_H
#define RESPSCHEDULETASKDOWNLOADINFO_H

#include "transmsglib_global.h"
#include "taskreplyinfo.h"
#include "core/serializable.h"
#include "core/validation.h"
#include "core/messageinfo.h"

class TRANSMSGLIBSHARED_EXPORT RespScheduleTaskDownloadInfo  : public TaskReplyInfo, public Validation, public MessageInfo
{
public:
    RespScheduleTaskDownloadInfo();
    ~RespScheduleTaskDownloadInfo();
public:
    void toXML(QXmlStreamWriter *writer = 0);
    void toEntity(QXmlStreamReader *reader = 0);
protected:
    void validate(TransException &tsExcep);
    quint8 messageType() const;
};

#endif // RESPSCHEDULETASKDOWNLOADINFO_H
