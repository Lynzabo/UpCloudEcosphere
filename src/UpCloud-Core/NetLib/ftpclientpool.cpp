#include "ftpclientpool.h"
#include "ftp/ftpdownloadmanager.h"
#include "ftp/ftpasyncdownloadmanager.h"
#include "ftp/ftpuploadmanager.h"
#include "ftp/ftpasyncuploadmanager.h"
#include "ftp/ftpcommonmanager.h"
void FTPClientPool::upload(const QMap<QString, QString> &upGroups, const bool &async, const bool &parallel, const int &iisNum, const int &upThreadsNum)
{
    if(async)
    {
        //异步处理
        FtpAsyncUploadManager *manager = new FtpAsyncUploadManager;
        connect(manager,SIGNAL(started()),this,SLOT(transStart()));
        connect(manager,SIGNAL(process(const QString &,const quint64 &,const quint64 &)),
                this,SLOT(transProcess(const QString &,const quint64 &,const quint64 &)),Qt::DirectConnection);
        connect(manager,SIGNAL(error(const QString &,const QString &)),this,SLOT(transError(const QString &,const QString &)),Qt::DirectConnection);
        connect(manager,SIGNAL(subFileEnd(const QString &,const QString &)),this,SLOT(transSubFileEnd(const QString &,const QString &)),Qt::DirectConnection);
        connect(manager,SIGNAL(end()),this,SLOT(transEnd()),Qt::DirectConnection);
        connect(manager,SIGNAL(finished()), manager, SLOT(deleteLater()));
        manager->upload(upGroups,parallel,meta,iisNum,upThreadsNum);
        manager->start();
    }
    else
    {
        //同步阻塞处理
        FtpUploadManager *manager = new FtpUploadManager;
        connect(manager,SIGNAL(start()),this,SLOT(transStart()));
        connect(manager,SIGNAL(process(const QString &,const quint64 &,const quint64 &)),
                this,SLOT(transProcess(const QString &,const quint64 &,const quint64 &)),Qt::DirectConnection);
        connect(manager,SIGNAL(error(const QString &,const QString &)),this,SLOT(transError(const QString &,const QString &)),Qt::DirectConnection);
        connect(manager,SIGNAL(subFileEnd(const QString &,const QString &)),this,SLOT(transSubFileEnd(const QString &,const QString &)),Qt::DirectConnection);
        connect(manager,SIGNAL(end()),this,SLOT(transEnd()),Qt::DirectConnection);
        manager->upload(upGroups,parallel,meta,iisNum,upThreadsNum);
        delete manager;
    }
}


void FTPClientPool::download(const QMap<QString, QString> &downGroups, const bool &async, const bool &parallel, const int &iisNum, const int &downThreadsNum)
{
    if(async)
    {
        //异步处理
        FtpAsyncDownloadManager *manager = new FtpAsyncDownloadManager;
        connect(manager,SIGNAL(started()),this,SLOT(transStart()));
        connect(manager,SIGNAL(process(const QString &,const quint64 &,const quint64 &)),
                this,SLOT(transProcess(const QString &,const quint64 &,const quint64 &)),Qt::DirectConnection);
        connect(manager,SIGNAL(error(const QString &,const QString &)),this,SLOT(transError(const QString &,const QString &)),Qt::DirectConnection);
        connect(manager,SIGNAL(subFileEnd(const QString &,const QString &)),this,SLOT(transSubFileEnd(const QString &,const QString &)),Qt::DirectConnection);
        connect(manager,SIGNAL(end()),this,SLOT(transEnd()),Qt::DirectConnection);
        connect(manager,SIGNAL(finished()), manager, SLOT(deleteLater()));
        manager->download(downGroups,parallel,meta,iisNum,downThreadsNum);
        manager->start();
    }
    else
    {
        //同步阻塞处理
        FtpDownloadManager *manager = new FtpDownloadManager;
        connect(manager,SIGNAL(start()),this,SLOT(transStart()));
        connect(manager,SIGNAL(process(const QString &,const quint64 &,const quint64 &)),
                this,SLOT(transProcess(const QString &,const quint64 &,const quint64 &)),Qt::DirectConnection);
        connect(manager,SIGNAL(error(const QString &,const QString &)),this,SLOT(transError(const QString &,const QString &)),Qt::DirectConnection);
        connect(manager,SIGNAL(subFileEnd(const QString &,const QString &)),this,SLOT(transSubFileEnd(const QString &,const QString &)),Qt::DirectConnection);
        connect(manager,SIGNAL(end()),this,SLOT(transEnd()),Qt::DirectConnection);
        manager->download(downGroups,parallel,meta,iisNum,downThreadsNum);
        delete manager;
    }
}

void FTPClientPool::transError(const QString &src, const QString &errMsg)
{
    qDebug() << "src:" << src << ",errMsg:" << errMsg;
    //在调用出可以接住这个信号
    emit
        error(taskUUID, src,errMsg);

}

void FTPClientPool::transStart()
{
    qDebug() << "start";
    //开始传输
    emit
        start();
}

void FTPClientPool::transSubFileEnd(const QString &fileUrl, const QString &destAbst)
{
    //一个文件传输完成
    qDebug() << "subFileEnd";
    emit
        subFileEnd(taskUUID, fileUrl,destAbst);
}

void FTPClientPool::transEnd()
{
    qDebug() << "end-------------";
    //传输完毕
    emit
        end(taskUUID);
}

void FTPClientPool::transProcess(const QString &fileUrl, const quint64 &haveDoneBytes, const quint64 &totalBytes)
{
    //qDebug() << QString("transProcess:%1:%2,%3").arg(fileUrl).arg(haveDoneBytes).arg(totalBytes);
    //传输进度
    emit
        process(fileUrl,haveDoneBytes,totalBytes);
}

void FTPClientPool::list(const QString &dir, QList<list_info> *listInfo)
{
    FtpCommonManager* manager = new FtpCommonManager;
    connect(manager, SIGNAL(start()), this, SLOT(transStart()));
    connect(manager, SIGNAL(end()), this, SLOT(transEnd()));
    connect(manager, SIGNAL(error(QString, QString)), this, SLOT(transError(QString,QString)));
    manager->list(dir, listInfo);
    delete manager;

}

void FTPClientPool::cd(const QString &dir)
{
    FtpCommonManager* manager = new FtpCommonManager;
    connect(manager, SIGNAL(start()), this, SLOT(transStart()));
    connect(manager, SIGNAL(end()), this, SLOT(transEnd()));
    connect(manager, SIGNAL(error(QString, QString)), this, SLOT(transError(QString,QString)));
    manager->cd(dir);
    delete manager;
}

void FTPClientPool::rename(const QString &oldname, const QString &newname)
{
    FtpCommonManager* manager = new FtpCommonManager;
    connect(manager, SIGNAL(start()), this, SLOT(transStart()));
    connect(manager, SIGNAL(end()), this, SLOT(transEnd()));
    connect(manager, SIGNAL(error(QString, QString)), this, SLOT(transError(QString,QString)));
    manager->rename(oldname, newname);
    delete manager;
}

void FTPClientPool::remove(const QString &file)
{
    FtpCommonManager* manager = new FtpCommonManager;
    connect(manager, SIGNAL(start()), this, SLOT(transStart()));
    connect(manager, SIGNAL(process(QString,quint64,quint64)), this, SLOT(transProcess(QString,quint64,quint64)));
    connect(manager, SIGNAL(end()), this, SLOT(transEnd()));
    connect(manager, SIGNAL(error(QString, QString)), this, SLOT(transError(QString,QString)));
    manager->remove(file);
    delete manager;
}

void FTPClientPool::rmdir(const QString &dir)
{
    FtpCommonManager* manager = new FtpCommonManager;
    connect(manager, SIGNAL(start()), this, SLOT(transStart()));
    connect(manager, SIGNAL(process(QString,quint64,quint64)), this, SLOT(transProcess(QString,quint64,quint64)));
    connect(manager, SIGNAL(end()), this, SLOT(transEnd()));
    connect(manager, SIGNAL(error(QString, QString)), this, SLOT(transError(QString,QString)));
    manager->rmdir(dir);
    delete manager;
}

void FTPClientPool::mkdir(const QString &dir)
{
    FtpCommonManager* manager = new FtpCommonManager;
    connect(manager, SIGNAL(start()), this, SLOT(transStart()));
    connect(manager, SIGNAL(end()), this, SLOT(transEnd()));
    connect(manager, SIGNAL(error(QString, QString)), this, SLOT(transError(QString,QString)));
    manager->mkdir(dir);
    delete manager;
}
