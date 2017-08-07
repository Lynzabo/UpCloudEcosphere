#include "ucgroupassocservlet.h"
#include "util/csgroupandclientutil.h"
#include "../../BusinessIServer/BasalIServer/bean/cscgroupassoc.h"
#include "../../BusinessIServer/BasalIServer/dao/csgroupandclinetdao.h"
using QtJson::JsonArray;
using QtJson::JsonObject;
using namespace Environment::Duplex_Interaction;

UpdateClientGroupAssocServlet::UpdateClientGroupAssocServlet()
{

}

void UpdateClientGroupAssocServlet::doExec(DRequestContext *request, DResponseContext *response)
{
    quint8 responseRState;
    QString uuid;uuid.clear();
    quint8 state;
    QString responseRContent;responseRContent.clear();
    bool ok;
    int i;
    QString result;result.clear();

    //准备参数
    QString params = request->getParams();
    QVariantMap paramsData = QtJson::parse(params,ok).toMap();
    QStringList supList;supList.clear();
    uuid = paramsData.value("uuid").toString();
    state = (quint8)paramsData.value("state").toInt();
    if(!ok) {
        qDebug() << trs("解析参数失败");
        responseRState = Data_Authority::_5;
        responseRContent = Data_Authority::_5_DESC_ParamParseError;
        goto end;
    }
    ////处理业务

    try{
        CsGroupAndClinetDao::updateGroupAssoc(uuid,state);

    }
    catch(DBException &ex){
        Q_UNUSED(ex)
        responseRState = Data_Authority::_4;
        responseRContent = Data_Authority::_4_DESC_DatabaseError;
        goto end;
    }

    responseRState = Data_Authority::_0;
    responseRContent = tr("成功");
end:;
    response->setResponseState(responseRState);
    response->setResponseContent(responseRContent);
}

