#include "uutaskservlet.h"
#include "util/unstructutil.h"
#include "../../../BusinessIServer/UnstructIServer/dao/csunstructdao.h"
using QtJson::JsonObject;
using QtJson::JsonArray;
using namespace Environment::Duplex_Interaction;

UpdateUnstructTaskServlet::UpdateUnstructTaskServlet()
{

}

void UpdateUnstructTaskServlet::doExec(DRequestContext *request, DResponseContext *response)
{
    quint8 responseRState;
    QString responseRContent;
    QString params;params.clear();
    QList<CsRUnstructTask> taskList;

    bool ok;
    //获得参数列表
    params = request->getParams();
    //解析参数列表
    ok = UnstructUtil::taskEntityFromjsonStr(taskList,params);
    if(!ok) {
        qDebug() << trs("传递的参数解析错误 ");
        responseRState = Data_Authority::_5;
        responseRContent = Data_Authority::_5_DESC_ParamParseError;
        goto end;
    }
    //处理业务
    try{

        CSUnstructDao::updateRtaskList(taskList);
    }
    //操作数据库错误
    catch(DBException& ex){
        Q_UNUSED(ex)
        responseRState = Data_Authority::_4;
        responseRContent = Data_Authority::_4_DESC_DatabaseError;
        goto end;
    }
    //准备结果集回执
    taskList.clear();
//    taskList = CSUnstructDao::dirTask();
    responseRState = Data_Authority::_0;
//    UnstructUtil::taskEntityTojsonStr(responseRContent,taskList);
end:;
    response->setResponseState(responseRState);
    response->setResponseContent(responseRContent);
}

