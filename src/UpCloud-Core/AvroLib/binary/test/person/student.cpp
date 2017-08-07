#include "student.h"

Student::Student()
{
}

void Student::fromDataStream(const QByteArray &out)
{
    Person::fromDataStream(out);
    uBIOOutputStream >> sex;
}
QChar Student::getSex() const
{
    return sex;
}

void Student::setSex(const QChar &value)
{
    sex = value;
}


QByteArray &Student::toDataStream()
{
    Person::toDataStream();
    uBIOInputStream << sex;
    return Binary::toDataStream();
}


