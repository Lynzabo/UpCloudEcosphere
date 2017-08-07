#ifndef TRANSEXCEPTION_H
#define TRANSEXCEPTION_H
#include <QtCore>
#include "transmsglib_global.h"
class TRANSMSGLIBSHARED_EXPORT TransException
{
public:
    TransException();
    quint8 getType() const;
    void setType(const quint8 &value);

    QString getText() const;
    void setText(const QString &value);

private:
    //异常类型
    quint8 type;
    //异常信息
    QString text;
};

#endif // TRANSEXCEPTION_H
