#ifndef ADDDICTSERVLET_H
#define ADDDICTSERVLET_H
#include <QtCore>
#include "base.h"
#include "duplex.h"
#include "basaloperaiserver_global.h"
#include "avro.h"

class BASALOPERAISERVERSHARED_EXPORT AddDictServlet : public AbstractServlet
{
public:
    AddDictServlet();
protected:
    /**
     * @brief doExec 处理请求
     * @param req   请求传递数据
     * @param resp  响应传递参数
     * 到达顺序2
     */
    virtual void doExec(DRequestContext *request, DResponseContext *response);
};

#endif // ADDDICTSERVLET_H
