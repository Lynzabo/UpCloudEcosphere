#ifndef NODERRECSCHEDULETASKPARSESTATUSREQUEST_H
#define NODERRECSCHEDULETASKPARSESTATUSREQUEST_H

#include "base.h"
#include "action.h"
#include "scheduleiclient_global.h"
#include "dao/nsscheduledao.h"

class SCHEDULEICLIENTSHARED_EXPORT NoderRecScheduleTaskParseStatusRequest : public AbstractRequest
{
public:
    NoderRecScheduleTaskParseStatusRequest();
    ~NoderRecScheduleTaskParseStatusRequest();
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
     * @brief CallbackByRespScheduleTask 解析报文体回调
     * @param scheduleEntity
     */
    static RespScheduleTaskExecStatus *CallbackByRespScheduleTask(RespScheduleTaskExecStatus *scheduleEntity = 0);
private:
    //接受报文体对象
    RespScheduleTaskExecStatus *gramEntity;
    static QMutex *mutex;
};

#endif // NODERRECSCHEDULETASKPARSESTATUSREQUEST_H
