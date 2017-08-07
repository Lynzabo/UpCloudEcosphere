#include "dirstructwidget.h"
#include "ui_dirstructwidget.h"
#include "modules/common/uihelper.h"
#include "editstructwidget.h"
#include "baseiremote.h"
using namespace RemoteUIEnvironment;
using namespace Environment::Task_Status::Center;
#include "../../../../FrontBusinessIRemoteUI/DDMIRemoteUI/StructOperaIRemoteUI/structoperairemoteui.h"
DirStructWidget::DirStructWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DirStructWidget)
{
    ui->setupUi(this);
    initWindow();
    initDatas();
}

DirStructWidget::~DirStructWidget()
{
    delete this->page;
    delete ui;
}

void DirStructWidget::showEvent(QShowEvent *)
{
    loadDatas();
}

void DirStructWidget::initWindow()
{
    ui->btn_open->setEnabled(false);
    //任务列表
    //设置分页导航条可用
    ui->tw_content->setPageNavatorUsable(true);
    //设置表头
    //设置表头列数量
    ui->tw_content->table_body->horizontalHeader()->setVisible(true);
    ui->tw_content->table_body->setColumnCount(6);
    //设置表头每列标签
    ui->tw_content->table_body->setHeaderColumnLabel(DirStructWidget::INDEX,tr("序号","table_body"));
    ui->tw_content->table_body->setHeaderColumnLabel(DirStructWidget::TASKNAME,tr("任务名称","table_body"));
    ui->tw_content->table_body->setHeaderColumnLabel(DirStructWidget::SENDTIME,tr("下发时间","table_body"));
    ui->tw_content->table_body->setHeaderColumnLabel(DirStructWidget::STRATEGY,tr("任务策略","table_body"));
    ui->tw_content->table_body->setHeaderColumnLabel(DirStructWidget::STATE,tr("state","table_body"));
    ui->tw_content->table_body->setHeaderColumnLabel(DirStructWidget::INSERTOR,tr("insertor","table_body"));
    //设置表头每列宽比
    ui->tw_content->table_body->setHeaderColumnWidth(DirStructWidget::INDEX,  60);
    ui->tw_content->table_body->setHeaderColumnWidth(DirStructWidget::TASKNAME,0.3);
    ui->tw_content->table_body->setHeaderColumnWidth(DirStructWidget::SENDTIME,0.2);
    ui->tw_content->table_body->setHeaderColumnWidth(DirStructWidget::STRATEGY,0.2);
    ui->tw_content->table_body->setHeaderColumnWidth(DirStructWidget::STATE,0.2);
    ui->tw_content->table_body->setHeaderColumnWidth(DirStructWidget::INSERTOR,0.1);
    //设置表头每列对齐方式
    ui->tw_content->table_body->setHeaderColumnAlignment(DirStructWidget::INDEX,Qt::AlignRight | Qt::AlignCenter);
    //设置表头可排序列,默认为都不可排序
    //参数2的值是分页getOrderFieldName的值,使用该值做排序,因此命名名成数据库字段名,大小写保持与SQL语句一致
    ui->tw_content->table_body->setHeaderColumnCanSort(DirStructWidget::TASKNAME,QString("TASK_NAME"));
    ui->tw_content->table_body->setHeaderColumnCanSort(DirStructWidget::SENDTIME,QString("SEND_TIME"));
    ui->tw_content->table_body->setHeaderColumnCanSort(DirStructWidget::STATE,QString("STATE"));
    ui->tw_content->table_body->setHeaderColumnCanSort(DirStructWidget::INSERTOR,QString("INSERTOR"));
    //关联表格相关信号      一个线程,默认的是用direct，检查一下该用&
    //广播选中表格体1行
    connect(ui->tw_content,&PageTableWidget::evt_tableBodySelectedRow,this,&DirStructWidget::on_tableBodySelectedRow);
    //广播选中多行
    connect(ui->tw_content,&PageTableWidget::evt_tableBodySelectedRows,this,&DirStructWidget::on_tableBodySelectedRows);
    //广播双击1行
    connect(ui->tw_content,&PageTableWidget::evt_tableBodyDoubleSelected,this,&DirStructWidget::on_tableBodyDoubleSelected);
    //广播选中空白区域
    connect(ui->tw_content,&PageTableWidget::evt_tableBodySelectedNull,this,&DirStructWidget::on_tableBodySelectedNull);
    //广播表格
    connect(ui->tw_content,&PageTableWidget::evt_pageTableAccept,this,&DirStructWidget::on_pageTableAccept);

    loadComboBoxText();
}

void DirStructWidget::initDatas()
{
    selectedTaskUuids.clear();
    ui->btn_open->setEnabled(false);
    ui->btn_folder->setIcon(QIcon(":ddmi/unstruct/imgs/unexpand"));

    newBtn = new QPushButton(this);
    newBtn->setStyleSheet("background-color: rgb(255, 255, 255,100);");
    newBtn->setIcon(QIcon(":/ddmi/unstruct/imgs/expand"));
    connect(newBtn,SIGNAL(clicked(bool)),this,SLOT(on_foldered()));
    newBtn->hide();
    curTaskList.clear();
    selectedTaskUuids.clear();
    addrInfoList.clear();
    fileInfoList.clear();
    statusInfoList.clear();


    this->page = new Page;
}


void DirStructWidget::on_tableBodySelectedRow(int selectedRow)
{
    //TODO
    selectedTaskUuids.clear();
    if(curTaskList.at(selectedRow).getState() == Stru::Task_State::PARSESUCCESS)
    {
        return;
    }
    selectedTaskUuids.append(curTaskList.at(selectedRow).getUuid());
    ui->btn_open->setEnabled(true);
}

void DirStructWidget::on_tableBodySelectedRows(QList<int> selectedRows)
{
    //TODO
    selectedTaskUuids.clear();
    for(int i:selectedRows) {
        if(curTaskList.at(i).getState() == Stru::Task_State::PARSESUCCESS)
        {
            continue;
        }
        QString uuid = curTaskList.at(i).getUuid();
        selectedTaskUuids.append(uuid);
    }
    ui->btn_open->setEnabled(true);
}

void DirStructWidget::on_tableBodyDoubleSelected(int selectedRow)
{
    selectedTaskUuids.clear();
    if(curTaskList.at(selectedRow).getState() == Stru::Task_State::PARSESUCCESS)
    {
        return;
    }
    EditStructWidget* eWidget = new EditStructWidget(this);
    QString taskUuid = curTaskList.at(selectedRow).getUuid();
    selectedTaskUuids.append(taskUuid);
    eWidget->setTaskUUID(taskUuid);
    UIHelper::OpenInSelf(this,eWidget);
    ui->btn_open->setEnabled(true);
}

void DirStructWidget::on_tableBodySelectedNull()
{
    selectedTaskUuids.clear();
}

void DirStructWidget::on_pageTableAccept(const Page *page)
{
    *(this->page) = *page;
    loadDatas();
}

void DirStructWidget::on_foldered()
{
    ui->w_folder->show();
    newBtn->hide();
}

void DirStructWidget::on_addTask()
{
    AddStructTaskRunnable* addTask = new AddStructTaskRunnable(this);
    addTask->setAddCondition(taskInfo,addrInfoList,fileInfoList,statusInfoList);
    QThreadPool::globalInstance()->start(addTask);
}

void DirStructWidget::on_itemtaskCallback(const qint32 msgId, const QString &msg, bool flg)
{
    if(msgId != CallbackStatus::Struct::_0){
        UIHelper::hideLoading(this);
        UIHelper::ShowMessageBoxError(msg);
        return;
    }
    //    UIHelper::hideLoading(this);
    if(flg) {
        loadDatas();
    }
}

void DirStructWidget::loadDatas()
{
    UIHelper::showLoading(this,tr("获取数据"));
    ListStructTaskRunnable* task = new ListStructTaskRunnable(this);
    QVariantMap params;
    params.insert("taskname",ui->l_taskName->text().trimmed());
    params.insert("insertor",ui->l_insertor->text().trimmed());
    params.insert("strategy",ui->l_strategy->text().trimmed());
    int index = ui->cb_showState->currentIndex();
    if(index < 1) {
        params.insert("state","");
    }
    else {
        params.insert("state",ui->cb_showState->itemTextValue(index).toString());
    }
    params.insert("send_time_begin",ui->dte_sendTime_begin->dateTime().toString("yyyy-MM-dd HH:mm:ss").trimmed());
    params.insert("send_time_end",ui->dte_sendTime_end->dateTime().toString("yyyy-MM-dd HH:mm:ss").trimmed());
    params.insert("exec_time_begin",ui->dte_execTime_begin->dateTime().toString("yyyy-MM-dd HH:mm:ss").trimmed());
    params.insert("exec_time_end",ui->dte_execTime_end->dateTime().toString("yyyy-MM-dd HH:mm:ss").trimmed());
    //设置查询条件信息
    task->setTaskInfo(params);
    task->setFilterPage(this->page);
    QThreadPool::globalInstance()->start(task);

}

QIcon DirStructWidget::stateToIcon(const quint8 state)
{
    //TODO  缓存中界面不可见 没有图标
    QIcon icon;
    switch (state) {
    case Stru::Task_State::DISCARD:
        icon = QIcon(":/ddmi/struct/imgs/STATE_DISCARD");
        break;
    case Stru::Task_State::PRESEND:
        icon = QIcon(":/ddmi/struct/imgs/STATE_PRESEND");
        break;
    case Stru::Task_State::SENDING:
        icon = QIcon(":/ddmi/struct/imgs/STATE_SENDING");
        break;
    case Stru::Task_State::ADDRISNULL:
        icon = QIcon(":/ddmi/struct/imgs/STATE_ADDRISNULL");
        break;
    case Stru::Task_State::SENDERROR:
        icon = QIcon(":/ddmi/struct/imgs/STATE_SENDERROR");
        break;
    case Stru::Task_State::SENDSUCCESS:
        icon = QIcon(":/ddmi/struct/imgs/STATE_SENDSUCCESS");
        break;
    case Stru::Task_State::DOWNERROR:
        icon = QIcon(":/ddmi/struct/imgs/STATE_DOWNERROR");
        break;
    case Stru::Task_State::DOWNSUCCESS:
        icon = QIcon(":/ddmi/struct/imgs/STATE_DOWNSUCCESS");
        break;
    case Stru::Task_State::PARSEERROR:
        icon = QIcon(":/ddmi/struct/imgs/STATE_PARSEERROR");
        break;
    case Stru::Task_State::PARSESUCCESS:
        icon = QIcon(":/ddmi/struct/imgs/STATE_PARSESUCCESS");
        break;
    case Stru::Task_State::TASKERROR:
        icon = QIcon(":/ddmi/struct/imgs/STATE_TASKERROR");
        break;
    case Stru::Task_State::TASKSUCCESS:
        icon = QIcon(":/ddmi/struct/imgs/STATE_TASKSUCCESS");
        break;
    case Stru::Task_State::PAUSE:
        icon = QIcon(":/ddmi/struct/imgs/STATE_PAUSE");
        break;
    default:
        break;
    }
    return icon;
}

QString DirStructWidget::stateToText(const quint8 state)
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

QString DirStructWidget::strategyToText(const quint16 strategy)
{
    Q_UNUSED(strategy)
    return tr("正常逻辑");
}

void DirStructWidget::loadComboBoxText()
{
    ui->cb_showState->clear();
    QStringList textList;
    textList<< tr("不限") << tr("废弃") << tr("可用") << tr("准备下发") << tr("正在下发") << tr("目标地址为空") << tr("下发错误") << tr("下发成功")
            << tr("下载错误") << tr("下载成功") << tr("解析失败") << tr("解析成功")<< tr("处理任务失败") << tr("处理任务成功") << tr("pause")  ;
    QStringList valueList;
    valueList<< tr("") << tr("0")<< tr("1") << tr("2") << tr("3") << tr("4") << tr("5") << tr("6") << tr("7") << tr("8") << tr("9")
             << tr("10") << tr("11") << tr("12") << tr("13") ;
    ui->cb_showState->setShowInfo(textList,valueList);
    QStringList setTextList;
    setTextList << tr("setTaskState") << tr("废弃") << tr("可用");
    QStringList setValueList;
    setValueList << tr("") << tr("0")<< tr("1") ;
    ui->cb_setState->clear();
    ui->cb_setState->setShowInfo(setTextList,setValueList);
}


void DirStructWidget::on_itemtaskCallback(const qint32 msgId, const QString &msg, const QList<CsRStructTask> &taskList)
{
    UIHelper::showLoading(this,tr("获取数据成功，正在加载数据 ..."));
    if(msgId != CallbackStatus::Struct::_0){
        UIHelper::hideLoading(this);
        UIHelper::ShowMessageBoxError(msg);
        return;
    }
    ui->tw_content->setPage(this->page);
    ui->tw_content->table_body->setRowCount(taskList.size());
    curTaskList = taskList;
    for(int i = 0;i < curTaskList.size(); ++i) {
        CsRStructTask task = curTaskList.at(i);
        QTableWidgetItem* item1 = new QTableWidgetItem;
        //TODO 待加图标
        item1->setIcon(stateToIcon(task.getState()));
        item1->setText(QString("%1").arg(i));
        ui->tw_content->table_body->setItem(i,TableHeaderElement::INDEX,item1);

        QTableWidgetItem* item2 = new QTableWidgetItem;
        item2->setText(task.getTaskName());
        ui->tw_content->table_body->setItem(i,TableHeaderElement::TASKNAME,item2);

        QTableWidgetItem* item3 = new QTableWidgetItem;
        item3->setText(task.getSendTime());
        ui->tw_content->table_body->setItem(i,TableHeaderElement::SENDTIME,item3);
        //TODO 这里的下拉框选择 以后要重新做
        QTableWidgetItem* item4 = new QTableWidgetItem;
        //        item4->setText(QString::number(task.getStrategy()));
        item4->setText(strategyToText(task.getStrategy()));
        ui->tw_content->table_body->setItem(i,TableHeaderElement::STRATEGY,item4);

        QTableWidgetItem* item5 = new QTableWidgetItem;
        //        item5->setText(QString::number(task.getState()));
        item5->setText(stateToText(task.getState()));
        ui->tw_content->table_body->setItem(i,TableHeaderElement::STATE,item5);

        QTableWidgetItem* item6 = new QTableWidgetItem;
        item6->setText(task.getInsertor());
        ui->tw_content->table_body->setItem(i,TableHeaderElement::INSERTOR,item6);
    }
    UIHelper::hideLoading(this);
}

void DirStructWidget::on_btn_select_clicked()
{
    loadDatas();
}



void DirStructWidget::on_btn_new_clicked()
{

    CreateTaskWidget* addTask = new CreateTaskWidget;
    addTask->setAddTaskInfo(&taskInfo,&addrInfoList,&fileInfoList,&statusInfoList);
    connect(addTask,SIGNAL(evt_save()),this,SLOT(on_addTask()));
    UIHelper::OpenInSelf(this,addTask);
}



void DirStructWidget::on_btn_del_clicked()
{
    int ok = UIHelper::ShowMessageBoxQuesion(tr("你确定要删除记录吗?"));
    if(!ok) {
        return;
    }
    DelStructTaskRunnable* task  =  new DelStructTaskRunnable(this);
    JsonArray params;
    foreach(const QString &uuid,selectedTaskUuids) {
        params.append(uuid);
    }
    task->setTaskInfo(params);
    QThreadPool::globalInstance()->start(task);
}

void DirStructWidget::on_btn_open_clicked()
{
    EditStructWidget* eWidget = new EditStructWidget(this);
    QString taskUuid = selectedTaskUuids.at(0);
    eWidget->setTaskUUID(taskUuid);
    UIHelper::OpenInSelf(this,eWidget);
}



void DirStructWidget::on_cb_setState_currentIndexChanged(int index)
{
    if(index < 1) {
        return;
    }
    if(selectedTaskUuids.isEmpty()) {
        UIHelper::ShowMessageBoxError(tr("Please select a message"));
        return;
    }
    quint8 state = ui->cb_setState->itemTextValue(index).toInt();
    QList<CsRStructTask> taskList;
    for(QList<CsRStructTask>::iterator item = curTaskList.begin();item != curTaskList.end(); ++item)
    {
        if(selectedTaskUuids.contains(item->getUuid()))
        {
            CsRStructTask task = *item;
            task.setState(state);
            taskList.append(task);
        }
    }
    UpdateStructTaskRunnable* task = new UpdateStructTaskRunnable(this);
    task->setTaskList(taskList);
    QThreadPool::globalInstance()->start(task);
}

void DirStructWidget::on_btn_send_clicked()
{
    if(selectedTaskUuids.isEmpty()) {
        UIHelper::ShowMessageBoxError(tr("Please select a message"));
        return;
    }
    QList<CsRStructTask> taskList;
    for(QList<CsRStructTask>::iterator item = curTaskList.begin();item != curTaskList.end(); ++item)
    {
        if(selectedTaskUuids.contains(item->getUuid()))
        {
            CsRStructTask task = *item;
            //设置状态为可用
            task.setState(0x1);
            QDateTime curTime = QDateTime::currentDateTime();
            //设置执行时间为当前时间
            task.setSendTime(curTime.toString("yyyy-MM-dd HH:mm:ss"));
            taskList.append(task);
        }
    }
    UpdateStructTaskRunnable* task = new UpdateStructTaskRunnable(this);
    task->setTaskList(taskList);
    QThreadPool::globalInstance()->start(task);
}

void DirStructWidget::on_btn_pause_clicked()
{
    if(selectedTaskUuids.isEmpty()) {
        UIHelper::ShowMessageBoxError(tr("Please select a message"));
        return;
    }
    QList<CsRStructTask> taskList;
    for(QList<CsRStructTask>::iterator item = curTaskList.begin();item != curTaskList.end(); ++item)
    {
        if(selectedTaskUuids.contains(item->getUuid()))
        {
            CsRStructTask task = *item;
            //设置状态为暂停
            task.setState(0xD);
            taskList.append(task);
        }
    }
    UpdateStructTaskRunnable* task = new UpdateStructTaskRunnable(this);
    task->setTaskList(taskList);
    QThreadPool::globalInstance()->start(task);
}

void DirStructWidget::on_btn_folder_clicked()
{
    oldPos = ui->btn_folder->pos();
    newPos = ui->lab_taskName->pos();
    newPos.setX(oldPos.x());
    newPos.setY(newPos.y() + 12);
    newBtn->move(newPos);
    newBtn->resize(ui->btn_folder->size());

    ui->w_folder->hide();
    newBtn->show();

}
