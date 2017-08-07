#include "abstractexector.h"

AbstractExector::AbstractExector()
{

}

void AbstractExector::doInit()
{
    //qDebug() << "Default Init";
}

void AbstractExector::doExecute(QMap<QTcpSocket *, quint64> &m_socks, PushContext *context)
{

}

void AbstractExector::doDestory()
{
    // qDebug() << "Default Destory";
}

void AbstractExector::doSetArgs(QMap<QTcpSocket *, quint64> &socks)
{

}

void AbstractExector::on_RemoteHostClosed(const quint64 &clientUUID)
{

}

void AbstractExector::doExecute()
{

}

