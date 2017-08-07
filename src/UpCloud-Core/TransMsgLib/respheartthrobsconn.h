#ifndef RESPHEARTTHROBSCONN_H
#define RESPHEARTTHROBSCONN_H

#include "transmsglib_global.h"
#include "replyinfo.h"
#include "core/serializable.h"
#include "core/validation.h"
#include "core/messageinfo.h"

class  TRANSMSGLIBSHARED_EXPORT RespHeartthrobsConn : public ReplyInfo, public Validation, public MessageInfo
{
public:
    RespHeartthrobsConn();
    ~RespHeartthrobsConn();
public:
    void toXML(QXmlStreamWriter *writer = 0);
    void toEntity(QXmlStreamReader *reader = 0);
protected:
    void validate(TransException &tsExcep);
    quint8 messageType() const;
};

#endif // RESPHEARTTHROBSCONN_H
