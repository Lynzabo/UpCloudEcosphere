#include "databaseconf.h"

SINGLETON_INITIALIZE(DatabaseConf)

DatabaseConf::DatabaseConf() {

}

DatabaseConf::~DatabaseConf() {
    delete settings;
    settings = NULL;
}


void DatabaseConf::setConfPath(const QString &confPath)
{
    this->confPath = confPath;
}

void DatabaseConf::loadConf()
{
    // 配置文件路径
    settings = new QSettings(confPath, QSettings::IniFormat);
}

QString DatabaseConf::dbName() const
{
    return settings->value("upCloud.database.dbName",QString()).toString();
}

QString DatabaseConf::dbDriver() const
{
    const QString dbLowerName = settings->value("upCloud.database.dbName",QString()).toString().toLower();
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

QString DatabaseConf::ip() const
{
    return settings->value("upCloud.database.ip",QString("127.0.0.1")).toString();
}

int DatabaseConf::port() const
{
    return settings->value("upCloud.database.port",0).toInt();
}

QString DatabaseConf::instanceName() const
{
    return settings->value("upCloud.database.instanceName",QString()).toString();
}

QString DatabaseConf::username() const
{
    return settings->value("upCloud.database.username",QString()).toString();
}

QString DatabaseConf::password() const
{
    return settings->value("upCloud.database.password",QString()).toString();
}

int DatabaseConf::houseKeepingSleepTime() const
{
    return settings->value("upCloud.database.houseKeepingSleepTime",1000).toInt();
}

int DatabaseConf::waitIntervalTime() const
{
    return settings->value("upCloud.database.waitIntervalTime",200).toInt();
}

int DatabaseConf::maximumConnectionCount() const
{
    return settings->value("upCloud.database.maximumConnectionCount",100).toInt();
}

int DatabaseConf::minimumConnectionCount() const
{
    return settings->value("upCloud.database.minimumConnectionCount",0).toInt();
}

bool DatabaseConf::isDebug() const
{
    return settings->value("upCloud.database.debug",true).toBool();
}

bool DatabaseConf::testOnBorrow() const
{
    return settings->value("upCloud.database.testOnBorrow",true).toBool();
}

QString DatabaseConf::testOnBorrowSql() const
{
    return settings->value("upCloud.database.testOnBorrowSql",QString("select 1")).toString();
}
