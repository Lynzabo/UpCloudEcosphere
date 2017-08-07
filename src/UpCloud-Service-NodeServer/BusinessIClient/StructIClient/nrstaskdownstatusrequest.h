#ifndef NODERRECSTRUCTTASKDOWNSTATUSREQUEST_H
#define NODERRECSTRUCTTASKDOWNSTATUSREQUEST_H

#include "base.h"
#include "action.h"
#include "structiclient_global.h"
#include "dao/nsstructdao.h"

class STRUCTICLIENTSHARED_EXPORT NoderRecStructTaskDownStatusRequest : public AbstractRequest
{
public:
    NoderRecStructTaskDownStatusRequest();
    ~NoderRecStructTaskDownStatusRequest();
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
    static RespStructFilesDownloadStatus *CallbackByRespStructTask(RespStructFilesDownloadStatus *structEntity = 0);
private:
    //报文体对象
    RespStructFilesDownloadStatus *gramEntity;
};

#endif // NODERRECSTRUCTTASKDOWNSTATUSREQUEST_H
