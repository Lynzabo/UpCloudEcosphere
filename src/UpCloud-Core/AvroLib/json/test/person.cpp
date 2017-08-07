#include "person.h"

Person::Person()
{

}
QString Person::getMyTitle() const
{
    return myTitle;
}

void Person::setMyTitle(const QString &value)
{
    myTitle = value;
}
QString Person::getMyArtist() const
{
    return myArtist;
}

void Person::setMyArtist(const QString &value)
{
    myArtist = value;
}
int Person::getMyYear() const
{
    return myYear;
}

void Person::setMyYear(int value)
{
    myYear = value;
}




