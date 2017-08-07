#include "nrsctaskparsestatusrequest.h"
#include "baseiclient.h"
using namespace Environment::Task_Status::Noder::Sche;
QMutex * NoderRecScheduleTaskParseStatusRequest::mutex = new QMutex;

NoderRecScheduleTaskParseStatusRequest::NoderRecScheduleTaskParseStatusRequest()
{

}

NoderRecScheduleTaskParseStatusRequest::~NoderRecScheduleTaskParseStatusRequest()
{
    delete gramEntity;
}

void NoderRecScheduleTaskParseStatusRequest::doRequest(RequestContext *request, ResponseContext *response)
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

    quint8 state;
    NSScheduleDao::getRTaskStateByTaskUUID(taskUUID,state);
    //如果执行状态为成功则继续，否则直接结束
    if(state == Task_State::EXECSUCCESS)
    {
        //报文执行反馈状态为失败
        if(taskState != Environment::Datagram::State::_0)
        {
            //修改任务状态为“失败”
            NSScheduleDao::updateRTaskState(taskUUID,Task_State::TASKERROR);
        }
        //报文执行反馈状态为成功
        else
        {
            //修改任务下发地址状态为“成功”
            NSScheduleDao::updateRTaskState(taskUUID,Task_State::TASKSUCCESS);
            ////迁移该任务、任务下文件、任务下节点服务器地址到归档表
            NSScheduleDao::moveRTask2STask(taskUUID);
        }
    }

    ////结束
end:
    mutex->unlock();
}

RespScheduleTaskExecStatus *NoderRecScheduleTaskParseStatusRequest::CallbackByRespScheduleTask(RespScheduleTaskExecStatus *scheduleEntity)
{
    return scheduleEntity;
}

