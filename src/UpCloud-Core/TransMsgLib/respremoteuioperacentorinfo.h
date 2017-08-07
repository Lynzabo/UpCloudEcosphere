#ifndef RESPREMOTEUIOPERACENTORINFO_H
#define RESPREMOTEUIOPERACENTORINFO_H

#include "transmsglib_global.h"
#include "remoteoperabaseinfo.h"
#include "core/serializable.h"
#include "core/validation.h"
#include "core/messageinfo.h"

class TRANSMSGLIBSHARED_EXPORT RespRemoteUIOperaCentorInfo : public RemoteOperaBaseInfo, public Validation, public MessageInfo
{
public:
    RespRemoteUIOperaCentorInfo();
    ~RespRemoteUIOperaCentorInfo();
public:
    void toXML(QXmlStreamWriter *writer = 0);
    void toEntity(QXmlStreamReader *reader = 0);
protected:
    void validate(TransException &tsExcep);
    quint8 messageType() const;
public:
    //状态码
    quint8 State;
    //返回内容
    QString Content;
};

#endif // RESPREMOTEUIOPERACENTORINFO_H
