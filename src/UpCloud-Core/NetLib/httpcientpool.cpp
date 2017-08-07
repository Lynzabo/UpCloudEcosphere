#include "httpcientpool.h"
#include "http/httpdownloadmanager.h"
#include "http/httpasyncdownloadmanager.h"

HttpCientPool::HttpCientPool(const QString &taskID)
{
    this->taskUUID = taskID;
}

void HttpCientPool::upload(const QMap<QString, QString> &upGroups, const bool &async, const bool &parallel, const int &iisNum, const int &upThreadsNum)
{

}

void HttpCientPool::download(const QMap<QString, QString> &downGroups, const bool &async, const bool &parallel, const int &iisNum, const int &downThreadsNum)
{
    if(async)
    {
        HttpAsyncDownloadManager *manager = new HttpAsyncDownloadManager;
        //下面几个connect与同步的一样
        connect(manager,SIGNAL(begin()),this,SLOT(transStart()));
        connect(manager,SIGNAL(process(const QString &,const quint64 &,const quint64 &)),
                this,SLOT(transProcess(const QString &,const quint64 &,const quint64 &)),Qt::DirectConnection);
        connect(manager,SIGNAL(error(const QString &,const QString &)),this,SLOT(transError(const QString &,const QString &)),Qt::DirectConnection);
        connect(manager,SIGNAL(subFileEnd(const QString &,const QString &)),this,SLOT(transSubFileEnd(const QString &,const QString &)),Qt::DirectConnection);
        connect(manager,SIGNAL(end()),this,SLOT(transEnd()),Qt::DirectConnection);
        ((HttpAsyncDownloadManager*)manager)->SetDownloadPro(downGroups,parallel,iisNum,downThreadsNum);
        manager->start();
    }
    else
    {
        HttpDownloadManager *manager = new HttpDownloadManager;
        connect(manager,SIGNAL(start()),this,SLOT(transStart()));
        connect(manager,SIGNAL(process(const QString &,const quint64 &,const quint64 &)),
                this,SLOT(transProcess(const QString &,const quint64 &,const quint64 &)),Qt::DirectConnection);
        connect(manager,SIGNAL(error(const QString &,const QString &)),this,SLOT(transError(const QString &,const QString &)),Qt::DirectConnection);
        connect(manager,SIGNAL(subFileEnd(const QString &,const QString &)),this,SLOT(transSubFileEnd(const QString &,const QString &)),Qt::DirectConnection);
        connect(manager,SIGNAL(end()),this,SLOT(transEnd()),Qt::DirectConnection);
        manager->download(downGroups,parallel,iisNum,downThreadsNum);
        delete manager;
    }
}

void HttpCientPool::transError(const QString &src, const QString &errMsg)
{
    qDebug() << "src:" << src << ",errMsg:" << errMsg;
    //在调用出可以接住这个信号
    emit
        error(taskUUID, src,errMsg);
}
void HttpCientPool::transStart()
{
    qDebug() << "start";
    //开始传输
    emit
        start();
}

void HttpCientPool::transSubFileEnd(const QString &fileUrl, const QString &destAbst)
{
    //一个文件传输完成
    qDebug() << "subFileEnd";
    emit
    subFileEnd(taskUUID, fileUrl,destAbst);
}
void HttpCientPool::transEnd()
{
    qDebug() << "end";
    //传输完毕
    emit
        end(taskUUID);
}

void HttpCientPool::transProcess(const QString &fileUrl, const quint64 &haveDoneBytes, const quint64 &totalBytes)
{
    qDebug() << QString("transProcess:%1:%2,%3").arg(fileUrl).arg(haveDoneBytes).arg(totalBytes);
    //传输进度
    emit
        process(fileUrl,haveDoneBytes,totalBytes);
}

