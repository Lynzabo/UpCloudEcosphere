#ifndef VCSRUNSTRUCTSENDADDR_H
#define VCSRUNSTRUCTSENDADDR_H
#include "csrusendaddr.h"

class VCsRUnstructSendAddr : public CsRUnstructSendAddr
{
public:
    VCsRUnstructSendAddr();
    quint8 getState() const;
    void setState(const quint8 &value);

    QString getDescritpion() const;
    void setDescritpion(const QString &value);


private:
    quint8 state;
    QString descritpion;
};

#endif // VCSRUNSTRUCTSENDADDR_H
