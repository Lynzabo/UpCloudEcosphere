#ifndef UPDATECLIENTGROUPASSOCSERVLET_H
#define UPDATECLIENTGROUPASSOCSERVLET_H
#include <QtCore>
#include "base.h"
#include "duplex.h"
#include "avro.h"
#include "basaloperaiserver_global.h"

class BASALOPERAISERVERSHARED_EXPORT UpdateClientGroupAssocServlet : public AbstractServlet
{
public:
    UpdateClientGroupAssocServlet();
protected:
    /**
      * @brief doExec   处理请求
      * @param request  请求传递数据
      * @param response 响应传递参数
      */
     virtual void doExec(DRequestContext *request, DResponseContext *response);
};

#endif // UPDATECLIENTGROUPASSOCSERVLET_H
