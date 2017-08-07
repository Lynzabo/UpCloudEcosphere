#include "istaskservlet.h"
#include "../../UpCloud-Service-Center/BusinessIServer/StructIServer/bean/csrstask.h"
#include "util/structutil.h"
#include "../../UpCloud-Service-Center/BusinessIServer/StructIServer/dao/csstructdao.h"
using namespace Environment::Duplex_Interaction;
using QtJson::JsonArray;
using QtJson::JsonObject;

ItemStructTaskServlet::ItemStructTaskServlet()
{

}

void ItemStructTaskServlet::doExec(DRequestContext *request, DResponseContext *response)
{
    quint8 responseRState;
    QString responseRContent;responseRContent.clear();
    bool ok;
    CsRStructTask task;
    task.clear();
    QString uuid;uuid.clear();
    QString params = request->getParams();
    //解析参数列表
    JsonObject json = QtJson::parse(params,ok).toMap();
    if(!ok) {
        responseRState = Data_Authority::_5;
        responseRContent = Data_Authority::_5_DESC_ParamParseError;
        goto end;
    }
    uuid = json.value("uuid").toString();
    //处理业务
    try{
        task = CSStructDao::dirRTaskByUUid(uuid);
    }
    catch(DBException &ex) {
        Q_UNUSED(ex)
        responseRState = Data_Authority::_4;
        responseRContent = Data_Authority::_4_DESC_DatabaseError;
        goto end;
    }
    //准备回执
    responseRState = Data_Authority::_0;
    StructUtil::taskEntinyTojsonStr(responseRContent,task);
end:;
    response->setResponseState(responseRState);
    response->setResponseContent(responseRContent);
}

