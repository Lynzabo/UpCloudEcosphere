#ifndef HEARTTHROBSERVERREQUEST_H
#define HEARTTHROBSERVERREQUEST_H
#include "base.h"
#include "action.h"
#include "transmsg.h"

#include "hthrobsiserver_global.h"

class HTHROBSISERVERSHARED_EXPORT HeartthrobServerRequest : public AbstractRequest
{
public:
    HeartthrobServerRequest();
    ~HeartthrobServerRequest();
protected:
    /**
     * @brief doRequest 获取请求
     * @param req   请求传递数据
     * @param resp  响应传递参数
     * 到达顺序3
     */
    void doRequest(RequestContext *request = 0,ResponseContext *response = 0);
public:
    /**
     * @brief CallbackByReqUnstructTask 解析报文体回调
     * @param unstructEntity
     */
    static ReqHeartthrobsConn *CallbackByHeartthrobsConn(ReqHeartthrobsConn *unstructEntity = 0);
private:
    //报文体对象
    ReqHeartthrobsConn *gramEntity;
    static QMutex *mutex;
};

#endif // HEARTTHROBSERVERREQUEST_H
