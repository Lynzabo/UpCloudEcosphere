#ifndef DTASKADDR_H
#define DTASKADDR_H

#include <QtCore>

class DTaskAddr
{
public:
    DTaskAddr();

    QString getAddrUUID() const;
    void setAddrUUID(const QString &value);

    bool getIsGroup() const;
    void setIsGroup(bool value);

private:
    QString addrUUID;
    bool isGroup;
};

#endif // DTASKADDR_H
