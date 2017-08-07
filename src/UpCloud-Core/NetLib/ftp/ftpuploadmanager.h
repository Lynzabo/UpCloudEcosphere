#ifndef FTPUPLOADMANAGER_H
#define FTPUPLOADMANAGER_H

#include <QtCore>
#include "ftpmeta.h"
#include "ftpfileupthread.h"

class FtpUploadManager : public QObject
{
    Q_OBJECT
public:
    explicit FtpUploadManager();
    ~FtpUploadManager();
    //加入上传路径list
    void upload(const QMap<QString,QString> &upGroups, const bool &parallel, FtpMeta *_meta, const int &_iisNum, const int &_upThreadsNum);
signals:
    void endloop();
    void start();
    //操作出错信号
    void error(const QString &src,const QString &errMsg);
    //一个文件上传完成信号
    void subFileEnd(const QString &fileUrl,const QString &destAbst);
    //所有文件上传完成信号
    void end();
    void process(const QString &fileUrl,const quint64 &haveDoneBytes,const quint64 &totalBytes);
public slots:
private slots:
    void SubFileFinished(const QString &fKey);
    void SubFileUploadError(const QString &fKey, const QString &errorStr);
    void transProcess(const QString &fileUrl,const quint64 &haveDoneBytes,const quint64 &totalBytes);
private:
    void startNextUpload();
    QString getKey2AbstPath(const QString &fkey);
    QString getFileUploadDestAbst(const QString &furl);
private:
    FtpMeta *meta;
    //多文件顺序排队队列,当文件就要上传，出队列
    QQueue<QString> *readyUpQueue;
    //未上传完的文件队列，上传完后才出队列
    QStringList notCompleteUpURLs;
    //并发上传文件数
    int iisNum;
    //上传单个文件启动线程数
    int upThreadsNum;
    //校验是否处理任务完成
    int upChecker;

    QMap<QString,FtpFileUpThread*> asyncFileMap;
    QReadWriteLock lockSize;
    //做阻塞用
    bool blockStatus;
    QMutex *subMutex;

    void clearAsyncFileMap();
    void deleteMap(QMap<QString, FtpFileUpThread *> &_asyncFileMap, const QString &_key);
public:
    //传输文件对
    QMap<QString,QString> transGroups;
};

#endif // FTPUPLOADMANAGER_H
