#ifndef ABSTRACTREQUEST_H
#define ABSTRACTREQUEST_H
#include "core/request.h"
#include "actionlib_global.h"
/**
 * @brief The AbstractRequest class 处理网络请求基本实现
 * 对Request中的接口提供默认实现,待开发业务时,继承该类做业务处理,当该类提供默认实现方法不满足业务需求时候,可在派生类重写.
 */
class ACTIONLIBSHARED_EXPORT AbstractRequest : public Request
{
public:
    AbstractRequest();
    /**
     * @brief doInit    当请求到来时候,比如在这里可以打开数据库连接
     * 到达顺序1
     */
    virtual void doInit();
    /**
     * @brief doValidate    校验报文数据体合法性
     * 到达顺序2
     */
    virtual void doValidate(RequestContext *request = 0,ResponseContext *response = 0);
    /**
     * @brief doRequest 获取请求
     * @param req   请求传递数据
     * @param resp  响应传递参数
     * 到达顺序3
     */
    virtual void doRequest(RequestContext *request = 0,ResponseContext *response = 0);
    /**
     * @brief doDestory 销毁,在进析构前会先进这个接口,比如在这里可以关闭数据库连接
     * 到达顺序4
     */
    virtual void doDestory();
private:
};

#endif // ABSTRACTREQUEST_H
