#include "crsctaskparsestatusrequest.h"
#include "baseiserver.h"
using namespace Environment::Datagram;
using namespace Environment::Task_Status::Center::Sche;

QMutex * CenterRecScheduleTaskParseStatusRequest::mutex = new QMutex;
CenterRecScheduleTaskParseStatusRequest::CenterRecScheduleTaskParseStatusRequest()
{

}

CenterRecScheduleTaskParseStatusRequest::~CenterRecScheduleTaskParseStatusRequest()
{
    delete mutex;
    delete gramEntity;
}

void CenterRecScheduleTaskParseStatusRequest::doRequest(RequestContext *request, ResponseContext *response)
{
    mutex->lock();
    QList<CsRScheduleSendAddr> addrEntrys;
    int count;
    int count_downSuccess = 0;
    int count_execError = 0;
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
    RespScheduleTaskExecStatus *respEntity = new RespScheduleTaskExecStatus;
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
            //修改任务状态为“执行出错”，任务下发地址状态为“执行出错”，出错原因见报文状态码
            QString errorMsg = trs("");
            CSScheduleDao::getErrorMsgByState(taskState,errorMsg);
            CSScheduleDao::updateRTaskAndAddr(taskUUID,Task_State::DOWNSUCCESS,Task_State::EXECERROR,QString("<>"),clientKey, SendAddr_State::EXECERROR, errorMsg);
            goto sendDatagram;
        }
    }
    taskState = gramEntity->State;
    taskNum = gramEntity->TaskUUID;
    respEntity->State = State::_0;
    //使用任务编号获取任务UUID
    CSScheduleDao::getRTaskUuidByTaskNum(taskUUID,taskNum);
    ////修改任务和任务下发地址状态
    ////状态为成功
    if(!(gramEntity->State == Environment::Task_Status::Noder::Sche::Task_State::EXECSUCCESS))
    {
        //状态为失败
        ////修改任务状态为“执行出错”，任务地址表状态为“执行出错”，往“控制传输任务下发状态表”添加出错信息
        QVector<Result*> Errors = gramEntity->resultInfo->results;
        QString clientError = trs("执行出错");
        CSScheduleDao::updateRTaskErrorInfo(taskUUID,Task_State::EXECERROR, SendAddr_State::EXECERROR, clientError,Errors);
    }
    else
    {
        ////修改任务状态及其下发地址状态
        //修改下发地址状态为“执行成功”
        QString clientError = trs("");
        CSScheduleDao::updateRSendAddrByTaskUUID(taskUUID, clientKey, SendAddr_State::EXECSUCCESS, clientError);
    }
    ////修改主任务状态
    ////判断是否所有节点服务器都反馈了
    addrEntrys = CSScheduleDao::dirRSendAddrsByTaskUUID(taskUUID);
    count = addrEntrys.size();
    for(int i=0; i<count; i++)
    {
        if(addrEntrys.at(i).getState() == SendAddr_State::DOWNSUCCESS)
        {
            count_downSuccess++;
        }
        else if(addrEntrys.at(i).getState() == SendAddr_State::EXECERROR)
        {
            count_execError++;
        }
    }
    //说明所有的节点都反馈了
    if(count_downSuccess == 0)
    {
        if(count_execError >= 1)
        {
            //说明有错误,修改主任务状态为“执行失败”
            CSScheduleDao::updateRTaskState(taskUUID,Task_State::EXECERROR);
        }
        else
        {
            //说明所有节点服务器反馈成功,故修改主任务状态为“执行成功”
            CSScheduleDao::updateRTaskState(taskUUID,Task_State::EXECSUCCESS);
            ////迁移任务
            CSScheduleDao::moveRTask2STask(taskUUID);
        }
    }
sendDatagram:
    ////拼装响应执行状态报文并发送给当前节点服务器
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

ReqScheduleTaskExecStatus *CenterRecScheduleTaskParseStatusRequest::CallbackByRespScheduleTask(ReqScheduleTaskExecStatus *scheduleEntity)
{
    return scheduleEntity;
}

