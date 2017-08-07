#include "lsfileservlet.h"
#include "../../UpCloud-Service-Center/BusinessIServer/StructIServer/bean/csrssendfiles.h"
#include "util/structutil.h"
#include "../../UpCloud-Service-Center/BusinessIServer/StructIServer/dao/csstructdao.h"
using namespace Environment::Duplex_Interaction;
using QtJson::JsonArray;
using QtJson::JsonObject;

ListStructFileServlet::ListStructFileServlet()
{

}

ListStructFileServlet::~ListStructFileServlet()
{
     delete this->page;
}

void ListStructFileServlet::doInit()
{
    this->page = new Page;
    page->setCurPageNum(1);
    page->setNumPerPage(10);
    page->setOrderFieldName("FILE_NAME");
    page->setOrderField(Qt::DescendingOrder);
}

void ListStructFileServlet::doExec(DRequestContext *request, DResponseContext *response)
{
    quint8 responseRState;
    QString responseRContent;responseRContent.clear();
    QString taskUuid;taskUuid.clear();
    QList<VCsRStructSendFiles> taskList;taskList.clear();
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
        taskList = CSStructDao::pageFileByTaskUuid(taskUuid,this->page);
    }
    catch(DBException &ex) {
        Q_UNUSED(ex)
        responseRState = Data_Authority::_4;
        responseRContent = Data_Authority::_4_DESC_DatabaseError;
        goto end;
    }
    //准备回执
    responseRState = Data_Authority::_0;
    StructUtil::taskEntinyTojsonStr(resultStr,taskList);
    PageUtil::pageEntityTojsonStr(*this->page,resultStr,pageStr);
    resultObj["resultStr"] = taskUuid;
    resultObj["pageStr"] = pageStr;
    responseRContent = QtJson::serialize(resultObj);
    goto end;
paramsError:
    responseRState = Data_Authority::_5;
    responseRContent = Data_Authority::_5_DESC_ParamParseError;
    qDebug() << responseRContent;
    goto end;
end:;
    response->setResponseState(responseRState);
    response->setResponseContent(responseRContent);
}

