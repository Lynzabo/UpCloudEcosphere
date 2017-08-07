#include "dstaskfilesservlet.h"
#include "util/scheduleutil.h"
#include "../../../BusinessIServer/ScheduleIServer/bean/csrscsendfiles.h"
#include "../../../BusinessIServer/ScheduleIServer/dao/csscheduledao.h"
using namespace Environment::Duplex_Interaction;
using QtJson::JsonArray;
using QtJson::JsonObject;
DelScheduleTaskFilesServlet::DelScheduleTaskFilesServlet()
{

}

void DelScheduleTaskFilesServlet::doExec(DRequestContext *request, DResponseContext *response)
{
    QString responseRContent;
    quint16 responseRState;
    QStringList uuids;uuids.clear();
    bool ok = false;
    //获取参数反序列化
    QString params = request->getParams();
    uuids = QtJson::parse(params,ok).toStringList();
    if(!ok)
    {
        responseRState = Data_Authority::_5;
        responseRContent = Data_Authority::_5_DESC_ParamParseError;
        goto end;
    }
    //处理业务
    try{
          CSScheduleDao::delTaskFiles(uuids);
    }
    catch(DBException &ex) {
        Q_UNUSED(ex)
        responseRState = Data_Authority::_4;
        responseRContent = Data_Authority::_4_DESC_DatabaseError;
        goto end;
    }
    responseRState = Data_Authority::_0;
    responseRContent = trs("成功");
end:;
    response->setResponseContent(responseRContent);
    response->setResponseState(responseRState);
}

