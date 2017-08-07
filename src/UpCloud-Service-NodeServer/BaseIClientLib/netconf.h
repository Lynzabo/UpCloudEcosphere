#ifndef NETCONF_H
#define NETCONF_H

#include "base.h"
#include "baseiclientlib_global.h"
class QSettings;

class BASEICLIENTLIBSHARED_EXPORT NetConf : public QObject
{
public:
    NetConf(QObject *parent = 0);
    ~NetConf();
public:
    /**
     * @brief getFtpHostname    读取FTP服务器主机地址
     * @param hostname          FTP服务器主机地址
     */
    void getFtpHostname(QString &hostname);

    /**
     * @brief getFtpPort        读取FTP服务器主机端口
     * @param port              FTP服务器主机端口
     */
    void getFtpPort(qint16 &port);

    /**
     * @brief getFtpUsername    登录FTP服务器用户名
     * @param username          用户名
     */
    void getFtpUsername(QString &username);

    /**
     * @brief getFtpPassword    登录FTP服务器密码
     * @param password          密码
     */
    void getFtpPassword(QString &password);

    /**
     * @brief getFtpIIsNum    读取FTP服务器允许同时下载文件数
     * @param iisNum          允许同时下载文件数
     */
    void getFtpIIsNum(int &iisNum);

    /**
     * @brief getFtpDownThreadsNum      读取FTP服务器下载单个文件启动线程数
     * @param asyncs            下载单个文件启动线程数
     */
    void getFtpDownThreadsNum(int &downThreadsNum);

    /**
     * @brief getHttpIIsNum   读取HTTP服务器允许同时下载文件数
     * @param iisNum          允许同时下载文件数
     */
    void getHttpIIsNum(int &iisNum);

    /**
     * @brief getHttpDownThreadsNum     读取HTTP服务器下载单个文件启动线程数
     * @param asyncs            下载单个文件启动线程数
     */
    void getHttpDownThreadsNum(int &downThreadsNum);
private:
    QSettings* m_set;
};
#endif // NETCONF_H
