#include "dirnodefilewidget.h"
#include "ui_dirnodefilewidget.h"
#include "../FrontBusinessIRemoteUI/DDMIRemoteUI/UnstructOperaIRemoteUI/unstructoperairemoteui.h"
#include "../FrontBusinessIRemoteUI/DDMIRemoteUI/StructOperaIRemoteUI/structoperairemoteui.h"
#include "baseiremote.h"
#include "modules/common/uihelper.h"
using namespace RemoteUIEnvironment;
using namespace Environment::Task_Status::Center;
DirNodeFileWidget::DirNodeFileWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DirNodeFileWidget)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_ShowModal,true);
    initWindow();
}

DirNodeFileWidget::~DirNodeFileWidget()
{
    delete ui;
}

void DirNodeFileWidget::loadDatas(const QList<CsRUnstructSendStatus> statusList, const QStringList &fileNameList, const QStringList &nodeNameList)
{
    m_unstruct_List = statusList;
    ui->tw_content->setRowCount(m_unstruct_List.size());
    for(int i = 0;i < ui->tw_content->rowCount(); ++i) {

        CsRUnstructSendStatus status = m_unstruct_List.at(i);

        QTableWidgetItem* item1 = new QTableWidgetItem;
        item1->setIcon(stateToIconForUnstruct(status.getState()));
        item1->setText(QString::number(i));
        ui->tw_content->setItem(i,TableHeaderElement::INDEX,item1);

        QTableWidgetItem* item2 = new QTableWidgetItem;
        item2->setText(status.getClientUuid());
        ui->tw_content->setItem(i,TableHeaderElement::CLIENT_UUID,item2);

        QTableWidgetItem* item3 = new QTableWidgetItem;
        if(nodeNameList.size() != m_unstruct_List.size()) {
            item3->setText(nodeNameList.at(0));
        }
        else {
            item3->setText(nodeNameList.at(i));
        }
        ui->tw_content->setItem(i,TableHeaderElement::NODE_NAME,item3);


        QTableWidgetItem* item4 = new QTableWidgetItem;
        if(fileNameList.size() != m_unstruct_List.size()) {
            item4->setText(fileNameList.at(0));
        }
        else {
            item4->setText(fileNameList.at(i));
        }
        ui->tw_content->setItem(i,TableHeaderElement::FILE_NAME,item4);

        QTableWidgetItem* item5 = new QTableWidgetItem;
        item5->setText(stateToTextForUnstruct(status.getState()));
        ui->tw_content->setItem(i,TableHeaderElement::STATE,item5);

    }
    operaType = NodeFileOperaTyple::UNSTRUCT;
}

void DirNodeFileWidget::loadDatas(const QList<CsRStructSendStatus> statusList, const QStringList &fileNameList, const QStringList &nodeNameList)
{
    m_struct_list = statusList;
    ui->tw_content->setRowCount(m_struct_list.size());
    for(int i = 0;i < ui->tw_content->rowCount(); ++i) {

        CsRStructSendStatus status = m_struct_list.at(i);

        QTableWidgetItem* item1 = new QTableWidgetItem;
        item1->setIcon(stateToIconForStruct(status.getState()));
        item1->setText(QString::number(i));
        ui->tw_content->setItem(i,TableHeaderElement::INDEX,item1);

        QTableWidgetItem* item2 = new QTableWidgetItem;
        item2->setText(status.getClientUuid());
        ui->tw_content->setItem(i,TableHeaderElement::CLIENT_UUID,item2);

        QTableWidgetItem* item3 = new QTableWidgetItem;
        if(nodeNameList.size() != m_struct_list.size()) {
            item3->setText(nodeNameList.at(0));
        }
        else {
            item3->setText(nodeNameList.at(i));
        }
        ui->tw_content->setItem(i,TableHeaderElement::NODE_NAME,item3);


        QTableWidgetItem* item4 = new QTableWidgetItem;
        if(fileNameList.size() != m_struct_list.size()) {
            item4->setText(fileNameList.at(0));
        }
        else {
            item4->setText(fileNameList.at(i));
        }
        ui->tw_content->setItem(i,TableHeaderElement::FILE_NAME,item4);

        QTableWidgetItem* item5 = new QTableWidgetItem;
        item5->setText(stateToTextForStruct(status.getState()));
        ui->tw_content->setItem(i,TableHeaderElement::STATE,item5);

    }
    operaType = NodeFileOperaTyple::STRUCT;
}

void DirNodeFileWidget::loadDatas(const QList<CsRScheduleSendStatus> statusList, const QStringList &fileNameList, const QStringList &nodeNameList)
{
    operaType = NodeFileOperaTyple::SCHEDULE;
}

void DirNodeFileWidget::on_itemtaskCallback(const qint32 msgId, const QString &msg)
{
    if(msgId == CallbackStatus::Unstruct::_0) {
        updateState();
    }
    else if(msgId == CallbackStatus::Struct::_0) {
        updateState();
    }
    else if(msgId == CallbackStatus::Schedule::_0) {
        updateState();
    }
    else {
        UIHelper::hideLoading(this);
        UIHelper::ShowMessageBoxError(msg);

    }
}

void DirNodeFileWidget::on_selectedRow(int selectedRow)
{
    selectedUUids.clear();
    rowNum.clear();
    rowNum.append(selectedRow);
    switch(operaType) {
    case NodeFileOperaTyple::UNSTRUCT:
    {
        CsRUnstructSendStatus status = m_unstruct_List.at(selectedRow);
        QString uuid = status.getUuid();
        selectedUUids.append(uuid);
    }
        break;
    case NodeFileOperaTyple::STRUCT:
    {
        CsRStructSendStatus status = m_struct_list.at(selectedRow);
        QString uuid = status.getUuid();
        selectedUUids.append(uuid);
    }
        break;
    case NodeFileOperaTyple::SCHEDULE:
    {
        CsRScheduleSendStatus status = m_schedule_list.at(selectedRow);
        QString uuid = status.getUuid();
        selectedUUids.append(uuid);
    }
        break;
    default:
        break;
    }
}

void DirNodeFileWidget::on_selectedRows(QList<int> selectedRows)
{
    selectedUUids.clear();
    rowNum.clear();
    rowNum.append(selectedRows);
    switch(operaType) {
    case NodeFileOperaTyple::UNSTRUCT:
    {
        foreach(const int selectedRow,selectedRows) {
            CsRUnstructSendStatus status = m_unstruct_List.at(selectedRow);
            QString uuid = status.getUuid();
            selectedUUids.append(uuid);
        }
    }
        break;
    case NodeFileOperaTyple::STRUCT:
    {
        foreach(const int selectedRow,selectedRows) {
            CsRStructSendStatus status = m_struct_list.at(selectedRow);
            QString uuid = status.getUuid();
            selectedUUids.append(uuid);
        }
    }
        break;
    case NodeFileOperaTyple::SCHEDULE:
    {
        foreach(const int selectedRow,selectedRows) {
            CsRScheduleSendStatus status = m_schedule_list.at(selectedRow);
            QString uuid = status.getUuid();
            selectedUUids.append(uuid);
        }
    }
        break;
    default:
        break;
    }
}


void DirNodeFileWidget::on_doubleSelected(int selectedRow)
{
    selectedUUids.clear();
    rowNum.clear();
    rowNum.append(selectedRow);
    switch(operaType) {
    case NodeFileOperaTyple::UNSTRUCT:
    {
        CsRUnstructSendStatus status = m_unstruct_List.at(selectedRow);
        QString uuid = status.getUuid();
        selectedUUids.append(uuid);
    }
        break;
    case NodeFileOperaTyple::STRUCT:
    {
        CsRStructSendStatus status = m_struct_list.at(selectedRow);
        QString uuid = status.getUuid();
        selectedUUids.append(uuid);
    }
        break;
    case NodeFileOperaTyple::SCHEDULE:
    {
        CsRScheduleSendStatus status = m_schedule_list.at(selectedRow);
        QString uuid = status.getUuid();
        selectedUUids.append(uuid);
    }
        break;
    default:
        break;
    }
}

void DirNodeFileWidget::on_btn_send_clicked()
{
    if(operaType == NodeFileOperaTyple::UNSTRUCT) {
        UIHelper::showLoading(this,tr("正在下发"));
        UpdateUnstructSendStatusRunnable* status = new UpdateUnstructSendStatusRunnable(this);
        status->setUpdateState(selectedUUids,m_unstruct_List.at(0).getTaskUuid(),Unstru::SendStatus_State::USABLE);
        QThreadPool::globalInstance()->start(status);
    }
    else if(operaType == NodeFileOperaTyple::STRUCT) {
        UIHelper::showLoading(this,tr("正在下发"));
        UpdateStructSendStatusRunnable* status = new UpdateStructSendStatusRunnable(this);
        status->setUpdateState(selectedUUids,m_struct_list.at(0).getTaskUuid(),Stru::SendStatus_State::USABLE);
        QThreadPool::globalInstance()->start(status);
    }
    else if(operaType == NodeFileOperaTyple::SCHEDULE){

    }
    else {

    }
}

void DirNodeFileWidget::on_btn_quit_clicked()
{
    this->deleteLater();
}

void DirNodeFileWidget::initWindow()
{
    //广播选中1行
    connect(ui->tw_content,&TableWidget::evt_selectedRow,this,&DirNodeFileWidget::on_selectedRow);
    //广播选中多行
    connect(ui->tw_content,&TableWidget::evt_selectedRows,this,&DirNodeFileWidget::on_selectedRows);
    //广播双击1行
    connect(ui->tw_content,&TableWidget::evt_doubleSelected,this,&DirNodeFileWidget::on_doubleSelected);
    ui->tw_content->setHeaderColumnWidth(DirNodeFileWidget::INDEX,  15.0/100);
    ui->tw_content->setHeaderColumnWidth(DirNodeFileWidget::CLIENT_UUID,30.0/100);
    ui->tw_content->setHeaderColumnWidth(DirNodeFileWidget::NODE_NAME,20.0/100);
    ui->tw_content->setHeaderColumnWidth(DirNodeFileWidget::FILE_NAME,20.0/100);
    ui->tw_content->setHeaderColumnWidth(DirNodeFileWidget::STATE,15.0/100);
}

void DirNodeFileWidget::updateState()
{
    if(operaType == NodeFileOperaTyple::UNSTRUCT) {
        for(QList<CsRUnstructSendStatus>::iterator item = m_unstruct_List.begin();
            item != m_unstruct_List.end(); ++item)
        {
            QString uuid = (*item).getUuid();
            if(selectedUUids.contains(uuid)) {
                (*item).setState(Unstru::SendStatus_State::USABLE);
            }
        }
        foreach(const int row,rowNum) {
            QTableWidgetItem *item =  ui->tw_content->item(row, DirNodeFileWidget::STATE);
            item->setText(stateToTextForUnstruct( Unstru::SendStatus_State::USABLE));
        }
    }
    else if(operaType == NodeFileOperaTyple::STRUCT) {
        for(QList<CsRStructSendStatus>::iterator item = m_struct_list.begin();
            item != m_struct_list.end(); ++item)
        {
            QString uuid = (*item).getUuid();
            if(selectedUUids.contains(uuid)) {
                (*item).setState(Stru::SendStatus_State::USABLE);
            }
        }
        foreach(const int row,rowNum) {
            QTableWidgetItem *item =  ui->tw_content->item(row, DirNodeFileWidget::STATE);
            item->setText(stateToTextForUnstruct( Stru::SendStatus_State::USABLE));
        }
    }
    else if(operaType == NodeFileOperaTyple::SCHEDULE) {

    }
    UIHelper::hideLoading(this);
    evt_send();
}

QIcon DirNodeFileWidget::stateToIconForUnstruct(const quint8 state)
{
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

QString DirNodeFileWidget::stateToTextForUnstruct(const quint8 state)
{
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

QIcon DirNodeFileWidget::stateToIconForStruct(const quint8 state)
{
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

QString DirNodeFileWidget::stateToTextForStruct(const quint8 state)
{
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
