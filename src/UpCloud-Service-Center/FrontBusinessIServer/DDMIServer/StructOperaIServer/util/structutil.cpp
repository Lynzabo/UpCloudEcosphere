#include "structutil.h"
using QtJson::JsonArray;
using QtJson::JsonObject;

StructUtil::StructUtil()
{

}

void StructUtil::taskEntinyTojsonStr(QString &msg, const QList<CsRStructSendFiles> &taskList)
{
    JsonArray jsonArray;
    QString str;
    for(int i =0;i < taskList.size(); ++i) {
        CsRStructSendFiles file = taskList.at(i);
        taskEntinyTojsonStr(str,file);
        jsonArray << str;
    }
    msg = QtJson::serialize(jsonArray);
}

void StructUtil::taskEntinyTojsonStr(QString &msg, const CsRStructSendFiles &task)
{
    JsonObject json;
    json["uuid"] = task.getUuid();
    json["filename"] = task.getFileName();
    json["downurl"] = task.getDownUrl();
    json["filedestname"] = task.getFileDestName();
    json["saveabst"] = task.getSaveAbst();
    json["sequence"] =task.getSequence();
    json["taskuuid"] = task.getTaskUuid();
    json["hardAbst"] = task.getHardAbst();
    json["fileSrc"] = task.getFileSrc();
    msg = QtJson::serialize(json);
}
//-----------------------for view--------begin----------------------
void StructUtil::taskEntinyTojsonStr(QString &msg, const QList<VCsRStructSendFiles> &taskList)
{
    JsonArray jsonArray;
    QString str;
    for(int i =0;i < taskList.size(); ++i) {
        VCsRStructSendFiles file = taskList.at(i);
        taskEntinyTojsonStr(str,file);
        jsonArray << str;
    }
    msg = QtJson::serialize(jsonArray);
}

void StructUtil::taskEntinyTojsonStr(QString &msg, const VCsRStructSendFiles &task)
{
    JsonObject json;
    json["uuid"] = task.getUuid();
    json["filename"] = task.getFileName();
    json["downurl"] = task.getDownUrl();
    json["filedestname"] = task.getFileDestName();
    json["saveabst"] = task.getSaveAbst();
    json["sequence"] =task.getSequence();
    json["taskuuid"] = task.getTaskUuid();
    json["hardAbst"] = task.getHardAbst();
    json["fileSrc"] = task.getFileSrc();
    json["state"] = task.getState();
    msg = QtJson::serialize(json);
}


bool StructUtil::taskEntinyFromjsonStr(QList<VCsRStructSendFiles> &taskList, const QString &msg)
{
    bool ok = false;
    VCsRStructSendFiles task;
    JsonArray jsonArray = QtJson::parse(msg,ok).toList();
    for(int i =0;i < jsonArray.size();++i) {
        ok = taskEntinyFromjsonStr(task,jsonArray.at(i).toString());
        if(!ok) {
            break;
        }
        taskList.push_back(task);
    }
    return ok;
}

bool StructUtil::taskEntinyFromjsonStr(VCsRStructSendFiles &task, const QString &msg)
{
    bool ok = false;
    JsonObject json = QtJson::parse(msg,ok).toMap();
    if(ok) {
        task.setUuid(json.value("uuid").toString());
        task.setFileName(json.value("filename").toString());
        task.setDownUrl(json.value("downurl").toString());
        task.setFileDestName(json.value("filedestname").toString());
        task.setSaveAbst(json.value("saveabst").toString());
        task.setSequence((quint32)json.value("sequence").toInt());
        task.setTaskUuid(json.value("taskuuid").toString());
        task.setHardAbst(json.value("hardAbst").toString());
        task.setFileSrc((quint8)json.value("fileSrc").toUInt());
        task.setState((quint8)json.value("state").toUInt());
    }
    return ok;
}
//-----------------------for view--------end------------------------
bool StructUtil::taskEntinyFromjsonStr(QList<CsRStructSendFiles> &taskList, const QString &msg)
{
    bool ok = false;
    CsRStructSendFiles task;
    JsonArray jsonArray = QtJson::parse(msg,ok).toList();
    for(int i =0;i < jsonArray.size();++i) {
        ok = taskEntinyFromjsonStr(task,jsonArray.at(i).toString());
        if(!ok) {
            break;
        }
        taskList.push_back(task);
    }
    return ok;
}

bool StructUtil::taskEntinyFromjsonStr(CsRStructSendFiles &task, const QString &msg)
{
    bool ok = false;
    JsonObject json = QtJson::parse(msg,ok).toMap();
    if(ok) {
        task.setUuid(json.value("uuid").toString());
        task.setFileName(json.value("filename").toString());
        task.setDownUrl(json.value("downurl").toString());
        task.setFileDestName(json.value("filedestname").toString());
        task.setSaveAbst(json.value("saveabst").toString());
        task.setSequence((quint32)json.value("sequence").toInt());
        task.setTaskUuid(json.value("taskuuid").toString());
    }
    return ok;
}

void StructUtil::taskEntinyTojsonStr(QString &msg, const QList<CsRStructSendAddr> &taskList)
{
    JsonArray jsonArray;
    QString str;
    for(int i =0;i < taskList.size(); ++i) {
        CsRStructSendAddr addr = taskList.at(i);
        taskEntinyTojsonStr(str,addr);
        jsonArray << str;
    }
    msg = QtJson::serialize(jsonArray);
}

void StructUtil::taskEntinyTojsonStr(QString &msg, const CsRStructSendAddr &task)
{
    JsonObject json;
    json["uuid"] = task.getUuid();
    json["clientuuid"] = task.getClientUuid();
    json["taskuuid"] = task.getTaskUuid();
    json["groupDesc"] = task.getGroupDesc();
    msg = QtJson::serialize(json);
}

bool StructUtil::taskEntinyFromjsonStr(QList<CsRStructSendAddr> &taskList, const QString &msg)
{
    bool ok = false;
    CsRStructSendAddr task;
    JsonArray jsonArray = QtJson::parse(msg,ok).toList();
    for(int i =0;i < jsonArray.size();++i) {
        ok = taskEntinyFromjsonStr(task,jsonArray.at(i).toString());
        if(!ok) {
            break;
        }
        taskList.push_back(task);
    }
    return ok;
}

bool StructUtil::taskEntinyFromjsonStr(CsRStructSendAddr &task, const QString &msg)
{
    bool ok = false;
    JsonObject json = QtJson::parse(msg,ok).toMap();
    if(ok) {
        task.setUuid(json.value("uuid").toString());
        task.setClientUuid(json.value("clientuuid").toString());
        task.setTaskUuid(json.value("taskuuid").toString());
        task.setGroupDesc(json.value("groupDesc").toString());

    }
    return ok;
}
void StructUtil::taskEntinyTojsonStr(QString &msg, const QList<VCsRStructSendAddr> &taskList)
{
    JsonArray jsonArray;
    QString str;
    for(int i =0;i < taskList.size(); ++i) {
        VCsRStructSendAddr addr = taskList.at(i);
        taskEntinyTojsonStr(str,addr);
        jsonArray << str;
    }
    msg = QtJson::serialize(jsonArray);
}

void StructUtil::taskEntinyTojsonStr(QString &msg, const VCsRStructSendAddr &task)
{
    JsonObject json;
    json["uuid"] = task.getUuid();
    json["clientuuid"] = task.getClientUuid();
    json["taskuuid"] = task.getTaskUuid();
    json["groupDesc"] = task.getGroupDesc();
    json["state"] = task.getState();
    json["description"] = task.getDescription();
    msg = QtJson::serialize(json);
}

bool StructUtil::taskEntinyFromjsonStr(QList<VCsRStructSendAddr> &taskList, const QString &msg)
{
    bool ok = false;
    VCsRStructSendAddr task;
    JsonArray jsonArray = QtJson::parse(msg,ok).toList();
    for(int i =0;i < jsonArray.size();++i) {
        ok = taskEntinyFromjsonStr(task,jsonArray.at(i).toString());
        if(!ok) {
            break;
        }
        taskList.push_back(task);
    }
    return ok;
}

bool StructUtil::taskEntinyFromjsonStr(VCsRStructSendAddr &task, const QString &msg)
{
    bool ok = false;
    JsonObject json = QtJson::parse(msg,ok).toMap();
    if(ok) {
        task.setUuid(json.value("uuid").toString());
        task.setClientUuid(json.value("clientuuid").toString());
        task.setTaskUuid(json.value("taskuuid").toString());
        task.setGroupDesc(json.value("groupDesc").toString());
        task.setState((quint8)json.value("state").toInt());
        task.setDescription(json.value("description").toString());

    }
    return ok;
}
void StructUtil::taskEntinyTojsonStr(QString &msg, const QList<CsRStructTask> &taskList)
{
    JsonArray jsonArray;
    QString str;
    for(int i =0;i < taskList.size(); ++i) {
        CsRStructTask task = taskList.at(i);
        taskEntinyTojsonStr(str,task);
        jsonArray << str;
    }
    msg = QtJson::serialize(jsonArray);
}

void StructUtil::taskEntinyTojsonStr(QString &msg, const CsRStructTask &task)
{
    JsonObject json;
    json["uuid"] = task.getUuid();
    json["taskname"] = task.getTaskName();
    json["tasknum"] = (quint32)task.getTaskNum();
    json["description"] = task.getDescription();
    json["sendtime"] = task.getSendTime();
    json["exectime"] = task.getExecTime();
    json["strategy"] = (quint16)task.getStrategy();
    json["state"] = (quint8)task.getState();
    json["insertor"] = task.getInsertor();
    json["inserttime"] = task.getInsertTime();
    json["operater"] = task.getOperater();
    json["operatime"] = task.getOperaTime();
    msg = QtJson::serialize(json);
}

bool StructUtil::taskEntinyFromjsonStr(QList<CsRStructTask> &taskList, const QString &msg)
{
    bool ok = false;
    CsRStructTask task;
    JsonArray jsonArray = QtJson::parse(msg,ok).toList();
    for(int i =0;i < jsonArray.size();++i) {
        ok = taskEntinyFromjsonStr(task,jsonArray.at(i).toString());
        if(!ok) {
            break;
        }
        taskList.push_back(task);
    }
    return ok;
}

bool StructUtil::taskEntinyFromjsonStr(CsRStructTask &task, const QString &msg)
{
    bool ok = false;
    JsonObject json = QtJson::parse(msg,ok).toMap();
    if(ok) {
        task.setUuid(json.value("uuid").toString());
        task.setTaskName(json.value("taskname").toString());
        task.setTaskNum((quint32)json.value("tasknum").toInt());
        task.setDescription(json.value("description").toString());
        task.setSendTime(json.value("sendtime").toString());
        task.setExecTime(json.value("exectime").toString());
        task.setStrategy((quint16)json.value("strategy").toInt());
        task.setState((quint8)json.value("state").toInt());
        task.setInsertor(json.value("insertor").toString());
        task.setInsertTime(json.value("inserttime").toString());
        task.setOperater(json.value("operater").toString());
        task.setOperaTime(json.value("operatime").toString());
    }
    return ok;
}

bool StructUtil::taskSendStatusEntityFromjsonStr(CsRStructSendStatus &status, const QString &msg)
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

bool StructUtil::taskSendStatusEntityFromjsonStr(QList<CsRStructSendStatus> &statusList, const QString &msg)
{
    bool ok = false;
    JsonArray jsonArray = QtJson::parse(msg,ok).toList();
    CsRStructSendStatus status;
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

void StructUtil::taskSendStatusEntityTojsonStr(QString &msg, const CsRStructSendStatus &status)
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

void StructUtil::taskSendStatusEntityTojsonStr(QString &msg, const QList<CsRStructSendStatus> &statusList)
{
    JsonArray jsonArray;
    QString str;
    int i = 0;
    for(i =0;i < statusList.size(); ++i) {
        CsRStructSendStatus status = statusList.at(i);
        taskSendStatusEntityTojsonStr(str,status);
        jsonArray << str;
    }
    msg = QtJson::serialize(jsonArray);
}
