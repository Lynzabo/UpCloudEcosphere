#include "mgsequenceservlet.h"
#include "util/csgroupandclientutil.h"
#include "../../BusinessIServer/BasalIServer/bean/cscgroup.h"
#include "../../BusinessIServer/BasalIServer/dao/csgroupandclinetdao.h"
using QtJson::JsonArray;
using QtJson::JsonObject;
using namespace Environment::Duplex_Interaction;

MoveGroupSequenceServlet::MoveGroupSequenceServlet()
{

}

void MoveGroupSequenceServlet::doExec(DRequestContext *request, DResponseContext *response)
{
    quint8 responseRState;
    QString responseRContent;responseRContent.clear();
    bool ok;
    QString result;result.clear();
    int opera_type;
    //准备参数
    QString params = request->getParams();
    QVariantMap groupInfo = QtJson::parse(params,ok).toMap();
    if(!ok)
    {
        responseRState = Data_Authority::_5;
        responseRContent = Data_Authority::_5_DESC_ParamParseError;
        goto end;
    }
    opera_type = groupInfo.value("opera_type").toInt();
    try{

        if(opera_type == 1) {
            CsGroupAndClinetDao::moveNodeToGroupIn(groupInfo);
        }
        else if(opera_type == 2) {
            CsGroupAndClinetDao::moveNodeToGroupOut(groupInfo);
        }
        else if(opera_type == 3) {
            CsGroupAndClinetDao::moveGroupToGroupIn(groupInfo);
        }
        else if(opera_type == 4) {
            CsGroupAndClinetDao::moveGroupToGroupOut(groupInfo);
        }
        else {
            responseRState = Data_Authority::_5;
            responseRContent = Data_Authority::_5_DESC_ParamParseError;
            goto end;
        }
    }
    catch(DBException &excep) {
        Q_UNUSED(excep)
        responseRState = Data_Authority::_4;
        responseRContent = Data_Authority::_4_DESC_DatabaseError;
        goto end;
    }
    responseRState = Data_Authority::_0;
    responseRContent = Data_Authority::_0_DESC_Success;
end:;
    response->setResponseState(responseRState);
    response->setResponseContent(responseRContent);
}

