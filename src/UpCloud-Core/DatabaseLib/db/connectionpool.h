#ifndef CONNECTIONPOOL_H
#define CONNECTIONPOOL_H

#include <QtSql>
#include <QStack>
#include <QString>
#include <QMap>
#include <QMutex>
#include <QMutexLocker>
#include "err/dbexecption.h"
#include "databaselib_global.h"
#include "databasemeta.h"
/**
 * 实现了一个简易的数据库连接池，简化了数据库连接的获取。通过配置最大的连接数可创建多个连接支持多线程访问数据库，
 * Qt 里同一个数据库连接不能被多个线程共享。连接使用完后释放回连接池而不是直接关闭，再次使用的时候不必重新建立连接，
 * 建立连接是很耗时的操作，底层是 Socket 连接。
 *
 * 如果 testOnBorrow 为 true，则连接断开后会自动重新连接（例如数据库程序崩溃了，网络的原因导致连接断了等），
 * 但是每次获取连接的时候都会先访问一下数据库测试连接是否有效，如果无效则重新建立连接。testOnBorrow 为 true 时，
 * 需要提供一条 SQL 语句用于测试查询，例如 MySQL 下可以用 SELECT 1。
 *
 * 如果 testOnBorrow 为 false，则连接断开后不会自动重新连接，这时获取到的连接调用 QSqlDatabase::isOpen() 返回的值
 * 仍然是 true（因为先前的时候已经建立好了连接，Qt 里没有提供判断底层连接断开的方法或者信号）。
 *
 * 当程序结束后，需要调用 DatabaseConnectionPool::release() 关闭所有数据库的连接（一般在 main() 函数返回前调用）。
 *
 * 使用方法：
 * 1. 从数据库连接池里取得连接
 * QSqlDatabase db = DatabaseConnectionPool::openConnection();
 *
 * 2. 使用 db 访问数据库，如
 * QSqlQuery query(db);
 *
 * 3. 数据库连接使用完后需要释放回数据库连接池
 * DatabaseConnectionPool::closeConnection(db);
 *
 * 4. 程序结束的时候关闭所有数据库连接
 * DatabaseConnectionPool::release();
 */
class DATABASELIBSHARED_EXPORT DatabaseConnectionPool {
public:
    // 关闭所有的数据库连接
    static void release();
    static void initialize(const QString &confPath);
    /**
     * @brief openConnection    读取db配置文件数据库配置,获取数据库连接
     * @param except
     * @return
     */
    static QSqlDatabase openConnection(DBException &except, const DatabaseMeta *dbMeta = NULL);
    // 释放数据库连接回连接池
    static void closeConnection(QSqlDatabase connection, const DatabaseMeta *dbMeta = NULL);

//    /**
//     * @brief openConnection    传统传入数据库元数据DatabaseMeta,创建数据库连接
//     * @param except
//     * @param dbMeta
//     * @return
//     * 该方法不会存在连接池,因为数据库配置是随时可以修改的
//     * 使用该方法不需要调用initialize,release方法,因为该方法就没有用到连接池
//     * TODO   二期优化此接口,添加连接池
//     */
//    static QSqlDatabase openConnection(DBException &except,const DatabaseMeta &dbMeta);


//    /**
//     * @brief closeConnection
//     * @param connection
//     * @param conn_name
//     * 该方法不会存在连接池,因为数据库配置是随时可以修改的
//     * 使用该方法不需要调用initialize,release方法,因为该方法就没有用到连接池
//     * TODO   二期优化此接口,添加连接池
//     */
//    static void closeConnection(QSqlDatabase connection,const DatabaseMeta &dbMeta);

    ~DatabaseConnectionPool();

private:
    void conf();
    void mkPoolName();
    static QString mkPoolName(const DatabaseMeta *dbMeta);
    static DatabaseConnectionPool* getInstance(const DatabaseMeta *dbMeta = NULL);

    DatabaseConnectionPool();
    DatabaseConnectionPool(const DatabaseConnectionPool &other);
    DatabaseConnectionPool& operator=(const DatabaseConnectionPool &other);
    // 创建数据库连接
    QSqlDatabase createConnection(const QString &connectionName,DBException &except);
    // 已使用的数据库连接名
    QStack<QString> usedConnectionNames;
    // 未使用的数据库连接名
    QStack<QString> unusedConnectionNames;
    //conf路径
    static QString confPath;
    // 数据库连接地址
    QString hostName;
    // 数据库实例名称(数据库名称)
    QString instanceName;
    // 数据库连接用户名
    QString username;
    // 数据库连接密码
    QString password;
    //  数据库驱动名称
    QString dbDriver;
    // 取得连接的时候验证连接是否有效
    bool    testOnBorrow;
    // 测试访问数据库的 SQL
    QString testOnBorrowSql;
    // 获取连接最大等待时间
    int maxWaitTime;
    // 尝试获取连接时等待间隔时间
    int waitInterval;
    // 最大连接数
    int maxConnectionCount;
    // 数据库的端口号
    int port;
    //pool name
    QString poolName;

    static QMutex mutex;
    static QWaitCondition waitConnection;
    static DatabaseConnectionPool *def_instance;
    static QMap<QString, DatabaseConnectionPool*> *instance_map;
};

#endif // CONNECTIONPOOL_H
