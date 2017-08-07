#include "clienttaskscheduler.h"
#include "clientconf.h"
using namespace Environment::Net_Conn_State;
ClientTaskScheduler::ClientTaskScheduler(QObject *parent) : QObject(parent)
{
    //任务定时器
    timer = new NSTimerController;
    //任务过滤器
    filter = new TaskSchedulerFilter;
    m_server.clear();
    readConf();
    manager = new BridgeClientManager(this,sockmeta);
    //连接服务
    connect(this,SIGNAL(evt_connectToServer()),this,SLOT(on_connectToServer()));
    connect(manager, SIGNAL(evt_bridgeConnSuccess(QTcpSocket*,quint64)), this, SLOT(on_bridgeConnSuccess(QTcpSocket*,quint64)));
}
void ClientTaskScheduler::on_take_write(QObject *socks, const QByteArray &datas)
{
    emit
    evt_write(datas);
}
void ClientTaskScheduler::on_notice_sync_socks()
{
    emit
    evt_sync_socks(m_server);
}

void ClientTaskScheduler::on_bridgeConnSuccess(QTcpSocket * socket, quint64 UUID)
{
    //连接服务断开,当中心重启服务的时候,客户端再连接时候会触发该信号
    connect(manager,&BridgeClientManager::evt_client_disconnected,this,&ClientTaskScheduler::on_client_disconnected,Qt::QueuedConnection);
    //往服务端写入数据
    //connect(this,&ClientTaskScheduler::evt_write,manager,&BridgeClientManager::on_write,Qt::QueuedConnection);
    //connect(this,SIGNAL(evt_write(QByteArray)),manager,SLOT(on_write(QByteArray)));
    connect(this,SIGNAL(evt_write(QByteArray)),manager,SLOT(on_write(QByteArray)),Qt::QueuedConnection);
    //从服务端读取数据
    connect(manager,&BridgeClientManager::evt_read,this,&ClientTaskScheduler::on_read,Qt::QueuedConnection);
    //网络出错信息
    connect(manager,&BridgeClientManager::evt_net_error,this,&ClientTaskScheduler::on_net_error,Qt::QueuedConnection);
    //客户发送数据块信息
    connect(manager,&BridgeClientManager::evt_client_trasferred,this,&ClientTaskScheduler::on_client_trasferred,Qt::QueuedConnection);
    //过滤器参数
    //阻塞接收客户请求
    connect(this,&ClientTaskScheduler::evt_read,filter,&Filter::on_read,Qt::DirectConnection);
    //异步接收响应并发出
    connect(filter,&Filter::evt_write,this,&ClientTaskScheduler::on_write,Qt::DirectConnection);

    //任务定时组

    //当调度器发出停止计时信号,停止计时服务   该evt_stopTimer信号暂时没有添加
    connect(manager,&BridgeClientManager::evt_client_disconnected,timer,&TimerController::on_stop);
    //计数端给调度器发出要同步客户端信号
    connect(timer,&TimerController::evt_notice_sync_socks,this,&ClientTaskScheduler::on_notice_sync_socks,Qt::DirectConnection);
    //调度器发送最新客户端信息到计数器
    connect(this,&ClientTaskScheduler::evt_sync_socks,timer,&TimerController::on_sync_socks,Qt::DirectConnection);
    //计时发送数据给调度器,通过调度器发送数据到客户端列表
    connect(timer,&NSTimerController::evt_write,this,&ClientTaskScheduler::on_take_write,Qt::QueuedConnection);
    //    connect(timer,SIGNAL(evt_write(QVector<QObject*>,QByteArray)),this,SIGNAL(on_take_write(QVector<QObject*>,QByteArray)));
    //发送网络出错到定时计数控制
    connect(this,&ClientTaskScheduler::evt_RemoteHostClosed,timer,&TimerController::on_RemoteHostClosed,Qt::QueuedConnection);

    //当绑定端口成功开启定时服务
    m_server.insert(socket,UUID);
    timer->on_start();
}
void ClientTaskScheduler::on_write(QTcpSocket * client,const QByteArray &data)
{
    emit
    evt_write(data);
}
ClientTaskScheduler::~ClientTaskScheduler()
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
    //会自动删除QTcpSocket
    this->m_server.clear();
    if(sockmeta != NULL)
    {
        delete sockmeta;
        sockmeta = NULL;
    }
}

void ClientTaskScheduler::startup()
{
    qDebug() << trs("准备连接中心服务");
    emit
    evt_connectToServer();
}

void ClientTaskScheduler::on_read(DataGramInfo *gram)
{
    if(m_server.size() <= 0)
        return;
    QTcpSocket *obj = m_server.firstKey();
    m_server.first() = gram->UUID;
    quint64 client_key = m_server.first();
    //    qDebug() << trs("读取服务数据:")<<datas;
    qDebug() << trs("读取中心服务数据:")<<gram->message;
    if(gram)
    {
        emit
        evt_read(obj,QString::number(client_key),gram);
    }
    //读取到报文,判断报文类型,找到该报文类型入库继续做操作,还是在这里发射返回反馈到服务器
}

void ClientTaskScheduler::on_net_error(QTcpSocket * sock,QAbstractSocket::SocketError err)
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
            qDebug() << trs("网络传输出错%1:%2").arg(err).arg(sock->errorString());
            qDebug() << trs("准备重新请求服务建立连接");
            QThread::sleep(sockmeta->getInterval());
            emit
            evt_connectToServer();
        }
    }
}

void ClientTaskScheduler::on_client_trasferred(QTcpSocket *pSock, qint64 dtw)
{
    //    if(dtw>20)
    //        qDebug() << trs("客户Send数据块结构的大小:%1").arg(dtw);
}

void ClientTaskScheduler::on_connectToServer()
{
    manager->connectToServer();
}

void ClientTaskScheduler::on_client_disconnected(QTcpSocket * sock)
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


void ClientTaskScheduler::readConf()
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

