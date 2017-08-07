#ifndef FTPASYNCUPLOADMANAGER_H
#define FTPASYNCUPLOADMANAGER_H

#include "ftpmeta.h"
#include "ftpuploadmanager.h"
class FtpAsyncUploadManager : public QThread
{
    Q_OBJECT
public:
    explicit FtpAsyncUploadManager();
    ~FtpAsyncUploadManager();
    //加入上传路径list
    void upload(const QMap<QString,QString> &upGroups, const bool &parallel, FtpMeta *_meta, const int &iisNum, const int &upThreadsNum);
signals:
    void begin();
    //操作出错信号
    void error(const QString &src,const QString &errMsg);
    //一个文件上传完成信号
    void subFileEnd(const QString &fileUrl,const QString &destAbst);
    //所有文件上传完成信号
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
    int upThreadsNum;
private slots:
    void transError(const QString &src,const QString &errMsg);
    void transStart();
    void transSubFileEnd(const QString &fileUrl,const QString &destAbst);
    void transEnd();
    void transProcess(const QString &fileUrl,const quint64 &haveDoneBytes,const quint64 &totalBytes);
};

#endif // FTPASYNCUPLOADMANAGER_H
