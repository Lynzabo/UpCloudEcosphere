#include "croperainterceptor.h"
#include "duplex.h"
#include "avro.h"
#include "erm.h"
#include "baseiserver.h"
QMutex * CenterRemoteUIOperaInterceptor::mutex = new QMutex;
using namespace Environment::Duplex_Interaction;
CenterRemoteUIOperaInterceptor::CenterRemoteUIOperaInterceptor()
{

}

CenterRemoteUIOperaInterceptor::~CenterRemoteUIOperaInterceptor()
{
    delete gramEntity;
}

void CenterRemoteUIOperaInterceptor::doRequest(RequestContext *request, ResponseContext *response)
{
    mutex->lock();
    QByteArray datagram;
    //发送报文实体对象
    RespRemoteUIOperaCentorInfo *respEntity = new RespRemoteUIOperaCentorInfo;
    CorePOJO *corePOJO = new CorePOJO;
    bool isLegal = true;
    int ExecType;
    QString json;json.clear();
    using QtJson::JsonObject;
    using QtJson::JsonArray;
    JsonObject objJson;
    QString paramsStr;paramsStr.clear();
    bool hasAuthority = true;
    QString responseContent;responseContent.clear();
    ////反序列化报文体到实体对象
    quint8 msgType = request->getMsgType();
    QString message = request->getMessage();
    QString clientKey = request->getClientKey();
    AbstractServlet *req;
    DRequestContext *dreq;
    DResponseContext *dresp;
    //解帧报文并生成报文实体
    try
    {
        gramEntity = DatagramUtil::getInstance().parseMessageText(CallbackByReqRemoteUIOperaCenterInfo,msgType,message);
    }
    catch(TransException &excep)
    {
        qDebug() << trs("反序列化报文体到实体对象:ErrorCode:%1,ErrorMsg:%2").arg(excep.getType()).arg(excep.getText());
        goto end;
    }
    ExecType = gramEntity->ExecType;
    isLegal = DuplexUtil::addrIsLegal(ExecType);
    if(!isLegal)
    {
        //不合法
        corePOJO->setState(Data_Authority::_2);
        corePOJO->setStateDesc(Data_Authority::_2_DESC_AddrIsInvalid);
        corePOJO->setContent(trs(""));
        goto sendDatagram;
    }
    ////获取用户权限,校验是否有操作权限,无操作权限,直接返回
    ////TODO    连接权限管理系统
    if(!hasAuthority)
    {
        //未授权访问地址
        corePOJO->setState(Data_Authority::_1);
        corePOJO->setStateDesc(Data_Authority::_1_DESC_Unauthorized);
        corePOJO->setContent(trs(""));
        goto sendDatagram;
    }
    ////执行操作
    paramsStr = gramEntity->Params;
    //获取实体对象
    req = (AbstractServlet *)FDuplexRegistryFactory::createObject(ExecType);
    if(req == NULL)
    {
        //未找到执行业务
        corePOJO->setState(Data_Authority::_3);
        corePOJO->setStateDesc(Data_Authority::_3_DESC_SeiviceIsNull);
        corePOJO->setContent(trs(""));
        goto sendDatagram;
    }
    req->doInit();
    //处理请求动作
    dreq = new DRequestContext(clientKey,(DataGramInfo*)gramEntity,ExecType,paramsStr);
    dresp = new DResponseContext(clientKey,ExecType,paramsStr);
    req->doExec(dreq,dresp);
    req->doDestory();
    corePOJO->setState(Data_Authority::_0);
    corePOJO->setStateDesc(Data_Authority::_0_DESC_Success);
    responseContent = dresp->getResponseContent();
    if(!(responseContent.isEmpty()))
    corePOJO->setContent(responseContent);
sendDatagram:
    objJson["state"] = corePOJO->getState();
    objJson["stateDesc"] = corePOJO->getStateDesc();
    objJson["content"] = corePOJO->getContent();
    json = QtJson::serialize(objJson);
    //TODO状态码未搞定
    respEntity->ExecType = gramEntity->ExecType;
    respEntity->Params = gramEntity->Params;
    respEntity->State = corePOJO->getState();
    respEntity->Content = json;
    delete corePOJO;
    ////拼装响应下载状态报文并发送给当前节点服务器
    try
    {
        DatagramUtil::getInstance().packDatagram(respEntity,datagram,  request->getUUID());
        delete respEntity;
    }
    catch(QString &excep)
    {
        qDebug() << trs("出错:%1").arg(excep);
        goto end;
    }
    catch(TransException &excep)
    {
        qDebug() << excep.getText();
        goto end;
    }
    response->setDatagram(datagram);
    ////结束
end:
    mutex->unlock();
}

ReqRemoteUIOperaCentorInfo *CenterRemoteUIOperaInterceptor::CallbackByReqRemoteUIOperaCenterInfo(ReqRemoteUIOperaCentorInfo *operaEntity)
{
    return operaEntity;
}

