#include "nuexector.h"

using namespace Environment::Task_Status::Noder::Unstru;
using namespace Environment::Datagram::Unstru_Data_Trans;
using namespace Environment::Task_Status::Center;

QMutex NoderUnstructExector::mutex;
NoderUnstructExector::NoderUnstructExector()
{
    //初始化任务集下载出错文件
    qDeleteAll(m_mapTaskUUIDErrorFiles);
    m_mapTaskUUIDErrorFiles.clear();
    m_centerSocks.clear();

    sfeMutex = new QMutex;
    endMutex = new QMutex;
    errMutex = new QMutex;
}

NoderUnstructExector::~NoderUnstructExector()
{
    //释放任务集下载出错文件
    qDeleteAll(m_mapTaskUUIDErrorFiles);
    m_mapTaskUUIDErrorFiles.clear();
    m_centerSocks.clear();

    delete sfeMutex;
    delete endMutex;
    delete errMutex;
}

void NoderUnstructExector::doExecute(QMap<QTcpSocket *, quint64> &m_socks, PushContext *context)
{
    mutex.lock();
    qDebug() << trs("Unstruct download exector ready to work");
    try
    {
        m_centerSocks = m_socks;
        m_pushContext = context;
        ////扫描非结构化任务表,查找所有可用任务
        QString curTime;
        TimerUtil::toString(curTime);
        QList<NsRUnstructTask> usableUnstructTasks = NsUnstructDao::dirRTaskByStatus(Task_State::USABLE,curTime);
        ////可用任务列表是否不为空
        if(usableUnstructTasks.size() <= 0)
        {
//            qDebug() << trs("Unstruct download exector exit,task is null");
            mutex.unlock();
            return;
        }
        //从配置文件读取网络连接配置
        NetConf *netconf = new NetConf;
        //主机服务地址
        QString hostname;
        //主机服务端口
        qint16 port;
        //主机服务登录用户名
        QString username;
        //主机服务登录密码
        QString password;
        //ftp允许同时下载文件数
        int ftpIIsNum;
        //ftp下载单个文件启动线程数
        int ftpDownThreadsNum;
        //http允许同时下载文件数
        int httpIIsNum;
        //http下载单个文件启动线程数
        int httpDownThreadsNum;

        netconf->getFtpHostname(hostname);
        netconf->getFtpPort(port);
        netconf->getFtpUsername(username);
        netconf->getFtpPassword(password);
        netconf->getFtpIIsNum(ftpIIsNum);
        netconf->getFtpDownThreadsNum(ftpDownThreadsNum);
        netconf->getHttpIIsNum(httpIIsNum);
        netconf->getHttpDownThreadsNum(httpDownThreadsNum);
        delete netconf;
        ////遍历可用任务列表
        ////修改当前任务状态为“正在下载”
        QString taskUUID = "";
        for(NsRUnstructTask task : usableUnstructTasks)
        {
            taskUUID = task.getUuid();
            NsUnstructDao::updateRTaskState(taskUUID,Task_State::DOWNING);
        }
        for(NsRUnstructTask task : usableUnstructTasks)
        {
            ////获取该任务的所有文件存放到队列中
            taskUUID = task.getUuid();

            //构建FTP下载器,存放到任务FTP下载器集
            FtpMeta::Builder* builder = new FtpMeta::Builder;
            FtpMeta *m_meta = (FtpMeta *)builder->setHostname(QString(hostname))
                    ->setPort(port)
                    ->setUsername(QString(username))
                    ->setPassword(QString(password))->build();
            FTPClientPool* ftpPool = new FTPClientPool(m_meta,taskUUID);
            connect(ftpPool,&FTPClientPool::subFileEnd,this,&NoderUnstructExector::on_TransSubFileEnd,Qt::DirectConnection);
            connect(ftpPool, &FTPClientPool::end, this, &NoderUnstructExector::on_TransEnd,Qt::DirectConnection);
            connect(ftpPool,&FTPClientPool::error,this,&NoderUnstructExector::on_TransError,Qt::DirectConnection);
            //构建HTTP下载器,存放到任务HTTP下载器集
            HttpCientPool* httpPool = new HttpCientPool(taskUUID);
            connect(httpPool,&HttpCientPool::subFileEnd,this,&NoderUnstructExector::on_TransSubFileEnd,Qt::DirectConnection);
            connect(httpPool, &HttpCientPool::end, this, &NoderUnstructExector::on_TransEnd,Qt::DirectConnection);
            connect(httpPool,&HttpCientPool::error,this,&NoderUnstructExector::on_TransError,Qt::DirectConnection);

            //存放任务下载出错信息
            QMap<QString,QString> *taskErrorFiles = new QMap<QString,QString>;
            m_mapTaskUUIDErrorFiles.insert(taskUUID,taskErrorFiles);

            QList<NsRUnstructSendFiles> sendFiles = NsUnstructDao::dirRSendFilesByTaskUUID(taskUUID,SendFiles_State::USABLE);
            if(sendFiles.size() == 0)
                on_TransEnd(taskUUID);
            ////使用HTTP/FTP下载器下载任务文件列表，根据实际下载情况修改任务状态和文件下载状态，调用下载策略反馈中心下载情况
            QMap<QString, QString> ftpDownGroups;
            QMap<QString, QString> httpDownGroups;
            //文件下载URL
            QString fileUrl = "";
            //保存位置
            QString destAbst = "";
            for(NsRUnstructSendFiles sendFile : sendFiles)
            {
                fileUrl.clear();
                destAbst.clear();
                fileUrl = sendFile.getFileUrl();
                destAbst = sendFile.getFileAbst();

                //修改当前任务所对应的所有文件状态为“正在下载”
                NsUnstructDao::updateRSendFilesStateByUrlAbst(taskUUID, fileUrl, destAbst, SendFiles_State::DOWNING);

                if(fileUrl.startsWith("ftp://", Qt::CaseInsensitive))
                {
                    ftpDownGroups.insert(fileUrl, destAbst);
                }
                else if(fileUrl.startsWith("http://", Qt::CaseInsensitive))
                {
                    httpDownGroups.insert(fileUrl, destAbst);
                }
            }
            ////下载一组文件
            if(ftpDownGroups.size() > 0)
            {
                QEventLoop *loop = new QEventLoop;
                connect(this, SIGNAL(endLoop()), loop, SLOT(quit()));
                ftpPool->download(ftpDownGroups,true,true,ftpIIsNum,ftpDownThreadsNum);
                loop->exec(QEventLoop::ExcludeUserInputEvents);
                delete loop;
                loop = NULL;
            }
            else if(httpDownGroups.size() > 0)
            {
                QEventLoop *loop = new QEventLoop;
                connect(this, SIGNAL(endLoop()), loop, SLOT(quit()));
                httpPool->download(httpDownGroups,true,true,httpIIsNum,httpDownThreadsNum);
                loop->exec(QEventLoop::ExcludeUserInputEvents);
                delete loop;
                loop = NULL;
            }
        }
    }catch(DBException &excep)
    {
        qDebug() << trs("Error:%1,%2,%3").arg(excep.getType()).arg(excep.getTypeDesc()).arg(excep.getText());
    }
    qDebug() << trs("Unstruct download exector download complete");
    mutex.unlock();
}

void NoderUnstructExector::doSetArgs(QMap<QTcpSocket *, quint64> &socks)
{
    m_socks =socks;
}

void NoderUnstructExector::doExecute()
{
    PushContext *context = new PushContext;
    this->doExecute(m_socks, context);
}

void NoderUnstructExector::on_RemoteHostClosed(const QString &clientUUID)
{
    //TODO修改任务状态
}
void NoderUnstructExector::on_TransEnd(const QString &taskID)
{
    endMutex->lock();
    QString taskUUID = taskID;
    QMap<QString,QString> *taskErrorFiles = m_mapTaskUUIDErrorFiles.value(taskUUID);

    NsRUnstructTask task = NsUnstructDao::getRTaskByUUID(taskUUID);
    quint16 strategy = task.getStrategy();
    //查看是否下载完所有文件,如果未下载完,不作后续操作
    bool isDownCompletected = NsUnstructDao::getRTaskDownloadStatus(taskUUID,SendFiles_State::USABLE);
    if(isDownCompletected == false)
    {
        endMutex->unlock();
        return;
    }
    ////当下载完所有文件(包括对所有文件处理完成)，根据下载策略，修改任务状态为“下载完成”或“下载出错”
    // TODO 策略判断 下载策略和该执行器业务处理不是很匹配
    //添加下载策略默认值
    strategy = Unstru_Down_Strategy::DS_2;

    ////拼装反馈下载状态报文
    ReqUnstructFilesDownloadStatus* reqEntity = new ReqUnstructFilesDownloadStatus;
    reqEntity->TaskUUID = task.getTaskNum();
    reqEntity->Strategy = strategy;

    //如果存在出错文件,修改任务状态为失败,发送出错回执报文
    if(taskErrorFiles->size() > 0)
    {
        //准备反馈出错报文实体
        reqEntity->State =  Task_State::DOWNERROR;
        //拼装出错文件信息
        ResultInfo* errorinfo = new ResultInfo;
        QVector<Result*> Errors;
        QMap<QString,QString>::iterator errIndex;
        for (errIndex = taskErrorFiles->begin(); errIndex != taskErrorFiles->end(); ++errIndex)
        {
            Result* error = new Result;
            error->DownloadURLs = errIndex.key();
            error->backMsg = errIndex.value();
            Errors.append(error);
        }
        errorinfo->results = Errors;
        reqEntity->resultInfo = errorinfo;

        NsUnstructDao::updateRTaskState(taskUUID,Task_State::DOWNERROR);
    }
    else
    {
        //准备反馈成功报文实体
        reqEntity->State =  Task_State::DOWNSUCCESS;
        NsUnstructDao::updateRTaskState(taskUUID,Task_State::DOWNSUCCESS);
    }
    goto sendDatagram;
sendDatagram:
    ////下发报文
    QList<quint64> socks= m_centerSocks.values();
    if(socks.size()==1)
    {
        quint64 serverUUID = socks.at(0);
        QVector<quint64> server;
        server.append(serverUUID);
        m_pushContext->setSocks(server);
        m_pushContext->setMessage(reqEntity);
        emit
        evt_write(m_pushContext);
    }
    endMutex->unlock();
    //结束本次任务的事件循环
    emit
    endLoop();

}

void NoderUnstructExector::on_TransSubFileEnd(const QString &taskID,const QString &fileUrl,const QString &destAbst)
{
    sfeMutex->lock();
    QString taskUUID = taskID;
    try
    {
        NsUnstructDao::updateRSendFilesStateByUrlAbst(taskUUID, fileUrl, destAbst, SendFiles_State::DOWNSUCCESS);
    }
    catch(DBException &excep)
    {
        qDebug() << trs("Error:%1,%2,%3").arg(excep.getType()).arg(excep.getTypeDesc()).arg(excep.getText());
    }
    sfeMutex->unlock();
}


void NoderUnstructExector::on_TransError(const QString &taskID,const QString &src,const QString &errMsg)
{
    errMutex->lock();
    QString taskUUID = taskID;
    //往当前任务出错文件集合中添加当前出错信息
    m_mapTaskUUIDErrorFiles.value(taskUUID)->insert(src,errMsg);

    QString fileUrl = src;
    try
    {
        NsUnstructDao::updateRSendFilesState(taskUUID, fileUrl, SendFiles_State::DOWNERROR,errMsg);
    }
    catch(DBException &excep)
    {
        qDebug() << trs("Error:%1,%2,%3").arg(excep.getType()).arg(excep.getTypeDesc()).arg(excep.getText());
    }
    errMutex->unlock();
}


