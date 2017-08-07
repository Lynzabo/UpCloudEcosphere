#ifndef NODEREQUESTBRIDGECONN_H
#define NODEREQUESTBRIDGECONN_H

#include "base.h"
#include "timer.h"
#include "transmsg.h"

#include "bridgeiclient_global.h"

class BRIDGEICLIENTSHARED_EXPORT NodeRequestBridgeConn
{
public:
    NodeRequestBridgeConn();
    /**
     * @brief requestBridgeConn 请求建立长连接
     */
    void requestBridgeConn(QString& pubKeyFileName);
private:
    QString m_pubKey;
    QString m_priKey;
    QString m_MACAddr;
    ReqBridgeConn* m_reqBridgeConn;
};

#endif // NODEREQUESTBRIDGECONN_H
