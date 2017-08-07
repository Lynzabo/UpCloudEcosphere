#include "person.h"

Person::Person()
{

}

QByteArray &Person::toDataStream()
{
    uBIOInputStream << myTitle << myArtist << qint32(myYear);
    return Binary::toDataStream();
}

void Person::fromDataStream(const QByteArray &out)
{
    Binary::fromDataStream(out);
    QString title,article;
    qint32 year;
    uBIOOutputStream >> title >> article >> year;
    myTitle = title;
    myArtist = article;
    myYear = year;
}
int Person::getMyYear() const
{
    return myYear;
}

void Person::setMyYear(int value)
{
    myYear = value;
}

QString Person::getMyArtist() const
{
    return myArtist;
}

void Person::setMyArtist(const QString &value)
{
    myArtist = value;
}

QString Person::getMyTitle() const
{
    return myTitle;
}

void Person::setMyTitle(const QString &value)
{
    myTitle = value;
}


