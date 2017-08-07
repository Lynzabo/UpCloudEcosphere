#include "selectdictwidget.h"
#include "ui_selectdictwidget.h"
#include "modules/common/uihelper.h"
#include "modules/common/loading.h"
#include <QDateTime>
using namespace RemoteUIEnvironment::CallbackStatus;
SelectDictWidget::SelectDictWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SelectDictWidget)
{
    ui->setupUi(this);
    m_parent = parent;

    initDatas();

    initWindow();
}

SelectDictWidget::~SelectDictWidget()
{
    delete ui;
}

QString SelectDictWidget::getDictParentName(const CsDict &dict)
{
    if(dict.getSupUuid() == m_uuid) {
        QString name = ui->lab_cur_pos->text();
        return name;
    }
    foreach(const CsDict &temDict,m_dictList) {
        if(dict.getSupUuid() == temDict.getUuid()) {
            QString name = temDict.getName();
            return name;
        }
    }
    return "";
}

void SelectDictWidget::on_itemClicked(const QString &uuid,const QString &name)
{
    ui->lab_cur_pos->setText(name);
    m_uuid = uuid;
    UIHelper::showLoading(this,tr("正在进行查询"));
    ListDictRunnable* dict =  new ListDictRunnable(this);
    QVariantMap params;
    params.insert("supUuid",uuid);
    //设置查询参数
    dict->setSelectCondition(params);
    //设置分页信息
    dict->setFilterPage(this->m_page);
    //设置只查找二级信息
    dict->setRecursion(false);
    QThreadPool::globalInstance()->start(dict);
}

void SelectDictWidget::on_tableBodySelectedRow(int selectedRow)
{
    selectedUuids.clear();
    m_selctedRows.clear();
    m_selctedRows.append(selectedRow);
    selectedUuids.append(m_dictList.at(selectedRow).getUuid());
}

void SelectDictWidget::on_tableBodySelectedRows(QList<int> selectedRows)
{
    selectedUuids.clear();
    m_selctedRows.clear();
    m_selctedRows.append(selectedRows);
    foreach(const int &row,selectedRows) {
        selectedUuids.append(m_dictList.at(row).getUuid());
    }
}
void SelectDictWidget::on_tableBodyDoubleSelected(int selectedRow)
{
    selectedUuids.clear();
    m_selctedRows.clear();
    m_selctedRows.append(selectedRow);
    selectedUuids.append(m_dictList.at(selectedRow).getUuid());
}

void SelectDictWidget::on_tableBodySelectedNull()
{
    selectedUuids.clear();
    m_selctedRows.clear();
}

void SelectDictWidget::on_pageTableAccept(const Page *page)
{
    *m_page = *page;
    on_btn_select_clicked();
}

void SelectDictWidget::on_foldered()
{
    ui->w_folder->show();
    newBtn->hide();
}

void SelectDictWidget::on_itemtaskCallback(const qint32 msgId, const QString &msg)
{
    if(msgId != Basal::_0 ) {
        UIHelper::hideLoading(this);
        UIHelper::ShowMessageBoxError(msg);
        return;
    }
    if(msg == "删除成功") {
        emit evt_delDicts(selectedUuids);
    }
    //添加不在重载，界面直接更新
    //    else if(msg == "添加成功") {
    //        emit evt_reload();
    //        QDateTime dateTime = QDateTime::currentDateTime();
    //        ui->dte_insert_time_end->setDateTime(dateTime);
    //    }
    else if(msg == "修改成功"){
        emit evt_reload();
    }
    on_btn_select_clicked();
}

void SelectDictWidget::on_itemtaskCallback(const qint32 msgId, const QString &msg, CsDict dict)
{
    if(msgId != Basal::_0 ) {
        UIHelper::hideLoading(this);
        UIHelper::ShowMessageBoxError(msg);
        return;
    }
    evt_addDict(dict);
    on_btn_select_clicked();
    UIHelper::hideLoading(this);
}

void SelectDictWidget::on_itemtaskCallback(const qint32 msgId, const QString &msg, const QList<CsDict> &dictList)
{
    if(msgId != Basal::_0 ) {
        UIHelper::hideLoading(this);
        UIHelper::ShowMessageBoxError(msg);
        return;
    }
    ui->tw_content->setPage(m_page);
    m_dictList = dictList;
    ui->tw_content->table_body->setRowCount(m_dictList.size());
    for(int i = 0;i < m_dictList.size(); ++i)
    {
        CsDict dict = m_dictList.at(i);
        QTableWidgetItem* item1 = new QTableWidgetItem;
        // TODO 图标函数需要添加
        //        item1->setIcon(stateToIcon(dict.getState()));
        item1->setText(QString("%1").arg(i));
        ui->tw_content->table_body->setItem(i,TableHeaderElement::INDEX,item1);

        QTableWidgetItem* item2 = new QTableWidgetItem;
        item2->setText(dict.getCode());
        ui->tw_content->table_body->setItem(i,TableHeaderElement::CODE,item2);

        QTableWidgetItem* item3 = new QTableWidgetItem;
        item3->setText(dict.getName());
        ui->tw_content->table_body->setItem(i,TableHeaderElement::NAME,item3);

        QTableWidgetItem* item4 = new QTableWidgetItem;
        item4->setText(dict.getDescription());
        ui->tw_content->table_body->setItem(i,TableHeaderElement::DESCRIPTION,item4);

        QTableWidgetItem* item5= new QTableWidgetItem;
        item5->setText(dict.getState() == 1?tr("可用"):tr("unUse"));
        ui->tw_content->table_body->setItem(i,TableHeaderElement::STATE,item5);

        QTableWidgetItem* item6 = new QTableWidgetItem;
        item6->setText(QString::number(dict.getSequence()));
        ui->tw_content->table_body->setItem(i,TableHeaderElement::SEQUENCE,item6);

        QTableWidgetItem* item7 = new QTableWidgetItem;
        item7->setText(dict.getInsertTime());
        ui->tw_content->table_body->setItem(i,TableHeaderElement::INSERT_TIME,item7);

        QTableWidgetItem* item8 = new QTableWidgetItem;
        item8->setText(dict.getInsertor());
        ui->tw_content->table_body->setItem(i,TableHeaderElement::INSERTER,item8);
    }
    UIHelper::hideLoading(this);
}

void SelectDictWidget::initWindow()
{

    ui->lab_cur_pos->clear();
    ui->cb_set_state->setCurrentIndex(0);
    ui->cb_state->setCurrentIndex(0);

    QDateTime date = QDateTime::currentDateTime();
    ui->dte_insert_time_end->setDateTime(date);
    ui->btn_folder->setIcon(QIcon(":/ddmi/unstruct/imgs/unexpand"));
    //任务列表
    //设置分页导航条可用
    ui->tw_content->setPageNavatorUsable(true);
    //设置表头
    //设置表头列数量
    ui->tw_content->table_body->horizontalHeader()->setVisible(true);
    ui->tw_content->table_body->setColumnCount(8);
    //设置表头每列标签
    ui->tw_content->table_body->setHeaderColumnLabel(SelectDictWidget::INDEX,tr("序号","table_body"));
    ui->tw_content->table_body->setHeaderColumnLabel(SelectDictWidget::CODE,tr("字典编码","table_body"));
    ui->tw_content->table_body->setHeaderColumnLabel(SelectDictWidget::NAME,tr("字典名称","table_body"));
    ui->tw_content->table_body->setHeaderColumnLabel(SelectDictWidget::DESCRIPTION,tr("字典描述","table_body"));
    ui->tw_content->table_body->setHeaderColumnLabel(SelectDictWidget::STATE,tr("codeState","table_body"));
    ui->tw_content->table_body->setHeaderColumnLabel(SelectDictWidget::SEQUENCE,tr("字典顺序","table_body"));
    ui->tw_content->table_body->setHeaderColumnLabel(SelectDictWidget::INSERT_TIME,tr("添加时间","table_body"));
    ui->tw_content->table_body->setHeaderColumnLabel(SelectDictWidget::INSERTER,tr("insertor","table_body"));
    //设置表头每列宽比

    ui->tw_content->table_body->setHeaderColumnWidth(SelectDictWidget::INDEX,0.05);
    ui->tw_content->table_body->setHeaderColumnWidth(SelectDictWidget::CODE,0.15);
    ui->tw_content->table_body->setHeaderColumnWidth(SelectDictWidget::NAME,0.15);
    ui->tw_content->table_body->setHeaderColumnWidth(SelectDictWidget::DESCRIPTION,0.15);
    ui->tw_content->table_body->setHeaderColumnWidth(SelectDictWidget::STATE,0.15);
    ui->tw_content->table_body->setHeaderColumnWidth(SelectDictWidget::SEQUENCE,0.1);
    ui->tw_content->table_body->setHeaderColumnWidth(SelectDictWidget::INSERT_TIME,0.15);
    ui->tw_content->table_body->setHeaderColumnWidth(SelectDictWidget::INSERTER,0.1);
    //设置表头每列对齐方式
    ui->tw_content->table_body->setHeaderColumnAlignment(SelectDictWidget::INDEX,Qt::AlignRight | Qt::AlignCenter);
    //设置表头可排序列,默认为都不可排序
    //参数2的值是分页getOrderFieldName的值,使用该值做排序,因此命名名成数据库字段名,大小写保持与SQL语句一致
    ui->tw_content->table_body->setHeaderColumnCanSort(SelectDictWidget::CODE,QString("CODE"));
    ui->tw_content->table_body->setHeaderColumnCanSort(SelectDictWidget::NAME,QString("NAME"));
    ui->tw_content->table_body->setHeaderColumnCanSort(SelectDictWidget::DESCRIPTION,QString("DESCRIPTION"));
    ui->tw_content->table_body->setHeaderColumnCanSort(SelectDictWidget::STATE,QString("STATE"));
    ui->tw_content->table_body->setHeaderColumnCanSort(SelectDictWidget::SEQUENCE,QString("SEQUENCE"));
    ui->tw_content->table_body->setHeaderColumnCanSort(SelectDictWidget::INSERT_TIME,QString("INSERT_TIME"));
    ui->tw_content->table_body->setHeaderColumnCanSort(SelectDictWidget::INSERTER,QString("INSERTOR"));
    //关联表格相关信号      一个线程,默认的是用direct，检查一下该用&
    //广播选中表格体1行
    connect(ui->tw_content,&PageTableWidget::evt_tableBodySelectedRow,this,&SelectDictWidget::on_tableBodySelectedRow);
    //广播选中多行
    connect(ui->tw_content,&PageTableWidget::evt_tableBodySelectedRows,this,&SelectDictWidget::on_tableBodySelectedRows);
    //广播双击1行
    connect(ui->tw_content,&PageTableWidget::evt_tableBodyDoubleSelected,this,&SelectDictWidget::on_tableBodyDoubleSelected);
    //广播选中空白区域
    connect(ui->tw_content,&PageTableWidget::evt_tableBodySelectedNull,this,&SelectDictWidget::on_tableBodySelectedNull);
    //广播表格
    connect(ui->tw_content,&PageTableWidget::evt_pageTableAccept,this,&SelectDictWidget::on_pageTableAccept);

    //加载下拉框
    loadComboBoxText();
}

void SelectDictWidget::initDatas()
{
    m_uuid.clear();
    m_dictList.clear();
    selectedUuids.clear();
    m_selctedRows.clear();
    m_folder = true;
    ui->btn_folder->setIcon(QIcon(":ddmi/unstruct/imgs/unexpand"));

    newBtn = new QPushButton(this);
    newBtn->setStyleSheet("background-color: rgb(255, 255, 255,100);");
    newBtn->setIcon(QIcon(":/ddmi/unstruct/imgs/expand"));
    connect(newBtn,SIGNAL(clicked(bool)),this,SLOT(on_foldered()));
    newBtn->hide();

    m_page = new Page;
}

void SelectDictWidget::loadComboBoxText()
{
    QStringList text;
    text  << tr("不限") << tr("可用") << tr("unUsed");
    QStringList value;
    value  << "" << "1" << "2";
    ui->cb_state->setShowInfo(text,value);
    text.removeFirst();
    text.insert(0,tr("setTaskState"));
    ui->cb_set_state->setShowInfo(text,value);
}

void SelectDictWidget::on_btn_select_clicked()
{
    UIHelper::showLoading(this,tr("正在查询"));
    ListDictRunnable* dict = new ListDictRunnable(this);
    QVariantMap params;
    QString code = "%" + ui->l_code->text().trimmed();
    params.insert("code",code.append("%"));
    QString name = "%" + ui->l_name->text().trimmed();
    params.insert("name",name.append("%"));
    QString description = "%" + ui->l_decription->text().trimmed();
    params.insert("description",description.append("%"));
    params.insert("state",(quint8)ui->cb_state->currentValue().toInt());
    params.insert("insertTimeBegin",ui->dte_insert_time_begin->text().trimmed());
    params.insert("insertTimeEnd",ui->dte_insert_time_end->text().trimmed());
    params.insert("supUuid",m_uuid);
    //设置查询参数
    dict->setSelectCondition(params);
    //设置分页参数
    dict->setFilterPage(m_page);
    QThreadPool::globalInstance()->start(dict);
}

void SelectDictWidget::on_btn_new_clicked()
{
    AddDictWidget* newDict = new AddDictWidget;
    QList<qint32> sequenceList;sequenceList.clear();
    for(int i = 0;i < ui->tw_content->table_body->rowCount(); ++i) {
        QTableWidgetItem* item =  ui->tw_content->table_body->item(i,SEQUENCE);
        qint32 sequence  =  (qint32)item->text().toInt();
        sequenceList.append(sequence);
    }
    connect(newDict,SIGNAL(evt_ok(bool)),this,SLOT(on_addWidgetOkForNew(bool)));
    newDict->show();
    newDict->setDictInfo(ui->lab_cur_pos->text(),&m_dict,sequenceList,false);
}

void SelectDictWidget::on_btn_del_clicked()
{
    int ok = UIHelper::ShowMessageBoxQuesion(tr("你确定要删除记录吗?"));
    if(!ok) {
        return;
    }
    UIHelper::showLoading(this,tr("正在删除"));
    DelDictRunnable* dict = new DelDictRunnable(this);
    dict->setDictList(selectedUuids);
    QThreadPool::globalInstance()->start(dict);
}

void SelectDictWidget::on_cb_set_state_currentIndexChanged(int index)
{
    UpdateDictRunnable* dict = new UpdateDictRunnable(this);
    if(m_selctedRows.isEmpty()) {
        return;
    }
    QList<CsDict> dictList;
    quint8 state = (quint8)ui->cb_set_state->itemTextValue(index).toInt();
    foreach(const int row,m_selctedRows)
    {
        CsDict temDict = m_dictList.at(row);
        temDict.setState(state);
        dictList.append(temDict);
    }
    dict->setUpdateList(dictList);
    QThreadPool::globalInstance()->start(dict);
}

void SelectDictWidget::on_addWidgetOkForNew(bool flg)
{
    AddDictRunable* dict = new AddDictRunable(this);
    m_dict.setSupUuid(m_uuid);
    dict->setDictInfo(m_dict);
    QThreadPool::globalInstance()->start(dict);
}

void SelectDictWidget::on_addWidgetOkForOpen(bool flg)
{
    UpdateDictRunnable* dict = new UpdateDictRunnable(this);
    QList<CsDict> dictList;
    dictList.append(m_dict);
    CsDict dictExChange;
    //是否要交换
    if(flg) {
        for(int i = 0; i < m_dictList.size(); ++i) {
            CsDict dict = m_dictList.at(i);
            if(m_dict.getSequence() == dict.getSequence()) {
                dictExChange = dict;
            }
        }
        dictExChange.setSequence(sequenceOld);
        dictList.append(dictExChange);
    }
    dict->setUpdateList(dictList);
    QThreadPool::globalInstance()->start(dict);
}



void SelectDictWidget::on_btn_open_clicked()
{
    if(m_selctedRows.isEmpty()) {
        UIHelper::ShowMessageBoxError(tr("Please select a message"));
        return;
    }
    AddDictWidget* newDict = new AddDictWidget;
    m_dict = m_dictList.at(m_selctedRows.at(0));
    sequenceOld = m_dict.getSequence();
    QString name = getDictParentName(m_dict);
    QList<qint32> sequenceList;sequenceList.clear();
    for(int i = 0;i < ui->tw_content->table_body->rowCount(); ++i) {
        QTableWidgetItem* item =  ui->tw_content->table_body->item(i,SEQUENCE);
        qint32 sequence  =  (qint32)item->text().toInt();
        if(sequence == sequenceOld) {
            continue;
        }
        sequenceList.append(sequence);
    }
    newDict->setDictInfo(name,&m_dict,sequenceList,true);
    connect(newDict,SIGNAL(evt_ok(bool)),this,SLOT(on_addWidgetOkForOpen(bool)));
    newDict->show();
}


void SelectDictWidget::on_btn_folder_clicked()
{
    oldPos = ui->btn_folder->pos();
    newPos = ui->lab_position->pos();
    newPos.setX(oldPos.x());
    newPos.setY(newPos.y() + 8);
    newBtn->move(newPos);
    newBtn->resize(ui->btn_folder->size());

    ui->w_folder->hide();
    newBtn->show();

}
