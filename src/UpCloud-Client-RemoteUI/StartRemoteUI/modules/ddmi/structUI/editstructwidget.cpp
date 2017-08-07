#include "editstructwidget.h"
#include <QDateTime>
#include "ui_editstructwidget.h"
#include "modules/common/uihelper.h"
#include "modules/common/grouptreewidget.h"
#include "modules/common/dirnodefilewidget.h"
#include "baseiremote.h"
#include "modules/common/fileinfolist.h"
using namespace RemoteUIEnvironment;
using namespace Environment::Task_Status::Center;
EditStructWidget::EditStructWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EditStructWidget)
{
    ui->setupUi(this);

    setAttribute(Qt::WA_DeleteOnClose);
    initWindow();
    initDatas();
}

void EditStructWidget::initWindow()
{
    //禁用下发按键 删除按键 添加按键
    ui->btn_addr_add->setEnabled(false);
    ui->btn_addr_del->setEnabled(false);
    ui->btn_addr_send->setEnabled(false);
    //设置节点服务器与关联文件显示位置为透明
    ui->lab_addr->setAttribute(Qt::WA_TranslucentBackground);
    ui->lab_addr_pos->setAttribute(Qt::WA_TranslucentBackground);
    ui->lab_file->setAttribute(Qt::WA_TranslucentBackground);
    ui->lab_file_pos->setAttribute(Qt::WA_TranslucentBackground);
    ////节点服务器列表
    //设置分页导航条可用
    ui->tw_nodes->setPageNavatorUsable(true);
    //设置表头
    //设置表头列数量
    ui->tw_nodes->table_body->horizontalHeader()->setVisible(true);
    ui->tw_nodes->table_body->setColumnCount(6);
    //设置表头每列标签
    ui->tw_nodes->table_body->setHeaderColumnLabel(EditStructWidget::NODER_INDEX,tr("序号","table_body"));
    ui->tw_nodes->table_body->setHeaderColumnLabel(EditStructWidget::NODER_CLIENT_UUID,tr("服务器固定码","table_body"));
    ui->tw_nodes->table_body->setHeaderColumnLabel(EditStructWidget::NODER_NODER_NAME,tr("节点服务器名","table_body"));
    ui->tw_nodes->table_body->setHeaderColumnLabel(EditStructWidget::NODER_GROUP,tr("groupNodess","table_body"));
    ui->tw_nodes->table_body->setHeaderColumnLabel(EditStructWidget::NODER_STATE,tr("nodeState","table_body"));
    ui->tw_nodes->table_body->setHeaderColumnLabel(EditStructWidget::NODER_ERRINFO,tr("error","table_body"));
    //设置表头每列宽比
    ui->tw_nodes->table_body->setHeaderColumnWidth(EditStructWidget::NODER_INDEX,  50);
    ui->tw_nodes->table_body->setHeaderColumnWidth(EditStructWidget::NODER_CLIENT_UUID,0.2);
    ui->tw_nodes->table_body->setHeaderColumnWidth(EditStructWidget::NODER_NODER_NAME,0.2);
    ui->tw_nodes->table_body->setHeaderColumnWidth(EditStructWidget::NODER_GROUP,0.2);
    ui->tw_nodes->table_body->setHeaderColumnWidth(EditStructWidget::NODER_STATE,100);
    ui->tw_nodes->table_body->setHeaderColumnWidth(EditStructWidget::NODER_ERRINFO,0.4);
    //设置表头每列对齐方式
    ui->tw_nodes->table_body->setHeaderColumnAlignment(EditStructWidget::NODER_INDEX,Qt::AlignRight | Qt::AlignCenter);
    //设置表头可排序列,默认为都不可排序
    //参数2的值是分页getOrderFieldName的值,使用该值做排序,因此命名名成数据库字段名,大小写保持与SQL语句一致
    ui->tw_nodes->table_body->setHeaderColumnCanSort(EditStructWidget::NODER_CLIENT_UUID,QString("CLIENT_UUID"));
    ui->tw_nodes->table_body->setHeaderColumnCanSort(EditStructWidget::NODER_NODER_NAME,QString("DESCRIPTION"));
    //    ui->tw_nodes->table_body->setHeaderColumnCanSort(EditStructWidget::NODER_STATE,QString("STATE"));
    //关联表格相关信号      一个线程,默认的是用direct，检查一下该用&
    //广播选中表格体1行
    connect(ui->tw_nodes,&PageTableWidget::evt_tableBodySelectedRow,this,&EditStructWidget::on_tableBodyNodeSelectedRow);
    //广播选中多行
    connect(ui->tw_nodes,&PageTableWidget::evt_tableBodySelectedRows,this,&EditStructWidget::on_tableBodyNodeSelectedRows);
    //广播双击1行
    connect(ui->tw_nodes,&PageTableWidget::evt_tableBodyDoubleSelected,this,&EditStructWidget::on_tableBodyNodeDoubleSelected);
    //广播选中空白区域
    connect(ui->tw_nodes,&PageTableWidget::evt_tableBodySelectedNull,this,&EditStructWidget::on_tableBodyNodeSelectedNull);
    //广播表格
    connect(ui->tw_nodes,&PageTableWidget::evt_pageTableAccept,this,&EditStructWidget::on_pageTableNodeAccept);




    ////文件列表
    //设置分页导航条可用
    ui->tw_files->setPageNavatorUsable(true);
    //设置表头
    //设置表头列数量
    ui->tw_files->table_body->horizontalHeader()->setVisible(true);
    ui->tw_files->table_body->setColumnCount(5);
    //设置表头每列标签
    ui->tw_files->table_body->setHeaderColumnLabel(EditStructWidget::FILES_INDEX,tr("序号","table_body"));
    ui->tw_files->table_body->setHeaderColumnLabel(EditStructWidget::FILES_FILENAME,tr("fileName","table_body"));
    ui->tw_files->table_body->setHeaderColumnLabel(EditStructWidget::FILES_SENDTIME,tr("下发时间","table_body"));
    ui->tw_files->table_body->setHeaderColumnLabel(EditStructWidget::FILES_STATE,tr("fileState","table_body"));
    ui->tw_files->table_body->setHeaderColumnLabel(EditStructWidget::FILES_ERRINFO,tr("错误描述","table_body"));
    //设置表头每列宽比
    ui->tw_files->table_body->setHeaderColumnWidth(EditStructWidget::FILES_INDEX,  50);
    ui->tw_files->table_body->setHeaderColumnWidth(EditStructWidget::FILES_FILENAME,0.3);
    ui->tw_files->table_body->setHeaderColumnWidth(EditStructWidget::FILES_SENDTIME,0.3);
    ui->tw_files->table_body->setHeaderColumnWidth(EditStructWidget::FILES_STATE,100);
    ui->tw_files->table_body->setHeaderColumnWidth(EditStructWidget::FILES_ERRINFO,0.4);
    //设置表头每列对齐方式
    ui->tw_files->table_body->setHeaderColumnAlignment(EditStructWidget::FILES_INDEX,Qt::AlignRight | Qt::AlignCenter);
    //设置表头可排序列,默认为都不可排序
    //参数2的值是分页getOrderFieldName的值,使用该值做排序,因此命名名成数据库字段名,大小写保持与SQL语句一致
    ui->tw_files->table_body->setHeaderColumnCanSort(EditStructWidget::FILES_FILENAME,QString("FILE_NAME"));
    //    ui->tw_files->table_body->setHeaderColumnCanSort(EditStructWidget::FILES_SENDTIME,QString("SEND_TIME"));
    //    ui->tw_files->table_body->setHeaderColumnCanSort(EditStructWidget::FILES_STATE,QString("STATE"));
    //关联表格相关信号      一个线程,默认的是用direct，检查一下该用&
    //广播选中表格体1行
    connect(ui->tw_files,&PageTableWidget::evt_tableBodySelectedRow,this,&EditStructWidget::on_tableBodyFileSelectedRow);
    //广播选中多行
    connect(ui->tw_files,&PageTableWidget::evt_tableBodySelectedRows,this,&EditStructWidget::on_tableBodyFileSelectedRows);
    //广播双击1行
    connect(ui->tw_files,&PageTableWidget::evt_tableBodyDoubleSelected,this,&EditStructWidget::on_tableBodyFileDoubleSelected);
    //广播选中空白区域
    connect(ui->tw_files,&PageTableWidget::evt_tableBodySelectedNull,this,&EditStructWidget::on_tableBodyFileSelectedNull);
    //广播表格
    connect(ui->tw_files,&PageTableWidget::evt_pageTableAccept,this,&EditStructWidget::on_pageTableFileAccept);
    loadComboBox();
}

void EditStructWidget::initDatas()
{
    //参数初始化
    taskUUID.clear();
    m_addrList.clear();
    m_fileList.clear();
    selectedAddrUuids.clear();
    selectedFileUuids.clear();
    m_clientUuid.clear();
    m_descriptionForGroup.clear();
    m_selectRowsForAddr.clear();
    m_selectRowsForFiles.clear();
    isUnionFiles = true;
    isUnionAddrs = true;
    isSaveAddrPos = false;
    fileNamePos.clear();
    isSaveFilePos = false;
    AddrNamePos.clear();
    //分页初始化
    nodesPage = new Page;
    filesPage = new Page;
}

void EditStructWidget::loadDatas()
{
    UIHelper::showLoading(this,tr("正在获取数据"));
    //加载信息
    ItemStructTaskRunnable* task = new ItemStructTaskRunnable(this);
    QVariantMap params;
    params["uuid"] = taskUUID;
    task->setTaskUuid(params);
    isUnionAddrs = true;
    isUnionFiles = true;
    isSaveAddrPos = false;
    isSaveFilePos = false;
    QThreadPool::globalInstance()->start(task);


}

QPixmap EditStructWidget::taskStateIcon(const quint8 state)
{
    QPixmap taskIcon;
    QSize iconSize(15,15);
    switch (state) {
    case Stru::Task_State::DISCARD:
        taskIcon = QPixmap(":/ddmi/struct/imgs/STATE_DISCARD");
        break;
    case Stru::Task_State::PRESEND:
        taskIcon = QPixmap(":/ddmi/struct/imgs/STATE_PRESEND");
        break;
    case Stru::Task_State::SENDING:
        taskIcon = QPixmap(":/ddmi/struct/imgs/STATE_SENDING");
        break;
    case Stru::Task_State::ADDRISNULL:
        taskIcon = QPixmap(":/ddmi/struct/imgs/STATE_ADDRISNULL");
        break;
    case Stru::Task_State::SENDERROR:
        taskIcon = QPixmap(":/ddmi/struct/imgs/STATE_SENDERROR");
        break;
    case Stru::Task_State::SENDSUCCESS:
        taskIcon = QPixmap(":/ddmi/struct/imgs/STATE_SENDSUCCESS");
        break;
    case Stru::Task_State::DOWNERROR:
        taskIcon = QPixmap(":/ddmi/struct/imgs/STATE_DOWNERROR");
        break;
    case Stru::Task_State::DOWNSUCCESS:
        taskIcon = QPixmap(":/ddmi/struct/imgs/STATE_DOWNSUCCESS");
        break;
    case Stru::Task_State::PARSEERROR:
        taskIcon = QPixmap(":/ddmi/struct/imgs/STATE_PARSEERROR");
        break;
    case Stru::Task_State::PARSESUCCESS:
        taskIcon = QPixmap(":/ddmi/struct/imgs/STATE_PARSESUCCESS");
        break;
    case Stru::Task_State::TASKERROR:
        taskIcon = QPixmap(":/ddmi/struct/imgs/STATE_TASKERROR");
        break;
    case Stru::Task_State::TASKSUCCESS:
        taskIcon = QPixmap(":/ddmi/struct/imgs/STATE_TASKSUCCESS");
        break;
    case Stru::Task_State::PAUSE:
        taskIcon = QPixmap(":/ddmi/struct/imgs/STATE_PAUSE");
        break;
    default:
        break;
    }
    QPixmap stateIcon = taskIcon.scaled(iconSize);
    return stateIcon;
}

QString EditStructWidget::taskStateToText(const quint8 state)
{
    //TODO  已修改完整
    QString text;
    switch (state) {
    case Stru::Task_State::DISCARD:
        text = tr("废弃");
        break;
    case Stru::Task_State::USABLE:
        text = tr("可用");
        break;
    case Stru::Task_State::PRESEND:
        text = tr("准备下发");
        break;
    case Stru::Task_State::SENDING:
        text = tr("正在下发");
        break;
    case Stru::Task_State::ADDRISNULL:
        text = tr("目标地址为空");
        break;
    case Stru::Task_State::SENDERROR:
        text = tr("下发错误");
        break;
    case Stru::Task_State::SENDSUCCESS:
        text = tr("下发成功");
        break;
    case Stru::Task_State::DOWNERROR:
        text = tr("下载错误");
        break;
    case Stru::Task_State::DOWNSUCCESS:
        text = tr("下载成功");
        break;
    case Stru::Task_State::PARSEERROR:
        text = tr("解析失败");
        break;
    case Stru::Task_State::PARSESUCCESS:
        text = tr("解析成功");
        break;
    case Stru::Task_State::TASKERROR:
        text = tr("任务处理失败");
        break;
    case Stru::Task_State::TASKSUCCESS:
        text = tr("任务处理成功");
        break;
    case Stru::Task_State::PAUSE:
        text = tr("pause");
        break;
    case Stru::Task_State::CACHEING:
        text = tr("cache");
        break;
    default:
        break;
    }
    return text;
}

QIcon EditStructWidget::noderStateToIcon(const quint8 state)
{
    //TODO 已修改完整
    QIcon icon;
    switch (state) {
    case Stru::SendStatus_State::DISCARD:
        icon = QIcon(":/ddmi/struct/imgs/STATE_DISCARD");
        break;
    case Stru::SendStatus_State::USABLE:
        icon = QIcon(":/ddmi/struct/imgs/STATE_USABLE");
        break;
    case Stru::SendStatus_State::PRESEND:
        icon = QIcon(":/ddmi/struct/imgs/STATE_PRESEND");
        break;
    case Stru::SendStatus_State::SENDING:
        icon = QIcon(":/ddmi/struct/imgs/STATE_SENDING");
        break;
    case Stru::SendStatus_State::SENDERROR:
        icon = QIcon(":/ddmi/struct/imgs/STATE_SENDERROR");
        break;
    case Stru::SendStatus_State::SENDSUCCESS:
        icon = QIcon(":/ddmi/struct/imgs/STATE_SENDSUCCESS");
        break;
    case Stru::SendStatus_State::DOWNERROR:
        icon = QIcon(":/ddmi/struct/imgs/STATE_DOWNERROR");
        break;
    case Stru::SendStatus_State::DOWNSUCCESS:
        icon = QIcon(":/ddmi/struct/imgs/STATE_DOWNSUCCESS");
        break;
    case Stru::SendStatus_State::PARSEERROR:
        icon = QIcon(":/ddmi/struct/imgs/STATE_PARSEERROR");
        break;
    case Stru::SendStatus_State::PARSESUCCESS:
        icon = QIcon(":/ddmi/struct/imgs/STATE_PARSESUCCESS");
        break;
    default:
        break;
    }
    return icon;
}

QString EditStructWidget::noderStateToText(const quint8 state)
{
    //TODO  已修改完整
    QString text;
    switch (state) {
    case Stru::SendStatus_State::DISCARD:
        text = tr("废弃");
        break;
    case Stru::SendStatus_State::USABLE:
        text = tr("可用");
        break;
    case Stru::SendStatus_State::PRESEND:
        text = tr("准备下发");
        break;
    case Stru::SendStatus_State::SENDING:
        text = tr("正在下发");
        break;
    case Stru::SendStatus_State::SENDERROR:
        text = tr("下发错误");
        break;
    case Stru::SendStatus_State::SENDSUCCESS:
        text = tr("下发成功");
        break;
    case Stru::SendStatus_State::DOWNERROR:
        text = tr("下载错误");
        break;
    case Stru::SendStatus_State::DOWNSUCCESS:
        text = tr("下载成功");
        break;
    case Stru::SendStatus_State::PARSEERROR:
        text = tr("解析失败");
        break;
    case Stru::SendStatus_State::PARSESUCCESS:
        text = tr("解析成功");
        break;
    default:
        break;
    }
    return text;
}

QIcon EditStructWidget::filesStateToIcon(const quint8 state)
{
    //TODO  已修改完整
    QIcon icon;
    switch (state) {
    case Stru::SendStatus_State::DISCARD:
        icon = QIcon(":/ddmi/struct/imgs/STATE_DISCARD");
        break;
    case Stru::SendStatus_State::PRESEND:
        icon = QIcon(":/ddmi/struct/imgs/STATE_PRESEND");
        break;
    case Stru::SendStatus_State::SENDING:
        icon = QIcon(":/ddmi/struct/imgs/STATE_SENDING");
        break;
    case Stru::SendStatus_State::SENDERROR:
        icon = QIcon(":/ddmi/struct/imgs/STATE_SENDERROR");
        break;
    case Stru::SendStatus_State::SENDSUCCESS:
        icon = QIcon(":/ddmi/struct/imgs/STATE_SENDSUCCESS");
        break;
    case Stru::SendStatus_State::DOWNERROR:
        icon = QIcon(":/ddmi/struct/imgs/STATE_DOWNERROR");
        break;
    case Stru::SendStatus_State::DOWNSUCCESS:
        icon = QIcon(":/ddmi/struct/imgs/STATE_DOWNSUCCESS");
        break;
    case Stru::SendStatus_State::PARSEERROR:
        icon = QIcon(":/ddmi/struct/imgs/STATE_PARSEERROR");
        break;
    case Stru::SendStatus_State::PARSESUCCESS:
        icon = QIcon(":/ddmi/struct/imgs/STATE_PARSESUCCESS");
        break;
    default:
        break;
    }
    return icon;
}

QString EditStructWidget::filesStateToText(const quint8 state)
{
    //TODO  已修改完整
    QString text;
    switch (state) {
    case Stru::SendStatus_State::DISCARD:
        text = tr("废弃");
        break;
    case Stru::SendStatus_State::USABLE:
        text = tr("可用");
        break;
    case Stru::SendStatus_State::PRESEND:
        text = tr("准备下发");
        break;
    case Stru::SendStatus_State::SENDING:
        text = tr("正在下发");
        break;
    case Stru::SendStatus_State::SENDERROR:
        text = tr("下发错误");
        break;
    case Stru::SendStatus_State::SENDSUCCESS:
        text = tr("下发成功");
        break;
    case Stru::SendStatus_State::DOWNERROR:
        text = tr("下载错误");
        break;
    case Stru::SendStatus_State::DOWNSUCCESS:
        text = tr("下载成功");
        break;
    case Stru::SendStatus_State::PARSEERROR:
        text = tr("解析失败");
        break;
    case Stru::SendStatus_State::PARSESUCCESS:
        text = tr("解析成功");
        break;
    default:
        break;
    }
    return text;
}

void EditStructWidget::loadComboBox()
{
    ui->cb_strategy->clear();
    QStringList textList;
    textList << tr("默认策略");

    QStringList valueList;
    valueList << tr("1");

    ui->cb_strategy->setShowInfo(textList,valueList);
}

void EditStructWidget::asyncLoadFile()
{
    if(!isUnionFiles) {
        return;
    }
    UIHelper::showLoading(this,tr("获取关联数据 ..."));

    ListStructFileRunnable* list_file = new ListStructFileRunnable(this);
    QString taskUuid = m_task.getUuid();
    list_file->setListCondition(taskUuid);
    list_file->setFilterPage(this->filesPage);
    QThreadPool::globalInstance()->start(list_file);
}

void EditStructWidget::asyncLoadAddr()
{
    if(!isUnionAddrs) {
        return;
    }
    UIHelper::showLoading(this,tr("获取任务节点服务数据..."));
    ListStructAddrRunnable* addr = new ListStructAddrRunnable(this);
    QString taskUuid = m_task.getUuid();
    addr->setTaskUuid(taskUuid);
    addr->setFilterPage(this->nodesPage);
    QThreadPool::globalInstance()->start(addr);
}

void EditStructWidget::on_nodeFileWidgetSend()
{
    loadDatas();
}

void EditStructWidget::on_addFile(const QStringList &filePathList, const QStringList &saveAbst)
{
    UIHelper::showLoading(this,tr("正在添加文件"));
    AddStructTaskFileRunnable* file = new AddStructTaskFileRunnable(this);
    QList<CsRStructSendFiles> fileList;
    for(int i = 0;i < filePathList.size(); ++i) {
        CsRStructSendFiles sendFile;
        QString pathStr = filePathList.at(i);
        int index = pathStr.lastIndexOf("/");
        QString fileName = pathStr.right(pathStr.size() - index -1);
        sendFile.setFileName(fileName);
        sendFile.setSaveAbst(saveAbst.at(i));
        fileList.append(sendFile);
    }
    file->setAddCondition(taskUUID,fileList,m_addrList);
    QThreadPool::globalInstance()->start(file);
}


EditStructWidget::~EditStructWidget()
{
    delete ui;
}

void EditStructWidget::showEvent(QShowEvent *event)
{
    loadDatas();
}

void EditStructWidget::setTaskUUID(const QString &uuid)
{
    taskUUID = uuid;
}

void EditStructWidget::on_itemtaskCallback(const qint32 msgId, const QString &msg)
{
    if(msgId != CallbackStatus::Struct::_0){
        UIHelper::hideLoading(this);
        UIHelper::ShowMessageBoxError(msg);
        return;
    }
    loadDatas();
    UIHelper::hideLoading(this);
}

void EditStructWidget::on_itemtaskCallbackNode(const qint32 msgId, const QString &msg, const QList<CsRStructSendStatus> &statusList, const QStringList &nameList)
{
    if(msgId != CallbackStatus::Struct::_0)
    {
        UIHelper::hideLoading(this);
        UIHelper::ShowMessageBoxError(msg);
        return;
    }
    //    DirNodeFileWidget* nodeInfo = new DirNodeFileWidget;
    //    connect(nodeInfo,SIGNAL(evt_send()),this,SLOT(on_nodeFileWidgetSend()));
    //    VCsRStructSendAddr addr = m_addrList.at(m_selectRowsForAddr.at(0));
    //    //这里要取出节点服务器名字
    //    QStringList nodeName;
    //    nodeName << addr.getDescription();
    //    nodeInfo->loadDatas(statusList,nameList,nodeName);
    //    nodeInfo->show();
    //    UIHelper::hideLoading(this);
    ui->tw_content->setCurrentIndex(1);
    ui->tw_files->setPage(this->filesPage);
    ui->tw_files->table_body->clearContents();
    ui->tw_files->table_body->setRowCount(statusList.size());

    VCsRStructSendAddr addr = m_addrList.at(m_selectRowsForAddr.at(0));
    ui->lab_file_pos->setText(addr.getClientUuid());
    fileNamePos = addr.getClientUuid();
    for(int i = 0;i < statusList.size(); ++i)
    {
        CsRStructSendStatus status = statusList.at(i);
        QTableWidgetItem* item1 = new QTableWidgetItem;
        item1->setIcon(filesStateToIcon(status.getState()));
        item1->setText(QString("%1").arg(i));
        ui->tw_files->table_body->setItem(i,FilesTableHeaderElement::FILES_INDEX,item1);

        QTableWidgetItem* item2 = new QTableWidgetItem;
        //        QString fileUUid = status.getSendFileUuid();
        //        QString fileName;fileName.clear();
        //        foreach(const VCsRStructSendFiles &file,m_fileList) {
        //            if(fileUUid == file.getUuid()) {
        //                fileName = file.getFileName();
        //            }
        //        }
        item2->setText(nameList.at(i));
        ui->tw_files->table_body->setItem(i,FilesTableHeaderElement::FILES_FILENAME,item2);

        QTableWidgetItem* item3 = new QTableWidgetItem;
        item3->setText(status.getTaskUuid());
        ui->tw_files->table_body->setItem(i,FilesTableHeaderElement::FILES_SENDTIME,item3);


        QTableWidgetItem* item4 = new QTableWidgetItem;
        item4->setText(filesStateToText(status.getState()));
        ui->tw_files->table_body->setItem(i,FilesTableHeaderElement::FILES_STATE,item4);

        QTableWidgetItem* item5 = new QTableWidgetItem;
        item5->setText(status.getError());
        ui->tw_files->table_body->setItem(i,FilesTableHeaderElement::FILES_ERRINFO,item5);
    }
    UIHelper::hideLoading(this);
}

void EditStructWidget::on_itemtaskCallbackFile(const qint32 msgId, const QString &msg, const QList<CsRStructSendStatus> &statusList, const QStringList &nameList)
{
    if(msgId != CallbackStatus::Struct::_0)
    {
        UIHelper::hideLoading(this);
        UIHelper::ShowMessageBoxError(msg);
        return;
    }
    //    DirNodeFileWidget* fileInfo = new DirNodeFileWidget;
    //    connect(fileInfo,SIGNAL(evt_send()),this,SLOT(on_nodeFileWidgetSend()));
    //    VCsRStructSendFiles file = m_fileList.at(m_selectRowsForFiles.at(0));
    //    //这里要取出文件名字
    //    QStringList fileName;
    //    fileName << file.getFileName();
    //    fileInfo->loadDatas(statusList,fileName,nameList);
    //    fileInfo->show();
    //    UIHelper::hideLoading(this);
    ui->tw_content->setCurrentIndex(0);
    ui->tw_nodes->setPage(this->nodesPage);
    ui->tw_nodes->table_body->clearContents();
    ui->tw_nodes->table_body->setRowCount(statusList.size());
    VCsRStructSendFiles file = m_fileList.at(m_selectRowsForFiles.at(0));
    ui->lab_addr_pos->setText(file.getFileName());
    AddrNamePos = file.getFileName();
    for(int i = 0;i < statusList.size(); ++i)
    {
        CsRStructSendStatus status = statusList.at(i);
        QTableWidgetItem* item1 = new QTableWidgetItem;
        //TODO 执行策略 需要商讨 获取节点服务器状态
        item1->setIcon(noderStateToIcon(status.getState()));
        item1->setText(QString("%1").arg(i));
        ui->tw_nodes->table_body->setItem(i,NodersTableHeaderElement::NODER_INDEX,item1);

        QTableWidgetItem* item2 = new QTableWidgetItem;
        item2->setText(status.getClientUuid());
        ui->tw_nodes->table_body->setItem(i,NodersTableHeaderElement::NODER_CLIENT_UUID,item2);

        //        QString addrUuid = status.getSendAddrUuid();
        //        QString groupDesc;
        //        foreach(const VCsRStructSendAddr &addr,m_addrList) {
        //            if(addrUuid == addr.getUuid()) {
        //                groupDesc = addr.getGroupDesc();
        //            }
        //        }
        QTableWidgetItem* item3 = new QTableWidgetItem;
        item3->setText(nameList.at(i));
        ui->tw_nodes->table_body->setItem(i,NodersTableHeaderElement::NODER_NODER_NAME,item3);

        //TODO 以后需要获取该节点服务器所属群组
        QTableWidgetItem* item4 = new QTableWidgetItem;
        item4->setText(nameList.at(i + statusList.size()));
        ui->tw_nodes->table_body->setItem(i,NodersTableHeaderElement::NODER_GROUP,item4);

        QTableWidgetItem* item5 = new QTableWidgetItem;
        //TODO 执行策略 需要商讨 获取节点服务器状态
        item5->setText(noderStateToText(status.getState()));
        ui->tw_nodes->table_body->setItem(i,NodersTableHeaderElement::NODER_STATE,item5);

        //TODO 界面中的错误描述 需要吗？
        QTableWidgetItem* item6 = new QTableWidgetItem;
        item6->setText(status.getError());
        ui->tw_nodes->table_body->setItem(i,NodersTableHeaderElement::NODER_ERRINFO,item6);
    }
    UIHelper::hideLoading(this);
}


void EditStructWidget::on_itemtaskCallback(const qint32 msgId, const QString &msg, const CsRStructTask &task)
{
    if(msgId != CallbackStatus::Struct::_0){
        UIHelper::hideLoading(this);
        UIHelper::ShowMessageBoxError(msg);
        return;
    }
    else {
        UIHelper::showLoading(this,tr("获取数据成功，正在读取展示 ..."));
        m_task = task;
        ui->lab_num->setText(QString::number(task.getTaskNum()));
        ui->l_taskName->setText(task.getTaskName());
        ui->te_description->setText(task.getDescription());
        quint8 state = task.getState();
        ui->lab_state->setText(taskStateToText(state));
        //按键可用  下发 删除 添加
        if(state == Stru::Task_State::USABLE || state == Stru::Task_State::DOWNERROR
                || state == Stru::Task_State::SENDERROR || state == Stru::Task_State::TASKERROR
                || state == Stru::Task_State::PARSEERROR) {
            ui->btn_addr_add->setEnabled(true);
            ui->btn_addr_del->setEnabled(true);
            ui->btn_addr_send->setEnabled(true);
        }
        else {
            ui->btn_addr_add->setEnabled(false);
            ui->btn_addr_del->setEnabled(false);
            ui->btn_addr_send->setEnabled(false);
        }
        ui->lab_icon->setPixmap(taskStateIcon(task.getState()));
        //TODO 暂时写死
        ui->cb_strategy->setCurrentIndex(0);
        ui->lab_insertor->setText(task.getInsertor());
        ui->lab_time->setText(task.getInsertTime());
        QDateTime time = QDateTime::fromString(task.getSendTime(),"yyyy-MM-dd HH:mm:ss");
        ui->dte_send->setDateTime(time);
        ui->dte_exec->setDateTime(time);
        //加载下发地址
        asyncLoadAddr();
    }
}

void EditStructWidget::on_itemtaskCallback(const qint32 msgId, const QString &msg, const QList<VCsRStructSendAddr> &addrList)
{
    if(msgId != CallbackStatus::Struct::_0){
        UIHelper::hideLoading(this);
        UIHelper::ShowMessageBoxError(msg);
        return;
    }
    int i = 0 ;
    ui->tw_nodes->setPage(this->nodesPage);
    ui->tw_nodes->table_body->setRowCount(addrList.size());
    this->m_addrList = addrList;
    if(isSaveAddrPos) {
        ui->lab_addr_pos->setText(AddrNamePos);
    }
    else {

        ui->lab_addr_pos->setText(tr("allFiles"));
    }
    for(i = 0;i < m_addrList.size(); ++i) {
        VCsRStructSendAddr addr = m_addrList.at(i);
        QTableWidgetItem* item1 = new QTableWidgetItem;
        item1->setIcon(noderStateToIcon(addr.getState()));
        item1->setText(QString("%1").arg(i));
        ui->tw_nodes->table_body->setItem(i,NodersTableHeaderElement::NODER_INDEX,item1);

        QTableWidgetItem* item2 = new QTableWidgetItem;
        item2->setText(addr.getClientUuid());
        ui->tw_nodes->table_body->setItem(i,NodersTableHeaderElement::NODER_CLIENT_UUID,item2);

        QTableWidgetItem* item3 = new QTableWidgetItem;
        item3->setText(addr.getDescription());
        ui->tw_nodes->table_body->setItem(i,NodersTableHeaderElement::NODER_NODER_NAME,item3);


        QTableWidgetItem* item4 = new QTableWidgetItem;
        item4->setText(addr.getGroupDesc());
        ui->tw_nodes->table_body->setItem(i,NodersTableHeaderElement::NODER_GROUP,item4);

        QTableWidgetItem* item5 = new QTableWidgetItem;
        item5->setText(noderStateToText(addr.getState()));
        ui->tw_nodes->table_body->setItem(i,NodersTableHeaderElement::NODER_STATE,item5);

        QTableWidgetItem* item6 = new QTableWidgetItem;
        item6->setText(tr("成功"));
        ui->tw_nodes->table_body->setItem(i,NodersTableHeaderElement::NODER_ERRINFO,item6);
        UIHelper::hideLoading(this);
    }

    //加载下发文件
    asyncLoadFile();

}

void EditStructWidget::on_itemtaskCallback(const qint32 msgId, const QString &msg, const QList<VCsRStructSendFiles> &fileList)
{
    if(msgId != CallbackStatus::Struct::_0){
        UIHelper::hideLoading(this);
        UIHelper::ShowMessageBoxError(msg);
        return;
    }
    int i = 0 ;
    ui->tw_files->setPage(this->filesPage);
    ui->tw_files->table_body->setRowCount(fileList.size());
    m_fileList = fileList;
    if(isSaveFilePos) {
        ui->lab_file_pos->setText(fileNamePos);
    }
    else {

        ui->lab_file_pos->setText(tr("allNodes"));
    }
    for(i = 0;i < m_fileList.size(); ++i) {
        VCsRStructSendFiles sendFile = fileList.at(i);
        QTableWidgetItem* item1 = new QTableWidgetItem;
        item1->setIcon(filesStateToIcon(sendFile.getState()));
        item1->setText(QString("%1").arg(i));
        ui->tw_files->table_body->setItem(i,FilesTableHeaderElement::FILES_INDEX,item1);

        QTableWidgetItem* item2 = new QTableWidgetItem;
        item2->setText(sendFile.getFileName());
        ui->tw_files->table_body->setItem(i,FilesTableHeaderElement::FILES_FILENAME,item2);

        QTableWidgetItem* item3 = new QTableWidgetItem;
        item3->setText(sendFile.getTaskUuid());
        ui->tw_files->table_body->setItem(i,FilesTableHeaderElement::FILES_SENDTIME,item3);


        QTableWidgetItem* item4 = new QTableWidgetItem;
        item4->setText(filesStateToText(sendFile.getState()));
        ui->tw_files->table_body->setItem(i,FilesTableHeaderElement::FILES_STATE,item4);

        QTableWidgetItem* item5 = new QTableWidgetItem;
        item5->setText(tr("成功"));
        ui->tw_files->table_body->setItem(i,FilesTableHeaderElement::FILES_ERRINFO,item5);
    }
    UIHelper::hideLoading(this);
}

void EditStructWidget::on_tableBodyNodeSelectedRow(int selectedRow)
{
    //单击事件
    selectedAddrUuids.clear();
    m_selectRowsForAddr.clear();
    m_selectRowsForAddr.append(selectedRow);
    selectedAddrUuids.append(m_addrList.at(selectedRow).getClientUuid());
}

void EditStructWidget::on_tableBodyNodeSelectedRows(QList<int> selectedRows)
{
    //多选事件
    selectedAddrUuids.clear();
    m_selectRowsForAddr.clear();
    m_selectRowsForAddr.append(selectedRows);
    for(int i:selectedRows) {
        QString uuid = m_addrList.at(i).getClientUuid();
        selectedAddrUuids.append(uuid);
    }
}

void EditStructWidget::on_tableBodyNodeDoubleSelected(int selectedRow)
{
    //双击事件
    isSaveFilePos = true;
    selectedAddrUuids.clear();
    m_selectRowsForAddr.clear();
    m_selectRowsForAddr.append(selectedRow);
    selectedAddrUuids.append(m_addrList.at(selectedRow).getClientUuid());
    UIHelper::showLoading(this,tr("正在查询文件信息"));
    ListStructSendStatusRunnable* status = new ListStructSendStatusRunnable(this);
    status->setNodeUuid(taskUUID,selectedAddrUuids.at(0));
    status->setFilterPage(this->filesPage);
    QThreadPool::globalInstance()->start(status);
}

void EditStructWidget::on_tableBodyNodeSelectedNull()
{

    selectedAddrUuids.clear();
}

void EditStructWidget::on_pageTableNodeAccept(const Page *page)
{
    *nodesPage = *page;
    isUnionAddrs = true;
    isUnionFiles = false;
    asyncLoadAddr();
}

void EditStructWidget::on_tableBodyFileSelectedRow(int selectedRow)
{
    //单击事件
    selectedFileUuids.clear();
    m_selectRowsForFiles.clear();
    m_selectRowsForFiles.append(selectedRow);
    selectedFileUuids.append(m_fileList.at(selectedRow).getUuid());
}

void EditStructWidget::on_tableBodyFileSelectedRows(QList<int> selectedRows)
{
    //多选事件
    selectedFileUuids.clear();
    m_selectRowsForFiles.clear();
    m_selectRowsForFiles.append(selectedRows);
    for(int i:selectedRows) {
        QString uuid = m_fileList.at(i).getUuid();
        selectedFileUuids.append(uuid);
    }
}

void EditStructWidget::on_tableBodyFileDoubleSelected(int selectedRow)
{
    //双击事件
    isSaveAddrPos = true;
    selectedFileUuids.clear();
    m_selectRowsForFiles.clear();
    m_selectRowsForFiles.append(selectedRow);
    selectedFileUuids.append(m_fileList.at(selectedRow).getUuid());
    UIHelper::showLoading(this,tr("正在查询节点信息"));
    ListStructSendStatusRunnable* status = new ListStructSendStatusRunnable(this);

    status->setFileName(taskUUID,selectedFileUuids.at(0));
    status->setFilterPage(this->nodesPage);
    QThreadPool::globalInstance()->start(status);
}

void EditStructWidget::on_tableBodyFileSelectedNull()
{

    selectedFileUuids.clear();
}

void EditStructWidget::on_pageTableFileAccept(const Page *page)
{
    *(this->filesPage) = *page;
    isUnionFiles = true;
    isUnionAddrs = false;
    asyncLoadFile();
}

void EditStructWidget::on_addNodes()
{
    AddStructTaskAddrRunnable* addr = new AddStructTaskAddrRunnable(this);
    addr->setAddCondition(m_clientUuid,taskUUID,m_descriptionForGroup);
    QThreadPool::globalInstance()->start(addr);
}

void EditStructWidget::on_btn_addr_del_clicked()
{
    if(selectedAddrUuids.isEmpty()) {
        return;
    }
    int ok = UIHelper::ShowMessageBoxQuesion(tr("你确定要删除记录吗?"));
    if(!ok) {
        return;
    }
    UIHelper::showLoading(this,tr("正在删除"));
    DelStructTaskAddrRunnable* addr = new DelStructTaskAddrRunnable(this);
    JsonArray params;params.clear();
    foreach(const QString &uuid,selectedAddrUuids) {
        params.push_back(uuid);
    }
    addr->setAddrInfo(params,taskUUID);
    QThreadPool::globalInstance()->start(addr);
}

void EditStructWidget::on_btn_file_del_clicked()
{
    if(selectedFileUuids.isEmpty()) {
        return;
    }
    int ok = UIHelper::ShowMessageBoxQuesion(tr("你确定要删除记录吗?"));
    if(!ok) {
        return;
    }
    DelStructTaskFileRunnable* file = new DelStructTaskFileRunnable(this);
    JsonArray params;params.clear();
    foreach(const QString &uuid,selectedFileUuids) {
        params.push_back(uuid);
    }
    file->setFileInfo(taskUUID,params);
    QThreadPool::globalInstance()->start(file);
}

void EditStructWidget::on_btn_back_clicked()
{
    UIHelper::OpenInSelf(this,new DirStructWidget);
}

void EditStructWidget::on_btn_addr_add_clicked()
{
    GroupTreeWidget* widget = new GroupTreeWidget;
    widget->setParamsForClientUuid(&m_clientUuid,&m_descriptionForGroup);
    connect(widget,SIGNAL(evt_ok()),this,SLOT(on_addNodes()));
    widget->show();
}

void EditStructWidget::on_btn_addr_send_clicked()
{
    UIHelper::showLoading(this,tr("正在下发"));
    //TODO 这里需要判断选中的节点服务器列表的状态 是否能修改 有待商讨
    UpdateStructTaskAddrRunnable* addr = new UpdateStructTaskAddrRunnable(this);
    addr->setUpdateInfo(selectedAddrUuids,taskUUID,Stru::SendStatus_State::USABLE);
    QThreadPool::globalInstance()->start(addr);
}

void EditStructWidget::on_btn_addr_open_clicked()
{
    if(selectedAddrUuids.isEmpty()) {
        return;
    }
    isSaveFilePos = true;
    UIHelper::showLoading(this,tr("正在查询文件信息"));
    ListStructSendStatusRunnable* status = new ListStructSendStatusRunnable(this);
    status->setNodeUuid(taskUUID,selectedAddrUuids.at(0));
    status->setFilterPage(this->filesPage);
    QThreadPool::globalInstance()->start(status);
}

void EditStructWidget::on_btn_file_open_clicked()
{
    if(selectedFileUuids.isEmpty()) {
        return;
    }
    isSaveAddrPos = true;
    UIHelper::showLoading(this,tr("正在查询节点信息"));
    ListStructSendStatusRunnable* status = new ListStructSendStatusRunnable(this);

    status->setFileName(taskUUID,selectedFileUuids.at(0));

    status->setFilterPage(this->nodesPage);
    QThreadPool::globalInstance()->start(status);
}

void EditStructWidget::on_btn_file_send_clicked()
{
    if(selectedFileUuids.isEmpty()) {
        return;
    }
    UIHelper::showLoading(this,tr("正在下发"));
    UpdateStructTaskFileRunnable* file = new  UpdateStructTaskFileRunnable(this);
    file->setUpdateInfo(selectedFileUuids,taskUUID,Stru::SendStatus_State::USABLE);
    QThreadPool::globalInstance()->start(file);
}

void EditStructWidget::on_btn_file_add_clicked()
{
    FileInfoList* fileDlg = new FileInfoList;
    connect(fileDlg,SIGNAL(evt_selectedFileInfoList(QStringList,QStringList)),this,SLOT(on_addFile(QStringList,QStringList)));
    fileDlg->show();
}

void EditStructWidget::on_btn_save_clicked()
{
    UpdateStructTaskRunnable* updateTask = new UpdateStructTaskRunnable(this);
    QList<CsRStructTask> taskList;
    m_task.setTaskName(ui->l_taskName->text().trimmed());
    if(m_task.getTaskName().isEmpty()) {
        UIHelper::ShowMessageBoxError("任务名称为空");
        return;
    }
    if(ui->cb_strategy->currentText().isEmpty()) {
        UIHelper::ShowMessageBoxError("任务策略为空");
        return;
    }
    m_task.setStrategy((quint16)1/*ui->cb_strategy->currentValue().toInt()*/);
    m_task.setSendTime(ui->dte_send->text());
    m_task.setExecTime(ui->dte_exec->text());
    m_task.setDescription(ui->te_description->toPlainText().trimmed());
    if(m_task.getDescription().isEmpty()) {
        UIHelper::ShowMessageBoxError("任务描术为空");
        return;
    }
    taskList.append(m_task);
    updateTask->setTaskList(taskList);
    QThreadPool::globalInstance()->start(updateTask);
}

void EditStructWidget::on_btn_addrForTask_clicked()
{
    isUnionFiles = false;
    isUnionAddrs = true;
    isSaveAddrPos = false;
    asyncLoadAddr();
}

void EditStructWidget::on_btn_fileForTask_clicked()
{
    isUnionAddrs = false;
    isUnionFiles = true;
    isSaveFilePos = false;
    asyncLoadFile();
}
