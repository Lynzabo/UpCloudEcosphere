#include "timercontroller.h"

TimerController::TimerController(QObject *parent) : QObject(parent)
{
    m_socks.clear();
}

void TimerController::on_sync_socks(QMap<QTcpSocket *, quint64> &m_clients)
{
    this->m_socks.clear();
    this->m_socks = m_clients;
}

void TimerController::on_RemoteHostClosed(QTcpSocket *senderSock)
{
    if(m_socks.contains(senderSock))
    {
        m_socks.remove(senderSock);
    }
}

