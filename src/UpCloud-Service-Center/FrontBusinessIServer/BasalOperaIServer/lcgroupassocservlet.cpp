#include "lcgroupassocservlet.h"
#include "util/csgroupandclientutil.h"
#include "../../BusinessIServer/BasalIServer/bean/vcscgroupassoc.h"
#include "../../BusinessIServer/BasalIServer/dao/csgroupandclinetdao.h"
using QtJson::JsonArray;
using QtJson::JsonObject;
using namespace Environment::Duplex_Interaction;
ListClinetGroupAssocServlet::ListClinetGroupAssocServlet()
{

}

void ListClinetGroupAssocServlet::doExec(DRequestContext *request, DResponseContext *response)
{
    quint8 responseRState;
    QString uuid;uuid.clear();
    QStringList groupList;groupList.clear();
    QString sup_uuid;sup_uuid.clear();
    QString responseRContent;responseRContent.clear();
    bool ok;
    int i;
    QString result;result.clear();
    QList<VCsClientGroupAssoc> taskList_node;taskList_node.clear();
    QList<CsClientGroup> taskList;taskList.clear();

    //准备参数
    QString params = request->getParams();
    JsonObject sup = QtJson::parse(params,ok).toMap();
    QStringList supList;supList.clear();
    quint32 page;
    supList.append(sup.value("supuuid").toString());
    page = sup.value("page").toInt();
    if(!ok) {
        qDebug() << trs("解析参数失败");
        responseRState = Data_Authority::_5;
        responseRContent = Data_Authority::_5_DESC_ParamParseError;
        goto end;
    }
    ////处理业务
    //查询所有组
    if(!sup.value("supuuid").toString().isEmpty()){
        try{
            taskList = CsGroupAndClinetDao::dirGroupClient(supList);

        }
        catch(DBException &ex){
            Q_UNUSED(ex)
            responseRState = Data_Authority::_4;
            responseRContent = Data_Authority::_4_DESC_DatabaseError;
            goto end;
        }

        //查询群组的节点服务表
        for(i = 0;i < taskList.size();i++) {
            groupList.push_back(taskList.at(i).getUuid());
        }
        try{

            taskList_node.append(CsGroupAndClinetDao::dirGroupClientAssoc(groupList,page));
        }
        catch(DBException &ex){
            Q_UNUSED(ex)
            responseRState = Data_Authority::_4;
            responseRContent = Data_Authority::_4_DESC_DatabaseError;
            goto end;
        }
        //准处理结果 返回修改的子组
    }
    else {
        try{

            taskList_node = CsGroupAndClinetDao::dirGroupClientAssoc({},page);
        }
        catch(DBException &ex){
            Q_UNUSED(ex)
            responseRState = Data_Authority::_4;
            responseRContent = Data_Authority::_4_DESC_DatabaseError;
            goto end;
        }
    }
    responseRState = Data_Authority::_0;
    CsGroupAndClientUtil::taskEntinyTojsonStr(responseRContent,taskList_node);
end:;
    response->setResponseState(responseRState);
    response->setResponseContent(responseRContent);
}

