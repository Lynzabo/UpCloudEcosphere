#include "dssendaddrservlet.h"
#include "../../UpCloud-Service-Center/BusinessIServer/StructIServer/bean/csrssendaddr.h"
#include "util/structutil.h"
#include "../../UpCloud-Service-Center/BusinessIServer/StructIServer/dao/csstructdao.h"
using namespace Environment::Duplex_Interaction;
using QtJson::JsonArray;
using QtJson::JsonObject;

DelStructSendAddrServlet::DelStructSendAddrServlet()
{

}

void DelStructSendAddrServlet::doExec(DRequestContext *request, DResponseContext *response)
{
    quint8 responseRState;
    QString responseRContent;responseRContent.clear();
    bool ok;
    QString taskUuid;taskUuid.clear();
    QStringList nodes;nodes.clear();
    QList<CsRStructSendAddr> taskList;taskList.clear();

    QString params = request->getParams();
    //解析参数列表
    JsonObject json = QtJson::parse(params,ok).toMap();
    if(!ok) {
        responseRState = Data_Authority::_5;
        responseRContent = Data_Authority::_5_DESC_ParamParseError;
        goto end;
    }
    taskUuid = json.value("taskuuid").toString();
    nodes = QtJson::parse(json.value("uuids").toString(),ok).toStringList();
    if(!ok) {
        responseRState = Data_Authority::_5;
        responseRContent = Data_Authority::_5_DESC_ParamParseError;
        goto end;
    }
    //处理业务
    try{
        CSStructDao::delRSendAddr(taskUuid,nodes);
    }
    catch(DBException &ex) {
        Q_UNUSED(ex)
        responseRState = Data_Authority::_4;
        responseRContent = Data_Authority::_4_DESC_DatabaseError;
        goto end;
    }
    //准备回执
    responseRState = Data_Authority::_0;
end:;
    response->setResponseState(responseRState);
    response->setResponseContent(responseRContent);
}

