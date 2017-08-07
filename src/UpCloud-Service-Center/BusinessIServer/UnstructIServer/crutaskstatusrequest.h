#ifndef CENTERRECUNSTRUCTTASKSTATUSREQUEST_H
#define CENTERRECUNSTRUCTTASKSTATUSREQUEST_H

#include "base.h"
#include "db.h"
#include "timer.h"
#include "transmsg.h"
#include "action.h"
#include "unstructiserver_global.h"
#include "bean/csrutask.h"
#include "bean/csrusendaddr.h"
#include "bean/csrusendfiles.h"
#include "dao/csunstructdao.h"
class UNSTRUCTISERVERSHARED_EXPORT CenterRecUnstructTaskStatusRequest : public AbstractRequest
{
public:
    CenterRecUnstructTaskStatusRequest();
    ~CenterRecUnstructTaskStatusRequest();
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
     * @brief CallbackByRespUnstructTask 解析报文体回调
     * @param unstructEntity
     */
    static ReqUnstructFilesDownloadStatus* CallbackByRespUnstructTask(ReqUnstructFilesDownloadStatus *unstructEntity = 0);
private:
    //接受报文体对象
    ReqUnstructFilesDownloadStatus *gramEntity;
};

#endif // CENTERRECUNSTRUCTTASKSTATUSREQUEST_H
