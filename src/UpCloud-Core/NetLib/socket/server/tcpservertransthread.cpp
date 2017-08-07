#include "tcpservertransthread.h"
#include <QTcpSocket>
#include <QSslSocket>
#include <assert.h>
#include <QDebug>
#include <QCoreApplication>
#include <QHostAddress>
#include "tcpserverpool.h"
#include <QMutex>
//网络上传/下载传输速度
QMutex g_mutex_sta;
quint64 g_bytesRecieved = 0;
quint64 g_bytesSent = 0;
quint64 g_secRecieved = 0;
quint64 g_secSent = 0;

int TcpServerTransThread::RUBBISH_CAN_SIZE = 256;

TcpServerTransThread::TcpServerTransThread(TcpServerPool *pThreadPool, int nPayLoad, int nReadTimeout, int nWriteTimeout, QObject *parent) :
    QObject(parent)
  ,m_pThreadPool(pThreadPool)
{
    gramQueue.clear();
    m_nPayLoad = nPayLoad;
    m_nReadTimeout = nReadTimeout;
    m_nWriteTimeout = nWriteTimeout;
    m_bActivated = true;
    //传输文件块队列控制
    connect(this,&TcpServerTransThread::evt_send, this, &TcpServerTransThread::on_send,Qt::QueuedConnection);

}

TcpServerTransThread::~TcpServerTransThread()
{

}

void TcpServerTransThread::Empty_RabishCan()
{
    m_mutex_rabish_can.lock();
    foreach (QObject * pDel,m_rabish_can)
        pDel->deleteLater();
    m_rabish_can.clear();
    m_set_rabish.clear();
    m_mutex_rabish_can.unlock();
}

bool TcpServerTransThread::isActive()
{
    return m_bActivated;
}

void TcpServerTransThread::Deactivate()
{
    m_bActivated = false;
}

QList <QObject *> TcpServerTransThread::clientsList()
{
    QList <QObject *> lsts ;
    m_mutex_protect.lock();
    lsts = m_clientList;
    m_mutex_protect.unlock();
    return lsts;
}

int TcpServerTransThread::CurrentClients()
{
    int nres = 0;
    m_mutex_protect.lock();
    nres = m_clientList.size();
    m_mutex_protect.unlock();
    return nres;
}

void TcpServerTransThread::DeactivateImmediately(TcpServerTransThread * ptr)
{
    if (ptr!=this)
        return;
    m_bActivated = false;
    this->KickAllClients(ptr);
}


void TcpServerTransThread::SetPayload(int nPayload)
{
    m_nPayLoad = nPayload;
    assert(m_nPayLoad>=256 && m_nPayLoad<=16*1024*1024);
}


void TcpServerTransThread::push_to_rabish_can(QObject * deletedobj)
{
    m_mutex_rabish_can.lock();
    if (m_set_rabish.contains(deletedobj)==false)
    {
        m_rabish_can.push_back(deletedobj);
        m_set_rabish.insert(deletedobj);
    }
    if (RUBBISH_CAN_SIZE<16)
        RUBBISH_CAN_SIZE = 16;
    if (RUBBISH_CAN_SIZE > 65536)
        RUBBISH_CAN_SIZE = 65536;
    if (m_rabish_can.size()>=RUBBISH_CAN_SIZE)
        qDebug()<< trs("删除旧的对象");

    while (m_rabish_can.size()>=RUBBISH_CAN_SIZE)
    {
        m_rabish_can.first()->deleteLater();
        m_set_rabish.remove(m_rabish_can.first());
        m_rabish_can.pop_front();
    }
    m_mutex_rabish_can.unlock();
}

void TcpServerTransThread::incomingConnection(QObject * threadid,qintptr socketDescriptor)
{
    if (threadid!=this)
        return;
    QTcpSocket * sock_client = new QTcpSocket(this);
    //该指针在连接关闭或者网络出错会利用回收站去删除
    if (sock_client)
    {
        //Initial content
        if (true ==sock_client->setSocketDescriptor(socketDescriptor))
        {
            //接收数据
            //  QTcpSocket::readyRead广播到TcpServerTransThread::new_data_recieved,在广播到TcpServerPool::evt_Data_recieved
            connect(sock_client, &QTcpSocket::readyRead,this, &TcpServerTransThread::new_data_recieved,Qt::QueuedConnection);
            //断开连接
            //  QTcpSocket::disconnected广播到TcpServerTransThread::client_closed,在广播到TcpServerPool::evt_ClientDisconnected
            connect(sock_client, &QTcpSocket::disconnected,this,&TcpServerTransThread::client_closed,Qt::QueuedConnection);
            //网络错误
            //  QTcpSocket::error广播到TcpServerTransThread::displayError,在广播到TcpServerPool::evt_ClientDisconnected和TcpServerPool::evt_Message
            connect(sock_client, SIGNAL(error(QAbstractSocket::SocketError)),this, SLOT(displayError(QAbstractSocket::SocketError)),Qt::QueuedConnection);
            //发出数据后
            //  QTcpSocket::bytesWritten广播到TcpServerTransThread::some_data_sended连接,在广播到TcpServerPool::evt_Data_transferred
            //connect(sock_client, &QTcpSocket::bytesWritten, this, &TcpServerTransThread::on_some_data_sended,Qt::QueuedConnection);
            m_mutex_protect.lock();
            m_clientList.insert(m_clientList.size(),sock_client);
            m_mutex_protect.unlock();

            qDebug()<<trs("为新客户ip:%1,port:%2分配传输线路完成").arg(sock_client->peerAddress().toString())
                      .arg(sock_client->peerPort());
            emit
            evt_NewClientConnected(sock_client);
            //emit evt_Message(sock_client,"Info>" +  QString(tr("Client Accepted.")));
        }
        else
            push_to_rabish_can(sock_client);
    }

}

void TcpServerTransThread::startConnection(QObject * threadid,const QHostAddress & addr, quint16 port)
{
    if (threadid!=this)
        return;
    QTcpSocket * sock_client =  new QTcpSocket(this);
    if (sock_client)
    {
        //接收数据
        //  QTcpSocket::readyRead广播到TcpServerTransThread::new_data_recieved,在广播到TcpServerPool::evt_Data_recieved
        connect(sock_client, &QTcpSocket::readyRead,this, &TcpServerTransThread::new_data_recieved,Qt::QueuedConnection);
        //断开连接
        //  QTcpSocket::disconnected广播到TcpServerTransThread::client_closed,在广播到TcpServerPool::evt_ClientDisconnected
        connect(sock_client, &QTcpSocket::disconnected,this,&TcpServerTransThread::client_closed,Qt::QueuedConnection);
        //网络错误
        //  QTcpSocket::error广播到TcpServerTransThread::displayError,在广播到TcpServerPool::evt_ClientDisconnected和TcpServerPool::evt_Message
        connect(sock_client, SIGNAL(error(QAbstractSocket::SocketError)),this, SLOT(displayError(QAbstractSocket::SocketError)),Qt::QueuedConnection);
        //发出数据后
        //  QTcpSocket::bytesWritten广播到TcpServerTransThread::some_data_sended连接,在广播到TcpServerPool::evt_Data_transferred
        //        connect(sock_client, &QTcpSocket::bytesWritten, this,&TcpServerTransThread::on_some_data_sended,Qt::QueuedConnection);
        //建立新连接
        //  QTcpSocket::connected广播到TcpServerTransThread::evt_NewClientConnected连接,在广播到TcpServerPool::evt_NewClientConnected
        connect(sock_client, &QTcpSocket::connected,this, &TcpServerTransThread::on_connected,Qt::QueuedConnection);
        m_mutex_protect.lock();
        m_clientList.insert(m_clientList.size(),sock_client);
        m_mutex_protect.unlock();
        sock_client->connectToHost(addr,port);
    }
    else
        assert(false);
}


void TcpServerTransThread::on_connected()
{
    QTcpSocket * pSock = qobject_cast<QTcpSocket*>(sender());
    emit evt_NewClientConnected(pSock);
}

void TcpServerTransThread::client_closed()
{
    QTcpSocket * pSock = qobject_cast<QTcpSocket*>(sender());
    if (pSock)
    {
        disconnect(pSock, &QTcpSocket::readyRead,this, &TcpServerTransThread::new_data_recieved);
        disconnect(pSock, &QTcpSocket::disconnected,this,&TcpServerTransThread::client_closed);
        disconnect(pSock, SIGNAL(error(QAbstractSocket::SocketError)),this, SLOT(displayError(QAbstractSocket::SocketError)));
        disconnect(pSock, &QTcpSocket::connected,this, &TcpServerTransThread::on_connected);

        m_buffer_sending.erase(pSock);
        m_buffer_sending_offset.erase(pSock);
        m_mutex_protect.lock();
        m_clientList.removeOne(pSock);
        m_mutex_protect.unlock();
        //pSock->abort();
        emit evt_ClientDisconnected(pSock);
        push_to_rabish_can(pSock);
    }
}
void TcpServerTransThread::new_data_recieved()
{
    QTcpSocket * pSock = qobject_cast<QTcpSocket*>(sender());
    if (pSock)
    {
        QByteArray array = pSock->readAll();

        if(array.size()>0)
        {
            int sz = array.size();
            g_mutex_sta.lock();
            g_bytesRecieved +=sz;
            g_secRecieved += sz;
            g_mutex_sta.unlock();
            emit
            evt_Data_recieved(pSock,array);
        }
    }
}

void TcpServerTransThread::displayError(QAbstractSocket::SocketError socketError)
{
    QTcpSocket * pSock = qobject_cast<QTcpSocket*>(sender());
    if (pSock)
    {
        emit evt_SocketError(pSock,socketError);
        //emit evt_Message(pSock,"Debug:" + pSock->errorString());
        disconnect(pSock, &QTcpSocket::readyRead,this, &TcpServerTransThread::new_data_recieved);
        disconnect(pSock, &QTcpSocket::disconnected,this,&TcpServerTransThread::client_closed);
        disconnect(pSock, SIGNAL(error(QAbstractSocket::SocketError)),this, SLOT(displayError(QAbstractSocket::SocketError)));
        //        disconnect(pSock, &QTcpSocket::bytesWritten, this, &TcpServerTransThread::on_some_data_sended);
        disconnect(pSock, &QTcpSocket::connected,this, &TcpServerTransThread::on_connected);
        m_buffer_sending.erase(pSock);
        m_buffer_sending_offset.erase(pSock);
        m_mutex_protect.lock();
        m_clientList.removeOne(pSock);
        m_mutex_protect.unlock();
        pSock->abort();
        emit evt_ClientDisconnected(pSock);
        //pSock->disconnectFromHost();
        //TODO 该错误是否应该删除该客户端连接,需要判断错误类型与否?
        push_to_rabish_can(pSock);
    }
}

void TcpServerTransThread::SendDataToClient(QObject *objClient, const QByteArray &dtarray)
{
    //将检查队列是否为空.为空的话,将触发 QTcpSocket::write方法发出m_nPayload大小的数据块.当这些数据块发送完毕,将触发QTcpSocket::bytesWritten事件,
    //由zp_netTransThread::some_data_sended槽响应
    m_mutex_protect.lock();
    //找到包含该客户端的工作线程
    if (m_clientList.contains(objClient)==false)
    {
        m_mutex_protect.unlock();
        return;
    }
    QTcpSocket * pSock = qobject_cast<QTcpSocket*>(objClient);
    if (pSock&&dtarray.size())
    {
        ////以后可更换队列为有优先级顺序,根据优先级选择先下发报文
        gramQueue.enqueue(dtarray);
        //控制下发
        if(gramQueue.size()>0)
        {
            QByteArray datas = gramQueue.dequeue();
            emit
            evt_send(pSock,datas);
        }
    }
    m_mutex_protect.unlock();
}
void TcpServerTransThread::on_send(QTcpSocket *pSock, const QByteArray &datas)
{
    m_mutex_write.lock();
    pSock->write(datas);
    pSock->waitForBytesWritten(m_nWriteTimeout);
//    QThread::currentThread()->msleep(50);
//    QCoreApplication::processEvents(QEventLoop::ExcludeUserInputEvents);
    m_mutex_write.unlock();
}



void TcpServerTransThread::KickAllClients(TcpServerTransThread * ptr)
{
    if (ptr!=this)
        return;
    m_mutex_protect.lock();
    QList<QObject *> clientList = m_clientList;
    m_mutex_protect.unlock();
    foreach(QObject * obj,clientList)
    {
        QTcpSocket * pSock = qobject_cast<QTcpSocket*>(obj);
        if (pSock)
        {
            pSock->disconnectFromHost();
        }

    }
}

void TcpServerTransThread::KickClient(QObject *objClient)
{
    m_mutex_protect.lock();
    if (m_clientList.contains(objClient)==false)
    {
        m_mutex_protect.unlock();
        return;
    }
    m_mutex_protect.unlock();
    QTcpSocket * pSock = qobject_cast<QTcpSocket*>(objClient);

    if (pSock)
    {
        pSock->disconnectFromHost();
    }
}

bool TcpServerTransThread::CanExit()
{
    if (m_bActivated==true)
        return false;
    if (CurrentClients())
        return false;
    return true;
}

#if 0
//新的解析报文数据的函数(考虑QStrng长度问题)---dyk
void TcpServerTransThread::on_restructure_datagram(QTcpSocket *client, const QByteArray &datas)
{
    //和客户端接收的区别是,必须在初始时候加锁,因为服务端接收是处理多个客户端的发送,restructQueue/cachedArray/gramInfo是事先放在集合里面的
    lock_restruct->lock();
    //如果不包含当前客户端,创建一条记录并进行初始化
    if(!cachedArrays.contains(client))
    {
        QByteArray nullArray;
        QList<DataGramInfo*> nullGramInfoList; nullGramInfoList.clear();
        cachedArrays.insert(client,nullArray);
        gramInfoList.insert(client,nullGramInfoList);
    }
    //获取当前客户端正在拼装的报文
    DataGramInfo* gramInfo = NULL;
    if(gramInfoList.value(client).isEmpty() == true)
    {
        gramInfo = new DataGramInfo;
        gramInfo->clear();
        ((QList<DataGramInfo*>)gramInfoList.value(client)).append(gramInfo);;
    }
    else
    {
        gramInfo = gramInfoList.value(client).last();
        if(gramInfo->end_ISREAD == true)
        {
            gramInfo = new DataGramInfo;
            gramInfo->clear();
            ((QList<DataGramInfo*>)gramInfoList.value(client)).append(gramInfo);
        }
    }

    //定义本次拼装的临时数据--存放数组datagram
    QByteArray datagram; datagram.clear();
    //定义本次拼装的临时数据--已经读取的位移长度
    int shift = 0;
    //获取当前客户端对应的缓存数据
    if(cachedArrays.value(client).size()>0)
    {
        datagram = cachedArrays.value(client);
        ((QByteArray)cachedArrays.value(client)).clear();
    }
    //追加新接收到到的数据,这里不再需要判断datas大小大于0,网络自定义TcpSocket获取数据时已经判断
    datagram += datas;
    QBuffer buffer(&datagram);
    buffer.open(QIODevice::ReadOnly);
    //输入
    QDataStream in(&buffer);
    //保持Version与写入时一致,这样不用考虑数据大小端先存问题
    in.setVersion(QDataStream::Qt_4_7);
    if(!gramInfo->begin_ISREAD)
    {
        goto beginRead;
    }
    else if(!gramInfo->msgType_ISREAD)
    {
        goto msgTypeRead;
    }
    else if(!gramInfo->UUID_ISREAD)
    {
        goto UUIDRead;
    }
    else if(!gramInfo->requestID_ISREAD)
    {
        goto requestIDRead;
    }
    else if(!gramInfo->timestamp_ISREAD)
    {
        goto timestampRead;
    }
    else if(!gramInfo->dataLength_ISREAD)
    {
        goto dataLengthRead;
    }
    else if(!gramInfo->message_ISREAD)
    {
        goto messageRead;
    }
    else if(!gramInfo->end_ISREAD)
    {
        goto endRead;
    }
    //从流中依次读取出来每个元数据,如果本次长度不够,从下次报文中读取
    //1.文件开始标记-->2字节
beginRead:;
    if(datagram.size()>=shift+2) //  2   quint16
    {
        shift += 2;
        in >> gramInfo->begin;
        gramInfo->begin_ISREAD = true;
    }
    else
        goto extra;
msgTypeRead:;
    //2.报文类型-->1字节
    if(datagram.size()>=shift+1)  //  (2)+1 quint8
    {
        shift += 1;
        in >> gramInfo->msgType;
        gramInfo->msgType_ISREAD = true;
    }
    else
        goto extra;
UUIDRead:;
    //3.固定码-->8字节
    if(datagram.size()>=shift+8) //  (2+1)+8   quint64
    {
        shift += 8;
        in >> gramInfo->UUID;
        gramInfo->UUID_ISREAD = true;
    }
    else
        goto extra;
requestIDRead:;
    //4.请求码-->QString的32个长度,64的8bit长度+前4个字节代表QString长度,并且前4个字节放的值就为QString的8bit长度+4个长度字节
    if(datagram.size()>=shift+68) //  (2+1+8)+32*2+4  //QString
        //use 8bit length,8bit length = QString.size()*2,and + the first 4bit QString length
    {
        shift += 68;
        in >> gramInfo->requestID;
        gramInfo->requestID_ISREAD = true;
    }
    else
        goto extra;
timestampRead:;
    //5.时间戳-->8字节
    if(datagram.size()>=shift+8) //   (2+1+8+32*2+4)+8   quint64
    {
        shift += 8;
        in >> gramInfo->timestamp;
        gramInfo->timestamp_ISREAD = true;
    }
    else
        goto extra;
dataLengthRead:;
    //6.报文体长度-->4字节 存放的是8bit的QString真实长度,不加真实长度
    if(datagram.size()>=shift+4) //  (2+1+8+32*2+4+8)+4    quint32
    {
        shift += 4;
        in >> gramInfo->dataLength;
        gramInfo->dataLength_ISREAD = true;
    }
    else
        goto extra;
messageRead:;
    //7.报文体-->gramInfo->dataLength长度+4
    if(datagram.size()>=(shift+gramInfo->dataLength+4))    //  (2+1+8+32*2+4+8+4)+gramInfo->dataLength+4(the QString's 8bit length+4 length)    QString
    {
        shift += (4+gramInfo->dataLength);
        in >> gramInfo->message;
        gramInfo->message_ISREAD = true;
    }
    else
        goto extra;
endRead:;
    //8.文件结尾标示符-->2字节
    if(datagram.size()>=(shift+2))    //   (2+1+8+32*2+4+8+4+gramInfo->dataLength+4)+2   quint16
    {
        shift += 2;
        in >> gramInfo->end;
        gramInfo->end_ISREAD = true;
        emit
        evt_Data_recieved(client,gramInfo);
        goto extra;
    }
    else
        goto extra;
extra:;
    //清除本次已经读取的Shift长度的数据
    buffer.close();
    if(shift > 0 && datagram.length() >= shift)
    {
        datagram.remove(0,shift);
    }
    //将本次未读取得剩余数据放到缓冲区,供下次读取拼装
    if(datagram.size()>0)
        ((QByteArray)cachedArrays.value(client)).append(datagram);
    lock_restruct->unlock();
}
#endif
#if 0
void TcpServerTransThread::on_restructure_datagram(QTcpSocket *client, const QByteArray &datas)
{
    //和客户端接收的区别是,必须在初始时候加锁,因为服务端接收是处理多个客户端的发送,restructQueue/cachedArray/gramInfo是事先放在集合里面的
    lock_restruct->lock();
    //如果重组线程队列集合不包含当前线程,创建一条记录并进行初始化
    if(!restructQueues.contains(client))
    {
        QQueue<QByteArray> nullQueue;
        QByteArray nullArray;
        restructQueues.insert(client,nullQueue);
        cachedArrays.insert(client,nullArray);
        DataGramInfo * nullGramInfo = new DataGramInfo;
        gramInfos.insert(client,nullGramInfo);
    }
    QQueue<QByteArray> restructQueue = restructQueues.value(client);
    QByteArray cachedArray = cachedArrays.value(client);
    DataGramInfo * gramInfo = gramInfos.value(client);
    if(!gramInfo)
        gramInfo = new DataGramInfo;
    restructQueue.enqueue(datas);
    //更新该队列
    restructQueues.remove(client);
    restructQueues.insert(client,restructQueue);
    //存放队列出队元素
    QByteArray datagram;
label:;
    datagram.clear();
    //第一次cachedArray肯定为空,以后可能不为空,如果不为空,存放的是上次出队列的数据
    if(cachedArray.size()>0)
        datagram = cachedArray;
    if(restructQueue.size()>0)
    {
        datagram += restructQueue.dequeue();
        //更新该队列
        restructQueues.remove(client);
        restructQueues.insert(client,restructQueue);
    }
    else
    {
        restructQueues.remove(client);
        cachedArrays.remove(client);
        //        delete gramInfo;
        gramInfos.remove(client);
        lock_restruct->unlock();
        return;
    }
    QBuffer buffer(&datagram);
    //qDebug() << trs("Analysis Size:") << datagram.size();
    buffer.open(QIODevice::ReadOnly);
    //输入
    QDataStream in(&buffer);
    in.setVersion(QDataStream::Qt_4_7);
    //对于传输过来的不符合报文装帧标准,会在解析报文体的时候校验
    if(gramInfo->begin==0)
    {
        goto beginRead;
    }
    else if(gramInfo->msgType==0)
    {
        goto msgTypeRead;
    }
    else if(gramInfo->UUID==0)
    {
        goto UUIDRead;
    }
    else if(gramInfo->requestID.isEmpty())
    {
        goto requestIDRead;
    }
    else if(gramInfo->timestamp==0)
    {
        goto timestampRead;
    }
    else if(gramInfo->dataLength==0)
    {
        goto dataLengthRead;
    }
    else if(gramInfo->message.isEmpty())
    {
        goto messageRead;
    }
    else if(gramInfo->end==0)
    {
        goto endRead;
    }
    else
    {
        //不可能进来
    }
    //从流中依次读取出来每个元数据,如果本次长度不够,从下次报文中读取
    //1.文件开始标记-->2字节
beginRead:;
    if(datagram.size()>=2)
        in >> gramInfo->begin;
    else
        goto extra;
msgTypeRead:;
    //2.报文类型-->1字节
    if(datagram.size()>=3)
        in >> gramInfo->msgType;
    else
        goto extra;
UUIDRead:;
    //3.固定码-->8字节
    if(datagram.size()>=11)
        in >> gramInfo->UUID;
    else
        goto extra;
requestIDRead:;
    //4.请求码-->32字节
    if(datagram.size()>=43)
        in >> gramInfo->requestID;
    else
        goto extra;
timestampRead:;
    //5.时间戳-->8字节
    if(datagram.size()>=51)
        in >> gramInfo->timestamp;
    else
        goto extra;
dataLengthRead:;
    //6.报文体长度-->4字节
    if(datagram.size()>=55)
        in >> gramInfo->dataLength;
    else
        goto extra;
messageRead:;
    //7.报文体-->gramInfo->dataLength字节
    if(datagram.size()>=55+gramInfo->dataLength)
    {
        in >> gramInfo->message;
    }
    else
        goto extra;
endRead:;
    //8.文件结尾标示符-->2字节
    //根据Qt机制肯定会把当前7个填满,然后进第8个.只是循环次数不清楚,每个DataGramInfo元数据合不合法也不知道,这个在业务部分有处理.
    if(datagram.size()>=55+gramInfo->dataLength+2)
    {
        in >> gramInfo->end;
        //cachedArray总保持缓冲器不会越来越大
        cachedArray.clear();
        cachedArrays.remove(client);
        cachedArrays.value(client,cachedArray);
        //        qDebug() << gramInfo->requestID;
        emit
        evt_Data_recieved(client,gramInfo);
        //        gramInfo->clear();
    }
    else
        goto extra;
    buffer.close();
    goto label;
extra:;
    //将本次未读的数据放到缓冲区域,等插入到下次数据流前面
    in >> cachedArray;
    cachedArrays.remove(client);
    cachedArrays.value(client,cachedArray);
    buffer.close();
    goto label;
}
#elif 0

void TcpServerTransThread::on_restructure_datagram(QTcpSocket *client, const QByteArray &datas)
{
    //和客户端接收的区别是,必须在初始时候加锁,因为服务端接收是处理多个客户端的发送,restructQueue/cachedArray/gramInfo是事先放在集合里面的
    lock_restruct->lock();
    //如果重组线程队列集合不包含当前线程,创建一条记录并进行初始化
    if(!restructQueues.contains(client))
    {
        QQueue<QByteArray> nullQueue;
        QByteArray nullArray;
        restructQueues.insert(client,nullQueue);
        cachedArrays.insert(client,nullArray);
        DataGramInfo * nullGramInfo = new DataGramInfo;
        gramInfos.insert(client,nullGramInfo);
    }
    QQueue<QByteArray> restructQueue = restructQueues.value(client);
    QByteArray cachedArray = cachedArrays.value(client);
    DataGramInfo * gramInfo = gramInfos.value(client);
    if(!gramInfo)
        gramInfo = new DataGramInfo;
    restructQueue.enqueue(datas);
    //更新该队列
    restructQueues.remove(client);
    restructQueues.insert(client,restructQueue);
    //存放队列出队元素
    int left = 0;
label:;
    //第一次cachedArray肯定为空,以后可能不为空,如果不为空,存放的是上次出队列的数据
    if(cachedArray.size()>0)
    {
        datagram = cachedArray;
        cachedArray.clear();
    }
    if(restructQueue.size()>0)
    {
        datagram += restructQueue.dequeue();
    }
    else
    {
        lock_restruct->unlock();
        return;
    }
    QBuffer buffer(&datagram);
    //    qDebug() << trs("Analysis Size:") << datagram.size();
    buffer.open(QIODevice::ReadOnly);
    //输入
    QDataStream in(&buffer);
    in.setVersion(QDataStream::Qt_4_7);
    //对于传输过来的不符合报文装帧标准,会在解析报文体的时候校验
    if(gramInfo->begin==0)
    {
        goto beginRead;
    }
    else if(gramInfo->msgType==0)
    {
        goto msgTypeRead;
    }
    else if(gramInfo->UUID==0)
    {
        goto UUIDRead;
    }
    else if(gramInfo->requestID.isEmpty())
    {
        goto requestIDRead;
    }
    else if(gramInfo->timestamp==0)
    {
        goto timestampRead;
    }
    else if(gramInfo->dataLength==0)
    {
        goto dataLengthRead;
    }
    else if(gramInfo->message.isEmpty())
    {
        goto messageRead;
    }
    else if(gramInfo->end==0)
    {
        goto endRead;
    }
    else
    {
        //不可能进来
    }
    //从流中依次读取出来每个元数据,如果本次长度不够,从下次报文中读取
    //1.文件开始标记-->2字节
beginRead:;
    if(datagram.size()>=2)
    {
        left += 2;
        in >> gramInfo->begin;
    }
    else
    {
        goto extra;
    }
msgTypeRead:;
    //2.报文类型-->1字节
    if(datagram.size()>=3)
    {
        left += 1;
        in >> gramInfo->msgType;
    }
    else
    {
        goto extra;
    }
UUIDRead:;
    //3.固定码-->8字节
    if(datagram.size()>=11)
    {
        left += 8;
        in >> gramInfo->UUID;
    }
    else
        goto extra;
requestIDRead:;
    //4.请求码-->32字节
    if(datagram.size()>=79) // 11+ 32 * 2 + 4  //43
    {
        left += 68;
        in >> gramInfo->requestID;
    }
    else
        goto extra;
timestampRead:;
    //5.时间戳-->8字节
    if(datagram.size()>=87) //51
    {
        left += 8;
        in >> gramInfo->timestamp;
    }
    else
        goto extra;
dataLengthRead:;
    //6.报文体长度-->4字节
    if(datagram.size()>=91) //55
    {
        left += 4;
        in >> gramInfo->dataLength;
    }
    else
        goto extra;
messageRead:;
    //7.报文体-->gramInfo->dataLength字节
    if(datagram.size()>=(95+(gramInfo->dataLength*2)))    //55+xxx
    {
        left += (gramInfo->dataLength*2 + 4);
        in >> gramInfo->message;
        qDebug()<<gramInfo->message.size();
    }
    else
        goto extra;
endRead:;
    //8.文件结尾标示符-->2字节
    //根据Qt机制肯定会把当前7个填满,然后进第8个.只是循环次数不清楚,每个DataGramInfo元数据合不合法也不知道,这个在业务部分有处理.
    if(datagram.size()>=(95+(gramInfo->dataLength*2))+2)
    {
        left += 2;
        in >> gramInfo->end;
        cachedArrays.remove(client);
        cachedArrays.value(client,cachedArray);
        qDebug()<<"_________TYPE______"<< gramInfo->msgType << "____message____" << gramInfo->message.length();
        if(gramInfo->message.isEmpty())
        {
            qDebug()<<"((((((((((((((((((";
        }
        emit
        evt_Data_recieved(client,gramInfo);
        //gramInfo->clear();
    }
    else
        goto extra;
    buffer.close();
    datagram.remove(0,left);
    cachedArray.clear();
    left = 0;
    goto label;
extra:;
    //将本次未读的数据放到缓冲区域,等插入到下次数据流前面
    buffer.close();
    datagram.remove(0,left);
    cachedArray.append(datagram);
    left = 0;
    cachedArrays.remove(client);
    cachedArrays.value(client,cachedArray);
    goto label;
}
#endif
