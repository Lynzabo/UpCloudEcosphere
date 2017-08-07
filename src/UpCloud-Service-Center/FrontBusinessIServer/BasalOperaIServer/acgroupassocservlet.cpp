#include "acgroupassocservlet.h"
#include "util/csgroupandclientutil.h"
#include "../../BusinessIServer/BasalIServer/bean/cscgroupassoc.h"
#include "../../BusinessIServer/BasalIServer/dao/csgroupandclinetdao.h"
using QtJson::JsonArray;
using QtJson::JsonObject;
using namespace Environment::Duplex_Interaction;

AddClientGroupAssocServlet::AddClientGroupAssocServlet()
{

}

void AddClientGroupAssocServlet::doExec(DRequestContext *request, DResponseContext *response)
{
    quint8 responseRState;
    QString curTime;
    QString responseRContent;responseRContent.clear();
    CsClientGroupAssoc task;
    QList<CsClientGroupAssoc> taskList;taskList.clear();
    bool ok;
    qint32 sequence;
    QString params = request->getParams();
    QStringList nodes ;
    QString groupuuid;

    //准备参数
    QVariantMap paramsMap = QtJson::parse(params,ok).toMap();
    if(!ok) {
        qDebug() << trs("解析参数失败");
        responseRState = Data_Authority::_5;
        responseRContent = Data_Authority::_5_DESC_ParamParseError;
        goto end;
    }
    nodes= QtJson::parse(paramsMap.value("clients").toString()).toStringList();
    groupuuid = paramsMap.value("groupuuid").toString();
    sequence = (qint32)paramsMap.value("sequence").toInt();
    //解析参数失败
    if(!ok) {
        qDebug() << trs("解析参数失败");
        responseRState = Data_Authority::_5;
        responseRContent = Data_Authority::_5_DESC_ParamParseError;
        goto end;
    }
    task.setGroupUuid(groupuuid);
    task.setInsertor("zjy");
    task.setState(1);
    task.setSequence(sequence);
    TimerUtil::toString(curTime);
    task.setInsertTime(curTime);
    //直接删除以前的记录，不需要判断
//    //判断添加记录是否存在
//    if(CsGroupAndClinetDao::dirGroupClientAssoc(groupuuid,nodes).size() > 0) {
//        responseRState = Data_Authority::_9;
//        responseRContent = Data_Authority::_9_DESC_RecordIsExsit;
//        goto end;
//    }
    //处理业务
    try{
        CsGroupAndClinetDao::addGroupClientAssoc(task,nodes);
    }
    catch(DBException &ex){
        Q_UNUSED(ex)
        responseRState = Data_Authority::_4;
        responseRContent = Data_Authority::_4_DESC_DatabaseError;
        goto end;
    }
    //处理结果
    responseRState = Data_Authority::_0;
    responseRContent = tr("成功");
end:;
    response->setResponseState(responseRState);
    response->setResponseContent(responseRContent);
}

