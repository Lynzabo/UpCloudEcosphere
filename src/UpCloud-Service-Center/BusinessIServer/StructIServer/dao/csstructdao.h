#ifndef CSSTRUCTDAO_H
#define CSSTRUCTDAO_H

#include "base.h"
#include "db.h"
#include "transmsg.h"

#include "../bean/csrstask.h"
#include "../bean/csrssendaddr.h"
#include "../bean/csrssendfiles.h"
#include "../bean/csrssendstatus.h"

#include "../bean/cssstask.h"
#include "../bean/cssssendaddr.h"
#include "../bean/cssssendfiles.h"

#include "../bean/vcsassendfiles.h"
#include "../bean/vcssendaddr.h"

class CSStructDao
{
public:
    CSStructDao();
    /**
     * @brief addTask 添加任务
     * @param task
     * @param addrInfoList
     * @param fileInfoList
     * @param statusInfoList
     */
    static void addTask(const CsRStructTask &task,const QList<CsRStructSendAddr> addrInfoList,
                        const QList<CsRStructSendFiles> fileInfoList,
                        const QList<CsRStructSendStatus> statusInfoList);
    /**
     * @brief updateRTask  修改任务
     * @param task
     */
    static void updateRTask(const QList<CsRStructTask> &taskList);
    /**
   * @brief dirRTask  向结构化任务表添加节点；
   * @param CsRStructTask    任务信息
   * @return
   */
    static void addTaskAddr(const CsRStructSendAddr &task);
    /**
    * @brief dirRTask  向结构化任务表添加文件；
    * @param CsRStructTask    任务信息
    * @return
    */
    static void addTaskFile(const CsRStructSendFiles &task);
    /**
     * @brief dirRTaskByUUid 通过UUID查询任务
     * @param uuid
     */
    static CsRStructTask dirRTaskByUUid(const QString &uuid);

    /**
     * @brief dirRTask 查询结化任务一条记录
     * @param task
     * @return
     */
    static QList<CsRStructTask> dirRTask(const QVariantMap &map = {});
    /**
     * @brief pageTask  分页查询非结构化任务
     * @param map
     * @param page
     * @return
     */
    static QList<CsRStructTask> pageTask(const QVariantMap & map,Page *page);
    /**
     * @brief dirRTask  获取所有可用结构化任务
     * @param status    任务状态
     * @param curTime   当前时间
     * @return
     */
    static QList<CsRStructTask> dirRTask(const quint8 &status, const QString &curTime);
    /**
     * @brief updateRTaskState     修改结构化任务状态
     * @param taskUUID  任务UUID
     * @param state 任务状态
     */
    static void updateRTaskState(const QString &taskUUID,const quint8 &state);
    /**
     * @brief updateRTaskSendStatusByUUID   修改务关联表关态
     * @param taskUuid
     * @param UUID
     * @param state
     */
    static void updateRTaskSendStatusByUUID(const QString &taskUuid,const QStringList &UUID,const quint8 &state);
    /**
     * @brief delRTask 删除指定的一组任务
     * @param uuids
     */
    static void delRTask(const QStringList &uuids);
    /**
     * @brief addTask  添加当前任务的之指定的节点服务器
     * @param taskUuid  任务UUID
     * @param nodes   节点服务器UUID
     */
    static void addRSendAddr(const QString &taskUuid, const QStringList &nodes, const QStringList groupDes);
    /**
     * @brief delRSendAddr  删除当前任务的之指定的节点服务器
     * @param taskUuid   任务UUID
     * @param nodes  节点服务器UUID
     */
    static void delRSendAddr(const QString &taskUuid,const QStringList &nodes);

    /**
     * @brief dirRSendAddrs   查找当前任务的所有节点服务器信息
     * @param taskUUID  任务UUID
     * @param nodes    一组节点服务器UUID
     * @return
     */
    static QList<CsRStructSendAddr> dirRSendAddr(const QString &taskUuid,const QStringList &nodes = {});
    /**
     * @brief dirRSendAddrsByTaskUUID  查询任务节点服务器信息
     * @param taskUUID
     * @return
     */
    static QList<VCsRStructSendAddr> pageAddrByTaskUuid(const QString& taskUUID, Page *page);
    /**
     * @brief dirRSendStatusByTaskUuidAndClientUuid 查询关联地址表 并查询对应的文件名
     * @param taskUuid   任务UUID
     * @param clientUuid  节点服务器UUID
     * @param paramsList  文件名列表（输出参数）
     * @return
     */
    static QList<CsRStructSendStatus> pageRSendStatusByTaskUuidAndClientUuid(const QString &taskUuid, const QString &clientUuid, QStringList &paramsList, Page *page);
    /**
     * @brief dirRSendStatusByTaskUuidAndSendFileUUid  查询关联地址表 并查询对应的节点服务器名
     * @param taskUuid  任务UUID
     * @param fileUuids  文件名
     * @param paramsList  节点服务器名列表
     * @return
     */
    static QList<CsRStructSendStatus> pageRSendStatusByTaskUuidAndSendFileUUid(const QString &taskUuid, const QString &fileUuids, QStringList &paramsList,Page* page);
    /**
     * @brief dirRSendAddrsByTaskUUID   查找当前任务的所有节点服务器信息
     * @param taskUUID  任务UUID
     * @return
     */
    static void dirRSendAddrsAndFilseByTaskUUID(const QString &taskUUID,
                                            const quint8 state,
                                            QList<CsRStructSendAddr>& addrs,
                                            QList<CsRStructSendFiles>& files);


    static void updateSendStatus(const QString &taskUUID,
                          const quint8 &oldState,
                          const quint8 &newState,
                          const QString &addrError);

    static void updateSendStatusByAddr(const QString& taskUUID,
                                             const quint8 &oldState,
                                             const quint8 &newState,
                                             const QString &addrError,
                                             const QString& clientUUID);

    //获取当前任务下发状态列表中是否含有某种状态 有true 无false
    static bool getSendStatusState(const QString& taskUUID,
                                   const quint8 sendState);
    /**
     * @brief updateRSendAddrByTaskUUID   修改任务下发地址状态
     * @param taskUUID
     * @param state
     */
    static void updateRSendAddrByTaskUUID(const QString &taskUUID, const QString &clientUUID, const quint8 &state, const QString &clientError);
    /**
     * @brief dirRSendFiles  查找当前可用任务下发指定的文件
     * @param taskUuid
     * @param newNameList
     */
    static QList<CsRStructSendFiles> dirRSendFiles(const QString &taskUuid,const QStringList &newNameList);
    /**
     * @brief delRSendFiles  删除当前任务的指定的文件
     * @param taskUuid
     * @param uuidList
     */
    static void delRSendFiles(const QString &taskUuid,const QStringList &uuidList);
    /**
     * @brief delRSendFiles 在当前任务指定的文件信息添加任务文件
     * @param taskUuid
     * @param taskList
     */
    static void addRSendFiles(const QString &taskUuid, const QList<CsRStructSendFiles> &taskList, const QList<CsRStructSendStatus> &statusList);
    /**
     * @brief dirRSendFilesByTaskUUID   查找当前可用任务下发的所有文件
     * @param taskUUID
     * @return
     */
    static QList<CsRStructSendFiles> dirRSendFilesByTaskUUID(const QString &taskUUID);
    /**
     * @brief updateRTaskAndAddr 修改任务节点服务器的状态 清空错误描述 并判断任务状态是否要修改
     * @param taskUUID
     * @param nodes
     * @param state
     */
    static void updateRTaskAndAddr(const QString& taskUUID, const QStringList &nodes, const quint8 state);
    /**
     * @brief updateRTaskAndFile 修改任务文件 清空错误描述 并判断任务状态是否要修改
     * @param taskUUID
     * @param nodes
     * @param state
     */
    static void updateRTaskAndFile(const QString& taskUUID, const QStringList &nodes, const quint8 state);
    /**
     * @brief updateRTaskAndAddr    修改任务表任务状态及任务下发地址状态
     * @param taskUUID
     * @param taskOldState
     * @param taskNewState
     * @param clientUUID
     * @param addrState
     * @param addrError
     * updateRTaskAndSendAddr
     */
    static void updateRTaskAndAddr(const QString& taskUUID,
                                   const quint8 &taskOldState,
                                   const quint8 &taskNewState,
                                   const QString &clientUUID,
                                   const quint8 &addrOldState,
                                   const quint8 &addrNewState,
                                   const QString &addrError);


    /**
     * @brief getRTaskUuidByTaskNum 获取结构化任务taskUUID
     * @param taskUUID
     * @param taskNum
     */
    static void getRTaskUuidByTaskNum(QString& taskUUID, const quint32 &taskNum);

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
    static void updateSendStateErrorInfo(const QString& taskUUID,
                                     const quint8 &oldState,
                                     const quint8 &newState,
                                     const QString &clientUUID,
                                     const QVector<Result*> &Errors);

    /**
     * @brief getRTaskStateByTaskUUID   获取结构化任务状态
     * @param taskUUID
     * @param state
     */
    static void getRTaskStateByTaskUUID(const QString& taskUUID, quint8 &state);

    /**
     * @brief moveRTask2STask   迁移当前任务到归档表
     * @param taskUUID
     */
    static void moveRTask2STask(const QString& taskUUID);

    static QList<VCsRStructSendFiles> pageFileByTaskUuid(const QString &taskUUID, Page *page);
    static VCsRStructSendFiles mapToVStructTaskSendFile(const QVariantMap &rowMap);

private:
    static CsRStructTask mapToRStructTask(const QVariantMap &rowMap);
    static CsRStructSendFiles mapToRStructTaskSendFile(const QVariantMap &rowMap);
    static CsRStructSendAddr mapToRStructTaskSendAddr(const QVariantMap &rowMap);
    static CsRStructSendStatus mapToStructSendStatus(const QVariantMap &rowMap);
    static VCsRStructSendAddr mapToRVStructTaskSendAddr(const QVariantMap &rowMap);
    //----------------------------------策略--------------------begin
    static quint8 defaultStrategy(const QList<quint8> &stateList);
    //----------------------------------策略--------------------end
};

#endif // CSSTRUCTDAO_H
