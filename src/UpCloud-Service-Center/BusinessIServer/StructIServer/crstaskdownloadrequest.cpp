#include "crstaskdownloadrequest.h"
#include "baseiserver.h"
using namespace Environment::Datagram;
using namespace Environment::Task_Status::Center::Stru;
using namespace Environment::Datagram::Stru_Data_Trans;

CenterRecStructTaskDownloadRequest::CenterRecStructTaskDownloadRequest()
{

}

CenterRecStructTaskDownloadRequest::~CenterRecStructTaskDownloadRequest()
{
    delete gramEntity;
}

void CenterRecStructTaskDownloadRequest::doRequest(RequestContext *request, ResponseContext *response)
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
    //固定码
    QString clientKey = QString::number(request->getUUID());
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
    CSStructDao::getRTaskUuidByTaskNum(taskUUID,taskNum);

    ////状态为成功
    if(taskState != Environment::Datagram::State::_0)
    {
        //任务状态不为成功
        //修改任务状态为“下发出错”，任务下发地址状态为“下发出错”，出错原因见报文状态码
        QString errorMsg = trs("");

        CSStructDao::getErrorMsgByState(taskState,errorMsg);
        CSStructDao::updateRTaskAndAddr(taskUUID,
                                        Task_State::SENDING,
                                        Task_State::SENDERROR,
                                        clientKey,
                                        SendStatus_State::SENDING,
                                        SendStatus_State::SENDERROR,
                                        errorMsg);
    }
    else
    {
        //修改任务、任务下发地址状态、结构化任务下发状态表
        /*
            根据计划任务编号、节点服务器UUID、响应状态修改结构化任务状态和结构化任务下发地址状态，注意：
                1.修改下发地址表状态为“下发成功”;当任务表任务状态已经是ERROR时不做修改，当任务不为ERROR，当回执状态为成功，修改任务为“下发成功”
                2.不用接收Catch
        */


        //修改当前节点服务器下发状态为“下发成功”
        QString clientError = trs("");
        CSStructDao::updateSendStatusByAddr(taskUUID,
                                            SendStatus_State::SENDING,
                                            SendStatus_State::SENDSUCCESS,
                                            clientError,
                                            clientKey);

        //查找当前节点服务器下发状态是否还有“SendStatus_State::SENDING”
        //如果有则说明还有节点服务器未返回，没有则说明所有的节点服务器都返回
        if(CSStructDao::getSendStatusState(taskUUID, SendStatus_State::SENDING) == false)
        {
            //所有都返回

            //查找当前节点服务器下发状态是否还有“SendStatus_State::SENDERROR”
            //如果有则主任务下发失败，没有则说明主任务下发成功
            if(CSStructDao::getSendStatusState(taskUUID, SendStatus_State::SENDERROR) == false)
            {
                //成功
                CSStructDao::updateRTaskState(taskUUID,Task_State::SENDSUCCESS);
            }
            else
            {
                //失败
                CSStructDao::updateRTaskState(taskUUID,Task_State::SENDERROR);
            }
        }

    }
    ////结束
end:
    qDebug() << trs("RespStructFilesDownloadInfo end");
}

RespStructFilesDownloadInfo *CenterRecStructTaskDownloadRequest::CallbackByRespStructTask(RespStructFilesDownloadInfo *structEntity)
{
    return structEntity;
}

