#ifndef SERVERTASKSCHEDULER_H
#define SERVERTASKSCHEDULER_H
#include <QtCore>
#include "netiserverlib_global.h"
#include "base.h"
#include "transmsg.h"
#include "action.h"
#include "timer.h"
#include "baseiserver.h"
#include "timeriserver.h"
#include "bridge/bridgeservermanager.h"
/**
 * @brief The ServerTaskScheduler class  服务端任务调度器
 */
class NETISERVERLIBSHARED_EXPORT ServerTaskScheduler : public QObject
{
    Q_OBJECT
public:
    explicit ServerTaskScheduler(QObject *parent = 0);
    ~ServerTaskScheduler();
    /**
     * @brief startup   启动任务调度
     */
    void startup();
    /**
     * @brief outputTransThread 输出每个工作线程的任务数量
     */
    void outputTransThread();

    /**
     * @brief outputTransProcess    输出发送/接收传输数据大小及速度
     */
//    void outputTransProcess();
signals:
    //停止服务
    void evt_finish();
    //往客户端发送数据
    void evt_write(QObject* clients, const QByteArray& datas);
    //接收客户端传输来数据
    void evt_read(QTcpSocket*  client,const QString &clientKey,DataGramInfo * gram);
    //定时计时服务
    void evt_stopTimer();
    //从调度器同步客户端信息
    void evt_sync_socks(QMap<QTcpSocket*,quint64> &socks);
    //远程客户端断开
    void evt_RemoteHostClosed(QTcpSocket* senderSock);
public slots:
    /**
     * @brief on_NewClientConnected 当有客户连接服务
     * @param client
     * @param uuid
     */
    void on_NewClientConnected(QTcpSocket *client, quint64 uuid);

    /**
     * @brief on_ClientDisconnected 客户端断开
     * @param client
     */
    void on_ClientDisconnected(QTcpSocket * client);


    /**
     * @brief on_write  写入数据
     * @param client
     * @param data
     */
    void on_write(QTcpSocket* client,const QByteArray &data);
    /**
     * @brief on_ListenSuccess  监听端口成功
     * @param id
     * @param port
     */
    void on_ListenSuccess(QString id,quint16 port);

    /**
     * @brief on_SocketError    与客户传输网络出错
     * @param senderSock
     * @param socketError
     */
    void on_SocketError(QObject* senderSock, QAbstractSocket::SocketError socketError);
    /**
     * @brief on_read   读取客户端数据
     * @param obj
     * @param datas
     */
    void on_read(QTcpSocket* client,DataGramInfo *gram);
    /**
     * @brief on_ListenError    监听端口出错
     * @param socketError   出错码
     * @param id    服务名
     * @param port  监听端口
     * @param errorString   出错信息
     */
    void on_ListenError(QAbstractSocket::SocketError socketError,QString id,quint16 port,QString errorString);

private:
    void readConf();
private:
    //服务管理
    BridgeServerManager *manager;
    QVector<SocketMeta *> addresses;
    QMutex read_lock;

    //节点服务器列表
    //m_RNoders存放所有在线节点服务器,
    QMap<QTcpSocket*,quint64> m_RNoders;
    //m_RClients存放所有在线远程UI客户端和第三方应用客户端
    QMap<QTcpSocket*,quint64> m_RClients;
    //m_RJ2EE存放所有web客户端
    QMap<QTcpSocket*,quint64> m_RJ2EE;

    //任务过滤器
    Filter *filter;
    //任务定时器
    TimerController *timer;
    QThread *timerThread;
};

#endif // SERVERTASKSCHEDULER_H
