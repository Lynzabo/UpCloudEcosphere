#ifndef REQSCHEDULETASKEXECSTATUS_H
#define REQSCHEDULETASKEXECSTATUS_H

#include "commonfilesexecstatus.h"
#include "transmsglib_global.h"
#include "core/validation.h"
#include "core/messageinfo.h"

class TRANSMSGLIBSHARED_EXPORT ReqScheduleTaskExecStatus: public CommonFilesExecStatus ,
        public Validation, public MessageInfo
{
public:
    ReqScheduleTaskExecStatus();
public:
    void toXML(QXmlStreamWriter *writer = 0);
    void toEntity(QXmlStreamReader *reader = 0);
protected:
    void validate(TransException &tsExcep);
    quint8 messageType() const;
};

#endif // REQSCHEDULETASKEXECSTATUS_H
