#include "dbquery.h"
#include "db/connectionpool.h"
#include "db/err/dbexecption.h"
#include "db/conf/databaseconf.h"
#include "base.h"
#include "erm.h"
void DBQuery::bindValues(QSqlQuery *query)
{
    //绑定基本类型
    for(QVariantMap::const_iterator i=m_baseParams.constBegin(); i!=m_baseParams.constEnd(); ++i)
    {
        query->bindValue(":" + i.key(), i.value());
    }
    //绑定list类型
    QVariantMap e_value;       //每一项对应的Value
    for(QVariantMap::const_iterator i=m_listParams.constBegin(); i!=m_listParams.constEnd(); ++i)
    {

        e_value = i.value().toMap();
        for(QVariantMap::const_iterator j=e_value.constBegin(); j!=e_value.constEnd(); ++j)
        {
            query->bindValue(j.key(), j.value());
        }
    }
}

void DBQuery::debug(const QSqlQuery &query, const QVariantMap &params)
{
    if (DatabaseConf::getInstance().isDebug()) {
        // qDebug() << trs("SQL Query:%1").arg(m_preSql);
        if (params.size() > 0) {
            //qDebug() << trs("SQL Params:") << params;
        }
    }
    if (query.lastError().type() != QSqlError::NoError) {
        DatabaseConnectionPool::closeConnection(db);
        DBException dbExcep;
        dbExcep.setType(query.lastError().type());
        dbExcep.setText(trs("SQL Error :%1").arg(query.lastError().text().trimmed()));
        throw dbExcep;
    }
}

QStringList DBQuery::getFieldNames(const QSqlQuery &query)
{
    QSqlRecord record = query.record();
    QStringList names;
    int count = record.count();

    for (int i = 0; i < count; ++i) {
        names << record.fieldName(i);
    }

    return names;
}

QList<QVariantMap> DBQuery::queryToMaps(QSqlQuery *query)
{
    QList<QVariantMap > rowMaps;
    QStringList fieldNames = getFieldNames(*query);

    while (query->next()) {
        QVariantMap rowMap;

        foreach (const QString &fieldName, fieldNames) {
            rowMap.insert(fieldName.trimmed(), query->value(fieldName));
        }

        rowMaps.append(rowMap);
    }

    return rowMaps;
}

void DBQuery::replaceSql(const QVariantMap &params)
{
    m_baseParams.clear();
    m_listParams.clear();

    m_replacedSql.clear();
    m_replacedSql = m_preSql;

    //每一项对应的Key
    QString v_key;
    //每一项对应的Value
    QVariant v_value;

    for (QVariantMap::const_iterator i=params.constBegin(); i!=params.constEnd(); ++i)
    {
        //每一项对应的key value
        v_key = i.key();
        v_value = i.value();

        //如果参数是个列表
        if((v_value.type() == QVariant::List) || (v_value.type() == QVariant::StringList))
        {
            const QVariantList list = v_value.toList();

            //列表长度
            int size = list.size();
            //要替换的新的总SQL语句片段
            QString sql_replace;sql_replace.clear();
            //要替换的每一项SQL语句片段
            QString re_pam; re_pam.clear();
            //新的参数列表
            QVariantMap re_params;re_params.clear();

            //生成新的占位符字符串
            for(int i=0; i<size; i++)
            {
                re_pam = QString("%1%2").arg(v_key).arg(QString::number(i));
                if(i == size - 1)
                {
                    sql_replace += (":" + re_pam);
                }
                else
                {
                    sql_replace += (":" + re_pam + ",");
                }
                re_params.insert((":" + re_pam),list.at(i));
            }
            //替换原有的占位符
            m_replacedSql.replace(":"+v_key, sql_replace);
            m_listParams.insert(v_key, re_params);
        }
        else
        {
            m_baseParams.insert(v_key, v_value);
        }
    }
}


quint64 DBQuery::count(const QString &sql, const QVariantMap &params)
{
    //截取sql语句from后面最为条件
    QString totalSentence = sql.mid(sql.toLower().indexOf("from"),sql.length());
    /*if(sqlParts.size()>0)
    {
        //过滤掉所有的order by
        QString part;part.clear();
        for (int i = 0; i < sqlParts.size(); ++i)
        {
            part = sqlParts.at(i);
            totalSentence.remove(part);
        }
    }*/
    totalSentence = trs("SELECT COUNT(*) ").append(totalSentence);
    return selectVariant(totalSentence,params).toLongLong();
}
/*
public PageH page(final PageH pageH,final String sentence,final boolean isSQL,final Map parmaters,final Map entitys,final Map joins,final Map scalars)
    throws DataAccessException {
    if(StringHelper.isEmpty(pageH.getPageNum())){
        pageH.setPageNum("1");//第几页显示
    }else{}
    String numPerPage = pageH.getNumPerPage();
    if(StringHelper.isEmpty(pageH.getNumPerPage())){
        pageH.setNumPerPage("10");//每页显示条数，以后参数管理给
    }else{}
    int startPage = Integer.parseInt(pageH.getPageNum());//哪一页开始查询
    int pageSize = Integer.parseInt(pageH.getNumPerPage());//每页显示条数
    int startRow = (startPage - 1) * pageSize;
    //Object[] parmatersKeys = parmaters.keySet().toArray();
    int totalCount = count(sentence, isSQL, parmaters);

    int totalPages=0;
    if(totalCount==0){
        totalPages=0;
    }else{
        if(totalCount%pageSize==0){
            totalPages=totalCount/pageSize;
        }else{
            totalPages=((int)Math.ceil((double)(totalCount/pageSize)))+1;
        }
    }
    pageH.setTotalPages(totalPages);
    pageH.setTotalCount(totalCount);
    if(totalCount>0){
        List result = list(sentence, isSQL, startRow, pageSize, parmaters, entitys, joins, scalars);
        if(CollectionUtil.isNotEmpty(result)){
            pageH.setResults(result);
        }
    }
    return pageH;
}
*/
Page *DBQuery::page(Page *page, const QString &sql, const QVariantMap &params)
{
    if(page->getCurPageNum() <= (quint32)0)
        page->setCurPageNum((quint32)1);
    if(page->getNumPerPage() <= 0)
        page->setNumPerPage((quint32)10);
    //哪一页开始查询
    quint32 startPage = page->getCurPageNum();
    //每页显示条数
    quint32 pageSize = page->getNumPerPage();
    quint32 startRow = (startPage - 1) * pageSize;
    quint64 totalCount = count(sql, params);
    quint32 totalPages =0;
    if(totalCount==0){
        totalPages=0;
    }else{
        if(totalCount%pageSize==0){
            totalPages=totalCount/pageSize;
        }else{
            totalPages=((quint32)qCeil((qreal)(totalCount/pageSize)))+1;
        }
    }
    page->setTotalPages(totalPages);
    page->setTotalCount(totalCount);
    QString pageSQL;
    QString dbLowerName;dbLowerName.clear();
//    QString dbLowerName = DatabaseConf::getInstance().dbDriver();
    if(dbMeta.isNull())
        dbLowerName = DatabaseConf::getInstance().dbDriver();
    else
        dbLowerName = trs("Q")+ dbMeta.getDbName().toUpper();
    if(dbLowerName==trs("QOCI"))
    {
        pageSQL.append(trs("SELECT * FROM "
                           "( SELECT A.*, ROWNUM RN FROM"
                           "( %1 "
                           ") A WHERE ROWNUM < %2 "
                           ") "
                           "WHERE RN > %3").arg(sql).arg(startRow+pageSize+1).arg(startRow));
    }
    else if(dbLowerName==trs("QDB2"))
    {
        pageSQL.append(trs("SELECT * FROM "
                           "( select rownumber() over() AS rn FROM"
                           "( %1 "
                           ") AS t WHERE t.rn BETWEEN %2 AND %3)").arg(sql).arg(startRow).arg(startRow+pageSize));

    }
    else if(dbLowerName==trs("QMYSQL") || dbLowerName==trs("QSQLITE2") || dbLowerName==trs("QSQLITE"))
    {
        pageSQL.append(trs("%1 limit %2,%3").arg(sql).arg(startRow).arg(pageSize));
    }
    else if(dbLowerName==trs("QODBC"))
    {
        //TODO 待使用SQL Server数据库时集成
    }
    if(totalCount>0){
        QList<QVariantMap> result = list(pageSQL,params);//;list(sentence, isSQL, startRow, pageSize, parmaters, entitys, joins, scalars);
        if(result.size()>0)
            page->setResults(result);
    }
    return page;
}

QList<QVariantMap> DBQuery::pageList(Page *page, const QString &sql, const QVariantMap &params)
{
    this->page(page,sql,params);
    return page->getResults();
}

QVariantMap DBQuery::uniqueResult(const QString &sql, const QVariantMap &params)
{
    return list(sql, params).value(0);
}

QList<QVariantMap> DBQuery::list(const QString &sql, const QVariantMap &params)
{
    QList<QVariantMap> maps;

    executeSql(sql, params, [&maps](QSqlQuery *query) {
        //TODO 调用静态的方法对不对
        maps = queryToMaps(query);
    });

    return maps;
}

QVariantList DBQuery::selectVariants(const QString &sql, const QVariantMap &params)
{
    QVariantList vars;

    executeSql(sql, params, [&vars](QSqlQuery *query) {
        while (query->next()) {
            vars.append(query->value(0).toString());
        }
    });

    return vars;
}

QVariant DBQuery::selectVariant(const QString &sql, const QVariantMap &params)
{
    QVariant result;

    executeSql(sql, params, [&result](QSqlQuery *query) {
        if (query->next()) {
            result = query->value(0);
        }
    });

    return result;
}

void DBQuery::setDatabaseMeta(const DatabaseMeta &dbMeta)
{
    this->dbMeta = dbMeta;
}

void DBQuery::executeSql(const QString &sql,
                         const QVariantMap &params,
                         std::function<void(QSqlQuery *query)> handleResult) {
    DBException dbExcep;
    if(dbMeta.isNull())
        db = DatabaseConnectionPool::openConnection(dbExcep);
    else
        db = DatabaseConnectionPool::openConnection(dbExcep,&(this->dbMeta));
    if(dbExcep.getType()!=QSqlError::ErrorType::NoError)
    {
        DatabaseConnectionPool::closeConnection(db);
        throw dbExcep;
    }
    QSqlQuery query(db);
    m_preSql = sql;
    replaceSql(params);
    query.prepare(m_replacedSql);
    bindValues(&query);

    if (query.exec()) {
        handleResult(&query);
    }
    debug(query, params);
    DatabaseConnectionPool::closeConnection(db);
}

