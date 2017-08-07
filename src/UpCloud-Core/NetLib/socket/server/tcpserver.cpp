#include "tcpserver.h"
TcpServer::TcpServer(QObject *parent )
    : QTcpServer(parent)
{

}

void TcpServer::incomingConnection(qintptr socketDescriptor)
{
    emit
        evt_NewClientArrived(socketDescriptor);
}
