#include "servertaskscheduler.h"
#include "serverconf.h"
#include "baseiserver.h"
ServerTaskScheduler::ServerTaskScheduler(QObject *parent) : QObject(parent)
{
    //任务定时器
    timer = new CSTimerController;
    //任务过滤器
    filter = new TaskSchedulerFilter;
    m_RNoders.clear();
    m_RClients.clear();
    m_RJ2EE.clear();

    readConf();
    manager = new BridgeServerManager(this);
    //监听端口成功
    connect(manager,&BridgeServerManager::evt_ListenSuccess,this,&ServerTaskScheduler::on_ListenSuccess,Qt::QueuedConnection);
    //监听端口出错
    connect(manager,&BridgeServerManager::evt_ListenError,this,&ServerTaskScheduler::on_ListenError,Qt::QueuedConnection);

    //当有客户端连接成功
    connect(manager,&BridgeServerManager::evt_NewClientConnected,this,&ServerTaskScheduler::on_NewClientConnected,Qt::QueuedConnection);
    //当有客户端断开连接
    connect(manager,&BridgeServerManager::evt_ClientDisconnected,this,&ServerTaskScheduler::on_ClientDisconnected,Qt::QueuedConnection);

    //当有客户端网络出错
    connect(manager,&BridgeServerManager::evt_SocketError,this,&ServerTaskScheduler::on_SocketError,Qt::QueuedConnection);

    //接收客户端传来数据
    connect(manager,&BridgeServerManager::evt_business_graminfo,this,&ServerTaskScheduler::on_read,Qt::DirectConnection);
    //传输数据到客户端
    connect(this,&ServerTaskScheduler::evt_write,manager,&BridgeServerManager::on_write,Qt::QueuedConnection);

    //过滤器参数
    //阻塞接收客户请求
    connect(this,&ServerTaskScheduler::evt_read,filter,&Filter::on_read,Qt::DirectConnection);
    //异步接收响应并发出
    connect(filter,&Filter::evt_write,this,&ServerTaskScheduler::on_write,Qt::DirectConnection);

    //任务定时组
    timerThread = new QThread(this);
    connect(timerThread,&QThread::started,timer,&TimerController::on_start);
    timer->moveToThread(timerThread);
    //当调度器发出停止计时信号,停止计时服务   该evt_stopTimer信号暂时没有添加
    connect(this,&ServerTaskScheduler::evt_stopTimer,timer,&TimerController::on_stop);
    //调度器发送最新客户端信息到计数器
    connect(this,&ServerTaskScheduler::evt_sync_socks,timer,&TimerController::on_sync_socks,Qt::DirectConnection);
    //计时发送数据给调度器,通过调度器阻塞发送数据到客户端列表
    connect(timer,&TimerController::evt_write,this,&ServerTaskScheduler::evt_write,Qt::QueuedConnection);
    //发送网络出错到定时计数控制
    connect(this,&ServerTaskScheduler::evt_RemoteHostClosed,timer,&TimerController::on_RemoteHostClosed,Qt::QueuedConnection);
}

ServerTaskScheduler::~ServerTaskScheduler()
{
    if(timer != NULL)
    {
        delete timer;
        timer = NULL;
    }
    if(filter != NULL)
    {
        delete filter;
        filter = NULL;
    }
    //不用删除,会自动删除QTcpSocket
    this->m_RNoders.clear();
    this->m_RClients.clear();
    this->m_RJ2EE.clear();
    //删除网络元数据集合
    qDeleteAll(this->addresses);
    this->addresses.clear();
}

void ServerTaskScheduler::startup()
{
    qDebug() << trs("准备监听服务");
    try
    {
        manager->StartServer(addresses);
    }catch(QString &excep)
    {
        qDebug() << trs("监听服务出错:%1").arg(excep);
        emit
        evt_finish();
    }
}

void ServerTaskScheduler::outputTransThread()
{
    manager->outputTransThread();
}

void ServerTaskScheduler::on_write(QTcpSocket * client,const QByteArray &data)
{
    emit
    evt_write((QObject*)client,data);
}

void ServerTaskScheduler::on_ListenSuccess(QString id, quint16 port)
{
    qDebug() << trs("服务%1监听%2端口成功,等待客户接入").arg(id).arg(port);
    //开启定时服务
    timerThread->start();
}

void ServerTaskScheduler::on_ClientDisconnected(QTcpSocket *client)
{
    //从当前节点/远程UI/J2ee列表中删除当前断开的远程
    if(m_RNoders.contains(client))
        m_RNoders.remove(client);
    else if(m_RClients.contains(client))
        m_RClients.remove(client);
    else if(m_RJ2EE.contains(client))
        m_RJ2EE.remove(client);
    emit
    evt_RemoteHostClosed(client);
}
void ServerTaskScheduler::on_ListenError(QAbstractSocket::SocketError socketError, QString id, quint16 port, QString errorString)
{
    qDebug() << trs("服务%1监听%2端口失败,失败代码:%3,失败原因:%4").arg(id).arg(port).arg(socketError).arg(errorString);
}

void ServerTaskScheduler::on_SocketError(QObject *senderSock, QAbstractSocket::SocketError socketError)
{
    QTcpSocket *socket = qobject_cast<QTcpSocket *>(senderSock);
    QString errorStr = trs("errorCode:%1,errorContent:%2").arg(socketError).arg(socket->errorString());
    qDebug()<<errorStr;
    if(socket->error() == QAbstractSocket::RemoteHostClosedError)
    {
        //从当前节点/远程UI/J2EE列表中删除当前断开的远程
        if(m_RNoders.contains(socket))
            m_RNoders.remove(socket);
        else if(m_RClients.contains(socket))
            m_RClients.remove(socket);
        else if(m_RJ2EE.contains(socket))
            m_RJ2EE.remove(socket);
        emit
        evt_RemoteHostClosed(socket);
    }
}

void ServerTaskScheduler::on_NewClientConnected(QTcpSocket *client, quint64 uuid)
{
    if(client)
    {
        qDebug()<<trs("客户ip:%1,port:%2, UUID:%3与服务端已经建立连接").arg(client->peerAddress().toString())
                  .arg(client->peerPort()).arg(uuid);

        //校验是节点服务器还是远程客户端,是节点服务器,往m_RNoders添加该节点服务器,是远程客户端,往m_RClients添加远程客户端
        Equip_Info *equipInfo = new Equip_Info;
        TerminalUUIDUtil::getInstance().parseTerminalUUID(uuid,equipInfo);
        //如果收到的是节点服务器传输来数据报文,往当前在线节点列表中保存当前节点
        if(equipInfo->EquipMainType == Environment::Net_Equip_MainType::DESKTOP_NODER)
        {
            m_RNoders.insert(client,uuid);
            emit evt_sync_socks(m_RNoders);
        }
        //如果收到的是远程UI传输来的数据报文,往当前在线远程UI列表中保存当前远程UI
        else if(equipInfo->EquipMainType == Environment::Net_Equip_MainType::DESKTOP_REMOTEUI)
        {
            m_RClients.insert(client,uuid);
//            emit evt_sync_socks(m_RClients);
        }
        else if(equipInfo->EquipMainType == Environment::Net_Equip_MainType::J2EE_REMOTEUI)
        {
            m_RJ2EE.insert(client,uuid);
//            emit vt_sync_socks(m_RJ2EE);
        }
        else
            return;
        delete equipInfo;
    }
}

void ServerTaskScheduler::on_read(QTcpSocket *client, DataGramInfo *gram)
{
    if(gram == NULL)
        return;
    //对建立过长连接的远程UI和节点服务器允许做业务处理
    if(m_RNoders.contains(client) || m_RClients.contains(client) || m_RJ2EE.contains(client))
    {
        emit
        evt_read(client,QString::number(gram->UUID),gram);
    }
}
void ServerTaskScheduler::readConf()
{
    this->addresses.clear();
    //解释数据块问题:考虑架构问题多个监听使用的还是固定的那几个任务传输线程,绑定哪个端口块的大小都一样,客户端不需要知道一次传块大小,
    //但需要知道传入的数据总长度
    //设置监听端口
    quint16 nPort1 = 0;
    //设置连接重新多长时间后请求连接
    //网络传输块的大小
    quint32 transBlockSize1 = 0;
    //发送数据超时时间
    quint32 writeTimeout1 = 0;
    //读取数据超时时间
    quint32 readTimeout1 = 0;

    ServerConf serconf;
    serconf.getNodeMainPort(nPort1);
    serconf.getNodeMainBlockSize(transBlockSize1);
    serconf.getNOdeMainWriteTimeout(writeTimeout1);
    serconf.getNodeMainReadTimeout(readTimeout1);

    if (nPort1<1024 || nPort1>=32768 )
        throw trs("监听服务端口必须在1024到32768之间,现在端口%1").arg(nPort1);
    if (transBlockSize1<10 || transBlockSize1>16*1024*1024 )
        throw trs("发送数据块大小必须在10到16*1024*1024之间,现在%1").arg(transBlockSize1);
    if (writeTimeout1<1000)
        throw trs("发送数据超时时间至少1000ms,现在%1").arg(writeTimeout1);
    if (readTimeout1<1000)
        throw trs("接收数据超时时间至少1000ms,现在%1").arg(readTimeout1);

    //设置监听端口
    quint16 nPort2 = 0;
    //设置连接重新多长时间后请求连接
    //网络传输块的大小
    quint32 transBlockSize2 = 0;
    //发送数据超时时间
    quint32 writeTimeout2 = 0;
    //读取数据超时时间
    quint32 readTimeout2 = 0;

    serconf.getUiMainPort(nPort2);
    serconf.getUiMainBlockSize(transBlockSize2);
    serconf.getUiMainWriteTimeout(writeTimeout2);
    serconf.getUiMainReadTimeout(readTimeout2);

    if (nPort2<1024 || nPort2>=32768 )
        throw trs("监听服务端口必须在1024到32768之间,现在端口%1").arg(nPort2);
    if (transBlockSize2<10 || transBlockSize2>16*1024*1024 )
        throw trs("发送数据块大小必须在10到16*1024*1024之间,现在%1").arg(transBlockSize2);
    if (writeTimeout2<1000)
        throw trs("发送数据超时时间至少1000ms,现在%1").arg(writeTimeout2);
    if (readTimeout2<1000)
        throw trs("接收数据超时时间至少1000ms,现在%1").arg(readTimeout2);


    //    assert(transBlockSize>=10 && transBlockSize<=16*1024*1024);
    SocketMeta::Builder *builder = new SocketMeta::Builder;
    SocketMeta *meta1 = (SocketMeta *)builder->setPort(nPort1)
            ->setBlockSize(transBlockSize1)
            ->setReadTimeout(writeTimeout1)
            ->setWriteTimeout(readTimeout1)
            ->setProtocol(SocketMeta::Protocol::TCP)
            //不需要setHostName,我们规定服务端允许任意IP访问
            ->build();
    SocketMeta::Builder *builder2 = new SocketMeta::Builder;
    SocketMeta *meta2 = (SocketMeta *)builder2->setPort(nPort2)
            ->setBlockSize(transBlockSize2)
            ->setReadTimeout(writeTimeout2)
            ->setWriteTimeout(readTimeout2)
            ->setProtocol(SocketMeta::Protocol::TCP)
            //不需要setHostName,我们规定服务端允许任意IP访问
            ->build();

    addresses.append(meta1);
    addresses.append(meta2);
    //读取多少线程同时干活nPlainThreads
}
