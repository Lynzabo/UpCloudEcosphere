#ifndef DBEXCEPTION_H
#define DBEXCEPTION_H

#include <QtCore>
#include <QSqlError>
#include "databaselib_global.h"
class DATABASELIBSHARED_EXPORT DBException
{
public:
    DBException();
    /**
     * @brief getType   输出异常类型
     * @return
     */
    QSqlError::ErrorType getType() const;
    /**
     * @brief setType   输入异常类型
     * @param value
     */
    void setType(const QSqlError::ErrorType &value=QSqlError::ErrorType::NoError);
    /**
     * @brief getText   输出异常内容
     * @return
     */
    QString getText() const;
    /**
     * @brief setText   输入异常内容
     * @param value
     */
    void setText(const QString &value="");

    QString getTypeDesc() const;

private:
    //异常类型,5种case
    QSqlError::ErrorType type;
    //异常信息
    QString text;
    //异常类型描述
    QString typeDesc;
};

#endif // DBEXCEPTION_H
