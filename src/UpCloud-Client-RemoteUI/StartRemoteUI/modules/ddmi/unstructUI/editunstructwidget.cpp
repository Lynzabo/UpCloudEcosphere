#include "editunstructwidget.h"
#include <QDateTime>
#include "ui_editunstructwidget.h"
#include "modules/common/uihelper.h"
#include "modules/common/grouptreewidget.h"
#include "modules/common/dirnodefilewidget.h"
#include "baseiremote.h"
#include "modules/common/fileinfolist.h"
using namespace RemoteUIEnvironment;
using namespace Environment::Task_Status::Center;
EditUnstructWidget::EditUnstructWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EditUnstructWidget)
{
    ui->setupUi(this);
    initDatas();
    setAttribute(Qt::WA_DeleteOnClose);
    //加载数据
    initWindow();
}

EditUnstructWidget::~EditUnstructWidget()
{
    delete nodesPage;
    delete filesPage;
    delete ui;
}

void EditUnstructWidget::setTaskUUID(const QString &_taskUUID)
{
    this->taskUUID = _taskUUID;
}

void EditUnstructWidget::showEvent(QShowEvent * event)
{
    loadDatas();
}

void EditUnstructWidget::on_itemtaskCallback(const qint32 msgId, const QString &msg)
{
    if(msgId != CallbackStatus::Unstruct::_0)
    {
        UIHelper::hideLoading(this);
        UIHelper::ShowMessageBoxError(msg);
        return;
    }
    UIHelper::hideLoading(this);
    //TODO 节点和关联数据都重新加载 效率低需要修改
    loadDatas();
}

void EditUnstructWidget::on_itemtaskCallbackNode(const qint32 msgId, const QString &msg, const QList<CsRUnstructSendStatus> &statusList, const QStringList &nameList)
{
    if(msgId != CallbackStatus::Unstruct::_0)
    {
        UIHelper::hideLoading(this);
        UIHelper::ShowMessageBoxError(msg);
        return;
    }
    isUnionFiles = true;
    //    DirNodeFileWidget* nodeInfo = new DirNodeFileWidget;
    //    connect(nodeInfo,SIGNAL(evt_send()),this,SLOT(on_nodeFileWidgetSend()));
    //    VCsRUnstructSendAddr addr = addrsList.at(m_selectRowsForAddr.at(0));
    //    //这里要取出节点服务器名字
    //    QStringList nodeName;
    //    nodeName << addr.getDescritpion();
    //    nodeInfo->loadDatas(statusList,nameList,nodeName);
    //    nodeInfo->show();
    //    UIHelper::hideLoading(this);
    //首先切换到关联列表，清空列表内容 设置新行数
    ui->tw_content->setCurrentIndex(1);
    ui->tw_files->table_body->clearContents();
    ui->tw_files->table_body->setRowCount(statusList.size());

    //指定的节点服务器的信息
    VCsRUnstructSendAddr addr = addrsList.at(m_selectRowsForAddr.at(0));
    ui->lab_file_pos->setText(addr.getClientUuid());
    fileNamePos = addr.getClientUuid();
    for(int i = 0;i < statusList.size(); ++i)
    {
        CsRUnstructSendStatus status = statusList.at(i);
        QTableWidgetItem* item1 = new QTableWidgetItem;
        item1->setIcon(filesStateToIcon(status.getState()));
        item1->setText(QString("%1").arg(i));
        ui->tw_files->table_body->setItem(i,FilesTableHeaderElement::FILES_INDEX,item1);

        QTableWidgetItem* item2 = new QTableWidgetItem;
        //        QString fileUUid = status.getSendFileUuid();
        //        QString fileName;fileName.clear();
        //        foreach(const VCsRUnstructSendFiles &file,filesList) {
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

void EditUnstructWidget::on_itemtaskCallbackFile(const qint32 msgId, const QString &msg, const QList<CsRUnstructSendStatus> &statusList, const QStringList &nameList)
{
    if(msgId != CallbackStatus::Unstruct::_0)
    {
        UIHelper::hideLoading(this);
        UIHelper::ShowMessageBoxError(msg);
        return;
    }
    //    DirNodeFileWidget* fileInfo = new DirNodeFileWidget;
    //    connect(fileInfo,SIGNAL(evt_send()),this,SLOT(on_nodeFileWidgetSend()));
    //    VCsRUnstructSendFiles file = filesList.at(m_selectRowsForFiles.at(0));
    //    //这里要取出文件名字
    //    QStringList fileName;
    //    fileName << file.getFileName();
    //    fileInfo->loadDatas(statusList,fileName,nameList);
    //    fileInfo->show();
    //    UIHelper::hideLoading(this);

    //首先切换到关联列表，清空列表内容 设置新行数
    ui->tw_content->setCurrentIndex(0);
    ui->tw_nodes->table_body->clearContents();
    ui->tw_nodes->table_body->setRowCount(statusList.size());
    //指定的文件的信息
    VCsRUnstructSendFiles file = filesList.at(m_selectRowsForFiles.at(0));
    ui->lab_addr_pos->setText(file.getFileName());
    AddrNamePos = file.getFileName();

    for(int i = 0;i < statusList.size(); ++i)
    {
        CsRUnstructSendStatus status = statusList.at(i);
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
        //        foreach(const VCsRUnstructSendAddr &addr,addrsList) {
        //            if(addrUuid == addr.getUuid()) {
        //                groupDesc = addr.getGroupDesc();
        //            }
        //        }
        QTableWidgetItem* item3 = new QTableWidgetItem;
        item3->setText(nameList.at(i));
        ui->tw_nodes->table_body->setItem(i,NodersTableHeaderElement::NODER_NODER_NAME,item3);

        //TODO 以后需要获取该节点服务器所属群组 这里有重要的BUG
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

void EditUnstructWidget::on_itemtaskCallback(const qint32 msgId, const QString &msg, const CsRUnstructTask &task)
{
    UIHelper::showLoading(this,tr("获取任务数据成功，准备展示 ..."));
    //如果出错,提示出错信息
    if(msgId != CallbackStatus::Unstruct::_0)
    {
        UIHelper::hideLoading(this);
        UIHelper::ShowMessageBoxError(msg);
        return;
    }
    else
    {
        this->task = task;
        ui->l_taskName->setText(this->task.getTaskName().trimmed());
        ui->lab_insertor_2->setText(this->task.getInsertor().trimmed());
        ui->lab_time->setText(this->task.getInsertTime().trimmed());
        ui->t_description->setText(this->task.getDescription().trimmed());
        ui->lab_num->setText(QString::number(this->task.getTaskNum()));
        quint8 state = task.getState();
        ui->lab_state->setText(taskStateToText(state));
        //按键可用  下发 删除 添加
        if(state == Unstru::Task_State::USABLE || state == Unstru::Task_State::DOWNERROR
                || state == Unstru::Task_State::SENDERROR || state == Unstru::Task_State::TASKERROR) {
            ui->btn_addr_add->setEnabled(true);
            ui->btn_addr_del->setEnabled(true);
            ui->btn_addr_send->setEnabled(true);
        }
        else {
            ui->btn_addr_add->setEnabled(false);
            ui->btn_addr_del->setEnabled(false);
            ui->btn_addr_send->setEnabled(false);
        }
        ui->lab_icon->setPixmap(taskStateIcon(this->task.getState()));
        QDateTime time = QDateTime::fromString(this->task.getSendTime(),"yyyy-MM-dd HH:mm:ss");
        ui->dateTimeEdit->setDateTime(time);
        //TODO 暂时写死
        ui->cb_strategy->setCurrentIndex(0);
        UIHelper::hideLoading(this);
        //加载下发地址
        asyncLoadAddrs();
    }
}

void EditUnstructWidget::on_itemtaskCallback(const qint32 msgId, const QString &msg, const QList<VCsRUnstructSendAddr> &addrList)
{
    if(msgId != CallbackStatus::Unstruct::_0)
    {
        UIHelper::hideLoading(this);
        UIHelper::ShowMessageBoxError(msg);
        return;
    }
    else
    {
        ui->tw_nodes->setPage(nodesPage);
        this->addrsList = addrList;
        ui->tw_nodes->table_body->setRowCount(addrList.size());
        if(isSaveAddrPos) {
            ui->lab_addr_pos->setText(AddrNamePos);
        }
        else {

            ui->lab_addr_pos->setText(tr("allFiles"));
        }
        for(int i = 0;i < this->addrsList.size(); ++i)
        {
            VCsRUnstructSendAddr addr = this->addrsList.at(i);
            QTableWidgetItem* item1 = new QTableWidgetItem;
            //TODO 执行策略 需要商讨 获取节点服务器状态
            item1->setIcon(noderStateToIcon(addr.getState()));
            item1->setText(QString("%1").arg(i));
            ui->tw_nodes->table_body->setItem(i,NodersTableHeaderElement::NODER_INDEX,item1);

            QTableWidgetItem* item2 = new QTableWidgetItem;
            item2->setText(addr.getClientUuid());
            ui->tw_nodes->table_body->setItem(i,NodersTableHeaderElement::NODER_CLIENT_UUID,item2);

            QTableWidgetItem* item3 = new QTableWidgetItem;
            item3->setText(addr.getDescritpion());
            ui->tw_nodes->table_body->setItem(i,NodersTableHeaderElement::NODER_NODER_NAME,item3);

            //TODO 以后需要获取该节点服务器所属群组
            QTableWidgetItem* item4 = new QTableWidgetItem;
            item4->setText(addr.getGroupDesc());
            ui->tw_nodes->table_body->setItem(i,NodersTableHeaderElement::NODER_GROUP,item4);

            QTableWidgetItem* item5 = new QTableWidgetItem;
            //TODO 执行策略 需要商讨 获取节点服务器状态
            item5->setText(noderStateToText(addr.getState()));
            ui->tw_nodes->table_body->setItem(i,NodersTableHeaderElement::NODER_STATE,item5);

            //TODO 界面中的错误描述 需要吗？
            QTableWidgetItem* item6 = new QTableWidgetItem;
            item6->setText(tr(""));
            ui->tw_nodes->table_body->setItem(i,NodersTableHeaderElement::NODER_ERRINFO,item6);
        }

        UIHelper::hideLoading(this);
        //加载下发文件
        asyncLoadFiles();
    }
}
void EditUnstructWidget::on_itemtaskCallback(const qint32 msgId, const QString &msg, const QList<VCsRUnstructSendFiles> &filesList)
{
    UIHelper::showLoading(this,tr("获取文件数据成功，读取显示 ..."));
    if(msgId != CallbackStatus::Unstruct::_0)
    {
        UIHelper::hideLoading(this);
        UIHelper::ShowMessageBoxError(msg);
        return;
    }
    else
    {
        ui->tw_files->setPage(filesPage);
        this->filesList = filesList;
        ui->tw_files->table_body->setRowCount(filesList.size());
        if(isSaveFilePos) {
            ui->lab_file_pos->setText(fileNamePos);
        }
        else {
            ui->lab_file_pos->setText(tr("allNodes"));
        }
        for(int i = 0;i < filesList.size(); ++i)
        {
            VCsRUnstructSendFiles sendFile = this->filesList.at(i);
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
            item5->setText("");
            ui->tw_files->table_body->setItem(i,FilesTableHeaderElement::FILES_ERRINFO,item5);
        }
        UIHelper::hideLoading(this);
    }
}


void EditUnstructWidget::initWindow()
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
    ui->tw_nodes->table_body->setHeaderColumnLabel(EditUnstructWidget::NODER_INDEX,tr("序号","table_body"));
    ui->tw_nodes->table_body->setHeaderColumnLabel(EditUnstructWidget::NODER_CLIENT_UUID,tr("服务器固定码","table_body"));
    ui->tw_nodes->table_body->setHeaderColumnLabel(EditUnstructWidget::NODER_NODER_NAME,tr("节点服务器名","table_body"));
    ui->tw_nodes->table_body->setHeaderColumnLabel(EditUnstructWidget::NODER_GROUP,tr("groupNodes","table_body"));
    ui->tw_nodes->table_body->setHeaderColumnLabel(EditUnstructWidget::NODER_STATE,tr("nodeState","table_body"));
    ui->tw_nodes->table_body->setHeaderColumnLabel(EditUnstructWidget::NODER_ERRINFO,tr("错误描述 ","table_body"));
    //设置表头每列宽比
    ui->tw_nodes->table_body->setHeaderColumnWidth(EditUnstructWidget::NODER_INDEX,  50);
    ui->tw_nodes->table_body->setHeaderColumnWidth(EditUnstructWidget::NODER_CLIENT_UUID,0.2);
    ui->tw_nodes->table_body->setHeaderColumnWidth(EditUnstructWidget::NODER_NODER_NAME,0.2);
    ui->tw_nodes->table_body->setHeaderColumnWidth(EditUnstructWidget::NODER_GROUP,0.2);
    ui->tw_nodes->table_body->setHeaderColumnWidth(EditUnstructWidget::NODER_STATE,100);
    ui->tw_nodes->table_body->setHeaderColumnWidth(EditUnstructWidget::NODER_ERRINFO,0.4);
    //设置表头每列对齐方式
    ui->tw_nodes->table_body->setHeaderColumnAlignment(EditUnstructWidget::NODER_INDEX,Qt::AlignRight | Qt::AlignCenter);
    //设置表头可排序列,默认为都不可排序
    //参数2的值是分页getOrderFieldName的值,使用该值做排序,因此命名名成数据库字段名,大小写保持与SQL语句一致
    ui->tw_nodes->table_body->setHeaderColumnCanSort(EditUnstructWidget::NODER_CLIENT_UUID,QString("CLIENT_UUID"));
    ui->tw_nodes->table_body->setHeaderColumnCanSort(EditUnstructWidget::NODER_NODER_NAME,QString("DESCRIPTION"));
    //    ui->tw_nodes->table_body->setHeaderColumnCanSort(EditUnstructWidget::NODER_STATE,QString("STATE"));
    //关联表格相关信号      一个线程,默认的是用direct，检查一下该用&
    //广播选中表格体1行
    connect(ui->tw_nodes,&PageTableWidget::evt_tableBodySelectedRow,this,&EditUnstructWidget::on_tableBodyNodeSelectedRow);
    //广播选中多行
    connect(ui->tw_nodes,&PageTableWidget::evt_tableBodySelectedRows,this,&EditUnstructWidget::on_tableBodyNodeSelectedRows);
    //广播双击1行
    connect(ui->tw_nodes,&PageTableWidget::evt_tableBodyDoubleSelected,this,&EditUnstructWidget::on_tableBodyNodeDoubleSelected);
    //广播选中空白区域
    connect(ui->tw_nodes,&PageTableWidget::evt_tableBodySelectedNull,this,&EditUnstructWidget::on_tableBodyNodeSelectedNull);
    //广播表格
    connect(ui->tw_nodes,&PageTableWidget::evt_pageTableAccept,this,&EditUnstructWidget::on_pageTableNodeAccept);




    ////文件列表
    //设置分页导航条可用
    ui->tw_files->setPageNavatorUsable(true);
    //设置表头
    //设置表头列数量
    ui->tw_files->table_body->horizontalHeader()->setVisible(true);
    ui->tw_files->table_body->setColumnCount(5);
    //设置表头每列标签
    ui->tw_files->table_body->setHeaderColumnLabel(EditUnstructWidget::FILES_INDEX,tr("序号","table_body"));
    ui->tw_files->table_body->setHeaderColumnLabel(EditUnstructWidget::FILES_FILENAME,tr("fileName","table_body"));
    ui->tw_files->table_body->setHeaderColumnLabel(EditUnstructWidget::FILES_SENDTIME,tr("下发时间","table_body"));
    ui->tw_files->table_body->setHeaderColumnLabel(EditUnstructWidget::FILES_STATE,tr("fileState","table_body"));
    ui->tw_files->table_body->setHeaderColumnLabel(EditUnstructWidget::FILES_ERRINFO,tr("错误描述","table_body"));
    //设置表头每列宽比
    ui->tw_files->table_body->setHeaderColumnWidth(EditUnstructWidget::FILES_INDEX,  50);
    ui->tw_files->table_body->setHeaderColumnWidth(EditUnstructWidget::FILES_FILENAME,0.3);
    ui->tw_files->table_body->setHeaderColumnWidth(EditUnstructWidget::FILES_SENDTIME,0.3);
    ui->tw_files->table_body->setHeaderColumnWidth(EditUnstructWidget::FILES_STATE,100);
    ui->tw_files->table_body->setHeaderColumnWidth(EditUnstructWidget::FILES_ERRINFO,0.4);
    //设置表头每列对齐方式
    ui->tw_files->table_body->setHeaderColumnAlignment(EditUnstructWidget::FILES_INDEX,Qt::AlignRight | Qt::AlignCenter);
    //设置表头可排序列,默认为都不可排序
    //参数2的值是分页getOrderFieldName的值,使用该值做排序,因此命名名成数据库字段名,大小写保持与SQL语句一致
    ui->tw_files->table_body->setHeaderColumnCanSort(EditUnstructWidget::FILES_FILENAME,QString("FILE_NAME"));
    //    ui->tw_files->table_body->setHeaderColumnCanSort(EditUnstructWidget::FILES_SENDTIME,QString("SEND_TIME"));
    //    ui->tw_files->table_body->setHeaderColumnCanSort(EditUnstructWidget::FILES_STATE,QString("STATE"));
    //关联表格相关信号      一个线程,默认的是用direct，检查一下该用&
    //广播选中表格体1行
    connect(ui->tw_files,&PageTableWidget::evt_tableBodySelectedRow,this,&EditUnstructWidget::on_tableBodyFileSelectedRow);
    //广播选中多行
    connect(ui->tw_files,&PageTableWidget::evt_tableBodySelectedRows,this,&EditUnstructWidget::on_tableBodyFileSelectedRows);
    //广播双击1行
    connect(ui->tw_files,&PageTableWidget::evt_tableBodyDoubleSelected,this,&EditUnstructWidget::on_tableBodyFileDoubleSelected);
    //广播选中空白区域
    connect(ui->tw_files,&PageTableWidget::evt_tableBodySelectedNull,this,&EditUnstructWidget::on_tableBodyFileSelectedNull);
    //广播表格
    connect(ui->tw_files,&PageTableWidget::evt_pageTableAccept,this,&EditUnstructWidget::on_pageTableFileAccept);
    //下拉框菜单加载
    loadComboBox();
}

void EditUnstructWidget::initDatas()
{


    //参数初始化
    taskUUID.clear();
    addrsList.clear();
    filesList.clear();
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

void EditUnstructWidget::loadDatas()
{
    UIHelper::showLoading(this,tr("获取数据..."));
    //加载任务信息
    ItemUnstructTaskRunnable *task = new ItemUnstructTaskRunnable(this);
    task->setTaskUUID(taskUUID);
    QThreadPool::globalInstance()->start(task);
    isUnionFiles = true;
    isUnionAddrs = true;
    isSaveAddrPos = false;
    fileNamePos.clear();
    isSaveFilePos = false;
    AddrNamePos.clear();
}

QPixmap EditUnstructWidget::taskStateIcon(const quint8 state)
{
    QSize picSize(15,15);
    QPixmap filterPixmap;
    //TODO  状态不完整,待以后添加完不可见,暂停增加完整
    switch (state) {
    case Unstru::Task_State::DISCARD:
        filterPixmap = QPixmap(":/ddmi/unstruct/imgs/STATE_DISCARD");
        break;
    case Unstru::Task_State::PRESEND:
        filterPixmap = QPixmap(":/ddmi/unstruct/imgs/STATE_PRESEND");
        break;
    case Unstru::Task_State::SENDING:
        filterPixmap = QPixmap(":/ddmi/unstruct/imgs/STATE_SENDING");
        break;
    case Unstru::Task_State::SENDERROR:
        filterPixmap = QPixmap(":/ddmi/unstruct/imgs/STATE_SENDERROR");
        break;
    case Unstru::Task_State::SENDSUCCESS:
        filterPixmap = QPixmap(":/ddmi/unstruct/imgs/STATE_SENDSUCCESS");
        break;
    case Unstru::Task_State::DOWNERROR:
        filterPixmap = QPixmap(":/ddmi/unstruct/imgs/STATE_DOWNERROR");
        break;
    case Unstru::Task_State::DOWNSUCCESS:
        filterPixmap = QPixmap(":/ddmi/unstruct/imgs/STATE_DOWNSUCCESS");
        break;
    case Unstru::Task_State::TASKERROR:
        filterPixmap = QPixmap(":/ddmi/unstruct/imgs/STATE_TASKERROR");
        break;
    case Unstru::Task_State::TASKSUCCESS:
        filterPixmap = QPixmap(":/ddmi/unstruct/imgs/STATE_TASKSUCCESS");
        break;
    case Unstru::Task_State::PAUSE:
        filterPixmap = QPixmap(":/ddmi/unstruct/imgs/STATE_PAUSE");
        break;
    default:
        break;
    }
    QPixmap scaledPixmap = filterPixmap.scaled(picSize);
    return scaledPixmap;

}

QString EditUnstructWidget::taskStateToText(const quint8 state)
{
    //TODO  已修改完整
    QString text;
    switch (state) {
    case Unstru::Task_State::DISCARD:
        text = tr("废弃");
        break;
    case Unstru::Task_State::USABLE:
        text = tr("可用");
        break;
    case Unstru::Task_State::PRESEND:
        text = tr("准备下发");
        break;
    case Unstru::Task_State::SENDING:
        text = tr("正在下发");
        break;
    case Unstru::Task_State::ADDRISNULL:
        text = tr("目标地址为空");
        break;
    case Unstru::Task_State::SENDERROR:
        text = tr("下发错误");
        break;
    case Unstru::Task_State::SENDSUCCESS:
        text = tr("下发成功");
        break;
    case Unstru::Task_State::DOWNERROR:
        text = tr("下载错误");
        break;
    case Unstru::Task_State::DOWNSUCCESS:
        text = tr("下载成功");
        break;
    case Unstru::Task_State::TASKERROR:
        text = tr("任务处理失败");
        break;
    case Unstru::Task_State::TASKSUCCESS:
        text = tr("任务处理成功");
        break;
    case Unstru::Task_State::PAUSE:
        text = tr("pause");
        break;
    case Unstru::Task_State::CACHEING:
        text = tr("cache");
        break;
    default:
        break;
    }
    return text;
}

QIcon EditUnstructWidget::noderStateToIcon(const quint8 state)
{
    //TODO  状态不完整,待以后添加完不可见,暂停增加完整
    QIcon icon;
    switch (state) {
    case Unstru::SendStatus_State::DISCARD:
        icon = QIcon(":/ddmi/unstruct/imgs/STATE_DISCARD");
        break;
    case Unstru::SendStatus_State::PRESEND:
        icon = QIcon(":/ddmi/unstruct/imgs/STATE_PRESEND");
        break;
    case Unstru::SendStatus_State::SENDING:
        icon = QIcon(":/ddmi/unstruct/imgs/STATE_SENDING");
        break;
    case Unstru::SendStatus_State::SENDERROR:
        icon = QIcon(":/ddmi/unstruct/imgs/STATE_SENDERROR");
        break;
    case Unstru::SendStatus_State::SENDSUCCESS:
        icon = QIcon(":/ddmi/unstruct/imgs/STATE_SENDSUCCESS");
        break;
    case Unstru::SendStatus_State::DOWNERROR:
        icon = QIcon(":/ddmi/unstruct/imgs/STATE_DOWNERROR");
        break;
    case Unstru::SendStatus_State::DOWNSUCCESS:
        icon = QIcon(":/ddmi/unstruct/imgs/STATE_DOWNSUCCESS");
        break;
    default:
        break;
    }
    return icon;
}

QString EditUnstructWidget::noderStateToText(const quint8 state)
{
    //TODO  状态不完整,待以后添加完不可见,暂停增加完整
    QString text;
    switch (state) {
    case Unstru::SendStatus_State::DISCARD:
        text = tr("废弃");
        break;
    case Unstru::SendStatus_State::USABLE:
        text = tr("可用");
        break;
    case Unstru::SendStatus_State::PRESEND:
        text = tr("准备下发");
        break;
    case Unstru::SendStatus_State::SENDING:
        text = tr("正在下发");
        break;
    case Unstru::SendStatus_State::SENDERROR:
        text = tr("下发错误");
        break;
    case Unstru::SendStatus_State::SENDSUCCESS:
        text = tr("下发成功");
        break;
    case Unstru::SendStatus_State::DOWNERROR:
        text = tr("下载错误");
        break;
    case Unstru::SendStatus_State::DOWNSUCCESS:
        text = tr("下载成功");
        break;
    default:
        break;
    }
    return text;
}

QIcon EditUnstructWidget::filesStateToIcon(const quint8 state)
{
    //TODO  状态不完整,待以后添加完不可见,暂停增加完整
    QIcon icon;
    switch (state) {
    case Unstru::SendStatus_State::DISCARD:
        icon = QIcon(":/ddmi/unstruct/imgs/STATE_DISCARD");
        break;
    case Unstru::SendStatus_State::USABLE:
        icon = QIcon(":/ddmi/unstruct/imgs/STATE_USABLE");
        break;
    case Unstru::SendStatus_State::PRESEND:
        icon = QIcon(":/ddmi/unstruct/imgs/STATE_PRESEND");
        break;
    case Unstru::SendStatus_State::SENDING:
        icon = QIcon(":/ddmi/unstruct/imgs/STATE_SENDING");
        break;
    case Unstru::SendStatus_State::SENDERROR:
        icon = QIcon(":/ddmi/unstruct/imgs/STATE_SENDERROR");
        break;
    case Unstru::SendStatus_State::SENDSUCCESS:
        icon = QIcon(":/ddmi/unstruct/imgs/STATE_SENDSUCCESS");
        break;
    case Unstru::SendStatus_State::DOWNERROR:
        icon = QIcon(":/ddmi/unstruct/imgs/STATE_DOWNERROR");
        break;
    case Unstru::SendStatus_State::DOWNSUCCESS:
        icon = QIcon(":/ddmi/unstruct/imgs/STATE_DOWNSUCCESS");
        break;
    default:
        break;
    }
    return icon;
}

QString EditUnstructWidget::filesStateToText(const quint8 state)
{
    //TODO  状态不完整,待以后添加完不可见,暂停增加完整
    QString text;
    switch (state) {
    case Unstru::SendStatus_State::DISCARD:
        text = tr("废弃");
        break;
    case Unstru::SendStatus_State::USABLE:
        text = tr("可用");
        break;
    case Unstru::SendStatus_State::PRESEND:
        text = tr("准备下发");
        break;
    case Unstru::SendStatus_State::SENDING:
        text = tr("正在下发");
        break;
    case Unstru::SendStatus_State::SENDERROR:
        text = tr("下发错误");
        break;
    case Unstru::SendStatus_State::SENDSUCCESS:
        text = tr("下发成功");
        break;
    case Unstru::SendStatus_State::DOWNERROR:
        text = tr("下载错误");
        break;
    case Unstru::SendStatus_State::DOWNSUCCESS:
        text = tr("下载成功");
        break;
    default:
        break;
    }
    return text;
}

void EditUnstructWidget::loadComboBox()
{
    ui->cb_strategy->clear();
    QStringList textList;
    textList << tr("默认策略");

    QStringList valueList;
    valueList << tr("1");

    ui->cb_strategy->setShowInfo(textList,valueList);
}

void EditUnstructWidget::asyncLoadAddrs()
{
    if(!isUnionAddrs)
        return;
    UIHelper::showLoading(this,tr("获取任务节点服务数据..."));
    //加载节点服务器列表
    ListUnstructAddrRunnable* listAddr = new ListUnstructAddrRunnable(this);
    //设置查询条件
    listAddr->setTaskUUID(this->task.getUuid());
    //设置分页信息
    listAddr->setFilterPage(nodesPage);
    QThreadPool::globalInstance()->start(listAddr);
}

void EditUnstructWidget::asyncLoadFiles()
{
    if(!isUnionFiles)
        return;
    UIHelper::showLoading(this,tr("获取文件数据..."));
    ListUnstructFileRunnable* listFile = new ListUnstructFileRunnable(this);
    listFile->setTaskUUID(this->task.getUuid());
    listFile->setFilterPage(this->filesPage);
    QThreadPool::globalInstance()->start(listFile);
}

void EditUnstructWidget::on_btn_save_clicked()
{
    UIHelper::showLoading(this,tr("正在修改任务"));
    UpdateUnstructTaskRunnable* updateTask = new UpdateUnstructTaskRunnable(this);
    QList<CsRUnstructTask> taskList;
    task.setTaskName(ui->l_taskName->text().trimmed());
    if(task.getTaskName().isEmpty()) {
        UIHelper::ShowMessageBoxError("任务名称为空");
        return;
    }
    if(ui->cb_strategy->currentText().isEmpty()) {
        UIHelper::ShowMessageBoxError("任务策略为空");
        return;
    }
    task.setStrategy((quint16)1/*ui->cb_strategy->currentValue().toInt()*/);
    task.setSendTime(ui->dateTimeEdit->text());
    if(task.getDescription().isEmpty()) {
        UIHelper::ShowMessageBoxError("任务描术为空");
        return;
    }
    task.setDescription(ui->t_description->toPlainText().trimmed());
    taskList.append(task);
    updateTask->setTaskList(taskList);
    QThreadPool::globalInstance()->start(updateTask);
}

void EditUnstructWidget::on_tableBodyNodeSelectedRow(int selectedRow)
{
    //设置必须多选按钮不可用
    selectedAddrUuids.clear();
    selectedAddrUuids.append(addrsList.at(selectedRow).getClientUuid());
    m_selectRowsForAddr.clear();
    m_selectRowsForAddr.append(selectedRow);
}

void EditUnstructWidget::on_tableBodyNodeSelectedRows(QList<int> selectedRows)
{
    //设置必须单选按钮不可用
    selectedAddrUuids.clear();
    for(int i: selectedRows) {
        QString uuid = addrsList.at(i).getClientUuid();
        selectedAddrUuids.append(uuid);
    }
    m_selectRowsForAddr.clear();
    m_selectRowsForAddr.append(selectedRows);
}

void EditUnstructWidget::on_tableBodyNodeDoubleSelected(int selectedRow)
{
    //双击事件
    selectedAddrUuids.clear();
    m_selectRowsForAddr.clear();

    isSaveFilePos = true;

    QString clientUuid = addrsList.at(selectedRow).getClientUuid();
    selectedAddrUuids.append(clientUuid);
    m_selectRowsForAddr.append(selectedRow);
    UIHelper::showLoading(this,tr("正在加载节点服务器的详细信息"));
    ListUnstructSendStatusRunnable* status = new ListUnstructSendStatusRunnable(this);
    //设置查询参数
    status->setNodeUuid(taskUUID,clientUuid);
    //设置分页 这是要设置文件的分页
    status->setFilterPage(this->filesPage);
    QThreadPool::globalInstance()->start(status);

}

void EditUnstructWidget::on_tableBodyNodeSelectedNull()
{
    selectedAddrUuids.clear();
}

void EditUnstructWidget::on_pageTableNodeAccept(const Page *page)
{
    *nodesPage = *page;
    isUnionAddrs = true;
    isUnionFiles = false;
    asyncLoadAddrs();
}

void EditUnstructWidget::on_tableBodyFileSelectedRow(int selectedRow)
{
    //设置必须多选按钮不可用
    selectedFileUuids.clear();
    selectedFileUuids.append(filesList.at(selectedRow).getUuid());
    m_selectRowsForFiles.clear();
    m_selectRowsForFiles.append(selectedRow);
}

void EditUnstructWidget::on_tableBodyFileSelectedRows(QList<int> selectedRows)
{
    //设置必须单选按钮不可用
    selectedFileUuids.clear();
    for(int i: selectedRows) {
        QString uuid = filesList.at(i).getUuid();
        selectedFileUuids.append(uuid);
    }
    m_selectRowsForFiles.clear();
    m_selectRowsForFiles.append(selectedRows);
}

void EditUnstructWidget::on_tableBodyFileDoubleSelected(int selectedRow)
{
    //双击事件
    selectedFileUuids.clear();
    selectedFileUuids.append(filesList.at(selectedRow).getUuid());
    m_selectRowsForFiles.clear();
    m_selectRowsForFiles.append(selectedRow);
    isSaveAddrPos = true;
    UIHelper::showLoading(this,tr("select all nodes"));
    ListUnstructSendStatusRunnable* status = new ListUnstructSendStatusRunnable(this);
    status->setFileName(taskUUID,selectedFileUuids.at(0));
    status->setFilterPage(this->nodesPage);
    QThreadPool::globalInstance()->start(status);
}

void EditUnstructWidget::on_tableBodyFileSelectedNull()
{
    selectedFileUuids.clear();
}

void EditUnstructWidget::on_pageTableFileAccept(const Page *page)
{
    *(this->filesPage) = *page;
    isUnionFiles = true;
    isUnionAddrs = false;
    asyncLoadFiles();
}

void EditUnstructWidget::on_addNodes()
{
    AddUnstructTaskAddrRunnable* addr = new AddUnstructTaskAddrRunnable(this);
    addr->setAddCondition(m_clientUuid,taskUUID,m_descriptionForGroup);
    QThreadPool::globalInstance()->start(addr);
}

void EditUnstructWidget::on_addFiles(const QStringList &filePathList,const QStringList &saveAbst)
{
    UIHelper::showLoading(this,tr("正在添加文件"));
    AddUnstructTaskFileRunnable* file = new AddUnstructTaskFileRunnable(this);
    QList<CsRUnstructSendFiles> fileList;
    for(int i = 0;i < filePathList.size(); ++i) {
        CsRUnstructSendFiles sendFile;
        QString pathStr = filePathList.at(i);
        int index = pathStr.lastIndexOf("/");
        QString fileName = pathStr.right(pathStr.size() - index -1);
        sendFile.setFileName(fileName);
        sendFile.setSaveAbst(saveAbst.at(i));
        fileList.append(sendFile);
    }
    file->setAddCondition(taskUUID,fileList,addrsList);
    QThreadPool::globalInstance()->start(file);
}

void EditUnstructWidget::on_btn_addr_del_clicked()
{
    if(selectedAddrUuids.isEmpty()) {
        return;
    }
    int ok = UIHelper::ShowMessageBoxQuesion(tr("你确定要删除记录吗?"));
    if(!ok) {
        return;
    }
    DelUnstructTaskAddrRunnable* addr = new DelUnstructTaskAddrRunnable(this);
    JsonArray params;
    foreach(const QString &uuid,selectedAddrUuids) {
        params.push_back(uuid);
    }
    addr->setAddrUuids(params,task.getUuid());
    QThreadPool::globalInstance()->start(addr);
}

void EditUnstructWidget::on_btn_file_del_clicked()
{
    if(selectedFileUuids.isEmpty()) {
        return;
    }
    int ok = UIHelper::ShowMessageBoxQuesion(tr("你确定要删除记录吗?"));
    if(!ok) {
        return;
    }
    UIHelper::showLoading(this,tr("正在删除"));
    DelUnstructTaskFileRunnable* file = new DelUnstructTaskFileRunnable(this);
    JsonArray params;
    foreach(const QString &uuid,selectedFileUuids) {
        params.push_back(uuid);
    }
    file->setFileUuids(task.getUuid(),params);
    QThreadPool::globalInstance()->start(file);
}

void EditUnstructWidget::on_btn_back_clicked()
{
    UIHelper::OpenInSelf(this,new DirUnstructWidget);
}

void EditUnstructWidget::on_btn_addr_add_clicked()
{
    GroupTreeWidget* widget = new GroupTreeWidget;
    widget->setParamsForClientUuid(&m_clientUuid,&m_descriptionForGroup);
    connect(widget,SIGNAL(evt_ok()),this,SLOT(on_addNodes()));
    widget->show();
}

void EditUnstructWidget::on_cb_addr_state_currentIndexChanged(int index)
{

}

void EditUnstructWidget::on_btn_addr_send_clicked()
{
    //修改单条或多条记录状态 并修改任务状态为可用
    //    foreach(const int index,m_selectRowsForAddr) {
    //        quint8 state = addrsList.at(index).getState();
    //        if(state != Environment::Task_Status::Center::Unstru::SendStatus_State::USABLE) {
    //            return;
    //        }
    //    }
    UpdateUnstructTaskAddrRunnable* addr = new UpdateUnstructTaskAddrRunnable(this);
    addr->setUpdateState(selectedAddrUuids,taskUUID,
                         Environment::Task_Status::Center::Unstru::SendStatus_State::USABLE);
    QThreadPool::globalInstance()->start(addr);

}

void EditUnstructWidget::on_btn_addr_open_clicked()
{
    if(selectedAddrUuids.isEmpty()) {
        return;
    }
    isSaveFilePos = true;
    UIHelper::showLoading(this,tr("正在加载节点服务器的详细信息"));
    ListUnstructSendStatusRunnable* status = new ListUnstructSendStatusRunnable(this);
    status->setNodeUuid(taskUUID,selectedAddrUuids.at(0));
    status->setFilterPage(this->filesPage);
    QThreadPool::globalInstance()->start(status);
}

void EditUnstructWidget::on_btn_file_send_clicked()
{
    UIHelper::showLoading(this,tr("立即下发正在更新数据"));
    UpdateUnstructTaskSendFilesRunnable* file = new UpdateUnstructTaskSendFilesRunnable(this);
    file->setUpdateState(selectedFileUuids,taskUUID,Unstru::SendStatus_State::USABLE);
    QThreadPool::globalInstance()->start(file);
}

void EditUnstructWidget::on_btn_file_add_clicked()
{
    FileInfoList* fileDlg = new FileInfoList;
    connect(fileDlg,SIGNAL(evt_selectedFileInfoList(QStringList,QStringList)),this,SLOT(on_addFiles(QStringList,QStringList)));
    fileDlg->show();
}

void EditUnstructWidget::on_btn_file_open_clicked()
{
    if(selectedFileUuids.isEmpty()) {
        return;
    }
    isSaveAddrPos = true;
    UIHelper::showLoading(this,tr("dir files about nodes"));
    ListUnstructSendStatusRunnable* status = new ListUnstructSendStatusRunnable(this);
    status->setFileName(taskUUID,selectedFileUuids.at(0));
    status->setFilterPage(this->nodesPage);
    QThreadPool::globalInstance()->start(status);
}

void EditUnstructWidget::on_nodeFileWidgetSend()
{
    loadDatas();
}

void EditUnstructWidget::on_btn_addrForTask_clicked()
{
    isUnionAddrs = true;
    isUnionFiles = false;
    isSaveAddrPos = false;
    asyncLoadAddrs();
}

void EditUnstructWidget::on_btn_filesForTask_clicked()
{
    isUnionFiles = true;
    isUnionAddrs = false;
    isSaveFilePos = false;
    asyncLoadFiles();
}
