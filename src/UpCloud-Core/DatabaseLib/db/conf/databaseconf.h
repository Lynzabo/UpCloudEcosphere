#ifndef DATABASECONF_H
#define DATABASECONF_H
#include <QtCore>
#include "databaselib_global.h"
#include "base.h"
class DATABASELIBSHARED_EXPORT DatabaseConf
{
    // 使用单例模式:
    // 取得对象 ConfigUtil::getInstance()
    // 删除对象 ConfigUtil::release()
    SINGLETON(DatabaseConf)
public:
    /**
     * @brief setConfPath   设置conf路径
     * @param confPath
     */
    void setConfPath(const QString &confPath);
    /**
     * @brief loadConf  加载配置文件
     */
    void loadConf();
    /**
     * @brief dbName    数据库类型
     * @return
     */
    QString dbName() const;
    /**
     * @brief dbName    数据库驱动类型
     * @return
     */
    QString dbDriver() const;
    /**
     * @brief ip    数据库连接地址
     * @return
     */
    QString ip() const;
    /**
     * @brief port  数据库端口号
     * @return
     */
    int port() const;
    /**
     * @brief instanceName  数据库实例名称(数据库名称)
     * @return
     */
    QString instanceName() const;
    /**
     * @brief username  数据库连接用户名
     * @return
     */
    QString username() const;
    /**
     * @brief password  数据库连接密码
     * @return
     */
    QString password() const;
    /**
     * @brief houseKeepingSleepTime 连接超时时间(ms为单位)
     * @return
     */
    int houseKeepingSleepTime() const;
    /**
     * @brief waitIntervalTime  等待间隔时间(ms为单位)
     * @return
     */
    int waitIntervalTime() const;
    /**
     * @brief maximumConnectionCount    连接池最大连接数
     * @return
     */
    int maximumConnectionCount() const;
    /**
     * @brief minimumConnectionCount    连接池最小连接数    代码中暂未解析
     * @return
     */
    int minimumConnectionCount() const;
    /**
     * @brief isDebug   调试模式(会输出数据库事务变化，执行SQL情况等输出信息)
     * @return
     */
    bool isDebug() const;
    /**
     * @brief testOnBorrow  取得连接的时候验证连接是否有效
     * @return
     */
    bool testOnBorrow() const;
    /**
     * @brief testOnBorrowSql   测试访问数据库的 SQL
     * @return
     * Notice   当testOnBorrow为true,testOnBorrowSql设置才有意义
     */
    QString testOnBorrowSql() const;

private:
    QSettings *settings;
    //conf路径
    QString confPath;
};

#endif // DATABASECONF_H
