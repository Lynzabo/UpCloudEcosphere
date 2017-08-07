#include "createtaskinfo.h"
#include "avro.h"
using QtJson::JsonArray;
using QtJson::JsonObject;
CreateTaskInfo::CreateTaskInfo()
{

}

QString CreateTaskInfo::getTaskName() const
{
    return taskName;
}

void CreateTaskInfo::setTaskName(const QString &value)
{
    taskName = value;
}

QString CreateTaskInfo::getSendTime() const
{
    return sendTime;
}

void CreateTaskInfo::setSendTime(const QString &value)
{
    sendTime = value;
}

QString CreateTaskInfo::getExecTime() const
{
    return execTime;
}

void CreateTaskInfo::setExecTime(const QString &value)
{
    execTime = value;
}

QString CreateTaskInfo::getParseTime() const
{
    return parseTime;
}

void CreateTaskInfo::setParseTime(const QString &value)
{
    parseTime = value;
}

quint8 CreateTaskInfo::getTaskState() const
{
    return taskState;
}

void CreateTaskInfo::setTaskState(const quint8 &value)
{
    taskState = value;
}

quint16 CreateTaskInfo::getStrategy() const
{
    return strategy;
}

void CreateTaskInfo::setStrategy(const quint16 &value)
{
    strategy = value;
}

QString CreateTaskInfo::getFileName() const
{
    return fileName;
}

void CreateTaskInfo::setFileName(const QString &value)
{
    fileName = value;
}

QString CreateTaskInfo::getClientUuid() const
{
    return clientUuid;
}

void CreateTaskInfo::setClientUuid(const QString &value)
{
    clientUuid = value;
}

QString CreateTaskInfo::getGroupDescription() const
{
    return groupDescription;
}

void CreateTaskInfo::setGroupDescription(const QString &value)
{
    groupDescription = value;
}

QString CreateTaskInfo::getClientDescription() const
{
    return clientDescription;
}

void CreateTaskInfo::setClientDescription(const QString &value)
{
    clientDescription = value;
}

quint8 CreateTaskInfo::getFileState() const
{
    return fileState;
}

void CreateTaskInfo::setFileState(const quint8 &value)
{
    fileState = value;
}

void CreateTaskInfo::mapAddTaskInfoToJson(QString &msg,const CreateTaskInfo &info)
{
    JsonObject jsonObj;
    jsonObj["fileName"] = info.getFileName();
    jsonObj["clientUuid"] = info.getClientUuid();
    jsonObj["groupDescription"] = info.getGroupDescription();
    jsonObj["fileState"] = info.getFileState();
    msg = QtJson::serialize(jsonObj);
}

void CreateTaskInfo::mapAddTaskInfoToJson(QString &msg, const QList<CreateTaskInfo> &infoList)
{
    JsonArray jsonArray;
    QString str;str.clear();
    foreach(const CreateTaskInfo &info,infoList) {
        mapAddTaskInfoToJson(str,info);
        jsonArray << str;
    }
    msg = QtJson::serialize(jsonArray);
}

bool CreateTaskInfo::mapAddTaskInfoFromJson(CreateTaskInfo &info, const QString &msg)
{
    bool ok = false;
    JsonObject jsonObj = QtJson::parse(msg,ok).toMap();
    if(ok) {
        info.setFileName(jsonObj.value("fileName").toString());
        info.setClientUuid(jsonObj.value("clientUuid").toString());
        info.setGroupDescription(jsonObj.value("groupDescription").toString());
        info.setFileState((quint8)jsonObj.value("fileState").toInt());
    }
    return ok;
}

bool CreateTaskInfo::mapAddTaskInfoFromJson(QList<CreateTaskInfo> &infoList, const QString &msg)
{
    bool ok = false;
    JsonArray jsonArray = QtJson::parse(msg,ok).toList();
    CreateTaskInfo info;
    foreach(const QVariant &json,jsonArray) {
        ok = mapAddTaskInfoFromJson(info,json.toString());
        if(!ok) {
            break;
        }
        infoList.append(info);
    }
    return ok;
}


