#include "lsaddrservlet.h"
#include "../../UpCloud-Service-Center/BusinessIServer/StructIServer/bean/csrssendaddr.h"
#include "util/structutil.h"
#include "../../UpCloud-Service-Center/BusinessIServer/StructIServer/dao/csstructdao.h"
using namespace Environment::Duplex_Interaction;
using QtJson::JsonArray;
using QtJson::JsonObject;

ListStructAddrServlet::ListStructAddrServlet()
{

}

ListStructAddrServlet::~ListStructAddrServlet()
{
     delete this->page;
}

void ListStructAddrServlet::doInit()
{
    this->page = new Page;
    page->setCurPageNum(1);
    page->setNumPerPage(10);
    page->setOrderFieldName("CLIENT_UUID");
    page->setOrderField(Qt::DescendingOrder);
}

void ListStructAddrServlet::doExec(DRequestContext *request, DResponseContext *response)
{
    quint8 requestState;
    QString responseContant;responseContant.clear();
    QList<VCsRStructSendAddr> vAddrList;
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

    //处理业务
    try{
        vAddrList = CSStructDao::pageAddrByTaskUuid(taskUuid,this->page);
    }
    catch(DBException &ex) {
        Q_UNUSED(ex)
        requestState = Data_Authority::_4;
        responseContant = Data_Authority::_4_DESC_DatabaseError;
        goto end;
    }
    requestState = Data_Authority::_0;
    StructUtil::taskEntinyTojsonStr(resultStr,vAddrList);
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
end:;
    response->setResponseState(requestState);
    response->setResponseContent(responseContant);
}

