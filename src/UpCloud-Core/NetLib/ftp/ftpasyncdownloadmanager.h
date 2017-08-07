#ifndef FTPASYNCDOWNLOADMANAGER_H
#define FTPASYNCDOWNLOADMANAGER_H
#include "ftpmeta.h"
#include "ftpdownloadmanager.h"
class FtpAsyncDownloadManager : public QThread
{
    Q_OBJECT
public:
    explicit FtpAsyncDownloadManager();
    ~FtpAsyncDownloadManager();
    //加入下载路径list
    void download(const QMap<QString,QString> &upGroups, const bool &parallel, FtpMeta *_meta, const int &iisNum, const int &downThreadsNum);
signals:
    void begin();
    //操作出错信号
    void error(const QString &src,const QString &errMsg);
    //一个文件下载完成信号
    void subFileEnd(const QString &fileUrl,const QString &destAbst);
    //所有文件下载完成信号
    void end();
    void process(const QString &fileUrl,const quint64 &haveDoneBytes,const quint64 &totalBytes);
protected:
    void run();
private:
    //传输文件对
    QMap<QString,QString> transGroups;
    bool parallel;
    FtpMeta *meta;
    int iisNum;
    int downThreadsNum;
private slots:
    void transError(const QString &src,const QString &errMsg);
    void transStart();
    void transSubFileEnd(const QString &fileUrl,const QString &destAbst);
    void transEnd();
    void transProcess(const QString &fileUrl,const quint64 &haveDoneBytes,const quint64 &totalBytes);
};

#endif // FTPASYNCDOWNLOADMANAGER_H
