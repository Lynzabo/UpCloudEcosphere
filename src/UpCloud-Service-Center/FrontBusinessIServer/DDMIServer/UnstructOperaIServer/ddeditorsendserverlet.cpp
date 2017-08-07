#include "ddeditorsendserverlet.h"
#include "baseiserver.h"
using QtJson::JsonObject;
using QtJson::JsonArray;
using namespace Environment::Duplex_Interaction;
using namespace Environment::Datagram::Web_Serverlet::DDEditor;
using namespace Environment::Task_Status::Center;
using namespace Environment::Net_Equip_MainType;
using namespace Environment::EquipState;

DDEditorSendServerlet::DDEditorSendServerlet()
{

}

void DDEditorSendServerlet::doExec(DRequestContext *request, DResponseContext *response)
{
    qDebug() << trs("Web send request arrived");
    ////[0]返回状态及出错内容
    quint8 responseState;
    QString responseContent;responseContent.clear();

    ////[1]生成非结构化,结构化32位UIID
    QString uTaskUUID; uTaskUUID.clear();
    QString sTaskUUID; sTaskUUID.clear();
    UuidUtil::nextUUID(uTaskUUID);
    UuidUtil::nextUUID(sTaskUUID);

    ////[2]定义本次任务实体
    CsRUnstructTask uStructTask;
    QList<CsRUnstructSendAddr*> uStructSendAddrList;
    QList<CsRUnstructSendFiles*> uStructSendFilesList;
    QList<CsRUnstructSendStatus*> uStructSendStatusList;

    CsRStructTask structTask;
    QList<CsRStructSendAddr*> structSendAddrList;
    QList<CsRStructSendFiles*> structSendFilesList;
    QList<CsRStructSendStatus* > structSendStatusList;

    ////[3]接收客户端传递来参数列表, 并解析获得任务实体
    DTask dTask;
    QList<DTaskAddr> dTaskAddrList;
    QList<DTaskFile> dUTaskFileList;
    QList<DTaskFile> dSTaskFileList;

    QString params = request->getParams();
    bool isSuccess;
    isSuccess = UnstructUtil::DTaskDDEditorJsonStrToEntity(params, dTask, dTaskAddrList, dUTaskFileList, dSTaskFileList);
    //解析参数列表失败
    if (isSuccess == false)
    {
        responseState = Data_Authority::_5;
        responseContent = Data_Authority::_5_DESC_ParamParseError;
        qDebug() << Data_Authority::_5_DESC_ParamParseError;
        goto end;
    }

    {
        ////[4]生成本次任务的主任务, 非结构化, 结构化
        //[4].1unstruct
        //UUID
        uStructTask.setUuid(uTaskUUID);
        //任务名称
        uStructTask.setTaskName(dTask.getTaskName());
        //计划任务编号
        quint32 u_taskNum = qrand()%(1 << 31);
        uStructTask.setTaskNum(u_taskNum);
        //任务描述
        uStructTask.setDescription(dTask.getDescription());
        //任务下发时间
        QString u_sendTime;u_sendTime.clear();
        TimerUtil::toString(u_sendTime);
        uStructTask.setSendTime(u_sendTime);
        //下发策略
        uStructTask.setStrategy(dTask.getStrategy());
        uStructTask.setStrategy(quint16(1));
        //任务状态
        uStructTask.setState(Unstru::Task_State::USABLE);
        //添加人
        QString u_insertor;u_insertor.clear();
        u_insertor = trs("Web");
        uStructTask.setInsertor(u_insertor);
        //添加时间
        QString u_insertTime;u_insertTime.clear();
        TimerUtil::toString(u_insertTime);
        uStructTask.setInsertTime(u_insertTime);
        //操作人
        QString u_operater;u_operater.clear();
        u_operater = trs("Web");
        uStructTask.setOperater(u_operater);
        //操作时间
        QString u_operaTime;u_operaTime.clear();
        TimerUtil::toString(u_operaTime);
        uStructTask.setOperaTime(u_operaTime);

        //[4].2 struct
        //UUID
        structTask.setUuid(sTaskUUID);
        //任务名称
        structTask.setTaskName(dTask.getTaskName());
        //计划任务编号
        quint32 s_taskNum = qrand()%(1 << 31);
        structTask.setTaskNum(s_taskNum);
        //任务描述
        structTask.setDescription(dTask.getDescription());
        //任务下发时间
        QString s_sendTime;s_sendTime.clear();
        TimerUtil::toString(s_sendTime);
        structTask.setSendTime(s_sendTime);
        //任务执行时刻
        QString s_execTime;s_execTime.clear();
        TimerUtil::toString(s_execTime);
        structTask.setExecTime(s_execTime);
        //执行策略
        structTask.setStrategy(dTask.getStrategy());
        structTask.setStrategy(quint16(1));
        //任务状态
        structTask.setState(Stru::Task_State::USABLE);
        //添加人
        QString s_insertor;s_insertor.clear();
        s_insertor = trs("Web");
        structTask.setInsertor(s_insertor);
        //添加时间
        QString s_insertTime;s_insertTime.clear();
        TimerUtil::toString(s_insertTime);
        structTask.setInsertTime(s_insertTime);
        //操作人
        QString s_operater;s_operater.clear();
        s_operater = trs("Web");
        structTask.setOperater(s_operater);
        //操作时间
        QString s_operaTime;s_operaTime.clear();
        TimerUtil::toString(s_operaTime);
        structTask.setOperaTime(s_operaTime);

        ////[5]生成本次任务的地址列表, 非结构化, 结构化
        QList<QString> clientAddrUUIDs;clientAddrUUIDs.clear();
        if(dTaskAddrList.size()<=0)
        {
            //TODO 发送给所有的节点服务器(1:状态为USABLE 2:设备类型为DESKTOP_NODER)
            QList<CsTerminal> terminals = CSTerminalDao::listTerminalByStateAndType(USABLE, DESKTOP_NODER);
            if(terminals.size() > 0)
            {
                foreach (CsTerminal terminal, terminals)
                {
                    clientAddrUUIDs.append(QString::number(terminal.getTerminalUUID()));
                }
            }
        }
        else
        {
            //TODO
            QList<QString> groupUUIDs; groupUUIDs.clear();
            for(DTaskAddr dTaskAddr : dTaskAddrList)
            {
                if(dTaskAddr.getIsGroup())
                {
                    //如果是组
                    groupUUIDs.append(dTaskAddr.getAddrUUID());
                }
                else
                {
                    clientAddrUUIDs.append(dTaskAddr.getAddrUUID());
                }

                groupUUIDs.append(dTaskAddr.getAddrUUID());
            }
            CSUnstructDao::getClientAddrByGroupUUID(groupUUIDs, clientAddrUUIDs);
        }

        //[5].1 unstruct
        //任务UUID
        QString uAddr_taskUuid;uAddr_taskUuid.clear();
        uAddr_taskUuid = uStructTask.getUuid();
        //UUID
        QString uAddr_uuid;uAddr_uuid.clear();
        //节点服务地址UUID
        QString uAddr_clientUuid;uAddr_clientUuid.clear();
        //组描述
        QString uAddr_groupDesc;uAddr_groupDesc.clear();


        //[5].2 struct
        //任务UUID
        QString sAddr_taskUuid;sAddr_taskUuid.clear();
        sAddr_taskUuid = structTask.getUuid();
        //UUID
        QString sAddr_uuid;sAddr_uuid.clear();
        //节点服务地址UUID
        QString sAddr_clientUuid;sAddr_clientUuid.clear();
        //组描述
        QString sAddr_groupDesc;sAddr_groupDesc.clear();

        CsRUnstructSendAddr* uStructSendAddr = NULL;
        CsRStructSendAddr* structSendAddr = NULL;

        for(int i=0; i<clientAddrUUIDs.size(); i++)
        {
            uStructSendAddr = new CsRUnstructSendAddr;
            structSendAddr = new CsRStructSendAddr;

            uStructSendAddr->setClientUuid(clientAddrUUIDs.at(i));
            UuidUtil::nextUUID(uAddr_uuid);
            uStructSendAddr->setUuid(uAddr_uuid);
            //TODO 需要获取节点服务器组所属群组的集合
            uStructSendAddr->setGroupDesc("Web_root");
            uStructSendAddr->setTaskUuid(uAddr_taskUuid);


            structSendAddr->setClientUuid(clientAddrUUIDs.at(i));
            UuidUtil::nextUUID(sAddr_uuid);
            structSendAddr->setUuid(sAddr_uuid);
            //TODO 需要获取节点服务器组所属群组的集合
            structSendAddr->setGroupDesc("Web_root");
            structSendAddr->setTaskUuid(sAddr_taskUuid);


            uStructSendAddrList.append(uStructSendAddr);
            structSendAddrList.append(structSendAddr);
        }

        ////[6]创建文件硬链接
        //[6].1 获取Ftp根目录
        QString ftpRoootPath; ftpRoootPath.clear();
        QString ftpAddr;ftpAddr.clear();
        //TODO
        ServerConf serverConf;
        serverConf.getFtpRootPath(ftpRoootPath);
        serverConf.getFtpAddr(ftpAddr);
        //ftpRoootPath = "/opt/data/ftproot/ftpdemo";
        //ftpAddr = "ftp://10.0.0.2/";

        /*
        //[7].2 生成Ftp时间目录
        QString dataPath; dataPath.clear();
        TimerUtil::toString(dataPath,"yyyy-MM-dd");
        QDir dir;
        if(dir.exists(ftpRoootPath + "/" + dataPath) == false)
        {
            dir.mkdir(ftpRoootPath + "/" + dataPath);
        }

        //[7].3生成非结构化-结构化目录名
        QString uAndsPath = trs("非结构化-结构化-%1-%2").arg(uTaskUUID).arg(sTaskUUID);



        //[7].4生成本次任务目录名
        QString taskPath; taskPath.clear();
        taskPath = ftpRoootPath + "/" + dataPath + "/" + uAndsPath;
        if(dir.exists(taskPath) == false)
        {
            dir.mkdir(taskPath);
        }
        */
        QString taskPath; taskPath.clear();
        taskPath = ftpRoootPath;

        //[7].5硬链接文件名 并生成CsRUnstructSendFiles CsRStructSendFiles

        QString srcAbst; srcAbst.clear();
        QString completeSuffix; completeSuffix.clear();

        //[7].5.1 生成CsRUnstructSendFiles
        //UUID
        QString uFile_uuid;uFile_uuid.clear();
        //原文件名
        QString uFile_fileName;uFile_fileName.clear();
        //文件下载地址
        QString uFile_downUrl;uFile_downUrl.clear();
        //新文件名
        QString uFile_fileDestName;uFile_fileDestName.clear();
        //文件保存路径
        QString uFile_saveAbst;uFile_saveAbst.clear();
        //任务UUID
        QString uFile_taskUuid;uFile_taskUuid.clear();
        uFile_taskUuid = uStructTask.getUuid();
        //文件来源
        quint8 uFile_fileSrc;uFile_fileSrc = quint8(0);
        //文件硬链接地址
        QString uFile_hardAbst;uFile_hardAbst.clear();


        CsRUnstructSendFiles* uStructSendFile = NULL;

        QString uHardLinkName; uHardLinkName.clear();

        for(DTaskFile dUTaskFile : dUTaskFileList)
        {
            UuidUtil::nextUUID(uHardLinkName);
            srcAbst = dUTaskFile.getSrcAbst();
            completeSuffix = QFileInfo(srcAbst).completeSuffix();
            uFile_hardAbst = taskPath + "/" + uHardLinkName + "." + completeSuffix;
            //创建硬链接失败
            if(HardLink::creatFileHardLink(srcAbst, uFile_hardAbst) != 0)
            {
                responseState = Send::state::_1;
                responseContent = Send::state::_1_DESC_CreateHardLinkFail;
                qDebug() << Send::state::_1_DESC_CreateHardLinkFail;
                //清空及删除本次任务已创建的目录
                /*
                if(DirUtil::DeleteDirectory(taskPath) == false)
                {
                    responseState = Send::state::_2;
                    responseContent = Send::state::_2_DESC_DestoryDirFail;
                    qDebug() << Send::state::_2_DESC_DestoryDirFail;
                }
                */
                goto end;
            }
            uStructSendFile = new CsRUnstructSendFiles;
            uStructSendFile->setFileName(uHardLinkName + "." + completeSuffix);
            //uStructSendFile->setDownUrl(ftpAddr + dataPath + "/" + uAndsPath + "/" + uHardLinkName + "." + completeSuffix);
            UuidUtil::nextUUID(uFile_uuid);
            uStructSendFile->setUuid(uFile_uuid);
            uStructSendFile->setTaskUuid(uFile_taskUuid);
            uStructSendFile->setFileDestName(dUTaskFile.getFileDestName());
            uStructSendFile->setSaveAbst(dUTaskFile.getSaveAbst());
            uStructSendFile->setFileSrc(uFile_fileSrc);
            uStructSendFile->setHardAbst(uFile_hardAbst);

            uStructSendFile->setDownUrl(ftpAddr + uHardLinkName + "." + completeSuffix);


            uStructSendFilesList.append(uStructSendFile);
        }

        //[7].5.2 生成CsRStructSendFiles
        //UUID
        QString sFile_uuid;sFile_uuid.clear();
        //原文件名
        QString sFile_fileName;sFile_fileName.clear();
        //文件下载地址
        QString sFile_downUrl;sFile_downUrl.clear();
        //新文件名
        QString sFile_fileDestName;sFile_fileDestName.clear();
        //文件保存路径
        QString sFile_saveAbst;sFile_saveAbst.clear();
        //文件解析次序
        quint32 sFile_sequence;sFile_sequence = 0;
        //任务UUID
        QString sFile_taskUuid;sFile_taskUuid.clear();
        sFile_taskUuid = structTask.getUuid();
        //文件来源
        quint8 sFile_fileSrc;sFile_fileSrc = quint8(0);
        //文件硬链接地址
        QString sFile_hardAbst;sFile_hardAbst.clear();

        CsRStructSendFiles* structSendFile = NULL;

        QString sHardLinkName; sHardLinkName.clear();

        DTaskFile tmp_dSTaskFile;
        for(int i=0; i<dSTaskFileList.size(); i++)
        {
            tmp_dSTaskFile = dSTaskFileList.at(i);
            UuidUtil::nextUUID(sHardLinkName);
            srcAbst = tmp_dSTaskFile.getSrcAbst();
            completeSuffix = QFileInfo(srcAbst).completeSuffix();
            sFile_hardAbst = taskPath + "/" + sHardLinkName + "." + completeSuffix;
            //创建硬链接失败
            if(HardLink::creatFileHardLink(srcAbst, sFile_hardAbst) != 0)
            {
                responseState = Send::state::_1;
                responseContent = Send::state::_1_DESC_CreateHardLinkFail;
                qDebug() << Send::state::_1_DESC_CreateHardLinkFail;
                //清空及删除本次任务已创建的目录
                /*
                if(DirUtil::DeleteDirectory(taskPath) == false)
                {
                    responseState = Send::state::_2;
                    responseContent = Send::state::_2_DESC_DestoryDirFail;
                    qDebug() << Send::state::_2_DESC_DestoryDirFail;
                }
                */
                goto end;
            }
            structSendFile = new CsRStructSendFiles;
            structSendFile->setFileName(sHardLinkName + "." + completeSuffix);
            //structSendFile->setDownUrl(ftpAddr + dataPath + "/" + uAndsPath + "/" + sHardLinkName + "." + completeSuffix);
            UuidUtil::nextUUID(sFile_uuid);
            structSendFile->setUuid(sFile_uuid);
            structSendFile->setTaskUuid(sFile_taskUuid);
            structSendFile->setFileDestName(tmp_dSTaskFile.getFileDestName());
            structSendFile->setSaveAbst(tmp_dSTaskFile.getSaveAbst());
            sFile_sequence = (quint32)i;
            structSendFile->setSequence(sFile_sequence);
            structSendFile->setFileSrc(sFile_fileSrc);
            structSendFile->setHardAbst(sFile_hardAbst);

            structSendFile->setDownUrl(ftpAddr + sHardLinkName + "." + completeSuffix);


            structSendFilesList.append(structSendFile);
        }

        //uStructSendStatusList
        //UUID
        QString uStatus_uuid;uStatus_uuid.clear();
        //节点服务地址UUID
        QString uStatus_clientUuid;uStatus_clientUuid.clear();
        //下发文件表UUID
        QString uStatus_sendFileUuid;uStatus_sendFileUuid.clear();
        //错误描述
        QString uStatus_error;uStatus_error.clear();
        //任务UUID
        QString uStatus_taskUuid;uStatus_taskUuid.clear();
        //文件状态
        quint8 uStatus_state;uStatus_state = 0;
        //下发地址表UUID
        QString uStatus_sendAddrUuid;uStatus_sendAddrUuid.clear();

        for(int i=0; i<uStructSendAddrList.size(); i++)
        {
            uStatus_clientUuid = uStructSendAddrList.at(i)->getClientUuid();
            uStatus_sendAddrUuid = uStructSendAddrList.at(i)->getUuid();
            for(int j=0; j< uStructSendFilesList.size(); j++)
            {
                uStatus_taskUuid = uStructSendFilesList.at(j)->getTaskUuid();
                uStatus_sendFileUuid = uStructSendFilesList.at(j)->getUuid();
                UuidUtil::nextUUID(uStatus_uuid);
                uStatus_error.clear();
                uStatus_state = Unstru::SendStatus_State::USABLE;

                CsRUnstructSendStatus* csRUnstructSendStatus = new CsRUnstructSendStatus;
                csRUnstructSendStatus->setUuid(uStatus_uuid);
                csRUnstructSendStatus->setClientUuid(uStatus_clientUuid);
                csRUnstructSendStatus->setSendFileUuid(uStatus_sendFileUuid);
                csRUnstructSendStatus->setError(uStatus_error);
                csRUnstructSendStatus->setTaskUuid(uStatus_taskUuid);
                csRUnstructSendStatus->setState(uStatus_state);
                csRUnstructSendStatus->setSendAddrUuid(uStatus_sendAddrUuid);
                uStructSendStatusList.append(csRUnstructSendStatus);
            }
        }

        //structSendStatusList
        //UUID
        QString sStatus_uuid;sStatus_uuid.clear();
        //节点服务地址UUID
        QString sStatus_clientUuid;sStatus_clientUuid.clear();
        //下发文件表UUID
        QString sStatus_sendFileUuid;sStatus_sendFileUuid.clear();
        //错误描述
        QString sStatus_error;sStatus_error.clear();
        //任务UUID
        QString sStatus_taskUuid;sStatus_taskUuid.clear();
        //下发地址表UUID
        QString sStatus_sendAddrUuid;sStatus_sendAddrUuid.clear();
        //状态
        quint8 sStatus_state;sStatus_state = 0;

        for(int i=0; i<structSendAddrList.size(); i++)
        {
            sStatus_clientUuid = structSendAddrList.at(i)->getClientUuid();
            sStatus_sendAddrUuid = structSendAddrList.at(i)->getUuid();
            for(int j=0; j< structSendFilesList.size(); j++)
            {
                sStatus_taskUuid = structSendFilesList.at(j)->getTaskUuid();
                sStatus_sendFileUuid = structSendFilesList.at(j)->getUuid();
                UuidUtil::nextUUID(sStatus_uuid);
                sStatus_error.clear();
                sStatus_state = Stru::SendStatus_State::USABLE;

                CsRStructSendStatus* csRStructSendStatus = new CsRStructSendStatus;
                csRStructSendStatus->setUuid(sStatus_uuid);
                csRStructSendStatus->setClientUuid(sStatus_clientUuid);
                csRStructSendStatus->setSendFileUuid(sStatus_sendFileUuid);
                csRStructSendStatus->setError(sStatus_error);
                csRStructSendStatus->setTaskUuid(sStatus_taskUuid);
                csRStructSendStatus->setState(sStatus_state);
                csRStructSendStatus->setSendAddrUuid(sStatus_sendAddrUuid);
                structSendStatusList.append(csRStructSendStatus);
            }
        }

        ////[8]执行数据库操作,向数据库中写入任务
        try
        {
            CSUnstructDao::addTaskFromWeb(uStructTask,
                                          uStructSendAddrList,
                                          uStructSendFilesList,
                                          uStructSendStatusList,
                                          structTask,
                                          structSendAddrList,
                                          structSendFilesList,
                                          structSendStatusList);
        }
        catch(DBException& ex)
        {
            Q_UNUSED(ex)
            responseState = Data_Authority::_4;
            responseContent = ex.getText();
            goto end;
        }
        ////[9]准备结果集回执
        JsonObject objJson ;
        objJson["UTaskUUID"] = uStructTask.getUuid();
        objJson["STaskUUID"] = structTask.getUuid();
        responseContent = QtJson::serializeStr(objJson, isSuccess);
        if(isSuccess == true)
        {
            responseState = Data_Authority::_0;
        }
        else
        {
            responseState = Send::state::_3;
            responseContent = Send::state::_3_DESC_CreateRespondJsonFail;
        }
    }
    ////[10]清理资源
    qDeleteAll(uStructSendAddrList);
    uStructSendAddrList.clear();
    qDeleteAll(uStructSendFilesList);
    uStructSendFilesList.clear();
    qDeleteAll(uStructSendStatusList);
    uStructSendStatusList.clear();

    qDeleteAll(structSendAddrList);
    structSendAddrList.clear();
    qDeleteAll(structSendFilesList);
    structSendFilesList.clear();
    qDeleteAll(structSendStatusList);
    structSendStatusList.clear();
    ////[11]回执
end:;
    //.返回客户端请求结果集  可选
    response->setResponseState(responseState);
    response->setResponseContent(responseContent);
}

