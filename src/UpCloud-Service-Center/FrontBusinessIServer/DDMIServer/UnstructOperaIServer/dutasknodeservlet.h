#ifndef DELUNSTRUCTTASKNODESERVLET_H
#define DELUNSTRUCTTASKNODESERVLET_H
#include <QtCore>
#include "unstructoperaiserver_global.h"
#include "base.h"
#include "duplex.h"
#include "avro.h"


class UNSTRUCTOPERAISERVERSHARED_EXPORT DelUnstructTaskNodeServlet : public AbstractServlet
{
public:
    DelUnstructTaskNodeServlet();
protected:
    /**
     * @brief doExec 删除任务节点服务器
     * @param request
     * @param response
     */
    virtual void doExec(DRequestContext *request, DResponseContext *response);
};

#endif // DELUNSTRUCTTASKNODESERVLET_H
