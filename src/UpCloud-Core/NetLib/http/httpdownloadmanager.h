#ifndef HTTPDOWNLOADMANAGER_H
#define HTTPDOWNLOADMANAGER_H
#include <QtCore>
#include "filedownthread.h"
class HttpDownloadManager : public QObject
{
    Q_OBJECT
public:
    explicit HttpDownloadManager();
    ~HttpDownloadManager();
    //加入下载路径list
    void download(const QMap<QString,QString> &upGroups, const bool &parallel, const int &_iisNum, const int &_downThreadsNum);
signals:
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
    //多文件顺序排队队列,当文件就要下载，出队列
    QQueue<QString> *readyDownQueue;
    //未下载完的文件队列，下载完后才出队列
    QStringList notCompleteDownURLs;
    //允许同时下载文件数
    int iisNum;
    //下载单个文件启动线程数
    int downThreadsNum;
    //校验是否处理任务完成
    int downChecker;
    QMap<QString,FileDownThread*> asyncFileMap;
    void clearAsyncFileMap();
    QReadWriteLock lockSize;
    //做阻塞用
    bool blockStatus;
    void deleteMap(QMap<QString, FileDownThread *> &_asyncFileMap, const QString &_key);
    QMutex *subMutex;
public:
    //传输文件对
    QMap<QString,QString> transGroups;
};

#endif // HTTPDOWNLOADMANAGER_H
