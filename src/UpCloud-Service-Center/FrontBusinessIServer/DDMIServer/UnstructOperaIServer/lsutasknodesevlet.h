#ifndef LISTSEVUNSTRUCTTASKSEVLET_H
#define LISTSEVUNSTRUCTTASKSEVLET_H
#include <QtCore>
#include "erm.h"
#include "unstructoperaiserver_global.h"
#include "base.h"
#include "duplex.h"
#include "avro.h"

class UNSTRUCTOPERAISERVERSHARED_EXPORT ListSevUnstructTaskNodeSevlet : public AbstractServlet
{
public:
    ListSevUnstructTaskNodeSevlet();
    ~ListSevUnstructTaskNodeSevlet();
protected:
    /**
     * @brief doInit    当请求到来时候,比如在这里可以打开数据库连接
     * 到达顺序1
     */
    void doInit();
    /**
     * @brief doExec 处理请求
     * @param req   请求传递数据
     * @param resp  响应传递参数
     * 到达顺序2
     */
    void doExec(DRequestContext *request = 0,DResponseContext *response = 0);
private:
    Page* page;
};

#endif // LISTSEVUNSTRUCTTASKSEVLET_H
