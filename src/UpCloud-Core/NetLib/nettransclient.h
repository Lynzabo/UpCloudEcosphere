#ifndef NETTRANSCLIENT_H
#define NETTRANSCLIENT_H
#include <QtCore>
#include "netlib_global.h"

/**
 * @brief The NetTransClient class  网络文件流传输(包括http/ftp)两种
 */
class NETLIBSHARED_EXPORT NetTransClient : public QObject
{
    Q_OBJECT
public:
    NetTransClient();
    ~NetTransClient();
    /**
     * @brief upload    上传文件接口类
     * @param upGroups  预上传的文件集合
     *                  {[d:/1.txt,http://127.0.0.1:8080/1.txt],[d:/2.txt,http://127.0.0.1:8080/2.txt]}
     * @param async     同步还是异步  false为同步,true为异步
     * @param parallel  并行还是串行上传    false为串行，true为并行,对于并行上传,在配置文件有配置同时允许多少文件并行
     */
    virtual void upload(const QMap<QString,QString> &upGroups,const bool &async = false,const bool &parallel = false, const int &iisNum = 0,const int &upThreadsNum = 0) = 0;
    /**
     * @brief download 下载文件接口类
     * @param downGroups 预下载的文件集合
     *                  {[http://127.0.0.1:8080/1.txt,d:/1.txt],[http://127.0.0.1:8080/2.txt,d:/2.txt]}
     * @param async 同步还是异步  false为同步,true为异步
     * @param parallel  并行还是串行下载    false为串行，true为并行,对于并行下载,在配置文件有配置同时允许多少文件并行
     */
    virtual void download(const QMap<QString,QString> &downGroups,const bool &async = false,const bool &parallel = false,const int &iisNum = 0,const int &downThreadsNum = 0) = 0;
public slots:
    virtual void transError(const QString &src,const QString &errMsg) = 0;
    virtual void transStart() = 0;
    virtual void transSubFileEnd(const QString &fileUrl,const QString &destAbst) = 0;
    virtual void transEnd() = 0;
    virtual void transProcess(const QString &fileUrl,const quint64 &haveDoneBytes,const quint64 &totalBytes) = 0;
signals:
    //上传/下载等开始信号
    void start();
    //一个文件上传/下载完成信号
    void subFileEnd(const QString &taskID,const QString &fileUrl,const QString &destAbst);
    //上传/下载等结束信号
    void end(const QString &taskID);
    void process(const QString &fileUrl,const quint64 &haveDoneBytes,const quint64 &totalBytes);
    //操作出错信号
    void error(const QString &taskID,const QString &src,const QString &errMsg);
    //操作可回显信息   暂不需要
//    void log(const QString &errMsg);
public:
    //异步调用线程对象，当异步执行动作的时候会用到它
//    QThread workerThread;

    QString taskUUID;
};

#endif // NETTRANSCLIENT_H
