#ifndef NODERRECSTRUCTTASKPARSESTATUSREQUEST_H
#define NODERRECSTRUCTTASKPARSESTATUSREQUEST_H


#include "action.h"
#include "structiclient_global.h"
#include "dao/nsstructdao.h"

class STRUCTICLIENTSHARED_EXPORT NoderRecStructTaskParseStatusRequest : public AbstractRequest
{
public:
    NoderRecStructTaskParseStatusRequest();
    ~NoderRecStructTaskParseStatusRequest();
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
     * @brief CallbackByRespStructTask 解析报文体回调
     * @param structEntity
     */
    static RespStructTaskExecStatus *CallbackByRespStructTask(RespStructTaskExecStatus *structEntity = 0);
private:
    //接受报文体对象
    RespStructTaskExecStatus *gramEntity;
};

#endif // NODERRECSTRUCTTASKPARSESTATUSREQUEST_H
