#include <QCoreApplication>
#include <QDebug>
#include <QtCore>
#include "ftpclientpool.h"
#include "nettransclient.h"
////测试Http的异步和同步下载
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    ///////////////////////////////测试FTP/Http同步、异步下载---begin---

    ////1.Ftp同步下载单通道测试
    FtpMeta::Builder *builder = new FtpMeta::Builder;
    FtpMeta *meta = (FtpMeta *)builder->setHostname(QString("localhost"))
            ->setPort(21)
            ->setUsername(QString("user01"))
            ->setPassword(QString("pwd01"))->build();
    NetTransClient *ftpClient = new FTPClientPool(meta);
    QMap<QString, QString> downGroups;
    downGroups.clear();
    downGroups.insert(QString("111.exe"),QString("d:/download/111.exe"));
    downGroups.insert(QString("1111.zip"),QString("d:/download/1111.zip"));
    ftpClient->download(downGroups,false,false);
    delete ftpClient;

    /*
    ////2.Ftp同步下载多通道测试
    FtpMeta::Builder *builder = new FtpMeta::Builder;
    FtpMeta *meta = (FtpMeta *)builder->setHostname(QString("localhost"))
            ->setPort(21)
            ->setUsername(QString("user01"))
            ->setPassword(QString("pwd01"))->build();
    NetTransClient *ftpClient = new FTPClientPool(meta);
    QMap<QString, QString> downGroups;
    downGroups.clear();
    downGroups.insert(QString("111.exe"),QString("d:/download/111.exe"));
    downGroups.insert(QString("1111.zip"),QString("d:/download/1111.zip"));
    ftpClient->download(downGroups,false,true);
    delete ftpClient;
    */
    /*
    ////3.Ftp异步下载单通道测试
    FtpMeta::Builder *builder = new FtpMeta::Builder;
    FtpMeta *meta = (FtpMeta *)builder->setHostname(QString("localhost"))
            ->setPort(21)
            ->setUsername(QString("user01"))
            ->setPassword(QString("pwd01"))->build();
    NetTransClient *ftpClient = new FTPClientPool(meta);
    QMap<QString, QString> downGroups;
    downGroups.clear();
    downGroups.insert(QString("111.exe"),QString("d:/download/111.exe"));
    downGroups.insert(QString("1111.zip"),QString("d:/download/1111.zip"));
    ftpClient->download(downGroups,true,false);
    qDebug() << "ayncs exec!";
    */
    /*
    ////4.Ftp异步下载多通道测试
    FtpMeta::Builder *builder = new FtpMeta::Builder;
    FtpMeta *meta = (FtpMeta *)builder->setHostname(QString("localhost"))
            ->setPort(21)
            ->setUsername(QString("user01"))
            ->setPassword(QString("pwd01"))->build();
    NetTransClient *ftpClient = new FTPClientPool(meta);
    QMap<QString, QString> downGroups;
    downGroups.clear();
    downGroups.insert(QString("111.exe"),QString("d:/download/111.exe"));
    downGroups.insert(QString("1111.zip"),QString("d:/download/1111.zip"));
    ftpClient->download(downGroups,true,true);
    qDebug() << "ayncs exec!";
    */


    /*
    ////1.Http同步下载单通道测试
    NetTransClient *httpClient = new HttpCientPool;
    QMap<QString, QString> downGroups;
    downGroups.clear();
    downGroups.insert(QString("http://localhost:8080/file/111.zip"),QString("d:/download/111.zip"));
    downGroups.insert(QString("http://localhost:8080/file/222.zip"),QString("d:/download/222.zip"));
    httpClient->download(downGroups,false,false);
    qDebug() << "download complete exec!";
    delete httpClient;
    */
    /*
    ////2.Http同步下载多通道测试
    NetTransClient *httpClient = new HttpCientPool;
    QMap<QString, QString> downGroups;
    downGroups.clear();
    downGroups.insert(QString("http://localhost:8080/file/111.zip"),QString("d:/download/111.zip"));
    downGroups.insert(QString("http://localhost:8080/file/222.zip"),QString("d:/download/222.zip"));
    httpClient->download(downGroups,false,true);
    qDebug() << "download complete exec!";
    delete httpClient;
    */
    /*
    ////3.Http异步下载单通道测试
    NetTransClient *httpClient = new HttpCientPool;
    QMap<QString, QString> downGroups;
    downGroups.clear();
    downGroups.insert(QString("http://localhost:8080/file/111.zip"),QString("d:/download/111.zip"));
    downGroups.insert(QString("http://localhost:8080/file/222.zip"),QString("d:/download/222.zip"));
    httpClient->download(downGroups,true,false);
    qDebug() << "ayncs exec!";
    */
    /*
    ////4.Http异步下载多通道测试
    NetTransClient *httpClient = new HttpCientPool;
    QMap<QString, QString> downGroups;
    downGroups.clear();
    downGroups.insert(QString("http://localhost:8080/file/111.zip"),QString("d:/download/111.zip"));
    downGroups.insert(QString("http://localhost:8080/file/222.zip"),QString("d:/download/222.zip"));
    httpClient->download(downGroups,true,true);
    qDebug() << "ayncs exec!";
    */
    ///////////////////////////////测试FTP/Http同步、异步下载---end---
    return a.exec();
}
