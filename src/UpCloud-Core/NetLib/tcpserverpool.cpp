#include "tcpserverpool.h"
#include <QCoreApplication>
#include <QStringList>

TcpServerPool::TcpServerPool(QObject *parent) :
    QObject(parent)
{
    //注册自定义信号/槽数据类型
    if (false==QMetaType::isRegistered(QMetaType::type("qintptr")))
        qRegisterMetaType<qintptr>("qintptr");
    if (false==QMetaType::isRegistered(QMetaType::type("QAbstractSocket::SocketError")))
        qRegisterMetaType<QAbstractSocket::SocketError>("QAbstractSocket::SocketError");
    if (false==QMetaType::isRegistered(QMetaType::type("QHostAddress")))
        qRegisterMetaType<QHostAddress>("QHostAddress");

}

QStringList TcpServerPool::ListenerNames()
{
    return m_map_netListenThreads.keys();
}

int TcpServerPool::TransThreadNum()
{
    return m_vec_NetTransThreads.size();
}

int TcpServerPool::totalClients(int idxThread)
{
    int nsz = m_vec_NetTransThreads.size();
    if (idxThread >=0 && idxThread<nsz)
        return m_vec_NetTransThreads[idxThread]->CurrentClients();
    else
        return 0;
}
void TcpServerPool::setNPayLoad(int nPayLoad)
{
    m_nPayLoad = nPayLoad;
}
void TcpServerPool::setNReadTimeout(int nReadTimeout)
{
    m_nReadTimeout = nReadTimeout;
}

void TcpServerPool::setNWriteTimeout(int nWriteTimeout)
{
    m_nWriteTimeout = nWriteTimeout;
}

void TcpServerPool::AddListeningAddress(QString  id, const QHostAddress & address , quint16 nPort)
{
    if (m_map_netListenThreads.find(id)==m_map_netListenThreads.end())
    {
        //Start Thread
        QThread * pThread = new QThread(this);
        TcpServerListenThread * pListenObj = new TcpServerListenThread(id,address,nPort);
        pThread->start();
        //m_mutex_listen.lock();
        m_map_netInternalListenThreads[id] = pThread;
        m_map_netListenThreads[id] = pListenObj;
        //m_mutex_listen.unlock();
        //开始监听id
        connect(this,&TcpServerPool::evt_startListen,pListenObj,&TcpServerListenThread::on_startListen,Qt::QueuedConnection);
        //监听成功
        connect(pListenObj,&TcpServerListenThread::evt_ListenSuccess,this,&TcpServerPool::evt_ListenSuccess,Qt::QueuedConnection);
        //监听出错
        connect(pListenObj,&TcpServerListenThread::evt_ListenError,this,&TcpServerPool::on_ListenError,Qt::QueuedConnection);
        //停止监听id
        connect(this,&TcpServerPool::evt_stopListen,pListenObj,&TcpServerListenThread::on_stopListen,Qt::QueuedConnection);
        //停止监听当前线程,并删除该线程
        connect(pListenObj,&TcpServerListenThread::evt_ListenClosed,this,&TcpServerPool::on_ListenClosed,Qt::QueuedConnection);
        //客户端发起接入请求后,首先触发了TcpServer的incomingConnection方法,该方法里发出evt_NewClientArrived信号,TcpServer的evt_NewClientArrived信号
        //又连接TcpServerListenThread::evt_NewClientArrived信号，通过该信号又触发TcpServerPool::on_New_Arrived_Client槽
        connect(pListenObj,&TcpServerListenThread::evt_NewClientArrived,this,&TcpServerPool::on_New_Arrived_Client,Qt::QueuedConnection);

        pListenObj->moveToThread(pThread);
        //立刻开启监听,这时会触发TcpServerListenThread线程去开启QTcpServer
        emit
            evt_startListen(id);
    }
    else
        throw trs("%1对应监听端口%2已经存在").arg(id).arg(nPort);
}

void TcpServerPool::RemoveListeningAddress(QString  id)
{
    //m_mutex_listen.lock();
    if (m_map_netListenThreads.find(id)!=m_map_netListenThreads.end())
        emit
            evt_stopListen(id);
    //m_mutex_listen.unlock();
}

void TcpServerPool::RemoveAllAddresses()
{
    //m_mutex_listen.lock();
    foreach (QString id,m_map_netListenThreads.keys())
        emit evt_stopListen(id);
    //m_mutex_listen.unlock();
}


void TcpServerPool::on_New_Arrived_Client(qintptr socketDescriptor)
{
    TcpServerListenThread * pSource = qobject_cast<TcpServerListenThread *>(sender());
    if (!pSource)
    {
        return;
    }
    qDebug()<<trs("客户请求连接服务,准备分配连接线路");
    //从固定数目的工作线程中找到客户数最少的工作线程,往该线程放入新进来的客户
    int nsz = m_vec_NetTransThreads.size();
    int nMinPay = 0x7fffffff;//2147483647
    int nMinIdx = -1;
    //找到任务数最少的工作线程的索引
    for (int i=0;i<nsz && nMinPay!=0;i++)
    {
        if (m_vec_NetTransThreads[i]->isActive()==false)
            continue;
        int nPat = m_vec_NetTransThreads[i]->CurrentClients();

        if (nPat<nMinPay)
        {
            nMinPay = nPat;
            nMinIdx = i;
        }
        //qDebug()<<i<<" "<<nPat<<" "<<nMinIdx;
    }
    //删除未激活的线程
    for (int i=0;i<nsz;i++)
        if (m_vec_NetTransThreads[i]->isActive()==false )
            TransThreadDel(m_vec_NetTransThreads[i]);

    if (nMinIdx>=0 && nMinIdx<nsz)
        /*
         * evt_EstablishConnection 事件携带了由均衡策略确定的承接线程、socketDescriptor描述符。这个事件广播给所有的传输线程对象.在各
         * 个对象的incomingConnection槽中,具体生成用于传输的套接字对象.注意,这个槽函数是运行在各个传输线程的事件循环中的,因此,创建的套接
         * 字直接属于特定线程.
         */
        emit
            evt_EstablishConnection(m_vec_NetTransThreads[nMinIdx],socketDescriptor);
}

void TcpServerPool::on_ListenClosed(QString  id)
{
    //m_mutex_listen.lock();
    if (m_map_netListenThreads.find(id)!=m_map_netListenThreads.end())
    {
        //清除要关闭的对象
        TcpServerListenThread * pListenObj = m_map_netListenThreads[id];
        QThread * pThread = m_map_netInternalListenThreads[id];
        m_map_netListenThreads.remove(id);
        m_map_netInternalListenThreads.remove(id);
        //disconnect signals;
        disconnect(this,&TcpServerPool::evt_startListen,pListenObj,&TcpServerListenThread::on_startListen);
        disconnect(this,&TcpServerPool::evt_stopListen,pListenObj,&TcpServerListenThread::on_stopListen);
        disconnect(pListenObj,&TcpServerListenThread::evt_ListenClosed,this,&TcpServerPool::on_ListenClosed);
        disconnect(pListenObj,&TcpServerListenThread::evt_NewClientArrived,this,&TcpServerPool::on_New_Arrived_Client);
        pListenObj->deleteLater();
        pThread->quit();
        pThread->wait();
        pThread->deleteLater();

    }
    //m_mutex_listen.unlock();
}

void TcpServerPool::on_Data_recieved(QTcpSocket *socket, const QByteArray &datas)
{
    emit
        evt_Data_recieved(socket,datas);
}

void TcpServerPool::on_ListenError(QAbstractSocket::SocketError socketError, QString id, quint16 port, QString errorString)
{
    evt_ListenError(socketError,id,port,errorString);
}

void TcpServerPool::AddClientTransThreads(int nThreads)
{
    if (nThreads>0 && nThreads<256)
    {
        for (int i=0;i<nThreads;i++)
        {
            TcpServerTransThread * clientTH = new TcpServerTransThread(this,m_nPayLoad,m_nReadTimeout,m_nWriteTimeout);
            QThread * pThread = new QThread(this);
            //m_mutex_trans.lock();
            m_vec_netInternalTransThreads.push_back(pThread);
            m_vec_NetTransThreads.push_back(clientTH);
            //m_mutex_trans.unlock();
            pThread->start();
            //Connect signals
            //工作线程断开
            connect (clientTH,&TcpServerTransThread::evt_ClientDisconnected,this,&TcpServerPool::evt_ClientDisconnected,Qt::QueuedConnection);
            //接收客户端传输来数据
            connect (clientTH,&TcpServerTransThread::evt_Data_recieved,this,&TcpServerPool::on_Data_recieved,Qt::DirectConnection);
            //服务端发出数据
            connect (clientTH,&TcpServerTransThread::evt_Data_transferred,this,&TcpServerPool::evt_Data_transferred,Qt::QueuedConnection);
            //接入新客户端
            connect (clientTH,&TcpServerTransThread::evt_NewClientConnected,this,&TcpServerPool::evt_NewClientConnected,Qt::QueuedConnection);
            //网络出错
            connect (clientTH,&TcpServerTransThread::evt_SocketError,this,&TcpServerPool::evt_SocketError,Qt::QueuedConnection);
            //当有客户端接入时候,会执行on_New_Arrived_Client方法,在该方法会触发evt_EstablishConnection信号
            connect (this,&TcpServerPool::evt_EstablishConnection,clientTH,&TcpServerTransThread::incomingConnection,Qt::QueuedConnection);
            //服务集群
            connect (this,&TcpServerPool::evt_FireConnection,clientTH,&TcpServerTransThread::startConnection,Qt::QueuedConnection);
            //发送数据到客户端,从所有传输线程中查找是否包含当前客户端,有就发送数据出去
            //参数1放客户端对象,参数2放数据
            connect (this,&TcpServerPool::evt_SendDataToClient,clientTH,&TcpServerTransThread::SendDataToClient,Qt::QueuedConnection);
            //关闭当前网络线程所有客户端连接
            connect (this,&TcpServerPool::evt_KickAll,clientTH,&TcpServerTransThread::KickAllClients,Qt::QueuedConnection);
            //关闭当前网络线程并设置失效
            connect (this,&TcpServerPool::evt_DeactivteImmediately,clientTH,&TcpServerTransThread::DeactivateImmediately,Qt::QueuedConnection);
            //关闭指定客户端
            connect (this,&TcpServerPool::evt_KickClient,clientTH,&TcpServerTransThread::KickClient,Qt::QueuedConnection);

            clientTH->moveToThread(pThread);
        }
    }
}

bool TcpServerPool::TransThreadDel(TcpServerTransThread * pThreadObj)
{
    if (pThreadObj->CanExit()==false)
        return false;
    int nsz = m_vec_NetTransThreads.size();
    int idx = -1;
    for (int i=0;i<nsz && idx<0;i++)
    {
        if (m_vec_NetTransThreads[i]==pThreadObj)
            idx = i;
    }
    if (idx>=0 && idx <nsz)
    {
        TcpServerTransThread * clientTH =  m_vec_NetTransThreads[idx];
        disconnect (clientTH,&TcpServerTransThread::evt_ClientDisconnected,this,&TcpServerPool::evt_ClientDisconnected);
        disconnect (clientTH,&TcpServerTransThread::evt_Data_recieved,this,&TcpServerPool::evt_Data_recieved);
        disconnect (clientTH,&TcpServerTransThread::evt_Data_transferred,this,&TcpServerPool::evt_Data_transferred);
        disconnect (clientTH,&TcpServerTransThread::evt_NewClientConnected,this,&TcpServerPool::evt_NewClientConnected);
        disconnect (clientTH,&TcpServerTransThread::evt_SocketError,this,&TcpServerPool::evt_SocketError);
        disconnect (this,&TcpServerPool::evt_EstablishConnection,clientTH,&TcpServerTransThread::incomingConnection);
        disconnect (this,&TcpServerPool::evt_FireConnection,clientTH,&TcpServerTransThread::startConnection);
        disconnect (this,&TcpServerPool::evt_SendDataToClient,clientTH,&TcpServerTransThread::SendDataToClient);
        disconnect (this,&TcpServerPool::evt_KickAll,clientTH,&TcpServerTransThread::KickAllClients);
        disconnect (this,&TcpServerPool::evt_DeactivteImmediately,clientTH,&TcpServerTransThread::DeactivateImmediately);
        disconnect (this,&TcpServerPool::evt_KickClient,clientTH,&TcpServerTransThread::KickClient);

        m_vec_netInternalTransThreads[idx]->quit();
        m_vec_netInternalTransThreads[idx]->wait();
        m_vec_NetTransThreads[idx]->Empty_RabishCan();
        m_vec_netInternalTransThreads[idx]->deleteLater();
        m_vec_NetTransThreads[idx]->deleteLater();
        m_vec_netInternalTransThreads.remove(idx);
        m_vec_NetTransThreads.remove(idx);

    }
    return true;
}

void TcpServerPool::KickAllClients()
{
    //m_mutex_trans.lock();
    int nsz = m_vec_NetTransThreads.size();
    for (int i=0;i<nsz;i++)
        emit
            evt_KickAll(m_vec_NetTransThreads[i]);
    //m_mutex_trans.unlock();
}

void TcpServerPool::DeactiveImmediately()
{
    //m_mutex_trans.lock();
    int nsz = m_vec_NetTransThreads.size();
    for (int i=0;i<nsz;i++)
        emit
            evt_DeactivteImmediately(m_vec_NetTransThreads[i]);
    //m_mutex_trans.unlock();
}

void TcpServerPool::RemoveClientTransThreads(int nThreads)
{

    //m_mutex_trans.lock();
    int nsz = m_vec_NetTransThreads.size();
    if (nThreads<0)
        nThreads = nsz;
    int nCount = 0;
    for (int i=0;i<nsz && nCount<nThreads;i++)
    {
        //取消激活当前线程,当新连接到来的时候会判断给激活的线程上添加任务,并且清除未激活的线程
        m_vec_NetTransThreads[i]->Deactivate();
        nCount ++;
    }
    //Fire TransThreadDel Immediately
    this->CanExit();
    //m_mutex_trans.unlock();
}

void TcpServerPool::SendDataToClient(QObject * clients,QByteArray   dtarray)
{
    //查找当前client所在的传输线程,然后同步传输
    //for (int i = 0; i < clients.size(); ++i) {
     //    emit evt_SendDataToClient(clients.at(i),dtarray);
    //}
    emit evt_SendDataToClient(clients,dtarray);

}

void TcpServerPool::KickClients(QObject * object)
{
    emit evt_KickClient(object);
}

bool TcpServerPool::CanExit()
{
    bool res = true;
    //m_mutex_trans.lock();
    int nsz = m_vec_NetTransThreads.size();
    for (int i=nsz-1;i>=0 && res==true;i--)
        res = TransThreadDel( m_vec_NetTransThreads[i]);
    //m_mutex_trans.unlock();

    //m_mutex_listen.lock();
    if (m_map_netListenThreads.size())
        res= false;
    //m_mutex_listen.unlock();
    return res;
}

bool TcpServerPool::connectTo (const QHostAddress & address , quint16 nPort)
{
    bool res= false;
    //m_mutex_trans.lock();
    int nsz = m_vec_NetTransThreads.size();
    int nMinPay = 0x7fffffff;
    int nMinIdx = -1;

    for (int i=0;i<nsz && nMinPay!=0;i++)
    {
        if (m_vec_NetTransThreads[i]->isActive()==false)
            continue;
        int nPat = m_vec_NetTransThreads[i]->CurrentClients();

        if (nPat<nMinPay)
        {
            nMinPay = nPat;
            nMinIdx = i;
        }
        //qDebug()<<i<<" "<<nPat<<" "<<nMinIdx;
    }
    //remove old threads
    for (int i=0;i<nsz;i++)
        if (m_vec_NetTransThreads[i]->isActive()==false )
            TransThreadDel(m_vec_NetTransThreads[i]);

    if (nMinIdx>=0 && nMinIdx<nsz)
    {
        res = true;
        emit
            evt_FireConnection(m_vec_NetTransThreads[nMinIdx],address,nPort);
    }
    //m_mutex_trans.unlock();
    return res;
}
