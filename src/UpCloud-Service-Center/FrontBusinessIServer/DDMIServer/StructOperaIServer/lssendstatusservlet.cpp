#include "lssendstatusservlet.h"
#include "../../UpCloud-Service-Center/BusinessIServer/StructIServer/bean/csrssendstatus.h"
#include "util/structutil.h"
#include "../../UpCloud-Service-Center/BusinessIServer/StructIServer/dao/csstructdao.h"
using namespace Environment::Duplex_Interaction;
using QtJson::JsonArray;
using QtJson::JsonObject;
ListStructSendStatusServlet::ListStructSendStatusServlet()
{

}

ListStructSendStatusServlet::~ListStructSendStatusServlet()
{
    delete this->page;
}

void ListStructSendStatusServlet::doInit()
{
    this->page = new Page;
    page->setCurPageNum(1);
    page->setNumPerPage(10);
    page->setOrderFieldName("UUID");
    page->setOrderField(Qt::DescendingOrder);
}

void ListStructSendStatusServlet::doExec(DRequestContext *request, DResponseContext *response)
{
    quint8 responseRState;
    QString responseRContent;responseRContent.clear();
    bool ok;
    QString taskUuid;taskUuid.clear();
    QString clientUuid;clientUuid.clear();
    QString fileName;fileName.clear();
    QStringList nameList;
    QString pageStr;pageStr.clear();
    QString resultStr;resultStr.clear();
    JsonObject resultSet;resultSet.clear();
    JsonObject json;json.clear();
    JsonObject resultObj;resultObj.clear();
    QString statusStr;statusStr.clear();
    QString paramsStr;paramsStr.clear();
    QString paramsObj;paramsObj.clear();
    QString resultNameList;resultNameList.clear();
    QList<CsRStructSendStatus> statusList;
    QString params = request->getParams();
    //解析参数列表
    JsonObject jsonObj = QtJson::parse(params,ok).toMap();
    if(!ok) {
        goto paramsError;
    }

    paramsObj = jsonObj.value("paramsObj").toString();
    json = QtJson::parse(paramsObj,ok).toMap();
    if(!ok) {
        goto paramsError;
    }
    if(json.contains("clientUuid")) {
        clientUuid = json.value("clientUuid").toString();
    }
    else {
        fileName = json.value("fileName").toString();
    }

    taskUuid = json.value("taskUuid").toString();
    if(!pageStr.isEmpty())
        ok = PageUtil::pageEntityFromjsonStr(pageStr,*this->page);
    if(!ok) {
        goto paramsError;
    }
    //处理业务
    try{
        if(fileName.isEmpty()) {
           statusList = CSStructDao::pageRSendStatusByTaskUuidAndClientUuid(taskUuid,clientUuid,nameList,this->page);
        }
        else {
           statusList =  CSStructDao::pageRSendStatusByTaskUuidAndSendFileUUid(taskUuid,fileName,nameList,this->page);
        }
    }
    catch(DBException &ex) {
        Q_UNUSED(ex)
        responseRState = Data_Authority::_4;
        responseRContent = Data_Authority::_4_DESC_DatabaseError;
        goto end;
    }
    //准备回执
    responseRState = Data_Authority::_0;
    //返回查询结果
    StructUtil::taskSendStatusEntityTojsonStr(statusStr,statusList);
    resultNameList = QtJson::serialize(nameList);
    resultObj["statusStr"] = statusStr;
    resultObj["nameList"] = resultNameList;
    resultStr = QtJson::serialize(resultObj);
    //返回查询条件
    if(json.contains("clientUuid")) {
        json["clientUuid"] = clientUuid;
    }
    else {
        json["fileName"] = fileName;
    }
    jsonObj.clear();
    json["taskUuid"] = taskUuid;
    paramsStr = QtJson::serialize(json);
    jsonObj.insert("paramsObj",paramsStr);
    //返回分页结果
    PageUtil::pageEntityTojsonStr(*this->page,resultStr,pageStr);
    jsonObj.insert("pageStr",pageStr);
    responseRContent = QtJson::serialize(jsonObj);
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

