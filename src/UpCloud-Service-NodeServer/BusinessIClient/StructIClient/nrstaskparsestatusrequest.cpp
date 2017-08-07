#include "nrstaskparsestatusrequest.h"
#include "baseiclient.h"
using namespace Environment::Task_Status::Noder::Stru;

NoderRecStructTaskParseStatusRequest::NoderRecStructTaskParseStatusRequest()
{

}

NoderRecStructTaskParseStatusRequest::~NoderRecStructTaskParseStatusRequest()
{
    delete gramEntity;
}

void NoderRecStructTaskParseStatusRequest::doRequest(RequestContext *request, ResponseContext *response)
{
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
        gramEntity = DatagramUtil::getInstance().parseMessageText(CallbackByRespStructTask,msgType,message);
    }
    catch(TransException &excep)
    {
        qDebug() << trs("反序列化报文体到实体对象:ErrorCode:%1,ErrorMsg:%2").arg(excep.getType()).arg(excep.getText());
        goto end;
    }
    taskState = gramEntity->State;
    taskNum = gramEntity->TaskUUID;
    //使用任务编号获取任务UUID
    NsStructDao::getRTaskUuidByTaskNum(taskUUID,taskNum);

    //获取任务解析状态
    quint8 state;
    NsStructDao::getRTaskStateByTaskUUID(taskUUID,state);
    //如果解析状态为成功则继续，否则直接结束
    if(state == Task_State::PARSESUCCESS)
    {
        //报文解析反馈状态为失败
        if(taskState != Environment::Datagram::State::_0)
        {
            //修改任务状态为“失败”
            NsStructDao::updateRTaskState(taskUUID,Task_State::TASKERROR);
        }
        //报文解析反馈状态为成功
        else
        {
            //修改任务下发地址状态为“成功”
            NsStructDao::updateRTaskState(taskUUID,Task_State::TASKSUCCESS);
            //迁移该任务、任务下文件、任务下节点服务器地址到归档表
            NsStructDao::moveRTask2STask(taskUUID);
        }
    }

    ////结束
end:
    qDebug() << trs("RespStructTaskExecStatus end");
}

RespStructTaskExecStatus *NoderRecStructTaskParseStatusRequest::CallbackByRespStructTask(RespStructTaskExecStatus *structEntity)
{
    return structEntity;
}

