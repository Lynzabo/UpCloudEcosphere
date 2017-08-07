#include "databasemeta.h"

const QString DatabaseMeta::DbName::ORACLE = trs("oracle");
const QString DatabaseMeta::DbName::DB2 = trs("db2");
const QString DatabaseMeta::DbName::MYSQL = trs("mysql");
const QString DatabaseMeta::DbName::SQLSERVER = trs("sqlserver");
const QString DatabaseMeta::DbName::SQLITE2 = trs("sqlite2");
const QString DatabaseMeta::DbName::SQLITE3 = trs("sqlite3");

DatabaseMeta::Builder::Builder()
{
    db = new DatabaseMeta;
}

DatabaseMeta::Builder::~Builder()
{
    delete db;
}

DatabaseMeta::Builder::Builder(const QString &dbName, const QString &ip, const int &port, const QString &instanceName, const QString &username, const QString &password, const int &houseKeepingSleepTime, const int &waitIntervalTime)
{
    db = new DatabaseMeta;
    db->dbName = dbName;
    db->ip = ip;
    db->port = port;
    db->instanceName = instanceName;
    db->username = username;
    db->password = password;
    db->houseKeepingSleepTime = houseKeepingSleepTime;
    db->waitIntervalTime = waitIntervalTime;
}

DatabaseMeta::Builder *DatabaseMeta::Builder::setDbName(const QString &dbName)
{
    db->dbName = dbName;
    return this;
}

DatabaseMeta::Builder *DatabaseMeta::Builder::setIp(const QString &ip)
{
    db->ip = ip;
    return this;
}

DatabaseMeta::Builder *DatabaseMeta::Builder::setPort(int port)
{
    db->port = port;
    return this;
}

DatabaseMeta::Builder *DatabaseMeta::Builder::setInstanceName(const QString &instanceName)
{
    db->instanceName = instanceName;
    return this;
}

DatabaseMeta::Builder *DatabaseMeta::Builder::setUsername(const QString &username)
{
    db->username = username;
    return this;
}

DatabaseMeta::Builder *DatabaseMeta::Builder::setPassword(const QString &password)
{
    db->password = password;
    return this;
}

DatabaseMeta::Builder *DatabaseMeta::Builder::setHouseKeepingSleepTime(int houseKeepingSleepTime)
{
    db->houseKeepingSleepTime = houseKeepingSleepTime;
    return this;
}

DatabaseMeta::Builder *DatabaseMeta::Builder::setWaitIntervalTime(int waitIntervalTime)
{
    db->waitIntervalTime = waitIntervalTime;
    return this;
}

DatabaseMeta *DatabaseMeta::Builder::build()
{
    return db;
}



QString DatabaseMeta::getDbName() const
{
    return dbName;
}
QString DatabaseMeta::getIp() const
{
    return ip;
}
int DatabaseMeta::getPort() const
{
    return port;
}
QString DatabaseMeta::getInstanceName() const
{
    return instanceName;
}
QString DatabaseMeta::getUsername() const
{
    return username;
}
QString DatabaseMeta::getPassword() const
{
    return password;
}
int DatabaseMeta::getHouseKeepingSleepTime() const
{
    return houseKeepingSleepTime;
}
int DatabaseMeta::getWaitIntervalTime() const
{
    return waitIntervalTime;
}

QString DatabaseMeta::getDbDriver() const
{
    const QString dbLowerName = dbName.toLower();
    if(dbLowerName=="oracle")
        return trs("QOCI");
    else if(dbLowerName=="db2")
        return trs("QDB2");
    else if(dbLowerName=="mysql")
        return trs("QMYSQL");
    else if(dbLowerName=="sqlserver")
        return trs("QODBC");
    else if(dbLowerName=="sqlite2")
        return trs("QSQLITE2");
    else
        return trs("QSQLITE");
}

bool DatabaseMeta::isNull() const
{
    return dbName.isEmpty()||ip.isEmpty() || port == 0 || instanceName.isEmpty() || username.isEmpty() || password.isEmpty();
}




