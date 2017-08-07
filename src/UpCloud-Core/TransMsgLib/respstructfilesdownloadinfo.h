#ifndef RESPSTRUCTFILESDOWNLOADINFO_H
#define RESPSTRUCTFILESDOWNLOADINFO_H

#include "transmsglib_global.h"
#include "taskreplyinfo.h"
#include "core/serializable.h"
#include "core/validation.h"
#include "core/messageinfo.h"

class TRANSMSGLIBSHARED_EXPORT RespStructFilesDownloadInfo : public TaskReplyInfo, public Validation, public MessageInfo
{
public:
    RespStructFilesDownloadInfo();
    ~RespStructFilesDownloadInfo();
public:
    void toXML(QXmlStreamWriter *writer = 0);
    void toEntity(QXmlStreamReader *reader = 0);
protected:
    void validate(TransException &tsExcep);
    quint8 messageType() const;
};

#endif // RESPSTRUCTFILESDOWNLOADINFO_H
