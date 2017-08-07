#ifndef REQREMOTEUIOPERACENTORCONN_H
#define REQREMOTEUIOPERACENTORCONN_H

#include "transmsglib_global.h"
#include "basicinfo.h"
#include "core/serializable.h"
#include "core/validation.h"
#include "core/messageinfo.h"

class TRANSMSGLIBSHARED_EXPORT ReqRemoteUIOperaCentorConn : public BasicInfo, public Validation, public MessageInfo
{
public:
    ReqRemoteUIOperaCentorConn();
    ~ReqRemoteUIOperaCentorConn();
public:
    void toXML(QXmlStreamWriter *writer = 0);
    void toEntity(QXmlStreamReader *reader = 0);
protected:
    void validate(TransException &tsExcep);
    quint8 messageType() const;
};

#endif // REQREMOTEUIOPERACENTORCONN_H
