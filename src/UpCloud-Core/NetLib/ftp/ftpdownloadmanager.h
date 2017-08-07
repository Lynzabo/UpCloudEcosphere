#ifndef FTPDOWNLOADMANAGER_H
#define FTPDOWNLOADMANAGER_H

#include <QtCore>
#include "ftpmeta.h"
#include "ftpfiledownthread.h"
class FtpDownloadManager : public QObject
{
    Q_OBJECT
public:
    explicit FtpDownloadManager();
    ~FtpDownloadManager();
    //加入下载路径list
    void download(const QMap<QString,QString> &upGroups, const bool &parallel, FtpMeta *_meta, const int &_iisNum, const int &_downThreadsNum);
signals:
    void endloop();
    void start();
    //操作出错信号
    void error(const QString &src,const QString &errMsg);
    //一个文件下载完成信号
    void subFileEnd(const QString &fileUrl,const QString &destAbst);
    //所有文件下载完成信号
    void end();
    void process(const QString &fileUrl,const quint64 &haveDoneBytes,const quint64 &totalBytes);
public slots:
private slots:
    void SubFileFinished(const QString &fKey);
    void SubFileDownloadError(const QString &fKey, const QString &errorStr);
    void transProcess(const QString &fileUrl,const quint64 &haveDoneBytes,const quint64 &totalBytes);
private:
    void startNextDownload();
    QString getKey2URL(const QString &fkey);
    QString getFileDownloadDestAbst(const QString &furl);
private:
    FtpMeta *meta;
    //多文件顺序排队队列,当文件就要下载，出队列
    QQueue<QString> *readyDownQueue;
    //未下载完的文件队列，下载完后才出队列
    QStringList notCompleteDownURLs;
    //并发下载文件数
    int iisNum;
    //下载单个文件启动线程数
    int downThreadsNum;
    //校验是否处理任务完成
    int downChecker;
    QMap<QString,FtpFileDownThread*> asyncFileMap;
    QReadWriteLock lockSize;
    //做阻塞用
    bool blockStatus;
    QMutex *subMutex;

    void clearAsyncFileMap();
    void deleteMap(QMap<QString, FtpFileDownThread *> &_asyncFileMap, const QString &_key);
public:
    //传输文件对
    QMap<QString,QString> transGroups;
};

#endif // FTPDOWNLOADMANAGER_H
