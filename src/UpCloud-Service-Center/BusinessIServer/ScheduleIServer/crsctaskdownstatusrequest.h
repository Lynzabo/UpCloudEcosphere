#ifndef CENTERRECSCHEDULETASKDOWNSTATUSREQUEST_H
#define CENTERRECSCHEDULETASKDOWNSTATUSREQUEST_H

#include "base.h"
#include "db.h"
#include "timer.h"
#include "transmsg.h"
#include "action.h"
#include "scheduleiserver_global.h"
#include "dao/csscheduledao.h"

class SCHEDULEISERVERSHARED_EXPORT CenterRecScheduleTaskDownStatusRequest : public AbstractRequest
{
public:
    CenterRecScheduleTaskDownStatusRequest();
    ~CenterRecScheduleTaskDownStatusRequest();
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
    static ReqScheduleTaskDownloadStatus* CallbackByRespScheduleTask(ReqScheduleTaskDownloadStatus *scheduleEntity = 0);
private:
    //接收报文体对象
    ReqScheduleTaskDownloadStatus *gramEntity;
    static QMutex *mutex;
};

#endif // CENTERRECSCHEDULETASKDOWNSTATUSREQUEST_H
