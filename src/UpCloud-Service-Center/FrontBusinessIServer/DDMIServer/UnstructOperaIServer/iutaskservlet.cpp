#include "iutaskservlet.h"
#include "util/unstructutil.h"
#include "../../../BusinessIServer/UnstructIServer/dao/csunstructdao.h"
using QtJson::JsonObject;
using QtJson::JsonArray;
using namespace Environment::Duplex_Interaction;

ItemUnstructTaskServlet::ItemUnstructTaskServlet()
{

}

void ItemUnstructTaskServlet::doExec(DRequestContext *request, DResponseContext *response)
{
    quint8 responseState;
    QString responseContent;responseContent.clear();
    QString taskId;
    QString result;
    CsRUnstructTask task;
    ////1.接收客户端传递来参数列表    可选
    QString params = request->getParams();
    bool ok;
    JsonObject paramObj = QtJson::parse(params, ok).toMap();
    //解析参数列表失败
    if (!ok) {
        responseState = Data_Authority::_5;
        responseContent = Data_Authority::_5_DESC_ParamParseError;
        qDebug() << Data_Authority::_5_DESC_ParamParseError;
        goto end;
    }

    taskId = paramObj["taskId"].toString();
    if(taskId.isEmpty())
    {
        responseState = Data_Authority::_7;
        responseContent = Data_Authority::_7_DESC_ParamsHasNullValue;
        qDebug() << Data_Authority::_7_DESC_ParamsHasNullValue;
        goto end;
    }
    ////2.处理业务
    task = CSUnstructDao::getTaskByUUID(taskId);
    UnstructUtil::taskEntityTojsonStr(result,task);
    responseState = Data_Authority::_0;
    responseContent = result;
    ////3.回执
    end:;
    //.返回客户端请求结果集  可选
    response->setResponseState(responseState);
    response->setResponseContent(responseContent);

}

