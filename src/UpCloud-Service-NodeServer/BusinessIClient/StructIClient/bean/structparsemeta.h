#ifndef STRUCTPARSEMETA_H
#define STRUCTPARSEMETA_H

#include <QtCore>

class StructParseMeta
{
//public:
//    class  DbType{
//    DbType(){}
//    ~DbType(){}
//    public:
//        static const QString ORACLE;
//        static const QString DB2;
//        static const QString MYSQL;
//        static const QString SQLSERVER;
//        static const QString SQLITE2;
//        static const QString SQLITE3;
//    };
public:
    StructParseMeta(){}
    ~StructParseMeta(){}
//    enum DbType {
//        Oracle,
//        MySQL,
//        SQLite3
//    };


public:
    class  Builder
    {
    public:
        Builder();
        Builder(const QString &dbType,
                const QString &IP,
                const quint16 &port,
                const QString &databaseName,
                const QString &username,
                const QString &password,
                const bool &async,
                const quint32 &asyncNum);
        ~Builder();
    public:
        Builder*  setDatabase(const QString &dbType);
        Builder*  setIp(const QString &IP);
        Builder*  setPort(const quint16 &port);
        Builder*  setDatabaseName(const QString &databaseName);
        Builder*  setUsername(const QString &username);
        Builder*  setPassword(const QString &password);
        Builder*  setAsync(const bool &async);
        Builder*  setAsyncNum(const quint32 &asyncNum);
        StructParseMeta*  build();
    private:
        StructParseMeta* structParseMeta;
    };
public:
    QString getDatabase() const;
    QString getIp() const;
    quint16 getPort() const;
    QString getDatabaseName() const;
    QString getUsername() const;
    QString getPassword() const;
    bool    getAsync() const;
    quint32 getAsyncNum() const;
private:
    //数据库类型
    QString dbType;
    //数据库IP
    QString IP;
    //数据库端口
    quint16 port;
    //数据库名称
    QString databaseName;
    //数据库用户名
    QString username;
    //数据库密码
    QString password;
    //是否支持多路解析
    bool async;
    //支持多路解析,通道数量
    quint32 asyncNum;
};

#endif // STRUCTPARSEMETA_H
