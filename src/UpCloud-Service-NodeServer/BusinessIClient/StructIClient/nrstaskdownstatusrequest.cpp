#include "nrstaskdownstatusrequest.h"
#include "baseiclient.h"
using namespace Environment::Task_Status::Noder::Stru;

NoderRecStructTaskDownStatusRequest::NoderRecStructTaskDownStatusRequest()
{

}

NoderRecStructTaskDownStatusRequest::~NoderRecStructTaskDownStatusRequest()
{
    delete gramEntity;
}

void NoderRecStructTaskDownStatusRequest::doRequest(RequestContext *request, ResponseContext *response)
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

    //获取任务下载状态
    quint8 state;
    NsStructDao::getRTaskStateByTaskUUID(taskUUID,state);
    //如果下载状态为成功则继续，否则直接结束
    if(state == Task_State::DOWNSUCCESS)
    {
        //报文解析反馈状态为失败
        if(taskState != Environment::Datagram::State::_0)
        {
            //修改任务状态, 任务下发地址状态 为 “不可解析”
            NsStructDao::updateRTaskAndSendFilesStateByUUID(taskUUID, Task_State::UNPARSE, SendFiles_State::UNPARSE);
        }
        //报文解析反馈状态为成功
        else
        {
            //修改任务状态, 任务下发地址状态 为 “可解析”
            NsStructDao::updateRTaskAndSendFilesStateByUUID(taskUUID, Task_State::PARSEABLE, SendFiles_State::PARSEABLE);
        }
    }

    ////结束
end:
    qDebug() << trs("RespStructFilesDownloadStatus end");
}

RespStructFilesDownloadStatus *NoderRecStructTaskDownStatusRequest::CallbackByRespStructTask(RespStructFilesDownloadStatus *structEntity)
{
    return structEntity;
}

