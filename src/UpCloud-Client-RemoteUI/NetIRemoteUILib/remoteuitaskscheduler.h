#ifndef REMOTEUITASKSCHEDULER_H
#define REMOTEUITASKSCHEDULER_H
#include <QtCore>
#include "baseiremote.h"
#include "base.h"
#include "timer.h"
#include "net.h"
#include "duplex.h"
#include "timeriremoteui.h"
#include "bridge/bridgeclientmanager.h"
#include "action.h"
#include "netiremoteuilib_global.h"

class NETIREMOTEUILIBSHARED_EXPORT RemoteUITaskScheduler : public QObject
{
    Q_OBJECT
public:
    explicit RemoteUITaskScheduler(QObject *parent = 0);
    ~RemoteUITaskScheduler();
signals:
    //销毁客户端
    void destoryApp();
    //连接服务
    void evt_connectToServer();
    //远程客户端断开
    void evt_RemoteHostClosed(QTcpSocket *senderSock);
    //往服务写入数据
    void evt_write(const QByteArray &datas);
    //接收服务端传输来数据
    void evt_read(QTcpSocket *  client,const QString &clientKey,DataGramInfo * gram);
    //从调度器同步服务端信息
    void evt_sync_socks(QMap<QTcpSocket*,quint64> &m_server);
    //接收重定向数据
    void evt_receive_duplex(RequestContext * request,ResponseContext *response);
    //连接中心服务成功
    void evt_connectToServerSuccess();
    //开始连接服务
    void evt_connectToServerInit(const QString &ip,const quint16 &port);
public slots:
    /**
     * @brief on_redirect   转发到其它业务
     * @param request
     * @param response
     */
    void on_redirect(RequestContext * request,ResponseContext *response);
    /**
     * @brief on_bridgeConnSuccess   当客户端连接成功服务端
     */
    void on_bridgeConnSuccess(QTcpSocket *sock, quint64 UUID);
    /**
     * @brief on_client_disconnected    当服务端断开连接
     */
    void on_client_disconnected(QTcpSocket *sock);

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
     * @brief startup   启动任务调度
     */
    void startup();
    /**
     * @brief on_sync_clients   通知同步服务状态信息
     */
    void on_notice_sync_socks();
    /**
     * @brief on_take_write  定时器使用写入数据
     * @param socks
     * @param datas
     */
    void on_take_write(QObject * socks, const QByteArray &datas);
    /**
     * @brief on_write  过滤器使用写入数据
     * @param client
     * @param data
     */
    void on_write(QTcpSocket * client,const QByteArray &data);
private slots:
    /**
     * @brief on_connectToServer    请求连接服务
     */
    void on_connectToServer();
private:
    /**
     * @brief initViews 初始化UI,并为UI绑定事件
     */
    void initViews();
    /**
     * @brief initDatas 初始化UI数据
     */
    void initDatas();
    /**
     * @brief initBroadcast 初始化远程客户端绑定广播操作
     */
    void initBroadcast();
    void readConf();
private:
    //任务定时器
    TimerController *timer;
    //任务过滤器
    Filter *filter;
    //服务管理
    BridgeClientManager *manager;
    //对于客户端只会有1条记录,当与服务连接成功会放进来服务端连接对象和服务UUID
    QMap<QTcpSocket*,quint64> m_server;
    //连接服务元数据
    SocketMeta* sockmeta;
};

#endif // REMOTEUITASKSCHEDULER_H
