#include "csstructdao.h"
using namespace Environment::Datagram;
using namespace Environment::Task_Status::Center::Stru;
CSStructDao::CSStructDao()
{

}

void CSStructDao::addTask(const CsRStructTask &task, const QList<CsRStructSendAddr> addrInfoList, const QList<CsRStructSendFiles> fileInfoList, const QList<CsRStructSendStatus> statusInfoList)
{
    bool flg = Environment::Db_Transaction_State::TRANS_FAIL;
    QString sqlForTask = "insert into CS_R_STRUCT_TASK values(:UUID,:TASK_NAME,:TASK_NUM,:DESCRIPTION,:SEND_TIME,:EXEC_TIME,:STRATEGY,:STATE,:INSERTOR,:INSERT_TIME,:OPERATOR,:OPERA_TIME)";
    QString sqlForTaskAddr = "insert into CS_R_STRUCT_SEND_ADDR values(:UUID,:CLIENT_UUID,:TASK_UUID,:GROUP_UUIDS)";
    QString sqlForTaskFile = "insert into CS_R_STRUCT_SEND_FILES values(:UUID,:FILE_NAME,:DOWN_URL,:FILE_DEST_NAME,:SAVE_ABST,:SEQUENCE,:TASK_UUID,:HARD_ABST,:FILE_SRC)";
    QString sqlForTaskStatus = "insert into CS_R_STRUCT_SEND_STATUS values(:UUID,:CLIENT_UUID,:SEND_FILE_UUID,:ERROR,:TASK_UUID,:SEND_ADDR_UUID,:STATE)";
    QVariantMap params;
    params["UUID"] = task.getUuid();
    params["TASK_NAME"] = task.getTaskName();
    params["TASK_NUM"] = task.getTaskNum();
    params["DESCRIPTION"] = task.getDescription();
    params["SEND_TIME"] = task.getSendTime();
    params["EXEC_TIME"] =task.getExecTime();
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
        CsRStructSendAddr addr = addrInfoList.at(i);
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
        CsRStructSendFiles file = fileInfoList.at(i);
        params["UUID"] = file.getUuid();
        params["FILE_NAME"] = file.getFileName();
        params["DOWN_URL"] = file.getDownUrl();
        params["FILE_DEST_NAME"] = file.getFileDestName();
        params["SAVE_ABST"] = file.getSaveAbst();
        params["SEQUENCE"] = file.getSequence();
        params["TASK_UUID"] = file.getTaskUuid();
        params["HARD_ABST"] = file.getHardAbst();
        params["FILE_SRC"] = file.getFileSrc();
        flg = transaction->execSQL(sqlForTaskFile,params);
        if(flg == Environment::Db_Transaction_State::TRANS_FAIL)
        {
            goto err;
        }
    }
    params.clear();
    for(int i = 0;i < statusInfoList.size(); ++i) {
        CsRStructSendStatus status = statusInfoList.at(i);
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

void CSStructDao::updateRTask(const QList<CsRStructTask> &taskList)
{
    bool ok;
    QString taskSql = "UPDATE CS_R_STRUCT_TASK set TASK_NAME = :taskname,TASK_NUM =:tasknum,DESCRIPTION =:description,SEND_TIME =:sendtime,EXEC_TIME =:exectime,STRATEGY =:strategy,STATE =:state,INSERTOR =:insertor,INSERT_TIME =:inserttime,OPERATOR =:operator,OPERA_TIME =:operatime where UUID =:uuid";
    QVariantMap params;
    DBException excep;
    DBTransaction *transaction = new DBTransaction;
    transaction->beginTransaction();
    foreach(const CsRStructTask &task,taskList) {
        params["uuid"] = task.getUuid();
        params["taskname"] = task.getTaskName();
        params["tasknum"] = task.getTaskNum();
        params["description"] = task.getDescription();
        params["sendtime"] = task.getSendTime();
        params["exectime"] = task.getExecTime();
        params["strategy"] = task.getStrategy();
        params["state"] = task.getState();
        params["insertor"] = task.getInsertor();
        params["inserttime"] = task.getInsertTime();
        params["operator"] = task.getOperater();
        params["operatime"] = task.getOperaTime();
        ok = transaction->execSQL(taskSql,params);
        if(!ok){
            goto end;
        }
    }
    transaction->commit();
    delete transaction;
    return;
end:
    transaction->rollback();
    delete transaction;
    excep.setText(trs("操作数据库时出错"));
    excep.setType(QSqlError::TransactionError);
    throw excep;
}
void CSStructDao::addTaskAddr(const CsRStructSendAddr &task)
{
    bool flg = Environment::Db_Transaction_State::TRANS_FAIL;
    QString addTaskAddrSql = "insert into CS_R_STRUCT_SEND_ADDR  values(:UUID,:CLIENT_UUID,:TASK_UUID, :GROUP_UUIDS)";
    QVariantMap params;

    params["UUID"] = task.getUuid();
    params["CLIENT_UUID"]=task.getClientUuid();
    params["TASK_UUID"]=task.getTaskUuid();
    params["GROUP_UUIDS"]=task.getGroupDesc();
    qDebug() << addTaskAddrSql;
    //必须try...catch才能回滚和提交
    DBTransaction *transaction = new DBTransaction;
    try
    {
        transaction->beginTransaction();
        flg = transaction->execSQL(addTaskAddrSql,params);
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

CsRStructTask CSStructDao::dirRTaskByUUid(const QString &uuid)
{
    QString sql =  "select * from CS_R_STRUCT_TASK WHERE UUID =:uuid";
    QVariantMap params;
    params["uuid"] = uuid;
    DBQuery query;
    return query.uniqueBean(mapToRStructTask,sql,params);
}
void CSStructDao::addTaskFile(const CsRStructSendFiles &task)
{
    bool flg = Environment::Db_Transaction_State::TRANS_FAIL;
    QString filesSql="insert into CS_R_struct_SEND_FILES values(:UUID,:FILE_NAME,:DOWN_URL,:FILE_DEST_NAME,:SAVE_ABST,:SEQUENCE,:TASK_UUID,:HARD_ABST,:FILE_SRC)";
    QVariantMap params;

    params["UUID"] = task.getUuid();
    params["FILE_NAME"] = task.getFileName();
    params["FILE_DEST_NAME"] = task.getFileDestName();
    params["DOWN_URL"] = task.getDownUrl();
    params["SAVE_ABST"] = task.getSaveAbst();
    params["TASK_UUID"] = task.getTaskUuid();
    params["SEQUENCE"] = task.getSequence();
    params["HARD_ABST"] = task.getHardAbst();
    params["FILE_SRC"] = task.getFileSrc();
    //必须try...catch才能提交与回滚
    DBTransaction *transaction = new DBTransaction;
    try
    {
        transaction->beginTransaction();
        flg = transaction->execSQL(filesSql,params);
        if(flg==Environment::Db_Transaction_State::TRANS_SUCCESS)
        {
            transaction->commit();
        }
        else
        {
            DBException excep;
            excep.setType(QSqlError::TransactionError);
            excep.setText("add task files error!");
            throw excep;
        }
    }
    catch(DBException ex)
    {
        qDebug()<<ex.getText();
        transaction->rollback();
        delete transaction;
        throw ex;
    }
    delete transaction;
}

QList<CsRStructTask> CSStructDao::dirRTask(const QVariantMap &map)
{
    QString sql = "select * from CS_R_STRUCT_TASK WHERE 1 = 1";
    QVariantMap params;
    if(!map.value("description").toString().isEmpty()){
        params["descritpion"] = map.value("description").toString();
        sql.append(" and DESCRIPTION =:description");
    }
    if(!map.value("taskname").toString().isEmpty()) {
        QString taskName = "%";
        taskName.append(map.value("taskname").toString()).append("%");
        params["taskname"] = taskName;
        sql.append(" and upper(TASK_NAME) LIKE upper(:taskname)");
    }
    if(!map.value("insertor").toString().isEmpty()) {
        QString insertor = "%";
        insertor.append(map.value("insertor").toString()).append("%");
        params["insertor"] = insertor;
        sql.append(" and upper(INSERTOR) LIKE upper(:insertor)");
    }
    if(!map.value("tasknum").toString().isEmpty()){
        params["tasknum"] = (quint32)map.value("tasknum").toInt();
        sql.append(" and TASK_NUM =:tasknum");
    }
    if(!map.value("strategy").toString().isEmpty()){
        params["strategy"] = (quint16)map.value("strategy").toInt();
        sql.append(" and STRATEGY =:strategy");
    }
    if(!map.value("state").toString().isEmpty()){
        params["state"] = (quint8)map.value("state").toInt();
        sql.append(" and STATE =:state");
    }
    if(!map.value("sendtime").toString().isEmpty()) {
        params["sendtime"] = map.value("sendtime").toString();
        sql.append(" and SEND_TIME =:sendtime");
    }
    if(!map.value("exectime").toString().isEmpty()) {
        params["exectime"] = map.value("exectime").toString();
        sql.append(" and SEND_TIME =:exectime");
    }
    if(map.contains("send_time_begin")) {
        params["send_time_begin"] = map.value("send_time_begin");
        params["send_time_end"] = map.value("send_time_end");
        sql.append(" and SEND_TIME between :send_time_begin and :send_time_end");
    }
    if(map.contains("exec_time_begin")) {
        params["exec_time_begin"] = map.value("exec_time_begin");
        params["exec_time_end"] = map.value("exec_time_end");
        sql.append(" and EXEC_TIME between :exec_time_begin and :exec_time_end");
    }

    sql.append(" union all ");


    sql.append("select * from CS_S_STRUCT_TASK WHERE 1 = 1");
    if(!map.value("description").toString().isEmpty()){
        params["s_descritpion"] = map.value("description").toString();
        sql.append(" and DESCRIPTION =:s_description");
    }
    if(!map.value("taskname").toString().isEmpty()) {
        QString taskName = "%";
        taskName.append(map.value("taskname").toString()).append("%");
        params["s_taskname"] = taskName;
        sql.append(" and upper(TASK_NAME) LIKE upper(:s_taskname)");
    }
    if(!map.value("insertor").toString().isEmpty()) {
        QString insertor = "%";
        insertor.append(map.value("insertor").toString()).append("%");
        params["s_insertor"] = insertor;
        sql.append(" and upper(INSERTOR) LIKE upper(:s_insertor)");
    }
    if(!map.value("tasknum").toString().isEmpty()){
        params["s_tasknum"] = (quint32)map.value("tasknum").toInt();
        sql.append(" and TASK_NUM =:s_tasknum");
    }
    if(!map.value("strategy").toString().isEmpty()){
        params["s_strategy"] = (quint16)map.value("strategy").toInt();
        sql.append(" and STRATEGY =:s_strategy");
    }
    if(!map.value("state").toString().isEmpty()){
        params["s_state"] = (quint8)map.value("state").toInt();
        sql.append(" and STATE =:s_state");
    }
    if(map.contains("send_time_begin")) {
        params["s_send_time_begin"] = map.value("send_time_begin");
        params["s_send_time_end"] = map.value("send_time_end");
        sql.append(" and SEND_TIME between :s_send_time_begin and :s_send_time_end");
    }
    if(map.contains("exec_time_begin")) {
        params["s_exec_time_begin"] = map.value("exec_time_begin");
        params["s_exec_time_end"] = map.value("exec_time_end");
        sql.append(" and EXEC_TIME between :s_exec_time_begin and :s_exec_time_end");
    }

    DBQuery query;
    return query.listBeans(mapToRStructTask,sql,params);
}

QList<CsRStructTask> CSStructDao::pageTask(const QVariantMap &map, Page *page)
{
    QString sql = "SELECT * "
                  "FROM "
                  "( SELECT * FROM CS_R_STRUCT_TASK "
                  "UNION ALL "
                  "SELECT * FROM CS_S_STRUCT_TASK "
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
    if(!map.value("exec_time_begin").toString().isEmpty())
    {
        params["exec_time_begin"] = map.value("exec_time_begin");
        sql.append(" and SEND_TIME >=:exec_time_begin");
    }
    if(!map.value("exec_time_end").toString().isEmpty())
    {
        params["exec_time_end"] = map.value("exec_time_end");
        sql.append(" and SEND_TIME <=:exec_time_end");
    }

    //order by
    sql.append(QString(" order by %1 %2")//order by column1 desc/asc
               .arg(!(page->getOrderFieldName().isEmpty()) ? page->getOrderFieldName() : "SEND_TIME")
               .arg(page->getOrderField() == Qt::DescendingOrder?"DESC":"ASC")
               );
    DBQuery query;
    return query.pageBean(mapToRStructTask,page,sql,params);
}

QList<CsRStructTask> CSStructDao::dirRTask(const quint8 &status, const QString &curTime)
{
    const QString sql="select * from CS_R_STRUCT_TASK where STATE=:state and SEND_TIME<:curTime";
    QVariantMap params;
    params["state"]       = status;
    params["curTime"]     = curTime;
    DBQuery query;
    return query.listBeans(mapToRStructTask, sql, params);
}

void CSStructDao::updateRTaskState(const QString &taskUUID, const quint8 &state)
{
    bool fly = Environment::Db_Transaction_State::TRANS_FAIL;
    QString sql = "update CS_R_STRUCT_TASK set STATE =:state where UUID =:uuid";

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
void CSStructDao::updateRTaskSendStatusByUUID(const QString &taskUuid,const QStringList &UUID, const quint8 &state)
{
    bool fly = Environment::Db_Transaction_State::TRANS_FAIL;
    QString sql = "update CS_R_STRUCT_SEND_STATUS set STATE=:state,ERROR=:error where UUID in(:uuids)";
    //查询任务状态
    QString sqlForState = "select * from CS_R_STRUCT_TASK where UUID =:taskUUID";
    //修改任务状态
    QString sqlForTask = "update CS_R_STRUCT_TASK set STATE = :taskState,SEND_TIME =:sendTime where UUID = :taskUUID";
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
                CsRStructTask task = query.uniqueBean(mapToRStructTask, sqlForState,params);
                quint8 taskState = task.getState();
                if(taskState == Task_State::DOWNERROR ||
                        taskState == Task_State::SENDERROR ||
                        taskState == Task_State::TASKERROR ||
                        taskState == Task_State::PARSEERROR)
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
void CSStructDao::delRTask(const QStringList &uuids)
{
    QVariantMap params;params.clear();
    bool ok;
    QString sql  = "DELETE CS_R_STRUCT_SEND_STATUS where TASK_UUID in (:uuids)";
    params.insert("uuids", (QVariant)uuids);
    DBTransaction* transaction = new DBTransaction;
    transaction->beginTransaction();
    ok = transaction->execSQL(sql,params);
    if(!ok) {
        goto end;
    }

    sql = "delete CS_R_STRUCT_SEND_FILES where TASK_UUID in (:uuids)";
    ok = transaction->execSQL(sql,params);
    if(!ok) {
        goto end;
    }
    sql = "delete CS_R_STRUCT_SEND_ADDR where TASK_UUID in (:uuids)";
    ok = transaction->execSQL(sql,params);
    if(!ok) {
        goto end;
    }
    sql = "delete CS_R_STRUCT_TASK where UUID in (:uuids)";
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

void CSStructDao::addRSendAddr(const QString &taskUuid, const QStringList &nodes,const QStringList groupDes)
{
    QString sql = "INSERT INTO CS_R_STRUCT_SEND_ADDR values(:uuid,:clientuuid,:taskuuid,:groupDes)";
    QString sqlForStatus = "insert into CS_R_STRUCT_SEND_STATUS values(:statusUuid,:clientuuid,:SEND_FILE_UUID,:ERROR,:taskuuid,:uuid,:STATE)";
    QString sqlForFile = "select * from CS_R_STRUCT_SEND_FILES where TASK_UUID  = :taskuuid";
    QVariantMap params;
    bool ok;
    QString uuid;uuid.clear();
    UuidUtil::nextUUID(uuid);
    params["taskuuid"] = taskUuid;
    params["STATE"] = SendStatus_State::USABLE;
    DBQuery dbquery;
    QList<CsRStructSendFiles> fileList =  dbquery.listBeans(mapToRStructTaskSendFile,sqlForFile,params);

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
            CsRStructSendFiles file = fileList.at(i);
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

void CSStructDao::delRSendAddr(const QString &taskUuid, const QStringList &nodes)
{
    QString sql = "DELETE CS_R_STRUCT_SEND_ADDR where TASK_UUID =:taskuuid and CLIENT_UUID IN (:nodes)";
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

QList<CsRStructSendAddr> CSStructDao::dirRSendAddr(const QString &taskUuid, const QStringList &nodes)
{
    QString sql = "select * from CS_R_STRUCT_SEND_ADDR WHERE TASK_UUID =:taskuuid and CLIENT_UUID IN (:nodes)";
    QVariantMap params;
    params["taskuuid"]       = taskUuid;
    params.insert("nodes", (QVariant)nodes);
    DBQuery query;
    return query.listBeans(mapToRStructTaskSendAddr, sql, params);
}

QList<VCsRStructSendAddr> CSStructDao::pageAddrByTaskUuid(const QString &taskUUID,Page* page)
{
    QString sql = "select * from (select a.*,g.DESCRIPTION from CS_R_STRUCT_SEND_ADDR a,CS_CLIENT_TERMINAL g WHERE TASK_UUID =:taskUUID and a.CLIENT_UUID = g.TERMINAL_UUID)";
    //order by
    sql.append(QString(" order by %1 %2")//order by column1 desc/asc
               .arg(!(page->getOrderFieldName().isEmpty()) ? page->getOrderFieldName() : "CLIENT_UUID")
               .arg(page->getOrderField() == Qt::DescendingOrder?"DESC":"ASC")
               );
    QVariantMap params;
    params["taskUUID"]       = taskUUID;
    DBQuery query;
    return query.pageBean(mapToRVStructTaskSendAddr,page, sql, params);
}

QList<CsRStructSendStatus> CSStructDao::pageRSendStatusByTaskUuidAndClientUuid(const QString &taskUuid, const QString &clientUuid,QStringList &paramsList,Page* page)
{
    QString sql = "select * from (SELECT s.*,f.FILE_NAME FROM CS_R_STRUCT_SEND_STATUS s,CS_R_STRUCT_SEND_FILES f"
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
    QList<CsRStructSendStatus> statusList;
    for(int i = 0;i < list.size(); ++i) {
        QVariantMap rowMap = list.at(i);
        CsRStructSendStatus status = mapToStructSendStatus(rowMap);
        statusList.append(status);
        paramsList << rowMap.value("FILE_NAME").toString();
    }
    return statusList;
}

QList<CsRStructSendStatus> CSStructDao::pageRSendStatusByTaskUuidAndSendFileUUid(const QString &taskUuid, const QString &fileUuids, QStringList &paramsList, Page *page)
{
    QString sql = "select * from (SELECT s.*,n.description,r.group_uuids FROM CS_R_STRUCT_SEND_STATUS s,CS_CLIENT_TERMINAL n,cs_r_struct_send_addr r"
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
    QList<CsRStructSendStatus> statusList;
    for(int i = 0;i < list.size(); ++i) {
        QVariantMap rowMap = list.at(i);
        CsRStructSendStatus status = mapToStructSendStatus(rowMap);
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
void CSStructDao::dirRSendAddrsAndFilseByTaskUUID(const QString &taskUUID,
                                                  const quint8 state,
                                                  QList<CsRStructSendAddr>& addrs,
                                                  QList<CsRStructSendFiles>& files)
{
    addrs.clear();
    files.clear();

    QString sql = "select * from CS_R_STRUCT_SEND_STATUS WHERE TASK_UUID =:taskUUID and STATE=:state";
    QVariantMap params;
    params["taskUUID"]    = taskUUID;
    params["state"]       = state;
    DBQuery query;
    QList<CsRStructSendStatus> status = query.listBeans(mapToStructSendStatus, sql, params);
    if(status.size() > 0)
    {
        QSet<QString> addruUUIDS;addruUUIDS.clear();
        QSet<QString> fileUUIDS; fileUUIDS.clear();
        foreach (CsRStructSendStatus state, status)
        {
            addruUUIDS.insert(state.getSendAddrUuid());
            fileUUIDS.insert(state.getSendFileUuid());
        }

        //addrs
        QList<QVariantMap> rowMap;

        QString sql_addr = "select * from CS_R_STRUCT_SEND_ADDR WHERE TASK_UUID =:taskUUID and UUID=:addrUUID";
        foreach (QString addrUUID, addruUUIDS)
        {
            params.clear();
            params["taskUUID"]    = taskUUID;
            params["addrUUID"]    = addrUUID;

            rowMap.clear();
            rowMap = query.list(sql_addr, params);
            if(rowMap.size()>0)
            {
                addrs.append(mapToRStructTaskSendAddr(rowMap.first()));
            }
        }

        //fiels
        QString sql_file = "select * from CS_R_STRUCT_SEND_FILES WHERE TASK_UUID =:taskUUID and UUID=:fileUUID";
        foreach (QString fileUUID, fileUUIDS)
        {
            params.clear();
            params["taskUUID"]    = taskUUID;
            params["fileUUID"]    = fileUUID;

            rowMap.clear();
            rowMap = query.list(sql_file, params);
            if(rowMap.size()>0)
            {
                files.append(mapToRStructTaskSendFile(rowMap.first()));
            }
        }
    }
}

void CSStructDao::updateSendStatus(const QString &taskUUID, const quint8 &oldState, const quint8 &newState, const QString &addrError)
{
    bool fly = Environment::Db_Transaction_State::TRANS_FAIL;
    QString sql = "update CS_R_STRUCT_SEND_STATUS set STATE =:newState,ERROR =:error where TASK_UUID =:taskUUID and STATE=:oldState";
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

void CSStructDao::updateSendStatusByAddr(const QString &taskUUID,
                                         const quint8 &oldState,
                                         const quint8 &newState,
                                         const QString &addrError,
                                         const QString &clientUUID)
{
    bool fly = Environment::Db_Transaction_State::TRANS_FAIL;
    QString sql = "update CS_R_STRUCT_SEND_STATUS set STATE =:newState,ERROR =:addrError where TASK_UUID =:taskUUID and CLIENT_UUID =:clientUUID and STATE=:oldState";
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

bool CSStructDao::getSendStatusState(const QString &taskUUID, const quint8 sendState)
{
    QString sql = "select * from CS_R_STRUCT_SEND_STATUS WHERE TASK_UUID =:taskUUID";
    QVariantMap params;
    params["taskUUID"]    = taskUUID;
    DBQuery query;
    QList<CsRStructSendStatus> status = query.listBeans(mapToStructSendStatus, sql, params);
    if(status.size() > 0 )
    {
        foreach (CsRStructSendStatus statu, status)
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

void CSStructDao::updateRSendAddrByTaskUUID(const QString &taskUUID, const QString &clientUUID, const quint8 &state, const QString &clientError)
{
    bool fly = Environment::Db_Transaction_State::TRANS_FAIL;
    QString sql = "update CS_R_STRUCT_SEND_STATUS set STATE =:state,ERROR =:error where TASK_UUID =:taskUUID and CLIENT_UUID =:clientUUID";

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

QList<CsRStructSendFiles> CSStructDao::dirRSendFiles(const QString &taskUuid, const QStringList &newNameList)
{
    QString sql = "select * from CS_R_STRUCT_SEND_FILES WHERE TASK_UUID =:taskuuid and FILE_DEST_NAME IN (:newNameList)";
    QVariantMap params;
    params["taskuuid"]       = taskUuid;
    params.insert("newNameList", (QVariant)newNameList);
    DBQuery query;
    return query.listBeans(mapToRStructTaskSendFile, sql,params);
}

void CSStructDao::delRSendFiles(const QString &taskUuid, const QStringList &uuidList)
{
    QString sql = "DELETE CS_R_STRUCT_SEND_STATUS where TASK_UUID =:taskuuid and SEND_FILE_UUID IN (:uuidList)";
    QVariantMap params;
    bool ok;
    params["taskuuid"] = taskUuid;
    params.insert("uuidList", (QVariant)uuidList);
    DBTransaction* transaction = new DBTransaction;
    transaction->beginTransaction();
    ok = transaction->execSQL(sql,params);
    if(!ok) {
        goto end;
    }
    sql = "DELETE CS_R_STRUCT_SEND_FILES where uuid IN (:uuidList)";
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

void CSStructDao::addRSendFiles(const QString &taskUuid, const QList<CsRStructSendFiles> &fileList,const QList<CsRStructSendStatus> &statusList)
{
    QString sqlForFile = "INSERT INTO CS_R_STRUCT_SEND_FILES values(:uuid,:filename,:downurl,:filedestname,:saveabst,:sequence,:taskuuid,:hardAbst,:fileSrc)";
    QString sqlForStatus = "insert into CS_R_STRUCT_SEND_STATUS values(:uuid,:clientUuid,:sendFileUuid,:error,:taskuuid,:sendAddrUuid,:state)";
    bool ok;
    QVariantMap params;
    QString uuid;uuid.clear();
    params["taskuuid"] = taskUuid;
    DBTransaction* transaction = new DBTransaction;
    transaction->beginTransaction();
    int i= 0;
    for(i =0 ;i < fileList.size();++i) {
        CsRStructSendFiles file = fileList.at(i);
        params["filedestname"] = file.getFileDestName();
        params["sequence"] = QString::number((quint32)file.getSequence());
        params["saveabst"] = file.getSaveAbst();
        params["filename"] = file.getFileName();
        params["downurl"] = file.getDownUrl();
        params["hardAbst"] = file.getHardAbst();
        params["fileSrc"] = file.getFileSrc();
        params["uuid"] = file.getUuid();
        ok = transaction->execSQL(sqlForFile,params);
        if(!ok) {
            goto end;
        }
    }
    for(i = 0;i < statusList.size(); ++i) {
        CsRStructSendStatus status = statusList.at(i);
        params["uuid"] = status.getUuid();
        params["clientUuid"] = status.getClientUuid();
        params["sendFileUuid"] = status.getSendFileUuid();
        params["error"] = status.getError();
        params["sendAddrUuid"] = status.getSendAddrUuid();
        params["state"] = status.getState();
        ok = transaction->execSQL(sqlForStatus,params);
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
    DBException execp;
    execp.setText(trs("添加数据错误"));
    execp.setType(QSqlError::TransactionError);
    throw execp;
}

QList<CsRStructSendFiles> CSStructDao::dirRSendFilesByTaskUUID(const QString &taskUUID)
{
    QString sql = "select * from CS_R_STRUCT_SEND_FILES WHERE TASK_UUID =:taskUUID";
    QVariantMap params;
    params["taskUUID"]       = taskUUID;
    DBQuery query;
    return query.listBeans(mapToRStructTaskSendFile, sql,params);
}

QList<VCsRStructSendFiles> CSStructDao::pageFileByTaskUuid(const QString &taskUUID,Page* page)
{
    QString sql = "select * from CS_R_STRUCT_SEND_FILES WHERE TASK_UUID =:taskUUID";
    //order by
    sql.append(QString(" order by %1 %2")//order by column1 desc/asc
               .arg(!(page->getOrderFieldName().isEmpty()) ? page->getOrderFieldName() : "FILE_NAME")
               .arg(page->getOrderField() == Qt::DescendingOrder?"DESC":"ASC")
               );
    QVariantMap params;
    params["taskUUID"]       = taskUUID;
    DBQuery query;
    return query.pageBean(mapToVStructTaskSendFile,page, sql,params);
}

VCsRStructSendFiles CSStructDao::mapToVStructTaskSendFile(const QVariantMap &rowMap)
{
    VCsRStructSendFiles vsendfiles;

    vsendfiles.setUuid(rowMap.value("UUID").toString());
    vsendfiles.setFileName(rowMap.value("FILE_NAME").toString());
    vsendfiles.setDownUrl(rowMap.value("DOWN_URL").toString());
    vsendfiles.setFileDestName(rowMap.value("FILE_DEST_NAME").toString());
    vsendfiles.setSaveAbst(rowMap.value("SAVE_ABST").toString());
    vsendfiles.setSequence((quint32)rowMap.value("SEQUENCE").toUInt());
    vsendfiles.setTaskUuid(rowMap.value("TASK_UUID").toString());
    vsendfiles.setHardAbst(rowMap.value("HARD_ABST").toString());
    vsendfiles.setFileSrc((quint8)rowMap.value("FILE_SRC").toUInt());
    QString sql = "select distinct state from CS_R_STRUCT_SEND_STATUS where"
                  " SEND_FILE_UUID =:sendFileUuid and TASK_UUID =:taskUuid";
    DBQuery query;
    QVariantMap params;
    params["sendFileUuid"] = vsendfiles.getUuid();
    params["taskUuid"] =  vsendfiles.getTaskUuid();
    QList<QVariantMap> Vstate =   query.list(sql,params);
    QList<quint8> stateList;
    foreach(const QVariantMap &state,Vstate) {
        stateList.append((quint8)state.value("STATE").toInt());
    }
    vsendfiles.setState(defaultStrategy(stateList));

    return vsendfiles;
}

quint8 CSStructDao::defaultStrategy(const QList<quint8> &stateList)
{
    if(stateList.contains(SendStatus_State::SENDERROR)) {
        return SendStatus_State::SENDERROR;
    }
    else if(stateList.contains(SendStatus_State::DOWNERROR)) {
        return SendStatus_State::DOWNERROR;
    }
    else if(stateList.contains(SendStatus_State::PARSEERROR)){
        return SendStatus_State::PARSEERROR;
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
    else if(stateList.contains(SendStatus_State::PARSESUCCESS)) {
        return SendStatus_State::PARSESUCCESS;
    }
}


void CSStructDao::updateRTaskAndAddr(const QString &taskUUID, const QStringList &nodes, const quint8 state)
{
    //错误描述需要清空
    bool fly = Environment::Db_Transaction_State::TRANS_FAIL;
    QString sql = "update CS_R_STRUCT_SEND_STATUS set STATE=:state,ERROR=:error where TASK_UUID=:taskUUID and CLIENT_UUID in(:uuids)";
    //查询任务状态
    QString sqlForState = "select * from CS_R_STRUCT_TASK where UUID =:taskUUID";
    //修改任务状态
    QString sqlForTask = "update CS_R_STRUCT_TASK set STATE = :taskState,SEND_TIME =:sendTime where UUID = :taskUUID";
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
                CsRStructTask task = query.uniqueBean(mapToRStructTask, sqlForState,params);
                quint8 taskState = task.getState();
                if(taskState == Task_State::DOWNERROR ||
                        taskState == Task_State::SENDERROR ||
                        taskState == Task_State::TASKERROR||
                        taskState == Task_State::PARSEERROR)
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
void CSStructDao::updateRTaskAndFile(const QString &taskUUID, const QStringList &nodes, const quint8 state)
{
    //错误描述需要清空
    bool fly = Environment::Db_Transaction_State::TRANS_FAIL;
    QString sql = "update CS_R_STRUCT_SEND_STATUS set STATE=:state,ERROR=:error where SEND_FILE_UUID in(:uuids)";
    //查询任务状态
    QString sqlForState = "select * from CS_R_STRUCT_TASK where UUID =:taskUUID";
    //修改任务状态
    QString sqlForTask = "update CS_R_STRUCT_TASK set STATE = :taskState,SEND_TIME =:sendTime where UUID = :taskUUID";
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
                CsRStructTask task = query.uniqueBean(mapToRStructTask, sqlForState,params);
                quint8 taskState = task.getState();
                if(taskState == Task_State::DOWNERROR ||
                        taskState == Task_State::SENDERROR ||
                        taskState == Task_State::TASKERROR||
                        taskState == Task_State::PARSEERROR)
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

void CSStructDao::updateRTaskAndAddr(const QString &taskUUID,
                                     const quint8 &taskOldState,
                                     const quint8 &taskNewState,
                                     const QString &clientUUID,
                                     const quint8 &addrOldState,
                                     const quint8 &addrNewState,
                                     const QString &addrError)
{
    bool fly = Environment::Db_Transaction_State::TRANS_FAIL;
    QString tasksql = "update CS_R_STRUCT_TASK set STATE =:newstate where UUID =:uuid and STATE=:oldstate";

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
            QString addrsql = "update CS_R_STRUCT_SEND_STATUS set STATE =:addrNewState,ERROR =:error where TASK_UUID =:taskUUID and CLIENT_UUID =:clientUUID and STATE=:addrOldState";
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



void CSStructDao::getRTaskUuidByTaskNum(QString &taskUUID, const quint32 &taskNum)
{
    QString sql = "select UUID from CS_R_STRUCT_TASK WHERE TASK_NUM =:taskNum";
    QVariantMap params;
    params["taskNum"]       = taskNum;
    DBQuery query;
    taskUUID = query.selectVariant(sql, params).toString();
}

void CSStructDao::getErrorMsgByState(const quint8 &taskState, QString &errorMsg)
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
    case Stru_Data_Trans::Resp_Info_State::_8:
        errorMsg = Stru_Data_Trans::Resp_Info_State::_8_DESC_ExecTimeIsNull;
        break;
        //执行时刻不符合日期格式yyyy-mm-dd hh:mm:ss
    case Stru_Data_Trans::Resp_Info_State::_9:
        errorMsg = Stru_Data_Trans::Resp_Info_State::_9_DESC_ExecTimeFormatError;
        break;
        //解析文件下载地址失败
    case Stru_Data_Trans::Resp_Info_State::_A:
        errorMsg = Stru_Data_Trans::Resp_Info_State::_A_DESC_ParseFileDownLoadAddrFail;
        break;
        //解析文件保存地址失败
    case Stru_Data_Trans::Resp_Info_State::_B:
        errorMsg = Stru_Data_Trans::Resp_Info_State::_B_DESC_ParseFileSaveAddrFail;
        break;
        //创建结构化任务入库失败
    case Stru_Data_Trans::Resp_Info_State::_C:
        errorMsg = Stru_Data_Trans::Resp_Info_State::_C_DESC_DBTransactionFail;
        break;
    default:
        break;
    }
}

void CSStructDao::updateSendStateErrorInfo(const QString &taskUUID,
                                           const quint8 &oldState,
                                           const quint8 &newState,
                                           const QString &clientUUID,
                                           const QVector<Result *> &Errors)
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
            sendStatussql += "CS_R_STRUCT_SEND_STATUS ";
            sendStatussql += "SET ";
            sendStatussql += "STATE = :newState ";
            sendStatussql += "ERROR = :error ";
            sendStatussql += "WHERE SEND_FILE_UUID IN ";
            sendStatussql += "(SELECT ";
            sendStatussql += "UUID ";
            sendStatussql += "FROM ";
            sendStatussql += "CS_R_STRUCT_SEND_FILES ";
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

void CSStructDao::getRTaskStateByTaskUUID(const QString &taskUUID, quint8 &state)
{
    QString sql = "select STATE from CS_R_STRUCT_TASK where UUID=:taskUUID";

    QVariantMap params;
    params["taskUUID"]       = taskUUID;
    DBQuery query;
    state = (quint8)query.selectVariant(sql, params).toUInt();
}

void CSStructDao::moveRTask2STask(const QString &taskUUID)
{
    /*
INSERT INTO CS_S_STRUCT_TASK (SELECT * FROM CS_R_STRUCT_TASK WHERE UUID=:o_id)
DELETE FROM CS_R_STRUCT_TASK WHERE UUID=:o_id
INSERT INTO CS_S_STRUCT_SEND_FILES (SELECT * FROM CS_R_STRUCT_SEND_FILES WHERE UUID=:o_id)
DELETE FROM CS_R_STRUCT_SEND_FILES WHERE UUID=:o_id
INSERT INTO CS_S_STRUCT_SEND_ADDR (SELECT * FROM CS_R_STRUCT_SEND_ADDR WHERE UUID=:o_id)
DELETE FROM CS_R_STRUCT_SEND_ADDR WHERE UUID=:o_id
    */
    bool fly = Environment::Db_Transaction_State::TRANS_FAIL;
    QString sql_insert_stask = "INSERT INTO CS_S_STRUCT_TASK (SELECT * FROM CS_R_STRUCT_TASK WHERE UUID=:o_id)";
    QString sql_delete_rtask = "DELETE FROM CS_R_STRUCT_TASK WHERE UUID=:o_id";
    QString sql_insert_sfile = "INSERT INTO CS_S_STRUCT_SEND_FILES (SELECT * FROM CS_R_STRUCT_SEND_FILES WHERE TASK_UUID=:o_id)";
    QString sql_delete_rfile = "DELETE FROM CS_R_STRUCT_SEND_FILES WHERE TASK_UUID=:o_id";
    QString sql_insert_saddr = "INSERT INTO CS_S_STRUCT_SEND_ADDR (SELECT * FROM CS_R_STRUCT_SEND_ADDR WHERE TASK_UUID=:o_id)";
    QString sql_delete_raddr = "DELETE FROM CS_R_STRUCT_SEND_ADDR WHERE TASK_UUID=:o_id";
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


CsRStructTask CSStructDao::mapToRStructTask(const QVariantMap &rowMap)
{
    CsRStructTask task;
    task.setUuid(rowMap.value("UUID").toString());
    task.setTaskName(rowMap.value("TASK_NAME").toString());
    task.setTaskNum(rowMap.value("TASK_NUM").toUInt());
    task.setDescription(rowMap.value("DESCRIPTION").toString());
    task.setSendTime(rowMap.value("SEND_TIME").toString());
    task.setExecTime(rowMap.value("EXEC_TIME").toString());
    task.setStrategy((quint16)(rowMap.value("STRATEGY").toUInt()));
    task.setState((quint8)rowMap.value("STATE").toUInt());
    task.setInsertor(rowMap.value("INSERTOR").toString());
    task.setInsertTime(rowMap.value("INSERT_TIME").toString());
    task.setOperater(rowMap.value("OPERATOR").toString());
    task.setOperaTime(rowMap.value("OPERA_TIME").toString());
    return task;
}

CsRStructSendFiles CSStructDao::mapToRStructTaskSendFile(const QVariantMap &rowMap)
{
    CsRStructSendFiles sendFile;
    sendFile.setUuid(rowMap.value("UUID").toString());
    sendFile.setFileName(rowMap.value("FILE_NAME").toString());
    sendFile.setDownUrl(rowMap.value("DOWN_URL").toString());
    sendFile.setFileDestName(rowMap.value("FILE_DEST_NAME").toString());
    sendFile.setSaveAbst(rowMap.value("SAVE_ABST").toString());
    sendFile.setSequence(rowMap.value("SEQUENCE").toUInt());
    sendFile.setTaskUuid(rowMap.value("TASK_UUID").toString());
    return sendFile;
}

CsRStructSendAddr CSStructDao::mapToRStructTaskSendAddr(const QVariantMap &rowMap)
{
    CsRStructSendAddr addr;
    addr.setUuid(rowMap.value("UUID").toString());
    addr.setClientUuid(rowMap.value("CLIENT_UUID").toString());
    addr.setTaskUuid(rowMap.value("TASK_UUID").toString());
    addr.setGroupDesc(rowMap.value("GROUP_UUIDS").toString());
    return addr;
}

CsRStructSendStatus CSStructDao::mapToStructSendStatus(const QVariantMap &rowMap)
{
    CsRStructSendStatus status;
    status.setUuid(rowMap.value("UUID").toString());
    status.setClientUuid(rowMap.value("CLIENT_UUID").toString());
    status.setSendFileUuid(rowMap.value("SEND_FILE_UUID").toString());
    status.setError(rowMap.value("ERROR").toString());
    status.setTaskUuid(rowMap.value("TASK_UUID").toString());
    status.setSendAddrUuid(rowMap.value("SEND_ADDR_UUID").toString());
    status.setState((quint8)rowMap.value("STATE").toUInt());
    return status;
}

VCsRStructSendAddr CSStructDao::mapToRVStructTaskSendAddr(const QVariantMap &rowMap)
{
    VCsRStructSendAddr addr;
    addr.setUuid(rowMap.value("UUID").toString());
    addr.setClientUuid(rowMap.value("CLIENT_UUID").toString());
    addr.setGroupDesc(rowMap.value("GROUP_UUIDS").toString());
    addr.setTaskUuid(rowMap.value("TASK_UUID").toString());
    addr.setDescription(rowMap.value("DESCRIPTION").toString());
    QString sql = "select distinct state from CS_R_STRUCT_SEND_STATUS where"
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

