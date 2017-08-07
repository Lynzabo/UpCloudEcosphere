#ifndef DELSECHEDULETASKADDRSERVLET_H
#define DELSECHEDULETASKADDRSERVLET_H
#include <QtCore>
#include "avro.h"
#include "base.h"
#include "duplex.h"
#include "scheduleoperaiserver_global.h"

class SCHEDULEOPERAISERVERSHARED_EXPORT DelScheduleTaskAddrServlet : public AbstractServlet
{
public:
    DelScheduleTaskAddrServlet();
    /**
     * @brief doExec 处理请求
     * @param req   请求传递数据
     * @param resp  响应传递参数
     * 到达顺序2
     */
    virtual void doExec(DRequestContext *request = 0,DResponseContext *response = 0);
};

#endif // DELSECHEDULETASKADDRSERVLET_H
