#include "nrutaskstatusrequest.h"
#include "baseiclient.h"
using namespace Environment::Task_Status::Noder::Unstru;
NoderRecUnstructTaskStatusRequest::NoderRecUnstructTaskStatusRequest()
{

}

NoderRecUnstructTaskStatusRequest::~NoderRecUnstructTaskStatusRequest()
{
    delete gramEntity;
}

void NoderRecUnstructTaskStatusRequest::doRequest(RequestContext *request, ResponseContext *response)
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
        gramEntity = DatagramUtil::getInstance().parseMessageText(CallbackByRespUnstructTask,msgType,message);
    }
    catch(TransException &excep)
    {
        qDebug() << trs("反序列化报文体到实体对象:ErrorCode:%1,ErrorMsg:%2").arg(excep.getType()).arg(excep.getText());
        goto end;
    }
    taskState = gramEntity->State;
    taskNum = gramEntity->TaskUUID;
    //使用任务编号获取任务UUID
    NsUnstructDao::getRTaskUuidByTaskNum(taskUUID,taskNum);

    ////如果任务状态为DOWNERROR不做任何处理之间结束
    quint8 state;
    NsUnstructDao::getRTaskStateByTaskUUID(taskUUID,state);
    if(state == Task_State::DOWNERROR)
    {
        goto end;
    }
    ////判断报文解析状态
    //状态不为成功
    if(taskState != Environment::Datagram::State::_0)
    {
        //任务状态不为成功
        //修改任务状态为“任务处理失败”
        NsUnstructDao::updateRTaskState(taskUUID,Task_State::TASKERROR);
        goto end;
    }
    else
    {
        //修改任务下发地址状态为“任务处理成功”
        NsUnstructDao::updateRTaskState(taskUUID,Task_State::TASKSUCCESS);
        ////迁移该任务、任务下文件、任务下节点服务器地址到归档表
        NsUnstructDao::moveRTask2STask(taskUUID);
        goto end;
    }
    ////结束
end:
    qDebug() << trs("RespUnstructFilesDownloadStatus end");
}

RespUnstructFilesDownloadStatus *NoderRecUnstructTaskStatusRequest::CallbackByRespUnstructTask(RespUnstructFilesDownloadStatus *unstructEntity)
{
    return unstructEntity;
}

