#ifndef FILEDOWNLOAD_H
#define FILEDOWNLOAD_H
#include <QtCore>
#include "core/serializable.h"
#include "base.h"
#include "transmsglib_global.h"
class TRANSMSGLIBSHARED_EXPORT FileDownload : public Serializable
{
    friend class FtpPush;
    friend class HttpPush;
public:
    FileDownload();
protected:
    void toXML(QXmlStreamWriter *writer = 0);
    void toEntity(QXmlStreamReader *reader = 0);
public:
    //文件下载地址
    QString DownloadURLs;
    //文件保存路径
    QString DescPath;
};

#endif // FILEDOWNLOAD_H
