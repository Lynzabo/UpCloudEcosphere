﻿#include "bridgeclientmanager.h"
#include "baseiremote.h"
#include "endecrypt.h"
using namespace Environment;
BridgeClientManager::BridgeClientManager(QObject *parent,SocketMeta *meta) : QObject(parent)
{
    m_reqBridgeConn = NULL;
    gramInfo = new DataGramInfo;
    cachedArray.clear();
    gramQueue.clear();
    sockmeta = meta;
    lock_write = new QMutex;
    //参数2代表网络传输一个块的大小
    client = new QTcpSocket(this);
    //校验请求服务ip/port输入是否合法
    connect(client, SIGNAL(hostFound()),this, SLOT(on_hostFound()));

    //当网络连接成功
    connect(client, SIGNAL(connected()),this, SLOT(on_client_connected()));
    //当网络连接断开
    connect(client, SIGNAL(disconnected()),this,SLOT(on_client_disconnected()));
    //当网络出错
    connect(client, SIGNAL(error(QAbstractSocket::SocketError)),this, SLOT(on_net_error(QAbstractSocket::SocketError)));

    //当接收服务端传来数据
    connect(client, SIGNAL(readyRead()),this, SLOT(new_data_recieved()));
    //对服务器传来数据流按报文装帧格式重组
    connect(this,&BridgeClientManager::evt_restructure_datagram, this, &BridgeClientManager::on_restructure_datagram,Qt::QueuedConnection);
    //长连接业务
    connect(this, &BridgeClientManager::evt_read, this, &BridgeClientManager::on_bridge);

    //客户端本次发送的数据块大小
    connect(client, SIGNAL(bytesWritten(qint64)), this, SLOT(on_client_trasferred(qint64)));
    //传输文件块队列控制
    connect(this,&BridgeClientManager::evt_send, this, &BridgeClientManager::on_send,Qt::QueuedConnection);
}

BridgeClientManager::~BridgeClientManager()
{
    delete sockmeta;
    sockmeta = NULL;
    delete lock_write;
    lock_write = NULL;
    gramQueue.clear();
    delete gramInfo;
}
////[0]启动与关闭
void BridgeClientManager::connectToServer()
{
    gramInfo->clear();
    cachedArray.clear();
    client->connectToHost(sockmeta->getHostname(),sockmeta->getPort());
    // State: 2; 2代表ConnectingState，正确的应该为3（ConnectedState）
    if(client->state()==QAbstractSocket::ConnectingState)
        qDebug() << trs("正在连接远程服务...");
    //阻塞4096ms去连接服务器
    if(!client->waitForConnected(sockmeta->getTimeout()))
    {
        qDebug() << trs("请求远程服务建立连接超时,%1s之后重新连接").arg(sockmeta->getInterval());
        QThread::sleep(sockmeta->getInterval());
        connectToServer();
    }
    if(client->state()==QAbstractSocket::ConnectedState)
    {
        qDebug() << trs("与远程服务已建立连接");
    }
    else
    {
        connectToServer();
    }
}

void BridgeClientManager::disConnectToServer()
{
    client->disconnected();
}

//长连接业务
void BridgeClientManager::bridgeConn()
{
    qDebug() << trs("开始建立长连接");
    if(this->genBridageDatagram() == false)
    {
        qDebug() << trs("生成长连接报文失败 ");
        bridgeConn();
    }
    else
    {
        //打包长连接报文
        QByteArray data;
        DatagramUtil::getInstance().packDatagram(m_reqBridgeConn,data);
        //发送长连接报文到服务端
        client->write(data);
    }
}

bool BridgeClientManager::genBridageDatagram()
{
    ////[0]初始化数据
    if(m_reqBridgeConn != NULL)
    {
        delete m_reqBridgeConn;
        m_reqBridgeConn = NULL;
    }
    m_reqBridgeConn  = new ReqBridgeConn;
    QString MACAddr;MACAddr.clear();
    ////[3]获取激活的MAC地址
    QStringList activeMACAddrs;activeMACAddrs.clear();
    MACUtil::getActiveMAC(activeMACAddrs);
    if(activeMACAddrs.size() >= 1)
    {
        MACAddr = activeMACAddrs.at(0);
    }
    else
    {
        qDebug() << QString("获取激活的MAC地址失败:%1!");
        return false;
    }
    ////[4]拼装请求报文实体
    //节点公钥码
    m_reqBridgeConn->PubKey = DatagramUtil::getInstance().m_pubKey;
    //节点私钥码
    m_reqBridgeConn->PriKey = DatagramUtil::getInstance().m_priKey;
    //MAC地址
    m_reqBridgeConn->MacAddr = MACAddr;

    return true;
}

////[2]连接与错误
void BridgeClientManager::on_client_connected()
{
    qDebug() << trs("连接中心服务成功");
    //发送长连接报文
    bridgeConn();
}

void BridgeClientManager::on_client_disconnected()
{
    qDebug() << trs("与中心服务断开连接");
    emit
    evt_client_disconnected(client);
}
void BridgeClientManager::on_net_error(QAbstractSocket::SocketError err)
{
    qDebug() << trs("网络连接错误:%1").arg(err);
    QTcpSocket * sock = qobject_cast<QTcpSocket *> (sender());
    emit
    evt_net_error(sock,err);
}


////[3]数据传输
//write
void BridgeClientManager::on_write(const QByteArray &datas)
{
    lock_write->lock();
    //往要下发报文队列中增加该报文,对于每种报文有优先级区分,优先级高的报文,尽管是后如队列,但是还是会先发送
    //暂未加优先级
    gramQueue.enqueue(datas);
    //控制下发
    if(gramQueue.size()>0)
    {
        QByteArray datas = gramQueue.dequeue();
        emit
        evt_send(datas);
    }
    lock_write->unlock();
}
//read
void BridgeClientManager::new_data_recieved()
{
    QTcpSocket * pSock = qobject_cast<QTcpSocket*>(sender());
    if (pSock)
    {
        QByteArray array =pSock->readAll();
        if(array.size()>0)
        {
            emit
            evt_restructure_datagram(array);
        }
    }
}

//restructure
void BridgeClientManager::on_restructure_datagram(const QByteArray &datas)
{
    QMutex lock;
    lock.lock();
    QByteArray tDatagram;
    tDatagram.clear();
    //已经读取的位移长度
    int shift = 0;
    if(cachedArray.size()>0)
    {
        tDatagram = cachedArray;
        cachedArray.clear();
    }
    //追加新数据,这里不再需要判断datas大小大于0,网络自定义TcpSocket获取数据时已经判断
    tDatagram += datas;
    QBuffer buffer(&tDatagram);
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
    if(tDatagram.size()>=shift+2) //  2   quint16
    {
        shift += 2;
        in >> gramInfo->begin;
        gramInfo->begin_ISREAD = true;
    }
    else
        goto extra;
msgTypeRead:;
    //2.报文类型-->1字节
    if(tDatagram.size()>=shift+1)  //  (2)+1 quint8
    {
        shift += 1;
        in >> gramInfo->msgType;
        gramInfo->msgType_ISREAD = true;
    }
    else
        goto extra;
UUIDRead:;
    //3.固定码-->8字节
    if(tDatagram.size()>=shift+8) //  (2+1)+8   quint64
    {
        shift += 8;
        in >> gramInfo->UUID;
        gramInfo->UUID_ISREAD = true;
    }
    else
        goto extra;
requestIDRead:;
    //4.请求码-->QString的32个长度,64的8bit长度+前4个字节代表QString长度,并且前4个字节放的值就为QString的8bit长度+4个长度字节
    if(tDatagram.size()>=shift+68) //  (2+1+8)+32*2+4  //QString
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
    if(tDatagram.size()>=shift+8) //   (2+1+8+32*2+4)+8   quint64
    {
        shift += 8;
        in >> gramInfo->timestamp;
        gramInfo->timestamp_ISREAD = true;
    }
    else
        goto extra;
dataLengthRead:;
    //6.报文体长度-->4字节 存放的是8bit的QString真实长度,不加真实长度
    if(tDatagram.size()>=shift+4) //  (2+1+8+32*2+4+8)+4    quint32
    {
        shift += 4;
        in >> gramInfo->dataLength;
        gramInfo->dataLength_ISREAD = true;
    }
    else
        goto extra;
messageRead:;
    //7.报文体-->gramInfo->dataLength长度+4
    if(tDatagram.size()>=(shift+gramInfo->dataLength+4))    //  (2+1+8+32*2+4+8+4)+gramInfo->dataLength+4(the QString's 8bit length+4 length)    QString
    {
        shift += (4+gramInfo->dataLength);
        in >> gramInfo->message;
        gramInfo->message_ISREAD = true;
    }
    else
        goto extra;
endRead:;
    //8.文件结尾标示符-->2字节
    if(tDatagram.size()>=(shift+2))    //   (2+1+8+32*2+4+8+4+gramInfo->dataLength+4)+2   quint16
    {
        shift += 2;
        in >> gramInfo->end;
        gramInfo->end_ISREAD = true;
        //TODO 要发送一个完整的报文出去，应该有一份内存拷贝当前graminfo,
        //否则如果发送的是当前报文,后面以队列方式连接，则执行gramInfo->clear();
        //时候就把同一份数据清掉了，对方接受的可能就是空值
        DataGramInfo *nextgramInfo = gramInfo;

        //解密message
        QString plainText;plainText.clear();
        QString priKey;priKey.clear();

        BotanEnDecrypt enDecrypt;
        enDecrypt.decryption(DatagramUtil::getInstance().m_priKey, gramInfo->message, plainText);

        gramInfo->message = plainText;
        gramInfo->dataLength = plainText.size();

        emit
        evt_read(nextgramInfo);
        gramInfo = new DataGramInfo;
        gramInfo->clear();
    }
    else
        goto extra;
extra:;
    //将本次未读取得剩余数据放到缓冲区,等插入数据到达时候先进行读取
    buffer.close();
    if(shift > 0 && tDatagram.length() >= shift)
    {
        tDatagram.remove(0,shift);
    }
    //如果有数据没有获取,缓存截断(当读到message中时候,shift为0,这时候缓存接下来的本次剩余)后的cache
    if(tDatagram.size()>0)
        cachedArray.append(tDatagram);
    lock.unlock();
}
//长连接
void BridgeClientManager::on_bridge(DataGramInfo *gram)
{
    //验证报文类型
    try{
        DatagramUtil::getInstance().validateMsgType(gram->msgType);
    }
    catch(QString &excep)
    {
        qDebug() << excep;
        return;
    }

    using namespace Environment::Datagram;
    if(gram->msgType == Bridge_Conn::RESPBRIDGECONN )
    {
        RespBridgeConn* respBridgeConn = new RespBridgeConn;
        respBridgeConn =  DatagramUtil::getInstance().parseMessageText(CallbackByRespBridge, gram->message_ISREAD, gram->message);
        if(respBridgeConn->State == State::_0)
        {
            qDebug() << trs("长连接建立成功 ");
            client->disconnect(this, &BridgeClientManager::evt_read, this, &BridgeClientManager::on_bridge);
            emit evt_bridgeConnSuccess(client, gram->UUID);
        }
        else
        {
            qDebug() << trs("长连接建立失败 ");
            qDebug() << trs("开始重新建立长连接");
            bridgeConn();
        }
        delete respBridgeConn;
    }
}

RespBridgeConn *BridgeClientManager::CallbackByRespBridge(RespBridgeConn *bridgeEntity)
{
    return bridgeEntity;
}


void BridgeClientManager::on_hostFound()
{
    qDebug() << trs("校验连接服务信息[IP:%1,port:%2]输入合法,超时时间%3ms,准备请求远程服务建立连接").arg(sockmeta->getHostname()).arg(sockmeta->getPort()).arg(sockmeta->getTimeout());
}

void BridgeClientManager::on_send(const QByteArray &datas)
{
    client->write(datas);
    QThread::currentThread()->msleep(50);
    QCoreApplication::processEvents(QEventLoop::ExcludeUserInputEvents);
}




void BridgeClientManager::on_client_trasferred(qint64 dtw)
{
    QTcpSocket * pSock = qobject_cast<QTcpSocket*>(sender());
    if (pSock)
    {
        emit
        evt_client_trasferred(pSock,dtw);
    }
}
