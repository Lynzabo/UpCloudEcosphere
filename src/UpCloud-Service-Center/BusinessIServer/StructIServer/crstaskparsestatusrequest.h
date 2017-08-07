#ifndef CENTERRECSTRUCTTASKPARSESTATUSREQUEST_H
#define CENTERRECSTRUCTTASKPARSESTATUSREQUEST_H

#include "base.h"
#include "db.h"
#include "timer.h"
#include "transmsg.h"
#include "action.h"
#include "structiserver_global.h"
#include "dao/csstructdao.h"

class STRUCTISERVERSHARED_EXPORT CenterRecStructTaskParseStatusRequest : public AbstractRequest
{
public:
    CenterRecStructTaskParseStatusRequest();
    ~CenterRecStructTaskParseStatusRequest();
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
    static ReqStructTaskExecStatus* CallbackByRespStructTask(ReqStructTaskExecStatus *structEntity = 0);
private:
    //接收报文体对象
    ReqStructTaskExecStatus *gramEntity;
};

#endif // CENTERRECSTRUCTTASKPARSESTATUSREQUEST_H
