#ifndef VCSRUNSTRUCTSENDFILES_H
#define VCSRUNSTRUCTSENDFILES_H
#include "csrusendfiles.h"

class VCsRUnstructSendFiles : public CsRUnstructSendFiles
{
public:
    VCsRUnstructSendFiles();

    quint8 getState() const;
    void setState(const quint8 &value);


private:
    quint8 state;
};

#endif // VCSRUNSTRUCTSENDFILES_H
