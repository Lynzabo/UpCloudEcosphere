#ifndef VCSASCSENDFILES_H
#define VCSASCSENDFILES_H
#include <QtCore>
#include "csrscsendfiles.h"

class VCsAScSendFiles : public CsRScheduleSendFiles
{
public:
    VCsAScSendFiles();
    quint8 getState() const;
    void setState(const quint8 &value);

    QString getErrMsg() const;
    void setErrMsg(const QString &value);

private:
    quint8 state;
    QString errMsg;
};

#endif // VCSASCSENDFILES_H
