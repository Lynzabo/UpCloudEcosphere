#include "nsunstructdao.h"

NsUnstructDao::NsUnstructDao()
{

}

QList<NsRUnstructTask> NsUnstructDao::dirRTaskByStatus(const quint8 &state, const QString &curTime)
{
    QString sql = "select * from NS_R_UNSTRUCT_TASK WHERE state =:state and INSERT_TIME <:curTime";
    QVariantMap params;
    params["state"]       = state;
    params["curTime"]      = curTime;
    DBQuery query;
    return query.listBeans(mapToRUnstructTask, sql,params);
}

void NsUnstructDao::updateRTaskState(const QString &taskUUID, const quint8 &state)
{
    bool fly = Environment::Db_Transaction_State::TRANS_FAIL;
    QString sql = "update NS_R_UNSTRUCT_TASK set STATE =:state where UUID =:uuid";

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

void NsUnstructDao::getRTaskNumByTaskUUID(const QString &taskUUID, quint32 &taskNum)
{
    QString sql = "select TASK_NUM from NS_R_UNSTRUCT_TASK WHERE UUID =:taskUUID";
    QVariantMap params;
    params["taskUUID"]       = taskUUID;
    DBQuery query;
    taskNum = (quint32)query.selectVariant(sql, params).toUInt();
}

void NsUnstructDao::getRTaskUuidByTaskNum(QString &taskUUID, const quint32 &taskNum)
{
    QString sql = "select UUID from NS_R_UNSTRUCT_TASK WHERE TASK_NUM =:taskNum";
    QVariantMap params;
    params["taskNum"]       = taskNum;
    DBQuery query;
    taskUUID = query.selectVariant(sql, params).toString();
}

bool NsUnstructDao::getRTaskDownloadStatus(const QString &taskUUID,const quint8 &filesState)
{
    QString sql = "select count(UUID) from NS_R_UNSTRUCT_TASK WHERE UUID =:taskUUID and STATE =:state";
    QVariantMap params;
    params["taskUUID"]       = taskUUID;
    params["state"]       = filesState;
    DBQuery query;
    int length = query.selectVariant(sql,params).toInt();
    return length == 0;
}

void NsUnstructDao::moveRTask2STask(const QString &taskUUID)
{
    //TODO
    /*
INSERT INTO NS_S_UNSTRUCT_TASK (SELECT * FROM NS_R_UNSTRUCT_TASK WHERE UUID=:o_id)
DELETE FROM NS_R_UNSTRUCT_TASK WHERE UUID=:o_id
INSERT INTO NS_S_UNSTRUCT_SEND_FILES (SELECT * FROM NS_R_UNSTRUCT_SEND_FILES WHERE UUID=:o_id)
DELETE FROM NS_R_UNSTRUCT_SEND_FILES WHERE UUID=:o_id
    */
    bool fly = Environment::Db_Transaction_State::TRANS_FAIL;
    QString sql_insert_stask = "INSERT INTO NS_S_UNSTRUCT_TASK (SELECT * FROM NS_R_UNSTRUCT_TASK WHERE UUID=:o_id)";
    QString sql_delete_rtask = "DELETE FROM NS_R_UNSTRUCT_TASK WHERE UUID=:o_id";
    QString sql_insert_sfile = "INSERT INTO NS_S_UNSTRUCT_SEND_FILES (SELECT * FROM NS_R_UNSTRUCT_SEND_FILES WHERE TASK_UUID=:o_id)";
    QString sql_delete_rfile = "DELETE FROM NS_R_UNSTRUCT_SEND_FILES WHERE TASK_UUID=:o_id";
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

NsRUnstructTask NsUnstructDao::getRTaskByUUID(const QString &taskUUID)
{
    QString sql = "select * from NS_R_UNSTRUCT_TASK WHERE UUID =:uuid";
    QVariantMap params;
    params["uuid"]       = taskUUID;
    DBQuery query;
    return query.uniqueBean(mapToRUnstructTask, sql,params);
}


void NsUnstructDao::deleteRTaskByTaskNum(const QString &taskNum)
{
    bool fly = Environment::Db_Transaction_State::TRANS_FAIL;
    QString sql = "delete from NS_R_UNSTRUCT_TASK where TASK_NUM=:taskNum";
    QVariantMap params;
    params["taskNum"] = taskNum;

    DBTransaction *transaction = new DBTransaction;
    try
    {
        transaction->beginTransaction();
        fly = transaction->execSQL(sql,params);
        if(fly == Environment::Db_Transaction_State::TRANS_SUCCESS)
        {
            transaction->commit();
            qDebug() << trs("删除成功");
        }
        else
        {
            transaction->rollback();
            DBException excep;
            excep.setType(QSqlError::TransactionError);
            excep.setText(trs("delete error"));
            throw excep;
        }
    }
    catch(DBException &ex)
    {
        qDebug() << trs("删除失败");
        transaction->rollback();
        //        qDebug() << excep.getText();
        //既然try...catch,就捕获异常做处理,如果不try...catch,自动回退直到找到try...catch
        throw ex;
    }
    delete transaction;
}

void NsUnstructDao::insertRTask(const NsRUnstructTask &nsRUnstructTask)
{
    //    //UUID
    //    QString uuid;
    //    //计划任务编号
    //    quint32 taskNum;
    //    //下发策略
    //    quint16 strategy;
    //    //任务状态
    //    quint8 state;
    //    //添加时间
    //    QString insertTime;
    QString sql = "insert into NS_R_UNSTRUCT_TASK(UUID, TASK_NUM, STRATEGY, STATE, INSERT_TIME) values (:uuid, :taskNum, :strategy, :state, :insertTime)";

    QVariantMap params;
    params["uuid"] = nsRUnstructTask.getUuid();
    params["taskNum"] = nsRUnstructTask.getTaskNum();
    params["strategy"] = nsRUnstructTask.getStrategy();
    params["state"]    = nsRUnstructTask.getState();
    params["insertTime"]   = nsRUnstructTask.getInsertTime();
    //必须try...catch才能回滚和提交
    DBTransaction *transaction = new DBTransaction;
    try
    {
        transaction->beginTransaction();
        //因为这里的key为整形,所以可以这样判断
        bool thisKey = transaction->insert(sql, params);
        if(thisKey)
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

void NsUnstructDao::insertRTaskAndTaskFiles(NsRUnstructTask *nsRUnstructTask, QList<NsRUnstructSendFiles *> downFiles)
{
    bool fly = Environment::Db_Transaction_State::TRANS_FAIL;
    QString tasksql = "insert into NS_R_UNSTRUCT_TASK(UUID, TASK_NUM, STRATEGY, STATE, INSERT_TIME) values (:uuid, :taskNum, :strategy, :state, :insertTime)";

    QVariantMap taskparams;
    taskparams["uuid"] = nsRUnstructTask->getUuid();
    taskparams["taskNum"] = nsRUnstructTask->getTaskNum();
    taskparams["strategy"] = nsRUnstructTask->getStrategy();
    taskparams["state"]    = nsRUnstructTask->getState();
    taskparams["insertTime"]   = nsRUnstructTask->getInsertTime();
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
                delete transaction;
                return;
            }
            for(NsRUnstructSendFiles *sendFile :downFiles)
            {
                QString filesql = "insert into NS_R_UNSTRUCT_SEND_FILES(UUID, FILE_URL, FILE_ABST, TASK_UUID, STATE, ERROR) values (:uuid, :fileUrl, :fileAbst, :taskUuid, :state, :error)";

                QVariantMap fileparams;
                fileparams["uuid"] = sendFile->getUuid();
                fileparams["fileUrl"] = sendFile->getFileUrl();
                fileparams["fileAbst"] = sendFile->getFileAbst();
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
error:;
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

QList<NsRUnstructSendFiles> NsUnstructDao::dirRSendFilesByTaskUUID(const QString &taskUUID,const quint8 &state)
{
    QString sql = "select * from NS_R_UNSTRUCT_SEND_FILES WHERE TASK_UUID =:taskUUID and STATE =:state";
    QVariantMap params;
    params["taskUUID"]       = taskUUID;
    params["state"]       = state;
    DBQuery query;
    return query.listBeans(mapToRUnstructSendFiles, sql,params);
}

void NsUnstructDao::getRTaskStateByTaskUUID(const QString &taskUUID, quint8 &state)
{
    QString sql = "select STATE from NS_R_UNSTRUCT_TASK where UUID=:taskUUID";

    QVariantMap params;
    params["taskUUID"]       = taskUUID;
    DBQuery query;
    state = (quint8)query.selectVariant(sql, params).toUInt();
}

void NsUnstructDao::insertRSendFiles(const NsRUnstructSendFiles &nsRUnstructSendFiles)
{
    QString sql = "insert into NS_R_UNSTRUCT_SEND_FILES(UUID, FILE_URL, FILE_ABST, TASK_UUID, STATE, ERROR) values (:uuid, :fileUrl, :fileAbst, :taskUuid, :state, :error)";

    QVariantMap params;
    params["uuid"] = nsRUnstructSendFiles.getUuid();
    params["fileUrl"] = nsRUnstructSendFiles.getFileUrl();
    params["fileAbst"] = nsRUnstructSendFiles.getFileAbst();
    params["taskUuid"]    = nsRUnstructSendFiles.getTaskUuid();
    params["state"]   = nsRUnstructSendFiles.getState();
    params["error"]   = nsRUnstructSendFiles.getError();
    //必须try...catch才能回滚和提交
    DBTransaction *transaction = new DBTransaction;
    try
    {
        transaction->beginTransaction();
        //因为这里的key为整形,所以可以这样判断
        bool thisKey = transaction->insert(sql, params);
        if(thisKey)
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

void NsUnstructDao::deleteRSendFilesByTaskUUID(const QString &taskUUID)
{
    bool fly = Environment::Db_Transaction_State::TRANS_FAIL;
    QString sql = "delete from NS_R_UNSTRUCT_SEND_FILES where TASK_UUID=:taskUUID";
    QVariantMap params;
    params["taskNum"] = taskUUID;

    DBTransaction *transaction = new DBTransaction;
    try
    {
        transaction->beginTransaction();
        fly = transaction->execSQL(sql,params);
        if(fly == Environment::Db_Transaction_State::TRANS_SUCCESS)
        {
            transaction->commit();
            qDebug() << trs("删除成功");
        }
        else
        {
            transaction->rollback();
            DBException excep;
            excep.setType(QSqlError::TransactionError);
            excep.setText(trs("delete error"));
            throw excep;
        }
    }
    catch(DBException &ex)
    {
        qDebug() << trs("删除失败");
        transaction->rollback();
        //        qDebug() << excep.getText();
        //既然try...catch,就捕获异常做处理,如果不try...catch,自动回退直到找到try...catch
        throw ex;
    }
    delete transaction;
}

void NsUnstructDao::updateRSendFilesStateByUrlAbst(const QString &taskUUID, const QString &fileUrl, const QString &destAbst, const quint8 &state)
{
    bool fly = Environment::Db_Transaction_State::TRANS_FAIL;
    QString sql = "update NS_R_UNSTRUCT_SEND_FILES set STATE =:state,ERROR ='' where TASK_UUID =:taskUUID and FILE_URL =:fileUrl and FILE_ABST =:destAbst";

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

void NsUnstructDao::updateRSendFilesState(const QString &taskUUID,const QString &fileUrl, const quint8 &state, const QString &errorMsg)
{
    bool fly = Environment::Db_Transaction_State::TRANS_FAIL;
    QString sendfilesql = "update NS_R_UNSTRUCT_SEND_FILES set STATE =:state,ERROR =:error where TASK_UUID =:taskUUID and FILE_URL =:fileUrl";
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

NsRUnstructTask NsUnstructDao::mapToRUnstructTask(const QVariantMap &rowMap)
{
    NsRUnstructTask task;
    task.setUuid(rowMap.value("UUID").toString());
    task.setTaskNum((quint32)rowMap.value("TASK_NUM").toUInt());
    task.setStrategy((quint16)rowMap.value("STRATEGY").toUInt());
    task.setState((quint8)rowMap.value("STATE").toUInt());
    task.setInsertTime(rowMap.value("INSERT_TIME").toString());
    return task;
}

NsRUnstructSendFiles NsUnstructDao::mapToRUnstructSendFiles(const QVariantMap &rowMap)
{
    NsRUnstructSendFiles task;
    task.setUuid(rowMap.value("UUID").toString());
    task.setFileUrl(rowMap.value("FILE_URL").toString());
    task.setFileAbst(rowMap.value("FILE_ABST").toString());
    task.setTaskUuid(rowMap.value("TASK_UUID").toString());
    task.setState((quint8)rowMap.value("STATE").toUInt());
    task.setError(rowMap.value("ERROR").toString());
    return task;
}


