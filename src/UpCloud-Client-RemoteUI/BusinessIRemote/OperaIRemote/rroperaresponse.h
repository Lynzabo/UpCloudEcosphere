#ifndef REMOTERRECOPERARESPONSE_H
#define REMOTERRECOPERARESPONSE_H
#include "action.h"
#include "baseiremote.h"
#include "operairemote_global.h"

class OPERAIREMOTESHARED_EXPORT RemoterRecOperaResponse : public AbstractRequest
{
public:
    RemoterRecOperaResponse();
    ~RemoterRecOperaResponse();
protected:
    /**
     * @brief doRequest 获取请求
     * @param req   请求传递数据
     * @param resp  响应传递参数
     * 到达顺序3
     */
    virtual void doRequest(RequestContext *request = 0,ResponseContext *response = 0);
public:
    /**
     * @brief CallbackByRespStructTask 解析报文体回调
     * @param structEntity
     */
    static RespRemoteUIOperaCentorInfo *CallbackByRespOpera(RespRemoteUIOperaCentorInfo *operaRespEntity = 0);
private:
    //报文体对象
    RespRemoteUIOperaCentorInfo *gramEntity;
    static QMutex *mutex;
};

#endif // REMOTERRECOPERARESPONSE_H
