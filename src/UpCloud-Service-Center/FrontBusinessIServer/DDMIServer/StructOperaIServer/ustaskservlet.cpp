#include "ustaskservlet.h"
#include "../../UpCloud-Service-Center/BusinessIServer/StructIServer/bean/csrstask.h"
#include "util/structutil.h"
#include "../../UpCloud-Service-Center/BusinessIServer/StructIServer/dao/csstructdao.h"
using namespace Environment::Duplex_Interaction;
using QtJson::JsonArray;
using QtJson::JsonObject;

UpdateStructTaskServlet::UpdateStructTaskServlet()
{

}

void UpdateStructTaskServlet::doExec(DRequestContext *request, DResponseContext *response)
{
    quint8 responseRState;
    QString responseRContent;responseRContent.clear();
    bool ok;
    CsRStructTask task;
    task.clear();
    QList<CsRStructTask> taskList;taskList.clear();
    QString params = request->getParams();

    //解析参数列表
    ok = StructUtil::taskEntinyFromjsonStr(taskList,params);
    if(!ok) {
        responseRState = Data_Authority::_5;
        responseRContent = Data_Authority::_5_DESC_ParamParseError;
        goto end;
    }
    //处理业务
    try{
        CSStructDao::updateRTask(taskList);
    }
    catch(DBException &ex) {
        Q_UNUSED(ex)
        responseRState = Data_Authority::_4;
        responseRContent = Data_Authority::_4_DESC_DatabaseError;
        goto end;
    }
    //准备回执
//    taskList = CSStructDao::dirRTask();
    responseRState = Data_Authority::_0;
//    StructUtil::taskEntinyTojsonStr(responseRContent,taskList);
end:;
    response->setResponseState(responseRState);
    response->setResponseContent(responseRContent);
}

