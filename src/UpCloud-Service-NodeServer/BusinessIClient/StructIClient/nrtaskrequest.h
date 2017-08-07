#ifndef NODERRECSTRUCTTASKREQUEST_H
#define NODERRECSTRUCTTASKREQUEST_H

#include "action.h"
#include "structiclient_global.h"
#include "dao/nsstructdao.h"

class STRUCTICLIENTSHARED_EXPORT NoderRecStructTaskRequest : public AbstractRequest
{
public:
    NoderRecStructTaskRequest();
    ~NoderRecStructTaskRequest();
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
    static ReqStructFilesDownloadInfo *CallbackByReqStructTask(ReqStructFilesDownloadInfo *structEntity = 0);
private:
    //接受报文体对象
    ReqStructFilesDownloadInfo *gramEntity;
    static QMutex *mutex;
};

#endif // NODERRECSTRUCTTASKREQUEST_H
