#ifndef LISTSTRUCTSENDSTATUSSERVLET_H
#define LISTSTRUCTSENDSTATUSSERVLET_H
#include <QtCore>
#include "avro.h"
#include "base.h"
#include "erm.h"
#include "duplex.h"
#include "structoperaiserver_global.h"

class STRUCTOPERAISERVERSHARED_EXPORT ListStructSendStatusServlet : public AbstractServlet
{
public:
    ListStructSendStatusServlet();
    ~ListStructSendStatusServlet();
protected:
    /**
     * @brief doInit    当请求到来时候,比如在这里可以打开数据库连接
     * 到达顺序1
     */
    void doInit();
    /**
     * @brief doExec 处理请求
     * @param req   请求传递数据
     * @param resp  响应传递参数
     * 到达顺序2
     */
    virtual void doExec(DRequestContext *request, DResponseContext *response);
private:
    Page* page;
};

#endif // LISTSTRUCTSENDSTATUSSERVLET_H
