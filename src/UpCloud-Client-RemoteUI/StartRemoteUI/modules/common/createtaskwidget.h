#ifndef CREATETASKWIDGET_H
#define CREATETASKWIDGET_H

#include <QWidget>
#include <QtCore>
#include "combobox.h"
#include "tablewidget.h"
#include "createtaskinfo.h"
#include "grouptreewidget.h"
#include "fileinfolist.h"
#include "filedialog.h"
#include "../../UpCloud-Service-Center/BusinessIServer/BasalIServer/bean/cscgroup.h"
#include "../../UpCloud-Service-Center/BusinessIServer/BasalIServer/bean/cscgroupassoc.h"
#include "../../UpCloud-Service-Center/BusinessIServer/UnstructIServer/bean/csrutask.h"
#include "../../UpCloud-Service-Center/BusinessIServer/StructIServer/bean/csrstask.h"
#include "../../UpCloud-Service-Center/BusinessIServer/ScheduleIServer/bean/csrsctask.h"
#include "../../UpCloud-Service-Center/BusinessIServer/UnstructIServer/bean/csrusendaddr.h"
#include "../../UpCloud-Service-Center/BusinessIServer/UnstructIServer/bean/csrusendfiles.h"
#include "../../UpCloud-Service-Center/BusinessIServer/UnstructIServer/bean/csrusendstatus.h"
#include "../../UpCloud-Service-Center/BusinessIServer/StructIServer/bean/csrssendaddr.h"
#include "../../UpCloud-Service-Center/BusinessIServer/StructIServer/bean/csrssendfiles.h"
#include "../../UpCloud-Service-Center/BusinessIServer/StructIServer/bean/csrssendstatus.h"

namespace Ui {
class CreateTaskWidget;
}

class CreateTaskWidget : public QWidget
{
    Q_OBJECT

public:
    enum NodesTableHeaderElement {
        NODE_NAME,
        GROUP_DESCRIPTION
    };
    enum FilesTableHeaderElement {
        FILE_NAME,
        SRC_ABST,
        SAVE_ABST,
        WORK_ABST
    };
    enum OPERA_TYPE{
        UNSTRUCT_TYPE,
        STRUCT_TYPE,
        SCHEDULE_TYPE
    };
    explicit CreateTaskWidget(QWidget *parent = 0);
    void setAddTaskInfo(CsRUnstructTask* task,
                        QList<CsRUnstructSendAddr>* addrInfoList,
                        QList<CsRUnstructSendFiles>* fileInfoList,
                        QList<CsRUnstructSendStatus>* statusInfoList);
    void setAddTaskInfo(CsRStructTask* task,
                        QList<CsRStructSendAddr>* addrInfoList,
                        QList<CsRStructSendFiles>* fileInfoList,
                        QList<CsRStructSendStatus>* statusInfoList);
    ~CreateTaskWidget();
signals:
    //保存信号
    void evt_save();
private slots:
    //接收所有选中节点服务器信息
    void on_selectedNodes();
private:
    void initWindow();
    //添加任务信息是否有空的项
    bool taskInfoIsEmply();
    //为新添加任务显示关联表信息
    void loadDatas();
    //加载下拉框值
    void loadComboBox();

    //设置非结构化参数信息
    void setUnstructParams();
    //设置结构化参数信息
    void setStructParams();

    //修改保存路径
    void updateSaveAbst();
    //所有选中文件信息
    void showSelectedFiles();

    //设置文件参数信息
    bool setFileList();
public Q_SLOTS:
    /**
     * @brief on_selectedRow    选中1行
     * @param selectedRow
     */
    void on_nodesSelectedRow(int selectedRow);
    /**
     * @brief on_selectedRows   选中多行
     * @param selectedRows
     */
    void on_nodesSelectedRows(QList<int> selectedRows);
    /**
     * @brief on_doubleSelected 双击1行
     * @param selectedRow
     */
    void on_nodesDoubleSelected(int selectedRow);


    /**
     * @brief on_selectedRow    选中1行
     * @param selectedRow
     */
    void on_filesSelectedRow(int selectedRow);
    /**
     * @brief on_selectedRows   选中多行
     * @param selectedRows
     */
    void on_filesSelectedRows(QList<int> selectedRows);
    /**
     * @brief on_doubleSelected 双击1行
     * @param selectedRow
     */
    void on_filesDoubleSelected(int selectedRow);

private slots:

    void on_btn_save_clicked();

    void on_btn_quit_clicked();

    void on_btn_nodes_add_clicked();

    void on_btn_nodes_del_clicked();

    void on_btn_files_add_clicked();

    //启动选择文件界面
    //-----------------------------------begin---------------------------
    void on_selectFileSrcAbst();
    //启动选择文件夹界面
    void on_selectDirSrcAbst();
    //选择保存路径
    void on_selectSaveDir(const QString &dir);
    //选择本地文件
    void on_selectSrcFiles(const QStringList &files);
    //选择目录
    void on_selectSrcDir(const QString &url);
    //选择工作目录
    void on_selectWorkDir(const QString &dir);
    //选择文件夹所有文件展开为文件
    bool loadDirFiles(const QString &path,const QString &srcPath,const QString &SavePath);
    //-------------------------------------end-----------------------------
    void on_btn_set_saveAbst_clicked();

    void on_btn_files_del_clicked();

private:
    Ui::CreateTaskWidget *ui;

    QList<int> nodesSelectRows;
    QList<int> filesSelectRows;
    //新建任务信息列表
    QList<CreateTaskInfo> infoList;
    GroupTreeWidget* treeWidget;
    FileInfoList* fileDlg;

    QStringList selectedClientUuids;
    QStringList nodesDescription;

    //添加节点服务器信息标志
    bool addrFlag;
    //添加文件列表信息标志
    bool fileFlag;
    //非结构化任务实体
    CsRUnstructTask*  m_unstruct_task;
    QList<CsRUnstructSendAddr>* unstruct_addrInfoList;
    QList<CsRUnstructSendFiles>* unstruct_fileInfoList;
    QList<CsRUnstructSendStatus>* unstruct_statusInfoList;
    //结构化任务实体
    CsRStructTask*    m_struct_task;
    QList<CsRStructSendAddr>* struct_addrInfoList;
    QList<CsRStructSendFiles>* struct_fileInfoList;
    QList<CsRStructSendStatus>* struct_statusInfoList;

    CsRScheduleTask*  m_schedule_task;

    OPERA_TYPE m_operaType;

    //以下是添加文件所用到的变量
    //---------------------begin--------------------
    //选中行
    //文件来源信息列表
    QStringList m_filePathList;
    //选择保存目录
    QString m_selectSaveDir;
    //选择工作目录
    QString m_selectWorkDir;
    //选择本地目录
    QList<int> dirIndexList;
    //默认保存目录
    QString m_defaultSaveDir;
    //保存目录链表
    QStringList m_saveDirList;
    //当前文件信息
    QStringList m_curSelectFiles;


    //文件保存路径列表
    QStringList m_saveAbst;
    //文件来源目录链表
    QStringList m_srcAbst;

    //选择菜单

    QMenu* m_menu;

    //---------------------end--------------------
};

#endif // CREATETASKWIDGET_H
