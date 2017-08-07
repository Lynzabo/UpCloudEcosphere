#ifndef BRIDGECLIENTMANAGER_H
#define BRIDGECLIENTMANAGER_H
#include <QtCore>
#include "neticlientlib_global.h"
#include "socket/client/tcpsocket.h"
#include "base.h"
#include "socket/socketmeta.h"
#include "transmsg.h"
class NETICLIENTLIBSHARED_EXPORT BridgeClientManager : public QObject
{
    Q_OBJECT
public:
    explicit BridgeClientManager(QObject *parent = 0,SocketMeta *meta = 0);
    ~BridgeClientManager();
    /**
     * @brief ConnectToServer   开启长连接服务
     */
    void connectToServer();
    /**
     * @brief DisConnectToServer    断开长连接服务
     */
    void disConnectToServer();
signals:
    void evt_bridgeConnSuccess(QTcpSocket * sock, quint64 UUID);
    void evt_read(DataGramInfo *gram);
    void evt_client_disconnected(QTcpSocket * sock);
    void evt_net_error(QTcpSocket * sock,QAbstractSocket::SocketError err);
    //客户端本次发送的数据块大小
    void evt_client_trasferred(QTcpSocket * pSock,qint64 dtw);
    //通知下一条报文可以下发
    void evt_send(const QByteArray &datas);
    void evt_restructure_datagram(const QByteArray &datas);
public slots:
    /**
     * @brief on_write 往服务器写入数据
     * @param datas 要写入的数据
     */
    void on_write(const QByteArray &datas);
    /**
     * @brief new_data_recieved 接收服务端传来数据
     */
    void new_data_recieved();
    /**
     * @brief on_client_connected   当网络连通
     */
    void on_client_connected();
    /**
     * @brief on_client_disconnected    当网络断开连接
     */
    void on_client_disconnected();
    /**
     * @brief on_client_trasferred  客户端本次发送的数据块大小
     * @param dtw
     */
    void on_client_trasferred(qint64 dtw);
    /**
     * @brief on_net_error  网络出错
     */
    void on_net_error(QAbstractSocket::SocketError err);
    /**
     * @brief on_hostFound  寻找主机
     */
    void on_hostFound();
    /**
     * @brief on_send   下发报文
     */
    void on_send(const QByteArray &datas);
    /**
     * @brief on_restructure_datagram   对服务端出来的数据流进行重组,重组为报文装帧格式
     * @param datas 服务端传输来的数据流
     */
    void on_restructure_datagram(const QByteArray &datas);

private:
    void bridgeConn();
    bool genBridageDatagram();
    static RespBridgeConn* CallbackByRespBridge(RespBridgeConn *bridgeEntity = 0);
private slots:
    void on_Read(DataGramInfo* gram);
private:
    QString m_pubKey;
    QString m_priKey;
    QString m_MACAddr;
    ReqBridgeConn* m_reqBridgeConn;
    RespBridgeConn* m_respBridgeConn;
private:
    QTcpSocket *client;
    SocketMeta* sockmeta;
    //写入服务器数据上锁
    QMutex* lock_write;
    //即要传输报文队列
    QQueue<QByteArray> gramQueue;

    //重组数据流上锁
    QMutex* lock_restruct;
    QByteArray cachedArray;
    DataGramInfo *gramInfo;

};

#endif // BRIDGECLIENTMANAGER_H
