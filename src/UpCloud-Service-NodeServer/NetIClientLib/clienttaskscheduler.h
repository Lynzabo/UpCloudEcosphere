#ifndef CLIENTTASKSCHEDULER_H
#define CLIENTTASKSCHEDULER_H
#include <QtCore>
#include "base.h"
#include "neticlientlib_global.h"
#include "action.h"
#include "timer.h"
#include "timericlient.h"
#include "baseiclient.h"
#include "bridge/bridgeclientmanager.h"
/**
 * @brief The ClientTaskScheduler class 客户端任务调度器
 */
class NETICLIENTLIBSHARED_EXPORT ClientTaskScheduler : public QObject
{
    Q_OBJECT
public:
    explicit ClientTaskScheduler(QObject *parent = 0);
    ~ClientTaskScheduler();
    /**
     * @brief startup   启动任务调度
     */
    void startup();
signals:
    //结束任务调度
    void evt_finish();
    //连接服务
    void evt_connectToServer();
    //往服务写入数据
    void evt_write(const QByteArray &datas);
    //接收服务端传输来数据
    void evt_read(QTcpSocket *  client,const QString &clientKey,DataGramInfo * gram);
    //往服务端发送数据
    void evt_write(QObject* socks, const QByteArray &datas);
    //定时计时服务
    void evt_stopTimer();
    //从调度器同步服务端信息
    void evt_sync_socks(QMap<QTcpSocket*,quint64> &m_server);
    //远程客户端断开
    void evt_RemoteHostClosed(QTcpSocket *senderSock);
public slots:    
    /**
     * @brief on_read   读取服务端数据
     * @param gram 装帧报文
     */
    void on_read(DataGramInfo *gram);
    /**
     * @brief evt_net_error 读取网络出错信息
     * @param sock
     * @param err
     */
    void on_net_error(QTcpSocket * sock,QAbstractSocket::SocketError err);
    /**
     * @brief on_client_trasferred  客户本次发送的块的大小
     * @param pSock
     * @param dtw
     */
    void on_client_trasferred(QTcpSocket * pSock,qint64 dtw);

    /**
     * @brief on_sync_clients   通知同步服务状态信息
     */
    void on_notice_sync_socks();
private slots:
    void on_bridgeConnSuccess(QTcpSocket*socket, quint64 UUID);
    /**
     * @brief on_connectToServer    请求连接服务
     */
    void on_connectToServer();
    /**
     * @brief on_client_disconnected    当服务端断开连接
     */
    void on_client_disconnected(QTcpSocket *sock);
    /**
     * @brief on_write  过滤器使用写入数据
     * @param client
     * @param data
     */
    void on_write(QTcpSocket * client,const QByteArray &data);
    /**
     * @brief on_take_write  定时器使用写入数据
     * @param socks
     * @param datas
     */
    void on_take_write(QObject * socks, const QByteArray &datas);
private:
    //服务管理
    BridgeClientManager *manager;
    //对于客户端只会有1条记录,当与服务连接成功会放进来服务端连接对象和服务UUID
    QMap<QTcpSocket*,quint64> m_server;
    //连接服务元数据
    SocketMeta* sockmeta;
    void readConf();
    //任务过滤器
    Filter *filter;
    //任务定时器
    TimerController *timer;
};

#endif // CLIENTTASKSCHEDULER_H
