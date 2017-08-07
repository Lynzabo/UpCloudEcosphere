#include "bridgeservermanager.h"
#include "baseiserver.h"
#include "endecrypt.h"
#include "db.h"

using namespace Environment::Net_Equip_MainType;
using namespace Environment::Terminal_Now_State;
using namespace Environment::EquipState;

BridgeServerManager::BridgeServerManager(QObject *parent) : QObject(parent)
{
    lock_restruct = new QMutex;
    //清空数据
    qDeleteAll(addresses);addresses.clear();

    QList<QTcpSocket*> sockets  = cachedArrays.keys();
    qDeleteAll(sockets);cachedArrays.clear();

    sockets  = gramInfoList.keys();
    qDeleteAll(sockets);
    QList<QList<DataGramInfo*> > grams = gramInfoList.values();
    while(grams.size() > 0)
    {
        qDeleteAll(grams.at(0));
    }
    gramInfoList.clear();


    sockets  = m_clients.keys();
    qDeleteAll(sockets);m_clients.clear();
    //TODO 修改8192为配置文件读取,并且在StartServer时候赋值
    m_netEngine = new TcpServerPool;

    //监听成功
    connect(m_netEngine,&TcpServerPool::evt_ListenSuccess,this,&BridgeServerManager::evt_ListenSuccess,Qt::QueuedConnection);
    //监听出错
    connect(m_netEngine,&TcpServerPool::evt_ListenError,this,&BridgeServerManager::evt_ListenError,Qt::QueuedConnection);

    //广播网络出错信息到TCP服务管理
    connect(m_netEngine,&TcpServerPool::evt_SocketError,this,&BridgeServerManager::on_SocketError,Qt::QueuedConnection);

    //与客户建立连接
    connect(m_netEngine,&TcpServerPool::evt_NewClientConnected,this,&BridgeServerManager::on_NewClientConnected,Qt::QueuedConnection);
    //与客户断开连接
    connect(m_netEngine,&TcpServerPool::evt_ClientDisconnected,this,&BridgeServerManager::on_ClientDisconnected,Qt::QueuedConnection);


    //接收客户端传输来数据
    connect(m_netEngine,&TcpServerPool::evt_Data_recieved,this,&BridgeServerManager::on_Data_recieved,Qt::QueuedConnection);//dircon
    //重组客户端发送过来的数据
    connect(this, SIGNAL(evt_read(QTcpSocket*,DataGramInfo*)), this, SLOT(on_read(QTcpSocket*,DataGramInfo*)));
    //向客户端发送数据
    connect(this,&BridgeServerManager::evt_write,m_netEngine,&TcpServerPool::SendDataToClient,Qt::QueuedConnection);
}

BridgeServerManager::~BridgeServerManager()
{
    m_netEngine->RemoveAllAddresses();
    m_netEngine->KickAllClients();
    m_netEngine->DeactiveImmediately();
    m_netEngine->deleteLater();
    //清空数据
    qDeleteAll(addresses);addresses.clear();

    QList<QTcpSocket*> sockets  = cachedArrays.keys();
    qDeleteAll(sockets);cachedArrays.clear();

    sockets  = gramInfoList.keys();
    qDeleteAll(sockets);
    QList<QList<DataGramInfo*> > grams = gramInfoList.values();
    while(grams.size() > 0)
    {
        qDeleteAll(grams.at(0));
    }
    gramInfoList.clear();


    sockets  = m_clients.keys();
    qDeleteAll(sockets);m_clients.clear();
}
////[0]开启,停止长连接服务
//开启长连接服务
void BridgeServerManager::StartServer(QVector<SocketMeta *> &addresses)
{
    this->addresses = addresses;
    int nListeners = this->addresses.size();
    if(nListeners<=0)
        throw trs("监听服务列表为空");
    m_netEngine->RemoveAllAddresses();
    m_netEngine->setNPayLoad(addresses.at(0)->getBlockSize());
    m_netEngine->setNReadTimeout(addresses.at(0)->getReadTimeout());
    m_netEngine->setNWriteTimeout(addresses.at(0)->getWriteTimeout());
    for (int i=0;i<nListeners;i++)
    {
        SocketMeta *sockMeta = this->addresses.at(i);
        if(sockMeta->getProtocol()!=SocketMeta::Protocol::TCP)
            throw trs("监听协议必须为UDP协议");
        QString listenName = trs("Listener%1").arg(i);
        QHostAddress listen_address(QHostAddress::Any) ;

        quint16 nPort = sockMeta->getPort();
        if (nPort<1024 || nPort>=32768 )
            throw trs("监听服务端口必须在1024到32768之间,服务%1端口%2").arg(listenName).arg(nPort);

        m_netEngine->AddListeningAddress(listenName,listen_address,nPort);
    }
    //nPlainThreads代表传输任务的线程个数
    int nPlainThreads = 1;
    //修改传输线程的个数,当重新启动服务的时候,修改nPlainThreads大小会发生问题,当第一次进来m_netEngine->TransThreadNum()大小为0
    //目前设计仅会进else if
    int nDeltaPlain = m_netEngine->TransThreadNum() - nPlainThreads;
    //删除超出个数的任务线程
    if (nDeltaPlain>0)
        m_netEngine->RemoveClientTransThreads(nDeltaPlain);
    //增加任务线程
    else if (nDeltaPlain<0)
        m_netEngine->AddClientTransThreads(-nDeltaPlain);
}
//停止长连接服务
void BridgeServerManager::StopServer()
{

}

////[1]监听Socke连接
void BridgeServerManager::on_NewClientConnected(QObject *client)
{
    QTcpSocket * sock = qobject_cast<QTcpSocket *> (client);
    m_clients.insert(sock, false);
    //数据缓存
    QByteArray nullArray;nullArray.clear();
    QList<DataGramInfo*> nullGramInfoList; nullGramInfoList.clear();
    cachedArrays.insert(sock,nullArray);
    gramInfoList.insert(sock,nullGramInfoList);
}

void BridgeServerManager::on_ClientDisconnected(QObject *client)
{
    QTcpSocket * sock = qobject_cast<QTcpSocket *> (client);
    if(m_clients.contains(sock))
    {
        m_clients.remove(sock);
        //数据缓存
        cachedArrays.remove(sock);
        QList<DataGramInfo*> graminfos = gramInfoList.value(sock);
        qDeleteAll(graminfos);
        gramInfoList.remove(sock);
    }

    emit evt_ClientDisconnected(sock);
}

void BridgeServerManager::on_SocketError(QObject *client, QAbstractSocket::SocketError socketError)
{
    QTcpSocket * sock = qobject_cast<QTcpSocket *> (client);
    if(m_clients.contains(sock))
    {
        m_clients.remove(sock);
        //数据缓存
        cachedArrays.remove(sock);
        QList<DataGramInfo*> graminfos = gramInfoList.value(sock);
        qDeleteAll(graminfos);
        gramInfoList.remove(sock);
    }

    emit evt_SocketError(client, socketError);
}


void BridgeServerManager::on_Data_recieved(QTcpSocket *client, const QByteArray& datas)
{
    //和客户端接收的区别是,必须在初始时候加锁,因为服务端接收是处理多个客户端的发送,restructQueue/cachedArray/gramInfo是事先放在集合里面的
    lock_restruct->lock();

    //获取当前客户端正在拼装的报文
    DataGramInfo* gramInfo = NULL;
    if(gramInfoList.value(client).isEmpty() == true)
    {
        gramInfo = new DataGramInfo;
        gramInfo->clear();
        gramInfoList[client].append(gramInfo);
    }
    else
    {
        gramInfo = gramInfoList.value(client).last();
        if(gramInfo->end_ISREAD == true)
        {
            gramInfo = new DataGramInfo;
            gramInfo->clear();
            gramInfoList[client].append(gramInfo);
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
        cachedArrays[client].clear();
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

        //解密message
        QString plainText;plainText.clear();
        QString priKey;priKey.clear();

        BotanEnDecrypt enDecrypt;
        TerminalKeYUtil::getInstance().getTerminalPriKey(gramInfo->UUID, priKey);
        enDecrypt.decryption(priKey, gramInfo->message, plainText);

        gramInfo->message = plainText;
        gramInfo->dataLength = plainText.size();

        emit
        evt_read(client,gramInfo);
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
        cachedArrays[client].append(datagram);
    lock_restruct->unlock();
}



void BridgeServerManager::on_write(QObject* clients, const QByteArray &datas)
{
    emit
    evt_write(clients,datas);
}



////[2]长连接
void BridgeServerManager::on_read(QTcpSocket *client, DataGramInfo *gram)
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
    if(gram->msgType == Bridge_Conn::REQBRIDGECONN )
    {
        QByteArray datagram;
        //接受报文实体对象
        ReqBridgeConn* gramEntity = NULL;
        //发送报文实体对象
        RespBridgeConn *respEntity = new RespBridgeConn;
        ////[1]反序列化报文体到实体对象
        quint8 msgType = gram->msgType;
        QString message = gram->message;
        try
        {
            gramEntity = DatagramUtil::getInstance().parseMessageText(CallbackByReqBridge,msgType,message);
        }
        catch(TransException &excep)
        {
            qDebug() << trs("反序列化报文体到实体对象:ErrorCode:%1,ErrorMsg:%2").arg(excep.getType()).arg(excep.getText());
            respEntity->State = excep.getType();
            goto sendDatagram;
        }
        try
        {
            ////[2]通过 固定码 判断此终端是否已经存在
            quint64 terminalUUID = gramEntity->UUID;
            if(CSTerminalDao::terminateIsExist(terminalUUID) == true)
            {
                ////[3]如果存在，则更新数据([IP] [MACAddr] [pubKey] [priKey] [state] [onlineTime] [offlineTime])
                //IP
                QString IP;IP.clear();
                IP = client->peerAddress().toString();
                //MACAddr
                QString MACAddr; MACAddr.clear();
                MACAddr = gramEntity->MacAddr;
                //pubKey
                QString pubKey; pubKey.clear();
                pubKey = gramEntity->PubKey;
                //priKey
                QString priKey; priKey.clear();
                priKey = gramEntity->PriKey;
                //state
                quint8 runState = ON_LINE;
                //onlineTime
                QString onlineTime; onlineTime.clear();
                TimerUtil::toString(onlineTime);
                //offlineTime
                QString offlineTime;offlineTime.clear();

                CSTerminalDao::updateTerminate(terminalUUID,IP, MACAddr, pubKey, priKey, runState, onlineTime, offlineTime);
            }
            else
            {
                ////[4]如果不存在，则插入新的数据
                //定义数据库入库实体
                CsTerminal* terminal = new CsTerminal;
                //UUID
                QString UUID;UUID.clear();
                UuidUtil::nextUUID(UUID);
                terminal->setUUID(UUID);
                //终端固定码
                terminal->setTerminalUUID(terminalUUID);
                //终端类型
                terminal->setType(TerminalUUIDUtil::getInstance().getTerminalUUIDType(gramEntity->UUID));
                //描述
                terminal->setDescription(QString());
                //IP
                terminal->setIP(client->peerAddress().toString());
                //MAC地址
                terminal->setMacAddr(gramEntity->MacAddr);
                 //公钥
                terminal->setPubKey(gramEntity->PubKey);
                //私钥
                terminal->setPriKey(gramEntity->PriKey);
                //状态
                terminal->setState(USABLE);
                //运行状态
                terminal->setRunState(ON_LINE);
                //创建时间
                QString createTime;createTime.clear();
                TimerUtil::toString(createTime);
                terminal->setCreateTime(createTime);
                //上线时间
                QString onlineTime;onlineTime.clear();
                TimerUtil::toString(onlineTime);
                terminal->setOnlineTime(onlineTime);
                //离线时间
                QString offlineTime;offlineTime.clear();
                terminal->setOfflineTime(offlineTime);

                //执行时数据库操作,向数据库中添加终端
                CSTerminalDao::addTerminate(*terminal);
            }
        }
        catch(DBException& dbExcep)
        {
            qDebug() << trs("数据库操作失败:ErrorCode:%1,ErrorMsg:%2").arg(dbExcep.getType()).arg(dbExcep.getText());
            //TODO
            respEntity->State = dbExcep.getType();
            goto sendDatagram;
        }
        ////[6]填充反馈报文实体对象
        respEntity->State = State::_0;
        goto sendDatagram;
        ////[7]发送回执报文
sendDatagram:
        try
        {
            DatagramUtil::getInstance().packDatagram(respEntity,datagram, gramEntity->UUID);
            m_netEngine->SendDataToClient(client, datagram);
            delete respEntity;
        }
        catch(QString &excep)
        {
            qDebug() << trs("出错:%1").arg(excep);
        }
        catch(TransException &excep)
        {
            qDebug() << excep.getText();
        }
        ////[8]更新此socket连接为true即建立长连接
        if(m_clients.contains(client))
        {
            m_clients[client] = true;
            emit evt_NewClientConnected(client, gram->UUID);
        }
    }
    else
    {
        if(m_clients.contains(client))
        {
            emit
            evt_business_graminfo(client, gram);
        }
    }
}

ReqBridgeConn *BridgeServerManager::CallbackByReqBridge(ReqBridgeConn *bridgeEntity)
{
    return bridgeEntity;
}

////[3]输出信息
void BridgeServerManager::outputTransThread()
{
    //取得网络处理核数
    int nClientThreads = m_netEngine->TransThreadNum();
    QString str_msg;
    str_msg += tr("Current Trans Threads: %1\n").arg(nClientThreads);
    int nTotalCLientsNums = 0;
    //输出每个核数下客户端数量
    for (int i=0;i<nClientThreads;i++)
    {
        str_msg += tr("\t%1:%2").arg(i+1).arg(m_netEngine->totalClients(i));
        if ((i+1)%5==0)
            str_msg += "\n";
        nTotalCLientsNums += m_netEngine->totalClients(i);
    }
}


void BridgeServerManager::OutputServerStatus()
{
    //记录网络状态信息
    QString str_msg;
    //获取网络所有监听对象
    QStringList lstListeners = m_netEngine->ListenerNames();
    str_msg += trs("Current Listen Threads: %1\n").arg(lstListeners.size());
    for (int i=0;i<lstListeners.size();i++)
        str_msg += trs("\tListen Threads %1: %2\n").arg(i+1).arg(lstListeners.at(i));
    //取得网络处理核数
    int nClientThreads = m_netEngine->TransThreadNum();

    str_msg += trs("Current Trans Threads: %1\n").arg(nClientThreads);
    int nTotalCLientsNums = 0;
    //输出每个核数下客户端数量
    for (int i=0;i<nClientThreads;i++)
    {
        str_msg += trs("\t%1:%2").arg(i+1).arg(m_netEngine->totalClients(i));
        if ((i+1)%5==0)
            str_msg += "\n";
        nTotalCLientsNums += m_netEngine->totalClients(i);
    }
}
