#include "nrsctaskdownstatusrequest.h"
#include "baseiclient.h"
using namespace Environment::Task_Status::Noder::Sche;
QMutex * NoderRecScheduleTaskDownStatusRequest::mutex = new QMutex;
NoderRecScheduleTaskDownStatusRequest::NoderRecScheduleTaskDownStatusRequest()
{

}

NoderRecScheduleTaskDownStatusRequest::~NoderRecScheduleTaskDownStatusRequest()
{
    delete gramEntity;
}

void NoderRecScheduleTaskDownStatusRequest::doRequest(RequestContext *request, ResponseContext *response)
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
    try
    {
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
    NSScheduleDao::getRTaskUuidByTaskNum(taskUUID,taskNum);


    //获取任务下载状态
    quint8 state;
    NSScheduleDao::getRTaskStateByTaskUUID(taskUUID,state);
    //如果下载状态为成功则继续，否则直接结束
    if(state == Task_State::DOWNSUCCESS)
    {
        //报文解析反馈状态为失败
        if(taskState != Environment::Datagram::State::_0)
        {
            //修改任务状态, 任务下发地址状态 为 “不可执行”
            NSScheduleDao::updateRTaskAndSendFilesStateByUUID(taskUUID, Task_State::UNEXEC, SendFiles_State::UNEXEC);
        }
        //报文解析反馈状态为成功
        else
        {
            //修改任务状态, 任务下发地址状态 为 “可执行”
            NSScheduleDao::updateRTaskAndSendFilesStateByUUID(taskUUID, Task_State::EXECABLE, SendFiles_State::EXECABLE);
        }
    }

    ////结束
end:
    mutex->unlock();
}

RespScheduleTaskDownloadStatus *NoderRecScheduleTaskDownStatusRequest::CallbackByRespScheduleTask(RespScheduleTaskDownloadStatus *scheduleEntity)
{
    return scheduleEntity;
}

