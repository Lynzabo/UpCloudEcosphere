#ifndef NODERRECUNSTRUCTTASKREQUEST_H
#define NODERRECUNSTRUCTTASKREQUEST_H
#include "base.h"
#include "action.h"
#include "unstructiclient_global.h"
#include "bean/nsrutask.h"
#include "bean/nsrusendfiles.h"
#include "dao/nsunstructdao.h"

class UNSTRUCTICLIENTSHARED_EXPORT NoderRecUnstructTaskRequest : public AbstractRequest
{
public:
    NoderRecUnstructTaskRequest();
    ~NoderRecUnstructTaskRequest();
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
    static ReqUnstructFilesDownloadInfo *CallbackByReqUnstructTask(ReqUnstructFilesDownloadInfo *unstructEntity = 0);
private:
    //报文体对象
    ReqUnstructFilesDownloadInfo *gramEntity;
};

#endif // NODERRECUNSTRUCTTASKREQUEST_H
