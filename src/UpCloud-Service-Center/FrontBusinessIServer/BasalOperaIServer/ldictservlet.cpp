#include "ldictservlet.h"
#include "util/dictutil.h"
#include "../../../UpCloud-Service-Center/BusinessIServer/BasalIServer/bean/csdict.h"
#include "../../../UpCloud-Service-Center/BusinessIServer/BasalIServer/dao/csdictdao.h"
using QtJson::JsonArray;
using QtJson::JsonObject;
using namespace Environment::Duplex_Interaction;

ListDictServlet::ListDictServlet()
{

}

ListDictServlet::~ListDictServlet()
{
    delete page;
}

void ListDictServlet::doInit()
{
    page = new Page;
    page->setCurPageNum(1);
    page->setNumPerPage(10);
    page->setOrderField(Qt::AscendingOrder);
    page->setOrderFieldName("SUP_UUID");
}

void ListDictServlet::doExec(DRequestContext *request, DResponseContext *response)
{

    quint8 responseRState;
    QString responseRContent;responseRContent.clear();
    QList<CsDict> dictList;
    QString paramsStr;paramsStr.clear();
    QString pageStr;pageStr.clear();
    JsonObject paramsObj;paramsObj.clear();
    QString resultStr;resultStr.clear();
    JsonObject resultObj;resultObj.clear();
    bool ok;
    //获取参数列表
    QString params = request->getParams();

    //参数+分页数据
    QVariantMap requestParamsObj = QtJson::parse(params, ok).toMap();
    if(!ok)
    {
        goto paramsError;
    }
    //解析参数列表
    paramsStr = requestParamsObj["paramsStr"].toString();
    paramsObj = QtJson::parse(paramsStr, ok).toMap();
    if(!ok)
    {
        goto paramsError;
    }
    //解析分页数据
    pageStr = requestParamsObj["pageStr"].toString();
    if(!pageStr.isEmpty())
        ok = PageUtil::pageEntityFromjsonStr(pageStr,*this->page);

    if(!ok) {
        responseRState = Data_Authority::_5;
        responseRContent = Data_Authority::_5_DESC_ParamParseError;
        goto end;
    }
    try{
        //判断是否使用分页
        if(paramsObj.keys().contains("closeFilter")) {
            //不使用分页
            dictList = CSDictDao::dirCsDict(paramsObj);
        }
        else {
            //分页
            dictList = CSDictDao::pageDict(paramsObj,this->page);
        }
    }
    catch(DBException ex){
        Q_UNUSED(ex)
        responseRState = Data_Authority::_4;
        responseRContent = Data_Authority::_4_DESC_DatabaseError;
        goto end;
    }
    responseRState = Data_Authority::_0;
    //组装分页数据
    DictUtil::taskEntinyTojsonStr(resultStr,dictList);
    PageUtil::pageEntityTojsonStr(*page,resultStr,pageStr);
    resultObj["paramsStr"] = paramsStr;
    resultObj["pageStr"] = pageStr;
    responseRContent = QtJson::serialize(resultObj);
    goto end;
paramsError:
    responseRState = Data_Authority::_5;
    responseRContent = Data_Authority::_5_DESC_ParamParseError;
    qDebug() << Data_Authority::_5_DESC_ParamParseError;
    goto end;

end:;
    response->setResponseState(responseRState);
    response->setResponseContent(responseRContent);
}

