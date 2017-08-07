#ifndef STRUCTUTIL_H
#define STRUCTUTIL_H
#include <QtCore>
#include <QList>
#include "avro.h"
#include "../../UpCloud-Service-Center/BusinessIServer/StructIServer/bean/csrstask.h"
#include "../../UpCloud-Service-Center/BusinessIServer/StructIServer/bean/csrssendaddr.h"
#include "../../UpCloud-Service-Center/BusinessIServer/StructIServer/bean/csrssendfiles.h"
#include "../../UpCloud-Service-Center/BusinessIServer/StructIServer/bean/csrssendstatus.h"
#include "../../UpCloud-Service-Center/BusinessIServer/StructIServer/bean/vcsassendfiles.h"
#include "../../UpCloud-Service-Center/BusinessIServer/StructIServer/bean/vcssendaddr.h"
class StructUtil
{
public:
    StructUtil();
    /**
     * @brief taskEntinyTojsonStr 实体对象转化json串
     * @param msg json串
     * @param taskList 实体对象
     */
    static void taskEntinyTojsonStr(QString &msg, const QList<CsRStructSendFiles> &taskList);
    /**
     * @brief taskEntinyTojsonStr 实体对象转化json串
     * @param msg json串
     * @param task 实体对象
     */
    static void taskEntinyTojsonStr(QString &msg,const CsRStructSendFiles &task);
    /**
     * @brief taskEntinyFromjsonStr json串转化为实体对象
     * @param taskList
     * @param msg
     * @return
     */
    static bool taskEntinyFromjsonStr(QList<CsRStructSendFiles> &taskList, const QString &msg);
    /**
     * @brief taskEntinyFromjsonStr json串转化为实体对象
     * @param task 实体对象
     * @param msg  json串
     * @return
     */
    static bool taskEntinyFromjsonStr(CsRStructSendFiles &task,const QString &msg);

    /**
     * @brief taskEntinyTojsonStr 实体对象转化json串
     * @param msg json串
     * @param taskList 实体对象
     */
    static void taskEntinyTojsonStr(QString &msg, const QList<CsRStructSendAddr> &taskList);
    /**
     * @brief taskEntinyTojsonStr 实体对象转化json串
     * @param msg json串
     * @param task 实体对象
     */
    static void taskEntinyTojsonStr(QString &msg,const CsRStructSendAddr &task);
    /**
     * @brief taskEntinyFromjsonStr json串转化为实体对象
     * @param taskList
     * @param msg
     * @return
     */
    static bool taskEntinyFromjsonStr(QList<CsRStructSendAddr> &taskList, const QString &msg);
    /**
     * @brief taskEntinyFromjsonStr json串转化为实体对象
     * @param task 实体对象
     * @param msg  json串
     * @return
     */
    static bool taskEntinyFromjsonStr(CsRStructSendAddr &task,const QString &msg);

    /**
     * @brief taskEntinyTojsonStr 实体对象转化json串
     * @param msg json串
     * @param taskList 实体对象
     */
    static void taskEntinyTojsonStr(QString &msg, const QList<VCsRStructSendAddr> &taskList);
    /**
     * @brief taskEntinyTojsonStr 实体对象转化json串
     * @param msg json串
     * @param task 实体对象
     */
    static void taskEntinyTojsonStr(QString &msg,const VCsRStructSendAddr &task);
    /**
     * @brief taskEntinyFromjsonStr json串转化为实体对象
     * @param taskList
     * @param msg
     * @return
     */
    static bool taskEntinyFromjsonStr(QList<VCsRStructSendAddr> &taskList, const QString &msg);
    /**
     * @brief taskEntinyFromjsonStr json串转化为实体对象
     * @param task 实体对象
     * @param msg  json串
     * @return
     */
    static bool taskEntinyFromjsonStr(VCsRStructSendAddr &task,const QString &msg);
    /**
     * @brief taskEntinyTojsonStr 实体对象转化json串
     * @param msg json串
     * @param taskList 实体对象
     */
    static void taskEntinyTojsonStr(QString &msg, const QList<CsRStructTask> &taskList);
    /**
     * @brief taskEntinyTojsonStr 实体对象转化json串
     * @param msg json串
     * @param task 实体对象
     */
    static void taskEntinyTojsonStr(QString &msg,const CsRStructTask &task);
    /**
     * @brief taskEntinyFromjsonStr json串转化为实体对象
     * @param taskList
     * @param msg
     * @return
     */
    static bool taskEntinyFromjsonStr(QList<CsRStructTask> &taskList, const QString &msg);
    /**
     * @brief taskEntinyFromjsonStr json串转化为实体对象
     * @param task 实体对象
     * @param msg  json串
     * @return
     */
    static bool taskEntinyFromjsonStr(CsRStructTask &task,const QString &msg);
    /**
     * @brief taskSendStatusEntityFromjsonStr 将Json串转换为实体
     * @param status
     * @param msg
     * @return
     */
    static bool taskSendStatusEntityFromjsonStr( CsRStructSendStatus &status,const QString &msg);
    /**
     * @brief taskSendStatusEntityFromjsonStr  将Json串转换为实体链表
     * @param status
     * @param msg
     * @return
     */
    static bool taskSendStatusEntityFromjsonStr(QList<CsRStructSendStatus> &statusList, const QString &msg);
    /**
     * @brief taskSendStatusEntityTojsonStr 将关联状态实体转换为JSON串
     * @param msg
     * @param status
     */
    static void taskSendStatusEntityTojsonStr(QString &msg, const CsRStructSendStatus &status);
    /**
     * @brief taskSendStatusEntityTojsonStr 将关联状态实体链表转换为JSON串
     * @param msg
     * @param statusList
     */
    static void taskSendStatusEntityTojsonStr(QString &msg,const QList<CsRStructSendStatus> &statusList);

    //-----------------------for view--------begin----------------------
    static void taskEntinyTojsonStr(QString &msg, const QList<VCsRStructSendFiles> &taskList);
    static void taskEntinyTojsonStr(QString &msg, const VCsRStructSendFiles &task);
    static bool taskEntinyFromjsonStr(QList<VCsRStructSendFiles> &taskList, const QString &msg);
    static bool taskEntinyFromjsonStr(VCsRStructSendFiles &task, const QString &msg);
    //-----------------------for view--------end------------------------
};

#endif // STRUCTUTIL_H
