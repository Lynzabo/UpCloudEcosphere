#include "remoteuitaskscheduler.h"

RemoteUITaskScheduler::RemoteUITaskScheduler(QObject *parent) : QObject(parent)
{
    //任务定时器
    timer = new RUTimerController;
    //任务过滤器
    filter = new TaskSchedulerFilter;
    m_server.clear();
    readConf();
    manager = new BridgeClientManager(this,sockmeta);
    //连接服务
    connect(this,SIGNAL(evt_connectToServer()),this,SLOT(on_connectToServer()));
    //连接服务成功
    connect(manager,&BridgeClientManager::evt_bridgeConnSuccess,this,&RemoteUITaskScheduler::on_bridgeConnSuccess,Qt::QueuedConnection);

}

RemoteUITaskScheduler::~RemoteUITaskScheduler()
{
    delete timer;
    delete filter;
    //会自动删除QTcpSocket
    this->m_server.clear();
    delete sockmeta;
}
//开启调度服务
void RemoteUITaskScheduler::startup()
{
    qDebug() << trs("调取器在后台工作,工作实例ID:") << QThread::currentThreadId();
    qDebug() << trs("准备连接中心服务");
    emit
    evt_connectToServer();
}
void RemoteUITaskScheduler::on_connectToServer()
{
    //通知UI开始连接
    emit
    evt_connectToServerInit(sockmeta->getHostname(),sockmeta->getPort());
    manager->connectToServer();
}
//长连接成功
void RemoteUITaskScheduler::on_bridgeConnSuccess(QTcpSocket *sock, quint64 UUID)
{
    ////数据连接
    //连接服务断开,当中心重启服务的时候,客户端再连接时候会触发该信号
    connect(manager,&BridgeClientManager::evt_client_disconnected,this,&RemoteUITaskScheduler::on_client_disconnected,Qt::QueuedConnection);
    //网络出错信息
    connect(manager,&BridgeClientManager::evt_net_error,this,&RemoteUITaskScheduler::on_net_error,Qt::QueuedConnection);

    //往服务端写入数据
    connect(this,SIGNAL(evt_write(QByteArray)),manager,SLOT(on_write(QByteArray)));
    //从服务端读取数据
    connect(manager,&BridgeClientManager::evt_read,this,&RemoteUITaskScheduler::on_read,Qt::QueuedConnection);

    //客户发送数据块信息
    connect(manager,&BridgeClientManager::evt_client_trasferred,this,&RemoteUITaskScheduler::on_client_trasferred,Qt::QueuedConnection);


    ////过滤器参数
    //阻塞接收客户请求
    connect(this,&RemoteUITaskScheduler::evt_read,filter,&Filter::on_read,Qt::DirectConnection);
    //异步接收响应并发出
    connect(filter,&Filter::evt_write,this,&RemoteUITaskScheduler::on_write,Qt::DirectConnection);
    //阻塞重定向到其它业务
    connect(filter,&Filter::evt_redirect,this,&RemoteUITaskScheduler::on_redirect,Qt::DirectConnection);

    ////任务定时组
    //当调度器发出停止计时信号,停止计时服务   该evt_stopTimer信号暂时没有添加
    connect(manager,&BridgeClientManager::evt_client_disconnected,timer,&TimerController::on_stop);
    //计数端给调度器发出要同步客户端信号
    connect(timer,&TimerController::evt_notice_sync_socks,this,&RemoteUITaskScheduler::on_notice_sync_socks,Qt::DirectConnection);
    //调度器发送最新客户端信息到计数器
    connect(this,&RemoteUITaskScheduler::evt_sync_socks,timer,&TimerController::on_sync_socks,Qt::DirectConnection);
    //计时发送数据给调度器,通过调度器发送数据到客户端列表
    connect(timer,&RUTimerController::evt_write,this,&RemoteUITaskScheduler::on_take_write,Qt::DirectConnection);
    //发送网络出错到定时计数控制
    connect(this,&RemoteUITaskScheduler::evt_RemoteHostClosed,timer,&TimerController::on_RemoteHostClosed,Qt::QueuedConnection);


    ////跟踪消息队列变化
    UpCloudDuplexFactory &duplex = UpCloudDuplexFactory::getInstance();
    connect(&duplex,&UpCloudDuplexFactory::evt_send,this,&RemoteUITaskScheduler::on_take_write,Qt::QueuedConnection);
    //消息发送器给调度器发出要同步客户端信号
    connect(&duplex,&UpCloudDuplexFactory::evt_notice_sync_socks,this,&RemoteUITaskScheduler::on_notice_sync_socks,Qt::DirectConnection);
    //调度器发送最新客户端信息到消息发送器
    connect(this,&RemoteUITaskScheduler::evt_sync_socks,&duplex,&UpCloudDuplexFactory::evt_sync_socks,Qt::DirectConnection);
    connect(this,&RemoteUITaskScheduler::evt_receive_duplex,&duplex,&UpCloudDuplexFactory::on_receive_duplex,Qt::DirectConnection);
    //当绑定端口成功开启定时服务
    m_server.insert(sock,UUID);

    timer->on_start();

    //长连接建立成功通知UI加载页面
    emit
    evt_connectToServerSuccess();
}

//网络断开后重连接
void RemoteUITaskScheduler::on_client_disconnected(QTcpSocket *sock)
{
    m_server.remove(sock);
    //通知执行器网络连接断开
    emit
    evt_RemoteHostClosed(sock);

    qDebug() << trs("与中心服务的连接已经断开,准备重新请求服务建立连接");
    QThread::sleep(sockmeta->getInterval());
    emit
    evt_connectToServer();
}
//网络错误处理
void RemoteUITaskScheduler::on_net_error(QTcpSocket *sock, QAbstractSocket::SocketError err)
{
    if (sock)
    {
        if(sock->error()==QAbstractSocket::ConnectionRefusedError)
        {
            qDebug() << trs("连接被服务端拒绝,准备重新请求服务建立连接");
            QThread::sleep(sockmeta->getInterval());
            emit
            evt_connectToServer();
        }
        //当中心停止服务的时候
        else if(sock->error() == QAbstractSocket::RemoteHostClosedError)
        {
            m_server.remove(sock);
            //通知执行器网络连接断开
            emit
            evt_RemoteHostClosed(sock);
            qDebug() << trs("远程服务已经关闭,准备重新请求服务建立连接");
            QThread::sleep(sockmeta->getInterval());
            emit
            evt_connectToServer();
        }
        else
        {
            m_server.remove(sock);
            //通知执行器网络连接断开
            emit
            evt_RemoteHostClosed(sock);
            qDebug() << trs("网络传输出错%1:%2").arg(err).arg(sock->errorString());
            QThread::sleep(sockmeta->getInterval());
            emit
            evt_connectToServer();
        }
    }
}

//向服务发送数据
void RemoteUITaskScheduler::on_write(QTcpSocket * client,const QByteArray &data)
{
    Q_UNUSED(client);
    emit
    evt_write(data);
}

//从服务端接收数据报文
void RemoteUITaskScheduler::on_read(DataGramInfo* gram)
{
    QTcpSocket *obj = m_server.firstKey();
    quint64 client_key = m_server.first();
    emit
    evt_read(obj,QString::number(client_key),gram);
    //读取到报文,判断报文类型,找到该报文类型入库继续做操作,还是在这里发射返回反馈到服务器
}

//如果为中心返回远程UI请求数据
void RemoteUITaskScheduler::on_redirect(RequestContext *request, ResponseContext *response)
{
    //目前需要处理操作来的报文
    //如果为中心返回远程UI请求数据
    if(response->getMsgType() == Environment::Datagram::UI_Ctrl::RESPREMOTEUIOPERACENTORINFO)
    {
        //MessageInfo *RespRemoteUIOperaCentorInfo = response->getMsgInfo();
        emit
        evt_receive_duplex(request,response);
    }
}


void RemoteUITaskScheduler::on_take_write(QObject *socks, const QByteArray &datas)
{
    emit
    evt_write(datas);
}

void RemoteUITaskScheduler::on_notice_sync_socks()
{
    emit
    evt_sync_socks(m_server);
}



//客户Send数据块结构的大小
void RemoteUITaskScheduler::on_client_trasferred(QTcpSocket *pSock, qint64 dtw)
{
    //        qDebug() << trs("客户Send数据块结构的大小:%1").arg(dtw);
}




void RemoteUITaskScheduler::readConf()
{
    QString hostname = "";
    //请求服务端口
    quint16 port = 0;
    //请求建立连接超时时间
    quint32 timeout = 0;
    //设置连接重新多长时间后请求连接
    quint32 interval = 0;
    //网络传输块的大小
    quint32 transBlockSize = 0;
    //发送数据超时时间
    quint32 writeTimeout = 0;
    //读取数据超时时间
    quint32 readTimeout = 0;

    ClientConf cliconf;
    cliconf.getLocalhost(hostname);
    cliconf.getMainPort(port);
    cliconf.getMainTimeout(timeout);
    cliconf.getMainInterval(interval);
    cliconf.getMainBlockSize(transBlockSize);
    cliconf.getMainWriteTimeout(writeTimeout);
    cliconf.getMainReadTimeout(readTimeout);

    //启动应用时,如果块的大小不合法,直接停止应用
    if (port<1024 || port>=32768 )
        throw trs("监听服务端口必须在1024到32768之间,现在端口%1").arg(port);
    if (interval<1)
        throw trs("设置连接服务失败多长时间继续请求连接,现在%1").arg(interval);
    if (timeout<1000)
        throw trs("连接服务超时时间必须至少1000,现在%1").arg(timeout);
    if (transBlockSize<10 || transBlockSize>16*1024*1024 )
        throw trs("发送数据块大小必须在10到16*1024*1024之间,现在%1").arg(transBlockSize);
    if (writeTimeout<1000)
        throw trs("发送数据超时时间至少1000ms,现在%1").arg(writeTimeout);
    if (readTimeout<1000)
        throw trs("接收数据超时时间至少1000ms,现在%1").arg(readTimeout);
    //    assert(timeout>=1000 && interval>=0 && transBlockSize>=10 && transBlockSize<=16*1024*1024 && writeTimeout>0 && readTimeout>0);
    SocketMeta::Builder *builder = new SocketMeta::Builder;
    sockmeta = (SocketMeta *)builder->setHostname(hostname)
            ->setPort(port)
            ->setProtocol(SocketMeta::Protocol::TCP)
            ->setTimeout(timeout)
            ->setInterval(interval)
            ->setBlockSize(transBlockSize)
            ->setWriteTimeout(writeTimeout)
            ->setReadTimeout(readTimeout)
            ->build();
}
