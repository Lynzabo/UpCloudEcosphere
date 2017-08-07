#ifndef TCPSERVERTRANSTHREAD_H
#define TCPSERVERTRANSTHREAD_H

#include <QtCore>
#include <QList>
#include <QAbstractSocket>
#include <QMutex>
#include <unordered_map>
#include <QSet>
#include <QList>
#include "transmsg.h"
class QMutex;
class QTcpSocket;
class TcpServerPool;
/**
 * @brief The TcpServerTransThread class    传输线程
 * 在一个传输线程池TcpServerPool的QVector<TcpServerTransThread *> m_vec_NetTransThreads中存放每一个传输线程TcpServerTransThread
 * 在每一个TcpServerTransThread中又存放多个客户端
 */
class TcpServerTransThread : public QObject
{
    Q_OBJECT
public:
    explicit TcpServerTransThread(TcpServerPool * pThreadPool,
                                  int nPayLoad = 4096,
                                  int nReadTimeout = 5000,
                                  int nWriteTimeout = 5000,
                                  QObject *parent = 0);
    ~TcpServerTransThread();
    /**
     * @brief clientsList   返回在线所有客户端
     * @return
     */
    QList <QObject *> clientsList();
    /**
     * @brief CurrentClients    返回在线所有客户端数量
     * @return
     */
    int CurrentClients();
    /**
     * @brief SetPayload    传输数据块被切大小,即一块的大小,最后一块肯定<=nPayload
     * @param nPayload
     */
    void SetPayload(int nPayload);
    /**
     * @brief isActive  当前线程是否可用
     * 当RemoveClientTransThreads的时候,会设置哪些线程不用,当on_New_Arrived_Client的时候,会删除不用线程,并往可用线程中添加任务
     * @return
     */
    bool isActive();

    bool CanExit();

    //清除垃圾箱
    void Empty_RabishCan();
    //Size of the RubbishCan
    static int RUBBISH_CAN_SIZE;

private:
    QQueue<QByteArray> gramQueue;
    bool m_bActivated;
    //尽管Qt的套接字本身具备缓存,塞入多大的数据都会成功, 但是本实现仍旧使用额外的队列, 每次缓存一个固定长度的片段并顺序发送. 这
    //样的好处,是可以给代码使用者一个机会,来加入代码检查缓冲区的大小,并作一些持久化的工作. 比如,队列超过100MB后,就把后续的数据
    //缓存在磁盘上, 而不是继续放在内存中,实现这个策略的变量是两个缓存:
    //sending buffer, hold byteArraies.
    //缓存存储各个套接字的队列
    std::unordered_map<QObject *,QList<QByteArray> > m_buffer_sending;
    //存储各个数据块的发送偏移
    std::unordered_map<QObject *,QList<qint64> > m_buffer_sending_offset;
    //客户端数目,可能是远程的客户连接客户端,可能是本地服务做客户端连接集群的客户端
    //存放当前工作线程的所有客户端
    QList<QObject*> m_clientList;
    int m_nPayLoad;
    int m_nReadTimeout;
    int m_nWriteTimeout;
    QMutex m_mutex_protect;
    TcpServerPool * m_pThreadPool;
    //当前传输线程客户端回收站
    //使用如下三个变量构建回收站
    QList<QObject *> m_rabish_can;
    QSet<QObject *> m_set_rabish;
    QMutex m_mutex_rabish_can;
    QMutex m_mutex_write;
    /**
     * @brief TcpServerTransThread::push_to_rabish_can  将要删除的客户端QTcpSocket指针对象放入回收站,超过回收站负载就删除该指针
     * @param deletedobj
     */
    void push_to_rabish_can(QObject * deletedobj);

public slots:
    /**
     * @brief TcpServerTransThread::incomingConnection  接收多线程的客户端连接
     * @param threadid  如果threadid不等于当前对象,这个信号仅仅被emit,不做其他操作
     * @param socketDescriptor  客户端socketDescriptor
     */
    void incomingConnection(QObject * threadid,qintptr socketDescriptor);
    /**
     * @brief TcpServerTransThread::startConnection 请求与远程建立连接
     * @param threadid  当前工作线程
     * @param addr  远程服务地址
     * @param port  远程服务端口
     */
    void startConnection(QObject * threadid,const QHostAddress & addr, quint16 port);
    //sending dtarray to objClient. dtarray will be pushed into m_buffer_sending
    /**
     * @brief SendDataToClient  发送数据到客户端,在执行该函数结束后会自动进some_data_sended进行自定义块大小发送
     * @param objClient 客户端QTcpSocket对象
     * @param dtarray   数据流
     */
    void SendDataToClient(QObject * objClient, const QByteArray& dtarray);
    /**
     * @brief Deactivate    设置当前传输线程不可用
     */
    void Deactivate();
    /**
     * @brief DeactivateImmediately 关闭当前网络线程并设置失效
     */
    void DeactivateImmediately(TcpServerTransThread *);
    //关闭工作线程所有客户端
    void KickAllClients(TcpServerTransThread *);
    //关闭工作线程指定客户端
    void KickClient(QObject *);
    /**
     * @brief on_send   下发报文
     */
    void on_send(QTcpSocket * pSock,const QByteArray &datas);
    /**
     * @brief on_restructure_datagram
     * @param datas
     */

protected slots:
    //当客户端关闭
    void client_closed();
    /**
     * @brief new_data_recieved 接收客户端数据
     * 在成功创建了套接字后, 数据的收发都在传输线程中运行了.当套接字收到数据后,简单的触发事件evt_Data_recieved
     */
    void new_data_recieved();
    void displayError(QAbstractSocket::SocketError socketError);
    //建立连接
    void on_connected();
signals:
    //网络出错
    void evt_SocketError(QObject * senderSock ,QAbstractSocket::SocketError socketError);
    //接入新客户端
    void evt_NewClientConnected(QObject * client);
    void evt_ClientEncrypted(QObject * client);
    //工作线程断开
    void evt_ClientDisconnected(QObject * client);
    //接收客户端传输来数据
    void evt_Data_recieved(QTcpSocket * ,const QByteArray &datas);
    //服务端发出数据
    void evt_Data_transferred(QObject * client,qint64);
    //通知下一条报文可以下发
    void evt_send(QTcpSocket * pSock,const QByteArray &datas);
};
#endif // TCPSERVERTRANSTHREAD_H
