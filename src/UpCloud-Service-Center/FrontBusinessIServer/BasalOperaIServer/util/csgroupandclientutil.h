#ifndef CSGROUPANDCLIENTUTIL_H
#define CSGROUPANDCLIENTUTIL_H
#include <QtCore>
#include "avro.h"
#include "../../../BusinessIServer/BasalIServer/bean/cscgroup.h"
#include "../../../BusinessIServer/BasalIServer/bean/cscgroupassoc.h"
#include "../../../BusinessIServer/BasalIServer/bean/cscextendinfo.h"
#include "../../../BusinessIServer/BasalIServer/bean/vcscgroupassoc.h"
class CsGroupAndClientUtil
{
public:
    CsGroupAndClientUtil();
    /**
     * @brief taskEntinyFromjsonStr 将json串转化为实体对象链表
     * @param task
     * @param msg
     * @return
     */
    static bool taskEntinyFromjsonStr(QList<CsClientGroup> &task,const QString &msg);
    /**
     * @brief taskEntinyFromjsonStr 将json串转化为实体对象
     * @param task
     * @param msg
     * @return
     */
    static bool taskEntinyFromjsonStr(CsClientGroup &task,const QString &msg);

    static void taskEntinyTojsonStr(QString &msg,const QList<CsClientGroup> &taskList);
    /**
     * @brief taskEntinyTojsonStr 将实体对象转化为json串
     * @param msg
     * @param task
     */
    static void taskEntinyTojsonStr(QString &msg,const CsClientGroup &task);
    /**
     * @brief taskEntinyFromjsonStr  将json串转化为实体对象
     * @param task
     * @param msg
     * @return
     */
    static bool taskEntinyFromjsonStr(QList<CsClientGroupAssoc> &taskList, const QString &msg);
    /**
     * @brief taskEntinyFromjsonStr  将json串转化为实体对象
     * @param task
     * @param msg
     */
    static bool taskEntinyFromjsonStr( CsClientGroupAssoc &task,const QString &msg);
    /**
     * @brief taskEntinyTojsonStr  将实体对象转化为json串
     * @param msg
     * @param taskList
     */
    static void taskEntinyTojsonStr(QString &msg, const QList<CsClientGroupAssoc> &taskList);
    /**
     * @brief taskEntinyTojsonStr  将实体对象转化为json串
     * @param msg
     * @param task
     */
    static void taskEntinyTojsonStr(QString &msg,const CsClientGroupAssoc &task);

    /**
     * @brief taskEntinyFromjsonStr  将json串转化为实体对象
     * @param task
     * @param msg
     * @return
     */
    static bool taskEntinyFromjsonStr(QList<VCsClientGroupAssoc> &taskList, const QString &msg);
    /**
     * @brief taskEntinyFromjsonStr  将json串转化为实体对象
     * @param task
     * @param msg
     */
    static bool taskEntinyFromjsonStr( VCsClientGroupAssoc &task,const QString &msg);
    /**
     * @brief taskEntinyTojsonStr  将实体对象转化为json串
     * @param msg
     * @param taskList
     */
    static void taskEntinyTojsonStr(QString &msg, const QList<VCsClientGroupAssoc> &taskList);
    /**
     * @brief taskEntinyTojsonStr  将实体对象转化为json串
     * @param msg
     * @param task
     */
    static void taskEntinyTojsonStr(QString &msg,const VCsClientGroupAssoc &task);
    /**
     * @brief taskEntinyFromjsonStr  将json串转化为实体对象
     * @param task
     * @param msg
     * @return
     */
    static bool taskEntinyFromjsonStr( QList<CsClientExtendInfo> &task,const QString &msg);
    /**
     * @brief taskEntinyFromjsonStr  将json串转化为实体对象
     * @param task
     * @param msg
     * @return
     */
    static bool taskEntinyFromjsonStr(CsClientExtendInfo &terminal, const QString &msg);
    /**
     * @brief taskEntinyTojsonStr  将实体对象转化为json串
     * @param msg
     * @param taskList
     */
    static void taskEntinyTojsonStr(QString &msg,const QList<CsClientExtendInfo> &taskList);
    /**
     * @brief taskEntinyTojsonStr   将实体对象转化为json串
     * @param msg
     * @param task
     */
    static void taskEntinyTojsonStr(QString &msg, const CsClientExtendInfo &terminal);

};

#endif // CSGROUPANDCLIENTUTIL_H
