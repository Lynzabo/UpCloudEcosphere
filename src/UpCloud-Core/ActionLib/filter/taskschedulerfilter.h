#ifndef TASKSCHEDULERFILTER_H
#define TASKSCHEDULERFILTER_H
#include "core/filter.h"
#include "chain/core/chain.h"
#include "actionlib_global.h"
#include "chain/taskschedulerchain.h"
#include "request/abstractrequest.h"
#include "response/abstractresponse.h"
class ACTIONLIBSHARED_EXPORT TaskSchedulerFilter : public Filter
{
public:
    TaskSchedulerFilter();
    ~TaskSchedulerFilter();
protected:
    /**
     * @brief doFilter  过滤客户请求并作相应操作
     * @param client    客户端对象
     * @param clientKey 客户端主键
     * @param gram  装帧报文
     */
    virtual void doFilter(QTcpSocket *client = 0, const QString &clientKey = "", DataGramInfo *gram = 0);

protected slots:
    /**
     * @brief on_read   读取请求来数据
     * @param client
     * @param clientKey
     * @param gram
     */
    void on_read(QTcpSocket * client, const QString &clientKey, DataGramInfo *gram);
private:
    Chain *chain;
};

#endif // TASKSCHEDULERFILTER_H
