#include "csgroupandclientutil.h"
using QtJson::JsonArray;
using QtJson::JsonObject;

CsGroupAndClientUtil::CsGroupAndClientUtil()
{

}

bool CsGroupAndClientUtil::taskEntinyFromjsonStr(QList<CsClientGroup> &taskList, const QString &msg)
{
    CsClientGroup task;
    bool ok = false;
    JsonArray jsonArray  = QtJson::parse(msg,ok).toList();
    for(int i = 0;i < jsonArray.size();i++) {
        ok = taskEntinyFromjsonStr(task,jsonArray.at(i).toString());
        if(!ok) {
            break;
        }
        taskList.insert(i,task);
    }
    return ok;
}

bool CsGroupAndClientUtil::taskEntinyFromjsonStr(CsClientGroup &task, const QString &msg)
{

    bool ok = false;
    JsonObject jsonObj = QtJson::parse(msg,ok).toMap();
    if(ok) {
        task.setUuid(jsonObj.value("uuid").toString());
        task.setName(jsonObj.value("name").toString());
        task.setDescription(jsonObj.value("description").toString());
        task.setSupUuid(jsonObj.value("supuuid").toString());
        task.setSequence((qint32)jsonObj.value("sequence").toInt());
        task.setState((quint8)jsonObj.value("state").toInt());
        task.setInsertor(jsonObj.value("insertor").toString());
        task.setInsertTime(jsonObj.value("inserttime").toString());
        task.setOperater(jsonObj.value("operater").toString());
        task.setOperatTime(jsonObj.value("operattime").toString());
    }
    return ok;
}

void CsGroupAndClientUtil::taskEntinyTojsonStr(QString &msg, const QList<CsClientGroup> &taskList)
{
    JsonArray jsonArray;
    CsClientGroup task;
    QString str;
    for(int i = 0;i < taskList.size();++i) {
        task = taskList.at(i);
        taskEntinyTojsonStr(str,task);
        jsonArray << str;
    }
    msg = QtJson::serialize(jsonArray);

}

void CsGroupAndClientUtil::taskEntinyTojsonStr(QString &msg, const CsClientGroup &task)
{
    JsonObject jsonObj;
    jsonObj["uuid"] = task.getUuid();
    jsonObj["name"] = task.getName();
    jsonObj["description"] = task.getDescription();
    jsonObj["supuuid"] = task.getSupUuid();
    jsonObj["sequence"] = (qint32)task.getSequence();
    jsonObj["state"] = (quint8)task.getState();
    jsonObj["insertor"] = task.getInsertor();
    jsonObj["inserttime"] = task.getInsertTime();
    jsonObj["operater"] = task.getOperater();
    jsonObj["operattime"] = task.getOperatTime();
    msg = QtJson::serialize(jsonObj);

}

bool CsGroupAndClientUtil::taskEntinyFromjsonStr(QList<CsClientGroupAssoc> &taskList, const QString &msg)
{
    CsClientGroupAssoc task;
    bool ok = false;
    JsonArray jsonArray  = QtJson::parse(msg,ok).toList();
    for(int i = 0;i < jsonArray.size();i++) {
        ok = taskEntinyFromjsonStr(task,jsonArray.at(i).toString());
        if(!ok) {
            break;
        }
        taskList.insert(i,task);
    }
    return ok;
}

bool CsGroupAndClientUtil::taskEntinyFromjsonStr(  CsClientGroupAssoc &task,const QString &msg)
{
    bool ok = false;
    JsonObject jsonObj = QtJson::parse(msg,ok).toMap();
    if(ok) {
        task.setUuid(jsonObj.value("uuid").toString());
        task.setClientUuid(jsonObj.value("clientuuid").toString());
        task.setGroupUuid(jsonObj.value("groupuuid").toString());
        task.setInsertor(jsonObj.value("insertor").toString());
        task.setInsertTime(jsonObj.value("inserttime").toString());
        task.setSequence((qint32)jsonObj.value("sequence").toInt());
        task.setState((quint16)jsonObj.value("state").toInt());
    }
    return ok;
}

void CsGroupAndClientUtil::taskEntinyTojsonStr(QString &msg, const QList<CsClientGroupAssoc> &taskList)
{
    JsonArray jsonArray;
    CsClientGroupAssoc task;
    QString str;
    for(int i = 0;i < taskList.size();++i) {
        task = taskList.at(i);
        taskEntinyTojsonStr(str,task);
        jsonArray << str;
    }
    msg = QtJson::serialize(jsonArray);
}

void CsGroupAndClientUtil::taskEntinyTojsonStr(QString &msg, const CsClientGroupAssoc &task)
{
    JsonObject jsonObj;
    jsonObj["uuid"] = task.getUuid();
    jsonObj["clientuuid"] = task.getClientUuid();
    jsonObj["groupuuid"] = task.getGroupUuid();
    jsonObj["insertor"] = task.getInsertor();
    jsonObj["inserttime"] = task.getInsertTime();
    jsonObj["sequence"] = task.getSequence();
    jsonObj["state"] = task.getState();
    msg = QtJson::serialize(jsonObj);
}



bool CsGroupAndClientUtil::taskEntinyFromjsonStr(QList<VCsClientGroupAssoc> &taskList, const QString &msg)
{
    VCsClientGroupAssoc task;
    bool ok = false;
    JsonArray jsonArray  = QtJson::parse(msg,ok).toList();
    for(int i = 0;i < jsonArray.size();i++) {
        ok = taskEntinyFromjsonStr(task,jsonArray.at(i).toString());
        if(!ok) {
            break;
        }
        taskList.insert(i,task);
    }
    return ok;
}

bool CsGroupAndClientUtil::taskEntinyFromjsonStr(  VCsClientGroupAssoc &task,const QString &msg)
{
    bool ok = false;
    JsonObject jsonObj = QtJson::parse(msg,ok).toMap();
    if(ok) {
        task.setUuid(jsonObj.value("uuid").toString());
        task.setClientUuid(jsonObj.value("clientuuid").toString());
        task.setGroupUuid(jsonObj.value("groupuuid").toString());
        task.setInsertor(jsonObj.value("insertor").toString());
        task.setInsertTime(jsonObj.value("inserttime").toString());
        task.setSequence((qint32)jsonObj.value("sequence").toInt());
        task.setState((quint16)jsonObj.value("state").toInt());
        task.setDescription(jsonObj.value("description").toString());
    }
    return ok;
}

void CsGroupAndClientUtil::taskEntinyTojsonStr(QString &msg, const QList<VCsClientGroupAssoc> &taskList)
{
    JsonArray jsonArray;
    VCsClientGroupAssoc task;
    QString str;
    for(int i = 0;i < taskList.size();++i) {
        task = taskList.at(i);
        taskEntinyTojsonStr(str,task);
        jsonArray << str;
    }
    msg = QtJson::serialize(jsonArray);
}

void CsGroupAndClientUtil::taskEntinyTojsonStr(QString &msg, const VCsClientGroupAssoc &task)
{
    JsonObject jsonObj;
    jsonObj["uuid"] = task.getUuid();
    jsonObj["clientuuid"] = task.getClientUuid();
    jsonObj["groupuuid"] = task.getGroupUuid();
    jsonObj["insertor"] = task.getInsertor();
    jsonObj["inserttime"] = task.getInsertTime();
    jsonObj["sequence"] = task.getSequence();
    jsonObj["state"] = task.getState();
    jsonObj["description"] = task.getDescription();
    msg = QtJson::serialize(jsonObj);
}
bool CsGroupAndClientUtil::taskEntinyFromjsonStr(QList<CsClientExtendInfo> &taskList, const QString &msg)
{
    bool ok;
    JsonArray jsonArray = QtJson::parse(msg,ok).toList();
    foreach(const QVariant &json,jsonArray) {
        CsClientExtendInfo terminal;
        ok = taskEntinyFromjsonStr(terminal,json.toString());
        if(!ok) {
            break;
        }
        taskList.append(terminal);
    }
    return ok;
}

bool CsGroupAndClientUtil::taskEntinyFromjsonStr(CsClientExtendInfo &terminal, const QString &msg)
{
    bool ok = false;
    JsonObject jsonObj = QtJson::parse(msg,ok).toMap();
    if(ok) {
        terminal.setUUID(jsonObj.value("uuid").toString());
        terminal.setTerminalUUID((quint64)jsonObj.value("terminalUuid").toLongLong());
        terminal.setType((quint8)jsonObj.value("type").toInt());
        terminal.setDescription(jsonObj.value("description").toString());
        terminal.setMacAddr(jsonObj.value("macaddr").toString());
        terminal.setIP(jsonObj.value("ip").toString());
        terminal.setPubKey(jsonObj.value("publicKey").toString());
        terminal.setPriKey(jsonObj.value("privateKey").toString());
        terminal.setState((quint8)jsonObj.value("state").toInt());
        terminal.setRunState((quint8)jsonObj.value("runState").toInt());
        terminal.setCreateTime(jsonObj.value("createTime").toString());
        terminal.setOnlineTime(jsonObj.value("onlineTime").toString());
        terminal.setOfflineTime(jsonObj.value("offlineTime").toString());
    }
    return ok;
}

void CsGroupAndClientUtil::taskEntinyTojsonStr(QString &msg, const QList<CsClientExtendInfo> &taskList)
{
    JsonArray jsonArray;
    foreach(const CsClientExtendInfo &terminal,taskList) {
        QString params;
        taskEntinyTojsonStr(params,terminal);
        jsonArray << params;
    }
    msg = QtJson::serialize(jsonArray);
}

void CsGroupAndClientUtil::taskEntinyTojsonStr(QString &msg, const CsClientExtendInfo &terminal)
{
    JsonObject jsonObj;
    jsonObj["uuid"] = terminal.getUUID();
    jsonObj["terminalUuid"] = terminal.getTerminalUUID();
    jsonObj["description"] = terminal.getDescription();
    jsonObj["macaddr"] = terminal.getMacAddr();
    jsonObj["ip"] = terminal.getIP();
    jsonObj["publicKey"] = terminal.getPubKey();
    jsonObj["privateKey"] = terminal.getPriKey();
    jsonObj["state"] = terminal.getState();
    jsonObj["runState"] = terminal.getRunState();
    jsonObj["createTime"] = terminal.getCreateTime();
    jsonObj["onlineTime"] = terminal.getOnlineTime();
    jsonObj["offlineTime"] = terminal.getOfflineTime();
    msg = QtJson::serialize(jsonObj);
}

