#ifndef DATABASEMETA_H
#define DATABASEMETA_H
#include <QtCore>
#include "databaselib_global.h"
#include "base.h"

/**
 * @brief The DatabaseMeta class    数据库元数据
 */
class DATABASELIBSHARED_EXPORT DatabaseMeta
{
public:
    class DATABASELIBSHARED_EXPORT DbName{
    DbName(){}
    ~DbName(){}
    public:
        static const QString ORACLE;
        static const QString DB2;
        static const QString MYSQL;
        static const QString SQLSERVER;
        static const QString SQLITE2;
        static const QString SQLITE3;
    };
public:
    DatabaseMeta(){}
    ~DatabaseMeta(){}
public:
    class DATABASELIBSHARED_EXPORT Builder{
    public:
        Builder();
        ~Builder();
        Builder(const QString &dbName,const QString &ip,const int &port,
                const QString &instanceName,const QString &username,const QString &password,
                const int &houseKeepingSleepTime,const int &waitIntervalTime);
        /**
         * @brief setDbName 设置数据库类型
         * @param dbName
         * @return
         */
        Builder* setDbName(const QString &dbName = DatabaseMeta::DbName::ORACLE);
        /**
         * @brief setIp 设置数据库连接地址
         * @param ip
         * @return
         */
        Builder* setIp(const QString &ip);
        /**
         * @brief setPort   设置数据库端口号
         * @param port
         * @return
         */
        Builder* setPort(int port);
        /**
         * @brief setInstanceName   设置数据库实例名称(数据库名称)instanceName
         * @param instanceName
         * @return
         */
        Builder* setInstanceName(const QString &instanceName);
        /**
         * @brief setUsername   设置数据库连接用户名
         * @param value
         * @return
         */
        Builder* setUsername(const QString &username);
        /**
         * @brief setPassword   设置数据库连接密码
         * @param value
         * @return
         */
        Builder* setPassword(const QString &password);
        /**
         * @brief setHouseKeepingSleepTime  连接超时时间(ms为单位)
         * @param houseKeepingSleepTime
         * @return
         */
        Builder* setHouseKeepingSleepTime(int houseKeepingSleepTime = 1000);
        /**
         * @brief setWaitIntervalTime   设置等待间隔时间(ms为单位)
         * @param value
         * @return
         */
        Builder* setWaitIntervalTime(int waitIntervalTime = 200);
        DatabaseMeta* build();
    private:
        DatabaseMeta *db;
    };
    QString getDbName() const;

    QString getIp() const;

    int getPort() const;

    QString getInstanceName() const;

    QString getUsername() const;

    QString getPassword() const;

    int getHouseKeepingSleepTime() const;

    int getWaitIntervalTime() const;
    QString getDbDriver() const;
    /**
     * @brief isNull    判断对象为空
     * @return
     */
    bool isNull() const;
private:
    //数据库类型
    QString dbName;
    //数据库连接地址
    QString ip;
    //数据库端口号
    int port;
    //数据库实例名称(数据库名称)instanceName
    QString instanceName;
    //数据库连接用户名
    QString username;
    //数据库连接密码
    QString password;
    //连接超时时间(ms为单位)
    int houseKeepingSleepTime;
    //等待间隔时间(ms为单位)
    int waitIntervalTime;
};

#endif // DATABASEMETA_H
