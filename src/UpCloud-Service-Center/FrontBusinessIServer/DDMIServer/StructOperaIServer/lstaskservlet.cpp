#include "lstaskservlet.h"
#include "../../UpCloud-Service-Center/BusinessIServer/StructIServer/bean/csrstask.h"
#include "util/structutil.h"
#include "../../UpCloud-Service-Center/BusinessIServer/StructIServer/dao/csstructdao.h"
using namespace Environment::Duplex_Interaction;
using QtJson::JsonArray;
using QtJson::JsonObject;

ListStructTaskServlet::ListStructTaskServlet()
{

}

ListStructTaskServlet::~ListStructTaskServlet()
{
    delete this->page;
}

void ListStructTaskServlet::doInit()
{
    page = new Page;
    //设置当前页码
    page->setCurPageNum(1);
    //设置每页显示条数
    page->setNumPerPage(10);
    page->setOrderFieldName("STATE");
    page->setOrderField(Qt::DescendingOrder);
}

void ListStructTaskServlet::doExec(DRequestContext *request, DResponseContext *response)
{
    quint8 responseState;
    QString responseContent;responseContent.clear();
    QList<CsRStructTask> taskList;
    //查询参数列表
    QString paramsStr;
    QVariantMap paramsObj;
    //分页page json串
    QString pageStr;pageStr.clear();
    QString params = request->getParams();
    bool ok;
    //结果集
    QString resultStr;resultStr.clear();
    //回执数据列表
    QVariantMap resultObj;resultObj.clear();
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
    if(!ok)
    {
        goto paramsError;
    }
    //获取分页列表数据
    try{
        taskList = CSStructDao::pageTask(paramsObj,this->page);
    }
    catch(DBException &ex) {
        Q_UNUSED(ex)
        responseState = Data_Authority::_4;
        responseContent = Data_Authority::_4_DESC_DatabaseError;
        goto end;
    }
    responseState = Data_Authority::_0;
    //组装分页数据
    StructUtil::taskEntinyTojsonStr(resultStr,taskList);
    PageUtil::pageEntityTojsonStr(*page,resultStr,pageStr);
    resultObj["paramsStr"] = paramsStr;
    resultObj["pageStr"] = pageStr;
    responseContent = QtJson::serialize(resultObj);
    goto end;
paramsError:
    responseState = Data_Authority::_5;
    responseContent = Data_Authority::_5_DESC_ParamParseError;
    qDebug() << Data_Authority::_5_DESC_ParamParseError;
    goto end;
end:;
    response->setResponseState(responseState);
    response->setResponseContent(responseContent);
}

