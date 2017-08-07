#include "dutaskfilesevlet.h"
#include "avro.h"
#include "util/unstructutil.h"
#include "../../../BusinessIServer/UnstructIServer/bean/csrutask.h"
#include "../../../BusinessIServer/UnstructIServer/dao/csunstructdao.h"
using QtJson::JsonObject;
using QtJson::JsonArray;
using namespace Environment::Duplex_Interaction;

DelUnstructTaskFileServlet::DelUnstructTaskFileServlet()
{

}

void DelUnstructTaskFileServlet::doExec(DRequestContext *request, DResponseContext *response)
{
    quint8 responseRState;
    QString responseRContent;responseRContent.clear();
    bool ok;
    int i;
    QString taskUuid;taskUuid.clear();
    QStringList uuidList;
    JsonArray uuids;uuids.clear();
    QList<CsRUnstructSendFiles> taskList;taskList.clear();
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
    foreach(const QVariant &uuid,uuids) {
        uuidList.append(uuid.toString());
    }

    //处理业务
    try{
        CSUnstructDao::delTaskFile(taskUuid,uuidList);
    }
    catch(DBException &ex) {
        Q_UNUSED(ex)
        responseRState = Data_Authority::_4;
        responseRContent = Data_Authority::_4_DESC_DatabaseError;
        goto end;
    }
    //准备回执
    responseRState = Data_Authority::_0;
set:;
    taskList = CSUnstructDao::dirRSendFilesByTaskUUID(taskUuid);
    UnstructUtil::taskAddrFileEntityTojsonStr(responseRContent,taskList);
end:;
    response->setResponseState(responseRState);
    response->setResponseContent(responseRContent);
}

