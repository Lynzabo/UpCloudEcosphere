#ifndef WINDOW_H
#define WINDOW_H
#include"base.h"
#include <QtCore>
#include <QMainWindow>

#include "netiremoteui.h"
#include "../../UpCloud-Service-Center/BusinessIServer/StructIServer/bean/csrstask.h"
#include "../../UpCloud-Service-Center/BusinessIServer/StructIServer/bean/csrssendaddr.h"
#include "../../UpCloud-Service-Center/BusinessIServer/StructIServer/bean/csrssendfiles.h"
#include "../../UpCloud-Service-Center/BusinessIServer/UnstructIServer/bean/csrutask.h"
#include "../../UpCloud-Service-Center/BusinessIServer/UnstructIServer/bean/csrusendaddr.h"
#include "../../UpCloud-Service-Center/BusinessIServer/UnstructIServer/bean/csrusendfiles.h"
#include "../../UpCloud-Service-Center/BusinessIServer/BasalIServer/bean/csdict.h"
#include "../../UpCloud-Service-Center/BusinessIServer/BasalIServer/bean/cscgroup.h"
#include "../../UpCloud-Service-Center/BusinessIServer/BasalIServer/bean/cscgroupassoc.h"
namespace Ui {
class Window;
}

class Window : public QMainWindow
{
    Q_OBJECT

public:
    explicit Window(QWidget *parent = 0);
    ~Window();
signals:
    //销毁客户端
    void destoryApp();
public slots:
    /**
     * @brief on_ReceiveMsg 接收异步工作传输来消息
     * @param msgID 消息ID    可选  当工作线程发送多个消息来时,使用它来作区分
     * @param msg
     */
    //void on_ReceiveMsg(const qint32 &msgID = 0,const QString &msg);
    void on_ReceiveMsg();
private slots:
    /**
     * @brief on_itemtaskCallback 工作线程返回数据到UI界面
     * @param msgId
     * @param msg
     * @param taskList
     */
    void on_itemtaskCallback(const qint32 msgId, const QString &msg, const QList<CsRStructSendFiles> &taskList);
    /**
     * @brief on_itemtaskCallback 工作线程返回数据到UI界面
     * @param msgId
     * @param msg
     * @param task
     */
    void on_itemtaskCallback(const qint32 msgId, const QString &msg, const CsRStructSendFiles &task);
    /**
     * @brief on_itemtaskCallback 工作线程返回数据到UI界面
     * @param msgId
     * @param msg
     * @param taskList
     */
    void on_itemtaskCallback(const qint32 msgId, const QString &msg, const QList<CsRStructSendAddr> &taskList);
    /**
     * @brief on_itemtaskCallback 工作线程返回数据到UI界面
     * @param msgId
     * @param msg
     * @param task
     */
    void on_itemtaskCallback(const qint32 msgId, const QString &msg, const CsRStructSendAddr &task);
    /**
     * @brief on_itemtaskCallback 工作线程返回数据到UI界面
     * @param msgId
     * @param msg
     * @param task
     */
    void on_itemtaskCallback(const qint32 msgId,const QString &msg,const CsRStructTask &task);
    /**
     * @brief on_itemtaskCallback 工作线程返回数据到UI界面
     * @param msgId
     * @param msg
     * @param taskList
     */
    void on_itemtaskCallback(const qint32 msgId, const QString &msg, const QList<CsRStructTask> &taskList);
    /**
     * @brief on_itemtaskCallback 工作线程返回数据到UI界面
     * @param msgId
     * @param msg
     * @param task
     */
    void on_itemtaskCallback(const qint32 msgId, const QString &msg, const QList<CsClientGroupAssoc> &taskList);
    /**
     * @brief on_itemtaskCallback 工作线程返回数据到UI界面
     * @param msgId
     * @param msg
     * @param task
     */
    void on_itemtaskCallback(const qint32 msgId, const QString &msg, const QList<CsClientGroup> &taskList);
    /**
     * @brief on_itemtaskCallback 工作线程返回数据到UI界面
     * @param msgId
     * @param msg
     * @param taskList
     */
    void on_itemtaskCallback(const qint32 msgId, const QString &msg, const QList<CsDict> &taskList);
    /**
     * @brief on_itemtaskCallback 工作线程返回数据到UI界面
     * @param msgId
     * @param msg
     * @param task
     */
    void on_itemtaskCallback(const qint32 msgId, const QString &msg, const CsRUnstructSendFiles &task);
    /**
     * @brief on_itemtaskCallback 工作线程返回数据到UI界面
     * @param msgId
     * @param msg
     * @param taskList
     */
    void on_itemtaskCallback(const qint32 msgId, const QString &msg, const QList<CsRUnstructSendFiles> &taskList);
    /**
     * @brief on_itemtaskCallback 工作线程返回数据到UI界面
     * @param msgId
     * @param msg
     * @param task
     */
    void on_itemtaskCallback(const qint32 msgId, const QString &msg, const CsRUnstructSendAddr &task);
    void on_itemtaskCallback(const qint32 msgId, const QString &msg, const QList<CsRUnstructSendAddr> &taskList);
    /**
     * @brief on_itemtaskCallback   工作线程返回数据到UI界面
     * @param msgId
     * @param msg
     * @param task
     */
    void on_itemtaskCallback(const qint32 msgId,const QString &msg,const CsRUnstructTask &task);
    /**
     * @brief on_itemtaskCallback  工作线程返回数据到UI界面
     * @param msgId
     * @param msg
     * @param task
     */
    void on_itemtaskCallback(const qint32 msgId,const QString &msg,const QList<CsRUnstructTask> &taskList);
private slots:
    /**
     * @brief startToWork  让任务调度器开始工作
     */
    void startToWork();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_4_clicked();


    void on_pushButton_3_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_8_clicked();




    void on_pushButton_17_clicked();

    void on_pushButton_16_clicked();

    void on_pushButton_15_clicked();

    void on_btn_itemtask_clicked();


    void on_btn_itemtask_2_clicked();

    void on_btn_itemtask_3_clicked();

    void on_btn_itemtask_4_clicked();

    void on_btn_itemtask_5_clicked();

    void on_btn_itemtask_9_clicked();

    void on_btn_itemtask_8_clicked();

    void on_btn_itemtask_6_clicked();

    void on_btn_itemtask_7_clicked();

    void on_btn_itemtask_11_clicked();

    void on_btn_itemtask_13_clicked();

    void on_btn_itemtask_10_clicked();

    void on_btn_itemtask_14_clicked();

    void on_btn_itemtask_12_clicked();

    void on_btn_listStructTask_clicked();

    void on_btn_delStructTask_clicked();

    void on_btn_addStructAddrTask_clicked();

    void on_btn_delStructAddrTask_clicked();

    void on_btn_addStructFileTask_clicked();

    void on_btn_delStructFileTask_clicked();

    void on_btn_addtask_clicked();

    void on_btn_addtaskfile_clicked();

    void on_btn_addtasknode_clicked();

    void on_btn_addStructTask_clicked();

    void on_btn_itemStructTask_clicked();

    void on_btn_updateStructTask_clicked();

protected:
    void closeEvent(QCloseEvent *closeEvent);
private:
    /**
     * @brief initViews 初始化UI,并为UI绑定事件
     */
    void initViews();
    /**
     * @brief initDatas 初始化UI数据
     */
    void initDatas();
    /**
     * @brief startupScheduler   开始任务调取器
     */
    void startupScheduler();
    /**
     * @brief ucout 日志输出
     * @param str
     */
    void ucout(const QString str);
private:
    Ui::Window *ui;
    RemoteUITaskScheduler *taskScheduler;
    QThread *remoteUIWorkThread;
};

#endif // WINDOW_H
