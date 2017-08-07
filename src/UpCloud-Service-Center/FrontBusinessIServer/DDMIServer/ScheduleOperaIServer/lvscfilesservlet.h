#ifndef LISTVCSASCSENDFILESSERVLET_H
#define LISTVCSASCSENDFILESSERVLET_H
#include <QtCore>
#include "avro.h"
#include "base.h"
#include "duplex.h"
#include "scheduleoperaiserver_global.h"

class SCHEDULEOPERAISERVERSHARED_EXPORT ListVCsAScSendFilesServlet : public AbstractServlet
{
public:
    ListVCsAScSendFilesServlet();
    /**
     * @brief doExec 处理请求
     * @param req   请求传递数据
     * @param resp  响应传递参数
     * 到达顺序2
     */
    virtual void doExec(DRequestContext *request = 0,DResponseContext *response = 0);
};

#endif // LISTVCSASCSENDFILESSERVLET_H
