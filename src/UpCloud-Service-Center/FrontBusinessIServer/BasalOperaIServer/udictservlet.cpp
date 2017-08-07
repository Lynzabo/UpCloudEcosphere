#include "udictservlet.h"
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
    QList<CsDict> taskList;
    //接收客户的参数列表
    params = request->getParams();

    bool ok = DictUtil::taskEntinyFromjsonStr(taskList,params);

    if(!ok) {
        responseRSteate = Data_Authority::_5;
        responseRContent = Data_Authority::_5_DESC_ParamParseError;
        goto end;
    }

    //处理业务
    try{
        CSDictDao::updateCsDict(taskList);
    }
    catch(DBException& ex) {
        Q_UNUSED(ex)
        responseRSteate = Data_Authority::_4;
        responseRContent = Data_Authority::_4_DESC_DatabaseError;
        goto end;
    }
    responseRSteate = Data_Authority::_0;
    responseRContent = tr("修改成功");
end:;
    response->setResponseState(responseRSteate);
    response->setResponseContent(responseRContent);

}

