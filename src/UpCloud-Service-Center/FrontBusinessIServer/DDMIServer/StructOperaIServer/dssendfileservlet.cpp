#include "dssendfileservlet.h"
#include "../../UpCloud-Service-Center/BusinessIServer/StructIServer/bean/csrssendfiles.h"
#include "util/structutil.h"
#include "../../UpCloud-Service-Center/BusinessIServer/StructIServer/dao/csstructdao.h"
using namespace Environment::Duplex_Interaction;
using QtJson::JsonArray;
using QtJson::JsonObject;

DelStructSendFileServlet::DelStructSendFileServlet()
{

}

void DelStructSendFileServlet::doExec(DRequestContext *request, DResponseContext *response)
{
    quint8 responseRState;
    QString responseRContent;responseRContent.clear();
    bool ok;
    int i;
    QString taskUuid;taskUuid.clear();
    QStringList uuidList;
    JsonArray uuids;
    QList<CsRStructSendFiles> taskList;taskList.clear();
    QString params = request->getParams();
    //解析参数列表
    JsonObject json = QtJson::parse(params,ok).toMap();
    if(!ok) {
        responseRState = Data_Authority::_5;
        responseRContent = Data_Authority::_5_DESC_ParamParseError;
        goto end;
    }
    taskUuid = json.value("taskuuid").toString();
    uuids = QtJson::parse(json.value("uuids").toString(),ok).toList();
    if(!ok) {
        responseRState = Data_Authority::_5;
        responseRContent = Data_Authority::_5_DESC_ParamParseError;
        goto end;
    }
    for(i = 0;i < uuids.size();++i) {
        uuidList.insert(i,uuids.at(i).toString());
    }

    //处理业务
    try{
        CSStructDao::delRSendFiles(taskUuid,uuidList);
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

