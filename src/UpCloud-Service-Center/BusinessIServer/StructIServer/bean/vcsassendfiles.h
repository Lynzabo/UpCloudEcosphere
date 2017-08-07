#ifndef VCSASSENDFILES_H
#define VCSASSENDFILES_H

#include <QtCore>
#include "csrssendfiles.h"

class VCsRStructSendFiles : public  CsRStructSendFiles
{
public:
    VCsRStructSendFiles();

    quint8 getState() const;
    void setState(const quint8 &value);
private:
    quint8 state;
};

#endif // VCSASSENDFILES_H
