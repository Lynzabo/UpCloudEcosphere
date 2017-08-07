#ifndef ASTASKSERVLET_H
#define ASTASKSERVLET_H
#include <QtCore>
#include "structoperaiserver_global.h"
#include "base.h"
#include "duplex.h"
#include "avro.h"

class STRUCTOPERAISERVERSHARED_EXPORT AddStructTaskServlet : public AbstractServlet
{
public:
    AddStructTaskServlet();
protected:
    /**
     * @brief doExec 处理请求
     * @param req   请求传递数据
     * @param resp  响应传递参数
     * 到达顺序2
     */
    virtual void doExec(DRequestContext *request = 0,DResponseContext *response = 0);
};
#endif // ASTASKSERVLET_H
