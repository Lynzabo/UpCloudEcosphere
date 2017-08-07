#ifndef REQHEARTTHROBSCONN_H
#define REQHEARTTHROBSCONN_H

#include "transmsglib_global.h"
#include "basicinfo.h"
#include "core/serializable.h"
#include "core/validation.h"
#include "core/messageinfo.h"

class TRANSMSGLIBSHARED_EXPORT ReqHeartthrobsConn : public BasicInfo, public Validation, public MessageInfo
{
public:
    ReqHeartthrobsConn();
    ~ReqHeartthrobsConn();
public:
    void toXML(QXmlStreamWriter *writer = 0);
    void toEntity(QXmlStreamReader *reader = 0);
protected:
    void validate(TransException &tsExcep);
    quint8 messageType() const;
};
#endif // REQHEARTTHROBSCONN_H
