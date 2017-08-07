#include "unstructutil.h"
using QtJson::JsonObject;
using QtJson::JsonArray;

UnstructUtil::UnstructUtil()
{

}
bool UnstructUtil::taskEntityFromjsonStr(CsRUnstructTask &task, const QString &msg)
{
    bool ok = false;
    JsonObject jsonResult = QtJson::parse(msg, ok).toMap();
    if (ok)
    {
        task.setUuid(jsonResult["uuid"].toString());
        task.setTaskName(jsonResult["taskName"].toString());
        task.setTaskNum((quint32)(jsonResult["taskNum"].toInt()));
        task.setDescription(jsonResult["description"].toString());
        task.setSendTime(jsonResult["sendTime"].toString());
        task.setStrategy((quint16)(jsonResult["strategy"].toInt()));
        task.setState((quint8)(jsonResult["state"].toInt()));
        task.setInsertor(jsonResult["insertor"].toString());
        task.setInsertTime(jsonResult["insertTime"].toString());
        task.setOperater(jsonResult["operater"].toString());
        task.setOperaTime(jsonResult["operaTime"].toString());
    }
    return ok;
}

bool UnstructUtil::taskEntityFromjsonStr(QList<CsRUnstructTask> &taskList, const QString &msg)
{
    bool ok;
    CsRUnstructTask task;
    JsonArray jsonArray = QtJson::parse(msg,ok).toList();
    int i = 0;
    for(i =0;i < jsonArray.size();++i) {
        QString objStr = jsonArray.at(i).toString();
        ok = taskEntityFromjsonStr(task,objStr);
        if(!ok) {
            break;
        }
        taskList.push_back(task);
    }
    return ok;
}

void UnstructUtil::taskEntityTojsonStr(QString &msg, const CsRUnstructTask &task)
{
    JsonObject objJson;
    objJson["uuid"] = task.getUuid();
    objJson["taskName"] = task.getTaskName();
    objJson["taskNum"] = (quint32)(task.getTaskNum());
    objJson["description"] = task.getDescription();
    objJson["sendTime"] = task.getSendTime();
    objJson["strategy"] = (quint16)(task.getStrategy());
    objJson["state"] = (quint8)(task.getState());
    objJson["insertor"] = task.getInsertor();
    objJson["insertTime"] = task.getInsertTime();
    objJson["operater"] = task.getOperater();
    objJson["operaTime"] = task.getOperaTime();
    msg = QtJson::serialize(objJson);
}

void UnstructUtil::taskEntityTojsonStr(QString &msg, const QList<CsRUnstructTask> &taskList)
{
    JsonArray jsonArray;
    QString str;
    int i = 0;
    for(i =0;i < taskList.size(); ++i) {
        CsRUnstructTask task = taskList.at(i);
        taskEntityTojsonStr(str,task);
        jsonArray << str;
    }
    msg = QtJson::serialize(jsonArray);
}

bool UnstructUtil::taskAddrEntityFromjsonStr(CsRUnstructSendAddr &addr, const QString &msg)
{
    bool ok;
    JsonObject jsonResult = QtJson::parse(msg,ok).toMap();
    if(ok) {
        addr.setUuid(jsonResult["uuid"].toString());
        addr.setClientUuid(jsonResult["client_uuid"].toString());
        addr.setGroupDesc(jsonResult["group_uuids"].toString());
        addr.setTaskUuid(jsonResult["task_uuid"].toString());
    }
    return ok;
}

bool UnstructUtil::taskVAddrEntityFromjsonStr(VCsRUnstructSendAddr &addr, const QString &msg)
{
    bool ok;
    JsonObject jsonResult = QtJson::parse(msg,ok).toMap();
    if(ok) {
        addr.setUuid(jsonResult["uuid"].toString());
        addr.setClientUuid(jsonResult["client_uuid"].toString());
        addr.setGroupDesc(jsonResult["group_uuids"].toString());
        addr.setTaskUuid(jsonResult["task_uuid"].toString());
        addr.setState((quint8)jsonResult["state"].toInt());
        addr.setDescritpion(jsonResult["description"].toString());
    }
    return ok;
}

bool UnstructUtil::taskAddrEntityFromjsonStr(QList<CsRUnstructSendAddr> &taskList, const QString &msg)
{
    bool ok;
    CsRUnstructSendAddr task;
    JsonArray jsonArray = QtJson::parse(msg,ok).toList();
    for(int i =0;i < jsonArray.size();++i) {
        ok = taskAddrEntityFromjsonStr(task,jsonArray.at(i).toString());
        if(!ok) {
            break;
        }
        taskList.push_back(task);
    }
    return ok;
}

bool UnstructUtil::taskVAddrEntityFromjsonStr(QList<VCsRUnstructSendAddr> &taskList, const QString &msg)
{
    bool ok;
    VCsRUnstructSendAddr task;
    JsonArray jsonArray = QtJson::parse(msg,ok).toList();
    for(int i =0;i < jsonArray.size();++i) {
        ok = taskVAddrEntityFromjsonStr(task,jsonArray.at(i).toString());
        if(!ok) {
            break;
        }
        taskList.push_back(task);
    }
    return ok;
}

void UnstructUtil::taskAddrEntityTojsonStr(QString &msg, const CsRUnstructSendAddr &addr)
{

    JsonObject objJson ;
    objJson["uuid"] = addr.getUuid();
    objJson["client_uuid"] = addr.getClientUuid();
    objJson["group_uuids"] = addr.getGroupDesc();
    objJson["task_uuid"] = addr.getTaskUuid();
    msg = QtJson::serialize(objJson);
}

void UnstructUtil::taskVAddrEntityTojsonStr(QString &msg, const VCsRUnstructSendAddr &vaddr)
{
    JsonObject objJson ;
    objJson["uuid"] = vaddr.getUuid();
    objJson["client_uuid"] = vaddr.getClientUuid();
    objJson["group_uuids"] = vaddr.getGroupDesc();
    objJson["task_uuid"] = vaddr.getTaskUuid();
    objJson["state"] = vaddr.getState();
    objJson["description"] = vaddr.getDescritpion();
    msg = QtJson::serialize(objJson);
}

void UnstructUtil::taskAddrEntityTojsonStr(QString &msg, const QList<CsRUnstructSendAddr> &taskList)
{
    JsonArray jsonArray;
    QString str;
    int i = 0;
    for(i =0;i < taskList.size(); ++i) {
        CsRUnstructSendAddr addr = taskList.at(i);
        taskAddrEntityTojsonStr(str,addr);
        jsonArray << str;
    }
    msg = QtJson::serialize(jsonArray);
}

void UnstructUtil::taskVAddrEntityTojsonStr(QString &msg, const QList<VCsRUnstructSendAddr> &taskList)
{
    JsonArray jsonArray;
    QString str;
    int i = 0;
    for(i =0;i < taskList.size(); ++i) {
        VCsRUnstructSendAddr addr = taskList.at(i);
        taskVAddrEntityTojsonStr(str,addr);
        jsonArray << str;
    }
    msg = QtJson::serialize(jsonArray);
}

bool UnstructUtil::taskAddrFileEntityFromjsonStr(CsRUnstructSendFiles &sendFile, const QString &msg)
{
    bool ok;
    JsonObject jsonResult = QtJson::parse(msg,ok).toMap();
    if(ok) {
        sendFile.setUuid(jsonResult["uuid"].toString());
        sendFile.setFileName(jsonResult["file_name"].toString());
        sendFile.setSaveAbst(jsonResult["save_abst"].toString());
        sendFile.setDownUrl(jsonResult["down_url"].toString());
        sendFile.setTaskUuid(jsonResult["task_uuid"].toString());
        sendFile.setFileDestName(jsonResult["file_dest_name"].toString());
    }
    return ok;
}

bool UnstructUtil::taskVAddrFileEntityFromjsonStr(VCsRUnstructSendFiles &sendFile, const QString &msg)
{
    bool ok;
    JsonObject jsonResult = QtJson::parse(msg,ok).toMap();
    if(ok) {
        sendFile.setUuid(jsonResult["uuid"].toString());
        sendFile.setFileName(jsonResult["file_name"].toString());
        sendFile.setSaveAbst(jsonResult["save_abst"].toString());
        sendFile.setDownUrl(jsonResult["down_url"].toString());
        sendFile.setTaskUuid(jsonResult["task_uuid"].toString());
        sendFile.setFileDestName(jsonResult["file_dest_name"].toString());
        sendFile.setState((quint8)jsonResult["state"].toInt());
    }
    return ok;
}

bool UnstructUtil::taskAddrFileEntityFromjsonStr(QList<CsRUnstructSendFiles> &taskList, const QString &msg)
{
    bool ok;
    CsRUnstructSendFiles task;
    JsonArray jsonArray = QtJson::parse(msg,ok).toList();
    for(int i =0;i < jsonArray.size();++i) {
        ok = taskAddrFileEntityFromjsonStr(task,jsonArray.at(i).toString());
        if(!ok) {
            break;
        }
        taskList.push_back(task);
    }
    return ok;
}

bool UnstructUtil::taskVAddrFileEntityFromjsonStr(QList<VCsRUnstructSendFiles> &taskList, const QString &msg)
{
    bool ok;
    VCsRUnstructSendFiles task;
    JsonArray jsonArray = QtJson::parse(msg,ok).toList();
    for(int i =0;i < jsonArray.size();++i) {
        ok = taskVAddrFileEntityFromjsonStr(task,jsonArray.at(i).toString());
        if(!ok) {
            break;
        }
        taskList.push_back(task);
    }
    return ok;
}

void UnstructUtil::taskAddrFileEntityTojsonStr(QString &msg, const CsRUnstructSendFiles &sendFile)
{
    JsonObject objJson;
    objJson["uuid"] = sendFile.getUuid();
    objJson["file_name"] = sendFile.getFileName();
    objJson["save_abst"] = sendFile.getSaveAbst();
    objJson["down_url"] = sendFile.getDownUrl();
    objJson["task_uuid"] = sendFile.getTaskUuid();
    objJson["file_dest_name"] = sendFile.getFileDestName();
    objJson["hard_abst"] = sendFile.getHardAbst();
    objJson["file_src"] = sendFile.getFileSrc();
    msg = QtJson::serialize(objJson);
}

void UnstructUtil::taskVAddrFileEntityTojsonStr(QString &msg, const VCsRUnstructSendFiles &sendFile)
{
    JsonObject objJson;
    objJson["uuid"] = sendFile.getUuid();
    objJson["file_name"] = sendFile.getFileName();
    objJson["save_abst"] = sendFile.getSaveAbst();
    objJson["down_url"] = sendFile.getDownUrl();
    objJson["task_uuid"] = sendFile.getTaskUuid();
    objJson["file_dest_name"] = sendFile.getFileDestName();
    objJson["hard_abst"] = sendFile.getHardAbst();
    objJson["file_src"] = sendFile.getFileSrc();
    objJson["state"] = sendFile.getState();
    msg = QtJson::serialize(objJson);
}

void UnstructUtil::taskAddrFileEntityTojsonStr(QString &msg, const QList<CsRUnstructSendFiles> &taskList)
{
    JsonArray jsonArray;
    QString str;
    for(int i =0;i < taskList.size(); ++i) {
        CsRUnstructSendFiles file = taskList.at(i);
        taskAddrFileEntityTojsonStr(str,file);
        jsonArray << str;
    }
    msg = QtJson::serialize(jsonArray);
}

void UnstructUtil::taskVAddrFileEntityTojsonStr(QString &msg, const QList<VCsRUnstructSendFiles> &taskList)
{
    JsonArray jsonArray;
    QString str;
    for(int i =0;i < taskList.size(); ++i) {
        VCsRUnstructSendFiles file = taskList.at(i);
        taskVAddrFileEntityTojsonStr(str,file);
        jsonArray << str;
    }
    msg = QtJson::serialize(jsonArray);
}

bool UnstructUtil::taskSendStatusEntityFromjsonStr(CsRUnstructSendStatus &status, const QString &msg)
{
    bool ok = false;
    JsonObject objJson =  QtJson::parse(msg,ok).toMap();
    if(ok) {
        status.setUuid(objJson.value("uuid").toString());
        status.setClientUuid(objJson.value("clientUuid").toString());
        status.setSendFileUuid(objJson.value("sendFileUuid").toString());
        status.setError(objJson.value("error").toString());
        status.setTaskUuid(objJson.value("taskUuid").toString());
        status.setSendAddrUuid(objJson.value("sendAddrUuid").toString());
        status.setState((quint8)objJson.value("state").toInt());
    }
    return ok;
}

bool UnstructUtil::taskSendStatusEntityFromjsonStr(QList<CsRUnstructSendStatus> &statusList, const QString &msg)
{
    bool ok = false;
    JsonArray jsonArray = QtJson::parse(msg,ok).toList();
    CsRUnstructSendStatus status;
    if(ok) {
        for(int i =0;i < jsonArray.size();++i) {
            ok = taskSendStatusEntityFromjsonStr(status,jsonArray.at(i).toString());
            if(!ok) {
                break;
            }
            statusList.push_back(status);
        }
    }
    return ok;
}

void UnstructUtil::taskSendStatusEntityTojsonStr(QString &msg, const CsRUnstructSendStatus &status)
{
    JsonObject objJson;
    objJson["uuid"] = status.getUuid();
    objJson["clientUuid"] = status.getClientUuid();
    objJson["sendFileUuid"] = status.getSendFileUuid();
    objJson["error"] = status.getError();
    objJson["taskUuid"] = status.getTaskUuid();
    objJson["sendAddrUuid"] = status.getSendAddrUuid();
    objJson["state"] = status.getState();
    msg = QtJson::serialize(objJson);
}

void UnstructUtil::taskSendStatusEntityTojsonStr(QString &msg, const QList<CsRUnstructSendStatus> &statusList)
{
    JsonArray jsonArray;
    QString str;
    int i = 0;
    for(i =0;i < statusList.size(); ++i) {
        CsRUnstructSendStatus status = statusList.at(i);
        taskSendStatusEntityTojsonStr(str,status);
        jsonArray << str;
    }
    msg = QtJson::serialize(jsonArray);
}

//-------------------------for JNI DTask DTaskAddr DTaskFile----begin------------
bool UnstructUtil::DTaskEntityToJsonStr(const DTask &dTask, QString &jsonStr)
{
    JsonObject objJson;
    objJson["taskName"] = dTask.getTaskName();
    objJson["description"] = dTask.getDescription();
    objJson["strategy"] = dTask.getStrategy();
    bool isSuccess = false;
    jsonStr = QtJson::serializeStr(objJson, isSuccess);
    return isSuccess;
}

bool UnstructUtil::DTaskJsonStrToEntity(const QString &jsonStr, DTask &dTask)
{
    bool isSuccess;
    JsonObject jsonResult = QtJson::parse(jsonStr,isSuccess).toMap();
    if(isSuccess) {
        dTask.setTaskName(jsonResult["taskName"].toString());
        dTask.setDescription(jsonResult["description"].toString());
        dTask.setStrategy((quint16)(jsonResult["strategy"].toUInt()));
    }
    return isSuccess;
}

bool UnstructUtil::DTaskAddrEntityToJsonStr(const DTaskAddr &dTaskAddr, QString &jsonStr)
{
    JsonObject objJson;
    objJson["addrUUID"] = dTaskAddr.getAddrUUID();
    objJson["isGroup"] = dTaskAddr.getIsGroup();
    bool isSuccess = false;
    jsonStr = QtJson::serializeStr(objJson, isSuccess);
    return isSuccess;
}

bool UnstructUtil::DTaskAddrJsonStrToEntity(const QString &jsonStr, DTaskAddr &dTaskAddr)
{
    bool isSuccess;
    JsonObject jsonResult = QtJson::parse(jsonStr,isSuccess).toMap();
    if(isSuccess) {
        dTaskAddr.setAddrUUID(jsonResult["addrUUID"].toString());
        dTaskAddr.setIsGroup(jsonResult["isGroup"].toBool());
    }
    return isSuccess;
}

bool UnstructUtil::DTaskFileEntityToJsonStr(const DTaskFile &dTaskFile, QString &jsonStr)
{
    JsonObject objJson;
    objJson["fileName"] = dTaskFile.getFileName();
    objJson["srcAbst"] = dTaskFile.getSrcAbst();
    objJson["fileDestName"] = dTaskFile.getFileDestName();
    objJson["saveAbst"] = dTaskFile.getSaveAbst();
    bool isSuccess = false;
    jsonStr = QtJson::serializeStr(objJson, isSuccess);
    return isSuccess;
}

bool UnstructUtil::DTaskFileJsonStrToEntity(const QString &jsonStr, DTaskFile &dTaskFile)
{
    bool isSuccess;
    JsonObject jsonResult = QtJson::parse(jsonStr,isSuccess).toMap();
    if(isSuccess) {
        dTaskFile.setFileName(jsonResult["fileName"].toString());
        dTaskFile.setSrcAbst(jsonResult["srcAbst"].toString());
        dTaskFile.setFileDestName(jsonResult["fileDestName"].toString());
        dTaskFile.setSaveAbst(jsonResult["saveAbst"].toString());
    }
    return isSuccess;
}

bool UnstructUtil::DTaskAddrListEntityToJsonStr(const QList<DTaskAddr> &dTaskAddrList, QString &jsonStr)
{
    bool isSuccess;
    JsonObject json;
    QString str;
    int i = 0;
    for(i =0;i < dTaskAddrList.size(); ++i)
    {
        if(DTaskAddrEntityToJsonStr(dTaskAddrList.at(i), str))
        {
            json.insert(QString::number(i),str);
        }
        else
        {
            isSuccess = false;
            return isSuccess;
        }
    }
    json.insert("size",i);
    jsonStr = QtJson::serializeStr(json, isSuccess);
    return isSuccess;
}

bool UnstructUtil::DTaskAddrListJsonStrToEntity(const QString &jsonStr, QList<DTaskAddr> &dTaskAddrList)
{
    bool isSuccess;
    DTaskAddr dTaskAddr;
    JsonObject json = QtJson::parse(jsonStr,isSuccess).toMap();
    if(isSuccess == false)
    {
        return isSuccess;
    }

    int i = 0;
    int size = json.value("size").toInt();
    for(i =0;i < size;++i)
    {
        if(DTaskAddrJsonStrToEntity(json.value(QString::number(i)).toString(), dTaskAddr))
        {
            dTaskAddrList.append(dTaskAddr);
        }
        else
        {
            isSuccess = false;
            return isSuccess;
        }
    }
    isSuccess = true;
    return isSuccess;
}

bool UnstructUtil::DTaskFileListEntityToJsonStr(const QList<DTaskFile> &dTaskFileList, QString &jsonStr)
{
    bool isSuccess;
    JsonObject json;
    QString str;
    int i = 0;
    for(i =0;i < dTaskFileList.size(); ++i)
    {
        if(DTaskFileEntityToJsonStr(dTaskFileList.at(i), str))
        {
            json.insert(QString::number(i),str);
        }
        else
        {
            isSuccess = false;
            return isSuccess;
        }
    }
    json.insert("size",i);
    jsonStr = QtJson::serializeStr(json, isSuccess);
    return isSuccess;
}

bool UnstructUtil::DTaskFileListJsonStrToEntity(const QString &jsonStr, QList<DTaskFile> &dTaskFileList)
{
    bool isSuccess;
    DTaskFile dTaskFile;
    JsonObject json = QtJson::parse(jsonStr,isSuccess).toMap();
    if(isSuccess == false)
    {
        return isSuccess;
    }

    int i = 0;
    int size = json.value("size").toInt();
    for(i =0;i < size;++i)
    {
        if(DTaskFileJsonStrToEntity(json.value(QString::number(i)).toString(), dTaskFile))
        {
            dTaskFileList.append(dTaskFile);
        }
        else
        {
            isSuccess = false;
            return isSuccess;
        }
    }
    isSuccess = true;
    return isSuccess;
}

bool UnstructUtil::DTaskDDEditorEntityToJsonStr(const DTask &dTask,
                                                const QList<DTaskAddr> &dTaskAddrList,
                                                const QList<DTaskFile> &dUTaskFileList,
                                                const QList<DTaskFile> &dSTaskFileList,
                                                QString &jsonStr)
{
    bool isSuccess;
    JsonObject json;

    QString str;

    //dTask
    if(DTaskEntityToJsonStr(dTask, str))
    {
        json.insert("DTask",str);
    }
    else
    {
        isSuccess = false;
        return isSuccess;
    }

    //dTaskAddrList
    if(DTaskAddrListEntityToJsonStr(dTaskAddrList, str))
    {
        json.insert("DTaskAddrList",str);
    }
    else
    {
        isSuccess = false;
        return isSuccess;
    }

    //dUTaskFileList
    if(DTaskFileListEntityToJsonStr(dUTaskFileList, str))
    {
        json.insert("DUTaskFileList",str);
    }
    else
    {
        isSuccess = false;
        return isSuccess;
    }

    //dSTaskFileList
    if(DTaskFileListEntityToJsonStr(dSTaskFileList, str))
    {
        json.insert("DSTaskFileList",str);
    }
    else
    {
        isSuccess = false;
        return isSuccess;
    }
    jsonStr = QtJson::serializeStr(json, isSuccess);
    return isSuccess;
}

bool UnstructUtil::DTaskDDEditorJsonStrToEntity(const QString &jsonStr,
                                                DTask &dTask,
                                                QList<DTaskAddr> &dTaskAddrList,
                                                QList<DTaskFile> &dUTaskFileList,
                                                QList<DTaskFile> &dSTaskFileList)
{
    bool isSuccess;

    JsonObject json = QtJson::parse(jsonStr,isSuccess).toMap();
    if(isSuccess == false)
    {
        return isSuccess;
    }

    //dTask
    if(DTaskJsonStrToEntity(json.value("DTask").toString(), dTask) == false)
    {
        isSuccess = false;
        return isSuccess;
    }

    //dTaskAddrList
    if(DTaskAddrListJsonStrToEntity(json.value("DTaskAddrList").toString(), dTaskAddrList) == false)
    {
        isSuccess = false;
        return isSuccess;
    }

    //dUTaskFileList
    if(DTaskFileListJsonStrToEntity(json.value("DUTaskFileList").toString(), dUTaskFileList) == false)
    {
        isSuccess = false;
        return isSuccess;
    }

    //dSTaskFileList
    if(DTaskFileListJsonStrToEntity(json.value("DSTaskFileList").toString(), dSTaskFileList) == false)
    {
        isSuccess = false;
        return isSuccess;
    }
    isSuccess = true;
    return isSuccess;
}

//-------------------------for JNI DTask DTaskAddr DTaskFile----begin------------
