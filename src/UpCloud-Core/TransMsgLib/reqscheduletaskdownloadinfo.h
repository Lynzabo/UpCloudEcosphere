#ifndef REQSCHEDULETASKDOWNLOADINFO_H
#define REQSCHEDULETASKDOWNLOADINFO_H

#include "commonfilesexecinfo.h"
#include "transmsglib_global.h"
#include "core/validation.h"
#include "core/messageinfo.h"

class TRANSMSGLIBSHARED_EXPORT ReqScheduleTaskDownloadInfo : public CommonFilesExecInfo ,
        public Validation, public MessageInfo
{
public:
    ReqScheduleTaskDownloadInfo();
public:
    void toXML(QXmlStreamWriter *writer = 0);
    void toEntity(QXmlStreamReader *reader = 0);
protected:
    void validate(TransException &tsExcep);
    quint8 messageType() const;
public:
    //执行入口文件名
    QString EntranceFile;

};

#endif // REQSCHEDULETASKDOWNLOADINFO_H
