#include "ustaskaddrservlet.h"
#include "../../UpCloud-Service-Center/BusinessIServer/StructIServer/bean/csrssendaddr.h"
#include "util/structutil.h"
#include "../../UpCloud-Service-Center/BusinessIServer/StructIServer/dao/csstructdao.h"
using namespace Environment::Duplex_Interaction;
using QtJson::JsonArray;
using QtJson::JsonObject;
UpateStructTaskAddrServlet::UpateStructTaskAddrServlet()
{

}

void UpateStructTaskAddrServlet::doExec(DRequestContext *request, DResponseContext *response)
{
    quint8 responseRState;
    QString responseRContent;responseRContent.clear();
    bool ok;
    QString taskUuid;taskUuid.clear();
    QStringList nodes;nodes.clear();
    quint8 state;
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
    state = (quint8)json.value("state").toInt();
    nodes = QtJson::parse(json.value("uuids").toString(),ok).toStringList();
    if(!ok) {
        responseRState = Data_Authority::_5;
        responseRContent = Data_Authority::_5_DESC_ParamParseError;
        goto end;
    }
    //处理业务
    try{
        CSStructDao::updateRTaskAndAddr(taskUuid,nodes,state);
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

