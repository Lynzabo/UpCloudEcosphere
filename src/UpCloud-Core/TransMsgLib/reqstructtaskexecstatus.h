#ifndef REQSTRUCTTASKEXECSTATUS_H
#define REQSTRUCTTASKEXECSTATUS_H

#include "commonfilesexecstatus.h"
#include "transmsglib_global.h"
#include "core/validation.h"
#include "core/messageinfo.h"

class TRANSMSGLIBSHARED_EXPORT ReqStructTaskExecStatus : public CommonFilesExecStatus ,
        public Validation, public MessageInfo
{
public:
    ReqStructTaskExecStatus();
public:
    void toXML(QXmlStreamWriter *writer = 0);
    void toEntity(QXmlStreamReader *reader = 0);
protected:
    void validate(TransException &tsExcep);
    quint8 messageType() const;
};

#endif // REQSTRUCTTASKEXECSTATUS_H
