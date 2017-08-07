#ifndef DBTRANSACTION_H
#define DBTRANSACTION_H
#include <QtCore>
#include <QtSql>
#include <functional>
#include "databaselib_global.h"
#include "databasemeta.h"
/**
 * @brief The DBTransaction class   数据库事务操作
 * Notice   调用DBTransaction,必须确定保证在事件循环中进行
 */
class DATABASELIBSHARED_EXPORT DBTransaction
{
public:
    /**
     * @brief beginTransaction  开启事务
     */
    void beginTransaction();
    /**
     * @brief commit    提交事务
     */
    void commit();
    /**
     * @brief rollback  回滚
     */
    void rollback();
    /**
     * 执行插入语句，并返回插入行的 id.
     * @param sql
     * @param params
     * @return 如果执行成功返插入的记录的 id，否则返回空.
     */
    bool insert(const QString &sql, const QVariantMap &params = QVariantMap());
    /**
     * 执行SQL语句,可以使create/drop/updat/delete语句都是更新语句).
     * @param sql
     * @param params
     * @return 如没有错误返回 true， 有错误返回 false.
     */
    bool execSQL(const QString &sql, const QVariantMap &params = QVariantMap());
    /**
     * @brief setDatabaseMeta   设置数据库元数据
     * @param dbMeta
     */
    void setDatabaseMeta(const DatabaseMeta &dbMeta);
private:
    QSqlDatabase db;
    /**
     * 定义了访问数据库算法的骨架，SQL 语句执行的结果使用传进来的 Lambda 表达式处理
     * @param sql
     * @param params
     * @param fn - 处理 SQL 语句执行的结果的 Lambda 表达式
     */
    bool executeSql(const QString &sql, const QVariantMap &params, std::function<void (QSqlQuery *)> handleResult);
    /**
     * 如果 database.conf 里 debug 为 true，则输出执行的 SQL，如果为 false，则不输出.
     * @param query
     */
    void debug(const QSqlQuery &query, const QVariantMap &params);
    /**
     * 把 map 中的 key 和 value 绑定到 query 里.
     * @param query
     * @param params
     */
    void bindValues(QSqlQuery *query);

    void replaceSql(const QVariantMap& params);

    DatabaseMeta dbMeta;

    //基本类型参数
    QVariantMap m_baseParams;
    //list类型参数
    QVariantMap m_listParams;
    //原始的Sql语句
    QString m_preSql;
    //替换后的Sql语句
    QString m_replacedSql;
};

#endif // DBTRANSACTION_H
