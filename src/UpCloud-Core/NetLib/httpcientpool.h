#ifndef HTTPCIENTPOOL_H
#define HTTPCIENTPOOL_H
#include "nettransclient.h"

/**
 * @brief The FTPClientPool class Http客户端
 * notice:可以继承于文件传输类，也可以继承于命令传输类，命令传输后续会指定规则
 * visit:
 *      HttpCientPool *httpClient = new HttpCientPool;
 *      httpClient -> upload...
 *          delete httpClient;
 */
//HTTP协议默认允许同时下载文件数
const int HTTP_DEFAULT_IISNUM = 3;
//HTTP协议默认下载单个文件启动线程数
const int HTTP_DEFAULT_DOWNTHREADSNUM = 5;

class NETLIBSHARED_EXPORT HttpCientPool : public NetTransClient
{
    Q_OBJECT
public:
    HttpCientPool(const QString &taskID = "");
    /**
     * @brief upload    上传文件接口类
     * @param upGroups  预上传的文件集合
     *                  {[d:/1.txt,http://127.0.0.1:8080/1.txt],[d:/2.txt,http://127.0.0.1:8080/2.txt]}
     * @param async     同步还是异步  false为同步,true为异步
     * @param parallel  并行还是串行上传    false为串行，true为并行,对于并行上传,在配置文件有配置同时允许多少文件并行
     */
    void upload(const QMap<QString,QString> &upGroups,const bool &async = false,const bool &parallel = false,const int &iisNum = HTTP_DEFAULT_IISNUM,const int &upThreadsNum = HTTP_DEFAULT_DOWNTHREADSNUM);

    /**
     * @brief download 下载文件接口类
     * @param downGroups 预下载的文件集合
     *                  {[http://127.0.0.1:8080/1.txt,d:/1.txt],[http://127.0.0.1:8080/2.txt,d:/2.txt]}
     * @param async 同步还是异步  false为同步,true为异步
     * @param parallel  并行还是串行下载    false为串行，true为并行,对于并行下载,在配置文件有配置同时允许多少文件并行
     * @param iisNum    允许同时下载文件数
     * @param downThreadsNum    下载单个文件启动线程数
     */
    void download(const QMap<QString,QString> &downGroups,const bool &async = false,const bool &parallel = false,const int &iisNum = HTTP_DEFAULT_IISNUM,const int &downThreadsNum = HTTP_DEFAULT_DOWNTHREADSNUM);
protected slots:
    void transError(const QString &src,const QString &errMsg);
    void transStart();
    void transSubFileEnd(const QString &fileUrl,const QString &destAbst);
    void transEnd();
    void transProcess(const QString &fileUrl,const quint64 &haveDoneBytes,const quint64 &totalBytes);
};

#endif // HTTPCIENTPOOL_H
