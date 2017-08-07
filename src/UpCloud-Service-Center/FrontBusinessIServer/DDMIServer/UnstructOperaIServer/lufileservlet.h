#ifndef LISTUNSTRUCTFILESERVLET_H
#define LISTUNSTRUCTFILESERVLET_H
#include <QtCore>
#include "unstructoperaiserver_global.h"
#include "duplex.h"
#include "erm.h"

class UNSTRUCTOPERAISERVERSHARED_EXPORT ListUnstructFileServlet : public AbstractServlet
{
public:
    ListUnstructFileServlet();
   ~ListUnstructFileServlet();
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
    virtual void doExec(DRequestContext *request = 0,DResponseContext *response = 0);
private:
    Page* page;
};

#endif // LISTUNSTRUCTFILESERVLET_H
