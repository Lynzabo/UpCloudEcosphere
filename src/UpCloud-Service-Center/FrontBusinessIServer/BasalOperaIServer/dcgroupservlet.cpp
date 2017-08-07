#include "dcgroupservlet.h"
#include "util/csgroupandclientutil.h"
#include "../../BusinessIServer/BasalIServer/bean/cscgroup.h"
#include "../../BusinessIServer/BasalIServer/dao/csgroupandclinetdao.h"
using QtJson::JsonArray;
using QtJson::JsonObject;
using namespace Environment::Duplex_Interaction;

DelClientGroupServlet::DelClientGroupServlet()
{

}

void DelClientGroupServlet::doExec(DRequestContext *request, DResponseContext *response)
{

    quint8 responseRState;
    QString responseRContent;responseRContent.clear();
    bool ok;
    QString params = request->getParams();
    QString groupuuid;

    //准备参数
    JsonObject paramsMap = QtJson::parse(params,ok).toMap();
    if(!ok) {
        qDebug() << trs("解析参数失败");
        responseRState = Data_Authority::_5;
        responseRContent = Data_Authority::_5_DESC_ParamParseError;
        goto end;
    }
    groupuuid = paramsMap.value("x_uuid").toString();
    //处理业务
    try{
        CsGroupAndClinetDao::delGroupClient(groupuuid);
    }
    catch(DBException &ex){
        Q_UNUSED(ex)
        responseRState = Data_Authority::_4;
        responseRContent = Data_Authority::_4_DESC_DatabaseError;
        goto end;
    }
    //处理结果
    responseRState = Data_Authority::_0;
    responseRContent = Data_Authority::_0_DESC_Success;

end:;
    response->setResponseState(responseRState);
    response->setResponseContent(responseRContent);
}

