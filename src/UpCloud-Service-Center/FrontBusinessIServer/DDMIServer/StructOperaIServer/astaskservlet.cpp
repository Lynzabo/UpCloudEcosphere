#include "astaskservlet.h"
#include "createftpfileinfo.h"
#include "../../../BusinessIServer/StructIServer/dao/csstructdao.h"
#include "../../../BusinessIServer/StructIServer/bean/csrstask.h"
#include "avro.h"
using QtJson::JsonObject;
using QtJson::JsonArray;
using namespace Environment::Duplex_Interaction;
#include "util/structutil.h"
AddStructTaskServlet::AddStructTaskServlet()
{
}
void AddStructTaskServlet::doExec(DRequestContext *request, DResponseContext *response)
{

    quint8 responseState;
    QString responseContent;responseContent.clear();
    QString result;result.clear();
    QString currtime;currtime.clear();
    TimerUtil::toString(currtime);
    CsRStructTask task;
    QList<CsRStructSendAddr> addrInfoList;
    QList<CsRStructSendFiles> fileInfoList;
    QList<CsRStructSendStatus> statusInfoList;
    QString uuid;uuid.clear();
    bool ok;
    qsrand(TimerUtil::currentTimeMillis());
    quint32  taskNum =  qrand()%(1<<31);
    //1.接收客户端传递来参数列表    可选
    QString params = request->getParams();
    JsonObject json = QtJson::parse(params).toMap();
    ok = StructUtil::taskEntinyFromjsonStr(task,json.value("taskStr").toString());
    //解析参数列表失败
    if (!ok) {
        responseState = Data_Authority::_5;
        responseContent = Data_Authority::_5_DESC_ParamParseError;
        qDebug() << Data_Authority::_5_DESC_ParamParseError;
        goto end;
    }
    StructUtil::taskEntinyFromjsonStr(addrInfoList,json.value("addrStr").toString());
    //解析参数列表失败
    if (!ok) {
        responseState = Data_Authority::_5;
        responseContent = Data_Authority::_5_DESC_ParamParseError;
        qDebug() << Data_Authority::_5_DESC_ParamParseError;
        goto end;
    }
    StructUtil::taskSendStatusEntityFromjsonStr(statusInfoList,json.value("statusStr").toString());
    //解析参数列表失败
    if (!ok) {
        responseState = Data_Authority::_5;
        responseContent = Data_Authority::_5_DESC_ParamParseError;
        qDebug() << Data_Authority::_5_DESC_ParamParseError;
        goto end;
    }
    StructUtil::taskEntinyFromjsonStr(fileInfoList,json.value("fileStr").toString());
    //解析参数列表失败
    if (!ok) {
        responseState = Data_Authority::_5;
        responseContent = Data_Authority::_5_DESC_ParamParseError;
        qDebug() << Data_Authority::_5_DESC_ParamParseError;
        goto end;
    }

//    //TODO 添加记录已存在
//    paramsMap["taskname"] = task.getTaskName();
//    paramsMap["state"] = task.getState();
//    paramsMap["description"] = task.getDescription();
//    paramsMap["sendtime"] = task.getSendTime();
//    paramsMap["strategy"] = task.getStrategy();
//    if(CSUnstructDao::listTask(paramsMap).size() > 0)
//    {
//        responseState = Data_Authority::_9;
//        responseContent = Data_Authority::_9_DESC_RecordIsExsit;
//        goto end;
//    }
    //后台填写任务数据
    UuidUtil::nextUUID(uuid);
    task.setTaskNum(taskNum);
    task.setUuid(uuid);
    task.setInsertor(trs("zjy"));
    task.setInsertTime(currtime);
    task.setOperater(trs("zjy"));
    task.setOperaTime(currtime);

    //后台填写任务节点数据
    for(QList<CsRStructSendAddr>::iterator item = addrInfoList.begin();
        item != addrInfoList.end(); ++item) {
        UuidUtil::nextUUID(uuid);
        item->setUuid(uuid);
        item->setTaskUuid(task.getUuid());
    }
    //后台填写任务文件数据
    for(QList<CsRStructSendFiles>::iterator item = fileInfoList.begin();
        item != fileInfoList.end(); ++item) {
        UuidUtil::nextUUID(uuid);
        QString path = item->getFileName();
        int index = path.lastIndexOf("/");
        QString fileName = path.right(path.size() - index -1);
        item->setUuid(uuid);
        item->setTaskUuid(task.getUuid());
        QString completeSuffix = QFileInfo(path).completeSuffix();
        UuidUtil::nextUUID(uuid);
        QString fileDestName = uuid + "." + completeSuffix;
        CreateFtpFileInfo fileInfo;
        fileInfo.setFtpInfo(fileName,item->getSaveAbst(),path);
        item->setUuid(uuid);
        item->setTaskUuid(task.getUuid());
        item->setDownUrl(fileInfo.getDownUrl());
        item->setFileName(fileName);
        item->setSequence(0);
        item->setFileDestName(fileDestName);
        item->setHardAbst(fileInfo.getHardAbst());
        item->setFileSrc( Environment::Files_Src_Type::RemoteUI);
    }
    //后台填写任务关联信息
    for(QList<CsRStructSendStatus>::iterator item = statusInfoList.begin();
        item != statusInfoList.end(); ++item) {
        UuidUtil::nextUUID(uuid);
        item->setUuid(uuid);
        QString clientUuid = item->getClientUuid();
        foreach(const CsRStructSendAddr addr,addrInfoList) {
            if(clientUuid == addr.getClientUuid()) {
                item->setSendAddrUuid(addr.getUuid());
                break;
            }
        }
        QString fileName = item->getSendFileUuid();
        int index = fileName.lastIndexOf("/");
        fileName = fileName.right(fileName.size() - index -1);
        foreach(const CsRStructSendFiles file,fileInfoList) {
            if(fileName == file.getFileName()) {
                item->setSendFileUuid(file.getUuid());
                break;
            }
        }
        item->setTaskUuid(task.getUuid());
        item->setError("");
    }
    //2.处理业务,获取结果集
    try
    {
        CSStructDao::addTask(task,addrInfoList,fileInfoList,statusInfoList);
    }
    catch(DBException& ex)
    {
        Q_UNUSED(ex)
        responseState = Data_Authority::_4;
        responseContent = ex.getText();
        goto end;
    }


    //3.准备结果集回执
    responseState = Data_Authority::_0;
    //回执
 end:;
    //.返回客户端请求结果集  可选
    response->setResponseState(responseState);
    response->setResponseContent(responseContent);
}



