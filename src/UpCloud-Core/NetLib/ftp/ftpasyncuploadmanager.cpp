#include "ftpasyncuploadmanager.h"

FtpAsyncUploadManager::FtpAsyncUploadManager()
{
    transGroups.clear();
}

FtpAsyncUploadManager::~FtpAsyncUploadManager()
{

}

void FtpAsyncUploadManager::upload(const QMap<QString, QString> &upGroups, const bool &parallel, FtpMeta *_meta, const int &iisNum, const int &upThreadsNum)
{
    transGroups = upGroups;
    this->parallel = parallel;
    this->meta = _meta;
    this->iisNum = iisNum;
    this->upThreadsNum = upThreadsNum;
}

void FtpAsyncUploadManager::run()
{
    FtpUploadManager *manager = new FtpUploadManager;
    connect(manager,SIGNAL(start()),this,SLOT(transStart()));
    connect(manager,SIGNAL(process(const QString &,const quint64 &,const quint64 &)),
        this,SLOT(transProcess(const QString &,const quint64 &,const quint64 &)),Qt::DirectConnection);
    connect(manager,SIGNAL(error(const QString &,const QString &)),this,SLOT(transError(const QString &,const QString &)),Qt::DirectConnection);
    connect(manager,SIGNAL(subFileEnd(const QString &,const QString &)),this,SLOT(transSubFileEnd(const QString &,const QString &)),Qt::DirectConnection);
    connect(manager,SIGNAL(end()),this,SLOT(transEnd()),Qt::DirectConnection);
    manager->upload(transGroups,parallel,meta,iisNum,upThreadsNum);
}

void FtpAsyncUploadManager::transError(const QString &src, const QString &errMsg)
{
    emit
        error(src,errMsg);
}
void FtpAsyncUploadManager::transStart()
{
    emit
    begin();
}

void FtpAsyncUploadManager::transSubFileEnd(const QString &fileUrl, const QString &destAbst)
{
    emit
    subFileEnd(fileUrl,destAbst);
}
void FtpAsyncUploadManager::transEnd()
{
    emit
    end();
}

void FtpAsyncUploadManager::transProcess(const QString &fileUrl, const quint64 &haveDoneBytes, const quint64 &totalBytes)
{
    emit
    process(fileUrl,haveDoneBytes,totalBytes);
}
