#include "ustaskaddrservlet.h"
#include "util/scheduleutil.h"
#include "../../../BusinessIServer/ScheduleIServer/bean/csrscsendaddr.h"
#include "../../../BusinessIServer/ScheduleIServer/dao/csscheduledao.h"
using namespace Environment::Duplex_Interaction;
using QtJson::JsonArray;
using QtJson::JsonObject;
UpdateScheduleTaskAddrServlet::UpdateScheduleTaskAddrServlet()
{

}

void UpdateScheduleTaskAddrServlet::doExec(DRequestContext *request, DResponseContext *response)
{
    QString responseRContent;
    quint16 responseRState;
    bool ok = false;
    QString time;time.clear();
    QString taskUuid;taskUuid.clear();
    quint8 state;
    QStringList nodes;nodes.clear();
    //获取参数反序列化
    QString params = request->getParams();

    JsonObject json = QtJson::parse(params,ok).toMap();
    if(!ok)
    {
        responseRState = Data_Authority::_5;
        responseRContent = Data_Authority::_5_DESC_ParamParseError;
        goto end;
    }
    taskUuid = json.value("taskUuid").toString();
    state = (quint8)json.value("state").toInt();
    nodes = QtJson::parse(json.value("nodes").toString(),ok).toStringList();
    time = QtJson::parse(json.value("time").toString(),ok).toString();
    //处理业务
    try{
         CSScheduleDao::updateRTaskAndSendAddrStatus(taskUuid,nodes,state);
    }
    catch(DBException &ex) {
        Q_UNUSED(ex)
        responseRState = Data_Authority::_4;
        responseRContent = Data_Authority::_4_DESC_DatabaseError;
        goto end;
    }
    responseRState = Data_Authority::_0;
    responseRContent = trs("成功");
end:;
    response->setResponseContent(responseRContent);
    response->setResponseState(responseRState);
}

