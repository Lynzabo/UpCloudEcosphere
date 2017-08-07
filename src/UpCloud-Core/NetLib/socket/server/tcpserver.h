#ifndef TCPSERVER_H
#define TCPSERVER_H
#include <QTcpServer>
#include "netlib_global.h"
/**
 * @brief The TcpServer class   系统运行时,负责监听QTcpServer
 * 该类重载了QTcpServer的incomingConnection()方法
 */
class NETLIBSHARED_EXPORT TcpServer : public QTcpServer
{
    Q_OBJECT
public:
    TcpServer(QObject *parent);
protected:
    /**
     * @brief incomingConnection    客户端发起接入请求后,首先触发了TcpServer的incomingConnection方法
     * @param socketDescriptor
     * 1.当网络中一个客户端发起连接时,这个函数会被立刻调用.在本派生类中,并没有直接产生套接字.它仅仅触发了一个称为“evt_NewClientArrived”的信号
     * 2.这个信号把套接字描述符泵出给接受者,用于在其他的线程中创建套接字所用.
     */
    void incomingConnection(qintptr socketDescriptor);
signals:
    void evt_NewClientArrived(qintptr socketDescriptor);
};

#endif // TCPSERVER_H
