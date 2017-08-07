#ifndef NODERRECUNSTRUCTTASKSTATUSREQUEST_H
#define NODERRECUNSTRUCTTASKSTATUSREQUEST_H
#include "base.h"
#include "action.h"
#include "unstructiclient_global.h"
#include "dao/nsunstructdao.h"

class UNSTRUCTICLIENTSHARED_EXPORT NoderRecUnstructTaskStatusRequest : public AbstractRequest
{
public:
    NoderRecUnstructTaskStatusRequest();
    ~NoderRecUnstructTaskStatusRequest();
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
    static RespUnstructFilesDownloadStatus* CallbackByRespUnstructTask(RespUnstructFilesDownloadStatus *unstructEntity = 0);
private:
    //报文体对象
    RespUnstructFilesDownloadStatus *gramEntity;
    static QMutex *mutex;
};

#endif // NODERRECUNSTRUCTTASKSTATUSREQUEST_H
