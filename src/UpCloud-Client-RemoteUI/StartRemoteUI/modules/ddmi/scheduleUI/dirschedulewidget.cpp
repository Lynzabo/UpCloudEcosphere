#include "dirschedulewidget.h"
#include "ui_dirschedulewidget.h"
#include "modules/common/loading.h"
#include "modules/common/uihelper.h"
#include "editschedulewidget.h"
#include "../../../../FrontBusinessIRemoteUI/DDMIRemoteUI/ScheduleOperaIRemoteUI/scheduleoperairemoteui.h"
using namespace RemoteUIEnvironment;
using namespace Environment::Task_Status::Center;
DirScheduleWidget::DirScheduleWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DirScheduleWidget)
{
    ui->setupUi(this);

    initDatas();
    initWindow();
}

DirScheduleWidget::~DirScheduleWidget()
{
    delete ui;
}

void DirScheduleWidget::on_itemtaskCallback(const qint32 cbMsgId, const QString &msg, const QList<CsRScheduleTask> &taskList)
{
    if(cbMsgId != CallbackStatus::Schedule::_0)
    {
        UIHelper::hideLoading(this);
        UIHelper::ShowMessageBoxError(msg);
        return;
    }
    curTaskList = taskList;
    ui->tw_content->setRowCount(curTaskList.size());
    for(int i = 0;i < curTaskList.size(); ++i)
    {
        CsRScheduleTask task = curTaskList.at(i);
        QTableWidgetItem* item1 = new QTableWidgetItem;
        // TODO 图标函数需要添加
        item1->setIcon(stateToIcon(task.getState()));
        item1->setText(QString("%1").arg(i));
        ui->tw_content->setItem(i,TableHeaderElement::INDEX,item1);

        QTableWidgetItem* item2 = new QTableWidgetItem;
        item2->setText(task.getTaskName());
        ui->tw_content->setItem(i,TableHeaderElement::TASKNAME,item2);

        QTableWidgetItem* item3 = new QTableWidgetItem;
        item3->setText(task.getSendTime());
        ui->tw_content->setItem(i,TableHeaderElement::SENDTIME,item3);

        QTableWidgetItem* item4 = new QTableWidgetItem;
        item4->setText(QString::number(task.getStrategy()));
        ui->tw_content->setItem(i,TableHeaderElement::STRATEGY,item4);

        QTableWidgetItem* item5= new QTableWidgetItem;
        item5->setText(stateToText(task.getState()));
        ui->tw_content->setItem(i,TableHeaderElement::STATE,item5);

        QTableWidgetItem* item6 = new QTableWidgetItem;
        item6->setText(task.getInsertor());
        ui->tw_content->setItem(i,TableHeaderElement::INSERTOR,item6);
    }
    UIHelper::hideLoading(this);
}

void DirScheduleWidget::on_selectedRow(int selectRow)
{
    selectedTaskUuids.clear();
    if(curTaskList.at(selectRow).getState() == Sche::Task_State::EXECSUCCESS)
    {
        return;
    }
    QString uuid = curTaskList.at(selectRow).getUuid();
    selectedTaskUuids.append(uuid);
}

void DirScheduleWidget::on_selectedRows(QList<int> selectRows)
{
    selectedTaskUuids.clear();
    foreach(const int index,selectRows)
    {
        if(curTaskList.at(index).getState() == Sche::Task_State::EXECSUCCESS)
        {
            continue;
        }
        QString uuid = curTaskList.at(index).getUuid();
        selectedTaskUuids.append(uuid);
    }
}

void DirScheduleWidget::on_doubleSelected(int selectRow)
{
    selectedTaskUuids.clear();
    if(curTaskList.at(selectRow).getState() == Sche::Task_State::EXECSUCCESS)
    {
        return;
    }
    EditScheduleWidget* edit = new EditScheduleWidget(this);
    QString uuid = curTaskList.at(selectRow).getUuid();
    selectedTaskUuids.append(uuid);
    edit->setTaskUuid(uuid);
    UIHelper::OpenInSelf(this,edit);
}

void DirScheduleWidget::initWindow()
{
    //广播选中1行
    connect(ui->tw_content,&TableWidget::evt_selectedRow,this,&DirScheduleWidget::on_selectedRow);
    //广播选中多行
    connect(ui->tw_content,&TableWidget::evt_selectedRows,this,&DirScheduleWidget::on_selectedRows);
    //广播双击1行
    connect(ui->tw_content,&TableWidget::evt_doubleSelected,this,&DirScheduleWidget::on_doubleSelected);
    ui->tw_content->setHeaderColumnWidth(DirScheduleWidget::INDEX,  60);
    ui->tw_content->setHeaderColumnWidth(DirScheduleWidget::TASKNAME,30.0/100);
    ui->tw_content->setHeaderColumnWidth(DirScheduleWidget::SENDTIME,20.0/100);
    ui->tw_content->setHeaderColumnWidth(DirScheduleWidget::STRATEGY,20.0/100);
    ui->tw_content->setHeaderColumnWidth(DirScheduleWidget::STATE,20.0/100);
    ui->tw_content->setHeaderColumnWidth(DirScheduleWidget::INSERTOR,10.0/100);
    //设置表头每列对齐方式,如果不设置某一列,这一列将按水平和垂直都居中对齐
    //ui->tw_content->setHeaderColumnAlignment(DirScheduleWidget::TASKNAME,Qt::AlignRight | Qt::AlignCenter);
    loadComboBoxText();
}

void DirScheduleWidget::initDatas()
{
    selectedTaskUuids.clear();
    curTaskList.clear();
    ui->btn_folder->setIcon(QIcon(":ddmi/unstruct/imgs/unexpand"));
    newBtn = new QPushButton(this);
    newBtn->setStyleSheet("background-color: rgb(255, 255, 255,100);");
    newBtn->setIcon(QIcon(":/ddmi/unstruct/imgs/expand"));
    connect(newBtn,SIGNAL(clicked(bool)),this,SLOT(on_foldered()));
    newBtn->hide();
}

void DirScheduleWidget::loadDates()
{
    QVariantMap params;
    params["taskName"] = ui->l_taskName->text().trimmed();
    params["insertor"] = ui->l_insertor->text().trimmed();
    params["strategy"] = ui->l_strategy->text().trimmed();
    int index = ui->cb_showState->currentIndex();
    if(index < 1)
    {
        params["state"] = "";
    }
    else
    {
        params["state"] = ui->cb_showState->currentValue().toString();
    }
    params["send_time_begin"] = ui->dte_send_begin->dateTime().toString("yyyy-MM-dd HH-mm-ss");
    params["send_time_end"] = ui->dte_send_end->dateTime().toString("yyyy-MM-dd HH-mm-ss");
    params["parse_time_begin"] = ui->dte_parse_begin->dateTime().toString("yyyy-MM-dd HH-mm-ss");
    params["parse_time_end"] = ui->dte_parse_end->dateTime().toString("yyyy-MM-dd HH-mm-ss");
    UIHelper::showLoading(this,tr("正在获取数据"));
    ListCsRScheduleTaskRunnable* task = new ListCsRScheduleTaskRunnable(this);
    task->setScheduleDirinfo(params);
    QThreadPool::globalInstance()->start(task);
}

void DirScheduleWidget::loadComboBoxText()
{
    ui->cb_showState->clear();
    QStringList textList;
    textList<< tr("不限") << tr("废弃") << tr("可用") << tr("准备下发") << tr("正在下发") << tr("目标地址为空") << tr("下发错误") << tr("下发成功")
            << tr("下载错误") << tr("下载成功") << tr("执行失败") << tr("执行成功")<< tr("处理任务失败") << tr("处理任务成功") << tr("pause")  ;
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

QString DirScheduleWidget::stateToText(const quint8 state)
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

QIcon DirScheduleWidget::stateToIcon(const quint8 state)
{
    //TODO  缓存中界面不可见 没有图标
    QIcon icon;
    switch (state) {
    case Sche::Task_State::DISCARD:
        icon = QIcon(":/ddmi/schedule/imgs/STATE_DISCARD");
        break;
    case Sche::Task_State::USABLE:
        icon = QIcon(":/ddmi/schedule/imgs/STATE_USABLE");
        break;
    case Sche::Task_State::PRESEND:
        icon = QIcon(":/ddmi/schedule/imgs/STATE_PRESEND");
        break;
    case Sche::Task_State::SENDING:
        icon = QIcon(":/ddmi/schedule/imgs/STATE_SENDING");
        break;
    case Sche::Task_State::ADDRISNULL:
        icon = QIcon(":/ddmi/schedule/imgs/STATE_ADDRISNULL");
        break;
    case Sche::Task_State::SENDERROR:
        icon = QIcon(":/ddmi/schedule/imgs/STATE_SENDERROR");
        break;
    case Sche::Task_State::SENDSUCCESS:
        icon = QIcon(":/ddmi/schedule/imgs/STATE_SENDSUCCESS");
        break;
    case Sche::Task_State::DOWNERROR:
        icon = QIcon(":/ddmi/schedule/imgs/STATE_DOWNERROR");
        break;
    case Sche::Task_State::DOWNSUCCESS:
        icon = QIcon(":/ddmi/schedule/imgs/STATE_DOWNSUCCESS");
        break;
    case Sche::Task_State::EXECERROR:
        icon = QIcon(":/ddmi/schedule/imgs/STATE_EXECERROR");
        break;
    case Sche::Task_State::EXECSUCCESS:
        icon = QIcon(":/ddmi/schedule/imgs/STATE_EXECSUCCESS");
        break;
    case Sche::Task_State::TASKERROR:
        icon = QIcon(":/ddmi/schedule/imgs/STATE_TASKERROR");
        break;
    case Sche::Task_State::TASKSUCCESS:
        icon = QIcon(":/ddmi/schedule/imgs/STATE_TASKSUCCESS");
        break;
    case Sche::Task_State::PAUSE:
        icon = QIcon(":/ddmi/schedule/imgs/STATE_PAUSE");
        break;
    default:
        break;
    }
    return icon;
}

void DirScheduleWidget::on_btn_new_clicked()
{
    UIHelper::OpenInSelf(this,new EditScheduleWidget(this));
}

void DirScheduleWidget::on_foldered()
{
    ui->w_folder->show();
    newBtn->hide();
}

void DirScheduleWidget::on_itemtaskCallback(const qint32 cbMsgId, const QString &msg)
{
    if(cbMsgId != CallbackStatus::Schedule::_0)
    {
        UIHelper::hideLoading(this);
        UIHelper::ShowMessageBoxError(msg);
        return;
    }
    loadDates();
}

void DirScheduleWidget::showEvent(QShowEvent *event)
{
    loadDates();
}

void DirScheduleWidget::on_btn_select_clicked()
{
    UIHelper::showLoading(this,tr("正在获取数据"));
    loadDates();
}

void DirScheduleWidget::on_cb_setState_currentIndexChanged(int index)
{
    if(index < 1)
    {
        return;
    }
    if(selectedTaskUuids.isEmpty())
    {
        UIHelper::ShowMessageBoxError(tr("Please select a message"));
        return;
    }
    QList<CsRScheduleTask> taskList;
    for(QList<CsRScheduleTask>::iterator item = curTaskList.begin(); item != curTaskList.end(); ++item)
    {
        if(selectedTaskUuids.contains(item->getUuid()))
        {
            CsRScheduleTask task = *item;
            task.setState((quint8)ui->cb_setState->itemTextValue(index).toInt());
            taskList.append(task);
        }
    }
    UIHelper::showLoading(this,tr("正在修改"));
    UpdateScheduleTaskRunnable* taskUpdate = new UpdateScheduleTaskRunnable(this);
    taskUpdate->setTaskList(taskList);
    QThreadPool::globalInstance()->start(taskUpdate);
}

void DirScheduleWidget::on_btn_send_clicked()
{
    if(selectedTaskUuids.isEmpty())
    {
        UIHelper::ShowMessageBoxError(tr("Please select a message"));
        return;
    }
    QList<CsRScheduleTask> taskList;
    for(QList<CsRScheduleTask>::iterator item = curTaskList.begin(); item != curTaskList.end(); ++item)
    {
        if(selectedTaskUuids.contains(item->getUuid()))
        {
            CsRScheduleTask task = *item;
            // 修改状态为可用
            task.setState(0x1);
            // 设置下发时间为当前时间
            QDateTime dateTime = QDateTime::currentDateTime();
            QString str = dateTime.toString("yyyy-MM-dd HH:mm:ss");
            task.setSendTime(str);
            taskList.append(task);
        }
    }
    UIHelper::showLoading(this,tr("正在下发"));
    UpdateScheduleTaskRunnable* taskUpdate = new UpdateScheduleTaskRunnable(this);
    taskUpdate->setTaskList(taskList);
    QThreadPool::globalInstance()->start(taskUpdate);
}

void DirScheduleWidget::on_btn_pause_clicked()
{
    if(selectedTaskUuids.isEmpty())
    {
        UIHelper::ShowMessageBoxError(tr("Please select a message"));
        return;
    }
    QList<CsRScheduleTask> taskList;
    for(QList<CsRScheduleTask>::iterator item = curTaskList.begin(); item != curTaskList.end(); ++item)
    {
        if(selectedTaskUuids.contains(item->getUuid()))
        {
            CsRScheduleTask task = *item;
            // 修改状态为暂停
            task.setState(0xD);
            taskList.append(task);
        }
    }
    UIHelper::showLoading(this,tr("正在暂停"));
    UpdateScheduleTaskRunnable* taskUpdate = new UpdateScheduleTaskRunnable(this);
    taskUpdate->setTaskList(taskList);
    QThreadPool::globalInstance()->start(taskUpdate);
}

void DirScheduleWidget::on_btn_open_clicked()
{
    if(selectedTaskUuids.isEmpty()) {
        UIHelper::ShowMessageBoxError(tr("Please select a Message"));
        return;
    }
    EditScheduleWidget* edit = new EditScheduleWidget(this);
    QString uuid = selectedTaskUuids.at(0);
    edit->setTaskUuid(uuid);
    UIHelper::OpenInSelf(this,edit);
}

void DirScheduleWidget::on_btn_del_clicked()
{
    int ok = UIHelper::ShowMessageBoxQuesion(tr("你确定要删除记录吗?"));
    if(!ok) {
        return;
    }
    UIHelper::showLoading(this,tr("正在删除"));
    DelScheduleTaskRunnable* task = new DelScheduleTaskRunnable(this);
    task->setTaskUuid(selectedTaskUuids);
    QThreadPool::globalInstance()->start(task);
}

void DirScheduleWidget::on_btn_folder_clicked()
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
