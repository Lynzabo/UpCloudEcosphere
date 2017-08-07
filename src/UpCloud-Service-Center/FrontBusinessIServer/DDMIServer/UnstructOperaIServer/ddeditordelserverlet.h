#ifndef DDEDITORDELSERVERLET_H
#define DDEDITORDELSERVERLET_H

#include <QtCore>
#include "unstructoperaiserver_global.h"
#include "base.h"
#include "duplex.h"
#include "avro.h"

class UNSTRUCTOPERAISERVERSHARED_EXPORT DDEditorDelServerlet : public AbstractServlet
{
public:
    DDEditorDelServerlet();
protected:
    /**
     * @brief doExec 处理请求
     * @param req   请求传递数据
     * @param resp  响应传递参数
     * 到达顺序2
     */
    virtual void doExec(DRequestContext *request = 0,DResponseContext *response = 0);
};

#endif // DDEDITORDELSERVERLET_H
