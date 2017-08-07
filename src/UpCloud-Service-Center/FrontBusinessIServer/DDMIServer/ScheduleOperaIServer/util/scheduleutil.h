#ifndef SCHEDULEUTIL_H
#define SCHEDULEUTIL_H
#include <QtCore>
#include "base.h"
#include "avro.h"
#include "../../UpCloud-Service-Center/BusinessIServer/ScheduleIServer/bean/csrsctask.h"
#include "../../UpCloud-Service-Center/BusinessIServer/ScheduleIServer/bean/csrscsendaddr.h"
#include "../../UpCloud-Service-Center/BusinessIServer/ScheduleIServer/bean/csrscsendfiles.h"
#include "../../UpCloud-Service-Center/BusinessIServer/ScheduleIServer/bean/vcsascsendfiles.h"
class ScheduleUtil
{
public:
    ScheduleUtil();
    /**
     * @brief taskEntinyToJson 实体转换Json串
     * @param msg
     * @param task
     */
    void static taskEntinyToJson(QString &msg,const CsRScheduleTask &task);
    /**
     * @brief taskListEntinyToJson  实体链表转换Json串
     * @param msg
     * @param taskList
     */
    void static taskListEntinyToJson(QString &msg,const QList<CsRScheduleTask> &taskList);
    /**
     * @brief taskEntinyFromJson Json串转换实体
     * @param task
     * @param msg
     */
    bool static taskEntinyFromJson(CsRScheduleTask &task, const QString &msg);
    /**
     * @brief taskListEntinyFromJson Json串转换实体链表
     * @param taskList
     * @param msg
     * @return
     */
    bool static taskListEntinyFromJson(QList<CsRScheduleTask> &taskList,const QString &msg);
    /**
     * @brief addrEntinyToJson  实体转换Json串
     * @param msg
     * @param addr
     */
    void static addrEntinyToJson(QString &msg,const CsRScheduleSendAddr &addr);
    /**
     * @brief addrListEntinyToJson  实体链表转换Json串
     * @param msg
     * @param addrList
     */
    void static addrListEntinyToJson(QString &msg, const QList<CsRScheduleSendAddr> &addrList);
    /**
     * @brief addrEntinyFromJson  Json串转换实体
     * @param addr
     * @param msg
     */
    bool static addrEntinyFromJson(CsRScheduleSendAddr &addr,const QString &msg);
    /**
     * @brief addListEntinyFromJson  Json串转换实体链表
     * @param addr
     * @param msg
     * @return
     */
    bool static addrListEntinyFromJson(QList<CsRScheduleSendAddr> &addrList, const QString &msg);
    /**
     * @brief fileEntinyToJson  实体转换Json串
     * @param msg
     * @param file
     */
    void static fileEntinyToJson(QString &msg,const CsRScheduleSendFiles &file);
    /**
     * @brief fileListEntinyToJson  实体链表转换Json串
     * @param msg
     * @param file
     */
    void static fileListEntinyToJson(QString &msg,const QList<CsRScheduleSendFiles> &fileList);
    /**
     * @brief fileEntinyFromJson  Json串转换实体
     * @param file
     * @param msg
     * @return
     */
    bool static fileEntinyFromJson(CsRScheduleSendFiles &file,const QString &msg);
    /**
     * @brief fileListEntinyFromJson   Json串转换实体链表
     * @param msg
     * @param fileList
     * @return
     */
    bool static fileListEntinyFromJson(QList<CsRScheduleSendFiles> &fileList,const QString &msg);
    //--------------------view    begin--------------------
        void static vFileEntinyToJson(QString &msg,const VCsAScSendFiles &vFile);
        void static vFileListEntinyToJson(QString &msg, const QList<VCsAScSendFiles> &vFileList);
        bool static vFileEntinyFromJson(VCsAScSendFiles &vFile,const QString &msg);
        bool static vFileListEntinyFromJson(QList<VCsAScSendFiles> &vFileList, const QString &msg);
        //--------------------view    end------------------------
};

#endif // SCHEDULEUTIL_H
