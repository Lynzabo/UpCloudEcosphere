#include "cstructexector.h"
using namespace Environment::Task_Status::Center::Stru;
#include <bitset>
CenterStructExector::CenterStructExector()
{

}

void CenterStructExector::doExecute(QMap<QTcpSocket *, QString> &m_socks, PushContext *context)
{
    try
    {
        ////扫描结构化任务表,查找所有结构化任务
        QString curTime;
        TimerUtil::toString(curTime);

        QList<CsRStructTask> usableStructTasks = CSStructDao::dirRTask(Task_State::USABLE,curTime);
        ////可用任务列表是否不为空
        if(usableStructTasks.size() <= 0)
            return;
        ////遍历可用任务列表
        for(CsRStructTask task : usableStructTasks)
        {
            //获取结构化任务UUID
            QString currentTaskUUID = task.getUuid();
            ////修改当前任务状态为“准备下发”
            CSStructDao::updateRTaskState(currentTaskUUID,Task_State::PRESEND);
            ////查找任务下发地址表当前任务所有下发节点服务器UUID列表
            QList<CsRStructSendAddr> addrEntrys = CSStructDao::dirRSendAddrsByTaskUUID(currentTaskUUID);
            ////如果节点服务器UUID列表不为空
            if(addrEntrys.size() <= 0)
            {
                ////修改任务状态为“目标地址为空”
                CSStructDao::updateRTaskState(currentTaskUUID,Task_State::ADDRISNULL);
                break;
            }
            else
            {
                ////获取在线客户端UUID列表
                QList<QString> onlineClientUUIDS = m_socks.values();
                ////在线客户端列表是否不为空
                if(onlineClientUUIDS.size() <= 0)
                {
                    ////修改任务表任务状态为“下发出错”,修改任务下发地址状态为“下发出错”,错误描述为网络断开
                    QString clientError = trs("网络断开");
                    CSStructDao::updateRTaskAndAllSendAddrStatus(currentTaskUUID,Task_State::ERROR, SendAddr_State::SENDERROR, clientError);
                }
                else
                {
                    ////遍历下发节点服务器列表，创建空的下发节点服务器列表缓存
                    QVector<QString *> sendAddrs;
                    sendAddrs.clear();
                    QString *clientUUID = NULL;
                    for(CsRStructSendAddr addr : addrEntrys)
                    {
                        clientUUID = new QString;
                        *clientUUID = addr.getClientUuid();
                        ////如果当前节点服务器在线
                        if(!onlineClientUUIDS.contains(*clientUUID))
                        {
                            ////当前节点服务器不在线，修改当前任务当前节点服务器状态为“下发出错”，错误描述为网络断开；修改任务状态为“下发出错”，并不允许以后再次修改
                            QString clientError = trs("网络断开");
                            CSStructDao::updateRTaskAndSendAddrStatus(currentTaskUUID,Task_State::ERROR, *clientUUID, SendAddr_State::SENDERROR, clientError);
                            delete clientUUID;
                        }
                        else
                        {
                            ////添加该节点服务器UUID到下发节点服务器列表缓存中
                            sendAddrs.append(clientUUID);
                            //修改当前任务当前节点服务器状态为“准备下发”
                            QString clientError = trs("");
                            CSStructDao::updateRSendAddrByTaskUUID(currentTaskUUID, *clientUUID, SendAddr_State::PRESEND, clientError);
                        }                        
                    }
                    ////查找下发文件列表并拼装结构化报文
                    QList<CsRStructSendFiles> sendFiles = CSStructDao::dirRSendFilesByTaskUUID(currentTaskUUID);
                    ////拼装报文
                    ReqStructFilesDownloadInfo *info = new ReqStructFilesDownloadInfo;
                    //计划任务编号
                    info->TaskUUID = task.getTaskNum();
                    //操作类型码
                    info->TaskExecType = Environment::Datagram::Stru_Data_Trans::Stru_Operate::Add;
                    //操作策略
                    info->Strategy = task.getStrategy();
                    //执行时刻
                    info->setExecTime(task.getExecTime());
                    //FtpPush & HttpPush
                    QVector<FileDownload*> vectorFTP;
                    QVector<FileDownload*> vectorHTTP;
                    for(CsRStructSendFiles &files : sendFiles)
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
                    CSStructDao::updateRTaskAndAllSendAddr(currentTaskUUID,Task_State::SENDING,Task_State::ERROR,QString("<>"),
                                                      SendAddr_State::SENDING, SendAddr_State::PRESEND,QString("="), clientError);
                    ////下发报文
                    context->setSocks(sendAddrs);
                    context->setMessage(info);
                    qDebug() << trs("下发结构化任务 ");
                    emit
                    evt_write(context);
                }
            }
        }

    }catch(DBException &excep)
    {
        qDebug() << trs("Error:%1,%2,%3").arg(excep.getType()).arg(excep.getTypeDesc()).arg(excep.getText());
    }
}

void CenterStructExector::on_RemoteHostClosed(const QString &clientUUID)
{
    //TODO修改任务状态

}

