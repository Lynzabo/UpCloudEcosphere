#include "dutasksservlet.h"
#include "util/unstructutil.h"
#include "../../../BusinessIServer/UnstructIServer/dao/csunstructdao.h"
using QtJson::JsonObject;
using QtJson::JsonArray;
using namespace Environment::Duplex_Interaction;

DelUnstructTasksServlet::DelUnstructTasksServlet()
{

}

void DelUnstructTasksServlet::doExec(DRequestContext *request, DResponseContext *response)
{
    quint8 responseRState;
    QString responseRContent;responseRContent.clear();
    bool ok;
    CsRUnstructTask task;
    QList<CsRUnstructTask> taskList;taskList.clear();

    QString params = request->getParams();
    //解析参数列表
    QStringList uuids = QtJson::parse(params,ok).toStringList();
    if(!ok) {
        responseRState = Data_Authority::_5;
        responseRContent = Data_Authority::_5_DESC_ParamParseError;
        goto end;
    }
    //处理业务
    try{
        CSUnstructDao::delTask(uuids);
    }
    catch(DBException &ex) {
        Q_UNUSED(ex)
        responseRState = Data_Authority::_4;
        responseRContent = Data_Authority::_4_DESC_DatabaseError;
        goto end;
    }
    //准备回执
//    taskList = CSUnstructDao::dirTask();
    responseRState = Data_Authority::_0;
//    UnstructUtil::taskEntityTojsonStr(responseRContent,taskList);
end:;
    response->setResponseState(responseRState);
    response->setResponseContent(responseRContent);
}

