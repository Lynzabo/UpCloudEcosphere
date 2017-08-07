#ifndef REQREMOTEUIOPERACENTORINFO_H
#define REQREMOTEUIOPERACENTORINFO_H

#include "transmsglib_global.h"
#include "remoteoperabaseinfo.h"
#include "core/serializable.h"
#include "core/validation.h"
#include "core/messageinfo.h"

class TRANSMSGLIBSHARED_EXPORT ReqRemoteUIOperaCentorInfo : public RemoteOperaBaseInfo, public Validation, public MessageInfo
{
public:
    ReqRemoteUIOperaCentorInfo();
    ~ReqRemoteUIOperaCentorInfo();
public:
    void toXML(QXmlStreamWriter *writer = 0);
    void toEntity(QXmlStreamReader *reader = 0);
protected:
    void validate(TransException &tsExcep);
    quint8 messageType() const;
};

#endif // REQREMOTEUIOPERACENTORINFO_H
