#ifndef SERVLET_H
#define SERVLET_H
#include "duplexlib_global.h"
#include <QtCore>
#include "server/context/drequestcontext.h"
#include "server/context/dresponsecontext.h"
class DUPLEXLIBSHARED_EXPORT Servlet : public QObject
{
    Q_OBJECT
public:
    explicit Servlet(QObject *parent = 0);
    /**
     * @brief doInit    当请求到来时候,比如在这里可以打开数据库连接
     * 到达顺序1
     */
    virtual void doInit() = 0;
    /**
     * @brief doExec 处理请求
     * @param req   请求传递数据
     * @param resp  响应传递参数
     * 到达顺序2
     */
    virtual void doExec(DRequestContext *request = 0,DResponseContext *response = 0) = 0;
    /**
     * @brief doDestory 销毁,在进析构前会先进这个接口,比如在这里可以关闭数据库连接
     * 到达顺序3
     */
    virtual void doDestory() = 0;

signals:

public slots:
};

#endif // SERVLET_H
