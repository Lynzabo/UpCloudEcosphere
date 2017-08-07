#ifndef EDITSCHEDULEWIDGET_H
#define EDITSCHEDULEWIDGET_H
#include <QtCore>
#include <QWidget>
#include "../../UpCloud-Service-Center/BusinessIServer/ScheduleIServer/bean/csrscsendaddr.h"
#include "../../UpCloud-Service-Center/BusinessIServer/ScheduleIServer/bean/csrscsendfiles.h"
#include "../../UpCloud-Service-Center/BusinessIServer/ScheduleIServer/bean/csrsctask.h"
#include "../../UpCloud-Service-Center/BusinessIServer/ScheduleIServer/bean/vcsascsendfiles.h"
namespace Ui {
class EditScheduleWidget;
}

class EditScheduleWidget : public QWidget
{
    Q_OBJECT

public:
    enum NodersTableHeaderElement {
        NODER_INDEX,
        NODER_CLIENT_UUID,
        NODER_NODER_NAME,
        NODER_GROUP,
        NODER_STATE,
        NODER_ERRINFO
    };
    enum FilesTableHeaderElement {
        FILES_INDEX,
        FILES_FILENAME,
        FILES_SENDTIME,
        FILES_STATE,
        FILES_ERRINFO
    };
    explicit EditScheduleWidget(QWidget *parent = 0);
    ~EditScheduleWidget();

    void setTaskUuid(const QString &value);

protected:
    void showEvent(QShowEvent *event);
public Q_SLOTS:
    /**
     * @brief on_nodeSelectedRow    节点服务器列表选中1行
     * @param selectedRow
     */
    void on_nodeSelectedRow(int selectedRow);
    /**
     * @brief on_nodeSelectedRows   节点服务器列表选中多行
     * @param selectedRows
     */
    void on_nodeSelectedRows(QList<int> selectedRows);
    /**
     * @brief on_nodeDoubleSelected 节点服务器列表双击1行
     * @param selectedRow
     */
    void on_nodeDoubleSelected(int selectedRow);
    /**
     * @brief on_filesSelectedRow    文件列表选中1行
     * @param selectedRow
     */
    void on_filesSelectedRow(int selectedRow);
    /**
     * @brief on_filesSelectedRows   文件列表选中多行
     * @param selectedRows
     */
    void on_filesSelectedRows(QList<int> selectedRows);
    /**
     * @brief on_filesDoubleSelected 文件列表双击1行
     * @param selectedRow
     */
    void on_filesDoubleSelected(int selectedRow);
private slots:
    void on_itemtaskCallback(const qint32 cbMsgId,const QString &msg);
    void on_itemtaskCallback(const qint32 cbMsgId,const QString &msg,const CsRScheduleTask &task);
    void on_itemtaskCallback(const qint32 cbMsgId,const QString &msg,const QList<CsRScheduleSendAddr> &addrList);
    void on_itemtaskCallback(const qint32 cbMsgId, const QString &msg, const QList<VCsAScSendFiles> &vFileList);
    void on_btn_quit_clicked();

    void on_btn_nodes_send_clicked();

    void on_btn_nodes_del_clicked();

    void on_btn_nodes_add_clicked();
    //增加节点服务器操作槽函数
    void on_addNodes();
    void on_btn_nodes_exec_clicked();

    void on_btn_files_del_clicked();

    void on_btn_save_clicked();

private:
    /**
     * @brief initWindow 初始化窗口
     */
    void initWindow();
    /**
     * @brief loadDatas 加载列表
     */
    void loadDatas();
    /**
     * @brief taskStateToIcon 设置任务状态图标
     * @param state
     * @return
     */
    QPixmap taskStateToIcon(const quint8 state);

    /**
     * @brief taskStateToText 设置任务状态描述
     * @param state
     * @return
     */
    QString taskStateToText(const quint8 state);
    /**
     * @brief nodesStateToText 设置地址状态描述
     * @param state
     * @return
     */
    QString nodesStateToText(const quint8 state);
    /**
     * @brief nodesStateToIcon  设置地址图标
     * @param state
     * @return
     */
    QIcon nodesStateToIcon(const quint8 state);
    /**
     * @brief filesStateToText  设置文件状态描述
     * @param state
     * @return
     */
    QString filesStateToText(const quint8 state);
    /**
     * @brief filesStateToIcon  设置文件状态图标
     * @param state
     * @return
     */
    QIcon filesStateToIcon(const quint8 state);
    /**
     * @brief loadComboBox 加载下拉框
     */
    void loadComboBox();
private:
    Ui::EditScheduleWidget *ui;
    QString taskUuid;
    CsRScheduleTask m_task;
    QStringList selectedNodesUuid;
    QList<CsRScheduleSendAddr> curNodesList;
    QStringList selectedFilesUuid;
    QList<CsRScheduleSendFiles> curFilesList;
    QList<VCsAScSendFiles> curVFilesList;
    //为添加节点服务器的两个参数 节点服务器列表  所属群组描述
    QStringList m_clientUuid;
    QStringList m_descriptionForGroup;
};

#endif // EDITSCHEDULEWIDGET_H
