#include "nrutaskrequest.h"
#include "util/timerutil.h"
#include "util/uuidutil.h"
#include "baseiclient.h"
using namespace Environment::Datagram;
using namespace Environment::Task_Status::Noder::Unstru;

NoderRecUnstructTaskRequest::NoderRecUnstructTaskRequest()
{

}

NoderRecUnstructTaskRequest::~NoderRecUnstructTaskRequest()
{
    delete gramEntity;
}

void NoderRecUnstructTaskRequest::doRequest(RequestContext *request, ResponseContext *response)
{
    QString uuid;
    QString insertTime;
    QList<NsRUnstructSendFiles *> downFiles;
    QString saveAbst;
    QVector<FileDownload*> FilesDownloadURLs;
    QString downURL;
    QByteArray datagram;

    ////反序列化报文体到实体对象
    quint8 msgType = request->getMsgType();
    QString message = request->getMessage();
    //发送报文实体对象
    RespUnstructFilesDownloadInfo *respEntity = new RespUnstructFilesDownloadInfo;
    //任务实体
    NsRUnstructTask *nsRUnstructTask = new NsRUnstructTask;
    int seq =0;
    //解帧报文并生成报文实体
    try
    {
        gramEntity = DatagramUtil::getInstance().parseMessageText(CallbackByReqUnstructTask,msgType,message);
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
            respEntity->State = Unstru_Data_Trans::Resp_Info_State::_8;
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
            respEntity->State = Unstru_Data_Trans::Resp_Info_State::_8;
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
            respEntity->State = Unstru_Data_Trans::Resp_Info_State::_9;
            goto sendDatagram;
        }
    }
    ////保存非结构化任务到数据库，置任务为“任务可用”

    UuidUtil::nextUUID(uuid);

    TimerUtil::toString(insertTime);

    nsRUnstructTask->setUuid(uuid);
    nsRUnstructTask->setTaskNum(gramEntity->TaskUUID);
    nsRUnstructTask->setStrategy(gramEntity->Strategy);
    nsRUnstructTask->setState(Task_State::USABLE);
    nsRUnstructTask->setInsertTime(insertTime);
    //任务文件实体集合

    qDeleteAll(downFiles);
    downFiles.clear();
    for(FileDownload* fileInfo : FilesDownloadURLs)
    {
        NsRUnstructSendFiles *downFile = new NsRUnstructSendFiles;
        QString fuuid;
        UuidUtil::nextUUID(fuuid);
        downFile->setUuid(fuuid);
        downFile->setFileUrl(fileInfo->DownloadURLs);
        downFile->setFileAbst(fileInfo->DescPath);
        downFile->setTaskUuid(nsRUnstructTask->getUuid()) ;
        ++seq;
        downFile->setState(SendFiles_State::USABLE);
        downFile->setError(trs(""));
        downFiles.append(downFile);
    }
    try
    {
        NsUnstructDao::insertRTaskAndTaskFiles(nsRUnstructTask,downFiles);
        respEntity->State = State::_0;
    }
    catch(DBException &ex)
    {
        qDebug() << trs("出错:%1%2%3").arg(ex.getType()).arg(ex.getTypeDesc()).arg(ex.getText());
        respEntity->State = Unstru_Data_Trans::Resp_Info_State::_A;
    }

    //析构任务及其任务文件实体
    delete nsRUnstructTask;
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
    qDebug() << trs("ReqUnstructFilesDownloadInfo end");
}

ReqUnstructFilesDownloadInfo * NoderRecUnstructTaskRequest::CallbackByReqUnstructTask(ReqUnstructFilesDownloadInfo *unstructEntity)
{
    return unstructEntity;
}

