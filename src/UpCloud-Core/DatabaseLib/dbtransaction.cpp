#include "dbtransaction.h"
#include "db/connectionpool.h"
#include "db/err/dbexecption.h"
#include "db/conf/databaseconf.h"
#include "base.h"

void DBTransaction::beginTransaction()
{
    DBException dbExcep;
    db = DatabaseConnectionPool::openConnection(dbExcep,&(this->dbMeta));

    if(dbExcep.getType()!=QSqlError::ErrorType::NoError)
    {
        DatabaseConnectionPool::closeConnection(db,&(this->dbMeta));
        throw dbExcep;
    }
    db.transaction();
}

void DBTransaction::commit()
{
    if(db.isValid())
    {
        bool res = db.commit();
        if(!res)
            qDebug()<<"DB Commit failed";
        DatabaseConnectionPool::closeConnection(db,&(this->dbMeta));
    }
}

void DBTransaction::rollback()
{
    if(db.isValid())
    {
        db.rollback();
        DatabaseConnectionPool::closeConnection(db,&(this->dbMeta));
    }
}

bool DBTransaction::insert(const QString &sql, const QVariantMap &params)
{
    bool ok;
    QVariant id;

    ok = executeSql(sql, params, [&id](QSqlQuery *query) {
            id = query->lastInsertId();;
    });
//    qDebug()<<"SQL:"<<sql <<"\n params:"<<params;
    return ok;
}

/*
QVariant DBTransaction::insert(const QString &sql, const QVariantMap &params)
{
    QVariant id;

    executeSql(sql, params, [&id](QSqlQuery *query) {
        // 插入行的主键
        id = query->lastInsertId();
    });

    return id;
}
*/

bool DBTransaction::execSQL(const QString &sql, const QVariantMap &params)
{
    bool result;

    executeSql(sql, params, [&result](QSqlQuery *query) {
        result = query->lastError().type() == QSqlError::NoError;
    });

    return result;
}

void DBTransaction::setDatabaseMeta(const DatabaseMeta &dbMeta)
{
    this->dbMeta = dbMeta;
}
bool DBTransaction::executeSql(const QString &sql,
                               const QVariantMap &params,
                               std::function<void(QSqlQuery *query)> handleResult) {
    bool ok;
    QSqlQuery query(db);
    m_preSql = sql;
    replaceSql(params);
    query.prepare(m_replacedSql);
    bindValues(&query);

    if (query.exec())
    {
        handleResult(&query);
        ok = true;
    }
    else
    {
        ok = false;
    }
    debug(query, params);
    return ok;
}
void DBTransaction::bindValues(QSqlQuery *query)
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



void DBTransaction::replaceSql(const QVariantMap &params)
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
void DBTransaction::debug(const QSqlQuery &query, const QVariantMap &params) {
    if (DatabaseConf::getInstance().isDebug()) {
        qDebug() << trs("SQL Query:%1").arg(m_preSql);
        if (params.size() > 0) {
            qDebug() << trs("SQL Params:") << params;
        }
    }
    if (query.lastError().type() != QSqlError::NoError) {
        DatabaseConnectionPool::closeConnection(db,&(this->dbMeta));
        DBException dbExcep;
        dbExcep.setType(query.lastError().type());
        dbExcep.setText(trs("SQL Error :%1").arg(query.lastError().text().trimmed()));
        throw dbExcep;
    }
}
