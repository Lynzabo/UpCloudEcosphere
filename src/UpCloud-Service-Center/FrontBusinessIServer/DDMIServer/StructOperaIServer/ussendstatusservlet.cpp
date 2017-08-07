#include "ussendstatusservlet.h"
#include "../../UpCloud-Service-Center/BusinessIServer/StructIServer/bean/csrssendstatus.h"
#include "util/structutil.h"
#include "../../UpCloud-Service-Center/BusinessIServer/StructIServer/dao/csstructdao.h"
using namespace Environment::Duplex_Interaction;
using QtJson::JsonArray;
using QtJson::JsonObject;

UpdateStructSendStatusServlet::UpdateStructSendStatusServlet()
{

}

void UpdateStructSendStatusServlet::doExec(DRequestContext *request, DResponseContext *response)
{
    quint8 responseRState;
    QString responseRContent;responseRContent.clear();
    bool ok;
    QStringList uuids;uuids.clear();
    QString taskUuid;taskUuid.clear();
    quint8 state;

    QString params = request->getParams();
    //解析参数列表
    JsonObject json = QtJson::parse(params,ok).toMap();
    if(!ok) {
        responseRState = Data_Authority::_5;
        responseRContent = Data_Authority::_5_DESC_ParamParseError;
        goto end;
    }
    state = (quint8)json.value("state").toInt();
    taskUuid = json.value("taskUuid").toString();
    uuids = QtJson::parse(json.value("uuids").toString(),ok).toStringList();
    if(!ok) {
        responseRState = Data_Authority::_5;
        responseRContent = Data_Authority::_5_DESC_ParamParseError;
        goto end;
    }
    //处理业务
    try{
        CSStructDao::updateRTaskSendStatusByUUID(taskUuid,uuids,state);
    }
    catch(DBException &ex) {
        Q_UNUSED(ex)
        responseRState = Data_Authority::_4;
        responseRContent = Data_Authority::_4_DESC_DatabaseError;
        goto end;
    }
    //准备回执
    responseRState = Data_Authority::_0;
    responseRContent = trs("成功");
end:;
    response->setResponseState(responseRState);
    response->setResponseContent(responseRContent);
}

