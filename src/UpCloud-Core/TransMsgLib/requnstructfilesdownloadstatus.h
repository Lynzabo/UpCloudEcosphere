#ifndef REQUNSTRUCTFILESDOWNLOADSTATUS_H
#define REQUNSTRUCTFILESDOWNLOADSTATUS_H

#include "commonfilesexecstatus.h"
#include "transmsglib_global.h"
#include "core/validation.h"
#include "core/messageinfo.h"

class TRANSMSGLIBSHARED_EXPORT ReqUnstructFilesDownloadStatus : public CommonFilesExecStatus ,
        public Validation, public MessageInfo
{
public:
    ReqUnstructFilesDownloadStatus();
public:
    void toXML(QXmlStreamWriter *writer = 0);
    void toEntity(QXmlStreamReader *reader = 0);
protected:
    void validate(TransException &tsExcep);
    quint8 messageType() const;
};

#endif // REQUNSTRUCTFILESDOWNLOADSTATUS_H
