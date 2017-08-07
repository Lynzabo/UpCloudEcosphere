#include "connectionpool.h"
#include "conf/databaseconf.h"
#include "base.h"
#include <QDebug>
QMutex DatabaseConnectionPool::mutex;
QWaitCondition DatabaseConnectionPool::waitConnection;
DatabaseConnectionPool* DatabaseConnectionPool::def_instance = NULL;
QMap<QString, DatabaseConnectionPool*> *DatabaseConnectionPool::instance_map = NULL;
QString DatabaseConnectionPool::confPath = QString();

DatabaseConnectionPool::DatabaseConnectionPool() {

}
void DatabaseConnectionPool::conf() {
    DatabaseConf &conf = DatabaseConf::getInstance();
    conf.setConfPath(this->confPath);
    conf.loadConf();
    hostName     = conf.ip();
    instanceName = conf.instanceName();
    username     = conf.username();
    password     = conf.password();
    dbDriver = conf.dbDriver();
    testOnBorrow = conf.testOnBorrow();
    testOnBorrowSql = conf.testOnBorrowSql();

    maxWaitTime  = conf.houseKeepingSleepTime();
    waitInterval = conf.waitIntervalTime();
    maxConnectionCount  = conf.maximumConnectionCount();
    port = conf.port();
    mkPoolName();
    //DatabaseConf::release();
}
DatabaseConnectionPool::~DatabaseConnectionPool() {
    // 销毁连接池的时候删除所有的连接
    foreach(QString connectionName, usedConnectionNames) {
        QSqlDatabase::removeDatabase(connectionName);
    }

    foreach(QString connectionName, unusedConnectionNames) {
        QSqlDatabase::removeDatabase(connectionName);
    }
}

DatabaseConnectionPool *DatabaseConnectionPool::getInstance(const DatabaseMeta *dbMeta) {
    QMutexLocker locker(&mutex);
    if(dbMeta == NULL || dbMeta->isNull())
    {
        //def pool
        return def_instance;
    }
    else
    {
        QString __poolname = DatabaseConnectionPool::mkPoolName(dbMeta);
        if(instance_map->contains(__poolname))
        {
            //find pool
            return instance_map->value(__poolname);
        }
        else
        {
            //create new pool


            qDebug() << trs("准备注册数据库服务连接池%1").arg(confPath);

            DatabaseConnectionPool *newPool = new DatabaseConnectionPool();
            newPool->confPath = confPath;
            newPool->conf();

            newPool->hostName = dbMeta->getIp();
            newPool->port = dbMeta->getPort();
            newPool->instanceName = dbMeta->getInstanceName();
            newPool->username = dbMeta->getUsername();
            newPool->password = dbMeta->getPassword();
            newPool->dbDriver = dbMeta->getDbDriver();
            newPool->mkPoolName();

            instance_map->insert(newPool->poolName,newPool);
            qDebug() << trs("注册数据库服务连接池%1成功,等待连接").arg(newPool->poolName);

            return newPool;
        }
    }
}

void DatabaseConnectionPool::mkPoolName()
{
    poolName = "["+hostName+QString::number(port)+ instanceName+ dbDriver+"]";
    return;
}

QString DatabaseConnectionPool::mkPoolName(const DatabaseMeta *dbMeta)
{
    if(dbMeta == NULL)
    {
        DBException e;
        e.setType(QSqlError::ConnectionError);
        e.setText("make pool name:no dbmeta");
        throw e;
    }
    QString tmpPoolName = "["+dbMeta->getIp()+QString::number(dbMeta->getPort())+ dbMeta->getInstanceName()+ dbMeta->getDbDriver()+"]";
    return tmpPoolName;
}

void DatabaseConnectionPool::release() {
    QMutexLocker locker(&mutex);

    QList<DatabaseConnectionPool*> __pool;
    if(instance_map != NULL)
    {
        __pool = instance_map->values();
    }
    qDeleteAll(__pool);
    __pool.clear();
    delete instance_map;
    instance_map = NULL;

}

void DatabaseConnectionPool::initialize(const QString &confPath)
{
    QMutexLocker locker(&mutex);

    qDebug() << trs("准备注册数据库服务连接池%1").arg(confPath);
    //init pool map
    instance_map = new QMap<QString, DatabaseConnectionPool*>();

    //init default pool
    def_instance = new DatabaseConnectionPool();
    def_instance->confPath = confPath;
    def_instance->conf();
    DatabaseConnectionPool::instance_map->insert(def_instance->poolName,def_instance);
    qDebug() << trs("注册数据库服务连接池%1成功,等待连接").arg(def_instance->poolName);
}

QSqlDatabase DatabaseConnectionPool::openConnection(DBException &except,const DatabaseMeta *dbMeta) {
    DatabaseConnectionPool* pool = DatabaseConnectionPool::getInstance(dbMeta);
    QString connectionName;

    QMutexLocker locker(&mutex);

    // 已创建连接数
    int connectionCount = pool->unusedConnectionNames.size() + pool->usedConnectionNames.size();

    // 如果连接已经用完，等待waitInterval毫秒看看是否有可用连接，最长等待maxWaitTime毫秒
    for (int i = 0;
         i < pool->maxWaitTime
         && pool->unusedConnectionNames.size() == 0 && connectionCount == pool->maxConnectionCount;
         i += pool->waitInterval) {
        waitConnection.wait(&mutex, pool->waitInterval);

        // 重新计算已创建连接数
        connectionCount = pool->unusedConnectionNames.size() + pool->usedConnectionNames.size();
    }

    if (pool->unusedConnectionNames.size() > 0) {
        // 有已经回收的连接,复用它们
        connectionName = pool->unusedConnectionNames.pop();
    } else if (connectionCount < pool->maxConnectionCount) {
        // 没有已经回收的连接,但是没有达到最大连接数,则创建新的连接
        connectionName = QString("%1 Connection-%2").arg(pool->poolName).arg(connectionCount + 1);
    } else {
        // 已经达到最大连接数
        qDebug() << trs("Cannot create more connections.");
        return QSqlDatabase();
    }

    // 创建连接
    QSqlDatabase db = pool->createConnection(connectionName,except);

    // 有效的连接才放入usedConnectionNames
    if (db.isOpen()) {
        pool->usedConnectionNames.push(connectionName);
    }

    return db;
}

void DatabaseConnectionPool::closeConnection(QSqlDatabase connection,const DatabaseMeta *dbMeta) {
    DatabaseConnectionPool* pool = DatabaseConnectionPool::getInstance(dbMeta);
    QString connectionName = connection.connectionName();
    connection.close();
    // 如果是我们创建的连接,从 used 里删除,放入 unused 里
    if (pool->usedConnectionNames.contains(connectionName)) {
        QMutexLocker locker(&mutex);
        pool->usedConnectionNames.removeOne(connectionName);
        pool->unusedConnectionNames.push(connectionName);
        waitConnection.wakeOne();
    }
}

QSqlDatabase DatabaseConnectionPool::createConnection(const QString &connectionName, DBException &except) {
    // 连接已经创建过了,复用它,而不是重新创建
    if (QSqlDatabase::contains(connectionName)) {
        QSqlDatabase db1 = QSqlDatabase::database(connectionName);
        //测试数据库连接是否有效
        if (testOnBorrow) {
            // 返回连接前访问数据库,如果连接断开,重新建立连接
            //qDebug() << trs("测试数据库的连接:[\"execute sql\":%1,\"for\":%2]").arg(testOnBorrowSql).arg(connectionName);
            QSqlQuery query(testOnBorrowSql, db1);

            if (query.lastError().type() != QSqlError::NoError) {
                except.setType(query.lastError().type());
                except.setText(trs("测试数据库的连接失败:%1").arg(query.lastError().text()));
//                return QSqlDatabase();
                throw except;
            }
        }

        return db1;
    }

    // 创建一个新的连接
    QSqlDatabase db = QSqlDatabase::addDatabase(dbDriver, connectionName);
    if(!db.isValid())
    {
        except.setType(db.lastError().type());
        except.setText(trs("加载数据库的驱动失败:%1").arg(db.lastError().text()));
        throw except;
    }
    db.setHostName(hostName);
    db.setDatabaseName(instanceName);
    db.setUserName(username);
    db.setPassword(password);

    if (port != 0) {
        db.setPort(port);
    }

    if (!db.open()) {
        except.setType(db.lastError().type());
        except.setText(trs("打开数据库的连接失败:%1").arg(db.lastError().text()));
        throw except;
//        return QSqlDatabase();
    }

    return db;
}
