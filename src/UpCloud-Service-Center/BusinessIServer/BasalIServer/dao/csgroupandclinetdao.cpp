#include "csgroupandclinetdao.h"
using namespace Environment;
CsGroupAndClinetDao::CsGroupAndClinetDao()
{
    
}

void CsGroupAndClinetDao::delGroupClient(const QString &uuid)
{
    QString sql = "DELETE CS_CLIENT_GROUP where uuid in (select distinct uuid from CS_CLIENT_GROUP  START WITH uuid IN (:uuid) CONNECT BY prior uuid=sup_uuid)";
    QString sqlForAssoc = "DELETE CS_CLIENT_GROUP_ASSOC where GROUP_UUID in (select distinct uuid from CS_CLIENT_GROUP  START WITH uuid IN (:uuid) CONNECT BY prior uuid=sup_uuid)";
    QString sqlSequence = "update CS_CLIENT_GROUP set sequence = sequence - 1 where sequence > (select sequence from CS_CLIENT_GROUP where UUID =:uuid)";
    QVariantMap params;
    bool ok;
    params["uuid"] = uuid;
    DBTransaction* transaction = new DBTransaction;
    transaction->beginTransaction();
    try {
        ok = transaction->execSQL(sqlSequence,params);
        if(ok) {
            ok = transaction->execSQL(sqlForAssoc,params);
            if(ok) {
                ok = transaction->execSQL(sql,params);
                if(!ok){
                    DBException execp;
                    execp.setText(QObject::trUtf8("数据库操作失败 "));
                    execp.setType(QSqlError::TransactionError);
                    throw execp;
                }
                else {
                    transaction->commit();
                    delete transaction;
                }
            }
            else {
                DBException execp;
                execp.setText(QObject::trUtf8("数据库操作失败 "));
                execp.setType(QSqlError::TransactionError);
                throw execp;
            }
        }
        else {
            DBException execp;
            execp.setText(QObject::trUtf8("数据库操作失败 "));
            execp.setType(QSqlError::TransactionError);
            throw execp;
        }
    }
    catch(DBException &ex) {
        transaction->rollback();
        delete transaction;
        throw ex;
    }
}

void CsGroupAndClinetDao::delGroupClientAssoc(const QList<CsClientGroup> &taskList)
{
    QString sql = "delete CS_CLIENT_GROUP_ASSOC where GROUP_UUID =:groupuuid";
    QVariantMap params;
    bool ok;
    int i;
    DBTransaction* transaction = new DBTransaction;
    transaction->beginTransaction();
    for(i =0;i < taskList.size();++i) {
        params["groupuuid"] = taskList.at(i).getUuid();
        
        ok = transaction->execSQL(sql,params);
        if(!ok) {
            goto end;
        }
    }
    
    transaction->commit();
    delete transaction;
    return;
end:;
    DBException excep;
    excep.setText(QObject::trUtf8("数据库删除错误 "));
    excep.setType(QSqlError::TransactionError);
    transaction->rollback();
    delete transaction;
    throw excep;
}

void CsGroupAndClinetDao::delGroupClientAssoc(const QVariantMap &params)
{
    QString sql;sql.clear();
    if(params.keys().contains("delAllForGroup")) {
        sql = "delete CS_CLIENT_GROUP_ASSOC where GROUP_UUID IN "
              "(select distinct uuid from CS_CLIENT_GROUP START WITH UUID = to_char(:uuid) CONNECT BY prior uuid = SUP_UUID)";
    }
    else {
        sql = "delete CS_CLIENT_GROUP_ASSOC where UUID =:uuid";
    }
    QString sqlSequence = "update CS_CLIENT_GROUP_ASSOC set sequence = sequence -1 where sequence >:sequence and group_uuid =:groupUuid";
    QVariantMap paramsData;
    paramsData["uuid"] = params.value("x_uuid").toString();
    paramsData["sequence"] = params.value("x_sequence").toString();
    paramsData["groupUuid"] = params.value("x_groupUuid").toString();
    bool ok;
    DBTransaction* transaction = new DBTransaction;
    transaction->beginTransaction();
    try{
        ok = transaction->execSQL(sql,paramsData);
        if(!ok) {
            DBException excep;
            excep.setText(QObject::trUtf8("数据库删除错误 "));
            excep.setType(QSqlError::TransactionError);
            throw excep;
        }
        else {
            ok = transaction->execSQL(sqlSequence,paramsData);
            if(ok) {
                transaction->commit();
                delete transaction;
            }
            else {
                DBException excep;
                excep.setText(QObject::trUtf8("数据库删除错误 "));
                excep.setType(QSqlError::TransactionError);
                throw excep;
            }
        }
    }
    catch(DBException &ex) {
        transaction->rollback();
        delete transaction;
        throw ex;
    }
    
}

void CsGroupAndClinetDao::addGroupClient(const CsClientGroup &task)
{
    QString sql = "insert into CS_CLIENT_GROUP "
                  "values(:uuid,:name,:description,:supuuid,"
                  ":sequence,:state,:insertor,:inserttime,:operater,:operattime)";
    bool ok;
    QVariantMap params;
    DBTransaction* transaction = new DBTransaction;
    transaction->beginTransaction();
    params["uuid"] = task.getUuid();
    params["name"] = task.getName();
    params["description"] = task.getDescription();
    params["supuuid"] = task.getSupUuid();
    params["sequence"] = (qint32)task.getSequence();
    params["state"] = (quint8)task.getState();
    params["insertor"] = task.getInsertor();
    params["inserttime"] = task.getInsertTime();
    params["operater"] = task.getOperater();
    params["operattime"] = task.getOperatTime();
    try {
        ok = transaction->execSQL(sql,params);
        if(ok) {
            transaction->commit();
            delete transaction;
        }
        else {
            DBException excep;
            excep.setText(trs("操作数据库失败 "));
            excep.setType(QSqlError::TransactionError);
            throw excep;
        }
    }
    catch(DBException &ex){
        
        transaction->rollback();
        delete transaction;
        throw ex;
    }
    
}

void CsGroupAndClinetDao::addGroupClient(const QVariantMap &params)
{
    QString sql = "insert into CS_CLIENT_GROUP "
                  "values(:uuid,:name,:description,:supUuid,"
                  ":sequence,:state,:insertor,:insertTime,:operator,:operatTime)";
    bool ok;
    DBTransaction* transaction = new DBTransaction;
    transaction->beginTransaction();
    try {
        ok = transaction->execSQL(sql,params);
        if(ok) {
            transaction->commit();
            delete transaction;
        }
        else {
            DBException excep;
            excep.setText(trs("操作数据库失败 "));
            excep.setType(QSqlError::TransactionError);
            throw excep;
        }
    }
    catch(DBException &ex){
        
        transaction->rollback();
        delete transaction;
        throw ex;
    }
}

void CsGroupAndClinetDao::addGroupClientAssoc(const CsClientGroupAssoc &task, const QStringList &nodes)
{
    QString uuid;uuid.clear();
    QString sqlForAdd = "insert into CS_CLIENT_GROUP_ASSOC values(:uuid,:clientuuid,:groupuuid,:insertor,:inserttime,:sequence,:state)";
    QString sqlForDel = "delete CS_CLIENT_GROUP_ASSOC where GROUP_UUID =:groupuuid";
    QVariantMap params;
    bool ok = false;
    DBTransaction* transaction = new DBTransaction;
    transaction->beginTransaction();
    params["groupuuid"] = task.getGroupUuid();
    params["insertor"] = task.getInsertor();
    params["inserttime"] = task.getInsertTime();
    params["state"] = task.getState();
    qint32 sequence = task.getSequence();
    ok =  transaction->execSQL(sqlForDel,params);
    if(!ok) {
        goto end;
    }
    for(int i = 0;i < nodes.size();i++) {
        UuidUtil::nextUUID(uuid);
        params["uuid"] = uuid;
        params["clientuuid"] = nodes.at(i);
        params["sequence"] =(qint32)(sequence + i);
        ok = transaction->execSQL(sqlForAdd,params);
        if(!ok) {
            goto end;
        }
    }
    transaction->commit();
    delete transaction;
    return;
end:;
    DBException excep;
    excep.setText(QObject::trUtf8("数据库添加错误 "));
    excep.setType(QSqlError::TransactionError);
    transaction->rollback();
    delete transaction;
    throw excep;
}

CsClientGroup CsGroupAndClinetDao::dirGroupClient(const QString &uuid)
{
    QString sql = "select * from CS_CLIENT_GROUP where UUID =:uuid";
    QVariantMap param;
    param["uuid"] = uuid;
    DBQuery query;
    return query.uniqueBean(mapToGroupClient,sql,param);
}

CsClientGroup CsGroupAndClinetDao::mapToGroupClient(const QVariantMap &rowMap)
{
    CsClientGroup task;
    task.setUuid(rowMap.value("UUID").toString());
    task.setName(rowMap.value("NAME").toString());
    task.setDescription(rowMap.value("DESCRIPTION").toString());
    task.setSupUuid(rowMap.value("SUP_UUID").toString());
    task.setSequence((qint32)rowMap.value("SEQUENCE").toInt());
    task.setState((quint8)rowMap.value("STATE").toInt());
    task.setInsertor(rowMap.value("INSERTOR").toString());
    task.setInsertTime(rowMap.value("INSERT_TIME").toString());
    task.setOperater(rowMap.value("OPERATOR").toString());
    task.setOperatTime(rowMap.value("OPERA_TIME").toString());
    return task;
}

CsClientGroupAssoc CsGroupAndClinetDao::mapToGroupClientAssoc(const QVariantMap &rowMap)
{
    CsClientGroupAssoc task;
    task.setUuid(rowMap.value("UUID").toString());
    task.setClientUuid(rowMap.value("CLIENT_UUID").toString());
    task.setGroupUuid(rowMap.value("GROUP_UUID").toString());
    task.setInsertor(rowMap.value("INSERTOR").toString());
    task.setInsertTime(rowMap.value("INSERT_TIME").toString());
    task.setSequence((qint32)rowMap.value("SEQUENCE").toInt());
    task.setState((quint16)rowMap.value("STATE").toInt());
    return task;
}

VCsClientGroupAssoc CsGroupAndClinetDao::mapToVGroupClientAssoc(const QVariantMap &rowMap)
{
    VCsClientGroupAssoc task;
    task.setUuid(rowMap.value("UUID").toString());
    task.setClientUuid(rowMap.value("CLIENT_UUID").toString());
    task.setGroupUuid(rowMap.value("GROUP_UUID").toString());
    task.setInsertor(rowMap.value("INSERTOR").toString());
    task.setInsertTime(rowMap.value("INSERT_TIME").toString());
    task.setSequence((qint32)rowMap.value("SEQUENCE").toInt());
    task.setState((quint16)rowMap.value("STATE").toInt());
    task.setDescription(rowMap.value("DESCRIPTION").toString());
    return task;
}

CsClientExtendInfo CsGroupAndClinetDao::mapToClientExtendInfo(const QVariantMap &rowMap)
{
    CsClientExtendInfo terminal;
    terminal.setUUID(rowMap.value("UUID").toString());
    terminal.setTerminalUUID(rowMap.value("TERMINAL_UUID").toLongLong());
    terminal.setType((quint8)rowMap.value("TYPE").toUInt());
    terminal.setDescription(rowMap.value("DESCRIPTION").toString());
    terminal.setMacAddr(rowMap.value("MACADDR").toString());
    terminal.setIP(rowMap.value("IP").toString());
    terminal.setPubKey(rowMap.value("PUBLIC_KEY").toString());
    terminal.setPriKey(rowMap.value("PRIVATE_KEY").toString());
    terminal.setState((quint8)rowMap.value("STATE").toUInt());
    terminal.setRunState((quint8)rowMap.value("RUNSTATE").toUInt());
    terminal.setCreateTime(rowMap.value("CREATE_TIME").toString());
    terminal.setOnlineTime(rowMap.value("ONLINE_TIME").toString());
    terminal.setOfflineTime(rowMap.value("OFFLINE_TIME").toString());
    return terminal;
}

QList<CsClientGroup> CsGroupAndClinetDao::dirGroupClient(const CsClientGroup &task )
{
    
    QString sql = "select * from CS_CLIENT_GROUP where 1 = 1";
    QVariantMap params;
    DBQuery query;
    if(!task.getUuid().isEmpty()) {
        params["uuid"] = task.getSupUuid();
        sql.append(" and UUID =:uuid");
    }
    if(task.getSupUuid().toInt() > -2) {
        params["supuuid"] = task.getSupUuid().toInt();
        sql.append(" and sup_UUID =:supuuid");
    }
    return query.listBeans(mapToGroupClient,sql,params);
}

QList<CsClientExtendInfo> CsGroupAndClinetDao::dirClientExtendInfo(const QString &clientUuid)
{
    QString sql = "select * from CS_CLIENT_TERMINAL where TERMINAL_UUID LIKE (:clientUuid)";
    DBQuery query;
    QVariantMap params;
    params["clientUuid"] = clientUuid;
    return query.listBeans(mapToClientExtendInfo,sql,params);
}



QList<CsClientGroup> CsGroupAndClinetDao::dirGroupClient(const QStringList &codes)
{
    QVariantMap params;
    DBQuery query;
    QString inCondition;inCondition.clear();
    QString sql;sql.clear();
    sql = "SELECT distinct * FROM CS_CLIENT_GROUP START WITH UUID IN (:inCondition) CONNECT BY prior uuid=sup_uuid order by SEQUENCE";
    params.insert("inCondition",(QVariant)codes);
    return query.listBeans(mapToGroupClient,sql,params);
}

QList<CsClientGroup> CsGroupAndClinetDao::dirGroupClientBySupUuid(const QStringList &supUuids, const quint32 page)
{
    QVariantMap params;
    DBQuery query;
    QString inCondition;inCondition.clear();
    QString sql = "SELECT * FROM"
                  " (SELECT A.*,rownum rn FROM"
                  " (SELECT DISTINCT * FROM CS_CLIENT_GROUP START WITH SUP_UUID IN (:inCondition)"
                  " CONNECT BY prior uuid=sup_uuid"
                  " ORDER BY sup_uuid,sequence ) A)"
                  " WHERE rn >= :pageRowNum*:page AND rn <:pageRowNum*(:page+1)";
    params.insert("inCondition",(QVariant)supUuids);
    params.insert("page",page);
    params.insert("pageRowNum",TreePage::PAGE_NUM);
    return query.listBeans(mapToGroupClient,sql,params);
}

QList<VCsClientGroupAssoc> CsGroupAndClinetDao::dirGroupClientAssoc(const QStringList &groupList,const quint32 page)
{
    QString sql = "SELECT * FROM (SELECT A.*,rownum rn FROM (select g.*,m.description from CS_CLIENT_GROUP_ASSOC g,cs_client_terminal m";
    
    QVariantMap params;
    if(groupList.isEmpty()) {
        sql.append(" where g.client_uuid = m.terminal_uuid order by sequence");
    }
    else {
        sql.append(" where g.client_uuid = m.terminal_uuid and GROUP_UUID IN (:incondition) order by sequence");
    }
    sql.append(") A)  WHERE rn >= :pageRowNum*:page AND rn <:pageRowNum*(:page+1)");
    DBQuery query;
    params.insert("incondition",(QVariant)groupList);
    params.insert("page",page);
    params.insert("pageRowNum",PAGE_NUM);
    return query.listBeans(mapToVGroupClientAssoc,sql,params);
}

QList<CsClientGroupAssoc> CsGroupAndClinetDao::dirGroupClientAssoc(const QString &groupUuid, const QStringList &nodes)
{
    QVariantMap params;
    params["groupuuid"] = groupUuid;
    DBQuery query;
    QString sql = "select * from CS_CLIENT_GROUP_ASSOC where GROUP_UUID =:groupuuid and CLIENT_UUID in (inCondition)";
    StringUtil::getInstance().formatSQLInParamsToInSQLCondition(sql,params,nodes,"inCondition");
    return query.listBeans(mapToGroupClientAssoc,sql,params);
}

CsClientGroup CsGroupAndClinetDao::itemGroupClient(const QString &uuid)
{
    QString sql = "select * from CS_CLIENT_GROUP where uuid =:uuid";
    QVariantMap params;
    params["uuid"] = uuid;
    DBQuery query;
    return query.uniqueBean(mapToGroupClient,sql,params);
}

void CsGroupAndClinetDao::updateGroupClient(const CsClientGroup &task)
{
    QString sql = "update CS_CLIENT_GROUP set NAME =:name,DESCRIPTION =:description,SUP_UUID =:supuuid,SEQUENCE =:sequence,STATE =:state,INSERTOR =:insertor,INSERT_TIME =:inserttime,OPERATOR =:operator,OPERA_TIME =:operatime where UUID =:uuid";
    QString sqlForGroup = "update CS_CLIENT_GROUP set state =:state where UUID IN "
                          "(select distinct uuid from CS_CLIENT_GROUP start with uuid IN(:uuid) connect by prior uuid = sup_uuid)";
    QString sqlForGroupAssoc = "update CS_CLIENT_GROUP_ASSOC set state =:state where GROUP_UUID IN "
                               "(select distinct uuid from CS_CLIENT_GROUP start with uuid IN(:uuid) connect by prior uuid = sup_uuid)";
    QVariantMap params;
    bool ok;
    params["uuid"] = task.getUuid();
    params["name"] = task.getName();
    params["description"] = task.getDescription();
    params["supuuid"] = task.getSupUuid();
    params["sequence"] =(quint32) task.getSequence();
    params["state"] = (qint8)task.getState();
    params["insertor"] = task.getInsertor();
    params["inserttime"] = task.getInsertTime();
    params["operator"] = task.getOperater();
    params["operatime"] = task.getOperatTime();
    DBTransaction* transction = new DBTransaction;
    transction->beginTransaction();
    try {
        ok = transction->execSQL(sql,params);
        if(ok){
            ok = transction->execSQL(sqlForGroup,params);
            if(ok) {
                ok = transction->execSQL(sqlForGroupAssoc,params);
                if(ok) {
                    transction->commit();
                    delete transction;
                }
                else {
                    DBException execp;
                    execp.setText(QObject::trUtf8("数据库操作失败 "));
                    execp.setType(QSqlError::TransactionError);
                    throw execp;
                }
            }
            else {
                DBException execp;
                execp.setText(QObject::trUtf8("数据库操作失败 "));
                execp.setType(QSqlError::TransactionError);
                throw execp;
            }
        }
        else {
            DBException execp;
            execp.setText(QObject::trUtf8("数据库操作失败 "));
            execp.setType(QSqlError::TransactionError);
            throw execp;
        }
    }
    catch(DBException &ex) {
        transction->rollback();
        delete transction;
        throw ex;
    }
}

void CsGroupAndClinetDao::updateGroupAssoc(const QString &uuid, const quint8 state)
{
    QString sql = "update CS_CLIENT_GROUP_ASSOC set state =:state where uuid =:uuid";
    bool ok = false;
    QVariantMap params;
    params["uuid"] = uuid;
    params["state"] = state;
    DBTransaction* transaction = new DBTransaction;
    transaction->beginTransaction();
    try{
        ok = transaction->execSQL(sql,params);
        if(ok) {
            transaction->commit();
            delete transaction;
        }
        else {
            transaction->rollback();
            delete transaction;
            DBException excep;
            excep.setText("操作数据失败");
            excep.setType(QSqlError::TransactionError);
            throw excep;
        }
    }
    catch(DBTransaction &ex) {
        throw ex;
    }
}

void CsGroupAndClinetDao::moveNodeToGroupIn(const QVariantMap &params)
{
    int xValue = params.value("x_sequence").toInt();
    int yValue = params.value("y_sequence").toInt();
    ////所有越过的值全部改变
    QString betweenSql;betweenSql.clear();
    QString sql;sql.clear();
    DBException excep;
    if(xValue > yValue)
    {
        //前移所有越过的节点顺序值都要加一
        betweenSql = "update CS_CLIENT_GROUP_ASSOC set SEQUENCE = SEQUENCE + 1 where "
                     "SEQUENCE < :x_sequence and SEQUENCE >= :y_sequence "
                     "and GROUP_UUID =:x_groupUuid";
        sql= "update CS_CLIENT_GROUP_ASSOC set SEQUENCE =:y_sequence  where "
             "UUID =:x_uuid";
    }
    else
    {
        //后移所有越过的节点顺序值都要减一
        betweenSql = "update CS_CLIENT_GROUP_ASSOC set SEQUENCE = SEQUENCE - 1 where "
                     "SEQUENCE > :x_sequence and SEQUENCE <= :y_sequence "
                     "and GROUP_UUID =:x_groupUuid";
        sql= "update CS_CLIENT_GROUP_ASSOC set SEQUENCE =:y_sequence  where "
             "UUID =:x_uuid";
    }
    
    bool ok = false;
    DBTransaction* transaction = new DBTransaction;
    transaction->beginTransaction();
    try{
        ok = transaction->execSQL(betweenSql,params);
        if(ok) {
            ok = transaction->execSQL(sql,params);
            if(!ok) {
                DBException ex;
                throw ex;
            }
        }
        else {
            DBException ex;
            throw ex;
        }
    }
    catch(DBException &ex) {
        Q_UNUSED(ex)
        excep.setText(QObject::tr("操作数据出错"));
        excep.setType(QSqlError::TransactionError);
        goto end;
    }
    transaction->commit();
    delete transaction;
    return;
end:;
    transaction->rollback();
    delete transaction;
    throw excep;
}

void CsGroupAndClinetDao::moveNodeToGroupOut(const QVariantMap &params)
{
    QString sqlForY = "update CS_CLIENT_GROUP_ASSOC Set SEQUENCE = SEQUENCE + 1 where sequence >= :y_sequence"
                      " and GROUP_UUID =:y_groupUuid";
    QString sqlForX = "update CS_CLIENT_GROUP_ASSOC SET SEQUENCE =:y_sequence,"
                      "GROUP_UUID =:y_groupUuid where UUID =:x_uuid";
    QString sqlForXGroup = "update CS_CLIENT_GROUP_ASSOC SET SEQUENCE = SEQUENCE - 1 where "
                           "SEQUENCE > :x_sequence and GROUP_UUID =:x_groupUuid";
    bool ok = false;
    DBException excep;
    DBTransaction* transaction = new DBTransaction;
    transaction->beginTransaction();
    try{
        ok = transaction->execSQL(sqlForXGroup,params);
        if(ok) {
            ok = transaction->execSQL(sqlForY,params);
            if(ok) {
                ok = transaction->execSQL(sqlForX,params);
                if(!ok) {
                    DBException ex;
                    throw ex;
                }
            }
            else {
                DBException ex;
                throw ex;
            }
        }
        else {
            DBException ex;
            throw ex;
        }
    }
    catch(DBException &ex) {
        Q_UNUSED(ex)
        excep.setText(QObject::tr("操作数据出错"));
        excep.setType(QSqlError::TransactionError);
        goto end;
    }
    transaction->commit();
    delete transaction;
    return;
end:;
    transaction->rollback();
    delete transaction;
    throw excep;
    
}

void CsGroupAndClinetDao::moveGroupToGroupIn(const QVariantMap &params)
{
    int xValue = params.value("x_sequence").toInt();
    int yValue = params.value("y_sequence").toInt();
    ////所有越过的值全部改变
    QString betweenSql;betweenSql.clear();
    QString sql;sql.clear();
    DBException excep;
    if(xValue > yValue)
    {
        //前移所有越过的节点顺序值都要加一
        betweenSql = "update CS_CLIENT_GROUP set SEQUENCE = SEQUENCE + 1 where "
                     "SEQUENCE < :x_sequence and SEQUENCE >= :y_sequence "
                     "and SUP_UUID =:x_groupUuid";
        sql = "update CS_CLIENT_GROUP set SEQUENCE =:y_sequence where "
              "UUID =:x_uuid";
    }
    else
    {
        //后移所有越过的节点顺序值都要减一
        betweenSql = "update CS_CLIENT_GROUP set SEQUENCE = SEQUENCE - 1 where "
                     "SEQUENCE > :x_sequence and SEQUENCE <= :y_sequence "
                     "and SUP_UUID =:x_groupUuid";
        sql = "update CS_CLIENT_GROUP set SEQUENCE =:y_sequence where "
              "UUID =:x_uuid";
    }
    bool ok = false;
    DBTransaction* transaction = new DBTransaction;
    transaction->beginTransaction();
    try{
        ok = transaction->execSQL(betweenSql,params);
        if(ok) {
            ok = transaction->execSQL(sql,params);
            if(!ok) {
                DBException ex;
                throw ex;
            }
        }
        else {
            DBException ex;
            throw ex;
        }
    }
    catch(DBException &ex) {
        Q_UNUSED(ex)
        excep.setText(QObject::tr("操作数据出错"));
        excep.setType(QSqlError::TransactionError);
        goto end;
    }
    transaction->commit();
    delete transaction;
    return;
end:;
    transaction->rollback();
    delete transaction;
    throw excep;
    
}

void CsGroupAndClinetDao::moveGroupToGroupOut(const QVariantMap &params)
{
    QString sqlForY = "update CS_CLIENT_GROUP set SEQUENCE = SEQUENCE + 1 where "
                      "sequence >= :y_sequence "
                      "and SUP_UUID =:y_groupUuid";
    QString sqlForX = "update CS_CLIENT_GROUP SET SEQUENCE =:y_sequence,"
                      "SUP_UUID =:y_groupUuid where UUID =:x_uuid";
    QString sqlForXGroup = "update CS_CLIENT_GROUP SET SEQUENCE = SEQUENCE - 1 where "
                           "SEQUENCE > :x_sequence and SUP_UUID =:x_groupUuid";
    bool ok = false;
    DBException excep;
    DBTransaction* transaction = new DBTransaction;
    transaction->beginTransaction();
    try{
        ok = transaction->execSQL(sqlForXGroup,params);
        if(ok) {
            ok = transaction->execSQL(sqlForY,params);
            if(ok) {
                ok = transaction->execSQL(sqlForX,params);
                if(!ok) {
                    DBException ex;
                    throw ex;
                }
            }
            else {
                DBException ex;
                throw ex;
            }
        }
        else {
            DBException ex;
            throw ex;
        }
    }
    catch(DBException &ex) {
        Q_UNUSED(ex)
        excep.setText(QObject::tr("操作数据出错"));
        excep.setType(QSqlError::TransactionError);
        goto end;
    }
    transaction->commit();
    delete transaction;
    return;
end:;
    transaction->rollback();
    delete transaction;
    throw excep;
}

