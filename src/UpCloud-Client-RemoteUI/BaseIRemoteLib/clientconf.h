#ifndef CLIENTCONF_H
#define CLIENTCONF_H
#include "base.h"
#include "baseiremotelib_global.h"


class BASEIREMOTELIBSHARED_EXPORT ClientConf : public QObject
{
public:
    explicit ClientConf(QObject *parent = 0);
    ~ClientConf();
public:
    /**
         * @brief getLocalhost          读取中心服务器主机地址
         * @param localhost             中心服务器主机地址
         */
        void getLocalhost(QString &localhost);

        /**
         * @brief getMainPort           读取中心服务器长连接端口
         * @param mainPort              中心服务器长连接端口
         */
        void getMainPort(quint16 &mainPort);

        /**
         * @brief getMainTimeout        读取远程UI客户端长连接中心服务器超时时间(ms为单位)
         * @param mainTimeout           远程UI客户端长连接中心服务器超时时间
         */
        void getMainTimeout(quint32 &mainTimeout);

        /**
         * @brief getBlockSize 读取远程UI客户端到中心服务器 长连接 传输块大小(Byte为单位)
         * @param blockSize    传输块大小
         */
        void getMainBlockSize(quint32 &blockSize);

        /**
         * @brief getMainInterval   读取远程UI客户端到中心服务器 长连接 设置网络连接失败多长时间重新连接(s为单位)
         * @param interval          重新连接时间
         */
        void getMainInterval(quint32 &interval);

        /**
         * @brief getMainWriteTimeout    读取远程UI客户端到中心服务器 长连接 发送数据超时时间(ms为单位)
         * @param writeTimeout           发送数据超时时间
         */
        void getMainWriteTimeout(quint32 &writeTimeout);

        /**
         * @brief getMainReadTimeout    读取远程UI客户端到中心服务器 长连接 读取数据超时时间(ms为单位)
         * @param readTimeout           读取数据超时时间
         */
        void getMainReadTimeout(quint32 &readTimeout);

        /**
         * @brief getHeartthrobTimeout 远程UI客户端到中心服务器 定时心跳 超时时间(ms为单位)默认为5000ms
         * @param timeout 定时时间
         */
        void getHeartthrobTimeout(quint32 &timeout);

        /**
         * @brief getFtpRootPath
         * @param ftpRootPath
         */
        void getFtpRootPath(QString& ftpRootPath);
        /**
         * @brief getFtpAddr
         * @param ftpAddr
         */
        void getFtpAddr(QString& ftpAddr);
private:
    QSettings* m_set;
};

#endif // CLIENTCONF_H
