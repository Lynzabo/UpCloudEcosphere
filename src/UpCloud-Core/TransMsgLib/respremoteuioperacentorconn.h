#ifndef RESPREMOTEUIOPERACENTORCONN_H
#define RESPREMOTEUIOPERACENTORCONN_H

#include "transmsglib_global.h"
#include "replyinfo.h"
#include "core/serializable.h"
#include "core/validation.h"
#include "core/messageinfo.h"

class TRANSMSGLIBSHARED_EXPORT RespRemoteUIOperaCentorConn : public ReplyInfo, public Validation, public MessageInfo
{
public:
    RespRemoteUIOperaCentorConn();
    ~RespRemoteUIOperaCentorConn();
public:
    void toXML(QXmlStreamWriter *writer = 0);
    void toEntity(QXmlStreamReader *reader = 0);
protected:
    void validate(TransException &tsExcep);
    quint8 messageType() const;
};

#endif // RESPREMOTEUIOPERACENTORCONN_H
