#ifndef RESPUNSTRUCTFILESDOWNLOADSTATUS_H
#define RESPUNSTRUCTFILESDOWNLOADSTATUS_H

#include "transmsglib_global.h"
#include "taskreplyinfo.h"
#include "core/serializable.h"
#include "core/validation.h"
#include "core/messageinfo.h"

class TRANSMSGLIBSHARED_EXPORT RespUnstructFilesDownloadStatus : public TaskReplyInfo, public Validation, public MessageInfo
{
public:
    RespUnstructFilesDownloadStatus();
    ~RespUnstructFilesDownloadStatus();
public:
    void toXML(QXmlStreamWriter *writer = 0);
    void toEntity(QXmlStreamReader *reader = 0);
protected:
    void validate(TransException &tsExcep);
    quint8 messageType() const;
};

#endif // RESPUNSTRUCTFILESDOWNLOADSTATUS_H
