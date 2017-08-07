#ifndef DELUNSTRUCTTASKFILESEVLET_H
#define DELUNSTRUCTTASKFILESEVLET_H
#include <QtCore>
#include "unstructoperaiserver_global.h"
#include "duplex.h"

class UNSTRUCTOPERAISERVERSHARED_EXPORT DelUnstructTaskFileServlet : public AbstractServlet
{
public:
    DelUnstructTaskFileServlet();
protected:
    /**
     * @brief doExec 处理请求
     * @param req   请求传递数据
     * @param resp  响应传递参数
     * 到达顺序2
     */
    virtual void doExec(DRequestContext *request = 0,DResponseContext *response = 0);
};

#endif // DELUNSTRUCTTASKFILESEVLET_H
