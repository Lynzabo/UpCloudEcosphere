#ifndef VCSRSTRUCTSENDADDR_H
#define VCSRSTRUCTSENDADDR_H
#include "csrssendaddr.h"

class VCsRStructSendAddr : public CsRStructSendAddr
{
public:
    VCsRStructSendAddr();
    quint8 getState() const;
    void setState(const quint8 &value);

    QString getDescription() const;
    void setDescription(const QString &value);

private:
    //依策略取状态
    quint8 state;
    //节点服务器备注信息
    QString description;
};

#endif // VCSRSTRUCTSENDADDR_H
