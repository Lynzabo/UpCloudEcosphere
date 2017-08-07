#ifndef DIRSCHEDULEWIDGET_H
#define DIRSCHEDULEWIDGET_H

#include <QWidget>
#include <QtCore>
#include <QPushButton>
#include "baseiremote.h"
#include "base.h"
#include "../../UpCloud-Service-Center/BusinessIServer/ScheduleIServer/bean/csrsctask.h"
namespace Ui {
class DirScheduleWidget;
}

class DirScheduleWidget : public QWidget
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
    explicit DirScheduleWidget(QWidget *parent = 0);
    ~DirScheduleWidget();
private Q_SLOTS:
    /**
     * @brief on_selectedRow 选中一行
     * @param selectRow
     */
    void  on_selectedRow(int selectRow);
    /**
     * @brief on_selectedRows 选中多行
     * @param selectRows
     */
    void on_selectedRows(QList<int> selectRows);
    /**
     * @brief on_doubleSelected 双击一行
     * @param selectRow
     */
    void on_doubleSelected(int selectRow);
    /**
     * @brief on_btn_new_clicked 新建
     */
    void on_btn_new_clicked();
    /**
     * @brief on_foldered 折叠
     */
    void on_foldered();
private slots:
    void on_itemtaskCallback(const qint32 cbMsgId,const QString &msg);
    void on_itemtaskCallback(const qint32 cbMsgId,const QString &msg,const QList<CsRScheduleTask> &taskList);
    void showEvent(QShowEvent *event);
    void on_btn_select_clicked();

    void on_cb_setState_currentIndexChanged(int index);

    void on_btn_send_clicked();

    void on_btn_pause_clicked();

    void on_btn_open_clicked();

    void on_btn_del_clicked();

    void on_btn_folder_clicked();

private:
    /**
     * @brief initWindow 初始化控件
     */
    void initWindow();
    /**
     * @brief initDatas
     */
    void initDatas();
    /**
     * @brief loadDates 加载列表信息
     */
    void loadDates();
    /**
     * @brief loadComboBoxText 加载下拉框
     */
    void loadComboBoxText();
    /**
     * @brief stateToText 设置状态描述
     * @param state
     * @return
     */
    QString stateToText(const quint8 state);
    /**
     * @brief stateToIcon 设置状态图标
     * @param state
     * @return
     */
    QIcon stateToIcon(const quint8 state);
private:
    Ui::DirScheduleWidget *ui;
    QStringList selectedTaskUuids;
    //当前显示列表的内容
    QList<CsRScheduleTask> curTaskList;

    QPoint oldPos;
    QPoint newPos;
    QPushButton* newBtn;

};

#endif // DIRSCHEDULEWIDGET_H
