#include "dstaskservlet.h"
#include "util/scheduleutil.h"
#include "../../../BusinessIServer/ScheduleIServer/bean/csrsctask.h"
#include "../../../BusinessIServer/ScheduleIServer/dao/csscheduledao.h"
using namespace Environment::Duplex_Interaction;
using QtJson::JsonArray;
using QtJson::JsonObject;
DelScheduleTaskServlet::DelScheduleTaskServlet()
{

}

void DelScheduleTaskServlet::doExec(DRequestContext *request, DResponseContext *response)
{
    QString responseRContent;
    quint16 responseRState;
    bool ok = false;
    //获取参数反序列化
    QString params = request->getParams();
    QStringList uuids = QtJson::parse(params,ok).toStringList();
    if(!ok)
    {
        responseRState = Data_Authority::_5;
        responseRContent = Data_Authority::_5_DESC_ParamParseError;
        goto end;
    }
    //处理业务
    try{
         CSScheduleDao::delTask(uuids);
    }
    catch(DBException &ex) {
        Q_UNUSED(ex)
        responseRState = Data_Authority::_4;
        responseRContent = Data_Authority::_4_DESC_DatabaseError;
        goto end;
    }
    responseRState = Data_Authority::_0;
end:;
    response->setResponseContent(responseRContent);
    response->setResponseState(responseRState);
}

