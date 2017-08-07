#include "heartthrobremoteexector.h"

HeartthrobRemoteExector::HeartthrobRemoteExector()
{

}

void HeartthrobRemoteExector::doExecute(QMap<QTcpSocket *, quint64> &m_socks, PushContext *context)
{
    ReqHeartthrobsConn *req = new ReqHeartthrobsConn;
    try
    {
        QList<quint64> socks= m_socks.values();
        if(socks.size()==1)
        {
            quint64 serverUUID = socks.at(0);
            QVector<quint64> server;
            server.append(serverUUID);
            context->setSocks(server);
            context->setMessage(req);
            qDebug() << trs("发送心跳报文 ");
            emit
            evt_write(context);
        }
    }
    catch(QString &excep)
    {
        qDebug() << trs("出错:%1").arg(excep);

    }
    catch(TransException &excep)
    {
        qDebug() << excep.getText();
    }
}

void HeartthrobRemoteExector::doSetArgs(QMap<QTcpSocket *, quint64> &socks)
{
    m_socks = socks;
}

void HeartthrobRemoteExector::doExecute()
{
    PushContext *context = new PushContext;
    this->doExecute(m_socks, context);
}
