#include "lcgroupservlet.h"
#include "util/csgroupandclientutil.h"
#include "../../BusinessIServer/BasalIServer/bean/cscgroup.h"
#include "../../BusinessIServer/BasalIServer/dao/csgroupandclinetdao.h"
using QtJson::JsonArray;
using QtJson::JsonObject;
using namespace Environment::Duplex_Interaction;

ListClinetGroupServlet::ListClinetGroupServlet()
{

}

void ListClinetGroupServlet::doExec(DRequestContext *request, DResponseContext *response)
{
    quint8 responseRState;
    QString responseRContent;responseRContent.clear();
    bool ok;
    QString result;result.clear();
    QList<CsClientGroup> groupList;groupList.clear();

    //准备参数
    QString params = request->getParams();
    QStringList list = QtJson::parse(params,ok).toStringList();
    quint32 page = list.takeLast().toInt();
    if(!ok) {
        qDebug() << trs("解析参数失败");
        responseRState = Data_Authority::_5;
        responseRContent = Data_Authority::_5_DESC_ParamParseError;
        goto end;
    }
    try{
        groupList = CsGroupAndClinetDao::dirGroupClientBySupUuid(list,page);
    }
    catch(DBException &ex){
        Q_UNUSED(ex)
        responseRState = Data_Authority::_4;
        responseRContent = Data_Authority::_4_DESC_DatabaseError;
        goto end;
    }
    //准处理结果 返回修改的子组

        responseRState = Data_Authority::_0;
        CsGroupAndClientUtil::taskEntinyTojsonStr(responseRContent,groupList);
end:;
    response->setResponseState(responseRState);
    response->setResponseContent(responseRContent);
}

