#include "ustaskservlet.h"
#include "util/scheduleutil.h"
#include "../../../BusinessIServer/ScheduleIServer/bean/csrsctask.h"
#include "../../../BusinessIServer/ScheduleIServer/dao/csscheduledao.h"
using namespace Environment::Duplex_Interaction;
using QtJson::JsonArray;
using QtJson::JsonObject;
UpdateScheduleTaskServlet::UpdateScheduleTaskServlet()
{

}

void UpdateScheduleTaskServlet::doExec(DRequestContext *request, DResponseContext *response)
{
    QString responseRContent;
    quint16 responseRState;
    QList<CsRScheduleTask> taskList;
    bool ok = false;
    //获取参数反序列化
    QString params = request->getParams();
    ok = ScheduleUtil::taskListEntinyFromJson(taskList,params);
    if(!ok)
    {
        responseRState = Data_Authority::_5;
        responseRContent = Data_Authority::_5_DESC_ParamParseError;
        goto end;
    }
    //处理业务
    try{
        CSScheduleDao::updateTask(taskList);
    }
    catch(DBException &ex) {
        Q_UNUSED(ex)
        responseRState = Data_Authority::_4;
        responseRContent = Data_Authority::_4_DESC_DatabaseError;
        goto end;
    }
    taskList.clear();
//    taskList = CSScheduleDao::listTask();
    responseRState = Data_Authority::_0;
//    ScheduleUtil::taskListEntinyToJson(responseRContent,taskList);
end:;
    response->setResponseContent(responseRContent);
    response->setResponseState(responseRState);
}

