#include "nrtaskrequest.h"
#include "util/timerutil.h"
#include "util/uuidutil.h"
using namespace Environment::Datagram;
using namespace Environment::Task_Status::Noder::Stru;
QMutex * NoderRecStructTaskRequest::mutex = new QMutex;
NoderRecStructTaskRequest::NoderRecStructTaskRequest()
{

}

NoderRecStructTaskRequest::~NoderRecStructTaskRequest()
{
    delete gramEntity;
}

void NoderRecStructTaskRequest::doRequest(RequestContext *request, ResponseContext *response)
{
    mutex->lock();
    QString uuid;
    QString insertTime;
    QList<NsRStructSendFiles *> downFiles;
    QString saveAbst;
    QVector<FileDownload*> FilesDownloadURLs;
    QString downURL;
    QByteArray datagram;

    ////反序列化报文体到实体对象
    quint8 msgType = request->getMsgType();
    QString message = request->getMessage();
    //发送报文实体对象
    RespStructFilesDownloadInfo *respEntity = new RespStructFilesDownloadInfo;
    //解帧报文并生成报文实体
    try
    {
        gramEntity = DatagramUtil::getInstance().parseMessageText(CallbackByReqStructTask,msgType,message);
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
    ////解析文件下载路径是否合法
    qDeleteAll(FilesDownloadURLs);
    FilesDownloadURLs.clear();
    downURL = trs("");
    for(FileDownload* fileInfo : gramEntity->ftpPush->FilesDownloadURLs)
    {
        downURL = fileInfo->DownloadURLs;
        if(!QUrl(downURL).isValid())
        {
            respEntity->State = Stru_Data_Trans::Resp_Info_State::_8;
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
            respEntity->State = Stru_Data_Trans::Resp_Info_State::_8;
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
            respEntity->State = Stru_Data_Trans::Resp_Info_State::_9;
            goto sendDatagram;
        }
    }
    ////保存结构化任务到数据库，置任务为“任务可用”
    //任务实体
    NsRStructTask *nsRStructTask = new NsRStructTask;

    UuidUtil::nextUUID(uuid);

    TimerUtil::toString(insertTime);

    nsRStructTask->setUuid(uuid);
    nsRStructTask->setTaskNum(gramEntity->TaskUUID);
    nsRStructTask->setStrategy(gramEntity->Strategy);
    nsRStructTask->setState(Task_State::USABLE);
    nsRStructTask->setInsertTime(insertTime);
    nsRStructTask->setExecTime(gramEntity->ExecTime); //add
    //任务文件实体集合

    qDeleteAll(downFiles);
    downFiles.clear();
    quint32 sequence=0;
    for(FileDownload* fileInfo : FilesDownloadURLs)
    {
        NsRStructSendFiles *downFile = new NsRStructSendFiles;
        QString fuuid;
        UuidUtil::nextUUID(fuuid);
        downFile->setUuid(fuuid);
        downFile->setFileUrl(fileInfo->DownloadURLs);
        downFile->setFileAbst(fileInfo->DescPath);
        downFile->setTaskUuid(nsRStructTask->getUuid()) ;
        downFile->setState(SendFiles_State::USABLE);
        downFile->setError(trs(""));
        sequence++;
        downFile->setSequence(sequence);//see
        downFiles.append(downFile);
    }
    try
    {
        NsStructDao::insertRTaskAndTaskFiles(nsRStructTask,downFiles);
        respEntity->State = State::_0;
    }
    catch(DBException &ex)
    {
        qDebug() << trs("出错:%1%2%3").arg(ex.getType()).arg(ex.getTypeDesc()).arg(ex.getText());
        respEntity->State = Stru_Data_Trans::Resp_Info_State::_A;
    }

    //析构任务及其任务文件实体
    delete nsRStructTask;
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

ReqStructFilesDownloadInfo *NoderRecStructTaskRequest::CallbackByReqStructTask(ReqStructFilesDownloadInfo *structEntity)
{
    //TODO
    return structEntity;
    //    gramEntity = structEntity;
}

