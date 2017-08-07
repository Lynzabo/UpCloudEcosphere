#ifndef PERSON_H
#define PERSON_H
#include <QtCore>

class Person
{
public:
    Person();
    QString getMyTitle() const;
    void setMyTitle(const QString &value);

    QString getMyArtist() const;
    void setMyArtist(const QString &value);

    int getMyYear() const;
    void setMyYear(int value);

private:
    QString myTitle;
    QString myArtist;
    int myYear;

};

#endif // PERSON_H
