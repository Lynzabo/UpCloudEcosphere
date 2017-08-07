#include "ucgroupservlet.h"
#include "util/csgroupandclientutil.h"
#include "../../BusinessIServer/BasalIServer/bean/cscgroup.h"
#include "../../BusinessIServer/BasalIServer/dao/csgroupandclinetdao.h"
using QtJson::JsonArray;
using QtJson::JsonObject;
using namespace Environment::Duplex_Interaction;

UpdateClientGroupServlet::UpdateClientGroupServlet()
{

}

void UpdateClientGroupServlet::doExec(DRequestContext *request, DResponseContext *response)
{
    quint8 responseRState;
    QString responseRContent;responseRContent.clear();
    bool ok;
    QString result;result.clear();
    CsClientGroup task,temtask;
    QList<CsClientGroup> taskList;taskList.clear();
    QString curTime;
    //准备参数
    QString params = request->getParams();
    ok = CsGroupAndClientUtil::taskEntinyFromjsonStr(task,params);
    //解析参数失败
    if(!ok) {
        qDebug() << trs("解析参数失败");
        responseRState = Data_Authority::_5;
        responseRContent = Data_Authority::_5_DESC_ParamParseError;
        goto end;
    }
    if(task.getUuid().isEmpty() || task.getName().isEmpty() || task.getDescription().isEmpty()
            /*|| task.getSequence() == 0*/ || task.getSupUuid().isEmpty()) {
        responseRState = Data_Authority::_7;
        responseRContent = Data_Authority::_7_DESC_ParamsHasNullValue;
        goto end;
    }
    temtask = CsGroupAndClinetDao::itemGroupClient(task.getUuid());
    task.setInsertor(temtask.getInsertor());
    task.setInsertTime(temtask.getInsertTime());
    task.setOperater(trs("zjy"));
    TimerUtil::toString(curTime);
    task.setOperatTime(curTime);
    try{
        CsGroupAndClinetDao::updateGroupClient(task);
    }
    catch(DBException &ex){
        Q_UNUSED(ex)
        responseRState = Data_Authority::_4;
        responseRContent = Data_Authority::_4_DESC_DatabaseError;
        goto end;
    }
    //准处理结果 返回修改的子组
//    task.clear();
//    task.setSupUuid("-1");
//    taskList = CsGroupAndClinetDao::dirGroupClient(task);
//    if(taskList.isEmpty()) {
//        responseRState = Data_Authority::_10;
//        responseRContent = Data_Authority::_10_DESC_RecordEmpty;
//    }
//    else {
        responseRState = Data_Authority::_0;
//        CsGroupAndClientUtil::taskEntinyTojsonStr(responseRContent,taskList);
//    }
end:;
    response->setResponseState(responseRState);
    response->setResponseContent(responseRContent);
}

