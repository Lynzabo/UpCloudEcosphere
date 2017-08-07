#ifndef LISTSTRUCTTASKSERVLET_H
#define LISTSTRUCTTASKSERVLET_H
#include <QtCore>
#include "avro.h"
#include "erm.h"
#include "base.h"
#include "duplex.h"
#include "structoperaiserver_global.h"

class STRUCTOPERAISERVERSHARED_EXPORT ListStructTaskServlet : public AbstractServlet
{
public:
    ListStructTaskServlet();
    ~ListStructTaskServlet();
protected:
    /**
     * @brief doInit    当请求到来时候
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
    Page *page;
};

#endif // LISTSTRUCTTASKSERVLET_H
