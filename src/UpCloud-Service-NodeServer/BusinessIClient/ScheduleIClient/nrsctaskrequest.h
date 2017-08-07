#ifndef NODERRECSCHEDULETASKREQUEST_H
#define NODERRECSCHEDULETASKREQUEST_H

#include "action.h"
#include "scheduleiclient_global.h"
#include "dao/nsscheduledao.h"

class SCHEDULEICLIENTSHARED_EXPORT NoderRecScheduleTaskRequest : public AbstractRequest
{
public:
    NoderRecScheduleTaskRequest();
    ~NoderRecScheduleTaskRequest();
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
     * @brief CallbackByReqStructTask 解析报文体回调
     * @param structEntity
     */
    static ReqScheduleTaskDownloadInfo *CallbackByReqScheduleTask(ReqScheduleTaskDownloadInfo *scheduleEntity = 0);
private:
    //接受报文体对象
    ReqScheduleTaskDownloadInfo *gramEntity;
    static QMutex *mutex;
};

#endif // NODERRECSCHEDULETASKREQUEST_H
