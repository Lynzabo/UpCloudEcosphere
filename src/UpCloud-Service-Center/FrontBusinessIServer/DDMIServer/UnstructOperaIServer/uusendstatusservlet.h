#ifndef UPDATEUNSTRUCTSENDSTATUSSERVLET_H
#define UPDATEUNSTRUCTSENDSTATUSSERVLET_H
#include <QtCore>
#include "unstructoperaiserver_global.h"
#include "base.h"
#include "duplex.h"
#include "avro.h"

class UNSTRUCTOPERAISERVERSHARED_EXPORT UpdateUnstructSendStatusServlet : public AbstractServlet
{
public:
    UpdateUnstructSendStatusServlet();
protected:
    /**
     * @brief doExec 处理请求
     * @param req   请求传递数据
     * @param resp  响应传递参数
     * 到达顺序2
     */
    virtual void doExec(DRequestContext *request = 0,DResponseContext *response = 0);
};

#endif // UPDATEUNSTRUCTSENDSTATUSSERVLET_H
