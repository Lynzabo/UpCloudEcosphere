/**
  * @brief This is the Zoom-Pipeline Network engine by goldenhawking, 2013,2014
  */
#ifndef TCPSERVERPOOL_H
#define TCPSERVERPOOL_H

#include <QObject>
#include "netlib_global.h"
#include <QThread>
#include <QMap>
#include <QVector>
#include <QMutex>
#include <QThread>
#include <QFile>
#include "socket/server/tcpserverlistenthread.h"
#include "socket/server/tcpservertransthread.h"
#include <QTcpSocket>
/**
 * @brief The TcpServerPool class   提供多线程的监听/传输网络
 */
class NETLIBSHARED_EXPORT TcpServerPool : public QObject
{
    Q_OBJECT
public:
    /**
     * @brief TcpServerPool 构建一个网络线程池
     * @param nPayLoad  自定义发送时缓存区块的大小
     * @param parent    当对象被delete的时候,该对象将被自动释放
     */
    explicit TcpServerPool(QObject *parent = 0);

    ////监听控制
    /**
     * @brief AddListeningAddress   添加一个套接字的监听,并且该socket会立刻被激活,并且一个address:port占据一个线程
     * @param id    多线程网络操作中,使用id标示操作的是哪个线程网络.使用id标示唯一的address:port.可以使用RemoveListeningAddress(id)关闭这个监听
     * @param address   监听的地址,即TCP服务对象.IPV6未测试
     * @param nPort TCP服务端口号.Linux环境该值必须大于1024
     */
    void AddListeningAddress(QString  id,const QHostAddress & address , quint16 nPort);
    /**
     * @brief RemoveListeningAddress    删除一个正在监听的套接字，并且该socket会立刻失效
     * @param id    当前网络标示
     */
    void RemoveListeningAddress(QString  id);
    /**
     * @brief RemoveAllAddresses    删除所有正在监听的套接字
     */
    void RemoveAllAddresses();

    ////传输控制
    /**
     * @brief TcpServerPool::AddClientTransThreads  添加多个传输线程来支持传输服务和客户端传输
     * @param nThreads  线程数目
     */
    void AddClientTransThreads(int nThreads);
    /**
     * @brief RemoveClientTransThreads  删除指定个数传输线程
     * @param nThreads
     * @param bSSL
     */
    void RemoveClientTransThreads(int nThreads);
    /**
     * @brief KickAllClients    删除所有客户传输线程
     */
    void KickAllClients();
    /**
     * @brief DeactiveImmediately   立刻取消激活
     */
    void DeactiveImmediately();


    //when Program exit, wait for close;
    /**
     * @brief CanExit   当程序退出，等待关闭
     * @return
     */
    bool CanExit();

    /**
     * @brief ListenerNames 返回所有监听名称
     * @return
     */
    QStringList ListenerNames();
    /**
     * @brief TransThreadNum    当前传输线程个数
     * @return
     */
    int TransThreadNum();
    /**
     * @brief totalClients  返回当前工作线程客户端数量
     * @param idxThread 当前线程,从0到TransThreadNum()-1
     * @return
     */
    int totalClients(int idxThread);
    /**
     * @brief setNPayLoad   设置网络传输数据块的大小
     * @param nPayLoad
     */
    void setNPayLoad(int nPayLoad);
    /**
     * @brief setNReadTimeout   设置读取一块数据块超时时间
     * @param nReadTimeout
     */
    void setNReadTimeout(int nReadTimeout);
    /**
     * @brief setNWriteTimeout   设置写入一块数据块超时时间
     * @param nWriteTimeout
     */
    void setNWriteTimeout(int nWriteTimeout);

protected:
    int m_nPayLoad;
    int m_nReadTimeout;
    int m_nWriteTimeout;
    //QMutex m_mutex_listen;
    //QMutex m_mutex_trans;

    //zp_netListenThread类本身是从QObject派生。它本身不是一个线程对象，而是被“绑定”在一个线程对象中运行的。一个进程可以拥有若干监听端口，
    //这些监听端口对应了不同的zp_netListenThread对象。这些监听线程对象由zp_net_Engine类管理，存储在这个类的成员变量中。
    //存放各端口的listenThreadObjects线程对象
    QMap<QString,TcpServerListenThread *> m_map_netListenThreads;
    //存储了listenThreadObjects各个端口的线程
    //Internal Threads to hold each listenThreadObjects' message Queue
    QMap<QString,QThread *> m_map_netInternalListenThreads;

    //存放服务与客户传输工作线程集合
    QVector<TcpServerTransThread *> m_vec_NetTransThreads;
    //存放服务与客户传输工作线程队列
    QVector<QThread *> m_vec_netInternalTransThreads;
    /**
     * @brief TcpServerPool::TransThreadDel 关闭当前工作线程,并进行必要的清理操作
     * @param pThreadObj
     * @return
     */
    bool TransThreadDel(TcpServerTransThread * pThreadObj);
signals:
    //网络出错
    void evt_SocketError(QObject * senderSock ,QAbstractSocket::SocketError socketError);
    //接入新客户端
    void evt_NewClientConnected(QObject * /*clientHandle*/);
    //客户断开
    void evt_ClientDisconnected(QObject * /*clientHandle*/);
    //接收客户端传输来数据
    void evt_Data_recieved(QTcpSocket *  /*clientHandle*/,const QByteArray&  /*data*/ );
    //一块数据被成功发送后
    void evt_Data_transferred(QObject *   /*clientHandle*/,qint64 /*bytes sent*/);

    //Internal Message for ctrl.------------------------------------
    ////监听控制
    //监听成功
    void evt_ListenSuccess(QString id,quint16 port);
    //开启监听id
    void evt_startListen(QString  id);
    //停止监听id
    void evt_stopListen(QString  id);
    //建立网络
    void evt_EstablishConnection(QObject * threadid,qintptr socketDescriptor);
    //与远程TCP服务建立网络连接
    void evt_FireConnection(QObject * threadid,const QHostAddress & hostAddr, quint16 port);
    //发送数据到客户端
    void evt_SendDataToClient(QObject * objClient,QByteArray   dtarray);
    void evt_KickClient(QObject *);
    void evt_DeactivteImmediately(TcpServerTransThread *);
    void evt_KickAll(TcpServerTransThread *);
    //监听出错
    void evt_ListenError(QAbstractSocket::SocketError socketError,QString id,quint16 port,QString errorString);
protected slots:
    /**
     * @brief TcpServerPool::on_New_Arrived_Client  从当前监听线程中接收TcpServer的incomingConnection,传递进来QTcpSocket的socketDescriptor,
     * TcpServerPool做出均衡控制,会从当前可用的传输线程中确定最空闲的那个线程,而后把套接字描述符转交给传输线程
     * @param socketDescriptor
     */
    void on_New_Arrived_Client(qintptr socketDescriptor);
    /**
     * @brief on_ListenClosed   当停止监听一个线程网络的时候,清除该线程本身及线程池相关内容
     * @param id    要停止的线程主键
     */
    void on_ListenClosed(QString  id);
    //接收客户端传输来数据
    void on_Data_recieved(QTcpSocket * socket, const QByteArray &datas);
public slots:
    /**
     * @brief on_ListenError    监听端口出错
     * @param socketError   出错码
     * @param id    服务名
     * @param port  监听端口
     * @param errorString   出错信息
     */
    void on_ListenError(QAbstractSocket::SocketError socketError,QString id,quint16 port,QString errorString);
    /**
     * @brief SendDataToClient  发送数据到客户端
     * @param objClient 客户端QTcpSocket对象
     * @param dtarray   数据流
     */
    void SendDataToClient(QObject *clients, QByteArray   dtarray);
    /**
     * @brief KickClients   关闭指定客户端
     * @param object
     */
    void KickClients(QObject * object);

    /**
     * @brief TcpServerPool::connectTo  连接到一个服务地址
     * @param address   远程服务IP
     * @param nPort 远程服务端口
     * @return
     */
    bool connectTo (const QHostAddress & address , quint16 nPort);

};
#endif // TCPSERVERPOOL_H
