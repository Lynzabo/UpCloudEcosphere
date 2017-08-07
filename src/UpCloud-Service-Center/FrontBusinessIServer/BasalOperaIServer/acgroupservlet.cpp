#include "acgroupservlet.h"
#include "util/csgroupandclientutil.h"
#include "../../BusinessIServer/BasalIServer/bean/cscgroup.h"
#include "../../BusinessIServer/BasalIServer/dao/csgroupandclinetdao.h"
using QtJson::JsonArray;
using QtJson::JsonObject;
using namespace Environment::Duplex_Interaction;

AddClientGroupServlet::AddClientGroupServlet()
{

}

void AddClientGroupServlet::doExec(DRequestContext *request, DResponseContext *response)
{
    quint8 responseRState;
    QString curTime;
    QString responseRContent;responseRContent.clear();
    CsClientGroup task;
    QList<CsClientGroup> taskList;taskList.clear();
    bool ok;
    QString params = request->getParams();
    QString uuid;uuid.clear();
    UuidUtil::nextUUID(uuid);


    //准备参数
    QVariantMap paramsMap = QtJson::parse(params,ok).toMap();
    //解析参数失败
    if(!ok) {
        qDebug() << trs("解析参数失败");
        responseRState = Data_Authority::_5;
        responseRContent = Data_Authority::_5_DESC_ParamParseError;
        goto end;
    }
    paramsMap["uuid"] = uuid;
    paramsMap["insertor"] = tr("zjy");
    TimerUtil::toString(curTime);
    paramsMap["insertTime"] = curTime;
    paramsMap["operator"] = tr("zjy");
    paramsMap["operatTime"] = curTime;
    //处理业务
    try{
        CsGroupAndClinetDao::addGroupClient(paramsMap);
    }
    catch(DBException &ex){
        Q_UNUSED(ex)
          responseRState = Data_Authority::_4;
          responseRContent = Data_Authority::_4_DESC_DatabaseError;
          goto end;
    }
    //处理结果
    responseRState = Data_Authority::_0;
    responseRContent = tr("成功");
end:;
    response->setResponseState(responseRState);
    response->setResponseContent(responseRContent);
}

