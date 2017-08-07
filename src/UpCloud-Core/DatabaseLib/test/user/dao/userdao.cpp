#include "userdao.h"
#include "dbquery.h"
#include "dbtransaction.h"
#include "base.h"
#include "db/err/dbexecption.h"
User UserDao::findByUserId(int id) {
    QString sql = "select id, username, password, email, mobile from user WHERE id=:id";
    QVariantMap params;
    params["id"]       = id;
    //不确定会出异常,可以捕获异常
    DBQuery query;
    try
    {
       return query.uniqueBean(mapToUser, sql,params);
    }
    catch(DBException &excep)
    {
//        qDebug() << excep.getText();
        //既然try...catch,就捕获异常做处理,如果不try...catch,自动回退直到找到try...catch
        throw excep;
    }
    //如果执行uniqueBean接口觉得肯定不会抛出异常,或者会抛出异常,但在findByUserId()不处理,将异常交给调用findByUserId()接口函数,下面可以直接
//    DBQuery query;
//    return query.uniqueBean(mapToUser, sql,params);
}
QList<User> UserDao::list() {
    QString sql = "select id, username, password, email, mobile from user";
    //不确定会出异常,可以捕获异常
    DBQuery query;
    try
    {
       return query.listBeans(mapToUser, sql);
    }
    catch(DBException &excep)
    {
//        qDebug() << excep.getText();
        //既然try...catch,就捕获异常做处理,如果不try...catch,自动回退直到找到try...catch
        throw excep;
    }
    //如果执行uniqueBean接口觉得肯定不会抛出异常,或者会抛出异常,但在findByUserId()不处理,将异常交给调用findByUserId()接口函数,下面可以直接
//  DBQuery query;
//  return query.listBeans(mapToUser, sql);
}
QList<User> UserDao::listByCond(const QString &cond) {
    QString sql = "select id, username, password, email, mobile from user where username like :name";
    QVariantMap params;
    params["name"]       = cond;
    //不确定会出异常,可以捕获异常
    DBQuery query;
    try
    {
       return query.listBeans(mapToUser, sql, params);
    }
    catch(DBException &excep)
    {
//        qDebug() << excep.getText();
        //既然try...catch,就捕获异常做处理,如果不try...catch,自动回退直到找到try...catch
        throw excep;
    }
    //如果执行uniqueBean接口觉得肯定不会抛出异常,或者会抛出异常,但在findByUserId()不处理,将异常交给调用findByUserId()接口函数,下面可以直接
//  DBQuery query;
//  return query.listBeans(mapToUser, sql);
}

void UserDao::listColsByCond(const QString &cond)
{
    QString sql = "select username, password from user where username like :name";
    QVariantMap params;
    params["name"]       = cond;
    QList<QVariantMap> list;
    //不确定会出异常,可以捕获异常
    DBQuery query;
    try
    {
       list = query.list(sql,params);
       foreach (const QVariantMap &u, list) {
           qDebug() << u.value("USERNAME").toString();
           qDebug() << u.value("PASSWORD").toString();
       }
    }
    catch(DBException &excep)
    {
//        qDebug() << excep.getText();
        //既然try...catch,就捕获异常做处理,如果不try...catch,自动回退直到找到try...catch
        throw excep;
    }
    //如果执行uniqueBean接口觉得肯定不会抛出异常,或者会抛出异常,但在findByUserId()不处理,将异常交给调用findByUserId()接口函数,下面可以直接
//  DBQuery query;
//  list = query.list(sql,params);
//  foreach (const QVariantMap &u, list) {
//      qDebug() << u.value("USERNAME").toString();
//      qDebug() << u.value("PASSWORD").toString();
//  }
}

void UserDao::other()
{
    //当有异常发生,终止后面执行,继续后退直到找到try...catch捕获异常
    DBQuery query;
    // 1. 查找 Alice 的 ID
    qDebug() << query.selectVariant("select id from user where username='Alice'").toInt();

    // 2. 查找 Alice 的密码
    qDebug() << query.uniqueResult("select password from user where username='Alice'")["password"].toString();

    // 3. 查找 Alice 的所有信息，如名字，密码，邮件等
    qDebug() << query.uniqueResult("select * from user where username='Alice'");

    // 4. 查找 Alice 和 Bob 的所有信息，如名字，密码，邮件等
    qDebug() << query.list("select * from user where username='Alice' or username='Bob'");

    // 5. 查找 Alice 和 Bob 的密码
    qDebug() << query.selectVariants("select password from user where username='Alice' or username='Bob'");

    // 6. 查询时使用命名参数
    QMap<QString, QVariant> params;
    params["id"] = 1;

    qDebug() << query.uniqueResult("select * from user where id=:id", params);
}
User UserDao::mapToUser(const QVariantMap &rowMap) {
    User user;
    user.id = rowMap.value("ID", -1).toInt();
    user.username = rowMap.value("USERNAME").toString();
    user.password = rowMap.value("PASSWORD").toString();
    user.email    = rowMap.value("EMAIL").toString();
    user.mobile   = rowMap.value("MOBILE").toString();
    return user;
}

void UserDao::insert(const User& user) {
    QString sql = "insert into user(id, username, password, email, mobile) values (:id, :username, :password, :email, :mobile)";

    QVariantMap params;
    params["id"] = user.id;
    params["username"] = user.username;
    params["password"] = user.password;
    params["email"]    = user.email;
    params["mobile"]   = user.mobile;
    //必须try...catch才能回滚和提交
    DBTransaction *transaction = new DBTransaction;
    try
    {
        transaction->beginTransaction();
        //因为这里的key为整形,所以可以这样判断
        int thisKey = transaction->insert(sql, params);
        if(thisKey>0)
        {
            transaction->commit();
            qDebug() << trs("插入成功");
        }
        else
        {
            transaction->rollback();
            DBException excep;
            excep.setType(QSqlError::TransactionError);
            excep.setText(trs("insert error"));
            throw excep;
        }
    }
    catch(DBException &ex)
    {
        qDebug() << trs("插入失败");
        transaction->rollback();
//        qDebug() << excep.getText();
        //既然try...catch,就捕获异常做处理,如果不try...catch,自动回退直到找到try...catch
        throw ex;
    }
}
void UserDao::update(const User& user) {
    bool fly = Environment::Db_Transaction_State::TRANS_FAIL;
    QString sql = "update user set username=:username, password=:password,email=:email, mobile=:mobile where id=:id";

    QVariantMap params;
    params["id"]       = user.id;
    params["username"] = user.username;
    params["password"] = user.password;
    params["email"]    = user.email;
    params["mobile"]   = user.mobile;
    //必须try...catch才能回滚和提交
    DBTransaction *transaction = new DBTransaction;
    try
    {
        transaction->beginTransaction();
        fly = transaction->execSQL(sql,params);
        if(fly == Environment::Db_Transaction_State::TRANS_SUCCESS)
        {
            transaction->commit();
            qDebug() << trs("修改成功");
        }
        else
        {
            DBException excep;
            excep.setType(QSqlError::TransactionError);
            excep.setText(trs("update error"));
            throw excep;
        }
    }
    catch(DBException &ex)
    {
        qDebug() << trs("修改失败");
        transaction->rollback();
        //既然try...catch,就捕获异常做处理,如果不try...catch,自动回退直到找到try...catch
        throw ex;
    }
}
void UserDao::deleteRecord()
{
    bool fly = Environment::Db_Transaction_State::TRANS_FAIL;
    QString sql = "delete from user where username like :username";
    QVariantMap params;
    params["username"] = "To_";

    DBTransaction *transaction = new DBTransaction;
    try
    {
        transaction->beginTransaction();
        fly = transaction->execSQL(sql,params);
        if(fly == Environment::Db_Transaction_State::TRANS_SUCCESS)
        {
            transaction->commit();
            qDebug() << trs("删除成功");
        }
        else
        {
            transaction->rollback();
            DBException excep;
            excep.setType(QSqlError::TransactionError);
            excep.setText(trs("delete error"));
            throw excep;
        }
    }
    catch(DBException &ex)
    {
        qDebug() << trs("删除失败");
        transaction->rollback();
//        qDebug() << excep.getText();
        //既然try...catch,就捕获异常做处理,如果不try...catch,自动回退直到找到try...catch
        throw ex;
    }
}
void UserDao::execSQL()
{
    bool fly = Environment::Db_Transaction_State::TRANS_FAIL;
    QString drop_sql = "drop table user;";
    QString create_sql = "CREATE TABLE `user` ("
                  "`id` int(11) NOT NULL AUTO_INCREMENT,"
                  "`username` varchar(256) NOT NULL,"
                  "`password` varchar(256) NOT NULL,"
                  "`email` varchar(256) DEFAULT NULL,"
                  "`mobile` varchar(32) DEFAULT NULL,"
                  "PRIMARY KEY (`id`)"
                  ");";
    DBTransaction *transaction = new DBTransaction;
    try
    {
        transaction->beginTransaction();
        fly = transaction->execSQL(drop_sql);
        if(fly == Environment::Db_Transaction_State::TRANS_SUCCESS)
        {
            fly = transaction->execSQL(create_sql);
            if(fly == Environment::Db_Transaction_State::TRANS_SUCCESS)
            {
                transaction->commit();
                qDebug() << trs("操作成功");
            }
            else
            {
                transaction->rollback();
                DBException excep;
                excep.setType(QSqlError::TransactionError);
                excep.setText(trs("create table error"));
                throw excep;
            }
        }
        else
        {
            transaction->rollback();
            DBException excep;
            excep.setType(QSqlError::TransactionError);
            excep.setText(trs("drop table error"));
            throw excep;
        }
    }
    //当两次execSQL抛出异常都会执行下面catch
    catch(DBException &ex)
    {
        qDebug() << trs("执行sql失败");
        transaction->rollback();
//        qDebug() << excep.getText();
        //既然try...catch,就捕获异常做处理,如果不try...catch,自动回退直到找到try...catch
        throw ex;
    }
}
