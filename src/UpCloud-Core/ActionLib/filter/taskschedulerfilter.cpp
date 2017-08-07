#include "taskschedulerfilter.h"
#include <QtConcurrent/QtConcurrent>
TaskSchedulerFilter::TaskSchedulerFilter()
{
    //创建任务执行链
    chain = new TaskSchedulerChain;
}

TaskSchedulerFilter::~TaskSchedulerFilter()
{
    delete chain;
    chain = NULL;
}

void TaskSchedulerFilter::doFilter(QTcpSocket *client, const QString &clientKey, DataGramInfo *gram)
{
    quint8 msgType = gram->msgType;
    try
    {
        //校验传输报文类型是否合法,不合法抛出异常
        //DatagramUtil::getInstance().validateMsgType(msgType);
        //根据报文类型到对应的业务处理
        //处理请求动作
        RequestContext *request = new RequestContext(client,clientKey,gram);
        ResponseContext *response = new ResponseContext(client,clientKey);        
        chain->invoke(request,response,gram);        
        if(response->getDatagram().size()>0)
        {
            //当前可重定向到其它业务
            if(response->getCanRedirect())
            {
                emit
                evt_redirect(request,response);
            }
            //当前报文可发送
            if(response->getCanSend())
            {
                emit
                evt_write(client,response->getDatagram());
            }
        }
        request->deleteLater();
        response->deleteLater();
        //delete request;
        //delete gram;
    }
    catch(...)
    {
        //不认识的报文类型不作于任何处理
    }   
}

void TaskSchedulerFilter::on_read(QTcpSocket *client, const QString &clientKey, DataGramInfo *gram)
{
    //    qDebug() << trs("客户%1传来数据:").arg(client_key) << gram->UUID;
    //    this->doFilter(client,clientKey,gram);
    //异步执行过滤
    QtConcurrent::run(this,&TaskSchedulerFilter::doFilter,client,clientKey,gram);
}

