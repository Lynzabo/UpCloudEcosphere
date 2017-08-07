#ifndef COMMONFILESEXECINFO_H
#define COMMONFILESEXECINFO_H

#include "commonfilesdownloadinfo.h"
#include <QDateTime>
#include "transmsglib_global.h"

class TRANSMSGLIBSHARED_EXPORT CommonFilesExecInfo : public CommonFilesDownloadInfo
{
public:
    CommonFilesExecInfo();
    ~CommonFilesExecInfo();
protected:
    void toXML(QXmlStreamWriter *writer = 0);
    void toEntity(QXmlStreamReader *reader = 0);
public:    
    //执行时刻
    QString ExecTime;
};


#endif // COMMONFILESEXECINFO_H
