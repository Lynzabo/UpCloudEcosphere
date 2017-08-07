#include "crsctaskdownstatusrequest.h"
#include "baseiserver.h"
using namespace Environment::Datagram;
using namespace Environment::Task_Status::Center::Sche;

QMutex * CenterRecScheduleTaskDownStatusRequest::mutex = new QMutex;
CenterRecScheduleTaskDownStatusRequest::CenterRecScheduleTaskDownStatusRequest()
{

}

CenterRecScheduleTaskDownStatusRequest::~CenterRecScheduleTaskDownStatusRequest()
{
    delete mutex;
    delete gramEntity;
}

void CenterRecScheduleTaskDownStatusRequest::doRequest(RequestContext *request, ResponseContext *response)
{
    mutex->lock();
    QByteArray datagram;

    ////反序列化报文体到实体对象
    quint8 msgType = request->getMsgType();
    QString message = request->getMessage();
    //任务状态
    quint8 taskState;
    //任务编号
    quint32 taskNum;
    //任务UUID
    QString taskUUID;
    QString clientKey = request->getClientKey();
    //发送报文实体对象
    RespScheduleTaskDownloadStatus *respEntity = new RespScheduleTaskDownloadStatus;
    //解帧报文并生成报文实体
    try
    {
        gramEntity = DatagramUtil::getInstance().parseMessageText(CallbackByRespScheduleTask,msgType,message);
        respEntity->TaskUUID = gramEntity->TaskUUID;
    }
    catch(TransException &excep)
    {
        qDebug() << trs("反序列化报文体到实体对象:ErrorCode:%1,ErrorMsg:%2").arg(excep.getType()).arg(excep.getText());
        ////任务编号不为空
        if(gramEntity->TaskUUID == 0)
        {
            delete respEntity;
            goto end;
        }
        else
        {
            respEntity->TaskUUID = gramEntity->TaskUUID;
            respEntity->State = excep.getType();
            //任务状态不为成功
            //修改任务状态为“下载出错”，任务下载地址状态为“下载出错”，出错原因见报文状态码
            QString errorMsg = trs("");
            CSScheduleDao::getErrorMsgByState(taskState,errorMsg);
            CSScheduleDao::updateRTaskAndAddr(taskUUID,Task_State::SENDSUCCESS,Task_State::DOWNERROR,QString("<>"),clientKey, SendAddr_State::DOWNERROR, errorMsg);
            goto sendDatagram;
        }
    }
    taskState = gramEntity->State;
    taskNum = gramEntity->TaskUUID;
    //使用任务编号获取任务UUID
    CSScheduleDao::getRTaskUuidByTaskNum(taskUUID,taskNum);
    ////修改任务和任务下载地址状态
    ////状态为成功
    if(!(gramEntity->State == Environment::Task_Status::Noder::Sche::Task_State::DOWNSUCCESS))
    {
        //状态为失败
        ////修改任务状态为“下载出错”，任务地址表状态为“下载出错”，往“控制传输任务下载状态表”添加出错信息
        QVector<Result*> Errors = gramEntity->resultInfo->results;
        QString clientError = trs("下载出错");
        CSScheduleDao::updateRTaskErrorInfo(taskUUID,Task_State::DOWNERROR, SendAddr_State::DOWNERROR, clientError,Errors);
        respEntity->State = State::_0;
        goto sendDatagram;
    }
    else
    {
        ////修改任务状态及其下载地址状态，
        //修改下载地址状态为“下载成功”
        QString clientError = trs("");
        CSScheduleDao::updateRSendAddrByTaskUUID(taskUUID, clientKey, SendAddr_State::DOWNSUCCESS, clientError);
        ////查找任务下载地址表当前任务所有下载节点服务器UUID列表
        QList<CsRScheduleSendAddr> addrEntrys = CSScheduleDao::dirRSendAddrsByTaskUUID(taskUUID);
        int count = addrEntrys.size();
        int count_downSuccess = 0;
        for(int i=0; i<count; i++)
        {
            if(addrEntrys.at(i).getState() == SendAddr_State::DOWNSUCCESS)
            {
                count_downSuccess++;
            }
        }
        if(count_downSuccess == count)
        {
            //说明这是最后一个反馈的节点服务器，而且该节点服务器反馈成功，故修改主任务状态为“下载成功”
            CSScheduleDao::updateRTaskState(taskUUID,Task_State::DOWNSUCCESS);
        }
        respEntity->State = State::_0;
        goto sendDatagram;
    }

sendDatagram:
    ////拼装响应下载状态报文并发送给当前节点服务器
    try
    {
        DatagramUtil::getInstance().packDatagram(respEntity,datagram, request->getUUID());
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

ReqScheduleTaskDownloadStatus *CenterRecScheduleTaskDownStatusRequest::CallbackByRespScheduleTask(ReqScheduleTaskDownloadStatus *scheduleEntity)
{
    return scheduleEntity;
}

