#ifndef REQUNSTRUCTFILESDOWNLOADINFO_H
#define REQUNSTRUCTFILESDOWNLOADINFO_H
#include "commonfilesdownloadinfo.h"
#include "transmsglib_global.h"
#include "core/validation.h"
#include "core/messageinfo.h"

class TRANSMSGLIBSHARED_EXPORT ReqUnstructFilesDownloadInfo : public CommonFilesDownloadInfo ,
        public Validation, public MessageInfo
{
public:
    ReqUnstructFilesDownloadInfo();
    void toXML(QXmlStreamWriter *writer = 0);
    void toEntity(QXmlStreamReader *reader = 0);
protected:
    void validate(TransException &tsExcep);
    quint8 messageType() const;
};

#endif // REQUNSTRUCTFILESDOWNLOADINFO_H
