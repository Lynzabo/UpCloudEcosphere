#include "ldictservlet.h"
#include "basaloperaiserver.h"
#include "util/dictutil.h"
#include "../../../UpCloud-Service-Center/BusinessIServer/BasalIServer/bean/csdict.h"
#include "../../../UpCloud-Service-Center/BusinessIServer/BasalIServer/dao/csdictdao.h"
using QtJson::JsonArray;
using QtJson::JsonObject;
using namespace Environment::Duplex_Interaction;

ListDictServlet::ListDictServlet()
{

}

void ListDictServlet::doExec(DRequestContext *request, DResponseContext *response)
{

    quint8 responseRState;
    QString responseRContent;responseRContent.clear();
    QString code;code.clear();
    QString supUuid;supUuid.clear();
    QList<CsDict> taskList;
    CsDict selectDict;
    bool ok;
    //获取参数列表
    QString params = request->getParams();
    JsonObject json = QtJson::parse(params,ok).toMap();
    if(!ok) {
        responseRState = Data_Authority::_5;
        responseRContent = Data_Authority::_5_DESC_ParamParseError;
        goto end;
    }
    code = json["code"].toString();
    supUuid = json["supUuid"].toString();

    //处理业务
    if(!(code.isEmpty()))
        selectDict.setCode(code);
    if(!(supUuid.isEmpty()))
        selectDict.setSupUuid(supUuid);


    taskList = CSDictDao::dirCsDict(selectDict);
    responseRState = Data_Authority::_0;
    DictUtil::taskEntinyTojsonStr(responseRContent,taskList);

 end:;
    response->setResponseState(responseRState);
    response->setResponseContent(responseRContent);
}

