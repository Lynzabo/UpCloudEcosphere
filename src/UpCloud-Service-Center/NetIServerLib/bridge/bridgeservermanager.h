#ifndef BRIDGESERVERMANAGER_H
#define BRIDGESERVERMANAGER_H
#include <QtCore>
#include "base.h"
#include "tcpserverpool.h"
#include "socket/socketmeta.h"
#include "netiserverlib_global.h"
#include "socket/client/tcpsocket.h"

class NETISERVERLIBSHARED_EXPORT BridgeServerManager : public QObject
{
    Q_OBJECT
public:
    explicit BridgeServerManager(QObject *parent = 0);
    ~BridgeServerManager();
    /**
     * @brief outputTransThread 输出每个工作线程的任务数量
     */
    void outputTransThread();
signals:
    //监听成功
    void evt_ListenSuccess(QString id,quint16 port);
    //监听出错
    void evt_ListenError(QAbstractSocket::SocketError socketError,QString id,quint16 port,QString errorString);

    //输出网络交互出错信息
    void evt_SocketError(QObject *senderSock, QAbstractSocket::SocketError socketError);

    //长连接接入新客户端
    void evt_NewClientConnected(QTcpSocket*, quint64);
    //长连接客户端断开
    void evt_ClientDisconnected(QTcpSocket* /*clientHandle*/);

    //接收客户端传输来数据
    void evt_read(QTcpSocket* client,DataGramInfo* gram);
    //传输数据到客户端
    void evt_write(QObject* clients, const QByteArray& dtarray);

    //除了长连接之外的其他业务的数据包
    void evt_business_graminfo(QTcpSocket* client,DataGramInfo* gram);

public slots:

    //接入新客户端
    void on_NewClientConnected(QObject* client);
    //客户断开
    void on_ClientDisconnected(QObject* client);
    //网络出错
    void on_SocketError(QObject* client, QAbstractSocket::SocketError socketError);
    //接收客户端传输来数据
    void on_Data_recieved(QTcpSocket *client, const QByteArray &datas);
    void on_read(QTcpSocket *client, DataGramInfo* gram);
    /**
     * @brief on_write  往指定的客户端写入数据
     * @param clients
     * @param datas
     */
    void on_write(QObject *clients, const QByteArray &datas);

public:
    /**
     * @brief StartServer   开启一组端口服务
     * @param addresses
     */
    void StartServer(QVector<SocketMeta *> &addresses);
    /**
     * @brief stopServer    关闭长连接服务
     */
    void StopServer();
    /**
     * @brief outputServerStatus    打印TCP服务服务器内核工作情况
     */
    void OutputServerStatus();
private:
    //TCP服务池
    TcpServerPool * m_netEngine;
    QVector<SocketMeta *> addresses;

    //重组数据流
    //重组数据流上锁
    QMutex *lock_restruct;
    //存放此客户端对应的数据缓存
    QMap<QTcpSocket*,QByteArray> cachedArrays;
    //存放此客户端对应的生成的报文列表
    QMap<QTcpSocket*,QList<DataGramInfo*> > gramInfoList;

    //长连接
private:
    static ReqBridgeConn* CallbackByReqBridge(ReqBridgeConn *bridgeEntity = 0);
    //在线节点服务器列表
    QMap<QTcpSocket*,bool> m_clients;
};

#endif // BRIDGESERVERMANAGER_H
