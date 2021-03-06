#ifndef ADDSTRUCTSENDFILESERVLET_H
#define ADDSTRUCTSENDFILESERVLET_H
#include <QtCore>
#include "avro.h"
#include "base.h"
#include "duplex.h"
#include "structoperaiserver_global.h"

class STRUCTOPERAISERVERSHARED_EXPORT AddStructSendFileServlet : public AbstractServlet
{
public:
    AddStructSendFileServlet();
protected:
    /**
     * @brief doExec 处理请求
     * @param req   请求传递数据
     * @param resp  响应传递参数
     * 到达顺序2
     */
    virtual void doExec(DRequestContext *request, DResponseContext *response);
};

#endif // ADDSTRUCTSENDFILESERVLET_H
