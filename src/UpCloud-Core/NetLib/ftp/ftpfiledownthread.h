#ifndef FTPFILEDOWNTHREAD_H
#define FTPFILEDOWNTHREAD_H

#include <QtCore>
#include <QtNetwork>
#include "ftpmeta.h"
#include "core/qftp.h"
#include "ftpcommonmanager.h"
class FtpFileDownThread : public QThread
{
    Q_OBJECT
public:
    FtpFileDownThread(const QString &index);
    ~FtpFileDownThread();
    void SetDownloadProp(const QString &url, const QString &abstPath, const int &subAyncsSize=5, FtpMeta *_meta=0);

    QString getF_Url();


signals:
    //结束时间循环
    void endLoop();
    //当前文件下载完毕信号
    void FileDownloadFinish(const QString &fKey);
    //下载文件失败信号
    void FileDownloadError(const QString &fKey,const QString &errorStr);
    //下载进度
    void process(const QString &fileUrl,const quint64 &haveDoneBytes,const quint64 &totalBytes);
protected:
    void run();
private:
    QFtp *qftp;
    //ftp服务信息
    FtpMeta *meta;
    //线程下载主键
    QString f_Key;
    //下载文件URL
    QString f_Url;
    //绝对路径
    QString f_AbstPath;
    //下载文件URL
    QUrl f_URL;
    //当前文件下载线程数
    int f_SubAyncsSize;
    //要下载的文件大小
    qint64 f_FileSize;
    //多线程已接收串长度
    quint64 f_ReceiveSize;
    //完成下载的线程数
    int f_FinishedNum;
    //要下载的文件对象
    QFile *f_File;    

private slots:
    void downloadFile();
    void dcommandFinish(int tmp, bool backSatus);
    void dcommandStateChanged(int state);
    //下载进度
    void dataTransferProgress(qint64, qint64);
    void hander_size(int tmp, const QString& output);
};
#endif // FTPFILEDOWNTHREAD_H
