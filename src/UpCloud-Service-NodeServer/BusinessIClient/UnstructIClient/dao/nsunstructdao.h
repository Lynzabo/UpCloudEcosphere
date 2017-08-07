#ifndef NSUNSTRUCTDAO_H
#define NSUNSTRUCTDAO_H

#include "base.h"
#include "db.h"

#include "bean/nsrutask.h"
#include "bean/nsrusendfiles.h"
class NsUnstructDao
{
public:
    NsUnstructDao();

public:
    /**
     * @brief dirRTaskByStatus 根据状态查找所有的可用的非结构化任务
     * @param state
     * @param curTime
     * @return
     */
    static QList<NsRUnstructTask> dirRTaskByStatus(const quint8 &state, const QString &curTime);
    /**
     * @brief updateRTaskStateByTaskUUID   修改非结构化任务状态
     * @param taskUUID
     * @param state
     */
    static void updateRTaskState(const QString &taskUUID,const quint8 &state);
    /**
     * @brief dirRSendFilesByTaskUUID    根据任务UUID查找所有的可用下发文件地址
     * @param taskUUID
     * @param state
     * @return
     */
    static  QList<NsRUnstructSendFiles> dirRSendFilesByTaskUUID(const QString &taskUUID,const quint8 &state);
    /**
     * @brief getRTaskStateByTaskUUID   使用任务UUID获取任务状态
     * @param taskUUID
     * @param state
     */
    static void getRTaskStateByTaskUUID(const QString &taskUUID, quint8 &state);




    /**
     * @brief getRTaskNumByTaskUUID 通过taskUUID 得到 taskNum
     * @param taskUUID
     * @param taskNum
     */
    static void getRTaskNumByTaskUUID(const QString &taskUUID,quint32 &taskNum);
    /**
     * @brief getRTaskUuidByTaskNum 获取非结构化任务taskUUID
     * @param taskUUID
     * @param taskNum
     */
    static void getRTaskUuidByTaskNum(QString& taskUUID, const quint32 &taskNum);
    /**
     * @brief getRTaskDownloadStatus    获取任务是否下载完所有文件
     * @param taskUUID
     * @param filesState
     * @return
     */
    static bool getRTaskDownloadStatus(const QString &taskUUID, const quint8 &filesState);
    /**
     * @brief moveRTask2STask   迁移当前任务到归档表
     * @param taskUUID
     */
    static void moveRTask2STask(const QString& taskUUID);
    /**
     * @brief getRTaskByUUID 通过taskUUID 得到非结构化任务
     * @param taskUUID
     */
    static NsRUnstructTask getRTaskByUUID(const QString &taskUUID);

    /**
     * @brief deleteRTaskByTaskNum 删除一条任务
     * @param taskNum
     */
    static void deleteRTaskByTaskNum(const QString &taskNum);

    /**
     * @brief insertRTask 插入任务表任务
     * @param nsRUnstructTask
     */
    static void insertRTask(const NsRUnstructTask& nsRUnstructTask);
    /**
     * @brief insertRTaskAndTaskFiles   插入非结构化任务并插入该任务文件
     * @param nsRUnstructTask
     * @param downFiles
     */
    static void insertRTaskAndTaskFiles(NsRUnstructTask *nsRUnstructTask,QList<NsRUnstructSendFiles *> downFiles);

    static void getRTaskUUIDByUrl(const QString &fileUrl, QString &uuid);



    /**
     * @brief insertRSendFiles 插入文件表
     * @param nsRUnstructSendFiles
     */
    static void insertRSendFiles(const NsRUnstructSendFiles& nsRUnstructSendFiles);

    /**
     * @brief deleteRSendFilesByTaskUUID 删除一个任务对应的文件
     * @param taskUUID
     */
    static void deleteRSendFilesByTaskUUID(const QString &taskUUID);

    /**
     * @brief updateRSendFilesStateByUrlAbst 通过文件下载地址和保存路径 修改文件状态
     * @param fileUrl
     * @param destAbst
     * @param state
     */
    static void updateRSendFilesStateByUrlAbst(const QString &taskUUID, const QString &fileUrl, const QString &destAbst, const quint8 &state);


    /**
     * @brief updateRSendFilesState  通过任务UUID和文件下载地址修改文件状态
     * @param taskUUID
     * @param fileUrl
     * @param state
     * @param errorMsg
     */
    static void updateRSendFilesState(const QString &taskUUID, const QString &fileUrl, const quint8 &state, const QString &errorMsg);

private:
     static NsRUnstructTask mapToRUnstructTask(const QVariantMap &rowMap);
     static NsRUnstructSendFiles mapToRUnstructSendFiles(const QVariantMap &rowMap);


};

#endif // NSUNSTRUCTDAO_H
