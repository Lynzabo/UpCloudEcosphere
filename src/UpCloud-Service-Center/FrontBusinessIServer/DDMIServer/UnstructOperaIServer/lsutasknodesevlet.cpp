#include "lsutasknodesevlet.h"
#include "avro.h"
#include "util/unstructutil.h"
#include "../../../BusinessIServer/UnstructIServer/bean/csrusendfiles.h"
#include "../../../BusinessIServer/UnstructIServer/bean/vcsrusendaddr.h"
#include "../../../BusinessIServer/UnstructIServer/dao/csunstructdao.h"
using QtJson::JsonObject;
using QtJson::JsonArray;
using namespace Environment::Duplex_Interaction;

ListSevUnstructTaskNodeSevlet::ListSevUnstructTaskNodeSevlet()
{

}

ListSevUnstructTaskNodeSevlet::~ListSevUnstructTaskNodeSevlet()
{
    delete this->page;
}

void ListSevUnstructTaskNodeSevlet::doInit()
{
    this->page = new Page;
    page->setCurPageNum(1);
    page->setNumPerPage(10);
    page->setOrderFieldName("CLIENT_UUID");
    page->setOrderField(Qt::DescendingOrder);
}

void ListSevUnstructTaskNodeSevlet::doExec(DRequestContext *request, DResponseContext *response)
{
    quint8 requestState;
    QString responseContant;responseContant.clear();
    QList<VCsRUnstructSendAddr> vAddrList;
    QString taskUuid;taskUuid.clear();
    QString pageStr;pageStr.clear();
    QString resultStr;resultStr.clear();
    JsonObject resultObj;resultObj.clear();
    bool ok;
    QString params = request->getParams();
    //分页和查询参数解析
    JsonObject paramsObj = QtJson::parse(params,ok).toMap();
    if(!ok) {
        goto paramsError;
    }
    //查询参数
    taskUuid =  paramsObj["taskUuid"].toString();
    pageStr = paramsObj["pageStr"].toString();
    if(!pageStr.isEmpty())
        ok = PageUtil::pageEntityFromjsonStr(pageStr,*this->page);
    if(!ok) {
        goto paramsError;
    }

    try{
        vAddrList = CSUnstructDao::pageAddrByTaskUuid(taskUuid,this->page);
    }
    catch(DBException ex){
        Q_UNUSED(ex)
        requestState = Data_Authority::_4;
        responseContant = Data_Authority::_4_DESC_DatabaseError;
        goto end;
    }


    requestState = Data_Authority::_0;
    UnstructUtil::taskVAddrEntityTojsonStr(resultStr,vAddrList);
    PageUtil::pageEntityTojsonStr(*this->page,resultStr,pageStr);
    resultObj["resultStr"] = taskUuid;
    resultObj["pageStr"] = pageStr;
    responseContant = QtJson::serialize(resultObj);
    goto end;
paramsError:
    requestState = Data_Authority::_5;
    responseContant = Data_Authority::_5_DESC_ParamParseError;
    qDebug() << responseContant;
    goto end;
end:
    response->setResponseState(requestState);
    response->setResponseContent(responseContant);
}

