#include "tcpserverlistenthread.h"
TcpServerListenThread::TcpServerListenThread(QString  id, QHostAddress address , quint16 port, QObject *parent)
    :QObject(parent)
    ,m_tcpServer(0)
    ,m_id(id)
    ,m_address(address)
    ,m_port(port)
{
}


void TcpServerListenThread::on_startListen(QString  id)
{
    if (id==m_id)
    {
        if (!m_tcpServer)
        {
            qDebug() << trs("准备监听服务%1,端口%2").arg(id).arg(m_port);
            m_tcpServer = new TcpServer(this);
            connect (m_tcpServer,&TcpServer::evt_NewClientArrived,this,&TcpServerListenThread::evt_NewClientArrived,Qt::QueuedConnection);
            if (!m_tcpServer->isListening() && false==m_tcpServer->listen(m_address,m_port))
            {
                disconnect (m_tcpServer,SIGNAL(evt_NewClientArrived(qintptr)),this,SLOT(evt_NewClientArrived(qintptr)));
                emit
                    evt_ListenError(m_tcpServer->serverError(),id,m_port,m_tcpServer->errorString());
                //qDebug() << trs("服务%1监听%2端口失败,错误代码:%3,错误信息:%4").arg(id).arg(m_port).arg(m_tcpServer->serverError()).arg(m_tcpServer->errorString());
                m_tcpServer->deleteLater();
                m_tcpServer = 0;
                //关闭这个线程.
                emit
                    evt_ListenClosed(m_id);
            }
            else
            {
                emit
                    evt_ListenSuccess(id,m_port);
            }
        }
    }
}
void TcpServerListenThread::on_stopListen(QString  id)
{
    if (id==m_id)
    {
        if (m_tcpServer)
        {
            disconnect (m_tcpServer,SIGNAL(evt_NewClientArrived(qintptr)),this,SLOT(evt_NewClientArrived(qintptr)));
            m_tcpServer->close();
            m_tcpServer->deleteLater();
            m_tcpServer = 0;
            //关闭这个线程.
                qDebug() << trs("服务%1关闭监听").arg(m_port);
            emit
                evt_ListenClosed(m_id);
        }
    }
}
