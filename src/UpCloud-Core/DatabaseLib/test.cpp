#include <QCoreApplication>
#include <QtCore>
#include "db.h"
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QString confPath = QString(trs("C:/UpCloud-package/conf/NodeServer-db.conf"));
    DatabaseConnectionPool::initialize(confPath);
    DBTransaction *tx = new DBTransaction;
    tx->beginTransaction();
    QString sql = "insert into user(id, username, password, email, mobile) values (:id, :username, :password, :email, :mobile)";

    QVariantMap params;
    params["id"] = "111";
    params["username"] = "111";
    params["password"] = "111";
    params["email"]    = "111";
    params["mobile"]   = "111";
    //必须try...catch才能回滚和提交
    DBTransaction *transaction = new DBTransaction;
    try
    {
        transaction->beginTransaction();
        DatabaseMeta::Builder *builder = new DatabaseMeta::Builder;
        DatabaseMeta *dbMeta = builder->setDbName(DatabaseMeta::DbName::MYSQL)->setIp(trs("10.0.0.114"))->setPort(3306)->setInstanceName(trs("c##nodeserver"))
                ->setUsername(trs("root"))->setPassword(trs("root"))->build();
        transaction->setDatabaseMeta(*dbMeta);
        //因为这里的key为整形,所以可以这样判断
        bool stats = transaction->execSQL(sql, params);
        if(stats)
        {
            transaction->commit();
            qDebug() << trs("插入成功");
        }
        else
        {
            transaction->rollback();
            DBException excep;
            excep.setType(QSqlError::TransactionError);
            excep.setText(trs("Exec Error"));
            throw excep;
        }
        delete dbMeta;
    }
    catch(DBException &ex)
    {
        qDebug() << trs("Exec Error");
        transaction->rollback();
        throw ex;
    }
    delete transaction;
    DatabaseConnectionPool::release();
    return a.exec();
}
/*
//test db page
#include <QCoreApplication>
#include <QtCore>
#include "db.h"


class Row
{
public:
    int id;
    QString name;
    int age;
};
Row mapToBean(const QVariantMap &rowMap)
{
    Row r;
    r.id = rowMap.value("id").toInt();
    r.name = rowMap.value("name").toString();
    r.age = rowMap.value("age").toInt();
    return r;
}


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QString confPath = QString(trs("C:/UpCloud-package/conf/NodeServer-db.conf"));
    DatabaseConnectionPool::initialize(confPath);

    DatabaseMeta::Builder *builder = new DatabaseMeta::Builder;
    DatabaseMeta *dbMeta = builder->setDbName(DatabaseMeta::DbName::MYSQL)
            ->setIp(trs("10.0.0.110"))->setPort(3306)->setInstanceName(trs("test"))
            ->setUsername(trs("root"))->setPassword(trs("root"))->build();

    Page* page = new Page;
    //设置第几页
    page->setCurPageNum((quint32)1);
    //设置每页显示条数
    page->setNumPerPage((quint32)20);
    //设置排序字段
    page->setOrderFieldName(trs("age"));
    //设置排序方式
    page->setOrderField(Page::DESC);
    QString sql;
    QVariantMap params;

    sql = "select * from people where 1 = 1";
    QString odfName = page->getOrderFieldName();
    if(!(odfName.isEmpty()))
    {
        if(odfName == trs("name"))
        {
            sql.append(trs(" order by name"));
        }
        else if(odfName == trs("age"))
        {
            sql.append(trs(" order by age"));
        }
        sql.append((page->getOrderField() == Page::DESC) ? trs(" desc"):trs(" asc"));
    }
    DBQuery query;
    query.setDatabaseMeta(*dbMeta);
    try
    {
//        page = query.page(page,sql,params);
//        qDebug() << "Page OK!";
//        quint32 curPageNum;
//        //每页显示条数
//        quint32 numPerPage;
//        //倒序还是正序
//        // Order orderField;
//        //排序字段名
//        QString orderFieldName;
//        //总页数
//        quint32 totalPages;
//        //所有记录总条数
//        quint64 totalCount;
//        //记录
//        QList<QVariantMap> results;
//        qDebug() << "curPageNum = " << page->getCurPageNum();
//        qDebug() << "numPerPage = " << page->getNumPerPage();
//        qDebug() << "orderFieldName = " << page->getOrderFieldName();
//        qDebug() << "totalPages = " << page->getTotalPages();
//        qDebug() << "totalCount = " << page->getTotalCount();
//        for(int i=0; i<page->getResults().size(); i++)
//        {
//            qDebug() << "result:" << page->getResults().at(i);
//        }
//        qDebug("Test End!");
        QList<Row> rows;
        QVariantMap rowMap;
        rows = query.pageBean(mapToBean, page, sql, params);
        for(int i=0; i<rows.size(); i++)
        {
            qDebug() << rows.at(i).id << "_" << rows.at(i).age << "_" << rows.at(i).name;
        }
    }
    catch(DBException &ex)
    {
        qDebug() << trs("Exec Error");
    }
    DatabaseConnectionPool::release();
    return a.exec();
}

 */
////////////////////////////////////////////////////////////测试使用多个数据源
//#include <QCoreApplication>
//#include <QtCore>
//#include "db.h"
//int main(int argc, char *argv[])
//{
//    QCoreApplication a(argc, argv);
//    QString confPath = QString(trs("C:/UpCloud-package/conf/NodeServer-db.conf"));
//    DatabaseConnectionPool::initialize(confPath);
//    QString sql = "select TASK_NUM from ns_r_unstruct_task WHERE UUID =:taskUUID";
//    QVariantMap params;
//    params["taskUUID"]       = QString("dsdasdasfdsfsdddas");
//    DBQuery query;
//    int taskNum = (quint32)query.selectVariant(sql, params).toUInt();
//    QString sql2 = "select TASK_NUM from ns_r_unstruct_task WHERE UUID =:taskUUID";
//    QVariantMap params2;
//    params2["taskUUID"]       = QString("111");
//    DBQuery query2;
//    DatabaseMeta::Builder *builder = new DatabaseMeta::Builder;
//    DatabaseMeta *dbMeta = builder->setDbName(DatabaseMeta::DbName::MYSQL)->setIp(trs("10.0.0.114"))->setPort(3306)->setInstanceName(trs("c##nodeserver"))
//            ->setUsername(trs("root"))->setPassword(trs("root"))->build();
//    query2.setDatabaseMeta(*dbMeta);
//    int taskNum2 = (quint32)query2.selectVariant(sql2, params2).toUInt();


//    QString sql3 = "select TASK_NUM from ns_r_unstruct_task WHERE UUID =:taskUUID";
//    QVariantMap params3;
//    params3["taskUUID"]       = QString("111");
//    DBQuery query3;
//    DatabaseMeta::Builder *builder3 = new DatabaseMeta::Builder;
//    DatabaseMeta *dbMeta3 = builder3->setDbName(DatabaseMeta::DbName::MYSQL)->setIp(trs("10.0.0.114"))->setPort(3306)->setInstanceName(trs("c##nodeserver"))
//            ->setUsername(trs("root"))->setPassword(trs("root"))->build();
//    query3.setDatabaseMeta(*dbMeta3);
//    int taskNum3 = (quint32)query2.selectVariant(sql3, params3).toUInt();


//    DatabaseConnectionPool::release();
//    return a.exec();
//}

////////////////////////////////////////////////////////////校验数据库驱动是否有效
//if(!QSqlDatabase::isDriverAvailable("QOCI"))
//{
//    qFatal("Driver not loaded");
//}

////////////////////////////////////////////////////////////1.读取database.conf配置
/*
#include <QCoreApplication>
#include <QtCore>
#include "base.h"
#include "db/conf/databaseconf.h"
int main(int argc, char *argv[])
{
    //注册系统日志自定义格式监听器
    Logger::registerSystemLogger();

    QCoreApplication app( argc, argv );
    qDebug() << "dbDriver:" << DatabaseConf::getInstance().dbDriver();
    qDebug() << "dbName:" << DatabaseConf::getInstance().dbName();
    qDebug() << "houseKeepingSleepTime:" << DatabaseConf::getInstance().houseKeepingSleepTime();
    qDebug() << "instanceName:" << DatabaseConf::getInstance().instanceName();
    qDebug() << "ip:" << DatabaseConf::getInstance().ip();
    qDebug() << "isDebug:" << DatabaseConf::getInstance().isDebug();
    qDebug() << "maximumConnectionCount:" << DatabaseConf::getInstance().maximumConnectionCount();
    qDebug() << "minimumConnectionCount:" << DatabaseConf::getInstance().minimumConnectionCount();
    qDebug() << "password:" << DatabaseConf::getInstance().password();
    qDebug() << "port:" << DatabaseConf::getInstance().port();
    qDebug() << "testOnBorrow:" << DatabaseConf::getInstance().testOnBorrow();
    qDebug() << "testOnBorrowSql:" << DatabaseConf::getInstance().testOnBorrowSql();
    qDebug() << "username:" << DatabaseConf::getInstance().username();
    qDebug() << "waitIntervalTime:" << DatabaseConf::getInstance().waitIntervalTime();
    return app.exec();
}
*/

//////////////////////////////////////////////////////////////2.使用封装DBQuery/DBTransaction
///// 实现代码
//#include "userdao.h"
//#include "dbquery.h"
//#include "dbtransaction.h"
//#include "base.h"
//#include "db/err/dbexecption.h"
//User UserDao::findByUserId(int id) {
//    QString sql = "select id, username, password, email, mobile from user WHERE id=:id";
//    QVariantMap params;
//    params["id"]       = id;
//    //不确定会出异常,可以捕获异常
//    DBQuery query;
//    try
//    {
//       return query.uniqueBean(mapToUser, sql,params);
//    }
//    catch(DBException &excep)
//    {
////        qDebug() << excep.getText();
//        //既然try...catch,就捕获异常做处理,如果不try...catch,自动回退直到找到try...catch
//        throw excep;
//    }
//    //如果执行uniqueBean接口觉得肯定不会抛出异常,或者会抛出异常,但在findByUserId()不处理,将异常交给调用findByUserId()接口函数,下面可以直接
////    DBQuery query;
////    return query.uniqueBean(mapToUser, sql,params);
//}
//QList<User> UserDao::list() {
//    QString sql = "select id, username, password, email, mobile from user";
//    //不确定会出异常,可以捕获异常
//    DBQuery query;
//    try
//    {
//       return query.listBeans(mapToUser, sql);
//    }
//    catch(DBException &excep)
//    {
////        qDebug() << excep.getText();
//        //既然try...catch,就捕获异常做处理,如果不try...catch,自动回退直到找到try...catch
//        throw excep;
//    }
//    //如果执行uniqueBean接口觉得肯定不会抛出异常,或者会抛出异常,但在findByUserId()不处理,将异常交给调用findByUserId()接口函数,下面可以直接
////  DBQuery query;
////  return query.listBeans(mapToUser, sql);
//}
//QList<User> UserDao::listByCond(const QString &cond) {
//    QString sql = "select id, username, password, email, mobile from user where username like :name";
//    QVariantMap params;
//    params["name"]       = cond;
//    //不确定会出异常,可以捕获异常
//    DBQuery query;
//    try
//    {
//       return query.listBeans(mapToUser, sql, params);
//    }
//    catch(DBException &excep)
//    {
////        qDebug() << excep.getText();
//        //既然try...catch,就捕获异常做处理,如果不try...catch,自动回退直到找到try...catch
//        throw excep;
//    }
//    //如果执行uniqueBean接口觉得肯定不会抛出异常,或者会抛出异常,但在findByUserId()不处理,将异常交给调用findByUserId()接口函数,下面可以直接
////  DBQuery query;
////  return query.listBeans(mapToUser, sql);
//}

//void UserDao::listColsByCond(const QString &cond)
//{
//    QString sql = "select username, password from user where username like :name";
//    QVariantMap params;
//    params["name"]       = cond;
//    QList<QVariantMap> list;
//    //不确定会出异常,可以捕获异常
//    DBQuery query;
//    try
//    {
//       list = query.list(sql,params);
//       foreach (const QVariantMap &u, list) {
//           qDebug() << u.value("USERNAME").toString();
//           qDebug() << u.value("PASSWORD").toString();
//       }
//    }
//    catch(DBException &excep)
//    {
////        qDebug() << excep.getText();
//        //既然try...catch,就捕获异常做处理,如果不try...catch,自动回退直到找到try...catch
//        throw excep;
//    }
//    //如果执行uniqueBean接口觉得肯定不会抛出异常,或者会抛出异常,但在findByUserId()不处理,将异常交给调用findByUserId()接口函数,下面可以直接
////  DBQuery query;
////  list = query.list(sql,params);
////  foreach (const QVariantMap &u, list) {
////      qDebug() << u.value("USERNAME").toString();
////      qDebug() << u.value("PASSWORD").toString();
////  }
//}

//void UserDao::other()
//{
//    //当有异常发生,终止后面执行,继续后退直到找到try...catch捕获异常
//    DBQuery query;
//    // 1. 查找 Alice 的 ID
//    qDebug() << query.selectVariant("select id from user where username='Alice'").toInt();

//    // 2. 查找 Alice 的密码
//    qDebug() << query.uniqueResult("select password from user where username='Alice'")["password"].toString();

//    // 3. 查找 Alice 的所有信息，如名字，密码，邮件等
//    qDebug() << query.uniqueResult("select * from user where username='Alice'");

//    // 4. 查找 Alice 和 Bob 的所有信息，如名字，密码，邮件等
//    qDebug() << query.list("select * from user where username='Alice' or username='Bob'");

//    // 5. 查找 Alice 和 Bob 的密码
//    qDebug() << query.selectVariants("select password from user where username='Alice' or username='Bob'");

//    // 6. 查询时使用命名参数
//    QMap<QString, QVariant> params;
//    params["id"] = 1;

//    qDebug() << query.uniqueResult("select * from user where id=:id", params);
//}
//User UserDao::mapToUser(const QVariantMap &rowMap) {
//    User user;
//    user.id = rowMap.value("ID", -1).toInt();
//    user.username = rowMap.value("USERNAME").toString();
//    user.password = rowMap.value("PASSWORD").toString();
//    user.email    = rowMap.value("EMAIL").toString();
//    user.mobile   = rowMap.value("MOBILE").toString();
//    return user;
//}

//void UserDao::insert(const User& user) {
//    QString sql = "insert into user(id, username, password, email, mobile) values (:id, :username, :password, :email, :mobile)";

//    QVariantMap params;
//    params["id"] = user.id;
//    params["username"] = user.username;
//    params["password"] = user.password;
//    params["email"]    = user.email;
//    params["mobile"]   = user.mobile;
//    //必须try...catch才能回滚和提交
//    DBTransaction *transaction = new DBTransaction;
//    try
//    {
//        transaction->beginTransaction();
//        //因为这里的key为整形,所以可以这样判断
//        int thisKey = transaction->insert(sql, params).toInt();
//        if(thisKey>0)
//        {
//            transaction->commit();
//            qDebug() << trs("插入成功");
//        }
//        else
//        {
//            transaction->rollback();
//            DBException excep;
//            excep.setType(QSqlError::TransactionError);
//            excep.setText(trs("insert error"));
//            throw excep;
//        }
//    }
//    catch(DBException &ex)
//    {
//        qDebug() << trs("插入失败");
//        transaction->rollback();
////        qDebug() << excep.getText();
//        //既然try...catch,就捕获异常做处理,如果不try...catch,自动回退直到找到try...catch
//        throw ex;
//    }
//}
//void UserDao::update(const User& user) {
//    bool fly = Environment::Db_Transaction_State::TRANS_FAIL;
//    QString sql = "update user set username=:username, password=:password,email=:email, mobile=:mobile where id=:id";

//    QVariantMap params;
//    params["id"]       = user.id;
//    params["username"] = user.username;
//    params["password"] = user.password;
//    params["email"]    = user.email;
//    params["mobile"]   = user.mobile;
//    //必须try...catch才能回滚和提交
//    DBTransaction *transaction = new DBTransaction;
//    try
//    {
//        transaction->beginTransaction();
//        fly = transaction->execSQL(sql,params);
//        if(fly == Environment::Db_Transaction_State::TRANS_SUCCESS)
//        {
//            transaction->commit();
//            qDebug() << trs("修改成功");
//        }
//        else
//        {
//            DBException excep;
//            excep.setType(QSqlError::TransactionError);
//            excep.setText(trs("update error"));
//            throw excep;
//        }
//    }
//    catch(DBException &ex)
//    {
//        qDebug() << trs("修改失败");
//        transaction->rollback();
//        //既然try...catch,就捕获异常做处理,如果不try...catch,自动回退直到找到try...catch
//        throw ex;
//    }
//}
//void UserDao::deleteRecord()
//{
//    bool fly = Environment::Db_Transaction_State::TRANS_FAIL;
//    QString sql = "delete from user where username like :username";
//    QVariantMap params;
//    params["username"] = "To_";

//    DBTransaction *transaction = new DBTransaction;
//    try
//    {
//        transaction->beginTransaction();
//        fly = transaction->execSQL(sql,params);
//        if(fly == Environment::Db_Transaction_State::TRANS_SUCCESS)
//        {
//            transaction->commit();
//            qDebug() << trs("删除成功");
//        }
//        else
//        {
//            transaction->rollback();
//            DBException excep;
//            excep.setType(QSqlError::TransactionError);
//            excep.setText(trs("delete error"));
//            throw excep;
//        }
//    }
//    catch(DBException &ex)
//    {
//        qDebug() << trs("删除失败");
//        transaction->rollback();
////        qDebug() << excep.getText();
//        //既然try...catch,就捕获异常做处理,如果不try...catch,自动回退直到找到try...catch
//        throw ex;
//    }
//}
//void UserDao::execSQL()
//{
//    bool fly = Environment::Db_Transaction_State::TRANS_FAIL;
//    QString drop_sql = "drop table user;";
//    QString create_sql = "CREATE TABLE `user` ("
//                  "`id` int(11) NOT NULL AUTO_INCREMENT,"
//                  "`username` varchar(256) NOT NULL,"
//                  "`password` varchar(256) NOT NULL,"
//                  "`email` varchar(256) DEFAULT NULL,"
//                  "`mobile` varchar(32) DEFAULT NULL,"
//                  "PRIMARY KEY (`id`)"
//                  ");";
//    DBTransaction *transaction = new DBTransaction;
//    try
//    {
//        transaction->beginTransaction();
//        fly = transaction->execSQL(drop_sql);
//        if(fly == Environment::Db_Transaction_State::TRANS_SUCCESS)
//        {
//            fly = transaction->execSQL(create_sql);
//            if(fly == Environment::Db_Transaction_State::TRANS_SUCCESS)
//            {
//                transaction->commit();
//                qDebug() << trs("操作成功");
//            }
//            else
//            {
//                transaction->rollback();
//                DBException excep;
//                excep.setType(QSqlError::TransactionError);
//                excep.setText(trs("create table error"));
//                throw excep;
//            }
//        }
//        else
//        {
//            transaction->rollback();
//            DBException excep;
//            excep.setType(QSqlError::TransactionError);
//            excep.setText(trs("drop table error"));
//            throw excep;
//        }
//    }
//    //当两次execSQL抛出异常都会执行下面catch
//    catch(DBException &ex)
//    {
//        qDebug() << trs("执行sql失败");
//        transaction->rollback();
////        qDebug() << excep.getText();
//        //既然try...catch,就捕获异常做处理,如果不try...catch,自动回退直到找到try...catch
//        throw ex;
//    }
//}
///// 测试代码,最后必须ConnectionPool::release();
//#include <QCoreApplication>
//#include <QtCore>
//#include "base.h"
//#include "test/user/dao/userdao.h"
//#include "test/user/bean/user.h"
//#include "db.h"
//int main(int argc, char *argv[])
//{
//    //注册系统日志自定义格式监听器
//    Logger::registerSystemLogger();

//    QCoreApplication app( argc, argv );
//    ///////////////////////////查询操作测试//////////////////////////////////////////////////////////////
//    /*
//    //findByUserId
//    try
//    {
//        User user = UserDao::findByUserId(1);
//        qDebug() << user.username;
//    }
//    catch(DBException &excep)
//    {
//        qDebug() << "Error: type:" << excep.getType() << ",typeDesc:" << excep.getTypeDesc() << ",text:" << excep.getText();
//    }
//    */
//    /*
//    //list
//    try
//    {
//        QList<User> list = UserDao::list();
//        for(User user:list)
//            qDebug() << user.username;
//    }
//    catch(DBException &excep)
//    {
//        qDebug() << "Error: type:" << excep.getType() << ",typeDesc:" << excep.getTypeDesc() << ",text:" << excep.getText();
//    }
//    */
//    /*
//    //listByCond
//    try
//    {
//        QList<User> list = UserDao::listByCond(QString("%os%"));
//        for(User user:list)
//            qDebug() << user.username;
//    }
//    catch(DBException &excep)
//    {
//        qDebug() << "Error: type:" << excep.getType() << ",typeDesc:" << excep.getTypeDesc() << ",text:" << excep.getText();
//    }
//    */
//    /*
//    //listColsByCond
//    try
//    {
//        UserDao::listColsByCond(QString("%os%"));
//    }
//    catch(DBException &excep)
//    {
//        qDebug() << "Error: type:" << excep.getType() << ",typeDesc:" << excep.getTypeDesc() << ",text:" << excep.getText();
//    }
//    try
//    {
//        UserDao::other();
//    }
//    catch(DBException &excep)
//    {
//        qDebug() << "Error: type:" << excep.getType() << ",typeDesc:" << excep.getTypeDesc() << ",text:" << excep.getText();
//    }
//    */
//    ///////////////////////////事务操作测试//////////////////////////////////////////////////////////////
//    /*
//    //insert
//    User *user = new User;
//    user->id = 4;
//    user->username = "Tom";
//    user->email = "tom@163.com";
//    user->mobile = "23131312";
//    user->password = "sascs";
//    try
//    {
//        UserDao::insert(*user);
//    }
//    catch(DBException &excep)
//    {
//        qDebug() << "Error: type:" << excep.getType() << ",typeDesc:" << excep.getTypeDesc() << ",text:" << excep.getText();
//    }
//    delete user;
//    */
//    /*
//    //update
//    User *user = new User;
//    user->id = 4;
//    user->username = "Tom";
//    user->email = "tom@163.com";
//    user->mobile = "01010101";
//    user->password = "sascs";
//    try
//    {
//        UserDao::update(*user);
//    }
//    catch(DBException &excep)
//    {
//        qDebug() << "Error: type:" << excep.getType() << ",typeDesc:" << excep.getTypeDesc() << ",text:" << excep.getText();
//    }
//    delete user;
//    */
//    /*
//    //deleteRecord
//    try
//    {
//        UserDao::deleteRecord();
//    }
//    catch(DBException &excep)
//    {
//        qDebug() << "Error: type:" << excep.getType() << ",typeDesc:" << excep.getTypeDesc() << ",text:" << excep.getText();
//    }
//    */
//    /*
//    //execSQL
//    try
//    {
//        UserDao::execSQL();
//    }
//    catch(DBException &excep)
//    {
//        qDebug() << "Error: type:" << excep.getType() << ",typeDesc:" << excep.getTypeDesc() << ",text:" << excep.getText();
//    }
//    */
//    ConnectionPool::release();
//    return app.exec();
//}

////////////////////////////////////////////////////////////3.调用连接池写传统调用Qt接口操作数据库
/*
//在main的最后必须ConnectionPool::release();
//(1).最简单操作
void foo() {
    try
    {
        // 1. 从数据库连接池里取得连接
        QSqlDatabase db = ConnectionPool::openConnection();
        // 2. 使用连接查询数据库
        QSqlQuery query(db);
        query.exec("SELECT * FROM user where id=1");
        query.exec();
        while (query.next()) {
            qDebug() << query.value("username").toString();
        }
        // 3. 连接使用完后需要释放回数据库连接池
        ConnectionPool::closeConnection(db);
    }
    catch(DBException &excep)
    {
//        qDebug() << excep.getText();
        //既然try...catch,就捕获异常做处理,如果不try...catch,自动回退直到找到try...catch
        throw excep;
    }
}
//(2).不带事务的使用占位符?
void foo() {
    try
    {
        // 1. 从数据库连接池里取得连接
        QSqlDatabase db = ConnectionPool::openConnection();
        // 2. 使用连接查询数据库
        QSqlQuery query(db);
        query.prepare("SELECT * FROM user where id=? and username = ?");
        int idValue = 100;
        QString nameValue = "ChenYun";
        query.addBindValue(idValue);
        query.addBindValue(nameValue);
        query.exec();
        while (query.next()) {
            qDebug() << query.value("username").toString();
        }
        // 3. 连接使用完后需要释放回数据库连接池
        ConnectionPool::closeConnection(db);
    }
    catch(DBException &excep)
    {
//        qDebug() << excep.getText();
        //既然try...catch,就捕获异常做处理,如果不try...catch,自动回退直到找到try...catch
        throw excep;
    }
}
int main(int argc, char *argv[]) {
    foo();
    ConnectionPool::release(); // 4. 释放数据库连接
    return 0;
}
//(3).不带事务的使用占位符:
void foo() {
    try
    {
        // 1. 从数据库连接池里取得连接
        DBException dbExcep;
        QSqlDatabase db = ConnectionPool::openConnection(dbExcep);
        if(dbExcep.getType()!=QSqlError::ErrorType::NoError)
        {
            ConnectionPool::closeConnection(db);
            throw dbExcep;
        }
        // 2. 使用连接查询数据库
        QSqlQuery query(db);
        query.prepare("SELECT * FROM user where id=:id and username =:username");
        int idValue = 100;
        QString nameValue = "ChenYun";
        query.bindValue(":id", idValue);
        query.bindValue(":name", nameValue);
        query.exec();
        // 3. 连接使用完后需要释放回数据库连接池
        ConnectionPool::closeConnection(db);
    }
    catch(DBException &excep)
    {
//        qDebug() << excep.getText();
        //既然try...catch,就捕获异常做处理,如果不try...catch,自动回退直到找到try...catch
        throw excep;
    }
}
//(4).带事务的使用占位符:
void foo() {
    QSqlDatabase db;
    try
    {
        // 1. 从数据库连接池里取得连接
        DBException dbExcep;
        db = ConnectionPool::openConnection(dbExcep);
        if(dbExcep.getType()!=QSqlError::ErrorType::NoError)
        {
            ConnectionPool::closeConnection(db);
            throw dbExcep;
        }
        db.transaction();
        // 2. 使用连接查询数据库
        QSqlQuery query(db);
        query.prepare("insert into student (id, name) values (:id, :name)");
        int idValue = 100;
        QString nameValue = "ChenYun";
        query.bindValue(":id", idValue);
        query.bindValue(":name", nameValue);
        query.exec();
        db.commit();
        // 3. 连接使用完后需要释放回数据库连接池
        ConnectionPool::closeConnection(db);
    }
    catch(DBException &excep)
    {
        if(db.isValid())
            db.rollback();
//        qDebug() << excep.getText();
        //既然try...catch,就捕获异常做处理,如果不try...catch,自动回退直到找到try...catch
        throw excep;
    }
}
//(5).带事务的使用占位符?
void foo() {
    QSqlDatabase db;
    try
    {
        // 1. 从数据库连接池里取得连接
        DBException dbExcep;
        db = ConnectionPool::openConnection(dbExcep);
        if(dbExcep.getType()!=QSqlError::ErrorType::NoError)
        {
            ConnectionPool::closeConnection(db);
            throw dbExcep;
        }
        db.transaction();
        // 2. 使用连接查询数据库
        QSqlQuery query(db);
        query.prepare("insert into student (id, name) values (?, ?)");
        int idValue = 100;
        QString nameValue = "ChenYun";
        query.addBindValue(idValue);
        query.addBindValue(nameValue);
        query.exec();
        db.commit();
        // 3. 连接使用完后需要释放回数据库连接池
        ConnectionPool::closeConnection(db);
    }
    catch(DBException &excep)
    {
        if(db.isValid())
            db.rollback();
//        qDebug() << excep.getText();
        //既然try...catch,就捕获异常做处理,如果不try...catch,自动回退直到找到try...catch
        throw excep;
    }
}
//(6).批处理操作使用占位符?
void foo() {
    QSqlDatabase db;
    try
    {
        // 1. 从数据库连接池里取得连接
        DBException dbExcep;
        db = ConnectionPool::openConnection(dbExcep);
        if(dbExcep.getType()!=QSqlError::ErrorType::NoError)
        {
            ConnectionPool::closeConnection(db);
            throw dbExcep;
        }
        // 2. 使用连接查询数据库
        QSqlQuery query(db);
        // 批处理
        query.prepare("insert into student (id, name) values (?, ?)");
        QVariantList ids;
        ids << 20 << 21 << 22;
        query.addBindValue(ids);
        QVariantList names;
        names << "xiaoming" << "xiaoliang" << "xiaogang";
        query.addBindValue(names);
        query.execBatch();
        db.commit();
        // 3. 连接使用完后需要释放回数据库连接池
        ConnectionPool::closeConnection(db);
    }
    catch(DBException &excep)
    {
        if(db.isValid())
            db.rollback();
//        qDebug() << excep.getText();
        //既然try...catch,就捕获异常做处理,如果不try...catch,自动回退直到找到try...catch
        throw excep;
    }
}
int main(int argc, char *argv[]) {
    foo();
    ConnectionPool::release(); // 4. 释放数据库连接
    return 0;
}

*/
