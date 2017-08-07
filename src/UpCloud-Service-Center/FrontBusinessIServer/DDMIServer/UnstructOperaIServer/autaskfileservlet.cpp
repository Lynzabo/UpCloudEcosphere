#include "autaskfileservlet.h"
#include "avro.h"
#include "util/unstructutil.h"
#include "createftpfileinfo.h"
#include "../../../BusinessIServer/UnstructIServer/bean/csrusendfiles.h"
#include "../../../BusinessIServer/UnstructIServer/dao/csunstructdao.h"
using QtJson::JsonObject;
using QtJson::JsonArray;
using namespace Environment::Duplex_Interaction;
using namespace Environment::Task_Status::Center;
using namespace Environment;
AddUnstructTaskFileServlet::AddUnstructTaskFileServlet()
{

}

void AddUnstructTaskFileServlet::doExec(DRequestContext *request, DResponseContext *response)
{
    quint8 responseRState;
    QString responseRContent;responseRContent.clear();
    bool ok;
    int i;
    QString taskUuid;taskUuid.clear();
    QStringList newNameList;
    QString uuid;
    QList<CsRUnstructSendFiles> fileList;fileList.clear();
    QList<VCsRUnstructSendAddr> addrList;addrList.clear();
    QList<CsRUnstructSendStatus> statusList;statusList.clear();
    QString params = request->getParams();
    //解析参数列表
    JsonObject json = QtJson::parse(params,ok).toMap();
    if(!ok) {
        responseRState = Data_Authority::_5;
        responseRContent = Data_Authority::_5_DESC_ParamParseError;
        goto end;
    }
    taskUuid = json.value("taskuuid").toString();
    ok = UnstructUtil::taskAddrFileEntityFromjsonStr(fileList,json.value("filelist").toString());
    if(!ok) {
        responseRState = Data_Authority::_5;
        responseRContent = Data_Authority::_5_DESC_ParamParseError;
        goto end;
    }
    ok = UnstructUtil::taskVAddrEntityFromjsonStr(addrList,json.value("addrList").toString());
    if(!ok) {
        responseRState = Data_Authority::_5;
        responseRContent = Data_Authority::_5_DESC_ParamParseError;
        goto end;
    }
    for(i = 0;i < fileList.size();++i) {
        newNameList.insert(i,fileList.at(i).getFileDestName());
    }
    //查询是否文件信息已存在
    if((CSUnstructDao::dirRSendFiles(taskUuid,newNameList)).count() > 0) {
        responseRState = Data_Authority::_9;
        goto set;
    }
    //后台生成添加任务关联列表信息
    //后台生成添加任务文件列表信息
    for(QList<CsRUnstructSendFiles>::iterator item = fileList.begin();
        item != fileList.end(); ++item) {
        UuidUtil::nextUUID(uuid);
        item->setUuid(uuid);
        QString fileName = item->getFileName();
        QString filePath = item->getSaveAbst();
        QString completeSuffix = QFileInfo(fileName).completeSuffix();
        UuidUtil::nextUUID(uuid);
        QString fileDestName = uuid + "." + completeSuffix;
        CreateFtpFileInfo fileInfo;
        fileInfo.setFtpInfo(fileName,item->getSaveAbst(),filePath);
        item->setDownUrl(fileInfo.getDownUrl());
        item->setFileDestName(fileDestName);
        item->setFileSrc(Files_Src_Type::RemoteUI);
        item->setHardAbst(fileInfo.getHardAbst());
        foreach(const VCsRUnstructSendAddr &addr,addrList) {
            CsRUnstructSendStatus status;
            status.setClientUuid(addr.getClientUuid());
            status.setError("");
            status.setSendFileUuid(item->getUuid());
            status.setSendAddrUuid(addr.getUuid());
            status.setState(Unstru::SendStatus_State::USABLE);
            status.setTaskUuid(taskUuid);
            UuidUtil::nextUUID(uuid);
            status.setUuid(uuid);
            statusList.append(status);
        }
    }

    //处理业务
    try{
        CSUnstructDao::addTaskFile(taskUuid,fileList,statusList);
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
    fileList = CSUnstructDao::dirRSendFilesByTaskUUID(taskUuid);
    UnstructUtil::taskAddrFileEntityTojsonStr(responseRContent,fileList);
end:;
    response->setResponseState(responseRState);
    response->setResponseContent(responseRContent);
}

