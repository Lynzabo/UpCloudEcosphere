#include "lsutasksevlet.h"
#include "avro.h"
#include "util/unstructutil.h"
#include "../../../BusinessIServer/UnstructIServer/bean/csrusendfiles.h"
#include "../../../BusinessIServer/UnstructIServer/dao/csunstructdao.h"
using QtJson::JsonObject;
using QtJson::JsonArray;
using namespace Environment::Duplex_Interaction;

ListSevUnstructTaskSevlet::ListSevUnstructTaskSevlet()
{

}

void ListSevUnstructTaskSevlet::doExec(DRequestContext *request, DResponseContext *response)
{
    quint8 requestState;
    QString responseContant;responseContant.clear();
     QList<CsRUnstructSendAddr> cstask;
     QString taskUuid;taskUuid.clear();

    bool ok;
    QString params = request->getParams();

    JsonObject paramsOjb = QtJson::parse(params,ok).toMap();
    if(!ok) {
        requestState = Data_Authority::_5;
        responseContant = Data_Authority::_5_DESC_ParamParseError;
        qDebug() << responseContant;
        goto end;
    }
    taskUuid =  paramsOjb["taskuuid"].toString();
    try{
        cstask = CSUnstructDao::dirRSendAddrsByTaskUUID(taskUuid);
    }
    catch(DBException ex){
        requestState = Data_Authority::_4;
        responseContant = Data_Authority::_4_DESC_DatabaseError;
        goto end;
    }


    requestState = Data_Authority::_0;
    UnstructUtil::taskAddrEntityTojsonStr(responseContant,cstask);
 end:;
    response->setResponseState(requestState);
    response->setResponseContent(responseContant);
}

