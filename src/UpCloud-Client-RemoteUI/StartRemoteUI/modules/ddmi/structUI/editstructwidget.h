#ifndef EditStructWidget_H
#define EditStructWidget_H

#include <QWidget>
#include "dirstructwidget.h"
#include "erm.h"
#include "../../../../FrontBusinessIRemoteUI/DDMIRemoteUI/StructOperaIRemoteUI/structoperairemoteui.h"
#include "../../UpCloud-Service-Center/BusinessIServer/StructIServer/bean/csrstask.h"
#include "../../UpCloud-Service-Center/BusinessIServer/StructIServer/bean/csrssendfiles.h"
#include "../../UpCloud-Service-Center/BusinessIServer/StructIServer/bean/csrssendaddr.h"
#include "../../UpCloud-Service-Center/BusinessIServer/StructIServer/bean/vcsassendfiles.h"
#include "../../UpCloud-Service-Center/BusinessIServer/StructIServer/bean/vcssendaddr.h"
#include "../../UpCloud-Service-Center/BusinessIServer/StructIServer/bean/csrssendstatus.h"
namespace Ui {
class EditStructWidget;
}

class EditStructWidget : public QWidget
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
    explicit EditStructWidget(QWidget *parent = 0);
    ~EditStructWidget();
    void showEvent(QShowEvent *event);
    void setTaskUUID(const QString &uuid);
private slots:
    void on_itemtaskCallback(const qint32 msgId, const QString &msg);
    void on_itemtaskCallbackNode(const qint32 msgId, const QString &msg,const QList<CsRStructSendStatus> &statusList,const QStringList &nameList);
    void on_itemtaskCallbackFile(const qint32 msgId, const QString &msg,const QList<CsRStructSendStatus> &statusList,const QStringList &nameList);
    void on_itemtaskCallback(const qint32 msgId, const QString &msg, const CsRStructTask &task);
    void on_itemtaskCallback(const qint32 msgId, const QString &msg, const QList<VCsRStructSendAddr> &addrList);
    void on_itemtaskCallback(const qint32 msgId, const QString &msg, const QList<VCsRStructSendFiles> &fileList);
    void on_btn_addr_del_clicked();

    void on_btn_file_del_clicked();

    void on_btn_back_clicked();

    void on_btn_addr_add_clicked();

    void on_btn_addr_send_clicked();

    void on_btn_addr_open_clicked();

    void on_btn_file_open_clicked();

    void on_btn_file_send_clicked();

    void on_btn_file_add_clicked();

    void on_btn_save_clicked();

    void on_btn_addrForTask_clicked();

    void on_btn_fileForTask_clicked();

public Q_SLOTS:
    /**
     * @brief on_nodeSelectedRow    节点服务器列表选中1行
     * @param selectedRow
     */
    void on_tableBodyNodeSelectedRow(int selectedRow);
    /**
     * @brief on_nodeSelectedRows   节点服务器列表选中多行
     * @param selectedRows
     */
    void on_tableBodyNodeSelectedRows(QList<int> selectedRows);
    /**
     * @brief on_nodeDoubleSelected 节点服务器列表双击1行
     * @param selectedRow
     */
    void on_tableBodyNodeDoubleSelected(int selectedRow);
    /**
     * @brief on_tableBodyNodeSelectedNull 未点击表格信号
     */
    void on_tableBodyNodeSelectedNull();
    /**
     * @brief on_pageTableNodeAccept 分页表格联动
     * @param page
     */
    void on_pageTableNodeAccept(const Page *page);
    /**
     * @brief on_filesSelectedRow    文件列表选中1行
     * @param selectedRow
     */
    void on_tableBodyFileSelectedRow(int selectedRow);
    /**
     * @brief on_filesSelectedRows   文件列表选中多行
     * @param selectedRows
     */
    void on_tableBodyFileSelectedRows(QList<int> selectedRows);
    /**
     * @brief on_filesDoubleSelected 文件列表双击1行
     * @param selectedRow
     */
    void on_tableBodyFileDoubleSelected(int selectedRow);
    /**
     * @brief on_tableBodyFileSelectedNull 未点击表格信号
     */
    void on_tableBodyFileSelectedNull();
    /**
     * @brief on_pageTableFileAccept 分页表格联动
     * @param page
     */
    void on_pageTableFileAccept(const Page* page);
    /**
    * @brief on_addNodes 增加节点服务器
    */
    void on_addNodes();
    /**
     * @brief on_nodeFileWidgetSend 节点服务器与文件详请界面下发 重新加载数据
     */
    void on_nodeFileWidgetSend();
    /**
     * @brief on_addFile 为当前任务所有的节点服务器添加文件
     *
     */
    void on_addFile(const QStringList &filePathList, const QStringList &saveAbst);
private:
    /**
     * @brief initWindow
     */
    void initWindow();
    /**
     * @brief initDatas 初始化数据
     */
    void initDatas();
    /**
     * @brief loadData  加载数据
     */
    void loadDatas();
    /**
     * @brief taskStateIcon 设置任务状态图标
     * @param state
     * @return
     */
    QPixmap taskStateIcon(const quint8 state);
    /**
     * @brief taskStateToText 设置任务状态文本
     * @param state
     * @return
     */
    QString taskStateToText(const quint8 state);
    /**
     * @brief noderStateIcon 设置节点服务器状态图标
     * @param state
     * @return
     */
    QIcon noderStateToIcon(const quint8 state);
    /**
     * @brief noderStateToText 设置节点服务器状态文本
     * @param state
     * @return
     */
    QString noderStateToText(const quint8 state);
    /**
     * @brief filesStateIcon 设置文件状态图标
     * @param state
     * @return
     */
    QIcon filesStateToIcon(const quint8 state);
    /**
     * @brief filesStateToText 设置文件状态文本
     * @param state
     * @return
     */
    QString filesStateToText(const quint8 state);
    /**
     * @brief loadComboBox 加载下拉框
     */
    void loadComboBox();

    /**
     * @brief asyncLoadFile
     */
    void asyncLoadFile();
    /**
     * @brief asyncLoadAddr
     */
    void asyncLoadAddr();
private:
    Ui::EditStructWidget *ui;
    QString taskUUID;
    CsRStructTask m_task;

    QList<VCsRStructSendAddr> m_addrList;
    QList<VCsRStructSendFiles> m_fileList;

    QList<QString> selectedAddrUuids;
    QList<QString> selectedFileUuids;

    QStringList m_clientUuid;
    QStringList m_descriptionForGroup;

    QList<int> m_selectRowsForAddr;
    QList<int> m_selectRowsForFiles;
    //是否联动关联节点服务列表
    bool isUnionAddrs;
    //是否联动关联文件列表
    bool isUnionFiles;

    Page* nodesPage;
    Page* filesPage;

    //节点服务器与文件位置信息参数 如果是联动数据就保存，否则就切换到所有主位置下
    bool isSaveAddrPos;
    QString fileNamePos;
    bool isSaveFilePos;
    QString AddrNamePos;
};

#endif // EditStructWidget_H
