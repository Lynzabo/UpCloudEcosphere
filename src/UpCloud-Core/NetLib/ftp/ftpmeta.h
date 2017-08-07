#ifndef FTPMETA_H
#define FTPMETA_H
#include <QtCore>
#include "netlib_global.h"

/**
 * @brief The FtpMeta class Ftp元数据
 */
class NETLIBSHARED_EXPORT FtpMeta
{
public:
/// public:
    ~FtpMeta(){}
    FtpMeta(){}

public:
    class NETLIBSHARED_EXPORT Builder{
    public:
        Builder();
        ~Builder();
        Builder(const QString &hostname,
                   const qint16 &port,
                   const QString &username,
                   const QString &password);
        /**
         * @brief setHostname 设置主机服务地址
         * @param value
         * @return
         */
        Builder* setHostname(const QString &hostname);
        /**
         * @brief setPort   设置主机服务端口
         * @param value
         * @return
         */
        Builder* setPort(const qint16 &port);
        /**
         * @brief setUsername   设置主机服务登录用户名
         * @param value
         * @return
         */
        Builder* setUsername(const QString &username);
        /**
         * @brief setPassword   设置主机服务登录密码
         * @param value
         * @return
         */
        Builder* setPassword(const QString &password);
        FtpMeta* build();
    private:
        FtpMeta *net;
    };
    QString getHostname() const;

    qint16 getPort() const;

    QString getUsername() const;

    QString getPassword() const;

private:
    //主机服务地址
    QString hostname;
    //主机服务端口
    qint16 port;
    //主机服务登录用户名
    QString username;
    //主机服务登录密码
    QString password;
};

#endif // FTPMETA_H
