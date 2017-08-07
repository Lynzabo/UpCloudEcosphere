#ifndef CENTERREMOTEUIOPERAINTERCEPTOR_H
#define CENTERREMOTEUIOPERAINTERCEPTOR_H
#include "base.h"
#include "action.h"
#include "operaiserver_global.h"
#include "duplex.h"
/**
 * @brief The CenterRemoteUIOperaInterceptor class  远程UI请求拦截器
 */
class OPERAISERVERSHARED_EXPORT CenterRemoteUIOperaInterceptor : public AbstractRequest
{
public:
    CenterRemoteUIOperaInterceptor();
    ~CenterRemoteUIOperaInterceptor();
protected:
    /**
     * @brief doRequest 获取请求
     * @param req   请求传递数据
     * @param resp  响应传递参数
     * 到达顺序3
     */
    void doRequest(RequestContext *request = 0, ResponseContext *response = 0);
public:
    /**
     * @brief CallbackByRespStructTask 解析报文体回调
     * @param structEntity
     */
    static ReqRemoteUIOperaCentorInfo* CallbackByReqRemoteUIOperaCenterInfo(ReqRemoteUIOperaCentorInfo *operaEntity = 0);
private:
    //接收报文体对象
    ReqRemoteUIOperaCentorInfo *gramEntity;
    static QMutex *mutex;
};

#endif // CENTERREMOTEUIOPERAINTERCEPTOR_H
