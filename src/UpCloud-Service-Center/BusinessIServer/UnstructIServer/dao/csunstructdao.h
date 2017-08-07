#ifndef CSUNSTRUCTDAO_H
#define CSUNSTRUCTDAO_H
#include "base.h"
#include "db.h"
#include "transmsg.h"
#include "../bean/csrutask.h"
#include "../bean/csrusendfiles.h"
#include "../bean/csrusendaddr.h"
#include "../bean/csrusendstatus.h"

#include "../bean/cssutask.h"
#include "../bean/cssusendaddr.h"
#include "../bean/cssusendfiles.h"

#include "../bean/vcsrusendaddr.h"
#include "../bean/vcsrusendfiles.h"

#include "../../StructIServer/bean/csrssendaddr.h"
#include "../../StructIServer/bean/csrssendfiles.h"
#include "../../StructIServer/bean/csrssendstatus.h"
#include "../../StructIServer/bean/csrstask.h"
#include "../../StructIServer/bean/cssssendaddr.h"
#include "../../StructIServer/bean/cssssendfiles.h"
#include "../../StructIServer/bean/cssstask.h"

class CSUnstructDao
{
public:

    /**
     * @brief getTaskByUUID 根据任务UUID获取任务信息
     * @param taskUUID
     * @return
     */
    static CsRUnstructTask getTaskByUUID(const QString &taskUUID);

    /**
     * @brief listTask 根据TaskUUID和state获取任务列表
     * @param taskUUID
     * @param state
     * @return
     */
    static QList<CsRUnstructTask> listTask(const QString &taskUUID,const quint8 state);

    /**
     * @brief dirRSendAddr 查询当前任务指定的clientUUID的一组记录
     * @param taskUuid
     * @param uuids
     * @return
     */
    static QList<CsRUnstructSendAddr> dirRSendAddr(const QString &taskUuid,const QStringList &uuids);
    /**
     * @brief addRSendAddr  为当前任务添加指定的一组节点服务器
     * @param taskUuid
     * @param uuids
     */
    static void addRSendAddr(const QString &taskUuid, const QStringList &uuids, const QStringList &groupDes);
    /**
     * @brief dirRSendAddrsByTaskUUIDandUUID 获取指定节点服务器的一条记录
     * @param taskUUID
     * @param UUID
     * @return
     */
    static CsRUnstructSendAddr dirRSendAddrsByTaskUUIDandUUID(const QString &taskUUID,const QString &clientUUID);
    /**
     * @brief addTask 添加任务
     * @param task
     * @param addrInfoList
     * @param fileInfoList
     * @param statusInfoList
     */
    static void addTask(const CsRUnstructTask &task,const QList<CsRUnstructSendAddr> addrInfoList,
                        const QList<CsRUnstructSendFiles> fileInfoList,
                        const QList<CsRUnstructSendStatus> statusInfoList);
    /**
     * @brief addTaskFile 在当前任务下 添加任务文件
     * @param taskUuid
     * @param taskList
     */
    static void addTaskFile(const QString &taskUuid, const QList<CsRUnstructSendFiles> &taskList, const QList<CsRUnstructSendStatus> &statusList);
    /**
    * @brief addTask 添加节点服务器
    * @param task
    * @return
    */
    static void addTaskNode(const CsRUnstructSendAddr &task);

    /**
     * @brief delTask 删除任务节点服务器
     * @param taskUUID、
     * @param clientUUID
     * @return
     */
    static void delTaskNode(const QString &taskUUID, const QStringList &nodes);
    /**
     * @brief dirRSendFiles 查询指定的任务文件
     * @param taskUuid
     * @param uuids
     * @return
     */
    static QList<CsRUnstructSendFiles> dirRSendFiles(const QString &taskUuid,const QStringList &uuids);
    /**
     * @brief dirRSendFilesByTaskUUIDandFileName 查询指定的任务文件
     * @param taskUUID
     * @param fileName
     * @return
     */
    static CsRUnstructSendFiles dirRSendFilesByTaskUUIDandFileName(const QString &taskUUID,const QString &fileName);
    /**
     * @brief dirRSendStatusByTaskUuidAndClientUuid 查询关联地址表 并查询对应的文件名
     * @param taskUuid   任务UUID
     * @param clientUuid  节点服务器UUID
     * @param paramsList  文件名列表（输出参数）
     * @return
     */
    static QList<CsRUnstructSendStatus> pageRSendStatusByTaskUuidAndClientUuid(const QString &taskUuid, const QString &clientUuid, QStringList &paramsList, Page *page);
    /**
     * @brief dirRSendStatusByTaskUuidAndSendFileUUid  查询关联地址表 并查询对应的节点服务器名
     * @param taskUuid  任务UUID
     * @param fileUuids  文件名
     * @param paramsList  节点服务器名列表
     * @return
     */
    static QList<CsRUnstructSendStatus> pageRSendStatusByTaskUuidAndSendFileUUid(const QString &taskUuid, const QString &fileUuids, QStringList &paramsList, Page *page);
    /**
     * @brief delTaskFile 删除指定的任务文件
     * @param taskUUID
     * @return
     */
    static void delTaskFile(const QString &taskUUID,const QStringList &uuidList);
    /**
     * @brief pageTask  分页查询非结构化任务
     * @param map
     * @param page
     * @return
     */
    static QList<CsRUnstructTask> pageTask(const QVariantMap & map,Page *page);
    /**
     * @brief listTask 专为界面查询的任务
     * @param map
     * @return
     */
    static QList<CsRUnstructTask> listTask(const QVariantMap & map);
    /**
     * @brief delTask 删除任务
     * @param taskUUID
     * @return
     */

    static void delTask(const QStringList &uuids);
    static QList<CsRUnstructSendStatus> dirSendStatusByTaskUuid(const QString &taskUuid);
    /**
     * @brief dirTaskByUUID 获取指定的非结构任务
     * @param UUID
     * @return
     */
    static CsRUnstructTask dirTaskByUUID(const QString &UUID);
    /**
     * @brief dirTask  查询所有任务
     * @return
     */
    static QList<CsRUnstructTask> dirTask();
    /**
     * @brief dirRTask  获取所有可用非结构化任务
     * @param status    任务状态
     * @param curTime   当前时间
     * @return
     */
    static QList<CsRUnstructTask> dirRTask(const quint8 &status, const QString &curTime);
    /**
     * @brief updateRtaskList 修改指定的任务链表
     * @param list
     */
    static void updateRtaskList(const QList<CsRUnstructTask> &list);
    /**
     * @brief updateRtask 修改指定的任务列表
     * @param task
     */
    static void updateRtask(const CsRUnstructTask &task);
    /**
     * @brief updateRTaskState     修改非结构化任务状态
     * @param taskUUID  任务UUID
     * @param state 任务状态
     */
    static void updateRTaskState(const QString &taskUUID,const quint8 &state);
    /**
     * @brief dirRSendAddrsByTaskUUID   查找当前任务的所有节点服务器信息
     * @param taskUUID  任务UUID
     * @return
     */
    static QList<VCsRUnstructSendAddr> pageAddrByTaskUuid(const QString &taskUUID,Page *page);
    /**
     * @brief dirRVSendFilesByTaskUUID 查找当前任务的所有文件信息
     * @param taskUuid
     * @return
     */
    static QList<VCsRUnstructSendFiles> pageFileByTaskUuid(const QString &taskUuid, Page *page);
    /**
     * @brief dirRSendAddrsByTaskUUID  查找当前任务的所有节点服务器信息
     * @param taskUuid
     * @return
     */
    static QList<CsRUnstructSendAddr> dirRSendAddrsByTaskUUID(const QString &taskUuid);

    static void dirRSendAddrsAndFilseByTaskUUID(const QString &taskUUID,
                                            const quint8 state,
                                            QList<CsRUnstructSendAddr>& addrs,
                                            QList<CsRUnstructSendFiles>& files);
    static void updateSendStatus(const QString &taskUUID,
                          const quint8 &oldState,
                          const quint8 &newState,
                          const QString &addrError);

    static void updateSendStatusByAddr(const QString& taskUUID,
                                             const quint8 &oldState,
                                             const quint8 &newState,
                                             const QString &addrError,
                                             const QString& clientUUID);
    /**
     * @brief updateRTaskAndAllSendAddrStatus    使用任务UUID修改当前任务状态和任务下发所有地址状态
     * @param taskUUID  任务UUID
     * @param taskState  任务状态
     * @param addrState 下发地址状态
     * @param addrError 下发地址错误描述
     */
    static void updateRTaskAndAllSendAddrStatus(const QString& taskUUID,const quint8 &taskState, const quint8 &statusState, const QString &statusError);
    /**
     * @brief updateRTaskAndSendAddrStatus    修改任务状态及任务下发地址状态
     * @param taskUUID  任务UUID
     * @param taskState 任务状态
     * @param clientUUID    节点服务地址UUID
     * @param addrState 节点状态
     * @param addrError 节点出错信息
     */
    static void updateRTaskAndSendAddrStatus(const QString& taskUUID,const quint8 &taskState,const QString& clientUUID ,const quint8 &statusState, const QString &statusError);
    /**
     * @brief updateRSendAddrByTaskUUID   修改任务下发地址状态
     * @param taskUUID
     * @param state
     */
    static void updateRSendAddrByTaskUUID(const QString &taskUUID, const QString &clientUUID, const quint8 &state, const QString &clientError);
    /**
     * @brief dirRSendFilesByTaskUUID   查找当前可用任务下发的所有文件
     * @param taskUUID
     * @return
     */
    static QList<CsRUnstructSendFiles> dirRSendFilesByTaskUUID(const QString &taskUUID);
    /**
     * @brief updateRTaskAndAddr    使用任务UUID和任务状态修改任务状态,使用任务UUID和下发地址状态修改任务下发地址状态
     * @param taskUUID  任务UUID
     * @param taskNewState  任务新状态
     * @param taskOldState  任务状态
     * @param taskOperaSymbol   任务状态过滤操作符
     * @param newAddrState  下发地址新状态
     * @param oldAddrState  下发地址久状态
     * @param addrOperaSymbol   下发地址过滤操作符
     * @param addrError 任务下发地址出错信息,如果修改下发地址状态为SUCCESS,错误没信息写""
     */
    static void updateRTaskAndAllSendAddr(const QString& taskUUID, const quint8 &taskNewState, const quint8 &taskOldState,const QString &taskOperaSymbol,
                                          const quint8 &newStatusState,const quint8 &oldStatusState,const QString &StatusOperaSymbol,const QString &StatusError);
    /**
     * @brief updateRTaskAndAddr    修改任务表任务状态及任务下发地址状态
     * @param taskUUID
     * @param taskOldState
     * @param taskNewState
     * @param taskOperaSymbol   任务条件运算符
     * @param clientUUID
     * @param addrState
     * @param addrError     
     * updateRTaskAndSendAddr
     */
    static void updateRTaskAndAddr(const QString& taskUUID, const quint8 &taskOldState, const quint8 &taskNewState,const QString &taskOperaSymbol,const QString &clientUUID, const quint8 &statusState,const QString &statusError);


    static void updateRTaskAndAddr(const QString& taskUUID,
                                   const quint8 &taskOldState,
                                   const quint8 &taskNewState,
                                   const QString &clientUUID,
                                   const quint8 &addrOldState,
                                   const quint8 &addrNewState,
                                   const QString &addrError);
    //获取当前任务下发状态列表中是否含有某种状态 有true 无false
    static bool getSendStatusState(const QString& taskUUID,
                                   const quint8 sendState);

    static void updateSendStateErrorInfo(const QString& taskUUID,
                                     const quint8 &oldState,
                                     const quint8 &newState,
                                     const QString &clientUUID,
                                     const QVector<Result*> &Errors);
    
    /**
     * @brief getRTaskUuidByTaskNum 获取非结构化任务taskUUID
     * @param taskUUID
     * @param taskNum
     */
    static void getRTaskUuidByTaskNum(QString& taskUUID, const quint32 &taskNum);

    /**
     * @brief getRTaskStateByTaskUUID   获取非结构化任务状态
     * @param taskUUID
     * @param state
     */
    static void getRTaskStateByTaskUUID(const QString& taskUUID, quint8 &state);
    /**
     * @brief getRTaskStateByTaskUUIDAndClientUUID 获取非结构化任务下发的服务器状态
     * @param taskUUID
     * @param clientUUID
     * @param state
     */
    static void getRTaskStateByTaskUUIDAndClientUUID(const QString& taskUUID, const QString &clientUUID, quint8 &state);
    /**
     * @brief getErrorMsgByState    使用任务错误状态获取任务错误信息
     * @param taskState
     * @param errorMsg
     */
    static void getErrorMsgByState(const quint8 &taskState,QString &errorMsg);
    /**
     * @brief updateRTaskErrorInfo  修改任务下载出错信息
     * @param taskUUID
     * @param taskState
     * @param addrState
     * @param addrError
     * @param Errors    出错文件状态
     */
    static void updateRTaskErrorInfo(const QString& taskUUID,const quint8 &taskState, const quint8 &statusState, const QString &statusError,const QVector<Result*> &Errors);

    /**
     * @brief moveRTask2STask   迁移当前任务到归档表
     * @param taskUUID
     */
    static void moveRTask2STask(const QString& taskUUID);


    /**
     * @brief updateRTaskStateByTaskUUID    根据任务状态、操作符修改任务状态
     * @param taskUUID
     * @param oldState
     * @param newState
     * @param operaSymbol
     * updateRTaskStateByTaskUUID(QString("1001"),1,2,QString("!="));对应sql:update CS_R_UNSTRUCT_TASK set STATE ='2' where UUID ='1001' and STATE != '1'
     * updateRTaskStateByTaskUUID(QString("1001"),1,2,QString("="));对应sql:update CS_R_UNSTRUCT_TASK set STATE ='2' where UUID ='1001' and STATE = '1'
     */
    static void updateRTaskStateByTaskUUID(const QString &taskUUID,const quint8 &oldState,const quint8 &newState,const QString &operaSymbol);

    /**
     * @brief updateRTaskSendAddrStateByTaskUUID   使用任务UUID修改非结构化任务下发的服务器状态
     * @param taskUUID
     * @param state
     * @param clientError
     */
    static void updateRTaskSendAddrStateByTaskUUID(const QString &taskUUID,const quint8 &state,const QString &clientError);
    /**
     * @brief updateRTaskSendAddrByTaskUUIDAndClientUUID 修改任务节点服务器的状态 （清空）出错描述 并判断任务的状态需要修改
     * @param taskUUID  任务UUID
     * @param nodes     节点服务器列表
     * @param state     修改后的任务地址表的状态
     */
    static void updateRTaskSendStatusByTaskUUIDAndClientUUID(const QString &taskUUID,const QStringList &nodes,const quint8 &state);
    /**
     * @brief updateRTaskSendStatusByTaskUUIDAndSendFileUUID   修改任务节点服务器的状态 （清空）出错描述 并判断任务的状态需要修改
     * @param taskUUID  任务UUID
     * @param sendFileUUids 文件列表UUID
     * @param state  修改后的任务地址表的状态
     */
    static void updateRTaskSendStatusByTaskUUIDAndSendFileUUID(const QString &taskUUID,const QStringList &sendFileUUids,const quint8 &state);
    /**
     * @brief updateRTaskSendAddrByTaskUUIDAndClientUUID   修改当前任务的当前节点服务器状态
     * @param taskUUID
     * @param state
     * @param clientError
     */
    static void updateRTaskSendStatusByTaskUUIDAndClientUUID(const QString &taskUUID,const QString &clientUUID,const quint8 &state,const QString &clientError);
    /**
     * @brief updateRTaskSendStatusByUUID   修改务关联表关态
     * @param taskUuid
     * @param UUID
     * @param state
     */
    static void updateRTaskSendStatusByUUID(const QString &taskUuid,const QStringList &UUID,const quint8 &state);

    /**
     * @brief saveSRTask 对于完成的任务进行归档
     * @param csSUnstructTask
     * @param csSUnstructSendAddr
     * @param csSUnstructSendFiles
     */
    static void saveSRTask(const CsSUnstructTask& csSUnstructTask, const CsSUnstructSendAddr& csSUnstructSendAddr, const CsSUnstructSendFiles& csSUnstructSendFiles);

    /**
     * @brief insertRTaskSendState 向主任务发送状态表中插入任务失败的数据
     * @param csRUnstructSendStatus
     */
    static void insertRTaskSendState(const CsRUnstructSendStatus& csRUnstructSendStatus);



    //--------------------get client_addr----------begin----------------

    static void getClientAddrByGroupUUID(QList<QString> &groupUUIDs, QList<QString> &clientUUIDs);

    static  void addTaskFromWeb(CsRUnstructTask& uStructTask,
                                QList<CsRUnstructSendAddr*> &uStructSendAddrList,
                                QList<CsRUnstructSendFiles *> &uStructSendFilesList,
                                QList<CsRUnstructSendStatus *> &uStructSendStatusList,
                                CsRStructTask &structTask,
                                QList<CsRStructSendAddr *> &structSendAddrList,
                                QList<CsRStructSendFiles *> &structSendFilesList,
                                QList<CsRStructSendStatus* > &structSendStatusList);
    //--------------------get client_addr----------begin----------------
    //获取公钥
    static void getPubKey(const quint64& terminateUUID, QString& pubKey);
    //获取私钥
    static void getPriKey(const quint64& terminateUUID, QString& priKey);
private:
    static CsRUnstructTask mapToRUnstructTask(const QVariantMap &rowMap);
    static CsRUnstructSendFiles mapToRUnstructTaskSendFile(const QVariantMap &rowMap);
    static CsRUnstructSendAddr mapToRUnstructTaskSendAddr(const QVariantMap &rowMap);
    static CsRUnstructSendStatus mapToRUnstructTaskSendStatus(const QVariantMap &rowMap);
    static VCsRUnstructSendAddr mapToRVUnstructTaskSendAddr(const QVariantMap &rowMap);
    static VCsRUnstructSendFiles mapToVUnstructTaskSendFile(const QVariantMap &rowMap);
    //----------------------------------策略--------------------begin
    static quint8 defaultStrategy(const QList<quint8> &stateList);
    //----------------------------------策略--------------------end
};

#endif // CSUNSTRUCTDAO_H
