#ifndef HTTPASYNCDOWNLOADMANAGER_H
#define HTTPASYNCDOWNLOADMANAGER_H
#include "httpdownloadmanager.h"

class HttpAsyncDownloadManager : public QThread
{
    Q_OBJECT
public:
    HttpAsyncDownloadManager();
    void SetDownloadPro(const QMap<QString, QString> &upGroups, const bool &parallel, const int &iisNum, const int &downThreadsNum);
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
    //允许同时下载文件数
    int iisNum;
    //下载单个文件启动线程数
    int downThreadsNum;
private slots:
    void transError(const QString &src,const QString &errMsg);
    void transStart();
    void transSubFileEnd(const QString &fileUrl,const QString &destAbst);
    void transEnd();
    void transProcess(const QString &fileUrl,const quint64 &haveDoneBytes,const quint64 &totalBytes);
};

#endif // HTTPASYNCDOWNLOADMANAGER_H
