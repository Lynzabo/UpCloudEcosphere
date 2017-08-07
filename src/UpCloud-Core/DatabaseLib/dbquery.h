#ifndef DBQUERY_H
#define DBQUERY_H
#include <QtCore>
#include <QtSql>
#include <functional>
#include "databaselib_global.h"
#include "databasemeta.h"
#include "erm.h"

//class Page;

/**
 * @brief The DBQuery class 数据库查询
 * Notice   调用DBQuery,必须确定保证在事件循环中进行
 */
class DATABASELIBSHARED_EXPORT DBQuery
{
public:
    /**
     * 执行查询语句，查询到一条记录，并把其映射成 map，Key 是列名，Value 是列值.
     * @param sql
     * @param params
     * @return 返回记录映射的 map.
     * Notice:  该方法是查询多个字段,不包括SQL中包含*情况,如果有*,也可以使用,但建议使用uniqueBean更方便
     */
    QVariantMap uniqueResult(const QString &sql, const QVariantMap &params = QVariantMap());
    /**
         * @brief count 获取总条数
         * @param sql
         * @param params    参数列表
         * @return
         */
    quint64 count(const QString &sql, const QVariantMap &params = QVariantMap());
    /**
     * @brief page  执行分页查询语句，查询到多条记录，并把每一条记录其映射成一个 map，Key 是列名，Value 是列值.
     * @param onepage 当前页
     * @param sql sql语句
     * @param params 参数
     * @return
     */
    Page* page(Page* page,const QString &sql, const QVariantMap &params = QVariantMap());
    /**
     * @brief page  执行分页查询语句，查询到多条记录，并把每一条记录其映射成一个 map，Key 是列名，Value 是列值.
     * @param onepage 当前页
     * @param sql sql语句
     * @param params 参数
     * @return  结果集list
     */
    QList<QVariantMap> pageList(Page* page,const QString &sql, const QVariantMap &params = QVariantMap());

    template <typename T>
    QList<T> pageBean(T mapToBean(const QVariantMap &rowMap),Page* onepage,const QString &sql, const QVariantMap &params = QVariantMap())
    {
        QList<T> beans;
        onepage = page(onepage, sql,params);
        // 每一个 map 都映射成一个 bean 对象
        foreach (const QVariantMap row, onepage->getResults()) {
            beans.append(mapToBean(row));
        }
        return beans;
    }

    /**
     * 执行查询语句，查询到多条记录，并把每一条记录其映射成一个 map，Key 是列名，Value 是列值.
     * 所有的 map 都放在 list 里。
     * @param sql
     * @param params
     * @return 返回记录映射的 map 的 list.
     */
    QList<QVariantMap> list(const QString &sql, const QVariantMap &params = QVariantMap());
    /**
     * 查询结果封装成一个对象 bean.
     * @param sql
     * @param mapToBean - 把 map 映射成对象的函数.
     * @return 返回查找到的 bean, 如果没有查找到，返回 T 的默认对象，其 id 最好是 -1，这样便于有效的对象区别。
     * Notice:  该方法是查询多个字段,不包括SQL中包含*情况,如果有*,也可以使用,但建议使用uniqueBean更方便
     */
    template <typename T>
    T uniqueBean(T mapToBean(const QVariantMap &rowMap), const QString &sql, const QVariantMap &params = QVariantMap()) {
        // 把 map 都映射成一个 bean 对象
        return mapToBean(uniqueResult(sql, params));
    }

    /**
     * 执行查询语句，查询到多个结果并封装成 bean 的 list.
     * @param sql
     * @param params
     * @param mapToBean - 把 map 映射成 bean 对象函数.
     * @return 返回 bean 的 list，如果没有查找到，返回空的 list.
     */
    template<typename T>
    QList<T> listBeans(T mapToBean(const QVariantMap &rowMap), const QString &sql, const QVariantMap &params = QVariantMap()) {
        QList<T> beans;

        // 每一个 map 都映射成一个 bean 对象
        foreach (const QVariantMap row, list(sql, params)) {
            beans.append(mapToBean(row));
        }

        return beans;
    }
    /**
     * 一个字段的查询结果中多条记录.
     * @param strs
     * @param sql
     * @param params
     * @return 返回 string list.
     */
    QVariantList selectVariants(const QString &sql, const QVariantMap &params = QVariantMap());

    /**
     * 一个字段的查询结果中只有一条记录.
     * @param str
     * @param sql
     * @param params
     * @return 返回 variant
     */
    QVariant selectVariant(const QString &sql, const QVariantMap &params = QVariantMap());
    /**
     * @brief setDatabaseMeta   设置数据库元数据
     * @param dbMeta
     */
    void setDatabaseMeta(const DatabaseMeta &dbMeta);

private:
    /**
     * 定义了访问数据库算法的骨架，SQL 语句执行的结果使用传进来的 Lambda 表达式处理
     * @param sql
     * @param params
     * @param fn - 处理 SQL 语句执行的结果的 Lambda 表达式
     */
    void executeSql(const QString &sql, const QVariantMap &params, std::function<void(QSqlQuery *query)> fn);
    /**
     * 把 map 中的 key 和 value 绑定到 query 里.
     * @param query
     * @param params
     */
    void bindValues(QSqlQuery *query);
    /**
     * 如果 database.conf 里 debug 为 true，则输出执行的 SQL，如果为 false，则不输出.
     * @param query
     */
    void debug(const QSqlQuery &query, const QVariantMap &params);
    /**
     * 取得 query 的 labels(没用别名就是数据库里的列名).
     * @param query
     * @return string list.
     */
    static QStringList getFieldNames(const QSqlQuery &query);
    /**
     * 把 query 中的查询得到的所有行映射为 map 的 list.
     * @param query
     * @return 返回 key 为列名，值为列的值的 map 的 list.
     */
    static QList<QVariantMap> queryToMaps(QSqlQuery *query);

    void replaceSql(const QVariantMap& params);

    QSqlDatabase db;
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

#endif // DBQUERY_H
