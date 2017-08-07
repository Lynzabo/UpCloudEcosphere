#include "editschedulewidget.h"
#include "ui_editschedulewidget.h"
#include "modules/common/loading.h"
#include "modules/common/uihelper.h"
#include "modules/common/grouptreewidget.h"
#include "dirschedulewidget.h"
#include "../../../../FrontBusinessIRemoteUI/DDMIRemoteUI/ScheduleOperaIRemoteUI/scheduleoperairemoteui.h"
using namespace RemoteUIEnvironment;
using namespace Environment::Task_Status::Center;
EditScheduleWidget::EditScheduleWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EditScheduleWidget)
{
    ui->setupUi(this);
    //禁用下发按键 删除按键
    ui->btn_nodes_del->setEnabled(false);
    ui->btn_nodes_send->setEnabled(false);
    ui->btn_nodes_add->setEnabled(false);
    ui->btn_nodes_exec->setEnabled(false);
    initWindow();
}

EditScheduleWidget::~EditScheduleWidget()
{
    delete ui;
}

void EditScheduleWidget::on_nodeSelectedRow(int selectedRow)
{
    selectedNodesUuid.clear();
    selectedNodesUuid.append(curNodesList.at(selectedRow).getClientUuid());
}

void EditScheduleWidget::on_nodeSelectedRows(QList<int> selectedRows)
{
    selectedNodesUuid.clear();
    foreach(const int index,selectedRows)
    {
        selectedNodesUuid.append(curNodesList.at(index).getClientUuid());
    }
}

void EditScheduleWidget::on_nodeDoubleSelected(int selectedRow)
{
    selectedNodesUuid.clear();
    selectedNodesUuid.append(curNodesList.at(selectedRow).getClientUuid());
}

void EditScheduleWidget::on_filesSelectedRow(int selectedRow)
{
    selectedFilesUuid.clear();
    selectedFilesUuid.append(curVFilesList.at(selectedRow).getUuid());
}

void EditScheduleWidget::on_filesSelectedRows(QList<int> selectedRows)
{
    selectedFilesUuid.clear();
    foreach(const int index,selectedRows)
    {
        selectedFilesUuid.append(curVFilesList.at(index).getUuid());
    }
}

void EditScheduleWidget::on_filesDoubleSelected(int selectedRow)
{
    selectedFilesUuid.clear();
    selectedFilesUuid.append(curVFilesList.at(selectedRow).getUuid());
}

void EditScheduleWidget::on_itemtaskCallback(const qint32 cbMsgId, const QString &msg)
{
    if(cbMsgId != CallbackStatus::Schedule::_0)
    {
        UIHelper::hideLoading(this);
        UIHelper::ShowMessageBoxError(msg);
        return;
    }
    loadDatas();
}

void EditScheduleWidget::on_itemtaskCallback(const qint32 cbMsgId, const QString &msg, const CsRScheduleTask &task)
{
    if(cbMsgId != CallbackStatus::Schedule::_0)
    {
        UIHelper::hideLoading(this);
        UIHelper::ShowMessageBoxError(msg);
        return;
    }
    m_task = task;
    if(taskUuid != m_task.getUuid())
    {
        taskUuid = m_task.getUuid();
    }
    ui->l_taskName->setText(m_task.getTaskName());
    //TODO 策略要重写
    ui->cb_strategy->setCurrentIndex(0);
    QDateTime dateTime = QDateTime::fromString(m_task.getSendTime(),"yyyy-MM-dd HH:mm:ss");
    ui->dte_send->setDateTime(dateTime);
    ui->te_description->setText(m_task.getDescription());
    ui->lab_icon->setPixmap(taskStateToIcon(m_task.getState()));
    quint8 state = task.getState();
    ui->lab_state->setText(taskStateToText(state));
    //按键可用  下发 删除 添加
    if(state == Sche::Task_State::USABLE || state == Sche::Task_State::DOWNERROR
            || state == Sche::Task_State::SENDERROR || state == Sche::Task_State::TASKERROR
            || state == Sche::Task_State::EXECERROR) {
        ui->btn_nodes_del->setEnabled(true);
        ui->btn_nodes_send->setEnabled(true);
        ui->btn_nodes_add->setEnabled(true);
        ui->btn_nodes_exec->setEnabled(true);
    }
    else {
        ui->btn_nodes_del->setEnabled(false);
        ui->btn_nodes_send->setEnabled(false);
        ui->btn_nodes_add->setEnabled(false);
        ui->btn_nodes_exec->setEnabled(false);
    }
    ui->lab_num->setText(QString::number(m_task.getTaskNum()));
    ui->lab_insertor->setText(m_task.getInsertor());
    ui->lab_insertTime->setText(m_task.getInsertTime());

    UIHelper::showLoading(this,tr("获取地址数据"));
    ListScheduleAddrRunnable* addr = new ListScheduleAddrRunnable(this);
    addr->setTaskUuid(taskUuid);
    QThreadPool::globalInstance()->start(addr);
}

void EditScheduleWidget::on_itemtaskCallback(const qint32 cbMsgId, const QString &msg, const QList<CsRScheduleSendAddr> &addrList)
{
    if(cbMsgId != CallbackStatus::Schedule::_0)
    {
        UIHelper::hideLoading(this);
        UIHelper::ShowMessageBoxError(msg);
        return;
    }
    curNodesList = addrList;
    ui->tw_nodes->setRowCount(curNodesList.size());
    for(int i = 0;i < curNodesList.size(); ++i)
    {
        CsRScheduleSendAddr addr = curNodesList.at(i);
        QTableWidgetItem* item1 = new QTableWidgetItem;
        item1->setIcon(nodesStateToIcon(addr.getState()));
        item1->setText(QString("%1").arg(i));
        ui->tw_nodes->setItem(i,NodersTableHeaderElement::NODER_INDEX,item1);

        QTableWidgetItem* item2 = new QTableWidgetItem;
        item2->setText(addr.getClientUuid());
        ui->tw_nodes->setItem(i,NodersTableHeaderElement::NODER_CLIENT_UUID,item2);

        QTableWidgetItem* item3 = new QTableWidgetItem;
        item3->setText(addr.getTaskUuid());
        ui->tw_nodes->setItem(i,NodersTableHeaderElement::NODER_NODER_NAME,item3);

        //TODO 以后需要获取该节点服务器所属群组
        QTableWidgetItem* item4 = new QTableWidgetItem;
        item4->setText(tr("上云科技"));
        ui->tw_nodes->setItem(i,NodersTableHeaderElement::NODER_GROUP,item4);
        QTableWidgetItem* item5 = new QTableWidgetItem;
        quint8 state = addr.getState();
        item5->setText(nodesStateToText(addr.getState()));
        ui->tw_nodes->setItem(i,NodersTableHeaderElement::NODER_STATE,item5);

        QTableWidgetItem* item6 = new QTableWidgetItem;
        item6->setText(tr("成功"));
        ui->tw_nodes->setItem(i,NodersTableHeaderElement::NODER_ERRINFO,item6);
        UIHelper::hideLoading(this);
    }
    UIHelper::hideLoading(this);
    UIHelper::showLoading(this,tr("获取文件列表"));
    ListVCsAScSendFilesRunnable* vFile = new ListVCsAScSendFilesRunnable(this);
    vFile->setTaskUuid(taskUuid);
    QThreadPool::globalInstance()->start(vFile);
}

void EditScheduleWidget::on_itemtaskCallback(const qint32 cbMsgId, const QString &msg, const QList<VCsAScSendFiles> &vFileList)
{
    if(cbMsgId != CallbackStatus::Schedule::_0)
    {
        UIHelper::hideLoading(this);
        UIHelper::ShowMessageBoxError(msg);
        return;
    }
    int i = 0 ;
    ui->tw_files->setRowCount(vFileList.size());
    curVFilesList = vFileList;
    UIHelper::showLoading(this,tr("读取数据 ..."));
    for(i = 0;i < curVFilesList.size(); ++i) {
        VCsAScSendFiles vFile;
        vFile= curVFilesList.at(i);
        QTableWidgetItem* item1 = new QTableWidgetItem;
        item1->setIcon(filesStateToIcon(vFile.getState()));
        item1->setText(QString("%1").arg(i));
        ui->tw_files->setItem(i,FilesTableHeaderElement::FILES_INDEX,item1);

        QTableWidgetItem* item2 = new QTableWidgetItem;
        item2->setText(vFile.getFileName());
        ui->tw_files->setItem(i,FilesTableHeaderElement::FILES_FILENAME,item2);

        QTableWidgetItem* item3 = new QTableWidgetItem;
        item3->setText(vFile.getTaskUuid());
        ui->tw_files->setItem(i,FilesTableHeaderElement::FILES_SENDTIME,item3);


        QTableWidgetItem* item4 = new QTableWidgetItem;
        item4->setText(filesStateToText(vFile.getState()));
        item4->setText(QString("%1").arg(vFile.getState()));
        ui->tw_files->setItem(i,FilesTableHeaderElement::FILES_STATE,item4);

        QTableWidgetItem* item5 = new QTableWidgetItem;
        item5->setText(vFile.getErrMsg());
        ui->tw_files->setItem(i,FilesTableHeaderElement::FILES_ERRINFO,item5);
    }
    UIHelper::hideLoading(this);
}

void EditScheduleWidget::showEvent(QShowEvent *event)
{
    loadDatas();
}

void EditScheduleWidget::initWindow()
{
    //设置节点服务器与关联文件显示位置为透明
    ui->lab_addr->setAttribute(Qt::WA_TranslucentBackground);
    ui->lab_addr_pos->setAttribute(Qt::WA_TranslucentBackground);
    ui->lab_file->setAttribute(Qt::WA_TranslucentBackground);
    ui->lab_file_pos->setAttribute(Qt::WA_TranslucentBackground);
    ////节点服务器列表
    //广播节点服务器列表选中1行
    connect(ui->tw_nodes,&TableWidget::evt_selectedRow,this,&EditScheduleWidget::on_nodeSelectedRow);
    //广播节点服务器列表选中多行
    connect(ui->tw_nodes,&TableWidget::evt_selectedRows,this,&EditScheduleWidget::on_nodeSelectedRows);
    //广播节点服务器列表双击1行
    connect(ui->tw_nodes,&TableWidget::evt_doubleSelected,this,&EditScheduleWidget::on_nodeDoubleSelected);
    ui->tw_nodes->setHeaderColumnWidth(NodersTableHeaderElement::NODER_INDEX,50);
    ui->tw_nodes->setHeaderColumnWidth(NodersTableHeaderElement::NODER_CLIENT_UUID,20.0/100);
    ui->tw_nodes->setHeaderColumnWidth(NodersTableHeaderElement::NODER_NODER_NAME,20.0/100);
    ui->tw_nodes->setHeaderColumnWidth(NodersTableHeaderElement::NODER_GROUP,20.0/100);
    ui->tw_nodes->setHeaderColumnWidth(NodersTableHeaderElement::NODER_STATE,100);
    ui->tw_nodes->setHeaderColumnWidth(NodersTableHeaderElement::NODER_ERRINFO,40.0/100);
    //设置表头每列对齐方式,如果不设置某一列,这一列将按水平和垂直都居中对齐
    //ui->tw_nodes->setHeaderColumnAlignment(Widget::INDEX,Qt::AlignRight | Qt::AlignCenter);
    ////文件列表
    //广播文件列表选中1行
    connect(ui->tw_files,&TableWidget::evt_selectedRow,this,&EditScheduleWidget::on_filesSelectedRow);
    //广播文件列表选中多行
    connect(ui->tw_files,&TableWidget::evt_selectedRows,this,&EditScheduleWidget::on_filesSelectedRows);
    //广播文件列表双击1行
    connect(ui->tw_files,&TableWidget::evt_doubleSelected,this,&EditScheduleWidget::on_filesDoubleSelected);
    ui->tw_files->setHeaderColumnWidth(EditScheduleWidget::FilesTableHeaderElement::FILES_INDEX,10.0/100);
    ui->tw_files->setHeaderColumnWidth(EditScheduleWidget::FilesTableHeaderElement::FILES_FILENAME,30.0/100);
    ui->tw_files->setHeaderColumnWidth(EditScheduleWidget::FilesTableHeaderElement::FILES_SENDTIME,30.0/100);
    ui->tw_files->setHeaderColumnWidth(EditScheduleWidget::FilesTableHeaderElement::FILES_STATE,20.0/100);
    ui->tw_files->setHeaderColumnWidth(EditScheduleWidget::FilesTableHeaderElement::FILES_ERRINFO,10.0/100);
    //设置表头每列对齐方式,如果不设置某一列,这一列将按水平和垂直都居中对齐
    //ui->tw_files->setHeaderColumnAlignment(Widget::INDEX,Qt::AlignRight | Qt::AlignCenter);
    loadComboBox();
}

void EditScheduleWidget::loadDatas()
{
    ItemScheduleTaskRunnable* task = new ItemScheduleTaskRunnable(this);
    task->setTaskUuid(taskUuid);
    QThreadPool::globalInstance()->start(task);
}

QPixmap EditScheduleWidget::taskStateToIcon(const quint8 state)
{
    //TODO  缓存中界面不可见 没有图标
    QPixmap taskIcon;
    QSize sizeIcon(15,15);
    switch (state) {
    case Sche::Task_State::DISCARD:
        taskIcon = QPixmap(":/ddmi/schedule/imgs/STATE_DISCARD");
        break;
    case Sche::Task_State::USABLE:
        taskIcon = QPixmap(":/ddmi/schedule/imgs/STATE_USABLE");
        break;
    case Sche::Task_State::PRESEND:
        taskIcon = QPixmap(":/ddmi/schedule/imgs/STATE_PRESEND");
        break;
    case Sche::Task_State::SENDING:
        taskIcon = QPixmap(":/ddmi/schedule/imgs/STATE_SENDING");
        break;
    case Sche::Task_State::ADDRISNULL:
        taskIcon = QPixmap(":/ddmi/schedule/imgs/STATE_ADDRISNULL");
        break;
    case Sche::Task_State::SENDERROR:
        taskIcon = QPixmap(":/ddmi/schedule/imgs/STATE_SENDERROR");
        break;
    case Sche::Task_State::SENDSUCCESS:
        taskIcon = QPixmap(":/ddmi/schedule/imgs/STATE_SENDSUCCESS");
        break;
    case Sche::Task_State::DOWNERROR:
        taskIcon = QPixmap(":/ddmi/schedule/imgs/STATE_DOWNERROR");
        break;
    case Sche::Task_State::DOWNSUCCESS:
        taskIcon = QPixmap(":/ddmi/schedule/imgs/STATE_DOWNSUCCESS");
        break;
    case Sche::Task_State::EXECERROR:
        taskIcon = QPixmap(":/ddmi/schedule/imgs/STATE_EXECERROR");
        break;
    case Sche::Task_State::EXECSUCCESS:
        taskIcon = QPixmap(":/ddmi/schedule/imgs/STATE_EXECSUCCESS");
        break;
    case Sche::Task_State::TASKERROR:
        taskIcon = QPixmap(":/ddmi/schedule/imgs/STATE_TASKERROR");
        break;
    case Sche::Task_State::TASKSUCCESS:
        taskIcon = QPixmap(":/ddmi/schedule/imgs/STATE_TASKSUCCESS");
        break;
    case Sche::Task_State::PAUSE:
        taskIcon = QPixmap(":/ddmi/schedule/imgs/STATE_PAUSE");
        break;
    default:
        break;
    }
    QPixmap stateIcon = taskIcon.scaled(sizeIcon);
    return stateIcon;
}

QString EditScheduleWidget::taskStateToText(const quint8 state)
{
    QString text;
    switch (state) {
    case Sche::Task_State::DISCARD:
        text = tr("废弃");
        break;
    case Sche::Task_State::USABLE:
        text = tr("可用");
        break;
    case Sche::Task_State::PRESEND:
        text = tr("准备下发");
        break;
    case Sche::Task_State::SENDING:
        text = tr("正在下发");
        break;
    case Sche::Task_State::ADDRISNULL:
        text = tr("目标地址为空");
        break;
    case Sche::Task_State::SENDERROR:
        text = tr("下发错误");
        break;
    case Sche::Task_State::SENDSUCCESS:
        text = tr("下发成功");
        break;
    case Sche::Task_State::DOWNERROR:
        text = tr("下载错误");
        break;
    case Sche::Task_State::DOWNSUCCESS:
        text = tr("下载成功");
        break;
    case Sche::Task_State::EXECERROR:
        text = tr("执行失败");
        break;
    case Sche::Task_State::EXECSUCCESS:
        text = tr("执行成功");
        break;
    case Sche::Task_State::TASKERROR:
        text = tr("任务处理失败");
        break;
    case Sche::Task_State::TASKSUCCESS:
        text = tr("任务处理成功");
        break;
    case Sche::Task_State::PAUSE:
        text = tr("pause");
        break;
    case Sche::Task_State::CACHEING:
        text = tr("cache");
        break;
    default:
        break;
    }
    return text;
}

QString EditScheduleWidget::nodesStateToText(const quint8 state)
{
    QString text;
    switch(state) {
    case Sche::SendAddr_State::DISCARD:
        text = tr("废弃");
        break;
    case Sche::SendAddr_State::USABLE:
        text = tr("可用");
        break;
    case Sche::SendAddr_State::PRESEND:
        text = tr("准备下发");
        break;
    case Sche::SendAddr_State::SENDING:
        text = tr("正在下发");
        break;
    case Sche::SendAddr_State::SENDERROR:
        text = tr("下发错误");
        break;
    case Sche::SendAddr_State::SENDSUCCESS:
        text = tr("下发成功");
        break;
    case Sche::SendAddr_State::DOWNERROR:
        text = tr("下载错误");
        break;
    case Sche::SendAddr_State::DOWNSUCCESS:
        text = tr("下载成功");
        break;
    case Sche::SendAddr_State::EXECERROR:
        text = tr("执行失败");
        break;
    case Sche::SendAddr_State::EXECSUCCESS:
        text = tr("执行成功");
        break;
    default:
        break;
    }
    return text;
}

QIcon EditScheduleWidget::nodesStateToIcon(const quint8 state)
{
    QIcon nodeIcon;
    switch (state) {
    case Sche::SendAddr_State::DISCARD:
        nodeIcon = QIcon(":/ddmi/schedule/imgs/STATE_DISCARD");
        break;
    case Sche::SendAddr_State::USABLE:
        nodeIcon = QIcon(":/ddmi/schedule/imgs/STATE_USABLE");
        break;
    case Sche::SendAddr_State::PRESEND:
        nodeIcon = QIcon(":/ddmi/schedule/imgs/STATE_PRESEND");
        break;
    case Sche::SendAddr_State::SENDING:
        nodeIcon = QIcon(":/ddmi/schedule/imgs/STATE_SENDING");
        break;
    case Sche::SendAddr_State::SENDERROR:
        nodeIcon = QIcon(":/ddmi/schedule/imgs/STATE_SENDERROR");
        break;
    case Sche::SendAddr_State::SENDSUCCESS:
        nodeIcon = QIcon(":/ddmi/schedule/imgs/STATE_SENDSUCCESS");
        break;
    case Sche::SendAddr_State::DOWNERROR:
        nodeIcon = QIcon(":/ddmi/schedule/imgs/STATE_DOWNERROR");
        break;
    case Sche::SendAddr_State::DOWNSUCCESS:
        nodeIcon = QIcon(":/ddmi/schedule/imgs/STATE_DOWNSUCCESS");
        break;
    case Sche::SendAddr_State::EXECERROR:
        nodeIcon = QIcon(":/ddmi/schedule/imgs/STATE_EXECERROR");
        break;
    case Sche::SendAddr_State::EXECSUCCESS:
        nodeIcon = QIcon(":/ddmi/schedule/imgs/STATE_EXECSUCCESS");
        break;
    default:
        break;
    }
    return nodeIcon;
}

QString EditScheduleWidget::filesStateToText(const quint8 state)
{
    QString text;
    switch(state) {
    case Sche::SendFile_State::DISCARD:
        text = tr("废弃");
        break;
    case Sche::SendFile_State::USABLE:
        text = tr("可用");
        break;
    case Sche::SendFile_State::PRESEND:
        text = tr("准备下发");
        break;
    case Sche::SendFile_State::SENDING:
        text = tr("正在下发");
        break;
    case Sche::SendFile_State::SENDERROR:
        text = tr("下发错误");
        break;
    case Sche::SendFile_State::SENDSUCCESS:
        text = tr("下发成功");
        break;
    case Sche::SendFile_State::DOWNERROR:
        text = tr("下载错误");
        break;
    case Sche::SendFile_State::DOWNSUCCESS:
        text = tr("下载成功");
        break;
    case Sche::SendFile_State::EXECERROR:
        text = tr("执行失败");
        break;
    case Sche::SendFile_State::EXECSUCCESS:
        text = tr("执行成功");
        break;
    default:
        break;
    }
    return text;
}

QIcon EditScheduleWidget::filesStateToIcon(const quint8 state)
{
    QIcon filesIcon;
    switch (state) {
    case Sche::SendFile_State::DISCARD:
        filesIcon = QIcon(":/ddmi/schedule/imgs/STATE_DISCARD");
        break;
    case Sche::SendFile_State::USABLE:
        filesIcon = QIcon(":/ddmi/schedule/imgs/STATE_USABLE");
        break;
    case Sche::SendFile_State::PRESEND:
        filesIcon = QIcon(":/ddmi/schedule/imgs/STATE_PRESEND");
        break;
    case Sche::SendFile_State::SENDING:
        filesIcon = QIcon(":/ddmi/schedule/imgs/STATE_SENDING");
        break;
    case Sche::SendFile_State::SENDERROR:
        filesIcon = QIcon(":/ddmi/schedule/imgs/STATE_SENDERROR");
        break;
    case Sche::SendFile_State::SENDSUCCESS:
        filesIcon = QIcon(":/ddmi/schedule/imgs/STATE_SENDSUCCESS");
        break;
    case Sche::SendFile_State::DOWNERROR:
        filesIcon = QIcon(":/ddmi/schedule/imgs/STATE_DOWNERROR");
        break;
    case Sche::SendFile_State::DOWNSUCCESS:
        filesIcon = QIcon(":/ddmi/schedule/imgs/STATE_DOWNSUCCESS");
        break;
    case Sche::SendFile_State::EXECERROR:
        filesIcon = QIcon(":/ddmi/schedule/imgs/STATE_EXECERROR");
        break;
    case Sche::SendFile_State::EXECSUCCESS:
        filesIcon = QIcon(":/ddmi/schedule/imgs/STATE_EXECSUCCESS");
        break;
    default:
        break;
    }
    return filesIcon;
}

void EditScheduleWidget::loadComboBox()
{
    ui->cb_strategy->clear();
    QStringList textList;
    textList << tr("默认策略");

    QStringList valueList;
    valueList << tr("1");

    ui->cb_strategy->setShowInfo(textList,valueList);
}
void EditScheduleWidget::setTaskUuid(const QString &value)
{
    taskUuid = value;
}


void EditScheduleWidget::on_btn_quit_clicked()
{
    UIHelper::OpenInSelf(this,new DirScheduleWidget);
}

void EditScheduleWidget::on_btn_nodes_send_clicked()
{
    UIHelper::showLoading(this,tr("正在下发"));
    UpdateScheTaskAddrRunnable* addr = new UpdateScheTaskAddrRunnable(this);
    addr->setScheAddr(taskUuid,selectedNodesUuid,Sche::SendAddr_State::USABLE);
    QThreadPool::globalInstance()->start(addr);
}

void EditScheduleWidget::on_btn_nodes_del_clicked()
{
    int ok = UIHelper::ShowMessageBoxQuesion(tr("你确定要删除记录吗?"));
    if(!ok) {
        return;
    }
    UIHelper::showLoading(this,tr("正在删除"));
    DelScheduleTaskAddrRunnable* addr = new DelScheduleTaskAddrRunnable(this);
    addr->setAddrInfo(taskUuid,selectedNodesUuid);
    QThreadPool::globalInstance()->start(addr);
}

void EditScheduleWidget::on_btn_nodes_add_clicked()
{
    GroupTreeWidget* widget = new GroupTreeWidget;
    widget->setParamsForClientUuid(&m_clientUuid,&m_descriptionForGroup);
    connect(widget,SIGNAL(evt_ok()),this,SLOT(on_addNodes()));
    widget->show();
}

void EditScheduleWidget::on_addNodes()
{
    AddScheduleTaskAddrRunable* addr = new AddScheduleTaskAddrRunable(this);
    addr->setAddrInfo(taskUuid, m_clientUuid,m_descriptionForGroup);
    QThreadPool::globalInstance()->start(addr);
}

void EditScheduleWidget::on_btn_nodes_exec_clicked()
{
    UIHelper::showLoading(this,tr("正在执行"));
    //TODO 执行是要修改为何种状态 有待商讨
    UpdateScheTaskAddrRunnable* addr = new UpdateScheTaskAddrRunnable(this);
    QString dateTime;
    TimerUtil::toString(dateTime);
    addr->setScheAddr(taskUuid,selectedNodesUuid,Sche::SendAddr_State::USABLE,dateTime);
    QThreadPool::globalInstance()->start(addr);
}

void EditScheduleWidget::on_btn_files_del_clicked()
{
    int ok = UIHelper::ShowMessageBoxQuesion(tr("你确定要删除记录吗?"));
    if(!ok) {
        return;
    }
    UIHelper::showLoading(this,tr("正在删除"));
    DelScheduleTaskFileRunnable* files = new DelScheduleTaskFileRunnable(this);
    files->setFilesInfo(selectedFilesUuid);
    QThreadPool::globalInstance()->start(files);
}

void EditScheduleWidget::on_btn_save_clicked()
{
    UpdateScheduleTaskRunnable * updateTask = new UpdateScheduleTaskRunnable(this);
    QList<CsRScheduleTask> taskList;
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
    m_task.setDescription(ui->te_description->toPlainText().trimmed());
    if(m_task.getDescription().isEmpty()) {
        UIHelper::ShowMessageBoxError("任务描术为空");
        return;
    }
    taskList.append(m_task);
    updateTask->setTaskList(taskList);
    QThreadPool::globalInstance()->start(updateTask);
}
