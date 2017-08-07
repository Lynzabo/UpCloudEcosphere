#ifndef SOCKETMETA_H
#define SOCKETMETA_H
#include <QtCore>
#include "netlib_global.h"
//网络连接超时默认时间
const quint32 TIMEOUT = 10;
class NETLIBSHARED_EXPORT SocketMeta
{
public:
    enum Protocol{
        //数据报式Socket(SOCK_DGRAM),针对面向连接的TCP
        TCP,
        //流式Socket(SOCK_STREAM),对应于连接的UDP
        UDP
    };
public:
    SocketMeta(){}
    ~SocketMeta(){}
public:
    class NETLIBSHARED_EXPORT Builder{
    public:
        Builder();
        ~Builder();
        Builder(const Protocol &protocol,
                   const QString &hostname,
                   const quint16 &port,
                   const quint32 &timeout,
                    const quint32 &blockSize,
                    const quint32 &interval);
        /**
         * @brief setProtocol   设置通信协议
         * @param value
         * @return
         */
        Builder* setProtocol(const Protocol &value);
        /**
         * @brief setHostname 设置主机IP
         * @param value
         * @return
         */
        Builder* setHostname(const QString &value);
        /**
         * @brief setPort   设置主机端口
         * @param value
         * @return
         */
        Builder* setPort(const quint16 &value);
        /**
         * @brief setPassword   设置网络连接超时时间
         * @param value 网络超时时间设置,默认为10s
         * @return
         */
        Builder* setTimeout(const quint32 &value = TIMEOUT);
        /**
         * @brief setBlockSize  设置网络传输块的大小
         * @param value
         * @return
         */
        Builder* setBlockSize(const quint32 &value);
        /**
         * @brief setInterval   设置网络连接失败多长时间重新连接
         * @param value
         * @return
         */
        Builder* setInterval(const quint32 &value);
        /**
         * @brief setWriteTimeout   设置发送数据超时时间
         * @param value
         * @return
         */
        Builder* setWriteTimeout(int value);
        /**
         * @brief setReadTimeout    设置读取数据超时时间
         * @param value
         * @return
         */
        Builder* setReadTimeout(int value);
        SocketMeta* build();
    private:
        SocketMeta *net;
    };


    Protocol getProtocol() const;

    QString getHostname() const;

    qint16 getPort() const;

    quint32 getTimeout() const;

    quint32 getBlockSize() const;

    quint32 getInterval() const;

    int getWriteTimeout() const;

    int getReadTimeout() const;

private:
    //协议类型,指的是http/ftp
    Protocol protocol;
    //主机服务地址
    QString hostname;
    //主机服务端口
    quint16 port;
    //连接超时时间,以ms为单位
    quint32 timeout;
    //网络传输块的大小
    quint32 blockSize;
    //设置网络连接失败多长时间重新连接,s为单位
    quint32 interval;
    //发送数据超时时间,ms为单位
    quint32 writeTimeout;
    //读取数据超时时间,ms为单位
    quint32 readTimeout;
};

#endif // SOCKETMETA_H
