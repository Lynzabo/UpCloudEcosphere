#ifndef ListBasalTaskSupcodeServlet_H
#define ListBasalTaskSupcodeServlet_H
#include <QtCore>
#include "base.h"
#include "duplex.h"
#include "basaloperaiserver_global.h"
#include "avro.h"
#include "erm.h"
class BASALOPERAISERVERSHARED_EXPORT ListDictServlet : public AbstractServlet
{
public:
    ListDictServlet();
    ~ListDictServlet();
protected:
    /**
     * @brief doInit 初始化参数
     */
    void doInit();
    /**
     * @brief doExec 处理请求
     * @param req   请求传递数据
     * @param resp  响应传递参数
     * 到达顺序2
     */
    virtual void doExec(DRequestContext *request, DResponseContext *response);
private:
    Page* page;
};

#endif // ListBasalTaskSupcodeServlet_H
