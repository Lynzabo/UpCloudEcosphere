#include "uutasksendfilesservlet.h"
#include "avro.h"
#include "util/unstructutil.h"
#include "../../../BusinessIServer/UnstructIServer/bean/csrusendfiles.h"
#include "../../../BusinessIServer/UnstructIServer/dao/csunstructdao.h"
using QtJson::JsonObject;
using QtJson::JsonArray;
using namespace Environment::Duplex_Interaction;
UpdateUnstructTaskSendFilesServlet::UpdateUnstructTaskSendFilesServlet()
{

}

void UpdateUnstructTaskSendFilesServlet::doExec(DRequestContext *request, DResponseContext *response)
{
    quint8 responseRState;
    QString responseRContent;responseRContent.clear();
    bool ok;
    int i;
    QString taskUuid;taskUuid.clear();
    QStringList uuids;
    quint8 state;
    QStringList newNameList;
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
    uuids = QtJson::parse(json.value("uuids").toString(),ok).toStringList();
    if(!ok) {
        responseRState = Data_Authority::_5;
        responseRContent = Data_Authority::_5_DESC_ParamParseError;
        goto end;
    }

    //处理业务
    try{
        CSUnstructDao::updateRTaskSendStatusByTaskUUIDAndSendFileUUID(taskUuid,uuids,state);
    }
    catch(DBException &ex) {
        Q_UNUSED(ex)
        responseRState = Data_Authority::_4;
        responseRContent = Data_Authority::_4_DESC_DatabaseError;
        goto end;
    }
    //准备回执
    responseRState = Data_Authority::_0;
    responseRContent = "成功";
end:;
    response->setResponseState(responseRState);
    response->setResponseContent(responseRContent);
}

