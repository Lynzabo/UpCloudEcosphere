#ifndef RESPBRIDGECONN_H
#define RESPBRIDGECONN_H

#include "transmsglib_global.h"
#include "replyinfo.h"
#include "core/serializable.h"
#include "core/validation.h"
#include "core/messageinfo.h"

class TRANSMSGLIBSHARED_EXPORT RespBridgeConn : public ReplyInfo, public Validation, public MessageInfo
{
public:
    RespBridgeConn();
    ~RespBridgeConn();
public:
    void toXML(QXmlStreamWriter *writer = 0);
    void toEntity(QXmlStreamReader *reader = 0);
protected:
    void validate(TransException &tsExcep);
    quint8 messageType() const;
public:
    //中心公钥码
    quint32 PubKey;
};
#endif // RESPBRIDGECONN_H
