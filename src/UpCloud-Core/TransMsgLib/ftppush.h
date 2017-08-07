#ifndef FTPPUSH_H
#define FTPPUSH_H
#include "core/serializable.h"
#include <filedownload.h>
class FtpPush : public Serializable
{
    friend class CommonFilesDownloadInfo;
public:
    FtpPush();
    ~FtpPush();
protected:
    void toXML(QXmlStreamWriter *writer = 0);
    void toEntity(QXmlStreamReader *reader = 0);
public:
    //存放一组文件下载地址
    QVector<FileDownload*> FilesDownloadURLs;
    //FTP服务端地址
    QString IP;
    //端口
    quint16 Port;
    //用户名
    QString Username;
    //密码
    QString Password;

};

#endif // FTPPUSH_H
