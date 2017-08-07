#ifndef DIRNODEFILEWIDGET_H
#define DIRNODEFILEWIDGET_H

#include <QWidget>
#include "../../UpCloud-Service-Center/BusinessIServer/UnstructIServer/bean/csrusendstatus.h"
#include "../../UpCloud-Service-Center/BusinessIServer/StructIServer/bean/csrssendstatus.h"
#include "../../UpCloud-Service-Center/BusinessIServer/ScheduleIServer/bean/csrscsendstatus.h"
namespace Ui {
class DirNodeFileWidget;
}

class DirNodeFileWidget : public QWidget
{
    Q_OBJECT

public:
    enum TableHeaderElement {
        INDEX,
        CLIENT_UUID,
        NODE_NAME,
        FILE_NAME,
        STATE
    };
    enum NodeFileOperaTyple{
        UNSTRUCT,
        STRUCT,
        SCHEDULE
    };
    enum SendTyple{
        SendFile,
        SendNode
    };
    explicit DirNodeFileWidget(QWidget *parent = 0);
    ~DirNodeFileWidget();
    //加载数据列表
    void loadDatas(const QList<CsRUnstructSendStatus> statusList,const QStringList &fileNameList,const QStringList &nodeNameList);
    void loadDatas(const QList<CsRStructSendStatus> statusList,const QStringList &fileNameList,const QStringList &nodeNameList);
    void loadDatas(const QList<CsRScheduleSendStatus> statusList,const QStringList &fileNameList,const QStringList &nodeNameList);
signals:
    void evt_send();
private slots:
    void on_itemtaskCallback(const qint32 msgId, const QString &msg);
    /**
     * @brief on_nodeSelectedRow    列表选中1行
     * @param selectedRow
     */
    void on_selectedRow(int selectedRow);
    /**
     * @brief on_nodeSelectedRows   列表选中多行
     * @param selectedRows
     */
    void on_selectedRows(QList<int> selectedRows);
    /**
     * @brief on_nodeDoubleSelected 列表双击1行
     * @param selectedRow
     */
    void on_doubleSelected(int selectedRow);

    void on_btn_send_clicked();

    void on_btn_quit_clicked();

private:
    void initWindow();
    //重新下发
    void afreshSendToUnstruct();
    void afreshSendToStruct();
    void afreshSendToSchedule();
    //同步修改界面中的状态
    void updateState();
    /**
     * @brief stateIcon 设置任务状态图标
     * @param state
     * @return
     */
    QIcon stateToIconForUnstruct(const quint8 state);
    /**
     * @brief stateIcon 设置任务状态描述
     * @param state
     * @return
     */
    QString stateToTextForUnstruct(const quint8 state);
    /**
     * @brief stateIcon 设置任务状态图标
     * @param state
     * @return
     */
    QIcon stateToIconForStruct(const quint8 state);
    /**
     * @brief stateIcon 设置任务状态描述
     * @param state
     * @return
     */
    QString stateToTextForStruct(const quint8 state);
private:
    Ui::DirNodeFileWidget *ui;
    NodeFileOperaTyple operaType;

    //记录选中的行号
    QList<int> rowNum;
    QStringList selectedUUids;


    QList<CsRUnstructSendStatus> m_unstruct_List;

    QList<CsRStructSendStatus> m_struct_list;

    QList<CsRScheduleSendStatus> m_schedule_list;
};

#endif // DIRNODEFILEWIDGET_H
