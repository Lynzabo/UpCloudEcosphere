#ifndef TCPSERVERLISTENTHREAD_H
#define TCPSERVERLISTENTHREAD_H

#include <QHostAddress>
#include "tcpserver.h"
#include "base.h"
#include <QtCore>
/**
 * @brief The TcpServerListenThread class  监听器线程对象
 * TcpServerListenThread类管理一个监听地址.这个对象会被移植到线程中.这个线程支持TcpServerListenThread的消息队列.在消息
 * 队列中wait和accept方法会被执行
 */
class TcpServerListenThread : public QObject
{
    Q_OBJECT
protected:
    //ZP_TcpServer类的实例具体
    TcpServer * m_tcpServer;
    QString m_id;   //The listen ID
    QHostAddress m_address;
    quint16 m_port;
public:
    explicit TcpServerListenThread(QString  id, QHostAddress address ,quint16 port,QObject *parent = 0);
signals:
    //告诉TcpServerPool,停止监听当前线程,并删除该线程
    void evt_ListenClosed(QString );
    //告诉TcpServerPool,一个新的incoming connection到达
    void evt_NewClientArrived(qintptr socketDescriptor);
    //监听成功
    void evt_ListenSuccess(QString id,quint16 port);
    //监听出错
    void evt_ListenError(QAbstractSocket::SocketError socketError,QString id,quint16 port,QString errorString);
public slots:
    /**
     * @brief TcpServerListenThread::startListen    TcpServerPool发出startListen信号的时候,会触发该槽,并且所有TcpServerListenThread对象
     * 的startListen槽都会收到这个信号,我们通过id来标示是送给哪个TcpServerListenThread
     * @param id    标示当前监听线程
     */
    void on_startListen(QString  id);
    /**
     * @brief TcpServerListenThread::stopListen    TcpServerPool发出stopListen信号的时候,会触发该槽,并且所有TcpServerListenThread对象
     * 的stopListen槽都会收到这个信号,我们通过id来标示是送给哪个TcpServerListenThread
     * @param id    标示当前监听线程
     */
    void on_stopListen(QString  id);
private:
};
#endif // TCPSERVERLISTENTHREAD_H
