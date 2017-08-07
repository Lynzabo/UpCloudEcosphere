#include "dirnodeserverwidget.h"
#include "ui_dirnodeserverwidget.h"
#include "baseiremote.h"
#include "modules/common/loading.h"
#include "modules/common/uihelper.h"
using namespace RemoteUIEnvironment;
DirNodeServerWidget::DirNodeServerWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DirNodeServerWidget)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowMinMaxButtonsHint);
    initWindow();

}

DirNodeServerWidget::~DirNodeServerWidget()
{
    delete ui;
}

void DirNodeServerWidget::loadItem(QListView *view, const QList<CsClientExtendInfo> &exList)
{
    QStandardItemModel* model = new QStandardItemModel;

    for(int i = 0;i < exList.size(); ++i ) {
        CsClientExtendInfo exInfo = exList.at(i);
        QString clientUuid = QString::number(exInfo.getTerminalUUID());
        if(m_newNodeList.contains(clientUuid)) {
            continue;
        }
        QStandardItem* item = new QStandardItem(clientUuid);
        model->appendRow(item);
        m_hashForBean.insert(clientUuid,exInfo);
    }
    view->setModel(model);
}

void DirNodeServerWidget::moveItemToRight()
{
    right_strListModel->setStringList(m_newNodeList);
    right_proxyModel->setSourceModel(right_strListModel);
    ui->lv_addNode->setModel(right_proxyModel);
}

void DirNodeServerWidget::moveItemToLeft()
{
    left_strListModel->setStringList(m_clientList);
    left_proxyModel->setSourceModel(left_strListModel);
    ui->lv_node->setModel(left_proxyModel);

}

void DirNodeServerWidget::setParamsInfo(QStringList *paramsForAdd,QStringList *paramsForDel)
{
    m_paramsForAdd = paramsForAdd;
    m_paramsForDel = paramsForDel;
}

void DirNodeServerWidget::setExistedNodeList(const QStringList &nodeList)
{
    m_oldNodeList = nodeList;
    m_newNodeList.append(m_oldNodeList);
//    for(int i = 0;i < m_newNodeList.size(); ++i ) {
//        QString clientUuid = m_newNodeList.at(i);
//        QStandardItem* item = new QStandardItem(clientUuid);
//        m_model->appendRow(item);
//    }
//    ui->lv_addNode->setModel(m_model);
    right_strListModel->setStringList(m_newNodeList);
    right_proxyModel->setSourceModel(right_strListModel);
    ui->lv_addNode->setModel(right_proxyModel);
}

void DirNodeServerWidget::on_btn_right_move_clicked()
{
    QModelIndexList indexs = ui->lv_node->selectionModel()->selectedIndexes();
    m_checkedList.clear();
    for(int i = indexs.size() -1 ;i > -1; --i) {
        QModelIndex index = indexs.at(i);
        QString client = index.data().toString();
        m_newNodeList.append(client);
        m_clientList.removeOne(client);
    }
    moveItemToRight();
    moveItemToLeft();
//    ui->lv_addNode->setModel(m_model);
}

void DirNodeServerWidget::on_btn_right_moveAll_clicked()
{
   ui->lv_node->selectAll();
   on_btn_right_move_clicked();
}

void DirNodeServerWidget::on_btn_ok_clicked()
{
//    for(int i = 0; i< m_newNodeList.size();++i) {
//        QString client = m_newNodeList.at(i);
//        if(!m_oldNodeList.contains(client)) {
//            (*m_paramsForAdd).append(client);
//        }
//    }
    for(int i = 0; i< m_oldNodeList.size();++i) {
        QString client = m_oldNodeList.at(i);
        if(!m_newNodeList.contains(client)) {
            (*m_paramsForDel).append(client);
        }
    }
    (*m_paramsForAdd).clear();
    (*m_paramsForAdd).append(m_newNodeList);
    emit evt_ok();
    this->deleteLater();
}

void DirNodeServerWidget::on_btn_quit_clicked()
{
    this->deleteLater();
}

void DirNodeServerWidget::on_l_left_find_textChanged(const QString &arg1)
{
//    ListClientExtendInfoRunnable* extend = new  ListClientExtendInfoRunnable(this);
//    extend->setExtendInfo("");
//    QThreadPool::globalInstance()->start(extend);

    QRegExp regExp(arg1,Qt::CaseInsensitive,
                   QRegExp::PatternSyntax::RegExp);
    left_proxyModel->setFilterRegExp(regExp);
}


void DirNodeServerWidget::on_itemtaskCallback(const qint32 msgId, const QString &msg, const QList<CsClientExtendInfo> &exList)
{
    if(msgId != CallbackStatus::Basal::_0) {
        UIHelper::ShowMessageBoxError(msg);
        return;
    }
    m_exList = exList;
    for(int i = m_exList.size() - 1; i  >= 0 ; --i) {
        QString client = QString::number(m_exList.at(i).getTerminalUUID());
        if(!m_newNodeList.contains(client)) {
            m_clientList.append(client);
        }
    }
    left_strListModel->setStringList(m_clientList);
    left_proxyModel->setSourceModel(left_strListModel);
    ui->lv_node->setModel(left_proxyModel);

//    QRegExp regExp(ui->l_left_find->text(),Qt::CaseInsensitive,
//                   QRegExp::PatternSyntax::RegExp);
//    left_proxyModel->setFilterRegExp(regExp);
}

void DirNodeServerWidget::showEvent(QShowEvent *event)
{
    ListClientExtendInfoRunnable* extend = new  ListClientExtendInfoRunnable(this);
    extend->setExtendInfo("");
    QThreadPool::globalInstance()->start(extend);
}

void DirNodeServerWidget::initWindow()
{
    m_newNodeList.clear();
    right_strListModel = new QStringListModel(this);
    right_proxyModel = new QSortFilterProxyModel(this);

    left_strListModel = new QStringListModel(this);
    left_proxyModel = new QSortFilterProxyModel(this);

    this->setAttribute(Qt::WA_ShowModal,true);
    ui->lv_node->setSelectionMode(QAbstractItemView::ExtendedSelection);
}

void DirNodeServerWidget::on_l_right_find_textChanged(const QString &arg1)
{
    QRegExp regExp(arg1,Qt::CaseInsensitive,
                   QRegExp::PatternSyntax::RegExp);
    right_proxyModel->setFilterRegExp(regExp);
}

void DirNodeServerWidget::on_btn_left_move_clicked()
{
   QModelIndexList indexs = ui->lv_addNode->selectionModel()->selectedIndexes();
   for(int i = indexs.size() -1 ; i > -1; --i) {
       QModelIndex index = indexs.at(i);
       QString client = index.data().toString();
       m_clientList.append(client);
       m_newNodeList.removeOne(client);
   }
   moveItemToRight();
   moveItemToLeft();
}

void DirNodeServerWidget::on_btn_left_allMove_clicked()
{
    ui->lv_addNode->selectAll();
    on_btn_left_move_clicked();
}
void DirNodeServerWidget::mouseMoveEvent(QMouseEvent *e)
{
    if (mousePressed && (e->buttons() && Qt::LeftButton)) {
        this->move(e->globalPos() - mousePoint);
        e->accept();
    }
}

void DirNodeServerWidget::mousePressEvent(QMouseEvent *e)
{
    if (e->button() == Qt::LeftButton) {
        mousePressed = true;
        mousePoint = e->globalPos() - this->pos();
        e->accept();
    }
}

void DirNodeServerWidget::mouseReleaseEvent(QMouseEvent *)
{
    mousePressed = false;
}

void DirNodeServerWidget::on_btn_menu_cancel_clicked()
{
     this->deleteLater();
}
