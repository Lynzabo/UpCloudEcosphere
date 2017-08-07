#include "ddictservlet.h"
#include "basaloperaiserver.h"
#include "util/dictutil.h"
#include "../../../UpCloud-Service-Center/BusinessIServer/BasalIServer/bean/csdict.h"
#include "../../../UpCloud-Service-Center/BusinessIServer/BasalIServer/dao/csdictdao.h"
using QtJson::JsonArray;
using QtJson::JsonObject;
using namespace Environment::Duplex_Interaction;

DelDictServlet::DelDictServlet()
{

}

void DelDictServlet::doExec(DRequestContext *request, DResponseContext *response)
{
    quint8 responseRState;
    QString responseRContent;responseRContent.clear();
    QList<CsDict> taskList;
    bool ok;
    //获取参数列表
    QString params = request->getParams();
    QStringList codes = QtJson::parse(params,ok).toStringList();
    if(!ok) {
        responseRState = Data_Authority::_5;
        responseRContent = Data_Authority::_5_DESC_ParamParseError;
        goto end;
    }
    if(codes.size()==0)
    {
        responseRState = Data_Authority::_7;
        responseRContent = Data_Authority::_7_DESC_ParamsHasNullValue;
        goto end;
    }
    //处理业务

    try{
       CSDictDao::delCsDict(codes);
    }
    catch(DBException& ex){
        Q_UNUSED(ex)
        responseRState = Data_Authority::_4;
        responseRContent = Data_Authority::_4_DESC_DatabaseError;
        goto end;
    }
     //准备结果集
    taskList = CSDictDao::dirCsDict();
    responseRState = Data_Authority::_0;
    DictUtil::taskEntinyTojsonStr(responseRContent,taskList);

 end:;
    response->setResponseState(responseRState);
    response->setResponseContent(responseRContent);
}

