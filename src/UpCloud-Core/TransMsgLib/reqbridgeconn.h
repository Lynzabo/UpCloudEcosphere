#ifndef REQBRIDGECONN_H
#define REQBRIDGECONN_H

#include "transmsglib_global.h"
#include "basicinfo.h"
#include "core/serializable.h"
#include "core/validation.h"
#include "core/messageinfo.h"

class TRANSMSGLIBSHARED_EXPORT ReqBridgeConn : public BasicInfo, public Validation, public MessageInfo
{
public:
    ReqBridgeConn();
    ~ReqBridgeConn();
public:
    void toXML(QXmlStreamWriter *writer = 0);
    void toEntity(QXmlStreamReader *reader = 0);
protected:
    void validate(TransException &tsExcep);
    quint8 messageType() const;
public:
    //节点公钥码
    QString PubKey;
    //节点私钥码
    QString PriKey;
    //MAC地址
    QString MacAddr;
};
#endif // REQBRIDGECONN_H
