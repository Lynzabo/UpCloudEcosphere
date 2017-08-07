#include "lvscfilesservlet.h"
#include "util/scheduleutil.h"
#include "../../../BusinessIServer/ScheduleIServer/bean/vcsascsendfiles.h"
#include "../../../BusinessIServer/ScheduleIServer/dao/csscheduledao.h"
using namespace Environment::Duplex_Interaction;
using QtJson::JsonArray;
using QtJson::JsonObject;

ListVCsAScSendFilesServlet::ListVCsAScSendFilesServlet()
{

}

void ListVCsAScSendFilesServlet::doExec(DRequestContext *request, DResponseContext *response)
{
    QString responseRContent;
    quint16 responseRState;
    QList<VCsAScSendFiles> vFileList;
    bool ok = false;
    //获取参数反序列化
    QString params = request->getParams();
    QString uuid = QtJson::parse(params,ok).toString();
    if(!ok)
    {
        responseRState = Data_Authority::_5;
        responseRContent = Data_Authority::_5_DESC_ParamParseError;
        goto end;
    }
    //处理业务
    try{
         vFileList = CSScheduleDao::listVFile(uuid);
    }
    catch(DBException &ex) {
        Q_UNUSED(ex)
        responseRState = Data_Authority::_4;
        responseRContent = Data_Authority::_4_DESC_DatabaseError;
        goto end;
    }
    responseRState = Data_Authority::_0;
    ScheduleUtil::vFileListEntinyToJson(responseRContent,vFileList);
end:;
    response->setResponseContent(responseRContent);
    response->setResponseState(responseRState);
}

