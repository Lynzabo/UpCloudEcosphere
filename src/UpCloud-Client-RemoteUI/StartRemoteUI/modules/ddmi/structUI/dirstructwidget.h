#ifndef DIRSTRUCTWIDGET_H
#define DIRSTRUCTWIDGET_H

#include <QWidget>
#include "erm.h"
#include "modules/common/createtaskwidget.h"
#include "../../UpCloud-Service-Center/BusinessIServer/StructIServer/bean/csrstask.h"
#include "../../UpCloud-Service-Center/BusinessIServer/StructIServer/bean/csrssendaddr.h"
#include "../../UpCloud-Service-Center/BusinessIServer/StructIServer/bean/csrssendfiles.h"
#include "../../UpCloud-Service-Center/BusinessIServer/StructIServer/bean/csrssendstatus.h"
namespace Ui {
class DirStructWidget;
}

class DirStructWidget : public QWidget
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
    explicit DirStructWidget(QWidget *parent = 0);
    ~DirStructWidget();
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
     * @brief on_foldered 折叠
     */
    void on_foldered();

    void on_addTask();
private slots:
    void on_itemtaskCallback(const qint32 msgId, const QString &msg,bool flg = true);
    void on_itemtaskCallback(const qint32 msgId, const QString &msg, const QList<CsRStructTask> &taskList);
    /**
     * @brief on_btn_select_clicked 查询功能
     */
    void on_btn_select_clicked();
    /**
     * @brief on_btn_new_clicked  新建功能
     */
    void on_btn_new_clicked();
    void on_btn_del_clicked();

    void on_btn_open_clicked();

    void on_cb_setState_currentIndexChanged(int index);

    void on_btn_send_clicked();

    void on_btn_pause_clicked();

    void on_btn_folder_clicked();

private:
    void initWindow();
    /**
     * @brief initDatas 初始化参数
     */
    void initDatas();
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
     * @brief loadComboBoxText 加载下拉框的
     */
    void loadComboBoxText();
private:
    Ui::DirStructWidget *ui;

    Page* page;
    QList<CsRStructTask> curTaskList;
    QList<QString> selectedTaskUuids;

    CsRStructTask taskInfo;

    QList<CsRStructSendAddr> addrInfoList;
    QList<CsRStructSendFiles> fileInfoList;
    QList<CsRStructSendStatus> statusInfoList;

    QPoint oldPos;
    QPoint newPos;
    QPushButton* newBtn;

    //
};

#endif // DIRSTRUCTWIDGET_H
