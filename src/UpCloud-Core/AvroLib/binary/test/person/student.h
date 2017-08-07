#ifndef STUDENT_H
#define STUDENT_H
#include "person.h"

class Student:public Person
{
public:
    Student();

    /**
     * @brief toDataStream  转换对象为数据流
     * @param in
     */
    virtual QByteArray &toDataStream();
    /**
     * @brief fromDataStream    转换数据流为对象
     * @param out
     */
    virtual void fromDataStream(const QByteArray &out);
    QChar getSex() const;
    void setSex(const QChar &value);

private:
    QChar sex;
};

#endif // STUDENT_H
