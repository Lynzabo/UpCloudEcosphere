#include "httpasyncdownloadmanager.h"

HttpAsyncDownloadManager::HttpAsyncDownloadManager()
{

}

void HttpAsyncDownloadManager::SetDownloadPro(const QMap<QString, QString> &upGroups,const bool &parallel, const int &iisNum, const int &downThreadsNum)
{
    transGroups = upGroups;
    this->parallel = parallel;
    this->iisNum = iisNum;
    this->downThreadsNum = downThreadsNum;
}

void HttpAsyncDownloadManager::run()
{
    HttpDownloadManager *manager = new HttpDownloadManager;
    connect(manager,SIGNAL(start()),this,SLOT(transStart()));
    connect(manager,SIGNAL(process(const QString &,const quint64 &,const quint64 &)),
        this,SLOT(transProcess(const QString &,const quint64 &,const quint64 &)),Qt::DirectConnection);
    connect(manager,SIGNAL(error(const QString &,const QString &)),this,SLOT(transError(const QString &,const QString &)),Qt::DirectConnection);
    connect(manager,SIGNAL(subFileEnd(const QString &,const QString &)),this,SLOT(transSubFileEnd(const QString &,const QString &)),Qt::DirectConnection);
    connect(manager,SIGNAL(end()),this,SLOT(transEnd()),Qt::DirectConnection);
    manager->download(transGroups,parallel,iisNum,downThreadsNum);
}

void HttpAsyncDownloadManager::transError(const QString &src, const QString &errMsg)
{
    emit
        error(src,errMsg);
}
void HttpAsyncDownloadManager::transStart()
{
    emit
    begin();
}

void HttpAsyncDownloadManager::transSubFileEnd(const QString &fileUrl, const QString &destAbst)
{
    emit
    subFileEnd(fileUrl,destAbst);
}
void HttpAsyncDownloadManager::transEnd()
{
    emit
    end();
}

void HttpAsyncDownloadManager::transProcess(const QString &fileUrl, const quint64 &haveDoneBytes, const quint64 &totalBytes)
{
    emit
    process(fileUrl,haveDoneBytes,totalBytes);
}
