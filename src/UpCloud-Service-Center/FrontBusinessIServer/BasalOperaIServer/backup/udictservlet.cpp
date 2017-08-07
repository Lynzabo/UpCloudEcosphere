#include "udictservlet.h"
#include "basaloperaiserver.h"
#include "util/dictutil.h"
#include "../../../UpCloud-Service-Center/BusinessIServer/BasalIServer/bean/csdict.h"
#include "../../../UpCloud-Service-Center/BusinessIServer/BasalIServer/dao/csdictdao.h"
using QtJson::JsonArray;
using QtJson::JsonObject;
using namespace Environment::Duplex_Interaction;
UpdateDictServlet::UpdateDictServlet()
{

}

void UpdateDictServlet::doExec(DRequestContext *request, DResponseContext *response)
{
    quint16 responseRSteate;
    QString responseRContent;responseRContent.clear();
    QString params;params.clear();
    CsDict task,tmpTask;
    QList<CsDict> taskList;
    QString curTime;
    //接收客户的参数列表
    params = request->getParams();
    bool ok = DictUtil::taskEntinyFromjsonStr(task,params);

    if(!ok) {
        responseRSteate = Data_Authority::_5;
        responseRContent = Data_Authority::_5_DESC_ParamParseError;
        goto end;
    }
    //判断参数列表是否有空
    if(task.getCode().isEmpty() || task.getName().isEmpty() || task.getSupUuid().isEmpty()
            || task.getSequence()==0 || task.getState() == 0)
    {
        responseRSteate = Data_Authority::_7;
        responseRContent = Data_Authority::_7_DESC_ParamsHasNullValue;
        goto end;
    }

    tmpTask = CSDictDao::itemCsDict(task.getUuid());
    task.setCode(tmpTask.getCode());
    task.setInsertor(tmpTask.getInsertor());
    task.setInsertTime(tmpTask.getInsertTime());
    task.setOperater(trs("zjy"));
    TimerUtil::toString(curTime);
    task.setOperaTime(curTime);

    //处理业务
    try{
        CSDictDao::updateCsDict(task);
    }
    catch(DBException& ex) {
        Q_UNUSED(ex)
        responseRSteate = Data_Authority::_4;
        responseRContent = Data_Authority::_4_DESC_DatabaseError;
        goto end;
    }
    taskList = CSDictDao::dirCsDict();
    responseRSteate = Data_Authority::_0;
    DictUtil::taskEntinyTojsonStr(responseRContent,taskList);
end:;
    response->setResponseState(responseRSteate);
    response->setResponseContent(responseRContent);

}

