#include "dictutil.h"
using QtJson::JsonArray;
using QtJson::JsonObject;
DictUtil::DictUtil()
{

}

bool DictUtil::taskEntinyFromjsonStr(QList<CsDict> &taskList, const QString &msg)
{
    bool ok = true;
    int num = 0;
    taskList.clear();
    JsonObject jsonO = QtJson::parse(msg,ok).toMap();
     num = jsonO["size"].toInt();
    int i = 0;
    for(i = 0;i < num; ++i) {
        CsDict task;
        ok = taskEntinyFromjsonStr(task,jsonO.value(QString::number(i)).toString());
        if(!ok) {
            break;
        }
        taskList.append(task);
    }
    //获取记录条数


    if(i == num) {
        ok = true;
    }
    return ok;
}

bool DictUtil::taskEntinyFromjsonStr(CsDict &task, const QString &msg)
{
    bool ok = false;
    JsonObject jsonObj = QtJson::parse(msg,ok).toMap();
    if(ok) {
        task.setUuid(jsonObj["uuid"].toString());
        task.setCode(jsonObj["code"].toString());
        task.setName(jsonObj["name"].toString());
        task.setDescription(jsonObj["descripion"].toString());
        task.setSequence((qint32)jsonObj["sequence"].toInt());
        task.setSupUuid(jsonObj["supUuid"].toString());
        task.setState((quint8)jsonObj["state"].toInt());
        task.setInsertor(jsonObj["insertor"].toString());
        task.setInsertTime(jsonObj["inserttime"].toString());
        task.setOperater(jsonObj["operater"].toString());
        task.setOperaTime(jsonObj["operatime"].toString());
    }
    return ok;

}

void DictUtil::taskEntinyTojsonStr(QString &msg, const QList<CsDict> &task)
{
    int i = 0;
    JsonObject jsonO;

    for(i = 0;i < task.size();++i) {
       QString str;
       taskEntinyTojsonStr(str,task.at(i));
       jsonO.insert(QString::number(i),str);
    }
    jsonO.insert("size",QString::number(task.size()));
    msg = QtJson::serialize(jsonO);
}

void DictUtil::taskEntinyTojsonStr(QString &msg, const CsDict &task)
{
    JsonObject jsonObj;
    jsonObj["uuid"] = task.getUuid();
    jsonObj["code"] = task.getCode();
    jsonObj["name"] = task.getName();
    jsonObj["descripion"] = task.getDescription();
    jsonObj["sequence"] = (qint32)task.getSequence();
    jsonObj["supUuid"] = task.getSupUuid();
    jsonObj["state"] = (quint8)task.getState();
    jsonObj["insertor"] = task.getInsertor();
    jsonObj["inserttime"] = task.getInsertTime();
    jsonObj["operater"] = task.getOperater();
    jsonObj["operatime"] = task.getOperaTime();
    msg = QtJson::serialize(jsonObj);
}

