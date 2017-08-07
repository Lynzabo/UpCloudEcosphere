#ifndef NSSTRUCTDAO_H
#define NSSTRUCTDAO_H

#include "base.h"
#include "db.h"

#include "bean/nsrstask.h"
#include "bean/nsrssendfiles.h"

#include "bean/nssstask.h"
#include "bean/nssssendfiles.h"

class NsStructDao
{
public:
    NsStructDao();

    /**
     * @brief insertRTaskAndTaskFiles   插入结构化任务并插入该任务文件
     * @param nsRStructTask
     * @param downFiles
     */
    static void insertRTaskAndTaskFiles(NsRStructTask *nsRStructTask,QList<NsRStructSendFiles *> downFiles);


    /**
     * @brief dirRTaskByStatus 根据状态查找所有的可用的结构化任务
     * @param state
     * @param curTime
     * @return
     */
    static QList<NsRStructTask> dirRTaskByStatus(const quint8 &state, const QString &curTime);

    /**
     * @brief updateRTaskState   修改结构化任务状态
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
    static  QList<NsRStructSendFiles> dirRSendFilesByTaskUUID(const QString &taskUUID,const quint8 &state);

    /**
     * @brief updateRSendFilesStateByUrlAbst 通过文件下载地址和保存路径 修改文件状态
     * @param fileUrl
     * @param destAbst
     * @param state
     */
    static void updateRSendFilesStateByUrlAbst(const QString &taskUUID, const QString &fileUrl, const QString &destAbst, const quint8 &state);

    /**
     * @brief updateRSendFilesState 修改文件地址表状态
     * @param taskUUID 任务UUID
     * @param oldState 旧状态
     * @param newState 新状态
     */
    static void updateRSendFilesState(const QString &taskUUID, const quint8 &oldState, const quint8 &newState);


    /**
     * @brief getRTaskByUUID 通过taskUUID 得到结构化任务
     * @param taskUUID
     */
    static NsRStructTask getRTaskByUUID(const QString &taskUUID);

    /**
     * @brief getRTaskDownloadStatus    获取任务是否下载完所有文件
     * @param taskUUID
     * @param filesState
     * @return
     */
    static bool getRTaskDownloadStatus(const QString &taskUUID, const quint8 &filesState);

    /**
     * @brief updateRSendFilesState  通过任务UUID和文件下载地址修改文件状态
     * @param taskUUID
     * @param fileUrl
     * @param state
     * @param errorMsg
     */
    static void updateRSendFilesState(const QString &taskUUID, const QString &fileUrl, const quint8 &state, const QString &errorMsg);

    /**
     * @brief updateRSendFilesState  通过任务UUID和文件保存地址修改文件状态
     * @param taskUUID
     * @param fileAbst
     * @param state
     * @param errorMsg
     */
    static void updateRSendFilesStateByAbst(const QString &taskUUID, const QString &fileAbst, const quint8 &state, const QString &errorMsg);

    /**
     * @brief getRTaskUuidByTaskNum 获取结构化任务taskUUID
     * @param taskUUID
     * @param taskNum
     */
    static void getRTaskUuidByTaskNum(QString& taskUUID, const quint32 &taskNum);

    /**
     * @brief getRTaskStateByTaskUUID   使用任务UUID获取任务状态
     * @param taskUUID
     * @param state
     */
    static void getRTaskStateByTaskUUID(const QString &taskUUID, quint8 &state);

    /**
     * @brief updateRTaskAndSendFilesStateByUUID 同时更新主任务状态和文件状态
     * @param taskUUID 任务UUID
     * @param taskState 主任务状态
     * @param sendFileState 文件状态
     */
    static void updateRTaskAndSendFilesStateByUUID(const QString &taskUUID, const quint8 &taskState, const quint8 &sendFileState);


    /**
     * @brief moveRTask2STask   迁移当前任务到归档表
     * @param taskUUID
     */
    static void moveRTask2STask(const QString& taskUUID);
private:
     static NsRStructTask mapToRStructTask(const QVariantMap &rowMap);
     static NsRStructSendFiles mapToRStructSendFiles(const QVariantMap &rowMap);
};

#endif // NSSTRUCTDAO_H
