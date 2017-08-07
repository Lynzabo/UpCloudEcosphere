#include "nsexector.h"

using namespace Environment::Task_Status::Noder::Stru;
using namespace Environment::Datagram::Stru_Data_Trans;
using namespace Environment::Task_Status::Noder;

NoderStructExector::NoderStructExector()
{
    //初始化任务集下载出错文件
    qDeleteAll(m_mapTaskUUIDErrorFiles);
    m_mapTaskUUIDErrorFiles.clear();
    m_centerSocks.clear();

    sfeMutex = new QMutex;
    endMutex = new QMutex;
    errMutex = new QMutex;
}

NoderStructExector::~NoderStructExector()
{
    //释放任务集下载出错文件
    qDeleteAll(m_mapTaskUUIDErrorFiles);
    m_mapTaskUUIDErrorFiles.clear();
    m_centerSocks.clear();

    delete sfeMutex;
    delete endMutex;
    delete errMutex;
}

void NoderStructExector::doExecute(QMap<QTcpSocket *, QString> &m_socks, PushContext *context)
{
    try
    {
        m_centerSocks = m_socks;
        m_pushContext = context;
        ////扫描结构化任务表,查找所有可用任务
        QString curTime;
        TimerUtil::toString(curTime);
        QList<NsRStructTask> usableStructTasks = NsStructDao::dirRTaskByStatus(Task_State::USABLE,curTime);
        ////可用任务列表是否不为空
        if(usableStructTasks.size() <= 0)
            return;
        ////遍历可用任务列表
        ////修改当前任务状态为“正在下载”
        QString taskUUID = "";
        for(NsRStructTask task : usableStructTasks)
        {
            taskUUID = task.getUuid();
            NsStructDao::updateRTaskState(taskUUID,Task_State::DOWNING);
        }
        for(NsRStructTask task : usableStructTasks)
        {
            ////获取该任务的所有文件存放到队列中
            taskUUID = task.getUuid();

            //构建FTP下载器,存放到任务FTP下载器集
            FtpMeta::Builder* builder = new FtpMeta::Builder;
            FtpMeta *m_meta = (FtpMeta *)builder->setHostname(QString("10.0.0.111"))
                    ->setPort(21)
                    ->setUsername(QString("dudu"))
                    ->setPassword(QString("dudu"))->build();
            FTPClientPool* ftpPool = new FTPClientPool(m_meta,taskUUID);
            connect(ftpPool,&FTPClientPool::subFileEnd,this,&NoderStructExector::on_TransSubFileEnd,Qt::DirectConnection);
            connect(ftpPool, &FTPClientPool::end, this, &NoderStructExector::on_TransEnd,Qt::DirectConnection);
            connect(ftpPool,&FTPClientPool::error,this,&NoderStructExector::on_TransError,Qt::DirectConnection);
            //构建HTTP下载器,存放到任务HTTP下载器集
            HttpCientPool* httpPool = new HttpCientPool(taskUUID);
            connect(httpPool,&HttpCientPool::subFileEnd,this,&NoderStructExector::on_TransSubFileEnd,Qt::DirectConnection);
            connect(httpPool, &HttpCientPool::end, this, &NoderStructExector::on_TransEnd,Qt::DirectConnection);
            connect(httpPool,&HttpCientPool::error,this,&NoderStructExector::on_TransError,Qt::DirectConnection);

            //存放任务下载出错信息
            QMap<QString,QString> *taskErrorFiles = new QMap<QString,QString>;
            m_mapTaskUUIDErrorFiles.insert(taskUUID,taskErrorFiles);

            QList<NsRStructSendFiles> sendFiles = NsStructDao::dirRSendFilesByTaskUUID(taskUUID,SendFiles_State::USABLE);
            if(sendFiles.size() == 0)
                on_TransEnd(taskUUID);
            ////使用HTTP/FTP下载器下载任务文件列表，根据实际下载情况修改任务状态和文件下载状态，调用下载策略反馈中心下载情况
            QMap<QString, QString> ftpDownGroups;
            QMap<QString, QString> httpDownGroups;
            //文件下载URL
            QString fileUrl = "";
            //保存位置
            QString destAbst = "";
            for(NsRStructSendFiles sendFile : sendFiles)
            {
                fileUrl.clear();
                destAbst.clear();
                fileUrl = sendFile.getFileUrl();
                destAbst = sendFile.getFileAbst();

                if(fileUrl.startsWith("ftp://", Qt::CaseInsensitive))
                {
                    //如果文件已经存在
                    if(QFileInfo::exists(destAbst))
                        NsStructDao::updateRSendFilesStateByUrlAbst(taskUUID, fileUrl, destAbst, SendFiles_State::DOWNCOMPLETE);
                    else
                        ftpDownGroups.insert(fileUrl, destAbst);
                }
                else if(fileUrl.startsWith("http://", Qt::CaseInsensitive))
                {
                    //如果文件已经存在
                    if(QFileInfo::exists(destAbst))
                        NsStructDao::updateRSendFilesStateByUrlAbst(taskUUID, fileUrl, destAbst, SendFiles_State::DOWNCOMPLETE);
                    else
                        httpDownGroups.insert(fileUrl, destAbst);
                }
            }
            ////下载一组文件
            if(ftpDownGroups.size() > 0)
            {
                QEventLoop loop;
                connect(this, SIGNAL(endLoop()), &loop, SLOT(quit()));
                ftpPool->download(ftpDownGroups,true,true);
                loop.exec(QEventLoop::ExcludeUserInputEvents);
            }
            else if(httpDownGroups.size() > 0)
            {
                QEventLoop loop;
                connect(this, SIGNAL(endLoop()), &loop, SLOT(quit()));
                httpPool->download(httpDownGroups,true,true);
                loop.exec(QEventLoop::ExcludeUserInputEvents);
            }
        }
    }catch(DBException &excep)
    {
        qDebug() << trs("Error:%1,%2,%3").arg(excep.getType()).arg(excep.getTypeDesc()).arg(excep.getText());
    }
}

void NoderStructExector::on_RemoteHostClosed(const QString &clientUUID)
{
    //TODO修改任务状态
}

void NoderStructExector::on_TransEnd(const QString &taskID)
{
    endMutex->lock();
    QString taskUUID = taskID;
    QMap<QString,QString> *taskErrorFiles = m_mapTaskUUIDErrorFiles.value(taskUUID);

    NsRStructTask task = NsStructDao::getRTaskByUUID(taskUUID);
    quint16 strategy = task.getStrategy();
    //查看是否下载完所有文件,如果未下载完,不作后续操作
    bool isDownCompletected = NsStructDao::getRTaskDownloadStatus(taskUUID,SendFiles_State::USABLE);
    if(isDownCompletected == false)
    {
        endMutex->unlock();
        return;
    }
    //结束文件下载事件循环
    emit
        endLoop();
    ////当下载完所有文件(包括对所有文件处理完成)，根据执行策略，修改任务状态为“下载完成”或“下载出错”
    //添加下载策略默认值
    if(strategy == 0)
        strategy = Stru_Exec_Strategy::ES_2;
    ////拼装反馈下载状态报文
    ReqUnstructFilesDownloadStatus* reqEntity = new ReqUnstructFilesDownloadStatus;
    reqEntity->TaskUUID = task.getTaskNum();
    reqEntity->Strategy = strategy;
    // TODO    下载策略和该执行器业务处理不是很匹配
    //策略判断
    //策略2:有文件出错，继续下载，并反馈出错文件
    if(strategy == Unstru_Down_Strategy::DS_2)
    {
        //如果存在出错文件,修改任务状态为失败,发送出错回执报文
        if(taskErrorFiles->size() > 0)
        {
            //准备反馈出错报文实体
            reqEntity->State =  Unstru::Task_State::ERROR;
            //拼装出错文件信息
            ErrorInfo* errorinfo = new ErrorInfo;
            QVector<Error*> Errors;
            QMap<QString,QString>::iterator errIndex;
            for (errIndex = taskErrorFiles->begin(); errIndex != taskErrorFiles->end(); ++errIndex)
            {
                Error* error = new Error;
                error->DownloadURLs = errIndex.key();
                error->ErrorMsg = errIndex.value();
                Errors.append(error);
            }
            errorinfo->Errors = Errors;
            reqEntity->errorinfo = errorinfo;

            NsUnstructDao::updateRTaskState(taskUUID,Task_State::DOWNERROR);
            //发送出错回执报文
            goto sendDatagram;
        }
        else
        {
            //准备反馈成功报文实体
            reqEntity->State =  Unstru::Task_State::DOWNSUCCESS;
            NsUnstructDao::updateRTaskState(taskUUID,Task_State::DOWNCOMPLETE);
            //发送下载成功回执报文
            goto sendDatagram;
        }
    }
    sendDatagram:
    ////下发报文
    QList<QString> socks= m_centerSocks.values();
    if(socks.size()==1)
    {
        QString serverUUID = socks.at(0);
        QVector<QString*> server;
        server.append(&serverUUID);
        m_pushContext->setSocks(server);
        m_pushContext->setMessage(reqEntity);
        emit
            evt_write(m_pushContext);
    }
    //清理缓存任务数据
    m_mapTaskUUIDErrorFiles.remove(taskUUID);
    endMutex->unlock();
}


void NoderStructExector::on_TransSubFileEnd(const QString &taskID, const QString &fileUrl, const QString &destAbst)
{
    sfeMutex->lock();
    QString taskUUID = taskID;
    try
    {
        NsStructDao::updateRSendFilesStateByUrlAbst(taskUUID, fileUrl, destAbst, SendFiles_State::DOWNCOMPLETE);
    }
    catch(DBException &excep)
    {
        qDebug() << trs("Error:%1,%2,%3").arg(excep.getType()).arg(excep.getTypeDesc()).arg(excep.getText());
    }
    sfeMutex->unlock();
}

void NoderStructExector::on_TransError(const QString &taskID, const QString &src, const QString &errMsg)
{
    errMutex->lock();
    QString taskUUID = taskID;
    //往当前任务出错文件集合中添加当前出错信息
    m_mapTaskUUIDErrorFiles.value(taskUUID)->insert(src,errMsg);

    QString fileUrl = src;
    try
    {
        NsStructDao::updateRSendFilesState(taskUUID, fileUrl, SendFiles_State::ERROR,errMsg);
    }
    catch(DBException &excep)
    {
        qDebug() << trs("Error:%1,%2,%3").arg(excep.getType()).arg(excep.getTypeDesc()).arg(excep.getText());
    }
    errMutex->unlock();
}
