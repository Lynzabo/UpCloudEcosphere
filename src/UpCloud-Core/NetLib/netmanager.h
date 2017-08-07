#ifndef NetManager_H
#define NetManager_H
#include <QtCore>
#include "netlib_global.h"

class NETLIBSHARED_EXPORT NetManager
{
////外部服务
public:
    /**
     * @brief upload 上传文件接口类
     * @param filesAbst 预上传的文件Abst集合
     * @param async 同步还是异步  false为同步,true为异步
     */
    virtual void upload(const QStringList &filesAbst,const bool &async = false) = 0;
    /**
     * @brief download 下载文件接口类
     * @param filesURL 预下载的文件URL集合
     * @param async 同步还是异步  false为同步,true为异步
     */
    virtual void download(const QStringList &filesURL,const bool &async = false) = 0;

////语义信息
public:
    //传输协议类型
    enum SERVICE{
        FTP,
        HTTP
    };
    ~NetManager(){}
    NetManager(){}

public:
    class NETLIBSHARED_EXPORT NetBuilder{
    public:
        NetBuilder();
        ~NetBuilder();
        NetBuilder(const SERVICE &service,
                   const QString &hostname,
                   const qint16 &port,
                   const QString &username,
                   const QString &password,
                   const qint16 &asyncnum);
        /**
         * @brief setService    设置主机服务类型
         * @param value
         * @return
         */
        NetBuilder* setService(const SERVICE &service=SERVICE::FTP);
        /**
         * @brief setHostname 设置主机服务地址
         * @param value
         * @return
         */
        NetBuilder* setHostname(const QString &hostname);
        /**
         * @brief setPort   设置主机服务端口
         * @param value
         * @return
         */
        NetBuilder* setPort(const qint16 &port);
        /**
         * @brief setUsername   设置主机服务登录用户名
         * @param value
         * @return
         */
        NetBuilder* setUsername(const QString &username);
        /**
         * @brief setPassword   设置主机服务登录密码
         * @param value
         * @return
         */
        NetBuilder* setPassword(const QString &password);
        /**
         * @brief setPassword   设置异步下载文件数目
         * @param value
         * @return
         */
        NetBuilder* setAsyncnum(const qint16 &asyncnum=5);
        NetManager* build();
    private:
        NetManager *net;

    };
private:
    //传输协议类型
    SERVICE service;
    //主机服务地址
    QString hostname;
    //主机服务端口
    qint16 port;
    //主机服务登录用户名
    QString username;
    //主机服务登录密码
    QString password;
    //异步下载文件数目
    qint16 asyncnum;

};

#endif // NetManager_H
