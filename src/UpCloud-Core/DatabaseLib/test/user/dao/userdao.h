#ifndef USERDAO_H
#define USERDAO_H
#include <QtCore>
#include "test/user/bean/user.h"
#include "databaselib_global.h"

class DATABASELIBSHARED_EXPORT UserDao
{
public:
    ///////////////////////////////////////////////////////////////////////////////
    ///                                                                          //
    ///                              查询方法                                     //
    ///                                                                          //
    ///////////////////////////////////////////////////////////////////////////////
    /**
     * @brief findByUserId  根据逐渐查找整个对象
     * @param id
     * @return
     */
    static User findByUserId(int id);
    /**
     * @brief list  查找所有对象
     * @return
     */
    static QList<User> list();
    /**
     * @brief listByCond    查找满足条件的对象
     * @param cond
     * @return
     */
    static QList<User> listByCond(const QString &cond);
    /**
     * @brief listColsByCond    查询指定的列
     * @param cond
     */
    static void listColsByCond(const QString &cond);
    /**
     * @brief other 其他参考方法
     */
    static void other();
///////////////////////////////////////////////////////////////////////////////
///                                                                          //
///                              操作事务                                     //
///                                                                          //
///////////////////////////////////////////////////////////////////////////////
    /**
    * @brief insert 插入一条记录
    * @param user
    */
    static void insert(const User &user);
    /**
     * @brief update    修改一条记录
     * @param user
     */
    static void update(const User &user);
    /**
     * @brief deleteRecord  根据参数删除用户信息
     * @param params
     */
    static void deleteRecord();
    /**
     * @brief execSQL   执行操作事务的其他SQL语句
     */
    void execSQL();

private:
    static User mapToUser(const QVariantMap &rowMap);
};

#endif // USERDAO_H
