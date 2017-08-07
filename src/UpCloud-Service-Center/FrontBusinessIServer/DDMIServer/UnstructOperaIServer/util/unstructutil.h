#ifndef UNSTRUCTUTIL_H
#define UNSTRUCTUTIL_H
#include <QtCore>
#include "avro.h"

#include"../../../../BusinessIServer/UnstructIServer/bean/csrusendfiles.h"
#include"../../../../BusinessIServer/UnstructIServer/bean/csrusendstatus.h"
#include"../../../../BusinessIServer/UnstructIServer/bean/csrutask.h"
#include"../../../../BusinessIServer/UnstructIServer/bean/csrusendaddr.h"
#include"../../../../BusinessIServer/UnstructIServer/bean/cssusendaddr.h"
#include"../../../../BusinessIServer/UnstructIServer/bean/cssusendfiles.h"
#include"../../../../BusinessIServer/UnstructIServer/bean/cssutask.h"
#include"../../../../BusinessIServer/UnstructIServer/bean/dtask.h"
#include"../../../../BusinessIServer/UnstructIServer/bean/dtaskaddr.h"
#include"../../../../BusinessIServer/UnstructIServer/bean/dtaskfile.h"
#include"../../../../BusinessIServer/UnstructIServer/bean/vcsrusendaddr.h"
#include"../../../../BusinessIServer/UnstructIServer/bean/vcsrusendfiles.h"
/**
 * @brief The UnstructUtil class    非结构化操作工具类
 */
class UnstructUtil
{
public:
    UnstructUtil();
    /**
     * @brief taskEntityFromjsonStr 将任务实体json串转换为实体对象
     * @param task
     * @param msg
     * @return
     */
    static bool taskEntityFromjsonStr(CsRUnstructTask &task,const QString &msg);
    /**
     * @brief taskEntityFromjsonStr  将任务实体json串转换为实体对象链表
     * @param tasklist
     * @param msg
     * @return
     */
    static bool taskEntityFromjsonStr(QList<CsRUnstructTask> &taskList, const QString &msg);
    /**
     * @brief taskEntityTojsonStr   将任务实体对象转换为json串
     * @param msg
     * @param task
     */
    static void taskEntityTojsonStr(QString &msg,const CsRUnstructTask &task);
    /**
     * @brief taskEntityTojsonStr  将任务实体对象链表转换为json串
     * @param msg
     * @param tasklist
     */
    static void taskEntityTojsonStr(QString &msg,const QList<CsRUnstructTask> &taskList);
    /**
     * @brief taskAddrEntityFromjsonStr 将任务地址实体json串转换为实体对象
     * @param addr
     * @param msg
     * @return
     */
    static bool taskAddrEntityFromjsonStr(CsRUnstructSendAddr &addr, const QString &msg);
    /**
     * @brief taskVAddrEntityFromjsonStr  将任务地址实体json串转换为实体对象
     * @param addr
     * @param msg
     * @return
     */
    static bool taskVAddrEntityFromjsonStr(VCsRUnstructSendAddr &addr, const QString &msg);
    /**
     * @brief taskAddrEntityFromjsonStr 将任务地址实体json串转换为实体对象链表
     * @param addr
     * @param msg
     * @return
     */
    static bool taskAddrEntityFromjsonStr(QList<CsRUnstructSendAddr> &taskList, const QString &msg);
    /**
     * @brief taskVAddrEntityFromjsonStr 将任务地址实体json串转换为实体对象链表
     * @param taskList
     * @param msg
     * @return
     */
    static bool taskVAddrEntityFromjsonStr(QList<VCsRUnstructSendAddr> &taskList, const QString &msg);
    /**
     * @brief taskAddrEntityTojsonStr   将任务地址实体对象转换为json串
     * @param msg
     * @param addr
     */
    static void taskAddrEntityTojsonStr(QString &msg,const CsRUnstructSendAddr &addr);
    /**
     * @brief taskAddrEntityTojsonStr  将任务地址实体JSON串转换为实体对象
     * @param msg
     * @param taskList
     */
    static void taskVAddrEntityTojsonStr(QString &msg, const VCsRUnstructSendAddr &vaddr);
    /**
     * @brief taskAddrEntityFromjsonStr  将任务地址实体JSON串转换为实体对象
     * @param addr
     * @param msg
     * @return
     */
    static void taskAddrEntityTojsonStr(QString &msg,const QList<CsRUnstructSendAddr> &taskList);
    /**
     * @brief taskVAddrEntityTojsonStr 将任务地址实体JSON串转换为实体对象
     * @param msg
     * @param taskList
     */
    static void taskVAddrEntityTojsonStr(QString &msg,const QList<VCsRUnstructSendAddr> &taskList);
    /**
     * @brief taskAddrFileEntityFromjsonStr 将任务地址文件实体json串转换为实体对象
     * @param sendFile
     * @param msg
     * @return
     */
    static bool taskAddrFileEntityFromjsonStr(CsRUnstructSendFiles &sendFile,const QString &msg);
    /**
     * @brief taskVAddrFileEntityFromjsonStr  将任务地址文件实体json串转换为实体对象
     * @param sendFile
     * @param msg
     * @return
     */
    static bool taskVAddrFileEntityFromjsonStr(VCsRUnstructSendFiles &sendFile,const QString &msg);
    /**
     * @brief taskAddrFileEntityFromjsonStr  将任务地址文件实体json串转换为实体对象链表
     * @param sendFile
     * @param msg
     * @return
     */
    static bool taskAddrFileEntityFromjsonStr(QList<CsRUnstructSendFiles> &taskList,const QString &msg);
    /**
     * @brief taskVAddrFileEntityFromjsonStr  将任务地址文件实体json串转换为实体对象链表
     * @param taskList
     * @param msg
     * @return
     */
    static bool taskVAddrFileEntityFromjsonStr(QList<VCsRUnstructSendFiles> &taskList,const QString &msg);
    /**
     * @brief taskAddrFileEntityTojsonStr   将任务地址文件实体对象转换为json串
     * @param msg
     * @param sendFile
     */
    static void taskAddrFileEntityTojsonStr(QString &msg,const CsRUnstructSendFiles &sendFile);
    /**
     * @brief taskVAddrFileEntityTojsonStr  将任务地址文件实体对象转换为json串
     * @param msg
     * @param sendFile
     */
    static void taskVAddrFileEntityTojsonStr(QString &msg,const VCsRUnstructSendFiles &sendFile);
    /**
     * @brief taskAddrFileEntityTojsonStr  将任务地址文件实体对象链表转换为json串
     * @param msg
     * @param sendFile
     */
    static void taskAddrFileEntityTojsonStr(QString &msg,const QList<CsRUnstructSendFiles> &taskList);
    /**
     * @brief taskVAddrFileEntityTojsonStr  将任务地址文件实体对象链表转换为json串
     * @param msg
     * @param taskList
     */
    static void taskVAddrFileEntityTojsonStr(QString &msg,const QList<VCsRUnstructSendFiles> &taskList);
    /**
     * @brief taskSendStatusEntityFromjsonStr 将Json串转换为实体
     * @param status
     * @param msg
     * @return
     */
    static bool taskSendStatusEntityFromjsonStr( CsRUnstructSendStatus &status,const QString &msg);
    /**
     * @brief taskSendStatusEntityFromjsonStr  将Json串转换为实体链表
     * @param status
     * @param msg
     * @return
     */
    static bool taskSendStatusEntityFromjsonStr(QList<CsRUnstructSendStatus> &statusList, const QString &msg);
    /**
     * @brief taskSendStatusEntityTojsonStr 将关联状态实体转换为JSON串
     * @param msg
     * @param status
     */
    static void taskSendStatusEntityTojsonStr(QString &msg, const CsRUnstructSendStatus &status);
    /**
     * @brief taskSendStatusEntityTojsonStr 将关联状态实体链表转换为JSON串
     * @param msg
     * @param statusList
     */
    static void taskSendStatusEntityTojsonStr(QString &msg,const QList<CsRUnstructSendStatus> &statusList);


    //-------------------------for JNI DTask DTaskAddr DTaskFile----begin------------

    /**
     * @brief DTaskEntityToJsonStr 将JNI DTask 实体 -----> JSON串
     * @param dTask DTask任务实体
     * @param jsonStr   DTaskJSON串
     * @return 成功返回true 失败返回false
     */
    static bool DTaskEntityToJsonStr(const DTask &dTask, QString &jsonStr);

    /**
     * @brief DTaskJsonStrToEntity  将JNI DTask JSON串 -----> 实体
     * @param msg   DTaskJSON串
     * @param jsonStr DTask任务实体
     * @return  成功返回true 失败返回false
     */
    static bool DTaskJsonStrToEntity(const QString &jsonStr, DTask &dTask);

    /**
     * @brief DTaskAddrEntityToJsonStr 将JNI DTaskAddr 实体 -----> JSON串
     * @param dTaskAddr DTaskAddr任务实体
     * @param jsonStr   DTaskAddrJSON串
     * @return  成功返回true 失败返回false
     */
    static bool DTaskAddrEntityToJsonStr(const DTaskAddr &dTaskAddr, QString &jsonStr);

    /**
     * @brief DTaskAddrJsonStrToEntity  将JNI DTaskAddr JSON串 -----> 实体
     * @param jsonStr   DTaskAddrJSON串
     * @param dTaskAddr DTaskAddr任务实体
     * @return  成功返回true 失败返回false
     */
    static bool DTaskAddrJsonStrToEntity(const QString &jsonStr, DTaskAddr &dTaskAddr);

    /**
     * @brief DTaskFileEntityToJsonStr  将JNI DTaskFile 实体 -----> JSON串
     * @param dTaskFile DTaskFile任务实体
     * @param jsonStr   DTaskFileJSON串
     * @return 成功返回true 失败返回false
     */
    static bool DTaskFileEntityToJsonStr(const DTaskFile &dTaskFile, QString &jsonStr);

    /**
     * @brief DTaskFileJsonStrToEntity  将JNI DTaskFile JSON串 -----> 实体
     * @param jsonStr   DTaskFileJSON串
     * @param dTaskFile DTaskFile任务实体
     * @return  成功返回true 失败返回false
     */
    static bool DTaskFileJsonStrToEntity(const QString &jsonStr, DTaskFile &dTaskFile);


    /**
     * @brief DTaskAddrListEntityToJsonStr  将JNI QList<DTaskAddr> 实体 -----> JSON串
     * @param dTaskAddrList QList<DTaskAddr>实体
     * @param jsonStr   QList<DTaskAddr>JSON串
     * @return 成功返回true 失败返回false
     */
    static bool DTaskAddrListEntityToJsonStr(const QList<DTaskAddr> &dTaskAddrList, QString &jsonStr);

    /**
     * @brief DTaskAddrListJsonStrToEntity  将JNI QList<DTaskAddr> JSON串 -----> 实体
     * @param $jsonStr  QList<DTaskAddr>JSON串
     * @param dTaskAddrList QList<DTaskAddr>实体
     * @return  成功返回true 失败返回false
     */
    static bool DTaskAddrListJsonStrToEntity(const QString &jsonStr, QList<DTaskAddr> &dTaskAddrList);

    /**
     * @brief DTaskFileListEntityToJsonStr  将JNI QList<DTaskFile> 实体 -----> JSON串
     * @param dTaskFileList QList<DTaskFile>实体
     * @param jsonStr   QList<DTaskFile>JSON串
     * @return 成功返回true 失败返回false
     */
    static bool DTaskFileListEntityToJsonStr(const QList<DTaskFile> &dTaskFileList, QString &jsonStr);

    /**
     * @brief DTaskFileListJsonStrToEntity  将JNI QList<DTaskFile> JSON串 -----> 实体
     * @param jsonStr   QList<DTaskFile>JSON串
     * @param dTaskFileList QList<DTaskFile>实体
     * @return  成功返回true 失败返回false
     */
    static bool DTaskFileListJsonStrToEntity(const QString &jsonStr, QList<DTaskFile> &dTaskFileList);

    /**
     * @brief DTaskDDEditorEntityToJsonStr  将JNI DDEditor 实体 -----> JSON串
     * @param dTask DTask任务实体
     * @param dTaskAddrList QList<DTaskAddr>实体
     * @param dUTaskFileList    QList<DTaskFile>非结构化实体
     * @param dSTaskFileList    QList<DTaskFile>结构化实体
     * @param jsonStr   DDEditor JSON串
     * @return  成功返回true 失败返回false
     */
    static bool DTaskDDEditorEntityToJsonStr(const DTask &dTask,
                                             const QList<DTaskAddr> &dTaskAddrList,
                                             const QList<DTaskFile> &dUTaskFileList,
                                             const QList<DTaskFile> &dSTaskFileList,
                                             QString &jsonStr);

    /**
     * @brief DTaskDDEditorJsonStrToEntity  将JNI DDEditor JSON串 -----> 实体
     * @param jsonStr   DDEditor JSON串
     * @param dTask DTask任务实体
     * @param dTaskAddrList QList<DTaskAddr>实体
     * @param dUTaskFileList    QList<DTaskFile>非结构化实体
     * @param dSTaskFileList    QList<DTaskFile>结构化实体
     * @return  成功返回true 失败返回false
     */
    static bool DTaskDDEditorJsonStrToEntity(const QString &jsonStr,
                                             DTask &dTask,
                                             QList<DTaskAddr> &dTaskAddrList,
                                             QList<DTaskFile> &dUTaskFileList,
                                             QList<DTaskFile> &dSTaskFileList);

    //-------------------------for JNI DTask DTaskAddr DTaskFile----begin------------
};

#endif // UNSTRUCTUTIL_H
























