#include "csunstructdao.h"
using namespace Environment::Datagram;
using namespace Environment::Task_Status::Center::Unstru;

CsRUnstructTask CSUnstructDao::getTaskByUUID(const QString &taskUUID)
{
    QString tasksql = "select * from CS_R_UNSTRUCT_TASK where uuid =:id";
    QVariantMap params;
    params["id"] = taskUUID;
    DBQuery dbquery;
    return dbquery.uniqueBean(mapToRUnstructTask,tasksql,params);
}

QList<CsRUnstructTask> CSUnstructDao::listTask(const QString &taskUUID,const quint8 state)
{
    QString tasksql = "select * from CS_R_UNSTRUCT_TASK where State =:state and uuid in (:uuid)";

    QVariantMap params;
    params["uuid"] = taskUUID;
    params["state"] = state;
    DBQuery dbquery;
    return dbquery.listBeans(mapToRUnstructTask,tasksql,params);
}

QList<CsRUnstructSendAddr> CSUnstructDao::dirRSendAddr(const QString &taskUuid, const QStringList &uuids)
{
    QString sql = "select * from CS_R_UNSTRUCT_SEND_ADDR where task_uuid =:taskuuid and client_uuid IN (:uuids)";
    QVariantMap params;
    params["taskuuid"] = taskUuid;
    params.insert("uuids", (QVariant)uuids);
    DBQuery query;
    return query.listBeans(mapToRUnstructTaskSendAddr,sql,params);
}

void CSUnstructDao::addRSendAddr(const QString &taskUuid, const QStringList &uuids,const QStringList &groupDes)
{
    QString sql = "INSERT INTO CS_R_UNSTRUCT_SEND_ADDR values(:uuid,:clientuuid,:taskuuid,:groupUuids)";
    QString sqlForStatus = "insert into CS_R_UNSTRUCT_SEND_STATUS values(:statusUuid,:clientuuid,:SEND_FILE_UUID,:ERROR,:taskuuid,:uuid,:STATE)";
    QString sqlForFile = "select * from CS_R_UNSTRUCT_SEND_FILES where TASK_UUID  = :taskuuid";
    QVariantMap params;
    bool ok;
    QString uuid;uuid.clear();
    UuidUtil::nextUUID(uuid);
    params["taskuuid"] = taskUuid;
    params["STATE"] = SendStatus_State::USABLE;

    DBQuery dbquery;
    QList<CsRUnstructSendFiles> fileList =  dbquery.listBeans(mapToRUnstructTaskSendFile,sqlForFile,params);

    DBTransaction* transaction = new DBTransaction;
    transaction->beginTransaction();
    int i= 0;
    for(i =0 ;i < uuids.size();++i) {
        UuidUtil::nextUUID(uuid);
        params["uuid"] = uuid;
        params["clientuuid"] = uuids.at(i);
        params["groupUuids"] = groupDes.at(i);
        ok = transaction->execSQL(sql,params);

        if(!ok) {
            goto end;
        }
        for(int i = 0;i < fileList.size(); ++i ) {
            CsRUnstructSendFiles file = fileList.at(i);
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

CsRUnstructSendAddr CSUnstructDao::dirRSendAddrsByTaskUUIDandUUID(const QString &taskUUID, const QString &clientUUID)
{
    QString sql = "select * from CS_R_UNSTRUCT_SEND_ADDR where task_uuid =:taskuuid and client_uuid =:clientuuid";
    QVariantMap params;
    params["taskuuid"] = taskUUID;
    params["clientuuid"] = clientUUID;
    DBQuery query;
    return query.uniqueBean(mapToRUnstructTaskSendAddr,sql,params);
}

void CSUnstructDao::delTaskNode(const QString &taskUUID, const QStringList &nodes)
{
    QString sql = "DELETE CS_R_UNSTRUCT_SEND_ADDR where TASK_UUID =:taskuuid and CLIENT_UUID IN (:nodes)";
    QString sqlForStatus = "DELETE CS_R_UNSTRUCT_SEND_STATUS where TASK_UUID =:taskuuid and CLIENT_UUID IN (:nodes)";
    QVariantMap params;
    params["taskuuid"] = taskUUID;
    params.insert("nodes", (QVariant)nodes);
    bool ok;
    DBTransaction* transaction = new DBTransaction;
    transaction->beginTransaction();
    try{
        ok = transaction->execSQL(sql,params);
        if(!ok) {
            DBException execp;
            execp.setText(trs("删除数据错误"));
            execp.setType(QSqlError::TransactionError);
            throw execp;

        }
        else {
            ok = transaction->execSQL(sqlForStatus,params);
            if(!ok) {
                DBException execp;
                execp.setText(trs("删除数据错误"));
                execp.setType(QSqlError::TransactionError);
                throw execp;
            }
            else {
                transaction->commit();
                delete transaction;
            }
        }
    }
    catch(DBException &ex) {
        transaction->rollback();
        delete transaction;
        throw ex;
    }
}

QList<CsRUnstructSendFiles> CSUnstructDao::dirRSendFiles(const QString &taskUuid, const QStringList &uuids)
{
    QString sql = "select * from CS_R_UNSTRUCT_SEND_FILES where TASK_UUID =:taskuuid and FILE_DEST_NAME IN (:uuids)";
    QVariantMap params;
    params["taskuuid"] = taskUuid;
    params.insert("uuids", (QVariant)uuids);
    DBQuery query;
    return query.listBeans(mapToRUnstructTaskSendFile,sql,params);
}

CsRUnstructSendFiles CSUnstructDao::dirRSendFilesByTaskUUIDandFileName(const QString &taskUUID, const QString &fileName)
{
    QString sql = "select * from CS_R_UNSTRUCT_SEND_FILES where task_uuid =:taskuuid and file_name =:filename";
    QVariantMap params;
    params["taskuuid"] = taskUUID;
    params["filename"] = fileName;
    DBQuery query;
    return query.uniqueBean(mapToRUnstructTaskSendFile,sql,params);
}

QList<CsRUnstructSendStatus> CSUnstructDao::pageRSendStatusByTaskUuidAndClientUuid(const QString &taskUuid, const QString &clientUuid,QStringList &paramsList,Page* page)
{
    QString sql = "select * from (SELECT s.*,f.FILE_NAME FROM CS_R_UNSTRUCT_SEND_STATUS s,CS_R_UNSTRUCT_SEND_FILES f"
                  " WHERE s.SEND_FILE_UUID = f.UUID"
                  " AND s.TASK_UUID =:taskUuid"
                  " AND s.CLIENT_UUID =:clientUuid)";
    //order by
    sql.append(QString(" order by %1 %2")//order by column1 desc/asc
               .arg(!(page->getOrderFieldName().isEmpty()) ? page->getOrderFieldName() : "CLIENT_UUID")
               .arg(page->getOrderField() == Qt::DescendingOrder?"DESC":"ASC")
               );
    QVariantMap params;
    params["taskUuid"] = taskUuid;
    params["clientUuid"] = clientUuid;
    DBQuery query;
    QList<QVariantMap> list =  query.pageList(page,sql,params);
    QList<CsRUnstructSendStatus> statusList;
    for(int i = 0;i < list.size(); ++i) {
        QVariantMap rowMap = list.at(i);
        CsRUnstructSendStatus status = mapToRUnstructTaskSendStatus(rowMap);
        statusList.append(status);
        paramsList << rowMap.value("FILE_NAME").toString();
    }
    return statusList;
}

QList<CsRUnstructSendStatus> CSUnstructDao::pageRSendStatusByTaskUuidAndSendFileUUid(const QString &taskUuid, const QString &fileUuids, QStringList &paramsList,Page* page)
{
    QString sql = "select * from (SELECT s.*,n.description,r.group_uuids FROM CS_R_UNSTRUCT_SEND_STATUS s,CS_CLIENT_TERMINAL n,cs_r_unstruct_send_addr r"
            " WHERE s.CLIENT_UUID = n.TERMINAL_UUID"
            " AND s.TASK_UUID =:taskUuid"
            " AND S.SEND_FILE_UUID =:fileUuid"
            " AND R.UUID = S.SEND_ADDR_UUID)";
    //order by
    sql.append(QString(" order by %1 %2")//order by column1 desc/asc
               .arg(!(page->getOrderFieldName().isEmpty()) ? page->getOrderFieldName() : "UUID")
               .arg(page->getOrderField() == Qt::DescendingOrder?"DESC":"ASC")
               );
    QVariantMap params;
    params["taskUuid"] = taskUuid;
    params["fileUuid"] = fileUuids;
    DBQuery query;
    QList<QVariantMap> list =  query.pageList(page,sql,params);
    QList<CsRUnstructSendStatus> statusList;
    for(int i = 0;i < list.size(); ++i) {
        QVariantMap rowMap = list.at(i);
        CsRUnstructSendStatus status = mapToRUnstructTaskSendStatus(rowMap);
        statusList.append(status);
        paramsList << rowMap.value("DESCRIPTION").toString();
    }
    //TODO 这里有BUG
    for(int i = 0;i < list.size(); ++i) {
        QVariantMap rowMap = list.at(i);
        paramsList << rowMap.value("GROUP_UUIDS").toString();
    }
    return statusList;
}

void CSUnstructDao::delTaskFile(const QString &taskUUID, const QStringList &uuidList)
{
    QString sql = "DELETE CS_R_UNSTRUCT_SEND_STATUS where TASK_UUID =:taskuuid and SEND_FILE_UUID IN (:uuidList)";
    QVariantMap params;
    bool ok;
    params["taskuuid"] = taskUUID;
    params.insert("uuidList", (QVariant)uuidList);
    DBTransaction* transaction = new DBTransaction;
    transaction->beginTransaction();
    ok = transaction->execSQL(sql,params);
    if(!ok) {
        goto end;
    }
    sql = "DELETE CS_R_UNSTRUCT_SEND_FILES where uuid IN (:uuidList)";
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
    excep.setType(QSqlError::TransactionError);
    excep.setText(trs("删除数据错误"));
    throw excep;

}

QList<CsRUnstructTask> CSUnstructDao::pageTask(const QVariantMap &map, Page *page)
{
    QString sql = "SELECT * "
                  "FROM "
                  "( SELECT * FROM CS_R_UNSTRUCT_TASK "
                  "UNION ALL "
                  "SELECT * FROM CS_S_UNSTRUCT_TASK "
                  ") "
                  "WHERE 1 =1";
    QVariantMap params;
    if(!map.value("taskname").toString().isEmpty()) {
        QString str = "%";
        str.append(map.value("taskname").toString()).append("%");
        params["taskname"] = str;
        sql.append(" and upper(TASK_NAME) LIKE upper(:taskname)");
    }
    if(!map.value("insertor").toString().isEmpty()) {
        QString str = "%";
        str.append(map.value("insertor").toString()).append("%");
        params["insertor"] = str;
        sql.append(" and upper(INSERTOR) LIKE upper(:insertor)");
    }
    if(!map.value("strategy").isNull()){
        params["strategy"] = (quint16)map.value("strategy").toInt();
        sql.append(" and STRATEGY =:strategy");
    }
    if(!map.value("state").isNull()){
        params["state"] =(quint8) map.value("state").toInt();
        sql.append(" and STATE =:state");
    }
    if(!map.value("sendtime").toString().isEmpty()) {
        params["sendtime"] = map.value("sendtime").toString();
        sql.append(" and SEND_TIME =:sendtime");
    }
    if(!map.value("send_time_begin").toString().isEmpty())
    {
        params["send_time_begin"] = map.value("send_time_begin");
        sql.append(" and SEND_TIME >=:send_time_begin");
    }
    if(!map.value("send_time_end").toString().isEmpty())
    {
        params["send_time_end"] = map.value("send_time_end");
        sql.append(" and SEND_TIME <=:send_time_end");
    }
    //order by
    sql.append(QString(" order by %1 %2")//order by column1 desc/asc
               .arg(!(page->getOrderFieldName().isEmpty()) ? page->getOrderFieldName() : "SEND_TIME")
               .arg(page->getOrderField() == Qt::DescendingOrder?"DESC":"ASC")
               );
    DBQuery query;
    return query.pageBean(mapToRUnstructTask,page,sql,params);

}

QList<CsRUnstructTask> CSUnstructDao::listTask(const QVariantMap &map)
{
    QString sql = "select * from CS_R_UNSTRUCT_TASK WHERE 1 = 1";

    QVariantMap params;
    if(!map.value("taskname").toString().isEmpty()) {
        QString str = "%";
        str.append(map.value("taskname").toString()).append("%");
        params["taskname"] = str;
        sql.append(" and upper(TASK_NAME) LIKE upper(:taskname)");
    }
    if(!map.value("insertor").toString().isEmpty()) {
        QString str = "%";
        str.append(map.value("insertor").toString()).append("%");
        params["insertor"] = str;
        sql.append(" and upper(INSERTOR) LIKE upper(:insertor)");
    }
    if(!map.value("strategy").isNull()){
        params["strategy"] = (quint16)map.value("strategy").toInt();
        sql.append(" and STRATEGY =:strategy");
    }
    if(!map.value("state").isNull()){
        params["state"] =(quint8) map.value("state").toInt();
        sql.append(" and STATE =:state");
    }
    if(!map.value("sendtime").toString().isEmpty()) {
        params["sendtime"] = map.value("sendtime").toString();
        sql.append(" and SEND_TIME =:sendtime");
    }
    params["send_time_begin"] = map.value("send_time_begin");
    params["send_time_end"] = map.value("send_time_end");
    sql.append(" and SEND_TIME between :send_time_begin and :send_time_end");

    sql.append(" union all ");

    sql.append("select * from CS_S_UNSTRUCT_TASK WHERE 1 = 1");
    if(!map.value("taskname").toString().isEmpty()) {
        QString str = "%";
        str.append(map.value("taskname").toString()).append("%");
        params["s_taskname"] = str;
        sql.append(" and upper(TASK_NAME) LIKE upper(:s_taskname)");
    }
    if(!map.value("insertor").toString().isEmpty()) {
        QString str = "%";
        str.append(map.value("insertor").toString()).append("%");
        params["s_insertor"] = str;
        sql.append(" and upper(INSERTOR) LIKE upper(:s_insertor)");
    }
    if(!map.value("strategy").isNull()){
        params["s_strategy"] = (quint16)map.value("strategy").toInt();
        sql.append(" and STRATEGY =:s_strategy");
    }
    if(!map.value("state").isNull()){
        params["s_state"] =(quint8) map.value("state").toInt();
        sql.append(" and STATE =:s_state");
    }
    params["s_send_time_begin"] = map.value("send_time_begin");
    params["s_send_time_end"] = map.value("send_time_end");
    sql.append(" and SEND_TIME between :s_send_time_begin and :s_send_time_end");
    DBQuery query;
    return query.listBeans(mapToRUnstructTask,sql,params);
}


void CSUnstructDao::addTask(const CsRUnstructTask &task, const QList<CsRUnstructSendAddr> addrInfoList, const QList<CsRUnstructSendFiles> fileInfoList, const QList<CsRUnstructSendStatus> statusInfoList)
{
    bool flg = Environment::Db_Transaction_State::TRANS_FAIL;
    QString sqlForTask = "insert into CS_R_UNSTRUCT_TASK values(:UUID,:TASK_NAME,:TASK_NUM,:DESCRIPTION,:SEND_TIME,:STRATEGY,:STATE,:INSERTOR,:INSERT_TIME,:OPERATOR,:OPERA_TIME)";
    QString sqlForTaskAddr = "insert into CS_R_UNSTRUCT_SEND_ADDR values(:UUID,:CLIENT_UUID,:TASK_UUID,:GROUP_UUIDS)";
    QString sqlForTaskFile = "insert into CS_R_UNSTRUCT_SEND_FILES values(:UUID,:FILE_NAME,:DOWN_URL,:FILE_DEST_NAME,:SAVE_ABST,:TASK_UUID,:HARD_ABST,:FILE_SRC)";
    QString sqlForTaskStatus = "insert into CS_R_UNSTRUCT_SEND_STATUS values(:UUID,:CLIENT_UUID,:SEND_FILE_UUID,:ERROR,:TASK_UUID,:SEND_ADDR_UUID,:STATE)";
    QVariantMap params;
    params["UUID"] = task.getUuid();
    params["TASK_NAME"] = task.getTaskName();
    params["TASK_NUM"] = task.getTaskNum();
    params["DESCRIPTION"] = task.getDescription();
    params["SEND_TIME"] = task.getSendTime();
    params["STRATEGY"] = task.getStrategy();
    params["STATE"] = task.getState();
    params["INSERTOR"] = task.getInsertor();
    params["INSERT_TIME"] = task.getInsertTime();
    params["OPERATOR"] = task.getOperater();
    params["OPERA_TIME"] = task.getOperaTime();

    //必须try...catch才能回滚和提交
    DBTransaction *transaction = new DBTransaction;

    transaction->beginTransaction();
    flg = transaction->execSQL(sqlForTask,params);
    if(flg == Environment::Db_Transaction_State::TRANS_FAIL)
    {
        goto err;
    }
    params.clear();
    for(int i = 0;i < addrInfoList.size(); ++i) {
        CsRUnstructSendAddr addr = addrInfoList.at(i);
        params["UUID"] = addr.getUuid();
        params["CLIENT_UUID"]=addr.getClientUuid();
        params["GROUP_UUIDS"]=addr.getGroupDesc();
        params["TASK_UUID"]=addr.getTaskUuid();
        flg = transaction->execSQL(sqlForTaskAddr,params);
        if(flg == Environment::Db_Transaction_State::TRANS_FAIL)
        {
            goto err;
        }
    }
    params.clear();
    for(int i = 0;i < fileInfoList.size(); ++i) {
        CsRUnstructSendFiles file = fileInfoList.at(i);
        params["UUID"] = file.getUuid();
        params["FILE_NAME"] = file.getFileName();
        params["DOWN_URL"] = file.getDownUrl();
        params["FILE_DEST_NAME"] = file.getFileDestName();
        params["SAVE_ABST"] = file.getSaveAbst();
        params["HARD_ABST"] = file.getHardAbst();
        params["FILE_SRC"] = file.getFileSrc();
        params["TASK_UUID"] = file.getTaskUuid();
        flg = transaction->execSQL(sqlForTaskFile,params);
        if(flg == Environment::Db_Transaction_State::TRANS_FAIL)
        {
            goto err;
        }
    }
    params.clear();
    for(int i = 0;i < statusInfoList.size(); ++i) {
        CsRUnstructSendStatus status = statusInfoList.at(i);
        params["UUID"] = status.getUuid() ;
        params["CLIENT_UUID"] = status.getClientUuid() ;
        params["SEND_FILE_UUID"] = status.getSendFileUuid() ;
        params["ERROR"] = status.getError() ;
        params["SEND_ADDR_UUID"] = status.getSendAddrUuid() ;
        params["TASK_UUID"] = status.getTaskUuid();
        params["STATE"] = status.getState() ;
        flg = transaction->execSQL(sqlForTaskStatus,params);
        if(flg == Environment::Db_Transaction_State::TRANS_FAIL)
        {
            goto err;
        }
    }

    transaction->commit();
    delete transaction;
    return;
err:;
    transaction->rollback();
    delete transaction;
    DBException excep;
    excep.setText(trs("添加数据错误"));
    excep.setType(QSqlError::TransactionError);
    throw excep;

}



void CSUnstructDao::addTaskFile(const QString &taskUuid, const QList<CsRUnstructSendFiles> &fileList,const QList<CsRUnstructSendStatus> &statusList)
{
    bool ok;
    QString sqlForFile = "insert into CS_R_UNSTRUCT_SEND_FILES values(:uuid,:filename,:downurl,:filedestname,:saveabsr,:taskuuid,:hardAbst,:fileSrc)";
    QString sqlForAddr = "insert into CS_R_UNSTRUCT_SEND_STATUS values(:uuid,:clientUuid,:sendFileUuid,:error,:taskuuid,:sendAddrUuid,:state)";
    QVariantMap params;
    QString uuid;uuid.clear();
    DBTransaction *transaction = new DBTransaction;
    transaction->beginTransaction();

    params["taskuuid"] = taskUuid;
    int i = 0;
    for(i = 0;i < fileList.size(); ++i) {
        CsRUnstructSendFiles file = fileList.at(i);
        params["uuid"] = file.getUuid();
        params["filename"] = file.getFileName();
        params["downurl"] = file.getDownUrl();
        params["filedestname"] = file.getFileDestName();
        params["saveabsr"] = file.getSaveAbst();
        params["hardAbst"] = file.getHardAbst();
        params["fileSrc"] = file.getFileSrc();
        ok = transaction->execSQL(sqlForFile,params);
        if(!ok) {
            goto end;
        }
    }
    for(i = 0;i < statusList.size(); ++i) {
        CsRUnstructSendStatus status = statusList.at(i);
        params["uuid"] = status.getUuid();
        params["clientUuid"] = status.getClientUuid();
        params["sendFileUuid"] = status.getSendFileUuid();
        params["error"] = status.getError();
        params["sendAddrUuid"] = status.getSendAddrUuid();
        params["state"] = status.getState();
        ok = transaction->execSQL(sqlForAddr,params);
        if(!ok) {
            goto end;
        }
    }
    transaction->commit();
    delete transaction;
    return;
end:;
    transaction->rollback();
    delete transaction;
    DBException excep;
    excep.setText(trs("添加数据错误"));
    excep.setType(QSqlError::TransactionError);
    throw excep;
}
void CSUnstructDao::addTaskNode(const CsRUnstructSendAddr &task)
{
    bool flg = Environment::Db_Transaction_State::TRANS_FAIL;
    QString addTaskNodeSql = "insert into CS_R_UNSTRUCT_SEND_ADDR(UUID,CLIENT_UUID,STATE,ERROR,TASK_UUID,GROUP_UUIDS)"
                             "values(:UUID,:CLIENT_UUID,:TASK_UUID,:GROUP_UUIDS)";
    qDebug() << addTaskNodeSql;
    QVariantMap params;
    params["UUID"] = task.getUuid();
    params["CLIENT_UUID"]=task.getClientUuid();
    params["GROUP_UUIDS"]=task.getGroupDesc();
    params["TASK_UUID"]=task.getTaskUuid();
    //必须try...catch才能回滚和提交
    DBTransaction *transaction = new DBTransaction;
    try
    {
        transaction->beginTransaction();
        flg = transaction->execSQL(addTaskNodeSql,params);
        if(flg == Environment::Db_Transaction_State::TRANS_SUCCESS)
        {
            transaction->commit();
        }
        else
        {

            DBException excep;
            excep.setType(QSqlError::TransactionError);
            excep.setText("add error");
            throw excep;

        }
    }
    catch(DBException &ex)
    {
        qDebug() << ex.getText();
        transaction->rollback();
        delete transaction;
        throw ex;
    }
    delete transaction;

}
void CSUnstructDao::delTask(const QStringList &uuids )
{

    QVariantMap params;
    bool ok;
    QString sql  = "DELETE CS_R_UNSTRUCT_SEND_STATUS where TASK_UUID in (:uuids)";
    params.insert("uuids", (QVariant)uuids);
    DBTransaction* transaction = new DBTransaction;
    transaction->beginTransaction();
    ok = transaction->execSQL(sql,params);
    if(!ok) {
        goto end;
    }
    sql = "delete CS_R_UNSTRUCT_SEND_FILES where TASK_UUID in (:uuids)";
    ok = transaction->execSQL(sql,params);
    if(!ok) {
        goto end;
    }
    sql = "delete CS_R_UNSTRUCT_SEND_ADDR where TASK_UUID in (:uuids)";
    ok = transaction->execSQL(sql,params);
    if(!ok) {
        goto end;
    }
    sql = "delete CS_R_UNSTRUCT_TASK where UUID in (:uuids)";
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

QList<CsRUnstructSendStatus> CSUnstructDao::dirSendStatusByTaskUuid(const QString &taskUuid)
{
    QString sql = "select * from CS_R_UNSTRUCT_SEND_STATUS where task_uuid =:taskUuid";
    QVariantMap params;
    params["taskUuid"] = taskUuid;
    DBQuery query;
    return query.listBeans(mapToRUnstructTaskSendStatus,sql,params);
}

CsRUnstructTask CSUnstructDao::dirTaskByUUID(const QString &UUID)
{
    QString sql = "select * from CS_R_UNSTRUCT_TASK where uuid =:uuid";
    QVariantMap params;
    params["uuid"] = UUID;
    DBQuery query;
    return query.uniqueBean(mapToRUnstructTask,sql,params);

}

QList<CsRUnstructTask> CSUnstructDao::dirTask()
{
    QString sql = "select * from CS_R_UNSTRUCT_TASK";
    DBQuery  query;
    QVariantMap params;
    return query.listBeans(mapToRUnstructTask,sql,params);
}

QList<CsRUnstructTask> CSUnstructDao::dirRTask(const quint8 &status, const QString &curTime)
{
    QString sql = "select * from CS_R_UNSTRUCT_TASK WHERE state =:state and SEND_TIME <:curTime";
    QVariantMap params;
    params["state"]       = status;
    params["curTime"]      = curTime;
    DBQuery query;
    return query.listBeans(mapToRUnstructTask, sql,params);
}

void CSUnstructDao::updateRtaskList(const QList<CsRUnstructTask> &list)
{
    QString sql = "update CS_R_UNSTRUCT_TASK set TASK_NAME=:taskname,TASK_NUM =:task_num,DESCRIPTION = :descripion,SEND_TIME =:sendtime,STRATEGY =:strategy,STATE =:state,INSERTOR =:insertor,INSERT_TIME =:inserttime,OPERATOR =:operator,OPERA_TIME =:operatime where uuid =:uuid";
    DBTransaction* transaction = new DBTransaction;
    QVariantMap params;

    DBException excep;
    transaction->beginTransaction();
    bool flg = Environment::Db_Transaction_State::TRANS_FAIL;
    foreach(const CsRUnstructTask &task,list) {
        params["taskname"] = task.getTaskName();
        params["task_num"] = task.getTaskNum();
        params["descripion"] = task.getDescription();
        params["sendtime"] = task.getSendTime();
        params["strategy"] = task.getStrategy();
        params["state"] = task.getState();
        params["insertor"] = task.getInsertor();
        params["inserttime"] = task.getInsertTime();
        params["operator"] = task.getOperater();
        params["operatime"] = task.getOperaTime();
        params["uuid"] = task.getUuid();
        flg = transaction->execSQL(sql,params);
        if(!flg) {
            goto end;
        }
    }
    transaction->commit();
    delete transaction;
    return;
end:;
    transaction->rollback();
    delete transaction;
    excep.setText("操作数据库失败 ");
    excep.setType(QSqlError::TransactionError);
    throw excep;
}

void CSUnstructDao::updateRtask(const CsRUnstructTask &task)
{
    QString sql = "update CS_R_UNSTRUCT_TASK set TASK_NAME=:taskname,TASK_NUM =:task_num,DESCRIPTION = :descripion,SEND_TIME =:sendtime,STRATEGY =:strategy,STATE =:state,INSERTOR =:insertor,INSERT_TIME =:inserttime,OPERATOR =:operator,OPERA_TIME =:operatime where uuid =:uuid";
    QVariantMap params;
    params["taskname"] = task.getTaskName();
    params["task_num"] = task.getTaskNum();
    params["descripion"] = task.getDescription();
    params["sendtime"] = task.getSendTime();
    params["strategy"] = task.getStrategy();
    params["state"] = task.getState();
    params["insertor"] = task.getInsertor();
    params["inserttime"] = task.getInsertTime();
    params["operator"] = task.getOperater();
    params["operatime"] = task.getOperaTime();
    params["uuid"] = task.getUuid();
    DBTransaction* transaction = new DBTransaction;
    bool flg = Environment::Db_Transaction_State::TRANS_FAIL;
    transaction->beginTransaction();
    try{
        flg = transaction->execSQL(sql,params);
        if(flg) {
            transaction->commit();
            delete transaction;
        }
        else {
            DBException excep;
            excep.setText("操作数据库失败 ");
            excep.setType(QSqlError::TransactionError);
            throw excep;
        }
    }
    catch(DBException& ex){
        Q_UNUSED(ex)
        transaction->rollback();
        delete transaction;
        throw ex;
    }

}

QList<CsRUnstructSendFiles> CSUnstructDao::dirRSendFilesByTaskUUID(const QString &taskUUID)
{
    QString sql = "select * from CS_R_UNSTRUCT_SEND_FILES WHERE TASK_UUID =:taskUUID";
    QVariantMap params;
    params["taskUUID"]       = taskUUID;
    DBQuery query;
    return query.listBeans(mapToRUnstructTaskSendFile, sql,params);
}

QList<VCsRUnstructSendAddr> CSUnstructDao::pageAddrByTaskUuid(const QString &taskUUID, Page *page)
{
    QString sql = "SELECT * FROM (select a.*,g.DESCRIPTION from CS_R_UNSTRUCT_SEND_ADDR a,CS_CLIENT_TERMINAL g WHERE TASK_UUID =:taskUUID and a.CLIENT_UUID = g.TERMINAL_UUID)";
    //order by
    sql.append(QString(" order by %1 %2")//order by column1 desc/asc
               .arg(!(page->getOrderFieldName().isEmpty()) ? page->getOrderFieldName() : "CLIENT_UUID")
               .arg(page->getOrderField() == Qt::DescendingOrder?"DESC":"ASC")
               );
    QVariantMap params;
    params["taskUUID"]    = taskUUID;
    DBQuery query;
    return query.pageBean(mapToRVUnstructTaskSendAddr,page,sql,params);
}

QList<VCsRUnstructSendFiles> CSUnstructDao::pageFileByTaskUuid(const QString &taskUuid,Page *page)
{
    QString sql = "select * from (select * from CS_R_UNSTRUCT_SEND_FILES WHERE TASK_UUID =:taskUUID)";
    //order by
    sql.append(QString(" order by %1 %2")//order by column1 desc/asc
               .arg(!(page->getOrderFieldName().isEmpty()) ? page->getOrderFieldName() : "FILE_NAME")
               .arg(page->getOrderField() == Qt::DescendingOrder?"DESC":"ASC")
               );
    QVariantMap params;
    params["taskUUID"]       = taskUuid;
    DBQuery query;
    return query.pageBean(mapToVUnstructTaskSendFile,page, sql,params);
}

QList<CsRUnstructSendAddr> CSUnstructDao::dirRSendAddrsByTaskUUID(const QString &taskUuid)
{
    QString sql = "select * from CS_R_UNSTRUCT_SEND_ADDR WHERE TASK_UUID =:taskUUID";
    QVariantMap params;
    params["taskUUID"]       = taskUuid;
    DBQuery query;
    return query.listBeans(mapToRUnstructTaskSendAddr, sql,params);
}

void CSUnstructDao::dirRSendAddrsAndFilseByTaskUUID(const QString &taskUUID,
                                                    const quint8 state,
                                                    QList<CsRUnstructSendAddr> &addrs,
                                                    QList<CsRUnstructSendFiles> &files)
{
    addrs.clear();
    files.clear();

    QString sql = "select * from CS_R_UNSTRUCT_SEND_STATUS WHERE TASK_UUID =:taskUUID and STATE=:state";
    QVariantMap params;
    params["taskUUID"]    = taskUUID;
    params["state"]       = state;
    DBQuery query;
    QList<CsRUnstructSendStatus> status = query.listBeans(mapToRUnstructTaskSendStatus, sql, params);
    if(status.size() > 0)
    {
        QSet<QString> addruUUIDS;addruUUIDS.clear();
        QSet<QString> fileUUIDS; fileUUIDS.clear();
        foreach (CsRUnstructSendStatus state, status)
        {
            addruUUIDS.insert(state.getSendAddrUuid());
            fileUUIDS.insert(state.getSendFileUuid());
        }

        //addrs
        QList<QVariantMap> rowMap;

        QString sql_addr = "select * from CS_R_UNSTRUCT_SEND_ADDR WHERE TASK_UUID =:taskUUID and UUID=:addrUUID";
        foreach (QString addrUUID, addruUUIDS)
        {
            params.clear();
            params["taskUUID"]    = taskUUID;
            params["addrUUID"]    = addrUUID;

            rowMap.clear();
            rowMap = query.list(sql_addr, params);
            if(rowMap.size() > 0)
                addrs.append(mapToRUnstructTaskSendAddr(rowMap.first()));
        }

        //fiels
        QString sql_file = "select * from CS_R_UNSTRUCT_SEND_FILES WHERE TASK_UUID =:taskUUID and UUID=:fileUUID";
        foreach (QString fileUUID, fileUUIDS)
        {
            params.clear();
            params["taskUUID"]    = taskUUID;
            params["fileUUID"]    = fileUUID;

            rowMap.clear();
            rowMap = query.list(sql_file, params);
            if(rowMap.size() > 0)
                files.append(mapToRUnstructTaskSendFile(rowMap.first()));
        }
    }
}

void CSUnstructDao::updateSendStatus(const QString &taskUUID,
                                     const quint8 &oldState,
                                     const quint8 &newState,
                                     const QString &addrError)
{
    bool fly = Environment::Db_Transaction_State::TRANS_FAIL;
    QString sql = "update CS_R_UNSTRUCT_SEND_STATUS set STATE =:newState,ERROR =:error where TASK_UUID =:taskUUID and STATE=:oldState";
    QVariantMap params;
    params["taskUUID"]       = taskUUID;
    params["newState"] = newState;
    params["error"] = addrError;
    params["oldState"] = oldState;
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

void CSUnstructDao::updateSendStatusByAddr(const QString &taskUUID,
                                           const quint8 &oldState,
                                           const quint8 &newState,
                                           const QString &addrError,
                                           const QString &clientUUID)
{
    bool fly = Environment::Db_Transaction_State::TRANS_FAIL;
    QString sql = "update CS_R_UNSTRUCT_SEND_STATUS set STATE =:newState,ERROR =:addrError where TASK_UUID =:taskUUID and CLIENT_UUID =:clientUUID and STATE=:oldState";
    QVariantMap params;
    params["taskUUID"]       = taskUUID;
    params["newState"]       = newState;
    params["error"] = addrError;
    params["clientUUID"]       = clientUUID;
    params["oldState"] = oldState;
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

void CSUnstructDao::getRTaskUuidByTaskNum(QString &taskUUID, const quint32 &taskNum)
{
    QString sql = "select UUID from CS_R_UNSTRUCT_TASK WHERE TASK_NUM =:taskNum";
    QVariantMap params;
    params["taskNum"]       = taskNum;
    DBQuery query;
    taskUUID = query.selectVariant(sql, params).toString();
}

void CSUnstructDao::getRTaskStateByTaskUUID(const QString &taskUUID, quint8 &state)
{
    QString sql = "select STATE from CS_R_UNSTRUCT_TASK where UUID=:taskUUID";

    QVariantMap params;
    params["taskUUID"]       = taskUUID;
    DBQuery query;
    state = (quint8)query.selectVariant(sql, params).toUInt();
}

void CSUnstructDao::getRTaskStateByTaskUUIDAndClientUUID(const QString &taskUUID, const QString &clientUUID, quint8 &state)
{
    QString sql = "select STATE from CS_R_UNSTRUCT_SEND_ADDR where TASK_UUID=:taskUUID and CLIENT_UUID =:clientUUID";

    QVariantMap params;
    params["taskUUID"]       = taskUUID;
    params["clientUUID"]       = clientUUID;
    DBQuery query;
    state = (quint8)query.selectVariant(sql, params).toUInt();
}

void CSUnstructDao::getErrorMsgByState(const quint8 &taskState, QString &errorMsg)
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
        //解析文件下载地址失败
    case Unstru_Data_Trans::Resp_Info_State::_8:
        errorMsg = Unstru_Data_Trans::Resp_Info_State::_8_DESC_ParseFileDownLoadAddrFail;
        break;
        //解析文件保存位置是否合法
    case Unstru_Data_Trans::Resp_Info_State::_9:
        errorMsg = Unstru_Data_Trans::Resp_Info_State::_9_DESC_ParseFileSaveAddrFail;
        break;
        //创建非结构化任务入库失败
    case Unstru_Data_Trans::Resp_Info_State::_A:
        errorMsg = Unstru_Data_Trans::Resp_Info_State::_A_DESC_DBTransactionFail;
        break;
    default:
        break;
    }
}

void CSUnstructDao::updateRTaskErrorInfo(const QString &taskUUID, const quint8 &taskState,
                                         const quint8 &statusState, const QString &statusError,
                                         const QVector<Result *> &Errors)
{
    bool fly = Environment::Db_Transaction_State::TRANS_FAIL;
    QString tasksql = "update CS_R_UNSTRUCT_TASK set STATE =:state where UUID =:uuid";

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
            QString statussql = "update CS_R_UNSTRUCT_SEND_STATUS set STATE =:state, ERROR =:error where TASK_UUID =:taskUUID";
            QVariantMap statusParams;
            statusParams["taskUUID"] = taskUUID;
            statusParams["state"] = statusState;
            statusParams["error"] = statusError;
            fly = transaction->execSQL(statussql,statusParams);
            if(fly == Environment::Db_Transaction_State::TRANS_SUCCESS)
            {
                if(Errors.size()<=0)
                {
                    transaction->commit();
                    return;
                }
                QString sendStatussql = "UPDATE ";
                sendStatussql += "CS_R_UNSTRUCT_SEND_STATUS ";
                sendStatussql += "SET ";
                sendStatussql += "ERROR = :error ";
                sendStatussql += "WHERE TASK_UUID IN ";
                sendStatussql += "(SELECT ";
                sendStatussql += "UUID ";
                sendStatussql += "FROM ";
                sendStatussql += "CS_R_UNSTRUCT_SEND_FILES ";
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

void CSUnstructDao::updateRTaskAndAllSendAddrStatus(const QString &taskUUID, const quint8 &taskState, const quint8 &statusState, const QString &statusError)
{
    bool fly = Environment::Db_Transaction_State::TRANS_FAIL;
    QString tasksql = "update CS_R_UNSTRUCT_TASK set STATE =:state where UUID =:uuid";

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
            QString statussql = "update CS_R_UNSTRUCT_SEND_STATUS set STATE =:state,ERROR =:error where TASK_UUID =:taskUUID";
            QVariantMap statusParams;
            statusParams["taskUUID"]       = taskUUID;
            statusParams["state"] = statusState;
            statusParams["error"] = statusError;
            fly = transaction->execSQL(statussql,statusParams);
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

void CSUnstructDao::updateRTaskAndSendAddrStatus(const QString &taskUUID, const quint8 &taskState, const QString &clientUUID, const quint8 &statusState, const QString &statusError)
{
    bool fly = Environment::Db_Transaction_State::TRANS_FAIL;
    QString tasksql = "update CS_R_UNSTRUCT_TASK set STATE =:state where UUID =:uuid";

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
            QString statussql = "update CS_R_UNSTRUCT_SEND_STATUS set STATE =:state,ERROR =:error where TASK_UUID =:taskUUID and CLIENT_UUID =:clientUUID";
            QVariantMap statusParams;
            statusParams["taskUUID"]       = taskUUID;
            statusParams["clientUUID"]       = clientUUID;
            statusParams["state"] = statusState;
            statusParams["error"] = statusError;
            fly = transaction->execSQL(statussql,statusParams);
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

void CSUnstructDao::moveRTask2STask(const QString &taskUUID)
{
    /*
INSERT INTO CS_S_UNSTRUCT_TASK (SELECT * FROM CS_R_UNSTRUCT_TASK WHERE UUID=:o_id)
DELETE FROM CS_R_UNSTRUCT_TASK WHERE UUID=:o_id
INSERT INTO CS_S_UNSTRUCT_SEND_FILES (SELECT * FROM CS_R_UNSTRUCT_SEND_FILES WHERE UUID=:o_id)
DELETE FROM CS_R_UNSTRUCT_SEND_FILES WHERE UUID=:o_id
INSERT INTO CS_S_UNSTRUCT_SEND_ADDR (SELECT * FROM CS_R_UNSTRUCT_SEND_ADDR WHERE UUID=:o_id)
DELETE FROM CS_R_UNSTRUCT_SEND_ADDR WHERE UUID=:o_id
    */
    bool fly = Environment::Db_Transaction_State::TRANS_FAIL;
    QString sql_insert_stask = "INSERT INTO CS_S_UNSTRUCT_TASK (SELECT * FROM CS_R_UNSTRUCT_TASK WHERE UUID=:o_id)";
    QString sql_delete_rtask = "DELETE FROM CS_R_UNSTRUCT_TASK WHERE UUID=:o_id";
    QString sql_insert_sfile = "INSERT INTO CS_S_UNSTRUCT_SEND_FILES (SELECT * FROM CS_R_UNSTRUCT_SEND_FILES WHERE TASK_UUID=:o_id)";
    QString sql_delete_rfile = "DELETE FROM CS_R_UNSTRUCT_SEND_FILES WHERE TASK_UUID=:o_id";
    QString sql_insert_saddr = "INSERT INTO CS_S_UNSTRUCT_SEND_ADDR (SELECT * FROM CS_R_UNSTRUCT_SEND_ADDR WHERE TASK_UUID=:o_id)";
    QString sql_delete_raddr = "DELETE FROM CS_R_UNSTRUCT_SEND_ADDR WHERE TASK_UUID=:o_id";
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
        throw ex;
    }
    delete transaction;
}

void CSUnstructDao::updateRTaskAndAllSendAddr(const QString &taskUUID, const quint8 &taskNewState, const quint8 &taskOldState, const QString &taskOperaSymbol, const quint8 &newStatusState, const quint8 &oldStatusState, const QString &StatusOperaSymbol, const QString &StatusError)
{
    bool fly = Environment::Db_Transaction_State::TRANS_FAIL;
    QString tasksql = "update CS_R_UNSTRUCT_TASK set STATE =:newstate where UUID =:uuid and STATE "+taskOperaSymbol+":oldstate";

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
            QString statusSql = "update CS_R_UNSTRUCT_SEND_STATUS set STATE =:newAddrState,ERROR =:error where TASK_UUID =:taskUUID and STATE "+StatusOperaSymbol + ":oldAddrState";
            QVariantMap statusParams;
            statusParams["taskUUID"]       = taskUUID;
            statusParams["oldAddrState"] = oldStatusState;
            statusParams["newAddrState"] = newStatusState;
            statusParams["error"] = StatusError;
            fly = transaction->execSQL(statusSql,statusParams);
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

void CSUnstructDao::updateRTaskAndAddr(const QString &taskUUID,
                                       const quint8 &taskOldState,
                                       const quint8 &taskNewState,
                                       const QString &taskOperaSymbol,
                                       const QString &clientUUID,
                                       const quint8 &statusState,
                                       const QString &statusError)
{
    bool fly = Environment::Db_Transaction_State::TRANS_FAIL;
    QString tasksql = "update CS_R_UNSTRUCT_TASK set STATE =:newstate where UUID =:uuid and STATE "+taskOperaSymbol+":oldstate";

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
            QString statusSql = "update CS_R_UNSTRUCT_SEND_STATUS set STATE =:state,ERROR =:error where TASK_UUID =:taskUUID and CLIENT_UUID =:clientUUID";
            QVariantMap statusParams;
            statusParams["taskUUID"]       = taskUUID;
            statusParams["state"] = statusState;
            statusParams["error"] = statusError;
            statusParams["clientUUID"] = clientUUID;
            fly = transaction->execSQL(statusSql,statusParams);
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

void CSUnstructDao::updateRTaskAndAddr(const QString &taskUUID, const quint8 &taskOldState, const quint8 &taskNewState, const QString &clientUUID, const quint8 &addrOldState, const quint8 &addrNewState, const QString &addrError)
{
    bool fly = Environment::Db_Transaction_State::TRANS_FAIL;
    QString tasksql = "update CS_R_UNSTRUCT_TASK set STATE =:newstate where UUID =:uuid and STATE=:oldstate";

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
            QString addrsql = "update CS_R_UNSTRUCT_SEND_STATUS set STATE =:addrNewState,ERROR =:error where TASK_UUID =:taskUUID and CLIENT_UUID =:clientUUID and STATE=:addrOldState";
            QVariantMap addrparams;
            addrparams["taskUUID"]       = taskUUID;
            addrparams["addrNewState"] = addrNewState;
            addrparams["addrOldState"] = addrOldState;
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

bool CSUnstructDao::getSendStatusState(const QString &taskUUID, const quint8 sendState)
{
    QString sql = "select * from CS_R_UNSTRUCT_SEND_STATUS WHERE TASK_UUID =:taskUUID";
    QVariantMap params;
    params["taskUUID"]    = taskUUID;
    DBQuery query;
    QList<CsRUnstructSendStatus> status = query.listBeans(mapToRUnstructTaskSendStatus, sql, params);
    if(status.size() > 0 )
    {
        foreach (CsRUnstructSendStatus statu, status)
        {
            if(statu.getState() == sendState)
            {
                return true;
            }
        }
        return false;
    }
    else
    {
        QString excep;
        excep = trs("未查询到当前任务");
        throw excep;
    }
}

void CSUnstructDao::updateSendStateErrorInfo(const QString &taskUUID, const quint8 &oldState, const quint8 &newState, const QString &clientUUID, const QVector<Result *> &Errors)
{
    bool fly = Environment::Db_Transaction_State::TRANS_FAIL;
    //必须try...catch才能回滚和提交
    DBTransaction *transaction = new DBTransaction;
    try
    {
        transaction->beginTransaction();
        if(Errors.size()<=0)
        {
            transaction->commit();
        }
        else
        {
            QString sendStatussql = "UPDATE ";
            sendStatussql += "CS_R_UNSTRUCT_SEND_STATUS ";
            sendStatussql += "SET ";
            sendStatussql += "STATE = :newState ";
            sendStatussql += "ERROR = :error ";
            sendStatussql += "WHERE SEND_FILE_UUID IN ";
            sendStatussql += "(SELECT ";
            sendStatussql += "UUID ";
            sendStatussql += "FROM ";
            sendStatussql += "CS_R_UNSTRUCT_SEND_FILES ";
            sendStatussql += "WHERE DOWN_URL = :downloadURL ";
            sendStatussql += "AND TASK_UUID = :taskUUID) ";
            sendStatussql += "AND CLIENT_UUID = :clientUUID ";
            sendStatussql += "AND TASK_UUID = :taskUUID ";
            sendStatussql += "AND STATE = :oldState ";
            QVariantMap sendStatusparams;
            for(Result *err :Errors)
            {
                sendStatusparams.clear();
                sendStatusparams["newState"]       = newState;
                sendStatusparams["error"]       = err->backMsg;
                sendStatusparams["downloadURL"] = err->DownloadURLs;
                sendStatusparams["taskUUID"] = taskUUID;
                sendStatusparams["clientUUID"] = clientUUID;
                sendStatusparams["oldState"]       = oldState;
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
err:;
        DBException excep;
        excep.setType(QSqlError::TransactionError);
        excep.setText(trs("update error"));
        throw excep;
    }
    catch(DBException &ex)
    {
        transaction->rollback();
        throw ex;
    }
    delete transaction;
}

void CSUnstructDao::updateRTaskState(const QString &taskUUID, const quint8 &state)
{
    bool fly = Environment::Db_Transaction_State::TRANS_FAIL;
    QString sql = "update CS_R_UNSTRUCT_TASK set STATE =:state where UUID =:uuid";

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

void CSUnstructDao::updateRSendAddrByTaskUUID(const QString &taskUUID,const QString &clientUUID, const quint8 &state, const QString &clientError)
{
    bool fly = Environment::Db_Transaction_State::TRANS_FAIL;
    QString sql = "update CS_R_UNSTRUCT_SEND_STATUS set STATE =:state,ERROR =:error where TASK_UUID =:taskUUID and CLIENT_UUID =:clientUUID";

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

void CSUnstructDao::updateRTaskStateByTaskUUID(const QString &taskUUID, const quint8 &oldState, const quint8 &newState, const QString &operaSymbol)
{
    bool fly = Environment::Db_Transaction_State::TRANS_FAIL;
    QString sql = "update CS_R_UNSTRUCT_TASK set STATE =:newstate where UUID =:uuid and STATE "+operaSymbol+":oldstate";

    QVariantMap params;
    params["uuid"]       = taskUUID;
    params["newstate"] = newState;
    params["oldstate"] = oldState;
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

void CSUnstructDao::updateRTaskSendAddrStateByTaskUUID(const QString &taskUUID, const quint8 &state, const QString &clientError)
{
    bool fly = Environment::Db_Transaction_State::TRANS_FAIL;
    QString sql = "update CS_R_UNSTRUCT_SEND_STATUS set STATE=:state,ERROR=:error where TASK_UUID=:taskUUID";

    QVariantMap params;
    params["taskUUID"]       = taskUUID;
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

void CSUnstructDao::updateRTaskSendStatusByTaskUUIDAndClientUUID(const QString &taskUUID, const QStringList &nodes, const quint8 &state)
{
    bool fly = Environment::Db_Transaction_State::TRANS_FAIL;
    QString sql = "update CS_R_UNSTRUCT_SEND_STATUS set STATE=:state,ERROR=:error where CLIENT_UUID in(:uuids)";
    //查询任务状态
    QString sqlForState = "select * from CS_R_UNSTRUCT_TASK where UUID =:taskUUID";
    //修改任务状态
    QString sqlForTask = "update CS_R_UNSTRUCT_TASK set STATE = :taskState,SEND_TIME =:sendTime where UUID = :taskUUID";
    QVariantMap params;
    params.insert("uuids",(QVariant)nodes);
    params["taskUUID"] = taskUUID;
    params["state"] = state;
    params["error"] = "";
    params["taskState"] = Task_State::USABLE;
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
            if(state == SendStatus_State::USABLE) {
                DBQuery query;
                CsRUnstructTask task = query.uniqueBean(mapToRUnstructTask, sqlForState,params);
                quint8 taskState = task.getState();
                if(taskState == Task_State::DOWNERROR ||
                        taskState == Task_State::SENDERROR ||
                        taskState == Task_State::TASKERROR)
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

void CSUnstructDao::updateRTaskSendStatusByTaskUUIDAndSendFileUUID(const QString &taskUUID, const QStringList &sendFileUUids, const quint8 &state)
{
    bool fly = Environment::Db_Transaction_State::TRANS_FAIL;
    QString sql = "update CS_R_UNSTRUCT_SEND_STATUS set STATE=:state,ERROR=:error where SEND_FILE_UUID in(:uuids)";
    //查询任务状态
    QString sqlForState = "select * from CS_R_UNSTRUCT_TASK where UUID =:taskUUID";
    //修改任务状态
    QString sqlForTask = "update CS_R_UNSTRUCT_TASK set STATE = :taskState,SEND_TIME =:sendTime where UUID = :taskUUID";
    QVariantMap params;
    params.insert("uuids",(QVariant)sendFileUUids);
    params["taskUUID"] = taskUUID;
    params["state"] = state;
    params["error"] = "";
    params["taskState"] = Task_State::USABLE;
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
            if(state == SendStatus_State::USABLE) {
                DBQuery query;
                CsRUnstructTask task = query.uniqueBean(mapToRUnstructTask, sqlForState,params);
                quint8 taskState = task.getState();
                if(taskState == Task_State::DOWNERROR ||
                        taskState == Task_State::SENDERROR ||
                        taskState == Task_State::TASKERROR)
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

void CSUnstructDao::updateRTaskSendStatusByTaskUUIDAndClientUUID(const QString &taskUUID, const QString &clientUUID, const quint8 &state, const QString &clientError)
{
    bool fly = Environment::Db_Transaction_State::TRANS_FAIL;
    QString sql = "update CS_R_UNSTRUCT_SEND_STATUS set STATE=:state,ERROR=:error where TASK_UUID=:taskUUID and UUID =:uuid";

    QVariantMap params;
    params["uuid"]       = clientUUID;
    params["taskUUID"]       = taskUUID;
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

void CSUnstructDao::updateRTaskSendStatusByUUID(const QString &taskUuid,const QStringList &UUID, const quint8 &state)
{
    bool fly = Environment::Db_Transaction_State::TRANS_FAIL;
    QString sql = "update CS_R_UNSTRUCT_SEND_STATUS set STATE=:state,ERROR=:error where UUID in(:uuids)";
    //查询任务状态
    QString sqlForState = "select * from CS_R_UNSTRUCT_TASK where UUID =:taskUUID";
    //修改任务状态
    QString sqlForTask = "update CS_R_UNSTRUCT_TASK set STATE = :taskState,SEND_TIME =:sendTime where UUID = :taskUUID";
    QVariantMap params;
    params.insert("uuids",(QVariant)UUID);
    params["taskUUID"] = taskUuid;
    params["state"] = state;
    params["error"] = "";
    params["taskState"] = Task_State::USABLE;
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
            if(state == SendStatus_State::USABLE) {
                DBQuery query;
                CsRUnstructTask task = query.uniqueBean(mapToRUnstructTask, sqlForState,params);
                quint8 taskState = task.getState();
                if(taskState == Task_State::DOWNERROR ||
                        taskState == Task_State::SENDERROR ||
                        taskState == Task_State::TASKERROR)
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



void CSUnstructDao::insertRTaskSendState(const CsRUnstructSendStatus &csRUnstructSendStatus)
{    
    QString sql = "insert into CS_R_UNSTRUCT_SEND_STATUS(UUID, CLIENT_UUID, SEND_FILE_UUID, ERROR, TASK_UUID) values (:uuid, :clientUuid, :sendFileUuid, :error, :taskUuid)";

    QVariantMap params;
    params["uuid"] = csRUnstructSendStatus.getUuid();
    params["clientUuid"] = csRUnstructSendStatus.getClientUuid();
    params["sendFileUuid"] = csRUnstructSendStatus.getSendFileUuid();
    params["error"]    = csRUnstructSendStatus.getError();
    params["taskUuid"]   = csRUnstructSendStatus.getTaskUuid();
    //必须try...catch才能回滚和提交
    DBTransaction *transaction = new DBTransaction;
    try
    {
        transaction->beginTransaction();
        //因为这里的key为整形,所以可以这样判断
        int thisKey = transaction->insert(sql, params);
        if(thisKey>0)
        {
            transaction->commit();
            qDebug() << trs("插入成功");
        }
        else
        {
            transaction->rollback();
            DBException excep;
            excep.setType(QSqlError::TransactionError);
            excep.setText(trs("insert error"));
            throw excep;
        }
    }
    catch(DBException &ex)
    {
        qDebug() << trs("插入失败");
        transaction->rollback();
        //        qDebug() << excep.getText();
        //既然try...catch,就捕获异常做处理,如果不try...catch,自动回退直到找到try...catch
        throw ex;
    }
    delete transaction;
}


void CSUnstructDao::saveSRTask(const CsSUnstructTask &csSUnstructTask, const CsSUnstructSendAddr &csSUnstructSendAddr, const CsSUnstructSendFiles &csSUnstructSendFiles)
{
    QString sql = "insert into CS_S_UNSTRUCT_TASK(UUID, TASK_NAME, TASK_NUM, DESCRIPTION, SEND_TIME, STRATEGY, STATE, INSERTOR, INSERT_TIME, OPERATOR, OPERA_TIME)"
                  " values (:uuid, :taskName, :taskNum, :description, :sendTime, :strategy, :state, :insertor, :insertTime, :operater, :operaTime)";

    QVariantMap params;
    params["uuid"] = csSUnstructTask.getUuid();
    params["taskName"] = csSUnstructTask.getTaskName();
    params["taskNum"] = csSUnstructTask.getTaskNum();
    params["description"]    = csSUnstructTask.getDescription();
    params["sendTime"]   = csSUnstructTask.getSendTime();
    params["strategy"]   = csSUnstructTask.getStrategy();
    params["state"]   = csSUnstructTask.getState();
    params["insertor"]   = csSUnstructTask.getInsertor();
    params["insertTime"]   = csSUnstructTask.getInsertTime();
    params["operater"]   = csSUnstructTask.getOperater();
    params["operaTime"]   = csSUnstructTask.getOperaTime();
    //必须try...catch才能回滚和提交
    DBTransaction *transaction = new DBTransaction;
    try
    {
        transaction->beginTransaction();
        //因为这里的key为整形,所以可以这样判断
        int thisKey = transaction->insert(sql, params);
        if(thisKey>0)
        {
            transaction->commit();
            qDebug() << trs("插入成功");
        }
        else
        {
            transaction->rollback();
            DBException excep;
            excep.setType(QSqlError::TransactionError);
            excep.setText(trs("insert error"));
            throw excep;
        }
    }
    catch(DBException &ex)
    {
        qDebug() << trs("插入失败");
        transaction->rollback();
        //        qDebug() << excep.getText();
        //既然try...catch,就捕获异常做处理,如果不try...catch,自动回退直到找到try...catch
        throw ex;
    }
    delete transaction;
}


CsRUnstructSendAddr CSUnstructDao::mapToRUnstructTaskSendAddr(const QVariantMap &rowMap) {
    CsRUnstructSendAddr addr;
    addr.setUuid(rowMap.value("UUID").toString());
    addr.setClientUuid(rowMap.value("CLIENT_UUID").toString());
    addr.setGroupDesc(rowMap.value("GROUP_UUIDS").toString());
    addr.setTaskUuid(rowMap.value("TASK_UUID").toString());
    return addr;
}

CsRUnstructSendStatus CSUnstructDao::mapToRUnstructTaskSendStatus(const QVariantMap &rowMap)
{
    CsRUnstructSendStatus status;
    status.setUuid(rowMap.value("UUID").toString());
    status.setClientUuid(rowMap.value("CLIENT_UUID").toString());
    status.setSendAddrUuid(rowMap.value("SEND_ADDR_UUID").toString());
    status.setSendFileUuid(rowMap.value("SEND_FILE_UUID").toString());
    status.setTaskUuid(rowMap.value("TASK_UUID").toString());
    status.setError(rowMap.value("ERROR").toString());
    status.setState((quint8)rowMap.value("STATE").toInt());
    return status;
}

VCsRUnstructSendAddr CSUnstructDao::mapToRVUnstructTaskSendAddr(const QVariantMap &rowMap)
{

    VCsRUnstructSendAddr addr;
    addr.setUuid(rowMap.value("UUID").toString());
    addr.setClientUuid(rowMap.value("CLIENT_UUID").toString());
    addr.setGroupDesc(rowMap.value("GROUP_UUIDS").toString());
    addr.setTaskUuid(rowMap.value("TASK_UUID").toString());
    addr.setDescritpion(rowMap.value("DESCRIPTION").toString());
    QString sql = "select distinct state from CS_R_UNSTRUCT_SEND_STATUS where"
                  " CLIENT_UUID =:clientUuid and TASK_UUID =:taskUuid";
    DBQuery query;
    QVariantMap params;
    params["clientUuid"] = addr.getClientUuid();
    params["taskUuid"] =  addr.getTaskUuid();
    QList<QVariantMap> vState =   query.list(sql,params);
    QList<quint8> stateList;
    foreach(const QVariantMap &state,vState) {
        stateList.append((quint8)state.value("STATE").toInt());
    }
    addr.setState(defaultStrategy(stateList));
    return addr;
}

VCsRUnstructSendFiles CSUnstructDao::mapToVUnstructTaskSendFile(const QVariantMap &rowMap)
{
    VCsRUnstructSendFiles sendFile;
    sendFile.setUuid(rowMap.value("UUID").toString());
    sendFile.setFileName(rowMap.value("FILE_NAME").toString());
    sendFile.setDownUrl(rowMap.value("DOWN_URL").toString());
    sendFile.setFileDestName(rowMap.value("FILE_DEST_NAME").toString());
    sendFile.setSaveAbst(rowMap.value("SAVE_ABST").toString());
    sendFile.setTaskUuid(rowMap.value("TASK_UUID").toString());
    sendFile.setHardAbst(rowMap.value("HADR_ABST").toString());
    sendFile.setFileSrc((quint8)rowMap.value("FILE_SRC").toInt());

    QString sql = "select distinct state from CS_R_UNSTRUCT_SEND_STATUS where"
                  " SEND_FILE_UUID =:sendFileUuid and TASK_UUID =:taskUuid";
    DBQuery query;
    QVariantMap params;
    params["sendFileUuid"] = sendFile.getUuid();
    params["taskUuid"] =  sendFile.getTaskUuid();
    QList<QVariantMap> Vstate =   query.list(sql,params);
    QList<quint8> stateList;
    foreach(const QVariantMap &state,Vstate) {
        stateList.append((quint8)state.value("STATE").toInt());
    }
    sendFile.setState(defaultStrategy(stateList));
    return sendFile;
}

quint8 CSUnstructDao::defaultStrategy(const QList<quint8> &stateList)
{
    if(stateList.contains(SendStatus_State::SENDERROR)) {
        return SendStatus_State::SENDERROR;
    }
    else if(stateList.contains(SendStatus_State::DOWNERROR)) {
        return SendStatus_State::DOWNERROR;
    }
    else if(stateList.contains(SendStatus_State::DISCARD)) {
        return SendStatus_State::DISCARD;
    }
    else if(stateList.contains(SendStatus_State::SENDING)) {
        return SendStatus_State::SENDING;
    }
    else if(stateList.contains(SendStatus_State::PRESEND)) {
        return SendStatus_State::PRESEND;
    }
    else if(stateList.contains(SendStatus_State::SENDSUCCESS)) {
        return SendStatus_State::SENDSUCCESS;
    }
    else if(stateList.contains(SendStatus_State::USABLE)) {
        return SendStatus_State::USABLE;
    }
    else if(stateList.contains(SendStatus_State::DOWNSUCCESS)) {
        return SendStatus_State::DOWNSUCCESS;
    }
}


void CSUnstructDao::getClientAddrByGroupUUID(QList<QString> &groupUUIDs, QList<QString> &clientUUIDs)
{
    QVariantMap params;
    QString sql = "SELECT distinct * FROM CS_CLIENT_GROUP START WITH UUID IN ("
                  ":groupUUIDs"
                  ") CONNECT BY prior UUID=SUP_UUID";
    params.clear();
    params.insert("groupUUIDs", (QVariant)groupUUIDs);
    DBQuery query;
    QList<QVariantMap> varMap = query.list(sql, params);

    for(int i=0; i<varMap.size(); i++)
    {
        clientUUIDs.append(varMap.at(i).value("UUID").toString());
    }
}

void CSUnstructDao::addTaskFromWeb(CsRUnstructTask& uStructTask,
                                   QList<CsRUnstructSendAddr*> &uStructSendAddrList,
                                   QList<CsRUnstructSendFiles *> &uStructSendFilesList,
                                   QList<CsRUnstructSendStatus *> &uStructSendStatusList,
                                   CsRStructTask &structTask,
                                   QList<CsRStructSendAddr *> &structSendAddrList,
                                   QList<CsRStructSendFiles *> &structSendFilesList,
                                   QList<CsRStructSendStatus* > &structSendStatusList)
{
    bool flg = Environment::Db_Transaction_State::TRANS_FAIL;

    //[1] uStructTask
    QString sql_uStructTask = "insert into CS_R_UNSTRUCT_TASK values(:UUID,:TASK_NAME,:TASK_NUM,:DESCRIPTION,:SEND_TIME,:STRATEGY,:STATE,:INSERTOR,:INSERT_TIME,:OPERATOR,:OPERA_TIME)";
    QVariantMap params;params.clear();
    params["UUID"] = uStructTask.getUuid();
    params["TASK_NAME"] = uStructTask.getTaskName();
    params["TASK_NUM"] = uStructTask.getTaskNum();
    params["DESCRIPTION"] = uStructTask.getDescription();
    params["SEND_TIME"] = uStructTask.getSendTime();
    params["STRATEGY"] = uStructTask.getStrategy();
    params["STATE"] = uStructTask.getState();
    params["INSERTOR"] = uStructTask.getInsertor();
    params["INSERT_TIME"] = uStructTask.getInsertTime();
    params["OPERATOR"] = uStructTask.getOperater();
    params["OPERA_TIME"] = uStructTask.getOperaTime();

    //必须try...catch才能回滚和提交
    DBTransaction *transaction = new DBTransaction;
    try
    {
        transaction->beginTransaction();
        flg = transaction->execSQL(sql_uStructTask,params);
        if(flg == Environment::Db_Transaction_State::TRANS_SUCCESS)
        {
            //[2]uStructSendAddrList
            QString sql_uStructSendAddr = "INSERT INTO CS_R_UNSTRUCT_SEND_ADDR values(:uuid,:clientuuid,:taskuuid,:groupuuids)";
            QVariantMap params;
            for(CsRUnstructSendAddr* uStructSendAddr : uStructSendAddrList)
            {
                params.clear();
                params["uuid"] = uStructSendAddr->getUuid();
                params["clientuuid"] = uStructSendAddr->getClientUuid();
                params["taskuuid"] = uStructSendAddr->getTaskUuid();
                params["groupuuids"] = uStructSendAddr->getGroupDesc();
                flg = transaction->execSQL(sql_uStructSendAddr,params);
                if(!flg)
                {
                    break;
                }
            }
            //[3]uStructSendFileList
            if(flg == Environment::Db_Transaction_State::TRANS_SUCCESS)
            {
                QString sql_uStructSendFiles = "insert into CS_R_UNSTRUCT_SEND_FILES values(:uuid,:filename,:downurl,:filedestname,:saveabsr,:taskuuid,:hardabst,:filesrc)";
                QVariantMap params;
                for(CsRUnstructSendFiles* uStructSendFiles: uStructSendFilesList)
                {
                    params.clear();
                    params["uuid"] = uStructSendFiles->getUuid();
                    params["filename"] = uStructSendFiles->getFileName();
                    params["downurl"] = uStructSendFiles->getDownUrl();
                    params["filedestname"] = uStructSendFiles->getFileDestName();
                    params["saveabsr"] = uStructSendFiles->getSaveAbst();
                    params["taskuuid"] = uStructSendFiles->getTaskUuid();
                    params["hardabst"] = uStructSendFiles->getHardAbst();
                    params["filesrc"] = uStructSendFiles->getFileSrc();
                    flg = transaction->execSQL(sql_uStructSendFiles,params);
                    if(!flg)
                    {
                        break;
                    }
                }
                //[4]uStructSendStatusList
                if(flg == Environment::Db_Transaction_State::TRANS_SUCCESS)
                {
                    QString sql_uStructSendStatusList = "insert into CS_R_UNSTRUCT_SEND_STATUS values(:UUID,:CLIENT_UUID,:SEND_FILE_UUID,:ERROR,:TASK_UUID,:SEND_ADDR_UUID,:STATE)";
                    QVariantMap params;
                    for(CsRUnstructSendStatus* uStructSendStatus: uStructSendStatusList)
                    {
                        params.clear();
                        params["UUID"] = uStructSendStatus->getUuid();
                        params["CLIENT_UUID"] = uStructSendStatus->getClientUuid();
                        params["SEND_FILE_UUID"] = uStructSendStatus->getSendFileUuid();
                        params["ERROR"] = uStructSendStatus->getError();
                        params["TASK_UUID"] = uStructSendStatus->getTaskUuid();
                        params["SEND_ADDR_UUID"] = uStructSendStatus->getSendAddrUuid();
                        params["STATE"] = uStructSendStatus->getState();
                        flg = transaction->execSQL(sql_uStructSendStatusList,params);
                        if(!flg)
                        {
                            break;
                        }
                    }
                    //[5]structTask
                    if(flg == Environment::Db_Transaction_State::TRANS_SUCCESS)
                    {
                        QString sql_structTask = "insert into CS_R_STRUCT_TASK values(:UUID,:TASK_NAME,:TASK_NUM,:DESCRIPTION,:SEND_TIME,:EXEC_TIME,:STRATEGY,:STATE,:INSERTOR,:INSERT_TIME,:OPERATOR,:OPERA_TIME)";
                        QVariantMap params;params.clear();
                        params["UUID"] = structTask.getUuid();
                        params["TASK_NAME"] = structTask.getTaskName();
                        params["TASK_NUM"] = structTask.getTaskNum();
                        params["DESCRIPTION"] = structTask.getDescription();
                        params["SEND_TIME"] = structTask.getSendTime();
                        params["EXEC_TIME"] = structTask.getExecTime();
                        params["STRATEGY"] = structTask.getStrategy();
                        params["STATE"] = structTask.getState();
                        params["INSERTOR"] = structTask.getInsertor();
                        params["INSERT_TIME"] = structTask.getInsertTime();
                        params["OPERATOR"] = structTask.getOperater();
                        params["OPERA_TIME"] = structTask.getOperaTime();
                        flg = transaction->execSQL(sql_structTask,params);
                        if(flg == Environment::Db_Transaction_State::TRANS_SUCCESS)
                        {
                            //[6]structSendAddrList
                            QString sql_structSendAddr = "insert into CS_R_STRUCT_SEND_ADDR  values(:UUID,:CLIENT_UUID,:TASK_UUID,:GROUPDESC)";
                            QVariantMap params;
                            for(CsRStructSendAddr* structSendAddr : structSendAddrList)
                            {
                                params.clear();
                                params["UUID"] = structSendAddr->getUuid();
                                params["CLIENT_UUID"]= structSendAddr->getClientUuid();
                                params["TASK_UUID"]= structSendAddr->getTaskUuid();
                                params["GROUPDESC"]= structSendAddr->getGroupDesc();
                                flg = transaction->execSQL(sql_structSendAddr,params);
                                if(!flg)
                                {
                                    break;
                                }
                            }

                            if(flg == Environment::Db_Transaction_State::TRANS_SUCCESS)
                            {
                                //[7]structSendFilesList
                                QString sql_structSendFiles="insert into CS_R_STRUCT_SEND_FILES values(:UUID,:FILE_NAME,:DOWN_URL,:FILE_DEST_NAME,:SAVE_ABST,:SEQUENCE,:TASK_UUID,:HARDABST,:FILESRC)";
                                QVariantMap params;
                                for(CsRStructSendFiles* structSendFiles : structSendFilesList)
                                {
                                    params.clear();
                                    params["UUID"] = structSendFiles->getUuid();
                                    params["FILE_NAME"] = structSendFiles->getFileName();
                                    params["FILE_DEST_NAME"] = structSendFiles->getFileDestName();
                                    params["DOWN_URL"] = structSendFiles->getDownUrl();
                                    params["SAVE_ABST"] = structSendFiles->getSaveAbst();
                                    params["TASK_UUID"] = structSendFiles->getTaskUuid();
                                    params["SEQUENCE"] = structSendFiles->getSequence();
                                    params["HARDABST"] = structSendFiles->getHardAbst();
                                    params["FILESRC"] = structSendFiles->getFileSrc();
                                    flg = transaction->execSQL(sql_structSendFiles,params);
                                    if(!flg)
                                    {
                                        break;
                                    }
                                }
                                //[8]structSendStatusList
                                if(flg == Environment::Db_Transaction_State::TRANS_SUCCESS)
                                {
                                    QString sql_structSendStatusList = "insert into CS_R_STRUCT_SEND_STATUS values(:UUID,:CLIENT_UUID,:SEND_FILE_UUID,:ERROR,:TASK_UUID,:SEND_ADDR_UUID,:STATE)";
                                    QVariantMap params;
                                    for(CsRStructSendStatus* structSendStatus: structSendStatusList)
                                    {
                                        params.clear();
                                        params["UUID"] = structSendStatus->getUuid();
                                        params["CLIENT_UUID"] = structSendStatus->getClientUuid();
                                        params["SEND_FILE_UUID"] = structSendStatus->getSendFileUuid();
                                        params["ERROR"] = structSendStatus->getError();
                                        params["TASK_UUID"] = structSendStatus->getTaskUuid();
                                        params["SEND_ADDR_UUID"] = structSendStatus->getSendAddrUuid();
                                        params["STATE"] = structSendStatus->getState();
                                        flg = transaction->execSQL(sql_structSendStatusList,params);
                                        if(!flg)
                                        {
                                            break;
                                        }
                                    }
                                    if(flg == Environment::Db_Transaction_State::TRANS_SUCCESS)
                                    {

                                        transaction->commit();
                                        delete transaction;
                                        return;
                                    }
                                    else
                                    {
                                        DBException excep;
                                        excep.setText(trs("add structSendStatusList error"));
                                        excep.setType(QSqlError::TransactionError);
                                        throw excep;
                                    }
                                }
                                else
                                {
                                    DBException excep;
                                    excep.setText(trs("add structSendFilesList error"));
                                    excep.setType(QSqlError::TransactionError);
                                    throw excep;
                                }
                            }
                            else
                            {
                                DBException excep;
                                excep.setText(trs("add structSendAddrList error"));
                                excep.setType(QSqlError::TransactionError);
                                throw excep;
                            }
                        }
                        else
                        {
                            DBException excep;
                            excep.setText(trs("add structTask error"));
                            excep.setType(QSqlError::TransactionError);
                            throw excep;
                        }
                    }
                    else
                    {
                        DBException excep;
                        excep.setText(trs("add uStructSendStatus error"));
                        excep.setType(QSqlError::TransactionError);
                        throw excep;
                    }
                }
                else
                {
                    DBException excep;
                    excep.setText(trs("add uStructSendFiles error"));
                    excep.setType(QSqlError::TransactionError);
                    throw excep;
                }
            }
            else
            {
                DBException excep;
                excep.setText(trs("add uStructSendAddr error"));
                excep.setType(QSqlError::TransactionError);
                throw excep;
            }
        }
        else
        {

            DBException excep;
            excep.setType(QSqlError::TransactionError);
            excep.setText("add uStructTask error");
            throw excep;
        }
    }
    catch(DBException &ex)
    {
        qDebug() << ex.getText();
        transaction->rollback();
        delete transaction;
        throw ex;
    }
}

void CSUnstructDao::getPubKey(const quint64& terminateUUID, QString& pubKey)
{
    QString sql = "select PUBLIC_KEY from CS_TERMINAL WHERE TERMINAL_UUID =:terminateUUID";
    QVariantMap params;
    params["terminateUUID"]       = terminateUUID;
    DBQuery query;
    QList<QVariantMap> ans = query.list(sql, params);
    if(ans.size() == 1)
    {
        pubKey =  ans.at(0).values().at(0).toString();
    }
    else
    {
        QString excep = trs("The pubkey is not ONLY!");
        throw excep;
    }
}

void CSUnstructDao::getPriKey(const quint64& terminateUUID, QString& priKey)
{
    QString sql = "select PRIVATE_KEY from CS_TERMINAL WHERE TERMINAL_UUID =:terminateUUID";
    QVariantMap params;
    params["terminateUUID"]       = terminateUUID;
    DBQuery query;
    QList<QVariantMap> ans = query.list(sql, params);
    if(ans.size() == 1)
    {
        priKey =  ans.at(0).values().at(0).toString();
    }
    else
    {
        QString excep = trs("The pubkey is not ONLY!");
        throw excep;
    }
}

CsRUnstructSendFiles CSUnstructDao::mapToRUnstructTaskSendFile(const QVariantMap &rowMap) {
    CsRUnstructSendFiles sendFile;
    sendFile.setUuid(rowMap.value("UUID").toString());
    sendFile.setFileName(rowMap.value("FILE_NAME").toString());
    sendFile.setDownUrl(rowMap.value("DOWN_URL").toString());
    sendFile.setFileDestName(rowMap.value("FILE_DEST_NAME").toString());
    sendFile.setSaveAbst(rowMap.value("SAVE_ABST").toString());
    sendFile.setTaskUuid(rowMap.value("TASK_UUID").toString());
    return sendFile;
}
CsRUnstructTask CSUnstructDao::mapToRUnstructTask(const QVariantMap &rowMap) {
    CsRUnstructTask task;
    task.setUuid(rowMap.value("UUID").toString());
    task.setTaskName(rowMap.value("TASK_NAME").toString());
    task.setTaskNum(rowMap.value("TASK_NUM").toInt());
    task.setDescription(rowMap.value("DESCRIPTION").toString());
    task.setSendTime(rowMap.value("SEND_TIME").toString());
    task.setStrategy(rowMap.value("STRATEGY").toInt());
    task.setState((quint8)rowMap.value("STATE").toUInt());
    task.setInsertor(rowMap.value("INSERTOR").toString());
    task.setInsertTime(rowMap.value("INSERT_TIME").toString());
    task.setOperater(rowMap.value("OPERATOR").toString());
    task.setOperaTime(rowMap.value("OPERA_TIME").toString());
    return task;
}



