#ifndef JSONEXCEPTION_H
#define JSONEXCEPTION_H
#include <QtCore>

class JsonException
{
public:
    JsonException(const QString &_msg);
    /**
     * @brief getMsg    打印异常信息
     * @return
     */
    QString getMsg() const;
private:
    //异常内容
    QString msg;
};

#endif // JSONEXCEPTION_H
