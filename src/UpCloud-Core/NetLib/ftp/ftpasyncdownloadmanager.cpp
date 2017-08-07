#include "ftpasyncdownloadmanager.h"

FtpAsyncDownloadManager::FtpAsyncDownloadManager()
{
    transGroups.clear();
}

FtpAsyncDownloadManager::~FtpAsyncDownloadManager()
{

}

void FtpAsyncDownloadManager::download(const QMap<QString, QString> &upGroups, const bool &parallel, FtpMeta *_meta, const int &iisNum, const int &downThreadsNum)
{
    transGroups = upGroups;
    this->parallel = parallel;
    this->meta = _meta;
    this->iisNum = iisNum;
    this->downThreadsNum = downThreadsNum;
}

void FtpAsyncDownloadManager::run()
{
    FtpDownloadManager *manager = new FtpDownloadManager;
    connect(manager,SIGNAL(start()),this,SLOT(transStart()));
    connect(manager,SIGNAL(process(const QString &,const quint64 &,const quint64 &)),
        this,SLOT(transProcess(const QString &,const quint64 &,const quint64 &)),Qt::DirectConnection);
    connect(manager,SIGNAL(error(const QString &,const QString &)),this,SLOT(transError(const QString &,const QString &)),Qt::DirectConnection);
    connect(manager,SIGNAL(subFileEnd(const QString &,const QString &)),this,SLOT(transSubFileEnd(const QString &,const QString &)),Qt::DirectConnection);
    connect(manager,SIGNAL(end()),this,SLOT(transEnd()),Qt::DirectConnection);
    manager->download(transGroups,parallel,meta,iisNum,downThreadsNum);
}

void FtpAsyncDownloadManager::transError(const QString &src, const QString &errMsg)
{
    emit
        error(src,errMsg);
}
void FtpAsyncDownloadManager::transStart()
{
    emit
    begin();
}

void FtpAsyncDownloadManager::transSubFileEnd(const QString &fileUrl, const QString &destAbst)
{
    emit
    subFileEnd(fileUrl,destAbst);
}
void FtpAsyncDownloadManager::transEnd()
{
    emit
    end();
}

void FtpAsyncDownloadManager::transProcess(const QString &fileUrl, const quint64 &haveDoneBytes, const quint64 &totalBytes)
{
    emit
    process(fileUrl,haveDoneBytes,totalBytes);
}
