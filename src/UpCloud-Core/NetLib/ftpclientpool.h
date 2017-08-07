#ifndef FTPCLIENTPOOL_H
#define FTPCLIENTPOOL_H
#include "nettransclient.h"
#include "ftp/ftpmeta.h"
/**
 * @brief The FTPClientPool class FTP客户端
 * notice:可以继承于文件传输类，也可以继承于命令传输类，以后添加其他协议会使用
 * visit:
 *      FTPClientPool::Builder *builder = new FTPClientPool::NetBuilder(
 *               NetManager::SERVICE::ftp,
 *               QString("localhost"),
 *               21,
 *               QString("user01"),
 *               QString("user01"));
 *   FTPClientPool *net = builder->build();
 *    net->download(...;
 *    delete builder;
 *    delete net;
 *   FTPClientPool::Builder *builder = new FTPClientPool::Builder;
 *   FTPClientPool *net = builder->setService(NetManager::SERVICE::ftp)
 *           ->setHostname(QString("localhost"))
 *           ->setPort(21)
 *           ->setUsername(QString("user01"))
 *           ->setPassword(QString("user01"))->build();
 *    net->download(...;
 *    delete builder;
 *    delete net;
 */
//FTP协议默认允许同时下载文件数
const int FTP_DEFAULT_DOWN_IISNUM = 3;
//FTP协议默认下载单个文件启动线程数
const int FTP_DEFAULT_DOWN_THREADSNUM = 5;

//FTP协议默认允许同时上传文件数
const int FTP_DEFAULT_UP_IISNUM = 3;
//FTP协议默认上传单个文件启动线程数
const int FTP_DEFAULT_UP_THREADSNUM = 5;

class NETLIBSHARED_EXPORT FTPClientPool : public NetTransClient
{
public:
    ~FTPClientPool(){
        delete meta;
    }
    FTPClientPool(FtpMeta *_meta,const QString &taskID = ""){
        meta = _meta;
        this->taskUUID = taskID;
    }
    /**
     * @brief upload    上传文件接口类
     * @param upGroups  预上传的文件集合
     *                  {[d:/1.txt,ftp://127.0.0.1:8080/1.txt],[d:/2.txt,ftp://127.0.0.1:8080/2.txt]}
     * @param async     同步还是异步  false为同步,true为异步
     * @param parallel  并行还是串行上传    false为串行，true为并行,对于并行上传,在配置文件有配置同时允许多少文件并行
     */
    void upload(const QMap<QString,QString> &upGroups,const bool &async = false,const bool &parallel = false,const int &iisNum = FTP_DEFAULT_UP_IISNUM,const int &upThreadsNum = FTP_DEFAULT_UP_THREADSNUM);
    /**
     * @brief download  下载文件接口类
     * @param downGroups    预下载的文件集合
     *                  {[ftp://127.0.0.1:8080/1.txt,d:/1.txt],[ftp://127.0.0.1:8080/2.txt,d:/2.txt]}
     * @param async 同步还是异步  false为同步,true为异步
     * @param parallel  并行还是串行下载    false为串行，true为并行,对于并行下载,在配置文件有配置同时允许多少文件并行
     * @param iisNum    允许同时下载文件数
     * @param downThreadsNum    下载单个文件启动线程数
     */
    void download(const QMap<QString,QString> &downGroups,const bool &async = false,const bool &parallel = false,const int &iisNum = FTP_DEFAULT_DOWN_IISNUM,const int &downThreadsNum = FTP_DEFAULT_DOWN_THREADSNUM);

    /**
     * @brief list      显示当前目录接口
     * @param dir       传入参数:目录名
     * @param listInfo  传出参数：目录信息
     */
    void list(const QString &dir, QList<struct list_info> *listInfo);

    /**
     * @brief cd        切换目录
     * @param dir       目录名
     */
    void cd(const QString &dir);

    /**
     * @brief rename    重命名目录/文件
     * @param oldname   旧名字
     * @param newname   新名字
     */
    void rename(const QString &oldname, const QString &newname);

    /**
     * @brief remove    删除文件
     * @param file      文件名
     */
    void remove(const QString &file);

    /**
     * @brief rmdir     删除目录
     * @param dir       目录名
     */
    void rmdir(const QString &dir);

    /**
     * @brief mkdir     创建目录
     * @param dir       目录名
     */
    void mkdir(const QString &dir);
protected slots:
    void transError(const QString &src,const QString &errMsg);
    void transStart();
    void transSubFileEnd(const QString &fileUrl,const QString &destAbst);
    void transEnd();
    void transProcess(const QString &fileUrl,const quint64 &haveDoneBytes,const quint64 &totalBytes);
private:
    FtpMeta *meta;
};

#endif // FTPCLIENTPOOL_H
