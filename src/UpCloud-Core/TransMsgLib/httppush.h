#ifndef HTTPPUSH_H
#define HTTPPUSH_H
#include "core/serializable.h"
#include "filedownload.h"


class HttpPush : public Serializable
{
    friend class CommonFilesDownloadInfo;
public:
    HttpPush();
    ~HttpPush();
protected:
    void toXML(QXmlStreamWriter *writer = 0);
    void toEntity(QXmlStreamReader *reader = 0);
public:
    //存放一组文件下载地址
    QVector<FileDownload*> FilesDownloadURLs;
};

#endif // HTTPPUSH_H
