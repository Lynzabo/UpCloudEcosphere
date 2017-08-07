#include "nsstructdao.h"

NsStructDao::NsStructDao()
{

}

void NsStructDao::insertRTaskAndTaskFiles(NsRStructTask *nsRStructTask, QList<NsRStructSendFiles *> downFiles)
{
    bool fly = Environment::Db_Transaction_State::TRANS_FAIL;
    QString tasksql = "insert into NS_R_STRUCT_TASK(UUID, TASK_NUM, STRATEGY, STATE, EXEC_TIME, INSERT_TIME) values (:uuid, :taskNum, :strategy, :state, :execTime, :insertTime)";

    QVariantMap taskparams;
    taskparams["uuid"] = nsRStructTask->getUuid();
    taskparams["taskNum"] = nsRStructTask->getTaskNum();
    taskparams["strategy"] = nsRStructTask->getStrategy();
    taskparams["state"]    = nsRStructTask->getState();
    taskparams["execTime"]   = nsRStructTask->getExecTime();
    taskparams["insertTime"]   = nsRStructTask->getInsertTime();
    DBTransaction *transaction = new DBTransaction;
    try
    {
        transaction->beginTransaction();
        fly = transaction->execSQL(tasksql,taskparams);
        if(fly == Environment::Db_Transaction_State::TRANS_SUCCESS)
        {
            if(downFiles.size() <= 0)
            {
                transaction->commit();
                qDebug() << trs("操作成功");
                return;
            }
            for(NsRStructSendFiles *sendFile : downFiles)
            {
                QString filesql = "insert into NS_R_STRUCT_SEND_FILES(UUID, FILE_URL, FILE_ABST, SEQUENCE, TASK_UUID, STATE, ERROR) values (:uuid, :fileUrl, :fileAbst, :sequence, :taskUuid, :state, :error)";

                QVariantMap fileparams;
                fileparams["uuid"] = sendFile->getUuid();
                fileparams["fileUrl"] = sendFile->getFileUrl();
                fileparams["fileAbst"] = sendFile->getFileAbst();
                fileparams["sequence"] = sendFile->getSequence();
                fileparams["taskUuid"]    = sendFile->getTaskUuid();
                fileparams["state"]   = sendFile->getState();
                fileparams["error"]   = sendFile->getError();
                fly = transaction->execSQL(filesql,fileparams);
                if(fly == Environment::Db_Transaction_State::TRANS_FAIL)
                {                    
                    goto error;
                }               
            }
            if(fly == Environment::Db_Transaction_State::TRANS_SUCCESS)
            {
                transaction->commit();
                qDebug() << trs("操作成功");
            }
        }
        else
        {
error:
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

QList<NsRStructTask> NsStructDao::dirRTaskByStatus(const quint8 &state, const QString &curTime)
{
    QString sql = "select * from NS_R_STRUCT_TASK WHERE state =:state and INSERT_TIME <:curTime";
    QVariantMap params;
    params["state"]       = state;
    params["curTime"]      = curTime;
    DBQuery query;
    return query.listBeans(mapToRStructTask, sql,params);
}

void NsStructDao::updateRTaskState(const QString &taskUUID, const quint8 &state)
{
    bool fly = Environment::Db_Transaction_State::TRANS_FAIL;
    QString sql = "update NS_R_STRUCT_TASK set STATE =:state where UUID =:uuid";

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
}

QList<NsRStructSendFiles> NsStructDao::dirRSendFilesByTaskUUID(const QString &taskUUID, const quint8 &state)
{
    QString sql = "select * from NS_R_STRUCT_SEND_FILES WHERE TASK_UUID =:taskUUID and STATE =:state";
    QVariantMap params;
    params["taskUUID"]       = taskUUID;
    params["state"]       = state;
    DBQuery query;
    return query.listBeans(mapToRStructSendFiles, sql,params);
}

void NsStructDao::updateRSendFilesStateByUrlAbst(const QString &taskUUID, const QString &fileUrl, const QString &destAbst, const quint8 &state)
{
    bool fly = Environment::Db_Transaction_State::TRANS_FAIL;
    QString sql = "update NS_R_STRUCT_SEND_FILES set STATE =:state,ERROR ='' where TASK_UUID =:taskUUID and FILE_URL =:fileUrl and FILE_ABST =:destAbst";

    QVariantMap params;
    params["taskUUID"]       = taskUUID;
    params["fileUrl"]       = fileUrl;
    params["destAbst"]       = destAbst;
    params["state"]       = state;
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

void NsStructDao::updateRSendFilesState(const QString &taskUUID, const quint8 &oldState, const quint8 &newState)
{
    bool fly = Environment::Db_Transaction_State::TRANS_FAIL;
    QString sql = "update NS_R_STRUCT_SEND_FILES set STATE =:newState where TASK_UUID =:taskUUID and STATE =:oldState";

    QVariantMap params;
    params["taskUUID"]       = taskUUID;
    params["oldState"]       = oldState;
    params["newState"]       = newState;
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

NsRStructTask NsStructDao::getRTaskByUUID(const QString &taskUUID)
{
    QString sql = "select * from NS_R_STRUCT_TASK WHERE UUID =:uuid";
    QVariantMap params;
    params["uuid"]       = taskUUID;
    DBQuery query;
    return query.uniqueBean(mapToRStructTask, sql,params);
}

bool NsStructDao::getRTaskDownloadStatus(const QString &taskUUID, const quint8 &filesState)
{
    QString sql = "select count(UUID) from NS_R_STRUCT_TASK WHERE UUID =:taskUUID and STATE =:state";
    QVariantMap params;
    params["taskUUID"]       = taskUUID;
    params["state"]       = filesState;
    DBQuery query;
    int length = query.selectVariant(sql,params).toInt();
    return length == 0;
}

void NsStructDao::updateRSendFilesState(const QString &taskUUID, const QString &fileUrl, const quint8 &state, const QString &errorMsg)
{
    bool fly = Environment::Db_Transaction_State::TRANS_FAIL;
    QString sendfilesql = "update NS_R_STRUCT_SEND_FILES set STATE =:state,ERROR =:error where TASK_UUID =:taskUUID and FILE_URL =:fileUrl";
    QVariantMap sendfileparams;
    sendfileparams["state"]       = state;
    sendfileparams["error"]       = errorMsg;
    sendfileparams["taskUUID"]       = taskUUID;
    sendfileparams["fileUrl"]       = fileUrl;
    //必须try...catch才能回滚和提交
    DBTransaction *transaction = new DBTransaction;
    try
    {
        transaction->beginTransaction();
        fly = transaction->execSQL(sendfilesql,sendfileparams);
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

void NsStructDao::updateRSendFilesStateByAbst(const QString &taskUUID, const QString &fileAbst, const quint8 &state, const QString &errorMsg)
{
    bool fly = Environment::Db_Transaction_State::TRANS_FAIL;
    QString sendfilesql = "update NS_R_STRUCT_SEND_FILES set STATE =:state,ERROR =:error where TASK_UUID =:taskUUID and FILE_ABST =:fileAbst";
    QVariantMap sendfileparams;
    sendfileparams["state"]       = state;
    sendfileparams["error"]       = errorMsg;
    sendfileparams["taskUUID"]       = taskUUID;
    sendfileparams["fileAbst"]       = fileAbst;
    //必须try...catch才能回滚和提交
    DBTransaction *transaction = new DBTransaction;
    try
    {
        transaction->beginTransaction();
        fly = transaction->execSQL(sendfilesql,sendfileparams);
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

void NsStructDao::getRTaskUuidByTaskNum(QString &taskUUID, const quint32 &taskNum)
{
    QString sql = "select UUID from NS_R_STRUCT_TASK WHERE TASK_NUM =:taskNum";
    QVariantMap params;
    params["taskNum"]       = taskNum;
    DBQuery query;
    taskUUID = query.selectVariant(sql, params).toString();
}

void NsStructDao::getRTaskStateByTaskUUID(const QString &taskUUID, quint8 &state)
{
    QString sql = "select STATE from NS_R_STRUCT_TASK where UUID=:taskUUID";

    QVariantMap params;
    params["taskUUID"]       = taskUUID;
    DBQuery query;
    state = (quint8)query.selectVariant(sql, params).toUInt();
}

void NsStructDao::updateRTaskAndSendFilesStateByUUID(const QString &taskUUID, const quint8 &taskState, const quint8 &sendFileState)
{
    bool fly = Environment::Db_Transaction_State::TRANS_FAIL;
    QVariantMap params;
    params["taskUUID"] = taskUUID;
    params["taskState"] = taskState;
    params["sendFileState"] = sendFileState;
    QString sql_update_task = "update NS_R_STRUCT_TASK set STATE =:taskState where UUID =:taskUUID";
    QString sql_update_sendFile = "update NS_R_STRUCT_SEND_FILES set STATE =:sendFileState where TASK_UUID =:taskUUID";

    DBTransaction *transaction = new DBTransaction;
    try
    {
        DBException excep;
        transaction->beginTransaction();
        fly = transaction->execSQL(sql_update_task,params);
        if(fly == Environment::Db_Transaction_State::TRANS_SUCCESS)
        {
            fly = transaction->execSQL(sql_update_sendFile,params);
            if(fly == Environment::Db_Transaction_State::TRANS_SUCCESS)
            {
                transaction->commit();
                qDebug() << trs("updateRTaskAndSendFilesStateByUUID成功");
                delete transaction;
                return;
            }
            else
            {
                excep.setText(trs("sql_update_sendFile error"));
                goto RollBack;
            }

        }
        else
        {
            excep.setText(trs("sql_update_task error"));
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

void NsStructDao::moveRTask2STask(const QString &taskUUID)
{
    //TODO
    /*
INSERT INTO NS_S_STRUCT_TASK (SELECT * FROM NS_R_STRUCT_TASK WHERE UUID=:o_id)
DELETE FROM NS_R_STRUCT_TASK WHERE UUID=:o_id
INSERT INTO NS_S_STRUCT_SEND_FILES (SELECT * FROM NS_R_STRUCT_SEND_FILES WHERE UUID=:o_id)
DELETE FROM NS_R_STRUCT_SEND_FILES WHERE UUID=:o_id
    */
    bool fly = Environment::Db_Transaction_State::TRANS_FAIL;
    QString sql_insert_stask = "INSERT INTO NS_S_STRUCT_TASK (SELECT * FROM NS_R_STRUCT_TASK WHERE UUID=:o_id)";
    QString sql_delete_rtask = "DELETE FROM NS_R_STRUCT_TASK WHERE UUID=:o_id";
    QString sql_insert_sfile = "INSERT INTO NS_S_STRUCT_SEND_FILES (SELECT * FROM NS_R_STRUCT_SEND_FILES WHERE TASK_UUID=:o_id)";
    QString sql_delete_rfile = "DELETE FROM NS_R_STRUCT_SEND_FILES WHERE TASK_UUID=:o_id";
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
                        transaction->commit();
                        qDebug() << trs("moveRTask2STask成功");
                        delete transaction;
                        return;
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

NsRStructTask NsStructDao::mapToRStructTask(const QVariantMap &rowMap)
{
    NsRStructTask task;
    task.setUuid(rowMap.value("UUID").toString());
    task.setTaskNum((quint32)rowMap.value("TASK_NUM").toUInt());
    task.setStrategy((quint16)rowMap.value("STRATEGY").toUInt());
    task.setState((quint8)rowMap.value("STATE").toUInt());
    task.setExecTime(rowMap.value("EXEC_TIME").toString());
    task.setInsertTime(rowMap.value("INSERT_TIME").toString());
    return task;
}

NsRStructSendFiles NsStructDao::mapToRStructSendFiles(const QVariantMap &rowMap)
{
    NsRStructSendFiles task;
    task.setUuid(rowMap.value("UUID").toString());
    task.setFileUrl(rowMap.value("FILE_URL").toString());
    task.setFileAbst(rowMap.value("FILE_ABST").toString());
    task.setSequence(rowMap.value("SEQUENCE").toUInt());
    task.setTaskUuid(rowMap.value("TASK_UUID").toString());
    task.setState((quint8)rowMap.value("STATE").toUInt());
    task.setError(rowMap.value("ERROR").toString());
    return task;
}

