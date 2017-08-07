#ifndef ABSTRACTSERVLET_H
#define ABSTRACTSERVLET_H
#include "duplexlib_global.h"
#include "server/servlet/core/servlet.h"


class DUPLEXLIBSHARED_EXPORT AbstractServlet : public Servlet
{
public:
    AbstractServlet();
public:
    /**
     * @brief doInit    当请求到来时候,比如在这里可以打开数据库连接
     * 到达顺序1
     */
    virtual void doInit();
    /**
     * @brief doExec 处理请求
     * @param req   请求传递数据
     * @param resp  响应传递参数
     * 到达顺序2
     */
    virtual void doExec(DRequestContext *request = 0,DResponseContext *response = 0);
    /**
     * @brief doDestory 销毁,在进析构前会先进这个接口,比如在这里可以关闭数据库连接
     * 到达顺序3
     */
    virtual void doDestory();
};

#endif // ABSTRACTSERVLET_H
