#include "autasknodeservlet.h"
#include "util/unstructutil.h"
#include "../../../BusinessIServer/UnstructIServer/bean/csrusendaddr.h"
#include "../../../BusinessIServer/UnstructIServer/dao/csunstructdao.h"
using QtJson::JsonObject;
using QtJson::JsonArray;
using namespace Environment::Duplex_Interaction;

AddUnstructTaskNodeServlet::AddUnstructTaskNodeServlet()
{

}

void AddUnstructTaskNodeServlet::doExec(DRequestContext *request, DResponseContext *response)
{
    quint8 responseRState;
    QString responseRContent;responseRContent.clear();
    bool ok;
    QString taskUuid;taskUuid.clear();
    QStringList nodes;nodes.clear();
    QStringList groupDes;groupDes.clear();
    QList<CsRUnstructSendAddr> taskList;taskList.clear();

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
    groupDes = QtJson::parse(json.value("description").toString(),ok).toStringList();
    if(!ok) {
        responseRState = Data_Authority::_5;
        responseRContent = Data_Authority::_5_DESC_ParamParseError;
        goto end;
    }
    //查询是否节点已存在
    if((CSUnstructDao::dirRSendAddr(taskUuid,nodes)).size() > 0) {
        responseRState = Data_Authority::_9;
        responseRContent = Data_Authority::_9_DESC_RecordIsExsit;
        goto end;
    }
    //处理业务
    try{
        CSUnstructDao::addRSendAddr(taskUuid,nodes,groupDes);
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

