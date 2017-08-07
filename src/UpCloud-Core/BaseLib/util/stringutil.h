#ifndef STRINGUTIL_H
#define STRINGUTIL_H
#include "core/singleton.h"
#include "baselib_global.h"
#include <QtCore>
/**
 * @brief The StringUtil class  字符串常用方法封装
 */
class BASELIBSHARED_EXPORT StringUtil
{
    SINGLETON(StringUtil)
public:
    /**
     * @brief formatSQLInParamsToInSQLCondition    转换QStringList字符串列表为SQL语句中in可以使用的条件
     * @param strList
     * @param inCondition
     * 如strList << "111" << "222" << "333";转换后结果'111','222','333'
     * SQL语句中使用in ('111','222','333')
     */
    void formatSQLInParamsToInSQLCondition(const QStringList &strList,QString &inCondition);
    /**
          因为bindValue没办法修改,所以只能修改
     * @brief formatSQLInParamsToInSQLCondition   通过修改sql和params  接口来实现sql in() 的使用
     * @param sql        原sql语句
     * @param params     供sql语句使用的params
     * @param strList    in 后所用的参数
     * @param indicate   要替换的标示符
     */
    void formatSQLInParamsToInSQLCondition(QString &sql, QVariantMap &params, const QStringList &strList, const QString &indicate);
};

#endif // STRINGUTIL_H
