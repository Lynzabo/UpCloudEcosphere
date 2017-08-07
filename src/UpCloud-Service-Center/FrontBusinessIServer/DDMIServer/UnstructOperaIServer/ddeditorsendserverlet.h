#ifndef DDEDITORSENDSERVERLET_H
#define DDEDITORSENDSERVERLET_H

#include <QtCore>
#include "unstructoperaiserver_global.h"
#include "base.h"
#include "duplex.h"
#include "avro.h"

#include "../../../BusinessIServer/UnstructIServer/bean/dtask.h"
#include "../../../BusinessIServer/UnstructIServer/bean/dtaskaddr.h"
#include "../../../BusinessIServer/UnstructIServer/bean/dtaskfile.h"

#include "../../../BusinessIServer/UnstructIServer/dao/csunstructdao.h"
#include "../../../BusinessIServer/StructIServer/dao/csstructdao.h"
#include "util/unstructutil.h"



class UNSTRUCTOPERAISERVERSHARED_EXPORT DDEditorSendServerlet : public AbstractServlet
{
public:
    DDEditorSendServerlet();
protected:
    /**
     * @brief doExec 处理请求
     * @param req   请求传递数据
     * @param resp  响应传递参数
     * 到达顺序2
     */
    virtual void doExec(DRequestContext *request = 0,DResponseContext *response = 0);
};

#endif // DDEDITORSENDSERVERLET_H
