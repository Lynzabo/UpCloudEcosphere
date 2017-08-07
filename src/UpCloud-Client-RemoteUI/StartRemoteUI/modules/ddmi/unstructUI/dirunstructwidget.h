#ifndef DIRUNSTRUCTWIDGET_H
#define DIRUNSTRUCTWIDGET_H

#include <QWidget>
#include "../../common/loading.h"
#include "page.h"
#include "modules/common/createtaskwidget.h"
#include "../../UpCloud-Service-Center/BusinessIServer/UnstructIServer/bean/csrutask.h"
#include "../../../../FrontBusinessIRemoteUI/DDMIRemoteUI/UnstructOperaIRemoteUI/unstructoperairemoteui.h"
namespace Ui {
class DirUnstructWidget;
}

class DirUnstructWidget : public QWidget
{
    Q_OBJECT
public:
    enum TableHeaderElement {
        INDEX,
        TASKNAME,
        SENDTIME,
        STRATEGY,
        STATE,
        INSERTOR
    };
public:
    explicit DirUnstructWidget(QWidget *parent = 0);
    ~DirUnstructWidget();
signals:
    void evt_addTaskSuccess();
protected:
    virtual void showEvent(QShowEvent *);
public Q_SLOTS:
    /**
     * @brief on_selectedRow    选中1行
     * @param selectedRow
     */
    void on_tableBodySelectedRow(int selectedRow);
    /**
     * @brief on_selectedRows   选中多行
     * @param selectedRows
     */
    void on_tableBodySelectedRows(QList<int> selectedRows);
    /**
     * @brief on_doubleSelected 双击1行
     * @param selectedRow
     */
    void on_tableBodyDoubleSelected(int selectedRow);
    /**
     * @brief on_tableBodySelectedNull  未选中表格体信号
     */
    void on_tableBodySelectedNull();

    /**
     * @brief on_pageTableAccept    分页表格联动信号
     * @param page
     */
    void on_pageTableAccept(const Page *page);
    /**
     * @brief on_addTask 新建一条任务
     */
    void on_addTask();
    /**
     * @brief on_fordered 折叠
     */
    void on_fordered();
private slots:
    void on_itemtaskCallback(const qint32 msgId, const QString &msg,bool flg = true);
    void on_itemtaskCallback(const qint32 msgId, const QString &msg, const QList<CsRUnstructTask> &taskList);
    void on_btn_new_clicked();

    void on_btn_open_clicked();

    void on_btn_select_clicked();

    void on_btn_del_clicked();

    void on_cb_setState_currentIndexChanged(int index);

    void on_btn_send_clicked();

    void on_btn_pause_clicked();

    void on_btn_folder_clicked();

private:
    /**
     * @brief initWindow    初始化窗口基本数据
     */
    void initWindow();
    /**
     * @brief loadDatas 加载数据
     */
    void loadDatas();
    /**
     * @brief stateIcon 设置任务状态图标
     * @param state
     * @return
     */
    QIcon stateToIcon(const quint8 state);
    /**
     * @brief stateIcon 设置任务状态描述
     * @param state
     * @return
     */
    QString stateToText(const quint8 state);
    /**
     * @brief strategyToText 设置任务策略描述
     * @param strategy
     * @return
     */
    QString strategyToText(const quint16 strategy);
    /**
     * @brief loadComboBoxText 加载下拉框信息
     */
    void loadComboBoxText();
    /**
     * @brief initData  初始化参数
     */
    void initData();
private:
    Ui::DirUnstructWidget *ui;
    Page* page;

    Loading *loading;
    CreateTaskWidget* newTaskWidget;
    QList<CsRUnstructTask> curTaskLists;
    //保存选中行索引,选中多行和单行都会更新.
    QList<QString> selectedTasksUUIDs;

    CsRUnstructTask taskInfo;

    QList<CsRUnstructSendAddr> addrInfoList;
    QList<CsRUnstructSendFiles> fileInfoList;
    QList<CsRUnstructSendStatus> statusInfoList;
    QPoint oldPos;
    QPoint newPos;
    QPushButton* newBtn;
};

#endif // DIRUNSTRUCTWIDGET_H
