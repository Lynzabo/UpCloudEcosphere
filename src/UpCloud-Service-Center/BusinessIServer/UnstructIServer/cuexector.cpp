#include "cuexector.h"
using namespace Environment::Task_Status::Center::Unstru;

QMutex CenterUnstructExector::mutex;
CenterUnstructExector::CenterUnstructExector()
{

}

void CenterUnstructExector::doExecute(QMap<QTcpSocket *, quint64> &socks, PushContext *context)
{
    mutex.lock();
    qDebug() << trs("Unstruct send exector ready to work");
    try
    {
        ////扫描非结构化任务表,查找所有非结构化任务
        QString curTime;
        TimerUtil::toString(curTime);

        QList<CsRUnstructTask> usableUnstructTasks = CSUnstructDao::dirRTask(Task_State::USABLE,curTime);
        ////可用任务列表是否不为空
        if(usableUnstructTasks.size() <= 0)
        {
//            qDebug() << trs("Unstruct send exector exit,task is null");
            mutex.unlock();
            return;
        }
        ////遍历可用任务列表
        for(CsRUnstructTask task : usableUnstructTasks)
        {
            //获取非结构化任务UUID
            QString currentTaskUUID = task.getUuid();

            ////查找任务下发地址表当前任务所有下发节点 服务器列表,文件列表
            QList<CsRUnstructSendAddr> addrEntrys;
            QList<CsRUnstructSendFiles> sendFiles;
            CSUnstructDao::dirRSendAddrsAndFilseByTaskUUID(currentTaskUUID,
                                                           SendStatus_State::USABLE,
                                                           addrEntrys, sendFiles);
            ////修改当前任务状态为“准备下发”
            CSUnstructDao::updateRTaskState(currentTaskUUID,Task_State::PRESEND);
            ////修改下发状态为“准备下发”
            CSUnstructDao::updateSendStatus(currentTaskUUID,
                                            Task_State::USABLE,
                                            SendStatus_State::PRESEND,
                                            QString());
            ////如果节点服务器UUID列表不为空
            if(addrEntrys.size() <= 0)
            {
                ////修改任务状态为“目标地址为空”
                CSUnstructDao::updateRTaskState(currentTaskUUID,Task_State::ADDRISNULL);
                break;
            }
            else
            {
                ////获取在线客户端UUID列表
                QList<quint64> onlineClientUUIDS = socks.values();
                ////在线客户端列表是否不为空
                if(onlineClientUUIDS.size() <= 0)
                {
                    ////修改任务表任务状态为“下发出错”,修改任务下发地址状态为“下发出错”,错误描述为网络断开

                    QString statusError = trs("网络断开");
                    ////修改当前任务任务状态为“下发出错”
                    CSUnstructDao::updateRTaskState(currentTaskUUID,Task_State::SENDERROR);
                    CSUnstructDao::updateSendStatus(currentTaskUUID,
                                                    SendStatus_State::PRESEND,
                                                    SendStatus_State::SENDERROR,
                                                    statusError);
                }
                else
                {
                    ////遍历下发节点服务器列表，创建空的下发节点服务器列表缓存
                    QVector<quint64> sendAddrs;
                    sendAddrs.clear();
                    quint64 clientUUID = 0;
                    for(CsRUnstructSendAddr addr : addrEntrys)
                    {
                        clientUUID = addr.getClientUuid().toLongLong();
                        ////如果当前节点服务器在线
                        if(!onlineClientUUIDS.contains(clientUUID))
                        {
                            ////当前节点服务器不在线，修改当前任务当前节点服务器状态为“下发出错”，错误描述为网络断开；修改任务状态为“下发出错”，并不允许以后再次修改
                            QString clientError = trs("网络断开");
                            CSUnstructDao::updateSendStatusByAddr(currentTaskUUID,
                                                                SendStatus_State::PRESEND,
                                                                SendStatus_State::SENDERROR,
                                                                clientError,
                                                                QString::number(clientUUID));

                        }
                        else
                        {
                            ////添加该节点服务器UUID到下发节点服务器列表缓存中
                            sendAddrs.append(clientUUID);
                        }
                    }
                    ////拼装报文
                    ReqUnstructFilesDownloadInfo *info = new ReqUnstructFilesDownloadInfo;
                    m_infoList.append(info);
                    //计划任务编号
                    info->TaskUUID = task.getTaskNum();
                    //操作类型码
                    info->TaskExecType = Environment::Datagram::Unstru_Data_Trans::Add;
                    //操作策略
                    info->Strategy = task.getStrategy();
                    //FtpPush & HttpPush
                    QVector<FileDownload*> vectorFTP;
                    QVector<FileDownload*> vectorHTTP;
                    for(CsRUnstructSendFiles files : sendFiles)
                    {
                        FileDownload *fileInfo = new FileDownload;
                        fileInfo->DownloadURLs = files.getDownUrl();
                        fileInfo->DescPath = QString("%1/%2").arg(files.getSaveAbst()).arg(files.getFileDestName());
                        if(fileInfo->DownloadURLs.startsWith(QString("http://")))
                            vectorHTTP.append(fileInfo);
                        else if(fileInfo->DownloadURLs.startsWith(QString("ftp://")))
                            vectorFTP.append(fileInfo);
                    }
                    if(vectorFTP.size() > 0 )
                    {
                        //FTP元数据
                        info->ftpPush->IP = QString("10.10.10.104");
                        info->ftpPush->Port = 21;
                        info->ftpPush->Username = QString("user01");
                        info->ftpPush->Password = QString("pwd01");

                        info->ftpPush->FilesDownloadURLs = vectorFTP;
                    }
                    if(vectorHTTP.size() > 0)
                        info->httpPush->FilesDownloadURLs = vectorHTTP;
                    ////修改当前任务节点列表缓存中所有节点状态为"准备下发"的状态为“正在下发”，当任务状态不为“下发出错”时，修改任务状态为“正在下发”
                    QString clientError = trs("");

                    ////修改当前任务状态为“正在下发”
                    CSUnstructDao::updateRTaskState(currentTaskUUID,Task_State::SENDING);
                    ////修改下发状态为“正在下发”
                    CSUnstructDao::updateSendStatus(currentTaskUUID,Task_State::PRESEND, SendStatus_State::SENDING, clientError);

                    ////下发报文
                    context->setSocks(sendAddrs);
                    context->setMessage(info);
                    qDebug() << trs("下发非结构化任务");
                    emit
                    evt_write(context);
                }
            }
        }

    }catch(DBException &excep)
    {
        qDebug() << trs("Error:%1,%2,%3").arg(excep.getType()).arg(excep.getTypeDesc()).arg(excep.getText());
    }
    qDebug() << trs("Unstruct send exector download complete");
    mutex.unlock();
}

void CenterUnstructExector::doSetArgs(QMap<QTcpSocket *, quint64> &socks)
{
    m_socks = socks;
}

void CenterUnstructExector::doExecute()
{
    qDebug() << "CenterUnstructExector::doExecute()" << QThread::currentThreadId();
    PushContext* contex = new PushContext;
    this->doExecute(m_socks, contex);
}

void CenterUnstructExector::on_RemoteHostClosed(const quint64 &clientUUID)
{
    //TODO修改任务状态
}


