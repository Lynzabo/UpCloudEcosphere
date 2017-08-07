#include "crutaskstatusrequest.h"
#include "baseiserver.h"
using namespace Environment::Datagram;
using namespace Environment::Task_Status::Center::Unstru;
using namespace Environment::Task_Status::Center;

CenterRecUnstructTaskStatusRequest::CenterRecUnstructTaskStatusRequest()
{

}

CenterRecUnstructTaskStatusRequest::~CenterRecUnstructTaskStatusRequest()
{
    delete gramEntity;
}
void CenterRecUnstructTaskStatusRequest::doRequest(RequestContext *request, ResponseContext *response)
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
    RespUnstructFilesDownloadStatus *respEntity = new RespUnstructFilesDownloadStatus;
    //解帧报文并生成报文实体
    try
    {
        gramEntity = DatagramUtil::getInstance().parseMessageText(CallbackByRespUnstructTask,msgType,message);
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

            CSUnstructDao::getErrorMsgByState(taskState,errorMsg);
            CSUnstructDao::updateRTaskAndAddr(taskUUID,
                                            Task_State::SENDSUCCESS,
                                            Task_State::DOWNERROR,
                                            clientKey,
                                            SendStatus_State::SENDSUCCESS,
                                            SendStatus_State::DOWNERROR,
                                            errorMsg);
            goto sendDatagram;
        }
    }
    taskState = gramEntity->State;
    taskNum = gramEntity->TaskUUID;
    //使用任务编号获取任务UUID
    CSUnstructDao::getRTaskUuidByTaskNum(taskUUID,taskNum);
    ////修改任务和任务下载地址状态
    ////状态为成功
    if(!(gramEntity->State == Environment::Task_Status::Noder::Unstru::Task_State::DOWNSUCCESS))
    {
        //状态为失败
        ////修改任务状态为“下载出错”，任务地址表状态为“下载出错”，往“非结构化任务下载状态表”添加出错信息
        QVector<Result*> Errors = gramEntity->resultInfo->results;
        CSUnstructDao::updateRTaskState(taskUUID,Task_State::DOWNERROR);
        CSUnstructDao::updateSendStateErrorInfo(taskUUID,
                                              SendStatus_State::SENDSUCCESS,
                                              SendStatus_State::DOWNERROR,
                                              clientKey,
                                              Errors);
        respEntity->State = State::_0;
        goto sendDatagram;
    }
    else
    {
        //修改当前节点服务器下发状态为“下载成功”
        QString clientError = trs("");
        CSUnstructDao::updateSendStatusByAddr(taskUUID,
                                            SendStatus_State::SENDSUCCESS,
                                            SendStatus_State::DOWNSUCCESS,
                                            clientError,
                                            clientKey);

        //查找当前节点服务器下发状态是否还有“SendStatus_State::SENDSUCCESS”
        //如果有则说明还有节点服务器未返回，没有则说明所有的节点服务器都返回
        if(CSUnstructDao::getSendStatusState(taskUUID, SendStatus_State::SENDSUCCESS) == false)
        {
            //所有都返回

            //查找当前节点服务器下发状态是否还有“SendStatus_State::DOWNERROR”
            //如果有则主任务下载失败，没有则说明主任务下载成功
            if(CSUnstructDao::getSendStatusState(taskUUID, SendStatus_State::DOWNERROR) == false)
            {
                //成功
                CSUnstructDao::updateRTaskState(taskUUID,Task_State::DOWNSUCCESS);
                ////迁移任务
                CSUnstructDao::moveRTask2STask(taskUUID);
            }
            else
            {
                //失败
                CSUnstructDao::updateRTaskState(taskUUID,Task_State::DOWNERROR);
            }
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
    qDebug() << trs("ReqUnstructFilesDownloadStatus end");
}

ReqUnstructFilesDownloadStatus *CenterRecUnstructTaskStatusRequest::CallbackByRespUnstructTask(ReqUnstructFilesDownloadStatus *unstructEntity)
{
    return unstructEntity;
}
