#include "taskschedulerchain.h"
#include "context/requestcontext.h"
TaskSchedulerChain::TaskSchedulerChain()
{

}

void TaskSchedulerChain::invoke(RequestContext *request,ResponseContext *response, DataGramInfo *gram)
{
    //根据报文类型自动跳转到响应的Request
    quint8 msgType = gram->msgType;
    //获取实体对象
    AbstractRequest *req = (AbstractRequest *)ActionRegistryFactory::createObject(msgType);
    if(req == NULL)
        return;
    req->doInit();
    req->doValidate(request,response);
    if(response->getDatagram().size()<=0)
        req->doRequest(request,response);
    req->doDestory();
}

