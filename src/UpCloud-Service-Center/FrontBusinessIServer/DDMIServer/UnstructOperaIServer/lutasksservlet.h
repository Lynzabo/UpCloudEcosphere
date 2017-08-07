#ifndef LISTUNSTRUCTTASKSSERVLET_H
#define LISTUNSTRUCTTASKSSERVLET_H
#include <QtCore>
#include "unstructoperaiserver_global.h"
#include "duplex.h"
#include "erm.h"
#include "../../../BusinessIServer/UnstructIServer/bean/csrusendaddr.h"
class UNSTRUCTOPERAISERVERSHARED_EXPORT ListUnstructTasksServlet : public AbstractServlet
{
public:
    ListUnstructTasksServlet();
    ~ListUnstructTasksServlet();
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
    virtual void doExec(DRequestContext *request = 0,DResponseContext *response = 0);
private:
    Page *page;
};

#endif // LISTUNSTRUCTTASKSSERVLET_H
