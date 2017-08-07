#ifndef COMMONFILESDOWNLOADINFO_H
#define COMMONFILESDOWNLOADINFO_H
#include "taskinfo.h"
#include "ftppush.h"
#include "httppush.h"
#include "transmsglib_global.h"

class TRANSMSGLIBSHARED_EXPORT CommonFilesDownloadInfo : public TaskInfo
{
public:
    CommonFilesDownloadInfo();
    ~CommonFilesDownloadInfo();
protected:
    void toXML(QXmlStreamWriter *writer = 0);
    void toEntity(QXmlStreamReader *reader = 0);
public:
    //FTP协议推送文件基本元数据
    FtpPush *ftpPush;
    //Http协议推送文件基本元数据
    HttpPush *httpPush;
    //操作类型码
    quint8 TaskExecType;
    //操作策略
    quint16 Strategy;


};

#endif // COMMONFILESDOWNLOADINFO_H
