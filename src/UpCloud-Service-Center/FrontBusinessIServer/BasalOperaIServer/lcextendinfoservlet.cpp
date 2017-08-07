#include "lcextendinfoservlet.h"
#include "util/csgroupandclientutil.h"
#include "../../BusinessIServer/BasalIServer/bean/cscextendinfo.h"
#include "../../BusinessIServer/BasalIServer/dao/csgroupandclinetdao.h"
using QtJson::JsonArray;
using QtJson::JsonObject;
using namespace Environment::Duplex_Interaction;

ListClientExtendInfoServlet::ListClientExtendInfoServlet()
{

}

void ListClientExtendInfoServlet::doExec(DRequestContext *request, DResponseContext *response)
{
    quint8 responseRState;
    QString responseRContent;responseRContent.clear();
    bool ok;
    QString result;result.clear();
    QList<CsClientExtendInfo> exList;exList.clear();

    //准备参数
    QString params = request->getParams();
    QString clientUuid = QtJson::parse(params,ok).toString();
    if(!ok) {
        qDebug() << trs("解析参数失败");
        responseRState = Data_Authority::_5;
        responseRContent = Data_Authority::_5_DESC_ParamParseError;
        goto end;
    }
    try{
        exList = CsGroupAndClinetDao::dirClientExtendInfo(clientUuid);
    }
    catch(DBException &ex){
        Q_UNUSED(ex)
        responseRState = Data_Authority::_4;
        responseRContent = Data_Authority::_4_DESC_DatabaseError;
        goto end;
    }
    //准处理结果 返回修改的子组

        responseRState = Data_Authority::_0;
        CsGroupAndClientUtil::taskEntinyTojsonStr(responseRContent,exList);
end:;
    response->setResponseState(responseRState);
    response->setResponseContent(responseRContent);
}

