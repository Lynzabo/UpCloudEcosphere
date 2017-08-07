#ifndef PERSON_H
#define PERSON_H
#include "binary/binary.h"

class Person : public Binary
{
public:
    Person();
    QString getMyTitle() const;
    void setMyTitle(const QString &value);

    QString getMyArtist() const;
    void setMyArtist(const QString &value);

    int getMyYear() const;
    void setMyYear(int value);

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
private:
    QString myTitle;
    QString myArtist;
    int myYear;
};

#endif // PERSON_H
