#include "csscheduledao.h"
using namespace Environment::Datagram;
using namespace Environment::Task_Status::Center::Sche;
CSScheduleDao::CSScheduleDao()
{

}

void CSScheduleDao::addTaskAddr(const QString &taskUuid, const QStringList &nodes, const QStringList &groupDes)
{
    //TODO 后续需要添加地址表中的所属群组字段
//    QString sql = "INSERT INTO CS_R_SCHEDULE_SEND_ADDR values(:uuid,:clientuuid,,:taskuuid,:groupDes)";
    QString sql = "INSERT INTO CS_R_SCHEDULE_SEND_ADDR values(:uuid,:clientuuid,:STATE,:ERROR,:taskuuid)";
    QString sqlForStatus = "insert into CS_R_SCHEDULE_SEND_STATUS values(:statusUuid,:clientuuid,:SEND_FILE_UUID,:ERROR,:taskuuid,:uuid,:STATE)";
    QString sqlForFile = "select * from CS_R_SCHEDULE_SEND_FILES where TASK_UUID  = :taskuuid";
    QVariantMap params;
    bool ok;
    QString uuid;uuid.clear();
    UuidUtil::nextUUID(uuid);
    params["taskuuid"] = taskUuid;
    //TODO
    params["STATE"] = Task_State::USABLE /*SendStatus_State::USABLE*/;
    DBQuery dbquery;
    QList<CsRScheduleSendFiles> fileList =  dbquery.listBeans(mapToRScheduleTaskSendFile,sqlForFile,params);

    params["ERROR"] = "";
    DBTransaction* transaction = new DBTransaction;
    transaction->beginTransaction();
    int i= 0;
    for(i =0 ;i < nodes.size();++i) {
        UuidUtil::nextUUID(uuid);
        params["uuid"] = uuid;
        params["clientuuid"] = nodes.at(i);
        params["groupDes"] = groupDes.at(i);
        ok = transaction->execSQL(sql,params);
        if(!ok) {
            goto end;
        }
        for(int i = 0;i < fileList.size(); ++i ) {
            CsRScheduleSendFiles file = fileList.at(i);
            UuidUtil::nextUUID(uuid);
            params["statusUuid"] = uuid;
            params["SEND_FILE_UUID"] = file.getUuid();
            ok = transaction->execSQL(sqlForStatus,params);

            if(!ok) {
                goto end;
            }
        }
    }
    transaction->commit();
    delete transaction;
    return;
end:;
    transaction->rollback();
    delete transaction;
    DBException execp;
    execp.setText(trs("添加数据错误"));
    execp.setType(QSqlError::TransactionError);
    throw execp;
}

void CSScheduleDao::delTask(const QStringList &uuids)
{
    QVariantMap params;params.clear();
    bool ok = false;
    QString sql  = "DELETE CS_R_SCHEDULE_SEND_STATUS where TASK_UUID in (:uuids)";
    params.insert("uuids", (QVariant)uuids);
    DBTransaction* transaction = new DBTransaction;
    transaction->beginTransaction();
    ok = transaction->execSQL(sql,params);
    if(!ok) {
        goto end;
    }

    sql = "delete CS_R_SCHEDULE_SEND_FILES where TASK_UUID in (:uuids)";
    ok = transaction->execSQL(sql,params);
    if(!ok) {
        goto end;
    }
    sql = "delete CS_R_SCHEDULE_SEND_ADDR where TASK_UUID in (:uuids)";
    ok = transaction->execSQL(sql,params);
    if(!ok) {
        goto end;
    }
    sql = "delete CS_R_SCHEDULE_TASK where UUID in (:uuids)";
    ok = transaction->execSQL(sql,params);
    if(!ok) {
        goto end;
    }
    transaction->commit();
    delete transaction;
    return;
end:;
    transaction->rollback();
    delete transaction;
    DBException excep;
    excep.setText(trs("删除数据错误"));
    excep.setType(QSqlError::TransactionError);
    throw excep;
}

void CSScheduleDao::delTaskAddr(const QString &taskUuid, const QStringList &nodes)
{
    QString sql = "DELETE CS_R_SCHEDULE_SEND_ADDR where TASK_UUID =:taskuuid and CLIENT_UUID IN (:nodes)";
    QVariantMap params;
    params["taskuuid"] = taskUuid;
    params.insert("nodes", (QVariant)nodes);
    bool ok;
    DBTransaction* transaction = new DBTransaction;
    transaction->beginTransaction();
    try{
        ok = transaction->execSQL(sql,params);
        if(!ok) {
            DBException execp;
            execp.setText(trs("添加数据错误"));
            execp.setType(QSqlError::TransactionError);
            throw execp;

        }
        else {
            transaction->commit();
            delete transaction;
        }
    }
    catch(DBException &ex) {
        transaction->rollback();
        delete transaction;
        throw ex;
    }
}

void CSScheduleDao::delTaskFiles(const QStringList &uuids)
{
    QVariantMap params;params.clear();
    bool ok = false;
    QString sql  = "DELETE CS_R_SCHEDULE_SEND_STATUS where SEND_FILE_UUID in (:uuids)";
    params.insert("uuids", (QVariant)uuids);
    DBTransaction* transaction = new DBTransaction;
    transaction->beginTransaction();
    ok = transaction->execSQL(sql,params);
    if(!ok) {
        goto end;
    }

    sql = "delete CS_R_SCHEDULE_SEND_FILES where UUID in (:uuids)";
    ok = transaction->execSQL(sql,params);
    if(!ok) {
        goto end;
    }
    transaction->commit();
    delete transaction;
    return;
end:;
    transaction->rollback();
    delete transaction;
    DBException excep;
    excep.setText(trs("删除数据错误"));
    excep.setType(QSqlError::TransactionError);
    throw excep;
}


QList<CsRScheduleTask> CSScheduleDao::listTask(const QVariantMap &listInfo)
{
    QString sql = "select * from CS_R_SCHEDULE_TASK where 1 = 1";
    QVariantMap params;
    if(!listInfo.value("taskName").toString().isEmpty())
    {
        QString str = "%";
        str.append(listInfo.value("taskName").toString()).append("%");
        params["taskName"] = str;
        sql.append(" and upper(TASK_NAME) LIKE upper(:taskName)");
    }
    if(!listInfo.value("insertor").toString().isEmpty())
    {
        QString str = "%";
        str.append(listInfo.value("insertor").toString()).append("%");
        params["insertor"] = str;
        sql.append(" and upper(INSERTOR) LIKE upper(:insertor)");
    }
    if(!listInfo.value("strategy").toString().isEmpty())
    {
        params["strategy"] =(quint16)listInfo.value("strategy").toInt();
        sql.append(" and STRATEGY =:strategy");
    }
    if(!listInfo.value("state").toString().isEmpty())
    {
        params["state"] = (quint8)listInfo.value("state").toInt();
        sql.append(" and STATE =:state");
    }
    if(listInfo.contains("send_time_begin"))
    {
        params["send_time_begin"] = listInfo.value("send_time_begin");
        params["send_time_end"] = listInfo.value("send_time_end");
        sql.append(" and SEND_TIME between :send_time_begin and :send_time_end");

        params["parse_time_begin"] = listInfo.value("parse_time_begin");
        params["parse_time_end"] = listInfo.value("parse_time_end");
        sql.append(" and EXEC_TIME between :parse_time_begin and :parse_time_end");
    }
    sql.append(" union all ");

    sql.append("select * from CS_S_SCHEDULE_TASK where 1 = 1");
    if(!listInfo.value("taskName").toString().isEmpty())
    {
        QString str = "%";
        str.append(listInfo.value("taskName").toString()).append("%");
        params["s_taskName"] = str;
        sql.append(" and upper(TASK_NAME) LIKE upper(:s_taskName)");
    }
    if(!listInfo.value("insertor").toString().isEmpty())
    {
        QString str = "%";
        str.append(listInfo.value("insertor").toString()).append("%");
        params["s_insertor"] = str;
        sql.append(" and upper(INSERTOR) LIKE upper(:s_insertor)");
    }
    if(!listInfo.value("strategy").toString().isEmpty())
    {
        params["s_strategy"] = (quint16)listInfo.value("strategy").toInt();
        sql.append(" and STRATEGY =:s_strategy");
    }
    if(!listInfo.value("state").toString().isEmpty())
    {
        params["s_state"] = (quint8)listInfo.value("state").toInt();
        sql.append(" and STATE =:s_state");
    }
    if(listInfo.contains("send_time_begin"))
    {
        params["s_send_time_begin"] = listInfo.value("send_time_begin");
        params["s_send_time_end"] = listInfo.value("send_time_end");
        sql.append(" and SEND_TIME between :s_send_time_begin and :s_send_time_end");

        params["s_parse_time_begin"] = listInfo.value("parse_time_begin");
        params["s_parse_time_end"] = listInfo.value("parse_time_end");
        sql.append(" and EXEC_TIME between :s_parse_time_begin and :s_parse_time_end");
    }
    DBQuery query;
    return query.listBeans(mapToRScheduleTask,sql,params);

}

QList<CsRScheduleSendAddr> CSScheduleDao::listAddr(const QString &taskUuid)
{
    QString sql = "select * from CS_R_SCHEDULE_SEND_ADDR where TASK_UUID =:taskUuid";
    QVariantMap params;
    params["taskUuid"] = taskUuid;
    DBQuery query;
    return query.listBeans(mapToRScheduleTaskSendAddr,sql,params);
}

QList<VCsAScSendFiles> CSScheduleDao::listVFile(const QString &taskUuid)
{
    QString sql = "select * from V_CS_A_SCHEDULE_SEND_FILES WHERE TASK_UUID =:taskUuid";
    QVariantMap params;
    params["taskUuid"]       = taskUuid;
    DBQuery query;
    return query.listBeans(mapToRScheduleVFile, sql, params);
}

QList<CsRScheduleTask> CSScheduleDao::itemTask(const QVariantMap &info)
{
    QString sql = "select * from CS_R_SCHEDULE_TASK WHERE 1 = 1";
    QVariantMap params;
    if(info.contains("uuid"))
    {
        params["uuid"] = info.value("uuid").toString();
        sql.append(" and UUID =:uuid");
    }
    if(info.contains("taskName"))
    {
        params["taskName"] = info.value("taskName").toString();
        sql.append(" and TASK_NAME =:taskName");
    }
    if(info.contains("taskNum"))
    {
        params["TASK_NUM"] = (quint32)info.value("taskNum").toInt();
        sql.append(" and TASK_NUM =:taskNum");
    }
    if(info.contains("description"))
    {
        params["description"] = info.value("description").toString();
        sql.append(" and DESCRIPTION =:description");
    }
    if(info.contains("sendTime"))
    {
        params["sendTime"] = info.value("sendTime").toString();
        sql.append(" and SEND_TIME =:sendTime");
    }
    if(info.contains("execTime"))
    {
        params["execTime"] = info.value("execTime").toString();
        sql.append(" and EXEC_TIME =:execTime");
    }
    if(info.contains("strategy"))
    {
        params["strategy"] = (quint16)info.value("strategy").toInt();
        sql.append(" and STRATEGY =:strategy");
    }
    if(info.contains("state"))
    {
        params["state"] = (quint8)info.value("state").toInt();
        sql.append(" and STATE =:state");
    }
    if(info.contains("saveAbst"))
    {
        params["saveAbst"] = info.value("saveAbst").toString();
        sql.append(" and SAVE_ABST =:saveAbst");
    }
    if(info.contains("insertor"))
    {
        params["insertor"] = info.value("insertor").toString();
        sql.append(" and INSERTOR =:insertor");
    }
    if(info.contains("insertTime"))
    {
        params["insertTime"] = info.value("insertTime").toString();
        sql.append(" and INSERT_TIME =:insertTime");
    }
    if(info.contains("operator"))
    {
        params["operator"] = info.value("operator").toString();
        sql.append(" and OPERATOR =:operator");
    }
    if(info.contains("operaTime"))
    {
        params["operaTime"] = info.value("operaTime").toString();
        sql.append(" and OPERA_TIME =:operaTime");
    }
    DBQuery query;
    return query.listBeans(mapToRScheduleTask, sql, params);
}

QList<CsRScheduleTask> CSScheduleDao::dirRTask(const quint8 &state, const QString &curTime)
{
    QString sql = "select * from CS_R_SCHEDULE_TASK WHERE state =:state and SEND_TIME <:curTime";
    QVariantMap params;
    params["state"]       = state;
    params["curTime"]     = curTime;
    DBQuery query;
    return query.listBeans(mapToRScheduleTask, sql, params);
}

void CSScheduleDao::updateTask(const QList<CsRScheduleTask> &taskList)
{
    bool fly = Environment::Db_Transaction_State::TRANS_FAIL;
    QString sqlTask = "update CS_R_SCHEDULE_TASK set TASK_NAME =:taskName, "
                      "TASK_NUM =:taskNum, "
                      "DESCRIPTION =:description, "
                      "SEND_TIME =:sendTime, "
                      "EXEC_TIME =:execTime, "
                      "STRATEGY =:strategy, "
                      "STATE =:state, "
                      "SAVE_ABST =:saveAbst, "
                      "INSERTOR =:insertor, "
                      "INSERT_TIME =:insertTime, "
                      "OPERATOR =:operator, "
                      "OPERA_TIME =:operaTime "
                      "where UUID =:uuid";
    QString sqlAddr = "update CS_R_SCHEDULE_SEND_ADDR set STATE =:state where TASK_UUID =:uuid";
    QVariantMap params;
    DBException excep;
    DBTransaction* transaction = new DBTransaction;
    transaction->beginTransaction();
    foreach(const CsRScheduleTask &task,taskList)
    {
        params["uuid"] = task.getUuid();
        params["taskName"] = task.getTaskName();
        params["taskNum"] = task.getTaskNum();
        params["description"] = task.getDescription();
        params["sendTime"] = task.getSendTime();
        params["execTime"] = task.getExecTime();
        params["strategy"] = task.getStrategy();
        params["state"] = task.getState();
        params["saveAbst"] = task.getSaveAbst();
        params["insertor"] = task.getInsertor();
        params["insertTime"] = task.getInsertTime();
        params["operator"] = task.getOperater();
        params["operaTime"] = task.getOperaTime();
        fly = transaction->execSQL(sqlTask,params);
        if(fly == Environment::Db_Transaction_State::TRANS_SUCCESS)
        {
            fly = transaction->execSQL(sqlAddr,params);
            if(fly == Environment::Db_Transaction_State::TRANS_FAIL)
            {
                goto end;
            }
        }
        else
        {
            goto end;
        }
    }
    transaction->commit();
    delete transaction;
    return;
end:;
    transaction->rollback();
    delete transaction;
    excep.setText(trs("操作数据错误"));
    excep.setType(QSqlError::TransactionError);
    throw excep;
}

void CSScheduleDao::updateRTaskState(const QString &taskUUID, const quint8 &state)
{
    bool fly = Environment::Db_Transaction_State::TRANS_FAIL;
    QString sql = "update CS_R_SCHEDULE_TASK set STATE =:state where UUID =:uuid";

    QVariantMap params;
    params["uuid"]       = taskUUID;
    params["state"] = state;
    //必须try...catch才能回滚和提交
    DBTransaction *transaction = new DBTransaction;
    try
    {
        transaction->beginTransaction();
        fly = transaction->execSQL(sql,params);
        if(fly == Environment::Db_Transaction_State::TRANS_SUCCESS)
        {
            transaction->commit();
        }
        else
        {
            DBException excep;
            excep.setType(QSqlError::TransactionError);
            excep.setText(trs("update error"));
            throw excep;
        }
    }
    catch(DBException &ex)
    {
        transaction->rollback();
        throw ex;
    }
    delete transaction;
}

QList<CsRScheduleSendAddr> CSScheduleDao::dirRSendAddrsByTaskUUID(const QString &taskUUID)
{
    QString sql = "select * from CS_R_SCHEDULE_SEND_ADDR WHERE TASK_UUID =:taskUUID";
    QVariantMap params;
    params["taskUUID"]       = taskUUID;
    DBQuery query;
    return query.listBeans(mapToRScheduleTaskSendAddr, sql, params);
}

void CSScheduleDao::updateRTaskAndAllSendAddrStatus(const QString &taskUUID, const quint8 &taskState, const quint8 &addrState, const QString &addrError)
{
    bool fly = Environment::Db_Transaction_State::TRANS_FAIL;
    QString tasksql = "update CS_R_SCHEDULE_TASK set STATE =:state where UUID =:uuid";

    QVariantMap params;
    params["uuid"]       = taskUUID;
    params["state"] = taskState;
    //必须try...catch才能回滚和提交
    DBTransaction *transaction = new DBTransaction;
    try
    {
        transaction->beginTransaction();
        fly = transaction->execSQL(tasksql,params);
        if(fly == Environment::Db_Transaction_State::TRANS_SUCCESS)
        {
            QString addrsql = "update CS_R_SCHEDULE_SEND_ADDR set STATE =:state,ERROR =:error where TASK_UUID =:taskUUID";
            QVariantMap addrparams;
            addrparams["taskUUID"]       = taskUUID;
            addrparams["state"] = addrState;
            addrparams["error"] = addrError;
            fly = transaction->execSQL(addrsql,addrparams);
            if(fly == Environment::Db_Transaction_State::TRANS_SUCCESS)
            {
                transaction->commit();
            }
            else
            {
                goto err;
            }
        }
        else
        {
err:;
            DBException excep;
            excep.setType(QSqlError::TransactionError);
            excep.setText(trs("update error"));
            throw excep;
        }
    }
    catch(DBException &ex)
    {
        transaction->rollback();
        throw ex;
    }
    delete transaction;
}

void CSScheduleDao::updateRTaskAndSendAddrStatus(const QString &taskUUID, const QStringList &nodes, const quint8 &state)
{
    //错误描述需要清空
    bool fly = Environment::Db_Transaction_State::TRANS_FAIL;
    QString sql = "update CS_R_SCHEDULE_SEND_ADDR set STATE=:state,ERROR=:error where TASK_UUID=:taskUUID and CLIENT_UUID in(:uuids)";
    //查询任务状态
    QString sqlForState = "select * from CS_R_SCHEDULE_TASK where UUID =:taskUUID";
    //修改任务状态
    QString sqlForTask = "update CS_R_SCHEDULE_TASK set STATE = :taskState,SEND_TIME =:sendTime where UUID = :taskUUID";
    QVariantMap params;
    params.insert("uuids",(QVariant)nodes);
    params["taskUUID"] = taskUUID;
    params["state"] = state;
    params["error"] = "";
    params["taskState"] = Task_State::USABLE;
    //TODO
    QString currtime;currtime.clear();
    TimerUtil::toString(currtime);
    params["sendTime"] = currtime;
    //必须try...catch才能回滚和提交
    DBTransaction *transaction = new DBTransaction;
    try
    {
        transaction->beginTransaction();
        fly = transaction->execSQL(sql,params);
        if(fly == Environment::Db_Transaction_State::TRANS_SUCCESS)
        {
            //如果地址任务修改为可用才去修改 任务状态进行扫描
            if(state == SendAddr_State::USABLE) {
                DBQuery query;
                CsRScheduleTask task = query.uniqueBean(mapToRScheduleTask, sqlForState,params);
                quint8 taskState = task.getState();
                if(taskState == Task_State::DOWNERROR ||
                        taskState == Task_State::SENDERROR ||
                        taskState == Task_State::TASKERROR||
                        taskState == Task_State::EXECERROR)
                {
                    fly = transaction->execSQL(sqlForTask,params);
                    if(fly == Environment::Db_Transaction_State::TRANS_SUCCESS) {
                        transaction->commit();
                        delete transaction;
                    }
                    else {
                        DBException excep;
                        excep.setType(QSqlError::TransactionError);
                        excep.setText(trs("update error"));
                        throw excep;
                    }
                }
            }
        }
        else
        {
            DBException excep;
            excep.setType(QSqlError::TransactionError);
            excep.setText(trs("update error"));
            throw excep;
        }
    }
    catch(DBException &ex)
    {
        transaction->rollback();
        throw ex;
        delete transaction;
    }
}

void CSScheduleDao::updateRTaskAndSendAddrStatus(const QString &taskUUID, const quint8 &taskState, const QString &clientUUID, const quint8 &addrState, const QString &addrError)
{
    bool fly = Environment::Db_Transaction_State::TRANS_FAIL;
    QString tasksql = "update CS_R_SCHEDULE_TASK set STATE =:state where UUID =:uuid";

    QVariantMap params;
    params["uuid"]       = taskUUID;
    params["state"] = taskState;
    //必须try...catch才能回滚和提交
    DBTransaction *transaction = new DBTransaction;
    try
    {
        transaction->beginTransaction();
        fly = transaction->execSQL(tasksql,params);
        if(fly == Environment::Db_Transaction_State::TRANS_SUCCESS)
        {
            QString addrsql = "update CS_R_SCHEDULE_SEND_ADDR set STATE =:state,ERROR =:error where TASK_UUID =:taskUUID and CLIENT_UUID =:clientUUID";
            QVariantMap addrparams;
            addrparams["taskUUID"]       = taskUUID;
            addrparams["clientUUID"]       = clientUUID;
            addrparams["state"] = addrState;
            addrparams["error"] = addrError;
            fly = transaction->execSQL(addrsql,addrparams);
            if(fly == Environment::Db_Transaction_State::TRANS_SUCCESS)
            {
                transaction->commit();
            }
            else
            {
                goto err;
            }
        }
        else
        {
err:;
            DBException excep;
            excep.setType(QSqlError::TransactionError);
            excep.setText(trs("update error"));
            throw excep;
        }
    }
    catch(DBException &ex)
    {
        transaction->rollback();
        throw ex;
    }
    delete transaction;
}

void CSScheduleDao::updateRSendAddrByTaskUUID(const QString &taskUUID, const QString &clientUUID, const quint8 &state, const QString &clientError)
{
    bool fly = Environment::Db_Transaction_State::TRANS_FAIL;
    QString sql = "update CS_R_SCHEDULE_SEND_ADDR set STATE =:state,ERROR =:error where TASK_UUID =:taskUUID and CLIENT_UUID =:clientUUID";

    QVariantMap params;
    params["taskUUID"]       = taskUUID;
    params["clientUUID"] = clientUUID;
    params["state"] = state;
    params["error"] = clientError;
    //必须try...catch才能回滚和提交
    DBTransaction *transaction = new DBTransaction;
    try
    {
        transaction->beginTransaction();
        fly = transaction->execSQL(sql,params);
        if(fly == Environment::Db_Transaction_State::TRANS_SUCCESS)
        {
            transaction->commit();
        }
        else
        {
            DBException excep;
            excep.setType(QSqlError::TransactionError);
            excep.setText(trs("update error"));
            throw excep;
        }
    }
    catch(DBException &ex)
    {
        transaction->rollback();
        throw ex;
    }
    delete transaction;
}

QList<CsRScheduleSendFiles> CSScheduleDao::dirRSendFilesByTaskUUID(const QString &taskUUID)
{
    QString sql = "select * from CS_R_SCHEDULE_SEND_FILES WHERE TASK_UUID =:taskUUID";
    QVariantMap params;
    params["taskUUID"]       = taskUUID;
    DBQuery query;
    return query.listBeans(mapToRScheduleTaskSendFile, sql,params);
}

void CSScheduleDao::updateRTaskAndAllSendAddr(const QString &taskUUID, const quint8 &taskNewState,
                                              const quint8 &taskOldState, const QString &taskOperaSymbol,
                                              const quint8 &newAddrState, const quint8 &oldAddrState,
                                              const QString &addrOperaSymbol, const QString &addrError)
{
    bool fly = Environment::Db_Transaction_State::TRANS_FAIL;
    QString tasksql = "update CS_R_SCHEDULE_TASK set STATE =:newstate where UUID =:uuid and STATE "+taskOperaSymbol+":oldstate";

    QVariantMap params;
    params["uuid"]       = taskUUID;
    params["newstate"] = taskNewState;
    params["oldstate"] = taskOldState;
    //必须try...catch才能回滚和提交
    DBTransaction *transaction = new DBTransaction;
    try
    {
        transaction->beginTransaction();
        fly = transaction->execSQL(tasksql,params);
        if(fly == Environment::Db_Transaction_State::TRANS_SUCCESS)
        {
            QString addrsql = "update CS_R_SCHEDULE_SEND_ADDR set STATE =:newAddrState,ERROR =:error where TASK_UUID =:taskUUID and STATE "+addrOperaSymbol + ":oldAddrState";
            QVariantMap addrparams;
            addrparams["taskUUID"]       = taskUUID;
            addrparams["oldAddrState"] = oldAddrState;
            addrparams["newAddrState"] = newAddrState;
            addrparams["error"] = addrError;
            fly = transaction->execSQL(addrsql,addrparams);
            if(fly == Environment::Db_Transaction_State::TRANS_SUCCESS)
            {
                transaction->commit();
            }
            else
            {
                goto err;
            }
        }
        else
        {
err:;
            DBException excep;
            excep.setType(QSqlError::TransactionError);
            excep.setText(trs("update error"));
            throw excep;
        }
    }
    catch(DBException &ex)
    {
        transaction->rollback();
        throw ex;
    }
    delete transaction;
}

void CSScheduleDao::updateRTaskAndAddr(const QString &taskUUID, const quint8 &taskOldState,
                                       const quint8 &taskNewState, const QString &taskOperaSymbol,
                                       const QString &clientUUID, const quint8 &addrState,
                                       const QString &addrError)
{
    bool fly = Environment::Db_Transaction_State::TRANS_FAIL;
    QString tasksql = "update CS_R_SCHEDULE_TASK set STATE =:newstate where UUID =:uuid and STATE "+taskOperaSymbol+":oldstate";

    QVariantMap params;
    params["uuid"]       = taskUUID;
    params["newstate"] = taskNewState;
    params["oldstate"] = taskOldState;
    //必须try...catch才能回滚和提交
    DBTransaction *transaction = new DBTransaction;
    try
    {
        transaction->beginTransaction();
        fly = transaction->execSQL(tasksql,params);
        if(fly == Environment::Db_Transaction_State::TRANS_SUCCESS)
        {
            QString addrsql = "update CS_R_SCHEDULE_SEND_ADDR set STATE =:state,ERROR =:error where TASK_UUID =:taskUUID and CLIENT_UUID =:clientUUID";
            QVariantMap addrparams;
            addrparams["taskUUID"]       = taskUUID;
            addrparams["state"] = addrState;
            addrparams["error"] = addrError;
            addrparams["clientUUID"] = clientUUID;
            fly = transaction->execSQL(addrsql,addrparams);
            if(fly == Environment::Db_Transaction_State::TRANS_SUCCESS)
            {
                transaction->commit();
            }
            else
            {
                goto err;
            }
        }
        else
        {
err:;
            DBException excep;
            excep.setType(QSqlError::TransactionError);
            excep.setText(trs("update error"));
            throw excep;
        }
    }
    catch(DBException &ex)
    {
        transaction->rollback();
        throw ex;
    }
    delete transaction;
}

void CSScheduleDao::getRTaskUuidByTaskNum(QString &taskUUID, const quint32 &taskNum)
{
    QString sql = "select UUID from CS_R_SCHEDULE_TASK WHERE TASK_NUM =:taskNum";
    QVariantMap params;
    params["taskNum"]       = taskNum;
    DBQuery query;
    taskUUID = query.selectVariant(sql, params).toString();
}

void CSScheduleDao::getErrorMsgByState(const quint8 &taskState, QString &errorMsg)
{
    switch (taskState) {
    //报文类型为空
    case State::_2:
        errorMsg = State::_2_DESC_DatagramTypeIsNull;
        break;
        //报文类型不匹配
    case State::_3:
        errorMsg = State::_3_DESC_DatagramUnmatched;
        break;
        //固定码为空
    case State::_4:
        errorMsg = State::_4_DESC_UUIDIsNull;
        break;
        //请求码为空
    case State::_5:
        errorMsg = State::_5_DESC_RequestIDIsNull;
        break;
        //任务编号为空
    case State::_6:
        errorMsg = State::_6_DESC_TaskNumIsNull;
        break;
        //执行策略为空
    case State::_7:
        errorMsg = State::_7_DESC_StrategyIsNull;
        break;
        //执行时刻为空
    case Sche_Data_Trans::Resp_Info_State::_8:
        errorMsg = Sche_Data_Trans::Resp_Info_State::_8_DESC_ExecTimeIsNull;
        break;
        //执行时刻不符合日期格式yyyy-mm-dd hh:mm:ss
    case Sche_Data_Trans::Resp_Info_State::_9:
        errorMsg = Sche_Data_Trans::Resp_Info_State::_9_DESC_ExecTimeFormatError;
        break;
        //入口文件保存路径为空
    case Sche_Data_Trans::Resp_Info_State::_A:
        errorMsg = Sche_Data_Trans::Resp_Info_State::_A_DESC_SaveAbstIsNull;
        break;
        //解析文件下载地址失败
    case Sche_Data_Trans::Resp_Info_State::_B:
        errorMsg = Sche_Data_Trans::Resp_Info_State::_B_DESC_ParseFileDownLoadAddrFail;
        break;
        //解析文件保存地址失败
    case Sche_Data_Trans::Resp_Info_State::_C:
        errorMsg = Sche_Data_Trans::Resp_Info_State::_C_DESC_ParseFileSaveAddrFail;
        break;
        //创建结构化任务入库失败
    case Sche_Data_Trans::Resp_Info_State::_D:
        errorMsg = Sche_Data_Trans::Resp_Info_State::_D_DESC_DBTransactionFail;
        break;
    default:
        break;
    }
}

void CSScheduleDao::updateRTaskErrorInfo(const QString &taskUUID, const quint8 &taskState,
                                         const quint8 &addrState, const QString &addrError,
                                         const QVector<Result *> &Errors)
{
    bool fly = Environment::Db_Transaction_State::TRANS_FAIL;
    QString tasksql = "update CS_R_SCHEDULE_TASK set STATE =:state where UUID =:uuid";

    QVariantMap params;
    params["uuid"]       = taskUUID;
    params["state"] = taskState;
    //必须try...catch才能回滚和提交
    DBTransaction *transaction = new DBTransaction;
    try
    {
        transaction->beginTransaction();
        fly = transaction->execSQL(tasksql,params);
        if(fly == Environment::Db_Transaction_State::TRANS_SUCCESS)
        {
            QString addrsql = "update CS_R_SCHEDULE_SEND_ADDR set STATE =:state, ERROR =:error where TASK_UUID =:taskUUID";
            QVariantMap addrparams;
            addrparams["taskUUID"]       = taskUUID;
            addrparams["state"] = addrState;
            addrparams["error"] = addrError;
            fly = transaction->execSQL(addrsql,addrparams);
            if(fly == Environment::Db_Transaction_State::TRANS_SUCCESS)
            {
                if(Errors.size()<=0)
                {
                    transaction->commit();
                    return;
                }
                QString sendStatussql = "UPDATE ";
                sendStatussql += "CS_R_SCHEDULE_SEND_STATUS ";
                sendStatussql += "SET ";
                sendStatussql += "ERROR = :error ";
                sendStatussql += "WHERE TASK_UUID IN ";
                sendStatussql += "(SELECT ";
                sendStatussql += "UUID ";
                sendStatussql += "FROM ";
                sendStatussql += "CS_R_SCHEDULE_SEND_FILES ";
                sendStatussql += "WHERE DOWN_URL = :downloadURL ";
                sendStatussql += "AND TASK_UUID = :taskUUID) ";
                QVariantMap sendStatusparams;
                for(Result *err :Errors)
                {
                    sendStatusparams.clear();
                    sendStatusparams["error"]       = err->backMsg;
                    sendStatusparams["downloadURL"] = err->DownloadURLs;
                    sendStatusparams["taskUUID"] = taskUUID;
                    fly = transaction->execSQL(sendStatussql,sendStatusparams);
                    if(fly == Environment::Db_Transaction_State::TRANS_FAIL)
                    {
                        goto err;
                    }

                }
                if(fly == Environment::Db_Transaction_State::TRANS_SUCCESS)
                {
                    transaction->commit();
                }
            }
            else
            {
                goto err;
            }
        }
        else
        {
err:;
            DBException excep;
            excep.setType(QSqlError::TransactionError);
            excep.setText(trs("update error"));
            throw excep;
        }
    }
    catch(DBException &ex)
    {
        transaction->rollback();
        throw ex;
    }
    delete transaction;
}

void CSScheduleDao::getRTaskStateByTaskUUID(const QString &taskUUID, quint8 &state)
{
    QString sql = "select STATE from CS_R_SCHEDULE_TASK where UUID=:taskUUID";

    QVariantMap params;
    params["taskUUID"]       = taskUUID;
    DBQuery query;
    state = (quint8)(query.selectVariant(sql, params).toUInt());
}

void CSScheduleDao::moveRTask2STask(const QString &taskUUID)
{
    /*
INSERT INTO CS_S_SCHEDULE_SEND_FILES (SELECT * FROM CS_R_SCHEDULE_SEND_FILES WHERE UUID=:o_id)
DELETE FROM CS_R_SCHEDULE_TASK WHERE UUID=:o_id
INSERT INTO CS_S_SCHEDULE_TASK (SELECT * FROM CS_R_SCHEDULE_TASK WHERE UUID=:o_id)
DELETE FROM CS_R_SCHEDULE_SEND_FILES WHERE UUID=:o_id
INSERT INTO CS_S_SCHEDULE_SEND_ADDR (SELECT * FROM CS_R_SCHEDULE_SEND_ADDR WHERE UUID=:o_id)
DELETE FROM CS_R_SCHEDULE_SEND_ADDR WHERE UUID=:o_id
    */
    bool fly = Environment::Db_Transaction_State::TRANS_FAIL;
    QString sql_insert_stask = "INSERT INTO CS_S_SCHEDULE_TASK (SELECT * FROM CS_R_SCHEDULE_TASK WHERE UUID=:o_id)";
    QString sql_delete_rtask = "DELETE FROM CS_R_SCHEDULE_TASK WHERE UUID=:o_id";
    QString sql_insert_sfile = "INSERT INTO CS_S_SCHEDULE_SEND_FILES (SELECT * FROM CS_R_SCHEDULE_SEND_FILES WHERE TASK_UUID=:o_id)";
    QString sql_delete_rfile = "DELETE FROM CS_R_SCHEDULE_SEND_FILES WHERE TASK_UUID=:o_id";
    QString sql_insert_saddr = "INSERT INTO CS_S_SCHEDULE_SEND_ADDR (SELECT * FROM CS_R_SCHEDULE_SEND_ADDR WHERE TASK_UUID=:o_id)";
    QString sql_delete_raddr = "DELETE FROM CS_R_SCHEDULE_SEND_ADDR WHERE TASK_UUID=:o_id";
    QVariantMap params;
    params["o_id"] = taskUUID;

    DBTransaction *transaction = new DBTransaction;
    try
    {
        DBException excep;
        transaction->beginTransaction();
        fly = transaction->execSQL(sql_insert_stask,params);
        if(fly == Environment::Db_Transaction_State::TRANS_SUCCESS)
        {
            fly = transaction->execSQL(sql_delete_rtask,params);
            if(fly == Environment::Db_Transaction_State::TRANS_SUCCESS)
            {
                fly = transaction->execSQL(sql_insert_sfile,params);
                if(fly == Environment::Db_Transaction_State::TRANS_SUCCESS)
                {
                    fly = transaction->execSQL(sql_delete_rfile,params);
                    if(fly == Environment::Db_Transaction_State::TRANS_SUCCESS)
                    {
                        fly = transaction->execSQL(sql_insert_saddr,params);
                        if(fly == Environment::Db_Transaction_State::TRANS_SUCCESS)
                        {
                            fly = transaction->execSQL(sql_delete_raddr,params);
                            if(fly == Environment::Db_Transaction_State::TRANS_SUCCESS)
                            {
                                transaction->commit();
                                qDebug() << trs("moveRTask2STask成功");
                                delete transaction;
                                return;
                            }
                            else
                            {
                                excep.setText(trs("sql_delete_raddr error"));
                                goto RollBack;
                            }
                        }
                        else
                        {
                            excep.setText(trs("sql_insert_saddr error"));
                            goto RollBack;
                        }
                    }
                    else
                    {
                        excep.setText(trs("sql_delete_rfile error"));
                        goto RollBack;
                    }
                }
                else
                {
                    excep.setText(trs("sql_insert_sfile error"));
                    goto RollBack;
                }
            }
            else
            {
                excep.setText(trs("sql_delete_rtask error"));
                goto RollBack;
            }
        }
        else
        {
            excep.setText(trs("sql_insert_stask error"));
            goto RollBack;
        }
RollBack:
        transaction->rollback();
        excep.setType(QSqlError::TransactionError);
        throw excep;
    }
    catch(DBException &ex)
    {
        qDebug() << ex.getText();
        transaction->rollback();
        //        qDebug() << excep.getText();
        //既然try...catch,就捕获异常做处理,如果不try...catch,自动回退直到找到try...catch
        delete transaction;
        throw ex;
    }
}

CsRScheduleTask CSScheduleDao::mapToRScheduleTask(const QVariantMap &rowMap)
{
    CsRScheduleTask task;
    task.setUuid(rowMap.value("UUID").toString());
    task.setTaskName(rowMap.value("TASK_NAME").toString());
    task.setTaskNum(rowMap.value("TASK_NUM").toUInt());
    task.setDescription(rowMap.value("DESCRIPTION").toString());
    task.setSendTime(rowMap.value("SEND_TIME").toString());
    task.setExecTime(rowMap.value("EXEC_TIME").toString());
    task.setStrategy((quint16)(rowMap.value("STRATEGY").toUInt()));
    task.setState((quint8)rowMap.value("STATE").toUInt());
    task.setSaveAbst(rowMap.value("SAVE_ABST").toString());
    task.setInsertor(rowMap.value("INSERTOR").toString());
    task.setInsertTime(rowMap.value("INSERT_TIME").toString());
    task.setOperater(rowMap.value("OPERATOR").toString());
    task.setOperaTime(rowMap.value("OPERA_TIME").toString());
    return task;
}

CsRScheduleSendFiles CSScheduleDao::mapToRScheduleTaskSendFile(const QVariantMap &rowMap)
{
    CsRScheduleSendFiles sendFile;
    sendFile.setUuid(rowMap.value("UUID").toString());
    sendFile.setFileName(rowMap.value("FILE_NAME").toString());
    sendFile.setDownUrl(rowMap.value("DOWN_URL").toString());
    sendFile.setFileDestName(rowMap.value("FILE_DEST_NAME").toString());
    sendFile.setSaveAbst(rowMap.value("SAVE_ABST").toString());
    sendFile.setTaskUuid(rowMap.value("TASK_UUID").toString());
    return sendFile;
}

CsRScheduleSendAddr CSScheduleDao::mapToRScheduleTaskSendAddr(const QVariantMap &rowMap)
{
    CsRScheduleSendAddr addr;
    addr.setUuid(rowMap.value("UUID").toString());
    addr.setClientUuid(rowMap.value("CLIENT_UUID").toString());
    addr.setState((quint8)rowMap.value("STATE").toUInt());
    addr.setError(rowMap.value("ERROR").toString());
    addr.setTaskUuid(rowMap.value("TASK_UUID").toString());
    return addr;
}

VCsAScSendFiles CSScheduleDao::mapToRScheduleVFile(const QVariantMap &rowMap)
{
    VCsAScSendFiles vFile;
    vFile.setUuid(rowMap.value("UUID").toString());
    vFile.setFileName(rowMap.value("FILE_NAME").toString());
    vFile.setDownUrl(rowMap.value("DOWN_URL").toString());
    vFile.setFileDestName(rowMap.value("FILE_DEST_NAME").toString());
    vFile.setSaveAbst(rowMap.value("SAVE_ABST").toString());
    vFile.setTaskUuid(rowMap.value("TASK_UUID").toString());
    vFile.setState((quint8)rowMap.value("STATE").toInt());
    vFile.setErrMsg(rowMap.value("ERRMSG").toString());
    return vFile;
}

