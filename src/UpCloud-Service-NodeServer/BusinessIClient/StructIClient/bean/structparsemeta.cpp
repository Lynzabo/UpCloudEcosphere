#include "structparsemeta.h"

//const QString StructParseMeta::DbType::ORACLE = trs("oracle");
//const QString StructParseMeta::DbType::DB2 = trs("db2");
//const QString StructParseMeta::DbType::MYSQL = trs("mysql");
//const QString StructParseMeta::DbType::SQLSERVER = trs("sqlserver");
//const QString StructParseMeta::DbType::SQLITE2 = trs("sqlite2");
//const QString StructParseMeta::DbType::SQLITE3 = trs("sqlite3");

StructParseMeta::Builder::Builder()
{
    structParseMeta = new StructParseMeta;
}

StructParseMeta::Builder::Builder(const QString &dbType, const QString &IP, const quint16 &port, \
                                  const QString &databaseName, const QString &username, const QString &password, \
                                  const bool &async, const quint32 &asyncNum)
{
    structParseMeta = new StructParseMeta;
    structParseMeta->dbType = dbType;
    structParseMeta->IP = IP;
    structParseMeta->port = port;
    structParseMeta->databaseName =  databaseName;
    structParseMeta->username = username;
    structParseMeta->password = password;
    structParseMeta->async = async;
    structParseMeta->asyncNum = asyncNum;
}

StructParseMeta::Builder::~Builder()
{
    delete structParseMeta;
}

StructParseMeta::Builder *StructParseMeta::Builder::setDatabase(const QString &dbType)
{
    structParseMeta->dbType = dbType;
    return this;
}

StructParseMeta::Builder *StructParseMeta::Builder::setIp(const QString &IP)
{
    structParseMeta->IP = IP;
    return this;
}

StructParseMeta::Builder *StructParseMeta::Builder::setPort(const quint16 &port)
{
    structParseMeta->port = port;
    return this;
}

StructParseMeta::Builder *StructParseMeta::Builder::setDatabaseName(const QString &databaseName)
{
    structParseMeta->databaseName = databaseName;
    return this;
}

StructParseMeta::Builder *StructParseMeta::Builder::setUsername(const QString &username)
{
    structParseMeta->username = username;
    return this;
}

StructParseMeta::Builder *StructParseMeta::Builder::setPassword(const QString &password)
{
    structParseMeta->password = password;
    return this;
}

StructParseMeta::Builder *StructParseMeta::Builder::setAsync(const bool &async)
{
    structParseMeta->async = async;
    return this;
}

StructParseMeta::Builder *StructParseMeta::Builder::setAsyncNum(const quint32 &asyncNum)
{
    structParseMeta->asyncNum = asyncNum;
    return this;
}

StructParseMeta *StructParseMeta::Builder::build()
{
    return structParseMeta;
}


QString StructParseMeta::getDatabase() const
{
    return dbType;
}

QString StructParseMeta::getIp() const
{
    return IP;
}

quint16 StructParseMeta::getPort() const
{
    return port;
}

QString StructParseMeta::getDatabaseName() const
{
    return databaseName;
}

QString StructParseMeta::getUsername() const
{
    return username;
}

QString StructParseMeta::getPassword() const
{
    return password;
}

bool StructParseMeta::getAsync() const
{
    return async;
}

quint32 StructParseMeta::getAsyncNum() const
{
    return asyncNum;
}
