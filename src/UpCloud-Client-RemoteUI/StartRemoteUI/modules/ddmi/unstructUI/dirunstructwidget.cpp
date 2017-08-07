#include "dirunstructwidget.h"
#include "ui_dirunstructwidget.h"

#include "modules/common/pagetablewidget.h"
#include <QTimer>
#include "modules/common/uihelper.h"
#include "modules/common/combobox.h"
#include <QStackedWidget>
#include "editunstructwidget.h"
#include "../structUI/dirstructwidget.h"

using namespace RemoteUIEnvironment;
using namespace Environment::Task_Status::Center;
DirUnstructWidget::DirUnstructWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DirUnstructWidget)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose);
    ui->btn_folder->setIcon(QIcon(":ddmi/unstruct/imgs/unexpand"));
    //初始化窗口基本数据
    initWindow();
    //初始化参数
    initData();
}

DirUnstructWidget::~DirUnstructWidget()
{
    delete this->page;
    delete ui;
}

void DirUnstructWidget::loadDatas()
{
    UIHelper::showLoading(this,tr("获取数据..."));
    //设置查询条件
    DirUnstructTaskRunnable* list = new DirUnstructTaskRunnable(this);
    QVariantMap params;
    params.insert("taskname",ui->l_taskName->text().trimmed());
    params.insert("insertor",ui->l_insertor->text().trimmed());
    params.insert("strategy",ui->l_strategy->text().trimmed());
    int tem  = ui->cb_showState->currentIndex();
    if(tem == -1) {
        params.insert("state","");
    }
    else {
        params.insert("state",ui->cb_showState->currentValue().toString().trimmed());
    }
    params.insert("send_time_begin",ui->dte_time_begin->dateTime().toString("yyyy-MM-dd HH:mm:ss").trimmed());
    params.insert("send_time_end",ui->dte_time_end->dateTime().toString("yyyy-MM-dd HH:mm:ss").trimmed());

    list->setListCondition(params);
    //设置过滤分页Page
    list->setFilterPage(this->page);
    QThreadPool::globalInstance()->start(list);
}

void DirUnstructWidget::showEvent(QShowEvent *)
{
    loadDatas();
}


void DirUnstructWidget::on_tableBodySelectedRow(int selectedRow)
{
    //设置必须多选按钮不可用
    selectedTasksUUIDs.clear();
    if(curTaskLists.at(selectedRow).getState() == Unstru::Task_State::DOWNSUCCESS)
    {
        return;
    }
    QString uuid = curTaskLists.at(selectedRow).getUuid();
    selectedTasksUUIDs << uuid;
    ui->btn_open->setEnabled(true);
}

void DirUnstructWidget::on_tableBodySelectedRows(QList<int> selectedRows)
{
    //设置必须单选按钮不可用
    selectedTasksUUIDs.clear();
    for(int i : selectedRows)
    {
        if(curTaskLists.at(i).getState() == Unstru::Task_State::DOWNSUCCESS)
        {
            continue;
        }
        QString uuid = curTaskLists.at(i).getUuid();
        selectedTasksUUIDs << uuid;
    }
    ui->btn_open->setEnabled(true);
}

void DirUnstructWidget::on_tableBodyDoubleSelected(int selectedRow)
{
    selectedTasksUUIDs.clear();
    if(curTaskLists.at(selectedRow).getState() == Unstru::Task_State::DOWNSUCCESS)
    {
        return;
    }
    EditUnstructWidget *eWidget = new EditUnstructWidget(this);
    QString uuid = curTaskLists.at(selectedRow).getUuid();
    selectedTasksUUIDs << uuid;
    eWidget->setTaskUUID(uuid);
    UIHelper::OpenInSelf(this,eWidget);
    ui->btn_open->setEnabled(true);
}

void DirUnstructWidget::on_tableBodySelectedNull()
{
    selectedTasksUUIDs.clear();
}

void DirUnstructWidget::on_pageTableAccept(const Page *page)
{
    //    ui->tw_content->table_body->setDefaultAlignment();
    *(this->page) = *page;
    loadDatas();
}

void DirUnstructWidget::on_addTask()
{
    UIHelper::showLoading(this,tr("添加任务"));
    AddUnstructTaskRunnable* addTask =  new AddUnstructTaskRunnable(this);
    addTask->setAddCondition(taskInfo,addrInfoList,fileInfoList,statusInfoList);
    QThreadPool::globalInstance()->start(addTask);
}

void DirUnstructWidget::on_fordered()
{
    ui->w_folder->show();
    newBtn->hide();
}

void DirUnstructWidget::on_itemtaskCallback(const qint32 msgId, const QString &msg, bool flg)
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

void DirUnstructWidget::on_itemtaskCallback(const qint32 msgId, const QString &msg, const QList<CsRUnstructTask> &taskList)
{
    UIHelper::showLoading(this,tr("获取数据成功，正在读取展示 ..."));
    if(msgId != CallbackStatus::Struct::_0){
        UIHelper::hideLoading(this);
        UIHelper::ShowMessageBoxError(msg);
        return;
    }
    curTaskLists = taskList;
    //设置分页基本配置
    ui->tw_content->setPage(this->page);
    ui->tw_content->table_body->clearContents();
    int i = 0 ;
    //设置表格内容总行数
    //    ui->tw_content->table_body->setRowCount(this->page->getNumPerPage());
    ui->tw_content->table_body->setRowCount(curTaskLists.size());
    for(i = 0;i < taskList.size(); ++i)
    {
        CsRUnstructTask task = taskList.at(i);
        QTableWidgetItem* item1 = new QTableWidgetItem;
        //TODO 待加状态图标
        item1->setIcon(stateToIcon(task.getState()));
        item1->setText(QString("%1").arg(i+1));
        ui->tw_content->table_body->setItem(i,TableHeaderElement::INDEX,item1);

        QTableWidgetItem* item2 = new QTableWidgetItem;
        item2->setText(task.getTaskName());
        ui->tw_content->table_body->setItem(i,TableHeaderElement::TASKNAME,item2);

        QTableWidgetItem* item3 = new QTableWidgetItem;
        item3->setText(task.getSendTime());
        ui->tw_content->table_body->setItem(i,TableHeaderElement::SENDTIME,item3);

        QTableWidgetItem* item4 = new QTableWidgetItem;
        //item4->setText(QString::number(task.getStrategy()));
        item4->setText(strategyToText(task.getStrategy()));
        ui->tw_content->table_body->setItem(i,TableHeaderElement::STRATEGY,item4);

        QTableWidgetItem* item5 = new QTableWidgetItem;
        quint8 state = task.getState();
        item5->setText(stateToText(task.getState()));
        ui->tw_content->table_body->setItem(i,TableHeaderElement::STATE,item5);

        QTableWidgetItem* item6 = new QTableWidgetItem;
        item6->setText(task.getInsertor());
        ui->tw_content->table_body->setItem(i,TableHeaderElement::INSERTOR,item6);
    }
    UIHelper::hideLoading(this);
}

void DirUnstructWidget::initWindow()
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
    ui->tw_content->table_body->setHeaderColumnLabel(DirUnstructWidget::INDEX,tr("序号","table_body"));
    ui->tw_content->table_body->setHeaderColumnLabel(DirUnstructWidget::TASKNAME,tr("任务名称","table_body"));
    ui->tw_content->table_body->setHeaderColumnLabel(DirUnstructWidget::SENDTIME,tr("下发时间","table_body"));
    ui->tw_content->table_body->setHeaderColumnLabel(DirUnstructWidget::STRATEGY,tr("任务策略","table_body"));
    ui->tw_content->table_body->setHeaderColumnLabel(DirUnstructWidget::STATE,tr("state","table_body"));
    ui->tw_content->table_body->setHeaderColumnLabel(DirUnstructWidget::INSERTOR,tr("insertor","table_body"));
    //设置表头每列宽比
    ui->tw_content->table_body->setHeaderColumnWidth(DirUnstructWidget::INDEX,  60);
    ui->tw_content->table_body->setHeaderColumnWidth(DirUnstructWidget::TASKNAME,0.3);
    ui->tw_content->table_body->setHeaderColumnWidth(DirUnstructWidget::SENDTIME,0.2);
    ui->tw_content->table_body->setHeaderColumnWidth(DirUnstructWidget::STRATEGY,0.2);
    ui->tw_content->table_body->setHeaderColumnWidth(DirUnstructWidget::STATE,0.2);
    ui->tw_content->table_body->setHeaderColumnWidth(DirUnstructWidget::INSERTOR,0.1);
    //设置表头每列对齐方式
    ui->tw_content->table_body->setHeaderColumnAlignment(DirUnstructWidget::INDEX,Qt::AlignRight | Qt::AlignCenter);
    //设置表头可排序列,默认为都不可排序
    //参数2的值是分页getOrderFieldName的值,使用该值做排序,因此命名名成数据库字段名,大小写保持与SQL语句一致
    ui->tw_content->table_body->setHeaderColumnCanSort(DirUnstructWidget::TASKNAME,QString("TASK_NAME"));
    ui->tw_content->table_body->setHeaderColumnCanSort(DirUnstructWidget::SENDTIME,QString("SEND_TIME"));
    ui->tw_content->table_body->setHeaderColumnCanSort(DirUnstructWidget::STATE,QString("STATE"));
    ui->tw_content->table_body->setHeaderColumnCanSort(DirUnstructWidget::INSERTOR,QString("INSERTOR"));
    //关联表格相关信号      一个线程,默认的是用direct，检查一下该用&
    //广播选中表格体1行
    connect(ui->tw_content,&PageTableWidget::evt_tableBodySelectedRow,this,&DirUnstructWidget::on_tableBodySelectedRow);
    //广播选中多行
    connect(ui->tw_content,&PageTableWidget::evt_tableBodySelectedRows,this,&DirUnstructWidget::on_tableBodySelectedRows);
    //广播双击1行
    connect(ui->tw_content,&PageTableWidget::evt_tableBodyDoubleSelected,this,&DirUnstructWidget::on_tableBodyDoubleSelected);
    //广播选中空白区域
    connect(ui->tw_content,&PageTableWidget::evt_tableBodySelectedNull,this,&DirUnstructWidget::on_tableBodySelectedNull);
    //广播表格
    connect(ui->tw_content,&PageTableWidget::evt_pageTableAccept,this,&DirUnstructWidget::on_pageTableAccept);
    //查询区域下拉菜单
    loadComboBoxText();
}

QIcon DirUnstructWidget::stateToIcon(const quint8 state)
{
    //TODO  缓存中不可见 没有图标
    QIcon icon;
    switch (state) {
    case Unstru::Task_State::DISCARD:
        icon = QIcon(":/ddmi/unstruct/imgs/STATE_DISCARD");
        break;
    case Unstru::Task_State::PRESEND:
        icon = QIcon(":/ddmi/unstruct/imgs/STATE_PRESEND");
        break;
    case Unstru::Task_State::SENDING:
        icon = QIcon(":/ddmi/unstruct/imgs/STATE_SENDING");
        break;
    case Unstru::Task_State::ADDRISNULL:
        icon = QIcon(":/ddmi/unstruct/imgs/STATE_ADDRISNULL");
        break;
    case Unstru::Task_State::SENDERROR:
        icon = QIcon(":/ddmi/unstruct/imgs/STATE_SENDERROR");
        break;
    case Unstru::Task_State::SENDSUCCESS:
        icon = QIcon(":/ddmi/unstruct/imgs/STATE_SENDSUCCESS");
        break;
    case Unstru::Task_State::DOWNERROR:
        icon = QIcon(":/ddmi/unstruct/imgs/STATE_DOWNERROR");
        break;
    case Unstru::Task_State::DOWNSUCCESS:
        icon = QIcon(":/ddmi/unstruct/imgs/STATE_DOWNSUCCESS");
        break;
    case Unstru::Task_State::TASKERROR:
        icon = QIcon(":/ddmi/unstruct/imgs/STATE_TASKERROR");
        break;
    case Unstru::Task_State::TASKSUCCESS:
        icon = QIcon(":/ddmi/unstruct/imgs/STATE_TASKSUCCESS");
        break;
    case Unstru::Task_State::PAUSE:
        icon = QIcon(":/ddmi/unstruct/imgs/STATE_PAUSE");
        break;
    default:
        break;
    }
    return icon;
}

QString DirUnstructWidget::stateToText(const quint8 state)
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

QString DirUnstructWidget::strategyToText(const quint16 strategy)
{
    Q_UNUSED(strategy)
    return tr("正常逻辑");
}

void DirUnstructWidget::loadComboBoxText()
{
    //    QVariantMap item0;
    //    item0.insert(tr("不限"),tr(""));
    //    m_showStateText.append(item0);
    //    QVariantMap item1;
    //    item1.insert(tr("废弃"),tr("0"));
    //    m_showStateText.append(item1);
    //    QVariantMap item2;
    //    item2.insert(tr("可用"),tr("1"));
    //    m_showStateText.append(item2);
    //    QVariantMap item3;
    //    item3.insert(tr("准备下发"),tr("2"));
    //    m_showStateText.append(item3);
    //    QVariantMap item4;
    //    item4.insert(tr("正在下发"),tr("3"));
    //    m_showStateText.append(item4);
    //    QVariantMap item5;
    //    item5.insert(tr("目标地址为空"),tr("4"));
    //    m_showStateText.append(item5);
    //    QVariantMap item6;
    //    item6.insert(tr("下发错误"),tr("5"));
    //    m_showStateText.append(item6);
    //    QVariantMap item7;
    //    item7.insert(tr("下发成功"),tr("6"));
    //    m_showStateText.append(item7);
    //    QVariantMap item8;
    //    item8.insert(tr("下载错误"),tr("7"));
    //    m_showStateText.append(item8);
    //    QVariantMap item9;
    //    item9.insert(tr("下载成功"),tr("8"));
    //    m_showStateText.append(item9);
    //        m_setStateText.append(QVariantMap(tr("设置任务状态 "),tr("设置任务状态 ")));
    //        m_setStateText.append(QVariantMap(m_showStateText);
    QStringList selectTextList;
    selectTextList<< tr("不限") << tr("废弃") << tr("可用") << tr("准备下发") << tr("正在下发") << tr("目标地址为空") << tr("下发错误") << tr("下发成功")
                  << tr("下载错误") << tr("下载成功")<< tr("处理任务失败") << tr("处理任务成功") << tr("pause")  ;
    QStringList selectValueList;
    selectValueList<< tr("") << tr("0")<< tr("1") << tr("2") << tr("3") << tr("4") << tr("5") << tr("6") << tr("7") << tr("8") << tr("9")
                   << tr("10") << tr("11") ;
    ui->cb_showState->setShowInfo(selectTextList,selectValueList);
    QStringList setTextList;
    setTextList << tr("setTaskState") << tr("废弃") << tr("可用");
    QStringList setValueList;
    setValueList << tr("") << tr("0")<< tr("1") ;
    ui->cb_setState->clear();
    ui->cb_setState->setShowInfo(setTextList,setValueList);
}

void DirUnstructWidget::initData()
{
    selectedTasksUUIDs.clear();
    curTaskLists.clear();
    selectedTasksUUIDs.clear();
    addrInfoList.clear();
    fileInfoList.clear();
    statusInfoList.clear();


    newBtn = new QPushButton(this);
    newBtn->setStyleSheet("background-color: rgb(255, 255, 255,100);");
    newBtn->setIcon(QIcon(":/ddmi/unstruct/imgs/expand"));
    connect(newBtn,SIGNAL(clicked(bool)),this,SLOT(on_fordered()));
    newBtn->hide();
    newBtn->move(newPos);
    this->page = new Page;
}

void DirUnstructWidget::on_btn_new_clicked()
{
    newTaskWidget = new CreateTaskWidget;
    newTaskWidget->setAddTaskInfo(&taskInfo,&addrInfoList,&fileInfoList,&statusInfoList);
    connect(newTaskWidget,SIGNAL(evt_save()),this,SLOT(on_addTask()));
    //    connect(this,SIGNAL(evt_addTaskSuccess()),newTaskWidget,SLOT(on_addTaskSuccess()));
    UIHelper::OpenInSelf(this,newTaskWidget);
}

void DirUnstructWidget::on_btn_open_clicked()
{
    EditUnstructWidget *eWidget = new EditUnstructWidget(this);
    QString selectedTaskUUID = selectedTasksUUIDs.at(0);
    eWidget->setTaskUUID(selectedTaskUUID);
    UIHelper::OpenInSelf(this,eWidget);
}


void DirUnstructWidget::on_btn_select_clicked()
{
    loadDatas();
}

void DirUnstructWidget::on_btn_del_clicked()
{
    int ok = UIHelper::ShowMessageBoxQuesion(tr("你确定要删除记录吗?"));
    if(!ok) {
        return;
    }
    UIHelper::showLoading(this,tr("正在删除"));
    DelUnstructTaskRunnable* task  =  new DelUnstructTaskRunnable(this);
    JsonArray params;
    foreach(const QString &str,selectedTasksUUIDs) {
        params.push_back(str);
    }
    task->setTaskUuids(params);
    QThreadPool::globalInstance()->start(task);
}
void DirUnstructWidget::on_cb_setState_currentIndexChanged(int index)
{
    if(index < 1) {
        return;
    }
    if(selectedTasksUUIDs.isEmpty()) {
        UIHelper::ShowMessageBoxInfo(tr("请先选择你要修改条目"));
        return;
    }
    UIHelper::showLoading(this,tr("update date ..."));
    quint8 state = (quint8)ui->cb_setState->itemTextValue(index).toInt();
    QList<CsRUnstructTask> taskList;
    UpdateUnstructTaskRunnable* task = new UpdateUnstructTaskRunnable(this);
    for(QList<CsRUnstructTask>::iterator item = curTaskLists.begin(); item != curTaskLists.end(); ++item) {
        if(selectedTasksUUIDs.contains(item->getUuid())) {
            item->setState(state);
            taskList.append(*item);
        }
    }
    task->setTaskList(taskList);
    QThreadPool::globalInstance()->start(task);
}

void DirUnstructWidget::on_btn_send_clicked()
{
    if(selectedTasksUUIDs.isEmpty()) {
        UIHelper::ShowMessageBoxInfo(tr("请先选择你要下发条目"));
        return;
    }
    QList<CsRUnstructTask> taskList;
    for(QList<CsRUnstructTask>::iterator item = curTaskLists.begin(); item != curTaskLists.end(); ++item) {
        if(selectedTasksUUIDs.contains(item->getUuid())) {
            //不修改当前列表的值
            CsRUnstructTask task = *item;
            //修改任务状态为可用
            task.setState(0x1);
            QDateTime curDate = QDateTime::currentDateTime();
            task.setSendTime(curDate.toString("yyyy-MM-dd HH:mm:ss"));
            taskList.append(task);
        }
    }
    UpdateUnstructTaskRunnable* task = new UpdateUnstructTaskRunnable(this);
    task->setTaskList(taskList);
    QThreadPool::globalInstance()->start(task);
}

void DirUnstructWidget::on_btn_pause_clicked()
{
    if(selectedTasksUUIDs.isEmpty()) {
        UIHelper::ShowMessageBoxInfo(tr("请先选择你要暂停条目"));
        return;
    }
    QList<CsRUnstructTask> taskList;
    for(QList<CsRUnstructTask>::iterator item = curTaskLists.begin(); item != curTaskLists.end(); ++item) {
        if(selectedTasksUUIDs.contains(item->getUuid())) {
            //不修改当前列表的值
            CsRUnstructTask task = *item;
            //修改任务状态为暂停
            task.setState(0xB);
            taskList.append(task);
        }
    }
    UpdateUnstructTaskRunnable* task = new UpdateUnstructTaskRunnable(this);
    task->setTaskList(taskList);
    QThreadPool::globalInstance()->start(task);
}

void DirUnstructWidget::on_btn_folder_clicked()
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
