#include "crsctaskdownloadrequest.h"
#include "baseiserver.h"
using namespace Environment::Task_Status::Center::Sche;
using namespace Environment::Datagram::Sche_Data_Trans;
QMutex * CenterRecScheduleTaskDownloadRequest::mutex = new QMutex;

CenterRecScheduleTaskDownloadRequest::CenterRecScheduleTaskDownloadRequest()
{

}

CenterRecScheduleTaskDownloadRequest::~CenterRecScheduleTaskDownloadRequest()
{
    delete gramEntity;
}

void CenterRecScheduleTaskDownloadRequest::doRequest(RequestContext *request, ResponseContext *response)
{
    mutex->lock();
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
    try
    {
        //TODO  --------
        gramEntity = DatagramUtil::getInstance().parseMessageText(CallbackByRespScheduleTask,msgType,message);
    }
    catch(TransException &excep)
    {
        qDebug() << trs("反序列化报文体到实体对象:ErrorCode:%1,ErrorMsg:%2").arg(excep.getType()).arg(excep.getText());
        goto end;
    }
    taskState = gramEntity->State;
    taskNum = gramEntity->TaskUUID;
    //使用任务编号获取任务UUID
    CSScheduleDao::getRTaskUuidByTaskNum(taskUUID,taskNum);

    ////状态为成功
    if(taskState != Environment::Datagram::State::_0)
    {
        //任务状态不为成功
        //修改任务状态为“下发出错”，任务下发地址状态为“下发出错”，出错原因见报文状态码
        QString errorMsg = trs("");

        CSScheduleDao::getErrorMsgByState(taskState,errorMsg);
        CSScheduleDao::updateRTaskAndAddr(taskUUID,Task_State::SENDING,Task_State::SENDERROR,QString("<>"),clientKey, SendAddr_State::SENDERROR, errorMsg);
    }
    else
    {
        //修改任务、任务下发地址状态、结构化任务下发状态表
        /*
            根据计划任务编号、节点服务器UUID、响应状态修改结构化任务状态和结构化任务下发地址状态，注意：
                1.修改下发地址表状态为“下发成功”;当任务表任务状态已经是ERROR时不做修改，当任务不为ERROR，当回执状态为成功，修改任务为“下发成功”
                2.不用接收Catch
        */
        CSScheduleDao::updateRTaskAndAddr(taskUUID,Task_State::SENDING,Task_State::SENDSUCCESS,QString("<>"),clientKey, SendAddr_State::SENDSUCCESS, trs(""));
    }
    ////结束
end:
    mutex->unlock();
}

RespScheduleTaskDownloadInfo *CenterRecScheduleTaskDownloadRequest::CallbackByRespScheduleTask(RespScheduleTaskDownloadInfo *scheduleEntity)
{
    return scheduleEntity;
}

