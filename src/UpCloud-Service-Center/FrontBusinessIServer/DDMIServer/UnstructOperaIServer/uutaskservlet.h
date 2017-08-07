#ifndef UPDATEUNSTRUCTTASKSERVLET_H
#define UPDATEUNSTRUCTTASKSERVLET_H
#include <QtCore>
#include "unstructoperaiserver_global.h"
#include "base.h"
#include "duplex.h"
#include "avro.h"

class UNSTRUCTOPERAISERVERSHARED_EXPORT UpdateUnstructTaskServlet : public AbstractServlet
{
public:
    UpdateUnstructTaskServlet();
    /**
     * @brief doExec  修改任务信息
     * @param request
     * @param response
     */
    virtual void doExec(DRequestContext *request, DResponseContext *response);
};

#endif // UPDATEUNSTRUCTTASKSERVLET_H
