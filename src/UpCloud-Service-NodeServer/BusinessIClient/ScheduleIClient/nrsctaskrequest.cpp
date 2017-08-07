#include "nrsctaskrequest.h"
#include "util/timerutil.h"
#include "util/uuidutil.h"
#include "baseiclient.h"
using namespace Environment::Datagram;
using namespace Environment::Task_Status::Noder::Sche;
QMutex * NoderRecScheduleTaskRequest::mutex = new QMutex;
NoderRecScheduleTaskRequest::NoderRecScheduleTaskRequest()
{

}

NoderRecScheduleTaskRequest::~NoderRecScheduleTaskRequest()
{
    delete gramEntity;
}

void NoderRecScheduleTaskRequest::doRequest(RequestContext *request, ResponseContext *response)
{
    mutex->lock();
    QString uuid;
    QString insertTime;
    QList<NsRScheduleSendFiles *> downFiles;
    QString saveAbst;
    QVector<FileDownload*> FilesDownloadURLs;
    QString downURL;
    QByteArray datagram;

    ////反序列化报文体到实体对象
    quint8 msgType = request->getMsgType();
    QString message = request->getMessage();
    //发送报文实体对象
    RespScheduleTaskDownloadInfo *respEntity = new RespScheduleTaskDownloadInfo;
    //任务实体
    NsRScheduleTask *nsRScheduleTask = new NsRScheduleTask;
    //解帧报文并生成报文实体
    try
    {
        gramEntity = DatagramUtil::getInstance().parseMessageText(CallbackByReqScheduleTask,msgType,message);
        respEntity->TaskUUID = gramEntity->TaskUUID;
    }
    catch(TransException &excep)
    {
        qDebug() << trs("反序列化报文体到实体对象:ErrorCode:%1,ErrorMsg:%2").arg(excep.getType()).arg(excep.getText());
        if(gramEntity->TaskUUID == 0)
        {
            delete respEntity;
            goto end;
        }
        else
        {
            respEntity->TaskUUID = gramEntity->TaskUUID;
            respEntity->State = excep.getType();
            goto sendDatagram;
        }
    }
    //解析执行时间是否为空
    if(gramEntity->ExecTime.isEmpty())
    {
        respEntity->State = Stru_Data_Trans::Resp_Info_State::_8;
        goto sendDatagram;
    }
    else
    {
        //解析执行时间是否合法
        QString descTime;
        try{
            TimerUtil::format(gramEntity->ExecTime, descTime);
        }
        catch(QString e)
        {
            Q_UNUSED(e);
            respEntity->State = Stru_Data_Trans::Resp_Info_State::_9;
            goto sendDatagram;
        }
    }
    //解析入口文件保存路径为空
    if(gramEntity->EntranceFile.isEmpty())
    {
        respEntity->State = Sche_Data_Trans::Resp_Info_State::_A;
        goto sendDatagram;
    }    
    ////解析文件下载路径是否合法
    qDeleteAll(FilesDownloadURLs);
    FilesDownloadURLs.clear();
    downURL = trs("");
    for(FileDownload* fileInfo : gramEntity->ftpPush->FilesDownloadURLs)
    {
        downURL = fileInfo->DownloadURLs;
        if(!QUrl(downURL).isValid())
        {
            respEntity->State = Sche_Data_Trans::Resp_Info_State::_B;
            goto sendDatagram;
        }
        else
        {
            FilesDownloadURLs.append(fileInfo);
        }
    }
    downURL.clear();
    for(FileDownload* fileInfo : gramEntity->httpPush->FilesDownloadURLs)
    {
        downURL = fileInfo->DownloadURLs;
        if(!QUrl(downURL).isValid())
        {
            respEntity->State = Sche_Data_Trans::Resp_Info_State::_B;
            goto sendDatagram;
        }
        else
        {
            FilesDownloadURLs.append(fileInfo);
        }
    }
    ////解析文件保存位置是否合法
    saveAbst = trs("");
    for(FileDownload* fileInfo : FilesDownloadURLs)
    {
        saveAbst = fileInfo->DescPath;
        if(!QUrl(saveAbst).isValid())
        {
            respEntity->State = Sche_Data_Trans::Resp_Info_State::_C;
            goto sendDatagram;
        }
    }
    ////保存结构化任务到数据库，置任务为“任务可用”

    UuidUtil::nextUUID(uuid);
    TimerUtil::toString(insertTime);

    nsRScheduleTask->setUuid(uuid);
    nsRScheduleTask->setTaskNum(gramEntity->TaskUUID);
    nsRScheduleTask->setStrategy(gramEntity->Strategy);
    nsRScheduleTask->setState(Task_State::USABLE);
    nsRScheduleTask->setExecTime(gramEntity->ExecTime);
    nsRScheduleTask->setSaveAbst(gramEntity->EntranceFile);
    nsRScheduleTask->setInsertTime(insertTime);

    //任务文件实体集合
    qDeleteAll(downFiles);
    downFiles.clear();
    for(FileDownload* fileInfo : FilesDownloadURLs)
    {
        NsRScheduleSendFiles *downFile = new NsRScheduleSendFiles;
        QString fuuid;
        UuidUtil::nextUUID(fuuid);
        downFile->setUuid(fuuid);
        downFile->setFileUrl(fileInfo->DownloadURLs);
        downFile->setFileAbst(fileInfo->DescPath);
        downFile->setTaskUuid(nsRScheduleTask->getUuid()) ;
        downFile->setState(SendFiles_State::USABLE);
        downFile->setError(trs(""));
        downFiles.append(downFile);
    }
    try
    {
        NSScheduleDao::insertRTaskAndTaskFiles(nsRScheduleTask,downFiles);
        respEntity->State = State::_0;
    }
    catch(DBException &ex)
    {
        qDebug() << trs("出错:%1%2%3").arg(ex.getType()).arg(ex.getTypeDesc()).arg(ex.getText());
        respEntity->State = Sche_Data_Trans::Resp_Info_State::_D;
    }

    //析构任务及其任务文件实体
    delete nsRScheduleTask;
    qDeleteAll(downFiles);
    downFiles.clear();
    qDeleteAll(FilesDownloadURLs);
    FilesDownloadURLs.clear();

sendDatagram:
    try
    {
        DatagramUtil::getInstance().packDatagram(respEntity,datagram);
        delete respEntity;
    }
    catch(QString &excep)
    {
        qDebug() << trs("出错:%1").arg(excep);
        goto end;
    }
    catch(TransException &excep)
    {
        qDebug() << excep.getText();
        goto end;
    }
    response->setDatagram(datagram);
    ////结束
end:
    mutex->unlock();
}

ReqScheduleTaskDownloadInfo *NoderRecScheduleTaskRequest::CallbackByReqScheduleTask(ReqScheduleTaskDownloadInfo *scheduleEntity)
{
    //TODO
    return scheduleEntity;
    //    gramEntity = scheduleEntity;
}

