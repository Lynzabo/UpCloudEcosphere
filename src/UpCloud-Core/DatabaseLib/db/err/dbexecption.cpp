#include "dbexecption.h"
#include "base.h"
DBException::DBException():type(QSqlError::ErrorType::NoError),text("")
{

}
QSqlError::ErrorType DBException::getType() const
{
    return type;
}

void DBException::setType(const QSqlError::ErrorType &value)
{
    type = value;
}
QString DBException::getText() const
{
    return text;
}

void DBException::setText(const QString &value)
{
    text = value;
}

QString DBException::getTypeDesc() const
{
    QString typeStr;
    switch (type) {
    case QSqlError::NoError:
        typeStr = trs("没有错误");
        break;
    case QSqlError::ConnectionError:
        typeStr = trs("数据库的连接出错");
        break;
    case QSqlError::StatementError:
        typeStr = trs("SQL声明出错");
        break;
    case QSqlError::TransactionError:
        typeStr = trs("操作事务出错");
        break;
    case QSqlError::UnknownError:
        typeStr = trs("未知错误");
        break;
    default:
        break;
    }
    return typeStr;
}





