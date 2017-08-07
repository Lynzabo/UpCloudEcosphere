#ifndef FTPFILEUPTHREAD_H
#define FTPFILEUPTHREAD_H

#include <QtCore>
#include <QtNetwork>
#include "ftpmeta.h"
#include "core/qftp.h"
class FtpFileUpThread : public QThread
{
    Q_OBJECT
public:
    FtpFileUpThread(const QString &index);
    ~FtpFileUpThread();
    void SetUploadProp(const QString &abstPath, const QString &url, const int &subAyncsSize=5, FtpMeta *_meta=0);

    QString getF_AbstPath();
signals:
    //结束时间循环
    void endLoop();
    //当前文件上传完毕信号
    void FileUploadFinish(const QString &fKey);
    //上传文件失败信号
    void FileUploadError(const QString &fKey,const QString &errorStr);
    //上传进度
    void process(const QString &fileUrl,const quint64 &haveDoneBytes,const quint64 &totalBytes);
protected:
    void run();
private:
    QFtp *qftp;
    //ftp服务信息
    FtpMeta *meta;
    //线程上传主键
    QString f_Key;
    //上传文件URL
    QString f_Url;
    //绝对路径
    QString f_AbstPath;
    //上传文件URL
    QUrl f_URL;
    //当前文件上传线程数
    int f_SubAyncsSize;
    //要上传的文件大小
    quint64 f_FileSize;
    //多线程已接收串长度
    quint64 f_ReceiveSize;
    //完成上传的线程数
    int f_FinishedNum;
    //要上传的文件对象
    QFile *f_File;
private slots:
    void uploadFile();
    void dcommandFinish(int tmp, bool backSatus);
    void dcommandStateChanged(int state);
    //上传进度
    void dataTransferProgress(qint64, qint64);
    void hander_size(int tmp, const QString& output);
};

#endif // FTPFILEUPTHREAD_H
