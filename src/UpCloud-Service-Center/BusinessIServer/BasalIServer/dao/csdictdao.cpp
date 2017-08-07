#include "csdictdao.h"

CSDictDao::CSDictDao()
{

}

void CSDictDao::addCsDict(const CsDict &task)
{
    QString sql = "insert into CS_DICT values("
                  ":uuid,:code,:name,:descripion,"
                  ":sequence,:supuuid,:state,"
                  ":insertor,:inserttime,:operator,:operatime)";
    DBTransaction* transaction = new DBTransaction;
    bool ok;
    //准备参数列表
    QVariantMap params;

    params["uuid"] = task.getUuid();
    params["code"] = task.getCode();
    params["name"] = task.getName();
    params["descripion"] = task.getDescription();
    params["sequence"] = task.getSequence();
    params["supuuid"] = task.getSupUuid();
    params["state"] = task.getState();
    params["insertor"] = task.getInsertor();
    params["inserttime"] = task.getInsertTime();
    params["operator"] = task.getOperater();
    params["operatime"] = task.getOperaTime();
    //UI端已经判定好字典顺序，无须再次重写顺序
    //    DBQuery query;
    //    QString sqlForSequence = "select * from CS_DICT where sup_uuid =:supuuid";
    //    QList<CsDict> list =  query.listBeans(mapToCsDict,sqlForSequence,params);
    //    params["sequence"] = (quint16)(list.size() + 1);
    //操作数据库
    transaction->beginTransaction();
    try{
        ok = transaction->execSQL(sql,params);
        if(!ok) {
            DBException excep;
            excep.setText("操作数据库失败 ");
            excep.setType(QSqlError::TransactionError);
            throw excep;
        }
        transaction->commit();
        delete transaction;
    }
    catch(DBException& ex) {
        transaction->rollback();
        delete transaction;
        throw ex;
    }
}

QList<CsDict> CSDictDao::dirCsDict(const QString &code, const QString supUuid)
{
    QString sql = "select * from CS_DICT where code =:code and sup_uuid =:supUuid";
    QVariantMap params;
    params["code"] =code;
    params["supUuid"] =supUuid;
    DBQuery query;
    return query.listBeans(mapToCsDict,sql,params);
}
CsDict CSDictDao::itemCsDict(const QString &uuid)
{
    QString sql = "select * from CS_DICT where UUID =:UUID";
    QVariantMap params;
    params["UUID"] =uuid;
    DBQuery query;
    return query.uniqueBean(mapToCsDict,sql,params);

}

QList<CsDict> CSDictDao::dirCsDict()
{
    QString sql = "select * from CS_DICT where UUID <:value order by UUID";
    QVariantMap params;
    params["value"] ="3"/*QString::number(4).toInt()*/;
    DBQuery query;
    return query.listBeans(mapToCsDict,sql,params);

}
QList<CsDict> CSDictDao::dirCsDict(const QVariantMap &paramsMap)
{
    QString sql = ("select * from (select distinct  * from cs_dict start with uuid in "
                   "(select  uuid from cs_dict where sup_uuid =:supUuid ) "
                   "connect by prior uuid =sup_uuid order by INSERT_TIME,sup_uuid,sequence) "
                   "where 1 = 1");
    if(paramsMap.contains("closeRecursion")) {
        sql = "select * from"
              " (select * from cs_dict where sup_uuid = :supUuid order by sequence)"
              " where 1 = 1";
    }
    QVariantMap params = paramsMap;
    if(!params.contains("supUuid")) {
        params.insert("supUuid",QString::number(-1));
    }
    if(!params.value("code").toString().isEmpty())
    {
        sql.append(" and code like UPPER(:code)");
    }
    if(!params.value("name").toString().isEmpty())
    {
        sql.append(" and UPPER(NAME) LIKE UPPER(:name)");
    }
    if(!params.value("description").toString().isEmpty())
    {
        sql.append(" and UPPER(DESCRIPTION) LIKE UPPER(:description)");
    }
    if(params.value("state").toInt() != 0)
    {

        sql.append(" and STATE =:state");
    }
    //TODO  时间是否精确查询
    if(params.contains("insertTimeBegin"))
    {
        sql.append(" and INSERT_TIME >=:insertTimeBegin and INSERT_TIME <= :insertTimeEnd");
    }
    DBQuery query;
    return query.listBeans(mapToCsDict,sql,params);
}

QList<CsDict> CSDictDao::pageDict(const QVariantMap &paramsMap,Page* page)
{
    QString sql = "select * from (select distinct  * from cs_dict start with uuid in "
                  "(select  uuid from cs_dict where sup_uuid =:supUuid ) "
                  "connect by prior uuid =sup_uuid order by sup_uuid,sequence) "
                  "where 1 = 1";
    QVariantMap params = paramsMap;
    if(paramsMap.contains("closeRecursion")) {
        sql = "select * from"
              " (select * from cs_dict where sup_uuid = :supUuid order by sequence)"
              " where 1 = 1";
    }
    if(!params.contains("supUuid")) {
        params.insert("supUuid",QString::number(-1));
    }
    if(!params.value("code").toString().isEmpty())
    {
        sql.append(" and UPPER(code) like UPPER(:code)");
    }
    if(!params.value("name").toString().isEmpty())
    {
        sql.append(" and UPPER(NAME) LIKE UPPER(:name)");
    }
    if(!params.value("description").toString().isEmpty())
    {
        sql.append(" and UPPER(DESCRIPTION) LIKE UPPER(:description)");
    }
    if(params.value("state").toInt() != 0)
    {

        sql.append(" and STATE =:state");
    }
    //TODO  时间是否精确查询
    if(params.contains("insertTimeBegin"))
    {
        sql.append(" and INSERT_TIME >=:insertTimeBegin and INSERT_TIME <= :insertTimeEnd");
    }
    //order by
    sql.append(QString(" order by %1 %2")//order by column1 desc/asc
               .arg(!(page->getOrderFieldName().isEmpty()) ? page->getOrderFieldName() : "FILE_NAME")
               .arg(page->getOrderField() == Qt::DescendingOrder?"DESC":"ASC")
               );
    DBQuery query;
    return query.pageBean(mapToCsDict,page,sql,params);
}

void CSDictDao::delCsDict(const QStringList &uuids)
{
    QVariantMap params;
    bool ok;
    QString sql = "DELETE cs_dict "
                  "WHERE uuid IN "
                  "(SELECT uuid "
                  "FROM"
                  "(SELECT DISTINCT * "
                  "FROM CS_DICT "
                  "START WITH uuid  IN (:inCondition)"
                  "CONNECT BY prior uuid=sup_uuid"
                  ")"
                  ")";

    DBTransaction* transaction = new DBTransaction;
    params.insert("inCondition",(QVariant)uuids);
    transaction->beginTransaction();
    try{
        ok = transaction->execSQL(sql,params);
        if(!ok) {
            DBException excep;
            excep.setText(QObject::trUtf8("数据库操作失败 "));
            excep.setType(QSqlError::TransactionError);
            throw excep;
        }
        transaction->commit();
        delete transaction;
    }
    catch(DBException &ex){
        transaction->rollback();
        delete transaction;
        throw ex;
    }

}

void CSDictDao::updateCsDict(const QList<CsDict> &taskList)
{
    QString sql = "update CS_DICT set NAME =:name,DESCRIPTION =:descripion,SEQUENCE =:sequence,sup_uuid =:supUuid,STATE =:state,INSERTOR =:insertor,INSERT_TIME =:inserttime,OPERATOR =:operator,OPERA_TIME =:operatime where UUID =:uuid";
    DBTransaction* transaction = new DBTransaction;
    bool ok;
    //准备参数列表
    QVariantMap params;
    transaction->beginTransaction();
    foreach(const CsDict &task,taskList) {
        params["uuid"] = task.getUuid();
        //params["code"] = task.getCode();
        params["name"] = task.getName();
        params["descripion"] = task.getDescription();
        params["sequence"] = (qint32)task.getSequence();
        params["supUuid"] = task.getSupUuid();
        params["state"] = (quint8)task.getState();
        params["insertor"] = task.getInsertor();
        params["inserttime"] = task.getInsertTime();
        params["operator"] = task.getOperater();
        params["operatime"] = task.getOperaTime();
        //操作数据库
        ok = transaction->execSQL(sql,params);
        if(!ok) {
            goto end;
        }
        else {
            continue;
        }

    }
    transaction->commit();
    delete transaction;
    return;
end:;
    transaction->rollback();
    delete transaction;

    DBException excep;
    excep.setText("操作数据库失败 ");
    excep.setType(QSqlError::TransactionError);
    throw excep;
}

CsDict CSDictDao::mapToCsDict(const QVariantMap &rowMap)
{

    CsDict task;
    task.setUuid(rowMap.value("UUID").toString());
    task.setCode(rowMap.value("CODE").toString());
    task.setName(rowMap.value("NAME").toString());
    task.setDescription(rowMap.value("DESCRIPTION").toString());
    task.setSequence((qint32)rowMap.value("SEQUENCE").toInt());
    task.setSupUuid(rowMap.value("SUP_UUID").toString());
    task.setState((quint8)rowMap.value("STATE").toInt());
    task.setInsertor(rowMap.value("INSERTOR").toString());
    task.setInsertTime(rowMap.value("INSERT_TIME").toString());
    task.setOperater(rowMap.value("OPERATOR").toString());
    task.setOperaTime(rowMap.value("OPERA_TIME").toString());
    return task;
}

