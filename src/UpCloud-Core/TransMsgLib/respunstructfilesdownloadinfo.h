#ifndef RESPUNSTRUCTFILESDOWNLOADINFO_H
#define RESPUNSTRUCTFILESDOWNLOADINFO_H

#include "transmsglib_global.h"
#include "taskreplyinfo.h"
#include "core/serializable.h"
#include "core/validation.h"
#include "core/messageinfo.h"

class TRANSMSGLIBSHARED_EXPORT RespUnstructFilesDownloadInfo : public TaskReplyInfo, public Validation, public MessageInfo
{
public:
    RespUnstructFilesDownloadInfo();
    ~RespUnstructFilesDownloadInfo();
public:
    void toXML(QXmlStreamWriter *writer = 0);
    void toEntity(QXmlStreamReader *reader = 0);
protected:
    void validate(TransException &tsExcep);
    quint8 messageType() const;
};

#endif // RESPUNSTRUCTFILESDOWNLOADINFO_H
