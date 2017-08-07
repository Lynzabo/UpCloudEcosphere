#include "adictservlet.h"
#include "util/dictutil.h"
#include "../../../UpCloud-Service-Center/BusinessIServer/BasalIServer/bean/csdict.h"
#include "../../../UpCloud-Service-Center/BusinessIServer/BasalIServer/dao/csdictdao.h"
using QtJson::JsonArray;
using QtJson::JsonObject;
using namespace Environment::Duplex_Interaction;
AddDictServlet::AddDictServlet()
{

}

void AddDictServlet::doExec(DRequestContext *request, DResponseContext *response)
{
    quint16 responseRSteate;
    QString responseRContent;responseRContent.clear();
    QString params;params.clear();
    CsDict task;
    QString curTime;
    QString uuid;uuid.clear();
    //接收客户的参数列表
    params = request->getParams();
    //解析
    bool ok = DictUtil::taskEntinyFromjsonStr(task,params);
    if(!ok) {
        responseRSteate = Data_Authority::_5;
        responseRContent = Data_Authority::_5_DESC_ParamParseError;
        goto end;
    }
    if(task.getCode().isEmpty() || task.getName().isEmpty() || task.getSupUuid().isEmpty())
    {
        responseRSteate = Data_Authority::_7;
        responseRContent = Data_Authority::_7_DESC_ParamsHasNullValue;
        goto end;
    }
    //处理业务
    UuidUtil::nextUUID(uuid);
    task.setUuid(uuid);
    TimerUtil::toString(curTime);
    task.setInsertor(trs("zjy"));
    task.setInsertTime(curTime);
    task.setOperater(trs("zjy"));
    task.setOperaTime(curTime);
    //记录是否已经存在
    if(CSDictDao::dirCsDict(task.getCode(),task.getSupUuid()).size() > 0)
    {
        responseRSteate = Data_Authority::_9;
        responseRContent = Data_Authority::_9_DESC_RecordIsExsit;
        goto end;
    }
    try{
        CSDictDao::addCsDict(task);
    }
    catch(DBException& ex) {
        Q_UNUSED(ex)
        responseRSteate = Data_Authority::_4;
        responseRContent = Data_Authority::_4_DESC_DatabaseError;
        goto end;
    }
    responseRSteate = Data_Authority::_0;
    DictUtil::taskEntinyTojsonStr(responseRContent,task);
end:;
    response->setResponseState(responseRSteate);
    response->setResponseContent(responseRContent);
}


