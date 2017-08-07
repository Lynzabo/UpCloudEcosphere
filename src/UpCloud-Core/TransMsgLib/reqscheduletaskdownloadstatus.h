#ifndef REQSCHEDULETASKDOWNLOADSTATUS_H
#define REQSCHEDULETASKDOWNLOADSTATUS_H

#include "commonfilesexecstatus.h"
#include "transmsglib_global.h"
#include "core/validation.h"
#include "core/messageinfo.h"

class TRANSMSGLIBSHARED_EXPORT ReqScheduleTaskDownloadStatus : public CommonFilesExecStatus ,
        public Validation, public MessageInfo
{
public:
    ReqScheduleTaskDownloadStatus();
public:
    void toXML(QXmlStreamWriter *writer = 0);
    void toEntity(QXmlStreamReader *reader = 0);
protected:
    void validate(TransException &tsExcep);
    quint8 messageType() const;
};

#endif // REQSCHEDULETASKDOWNLOADSTATUS_H
