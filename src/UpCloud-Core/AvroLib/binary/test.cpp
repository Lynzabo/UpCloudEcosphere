/*#include <QCoreApplication>
#include "test/person/person.h"
#include "test/person/student.h"
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    Person person1,person2;
    person1.setMyYear(111);
    person1.setMyTitle(QString("aa"));
    person1.setMyArtist(QString("dsfffds"));
    QByteArray out = person1.toDataStream();
    qDebug() << out.size();
    person2.fromDataStream(out);
    qDebug() << person2.getMyArtist() << ":" << person2.getMyTitle() << ":" << person2.getMyYear();

    Student stu1,stu2;
    stu1.setSex(QChar(1));
    stu1.setMyYear(222);
    stu1.setMyTitle(QString("vv"));
    stu1.setMyArtist(QString("dsds"));
    QByteArray out1 = stu1.toDataStream();
    qDebug() << out1.size();
    stu2.fromDataStream(out1);
    qDebug() << stu2.getMyArtist() << ":" << stu2.getMyTitle() << ":" << stu2.getMyYear() << stu2.getSex();
    return a.exec();
}
*/
