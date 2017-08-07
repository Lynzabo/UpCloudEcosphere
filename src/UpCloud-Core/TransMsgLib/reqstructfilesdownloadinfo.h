#ifndef REQSTRUCTFILESDOWNLOADINFO_H
#define REQSTRUCTFILESDOWNLOADINFO_H

#include "commonfilesexecinfo.h"
#include "transmsglib_global.h"
#include "core/validation.h"
#include "core/messageinfo.h"

class TRANSMSGLIBSHARED_EXPORT ReqStructFilesDownloadInfo : public CommonFilesExecInfo ,
        public Validation, public MessageInfo
{
public:
    ReqStructFilesDownloadInfo();
public:
    void toXML(QXmlStreamWriter *writer = 0);
    void toEntity(QXmlStreamReader *reader = 0);
protected:
    void validate(TransException &tsExcep);
    quint8 messageType() const;
};

#endif // REQSTRUCTFILESDOWNLOADINFO_H
