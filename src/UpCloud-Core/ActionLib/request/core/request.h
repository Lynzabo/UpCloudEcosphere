#ifndef REQUEST_H
#define REQUEST_H
#include <QtCore>
#include "actionlib_global.h"
#include "context/requestcontext.h"
#include "context/responsecontext.h"
/**
 * @brief The Request class 处理网络请求纯虚基类
 * 注:按上云报文装帧标准,接收方接收请求后享有如下接口
 */
class ACTIONLIBSHARED_EXPORT Request : public QObject
{
    Q_OBJECT
public:
    explicit Request(QObject *parent = 0);
    /**
     * @brief doInit    当请求到来时候,比如在这里可以打开数据库连接
     * 到达顺序1
     */
    virtual void doInit() = 0;
    /**
     * @brief doValidate    校验报文数据体合法性
     * 到达顺序2
     */
    virtual void doValidate(RequestContext *request = 0,ResponseContext *response = 0) = 0;
    /**
     * @brief doRequest 获取请求
     * @param req   请求传递数据
     * @param resp  响应传递参数
     * 到达顺序3
     */
    virtual void doRequest(RequestContext *request = 0,ResponseContext *response = 0) = 0;
    /**
     * @brief doDestory 销毁,在进析构前会先进这个接口,比如在这里可以关闭数据库连接
     * 到达顺序4
     */
    virtual void doDestory() = 0;


signals:

public slots:
};

#endif // REQUEST_H
