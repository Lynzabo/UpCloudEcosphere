#include "scheduleutil.h"
using QtJson::JsonArray;
using QtJson::JsonObject;
ScheduleUtil::ScheduleUtil()
{

}

void ScheduleUtil::taskEntinyToJson(QString &msg, const CsRScheduleTask &task)
{
    JsonObject json;
    json["task.uuid"] = task.getUuid();
    json["task.taskName"] = task.getTaskName();
    json["task.taskNum"] = task.getTaskNum();
    json["task.description"] = task.getDescription();
    json["task.sendTime"] = task.getSendTime();
    json["task.execTime"] = task.getExecTime();
    json["task.strategy"] = task.getStrategy();
    json["task.state"] = task.getState();
    json["task.saveAbst"] = task.getSaveAbst();
    json["task.insertor"] = task.getInsertor();
    json["task.insertTime"] = task.getInsertTime();
    json["task.operater"] = task.getOperater();
    json["task.operaTime"] = task.getOperaTime();
    msg  = QtJson::serialize(json);
}

void ScheduleUtil::taskListEntinyToJson(QString &msg, const QList<CsRScheduleTask> &taskList)
{
    JsonArray jsonArray;
    QString str;
    for(int i = 0;i < taskList.size(); ++i)
    {
        CsRScheduleTask task = taskList.at(i);
        taskEntinyToJson(str,task);
        jsonArray << str;
    }
    msg = QtJson::serialize(jsonArray);
}

bool ScheduleUtil::taskEntinyFromJson(CsRScheduleTask &task, const QString &msg)
{
    bool ok = false;
    JsonObject json = QtJson::parse(msg,ok).toMap();
    if(!ok)
    {
        return ok;
    }
    task.setUuid(json.value("task.uuid").toString());
    task.setTaskName(json.value("task.taskName").toString());
    task.setTaskNum((quint32)json.value("task.taskNum").toInt());
    task.setDescription(json.value("task.description").toString());
    task.setSendTime(json.value("task.sendTime").toString());
    task.setExecTime(json.value("task.execTime").toString());
    task.setStrategy((quint16)json.value("task.strategy").toInt());
    task.setState((quint8)json.value("task.state").toInt());
    task.setSaveAbst(json.value("task.saveAbst").toString());
    task.setInsertor(json.value("task.insertor").toString());
    task.setInsertTime(json.value("task.insertTime").toString());
    task.setOperater(json.value("task.operater").toString());
    task.setOperaTime(json.value("task.operaTime").toString());
    return ok;
}

bool ScheduleUtil::taskListEntinyFromJson(QList<CsRScheduleTask> &taskList, const QString &msg)
{
    bool ok = false;
    JsonArray jsonArray = QtJson::parse(msg,ok).toList();
    for(int i = 0;i < jsonArray.size(); ++i)
    {
        CsRScheduleTask task;
        ok = taskEntinyFromJson(task,jsonArray.at(i).toString());
        if(!ok) {
            break;
        }
        taskList.push_back(task);
    }
    return ok;

}

void ScheduleUtil::addrEntinyToJson(QString &msg, const CsRScheduleSendAddr &addr)
{
    JsonObject json;
    json["addr.uuid"] = addr.getUuid();
    json["addr.clientUuid"] = addr.getClientUuid();
    json["addr.state"] = addr.getState();
    json["addr.error"] = addr.getError();
    json["addr.taskUuid"] = addr.getTaskUuid();
    msg = QtJson::serialize(json);
}

void ScheduleUtil::addrListEntinyToJson(QString &msg, const QList<CsRScheduleSendAddr> &addrList)
{
    JsonArray jsonArray;
    QString str;
    for(int i = 0;i < addrList.size(); ++i)
    {
        CsRScheduleSendAddr task = addrList.at(i);
        addrEntinyToJson(str,task);
        jsonArray << str;
    }
    msg = QtJson::serialize(jsonArray);
}

bool ScheduleUtil::addrEntinyFromJson(CsRScheduleSendAddr &addr, const QString &msg)
{
    bool ok = false;
    JsonObject json = QtJson::parse(msg,ok).toMap();
    if(!ok)
    {
        return ok;
    }
    addr.setUuid(json.value("addr.uuid").toString());
    addr.setClientUuid(json.value("addr.clientUuid").toString());
    addr.setState((quint8)json.value("addr.state").toInt());
    addr.setError(json.value("addr.error").toString());
    addr.setTaskUuid(json.value("addr.taskUuid").toString());
    return ok;
}

bool ScheduleUtil::addrListEntinyFromJson(QList<CsRScheduleSendAddr> &addrList, const QString &msg)
{
    bool ok = false;
    JsonArray jsonArray = QtJson::parse(msg,ok).toList();
    for(int i = 0;i < jsonArray.size(); ++i)
    {
        CsRScheduleSendAddr addr;
        ok = addrEntinyFromJson(addr,jsonArray.at(i).toString());
        if(!ok) {
            break;
        }
        addrList.push_back(addr);
    }
    return ok;
}

void ScheduleUtil::fileEntinyToJson(QString &msg, const CsRScheduleSendFiles &file)
{

    JsonObject json;
    json["file.uuid"] = file.getUuid();
    json["file.fileName"] = file.getFileName();
    json["file.downUrl"] = file.getDownUrl();
    json["file.fileDestName"] = file.getFileDestName();
    json["file.saveAbst"] = file.getSaveAbst();
    json["file.taskUuid"] = file.getTaskUuid();
    json["file.hardAbst"] = file.getHardAbst();
    json["file.fileSrc"] = file.getFileSrc();
    msg = QtJson::serialize(json);
}

void ScheduleUtil::fileListEntinyToJson(QString &msg, const QList<CsRScheduleSendFiles> &fileList)
{
    JsonArray jsonArray;
    QString str;
    for(int i = 0;i < fileList.size(); ++i)
    {
        CsRScheduleSendFiles file = fileList.at(i);
        fileEntinyToJson(str,file);
        jsonArray << str;
    }
    msg = QtJson::serialize(jsonArray);
}

bool ScheduleUtil::fileEntinyFromJson(CsRScheduleSendFiles &file, const QString &msg)
{
    bool ok = false;
    JsonObject json = QtJson::parse(msg,ok).toMap();
    if(!ok) {
        return ok;
    }
    file.setUuid(json.value("file.uuid").toString());
    file.setFileName(json.value("file.fileName").toString());
    file.setDownUrl(json.value("file.downUrl").toString());
    file.setFileDestName(json.value("file.fileDestName").toString());
    file.setSaveAbst(json.value("file.saveAbst").toString());
    file.setTaskUuid(json.value("file.taskUuid").toString());
    file.setHardAbst(json.value("file.hardAbst").toString());
    file.setFileSrc((quint8)json.value("file.fileSrc").toInt());
    return ok;
}

bool ScheduleUtil::fileListEntinyFromJson(QList<CsRScheduleSendFiles> &fileList, const QString &msg)
{
    bool ok = false;
    JsonArray jsonArray = QtJson::parse(msg,ok).toList();
    for(int i = 0;i < jsonArray.size(); ++i)
    {
        CsRScheduleSendFiles file;
        ok = fileEntinyFromJson(file,jsonArray.at(i).toString());
        if(!ok) {
            break;
        }
        fileList.push_back(file);
    }
    return ok;
}

void ScheduleUtil::vFileEntinyToJson(QString &msg, const VCsAScSendFiles &vFile)
{
    JsonObject json;
      json["file.uuid"] = vFile.getUuid();
      json["file.fileName"] = vFile.getFileName();
      json["file.downUrl"] = vFile.getDownUrl();
      json["file.fileDestName"] = vFile.getFileDestName();
      json["file.saveAbst"] = vFile.getSaveAbst();
      json["file.taskUuid"] = vFile.getTaskUuid();
      json["file.hardAbst"] = vFile.getHardAbst();
      json["file.fileSrc"] = (quint8)vFile.getFileSrc();
      json["file.state"] = (quint8)vFile.getState();
      json["file.errMsg"] = vFile.getErrMsg();
      msg = QtJson::serialize(json);
}

void ScheduleUtil::vFileListEntinyToJson(QString &msg, const QList<VCsAScSendFiles> &vFileList)
{
    JsonArray jsonArray;
        QString str;
        for(int i = 0;i < vFileList.size(); ++i)
        {
            VCsAScSendFiles file = vFileList.at(i);
            vFileEntinyToJson(str,file);
            jsonArray << str;
        }
        msg = QtJson::serialize(jsonArray);
}

bool ScheduleUtil::vFileEntinyFromJson(VCsAScSendFiles &vFile, const QString &msg)
{
    bool ok = false;
       JsonObject json = QtJson::parse(msg,ok).toMap();
       if(!ok) {
           return ok;
       }
       vFile.setUuid(json.value("file.uuid").toString());
       vFile.setFileName(json.value("file.fileName").toString());
       vFile.setDownUrl(json.value("file.downUrl").toString());
       vFile.setFileDestName(json.value("file.fileDestName").toString());
       vFile.setSaveAbst(json.value("file.saveAbst").toString());
       vFile.setTaskUuid(json.value("file.taskUuid").toString());
       vFile.setHardAbst(json.value("file.hardAbst").toString());
       vFile.setFileSrc((quint8)json.value("file.fileSrc").toInt());
       vFile.setState((quint8)json.value("file.state").toInt());
       vFile.setErrMsg(json.value("file.errMsg").toString());
       return ok;
}

bool ScheduleUtil::vFileListEntinyFromJson(QList<VCsAScSendFiles> &vFileList, const QString &msg)
{
    bool ok = false;
        JsonArray jsonArray = QtJson::parse(msg,ok).toList();
        for(int i = 0;i < jsonArray.size(); ++i)
        {
            VCsAScSendFiles file;
            ok = vFileEntinyFromJson(file,jsonArray.at(i).toString());
            if(!ok) {
                break;
            }
            vFileList.append(file);
        }
        return ok;
}

