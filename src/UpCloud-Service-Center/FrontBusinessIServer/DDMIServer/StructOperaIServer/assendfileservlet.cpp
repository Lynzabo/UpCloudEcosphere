#include "assendfileservlet.h"
#include "createftpfileinfo.h"
#include "../../UpCloud-Service-Center/BusinessIServer/StructIServer/bean/csrssendfiles.h"
#include "util/structutil.h"
#include "../../UpCloud-Service-Center/BusinessIServer/StructIServer/dao/csstructdao.h"
using namespace Environment::Duplex_Interaction;
using namespace Environment::Task_Status::Center;
using QtJson::JsonArray;
using QtJson::JsonObject;
using namespace Environment;
AddStructSendFileServlet::AddStructSendFileServlet()
{

}

void AddStructSendFileServlet::doExec(DRequestContext *request, DResponseContext *response)
{
    quint8 responseRState;
    QString responseRContent;responseRContent.clear();
    bool ok;
    int i;
    QString taskUuid;taskUuid.clear();
    QString uuid;
    QList<VCsRStructSendAddr> addrList;
    QList<CsRStructSendStatus> statusList;statusList.clear();
    QStringList newNameList;
    QList<CsRStructSendFiles> fileList;fileList.clear();
    QString params = request->getParams();
    //解析参数列表
    JsonObject json = QtJson::parse(params,ok).toMap();
    if(!ok) {
        responseRState = Data_Authority::_5;
        responseRContent = Data_Authority::_5_DESC_ParamParseError;
        goto end;
    }
    taskUuid = json.value("taskuuid").toString();
    ok = StructUtil::taskEntinyFromjsonStr(fileList,json.value("filelist").toString());
    if(!ok) {
        responseRState = Data_Authority::_5;
        responseRContent = Data_Authority::_5_DESC_ParamParseError;
        goto end;
    }
    ok = StructUtil::taskEntinyFromjsonStr(addrList,json.value("addrList").toString());
    if(!ok) {
        responseRState = Data_Authority::_5;
        responseRContent = Data_Authority::_5_DESC_ParamParseError;
        goto end;
    }
    for(i = 0;i < fileList.size();++i) {
        newNameList.insert(i,fileList.at(i).getFileDestName());
    }
    //查询是否文件信息已存在
    if((CSStructDao::dirRSendFiles(taskUuid,newNameList)).count() > 0) {
        responseRState = Data_Authority::_9;
        goto set;
    }
    //后台增加任务文件信息列表
    //后台增加任务关联列表信息
    for(QList<CsRStructSendFiles>::iterator item = fileList.begin();
        item != fileList.end(); ++item) {
        UuidUtil::nextUUID(uuid);
        item->setUuid(uuid);
        QString fileName = item->getFileName();
        item->setUuid(uuid);
        QString path = item->getSaveAbst();
        QString completeSuffix = QFileInfo(path).completeSuffix();
        UuidUtil::nextUUID(uuid);
        QString fileDestName = uuid + "." + completeSuffix;
        CreateFtpFileInfo fileInfo;
        fileInfo.setFtpInfo(fileName,item->getSaveAbst(),path);
        item->setDownUrl(fileInfo.getDownUrl());
        item->setFileDestName(fileDestName);
        item->setFileSrc(Files_Src_Type::RemoteUI);
        item->setSequence(1);
        item->setHardAbst(fileInfo.getHardAbst());
        foreach(const VCsRStructSendAddr &addr,addrList) {
            CsRStructSendStatus status;
            status.setClientUuid(addr.getClientUuid());
            status.setError("");
            status.setSendFileUuid(item->getUuid());
            status.setSendAddrUuid(addr.getUuid());
            status.setState(Stru::SendStatus_State::USABLE);
            status.setTaskUuid(taskUuid);
            UuidUtil::nextUUID(uuid);
            status.setUuid(uuid);
            statusList.append(status);
        }
    }
    //处理业务
    try{
        CSStructDao::addRSendFiles(taskUuid,fileList,statusList);
    }
    catch(DBException &ex) {
        Q_UNUSED(ex)
        responseRState = Data_Authority::_4;
        responseRContent = Data_Authority::_4_DESC_DatabaseError;
        goto end;
    }
    //准备回执
    responseRState = Data_Authority::_0;
set:;
    fileList = CSStructDao::dirRSendFilesByTaskUUID(taskUuid);
    StructUtil::taskEntinyTojsonStr(responseRContent,fileList);
end:;
    response->setResponseState(responseRState);
    response->setResponseContent(responseRContent);
}

