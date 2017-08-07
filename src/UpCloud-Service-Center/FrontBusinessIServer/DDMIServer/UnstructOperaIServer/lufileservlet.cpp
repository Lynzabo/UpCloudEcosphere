#include "lufileservlet.h"
#include "avro.h"
#include "util/unstructutil.h"
#include "../../../BusinessIServer/UnstructIServer/bean/csrusendfiles.h"
#include "../../../BusinessIServer/UnstructIServer/dao/csunstructdao.h"
#include "../../../BusinessIServer/UnstructIServer/bean/vcsrusendfiles.h"
using QtJson::JsonObject;
using QtJson::JsonArray;
using namespace Environment::Duplex_Interaction;

ListUnstructFileServlet::ListUnstructFileServlet()
{

}

ListUnstructFileServlet::~ListUnstructFileServlet()
{
    delete this->page;
}

void ListUnstructFileServlet::doInit()
{
    this->page = new Page;
    page->setCurPageNum(1);
    page->setNumPerPage(10);
    page->setOrderFieldName("FILE_NAME");
    page->setOrderField(Qt::DescendingOrder);
}

void ListUnstructFileServlet::doExec(DRequestContext *request, DResponseContext *response)
{
    quint8 responseRState;
    QString responseRContent;responseRContent.clear();
    QString taskUuid;taskUuid.clear();
    QList<VCsRUnstructSendFiles> taskList;taskList.clear();
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
        taskList =  CSUnstructDao::pageFileByTaskUuid(taskUuid,this->page);
    }
    catch(DBException &ex) {
        Q_UNUSED(ex)
        responseRState = Data_Authority::_4;
        responseRContent = Data_Authority::_4_DESC_DatabaseError;
        goto end;
    }
    //准备回执
    responseRState = Data_Authority::_0;
    UnstructUtil::taskVAddrFileEntityTojsonStr(resultStr,taskList);
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

