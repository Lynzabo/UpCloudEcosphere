#include "crstaskparsestatusrequest.h"
#include "baseiserver.h"
using namespace Environment::Datagram;
using namespace Environment::Task_Status::Center::Stru;

CenterRecStructTaskParseStatusRequest::CenterRecStructTaskParseStatusRequest()
{

}

CenterRecStructTaskParseStatusRequest::~CenterRecStructTaskParseStatusRequest()
{
    delete gramEntity;
}

void CenterRecStructTaskParseStatusRequest::doRequest(RequestContext *request, ResponseContext *response)
{
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
    //固定码
    QString clientKey = QString::number(request->getUUID());
    //发送报文实体对象
    RespStructTaskExecStatus *respEntity = new RespStructTaskExecStatus;
    //解帧报文并生成报文实体
    try
    {
        gramEntity = DatagramUtil::getInstance().parseMessageText(CallbackByRespStructTask,msgType,message);
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
            //修改任务状态为“解析出错”，任务下发地址状态为“解析出错”，出错原因见报文状态码
            QString errorMsg = trs("");
            CSStructDao::getErrorMsgByState(taskState,errorMsg);
            CSStructDao::updateRTaskAndAddr(taskUUID,
                                            Task_State::DOWNSUCCESS,
                                            Task_State::PARSEERROR,
                                            clientKey,
                                            SendStatus_State::DOWNSUCCESS,
                                            SendStatus_State::PARSEERROR,
                                            errorMsg);
            goto sendDatagram;
        }
    }
    taskState = gramEntity->State;
    taskNum = gramEntity->TaskUUID;

    //使用任务编号获取任务UUID
    CSStructDao::getRTaskUuidByTaskNum(taskUUID,taskNum);
    ////修改任务和任务下发地址状态
    ////状态为成功
    if(!(gramEntity->State == Environment::Task_Status::Noder::Stru::Task_State::PARSESUCCESS))
    {
        //状态为失败
        ////修改任务状态为“解析出错”，任务地址表状态为“解析出错”，往“结构化任务下发状态表”添加出错信息
        QVector<Result*> Errors = gramEntity->resultInfo->results;
        CSStructDao::updateRTaskState(taskUUID,Task_State::DOWNERROR);
        CSStructDao::updateSendStateErrorInfo(taskUUID,
                                              SendStatus_State::SENDSUCCESS,
                                              SendStatus_State::PARSEERROR,
                                              clientKey,
                                              Errors);
    }
    else
    {
        ////修改任务状态及其下发地址状态
        //修改下发地址状态为“解析成功”
        //修改当前节点服务器下发状态为“下发成功”
        QString clientError = trs("");
        CSStructDao::updateSendStatusByAddr(taskUUID,
                                            SendStatus_State::DOWNSUCCESS,
                                            SendStatus_State::PARSESUCCESS,
                                            clientError,
                                            clientKey);
    }



    //查找当前节点服务器下发状态是否还有“SendStatus_State::DOWNSUCCESS”
    //如果有则说明还有节点服务器未返回，没有则说明所有的节点服务器都返回
    if(CSStructDao::getSendStatusState(taskUUID, SendStatus_State::DOWNSUCCESS) == false)
    {
        //所有都返回

        //查找当前节点服务器下发状态是否还有“SendStatus_State::DOWNERROR”
        //如果有则主任务下发失败，没有则说明主任务下发成功
        if(CSStructDao::getSendStatusState(taskUUID, SendStatus_State::DOWNERROR) == false)
        {
            //成功
            CSStructDao::updateRTaskState(taskUUID,Task_State::PARSESUCCESS);

            ////迁移任务
            CSStructDao::moveRTask2STask(taskUUID);
        }
        else
        {
            //失败
            CSStructDao::updateRTaskState(taskUUID,Task_State::PARSEERROR);
        }
    }

    respEntity->State = State::_0;
    goto sendDatagram;

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
    qDebug() << trs("ReqStructTaskExecStatus end");
}

ReqStructTaskExecStatus *CenterRecStructTaskParseStatusRequest::CallbackByRespStructTask(ReqStructTaskExecStatus *structEntity)
{
    return structEntity;
}

