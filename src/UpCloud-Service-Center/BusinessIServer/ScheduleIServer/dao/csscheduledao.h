#ifndef CSSCHEDULEDAO_H
#define CSSCHEDULEDAO_H

#include "base.h"
#include "db.h"
#include "transmsg.h"

#include "../bean/csrsctask.h"
#include "../bean/csrscsendaddr.h"
#include "../bean/csrscsendfiles.h"
#include "../bean/csrscsendstatus.h"
#include "../bean/vcsascsendfiles.h"

#include "../bean/csssctask.h"
#include "../bean/cssscsendaddr.h"
#include "../bean/cssscsendfiles.h"

class  CSScheduleDao
{
public:
    CSScheduleDao();
    /**
     * @brief addTaskAddr   增加节点服务器
     * @param taskUuid
     * @param nodes
     * @param groupDes
     */
    static void addTaskAddr(const QString &taskUuid,const QStringList &nodes,const QStringList &groupDes);
    /**
     * @brief delTask 删除任务
     * @param uuids
     */
    static void delTask(const QStringList &uuids);
    /**
     * @brief delTaskAddr 删除任务节点服务器
     * @param taskUuid
     * @param nodes
     */
    static void delTaskAddr(const QString &taskUuid,const QStringList &nodes);
    /**
     * @brief delTaskFiles 删除任务文件列表信息
     * @param uuids  文件列表UUID
     */
    static void delTaskFiles(const QStringList &uuids);
    /**
     * @brief listTask 获取所有符合查询条件的控制传输任务
     * @param listInfo 查询信息
     * @return
     */
    static QList<CsRScheduleTask> listTask(const QVariantMap &listInfo = {});
    /**
     * @brief listAddr  获取所有符合查询条件的控制传输任务地址列表
     * @param uuid
     * @return
     */
    static QList<CsRScheduleSendAddr> listAddr(const QString &taskUuid);
    /**
     * @brief listFile  获取所有符合查询条件的控制传输任务文件列表
     * @param taskUuid
     * @return
     */
    static QList<VCsAScSendFiles> listVFile(const QString &taskUuid);
    /**
     * @brief itemTask 获取任务信息
     * @param info
     * @return
     */
    static QList<CsRScheduleTask> itemTask(const QVariantMap &info);
    /**
     * @brief dirRTask  获取所有可用控制传输任务
     * @param state    任务状态
     * @param curTime   当前时间
     * @return
     */
    static QList<CsRScheduleTask> dirRTask(const quint8 &state, const QString &curTime);
    /**
     * @brief updateTask 修改控制传输任务信息
     * @param taskList  任务信息列表
     */
    static void updateTask(const QList<CsRScheduleTask> &taskList);

    /**
     * @brief updateRTaskState     修改控制传输任务状态
     * @param taskUUID  任务UUID
     * @param state 任务状态
     */
    static void updateRTaskState(const QString &taskUUID,const quint8 &state);

    /**
     * @brief dirRSendAddrsByTaskUUID   查找当前任务的所有节点服务器信息
     * @param taskUUID  任务UUID
     * @return
     */
    static QList<CsRScheduleSendAddr> dirRSendAddrsByTaskUUID(const QString &taskUUID);
    /**
     * @brief updateRTaskAndAllSendAddrStatus    使用任务UUID修改当前任务状态和任务下发所有地址状态
     * @param taskUUID  任务UUID
     * @param taskState  任务状态
     * @param addrState 下发地址状态
     * @param addrError 下发地址错误描述
     */
    static void updateRTaskAndAllSendAddrStatus(const QString& taskUUID,const quint8 &taskState, const quint8 &addrState, const QString &addrError);
    /**
     * @brief updateRTaskAndSendAddrStatus 修改任务节点服务器状态 清空错误信息 并判断任务状态是否可以修改
     * @param taskUUID 任务UUID
     * @param nodes   节点服务器列表
     * @param taskState  修改后的节点服务器状态
     */
    static void updateRTaskAndSendAddrStatus(const QString& taskUUID, const QStringList &nodes, const quint8 &state);
    /**
     * @brief updateRTaskAndSendAddrStatus    修改任务状态及任务下发地址状态
     * @param taskUUID  任务UUID
     * @param taskState 任务状态
     * @param clientUUID    节点服务地址UUID
     * @param addrState 节点状态
     * @param addrError 节点出错信息
     */
    static void updateRTaskAndSendAddrStatus(const QString& taskUUID,const quint8 &taskState,const QString& clientUUID ,const quint8 &addrState, const QString &addrError);

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
    static QList<CsRScheduleSendFiles> dirRSendFilesByTaskUUID(const QString &taskUUID);

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
                                          const quint8 &newAddrState,const quint8 &oldAddrState,const QString &addrOperaSymbol,const QString &addrError);
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
    static void updateRTaskAndAddr(const QString& taskUUID, const quint8 &taskOldState, const quint8 &taskNewState,const QString &taskOperaSymbol,const QString &clientUUID, const quint8 &addrState,const QString &addrError);

    /**
     * @brief getRTaskUuidByTaskNum 获取控制传输任务taskUUID
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
    static void updateRTaskErrorInfo(const QString& taskUUID,const quint8 &taskState, const quint8 &addrState, const QString &addrError,const QVector<Result*> &Errors);

    /**
     * @brief getRTaskStateByTaskUUID   获取控制传输任务状态
     * @param taskUUID
     * @param state
     */
    static void getRTaskStateByTaskUUID(const QString& taskUUID, quint8 &state);

    /**
     * @brief moveRTask2STask   迁移当前任务到归档表
     * @param taskUUID
     */
    static void moveRTask2STask(const QString& taskUUID);
private:
    static CsRScheduleTask mapToRScheduleTask(const QVariantMap &rowMap);
    static CsRScheduleSendFiles mapToRScheduleTaskSendFile(const QVariantMap &rowMap);
    static CsRScheduleSendAddr mapToRScheduleTaskSendAddr(const QVariantMap &rowMap);
    static VCsAScSendFiles mapToRScheduleVFile(const QVariantMap &rowMap);
};

#endif // CSSCHEDULEDAO_H
