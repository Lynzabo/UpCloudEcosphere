#include "dirnodesgroupwidget.h"
#include <QHBoxLayout>
#include "ui_dirnodesgroupwidget.h"
#include "modules/common/uihelper.h"
#include "modules/common/loading.h"
#include "dirnodeserverwidget.h"
#include "../FrontBusinessIRemoteUI/BasalOperaIRemoteUI/basaloperairemoteui.h"
using namespace RemoteUIEnvironment;
using namespace Environment;
DIRNodesGroupWidget::DIRNodesGroupWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DIRNodesGroupWidget)
{
    ui->setupUi(this);
    initWindow();

}

DIRNodesGroupWidget::~DIRNodesGroupWidget()
{
    delete m_groupTreeShow;
    delete ui;
}

void DIRNodesGroupWidget::setGroup()
{
    UIHelper::showLoading(this,tr("加载群组"));
    ListClientGroupRunnable* group = new ListClientGroupRunnable(this);
    QStringList list;
    list << "-1";
    group->setGroupInfo(list,m_pageNum);
    QThreadPool::globalInstance()->start(group);
}

void DIRNodesGroupWidget::setGroupAssoc()
{
    UIHelper::showLoading(this,tr("加载节点"));
    ListClientGroupAssocRunnable* node = new ListClientGroupAssocRunnable(this);
    node->setGroupAssocUuid("",m_pageNum);
    QThreadPool::globalInstance()->start(node);
}

void DIRNodesGroupWidget::on_moveNode()
{
    if(!m_params.value("y_uuid").isNull())
    {
        return;
    }
    if(m_groupTreeSelect->getCheckList().isEmpty()) {
        return;
    }

    QModelIndex index =  m_groupTreeSelect->getCheckList().at(0);
    QTreeWidgetItem* item = m_groupTreeSelect->getItemfromIndex(index);
    QString y_uuid = m_groupTreeSelect->getUuid(item);
    item = m_groupTreeShow->getItemFromUuid(y_uuid);
    m_groupTreeShow->setParamsY(m_params,item);
    //判断是否是本身 或者不合法移动到自身组内
    if(m_groupTreeShow->isInvalid(m_xItem,item)) {
        m_xItem = 0;
        return;
    }
    if(m_groupTreeShow->isGroup(item)) {
        ////只要目标为群组，直接移动到组内
        //        if(m_xItem->parent() == item->parent()) {
        //            return;
        //        }
        //        else {
        m_groupTreeShow->setNodeParams(m_params,item);
        if(m_xItem->parent() == item)  {
            qint32 sequence = m_params.value("y_sequence").toInt();
            m_params["y_sequence"] = (qint32)( sequence - 1);
        }
        m_params["opera_type"] = 2;
        //        }
    }
    else {
        if(m_xItem->parent() == item->parent()) {
            m_params["opera_type"] = 1;
        }
        else {
            m_params["opera_type"] = 2;
        }
    }
    MoveGroupSequenceRunnable* move = new MoveGroupSequenceRunnable(this);
    move->setMoveInfo(m_params);
    QThreadPool::globalInstance()->start(move);
    m_groupTreeSelect->deleteLater();
    m_params.clear();
}

void DIRNodesGroupWidget::on_setUseNode()
{
    UpdateClientGroupAssocRunnable* groupAssoc = new UpdateClientGroupAssocRunnable(this);
    QVariantMap params;
    params["uuid"] = m_params.value("x_uuid").toString();
    params["state"] = 1;
    groupAssoc->setGroupAssocInfo(params);
    QThreadPool::globalInstance()->start(groupAssoc);
}

void DIRNodesGroupWidget::on_delNode()
{
    int ok = UIHelper::ShowMessageBoxQuesion(tr("你确定要删除记录吗?"));
    if(!ok) {
        return;
    }
    UIHelper::showLoading(this,tr("正在删除"));
    DelClientGroupAssocRunnable* delGroupAssoc = new DelClientGroupAssocRunnable(this);
    delGroupAssoc->setDelCondition(m_params);
    QThreadPool::globalInstance()->start(delGroupAssoc);
}

void DIRNodesGroupWidget::on_addGroup()
{
    AddCsClientGroupRunnable* group = new AddCsClientGroupRunnable(this);
    QVariantMap params;params.clear();
    params["state"] = (quint8)m_params.value("state").toInt();
    params["name"] = m_params.value("name").toString();
    params["description"] = m_params.value("description").toString();
    params["sequence"] = m_groupTreeShow->getChildGroupCount(m_xItem);
    params["supUuid"] = m_params.value("x_uuid").toString();
    group->setGroupInfo(params);
    QThreadPool::globalInstance()->start(group);
}

void DIRNodesGroupWidget::on_editGroup()
{
    UpdateClientGroupRunnable* group = new UpdateClientGroupRunnable(this);
    QVariantMap params;params.clear();
    params["uuid"] = m_params.value("x_uuid").toString();
    params["state"] = (quint8)m_params.value("state").toInt();
    params["name"] = m_params.value("name").toString();
    params["description"] = m_params.value("description").toString();
    params["sequence"] = m_params.value("x_sequence").toString();
    params["supUuid"] = m_params.value("x_groupUuid").toString();
    group->setGroupInfo(params);
    QThreadPool::globalInstance()->start(group);
}

void DIRNodesGroupWidget::on_setUseGroup()
{
    UIHelper::showLoading(this,tr("正在修改"));
    UpdateClientGroupRunnable* group = new UpdateClientGroupRunnable(this);
    CsClientGroup groupInfo = m_groupTreeShow->getGroupByUuid(m_params.value("x_uuid").toString());
    QVariantMap params;
    params["uuid"] = groupInfo.getUuid();
    params["state"] = 1;
    params["name"] = groupInfo.getName();
    params["description"] = groupInfo.getDescription();
    params["sequence"] = groupInfo.getSequence();
    params["supUuid"] = groupInfo.getSupUuid();
    group->setGroupInfo(params);
    QThreadPool::globalInstance()->start(group);

}

void DIRNodesGroupWidget::on_moveGroup()
{
    if(!m_params.value("y_uuid").isNull())
    {
        return;
    }
    if(m_groupTreeSelect->getCheckList().isEmpty()) {
        return;
    }

    QModelIndex index =  m_groupTreeSelect->getCheckList().at(0);
    QTreeWidgetItem* item = m_groupTreeSelect->getItemfromIndex(index);
    QString y_uuid = m_groupTreeSelect->getUuid(item);
    item = m_groupTreeShow->getItemFromUuid(y_uuid);
    m_groupTreeShow->setGroupParams(m_params,item);
    //判断是否是本身 或者不合法移动到自身组内
    if(m_groupTreeShow->isInvalid(m_xItem,item)) {
        m_xItem = 0;
        return;
    }
    if(m_groupTreeShow->isGroup(item)) {
        if(m_xItem->parent() == item)  {
            m_params["y_sequence"] = (qint32)(m_params.value("y_seuquence").toInt() - 1);
        }
        m_params["opera_type"] = 4;

    }
    else {
        return;
    }
    MoveGroupSequenceRunnable* move = new MoveGroupSequenceRunnable(this);

    move->setMoveInfo(m_params);
    QThreadPool::globalInstance()->start(move);
    m_groupTreeSelect->deleteLater();
    m_params.clear();
}

void DIRNodesGroupWidget::on_delGroup()
{

    int ok = UIHelper::ShowMessageBoxQuesion(tr("你确定要删除记录吗?"));
    if(!ok) {
        return;
    }
    UIHelper::showLoading(this,tr("正在删除"));
    DelClientGroupRunnable* delGroup = new DelClientGroupRunnable(this);
    delGroup->setGroupInfo(m_params);
    QThreadPool::globalInstance()->start(delGroup);
}

void DIRNodesGroupWidget::on_addNode()
{
    AddClientGroupAssocRunnable* groupAssoc = new AddClientGroupAssocRunnable(this);
    QVariantMap params;
    params["groupuuid"] = m_params.value("x_uuid");
    //获取从最后的位置添加 但必须计算节点服务器的顺序
    //    int total = m_groupTreeShow->getChildCount(m_xItem);
    //    int count = m_groupTreeShow->getChildGroupCount(m_xItem);
    params["sequence"] = (qint32)(0);
    groupAssoc->setAddCondition(m_paramsForAddNode,params);
    QThreadPool::globalInstance()->start(groupAssoc);
}

void DIRNodesGroupWidget::on_delAllNodes()
{
    UIHelper::showLoading(this,tr("正在删除"));
    DelClientGroupAssocRunnable* delGroupAssoc = new DelClientGroupAssocRunnable(this);
    QString groupUuid = m_params.value("x_groupUuid").toString();
    m_params.insert("delAllForGroup",groupUuid);
    delGroupAssoc->setDelCondition(m_params);
    QThreadPool::globalInstance()->start(delGroupAssoc);
}

void DIRNodesGroupWidget::on_moveNodeForTree()
{
    m_groupTreeSelect = new GroupTree;
    m_groupTreeSelect->setEnableCheckBox(true);
    m_groupTreeSelect->setSignalOnlyOne(true);
    m_groupTreeSelect->setWindowModality(Qt::ApplicationModal);
    m_groupTreeSelect->setNodeList(m_groupTreeShow->getNodeList());
    m_groupTreeSelect->show();
    connect(m_groupTreeSelect,SIGNAL(evt_checkBoxChanged()),m_groupTreeSelect,SLOT(hide()));
    connect(m_groupTreeSelect,SIGNAL(evt_checkBoxChanged()),this,SLOT(on_moveNode()));

}

void DIRNodesGroupWidget::on_moveGroupForTree()
{
    m_groupTreeSelect = new GroupTree;
    m_groupTreeSelect->setEnableCheckBox(true);
    m_groupTreeSelect->setSignalOnlyOne(true);
    m_groupTreeSelect->setWindowModality(Qt::ApplicationModal);
    m_groupTreeSelect->setNodeList(m_groupTreeShow->getNodeList());
    m_groupTreeSelect->show();
    connect(m_groupTreeSelect,SIGNAL(evt_checkBoxChanged()),m_groupTreeSelect,SLOT(hide()));
    connect(m_groupTreeSelect,SIGNAL(evt_checkBoxChanged()),this,SLOT(on_moveGroup()));
}

void DIRNodesGroupWidget::on_editGroupForTree()
{
    //无需释放资源 已封装
    EditGroupWidget* edit = new EditGroupWidget;
    edit->getParams(&m_params);
    CsClientGroup groupInfo = m_groupTreeShow->getGroupByUuid(m_params.value("x_uuid").toString());
    edit->setShowGroupInfo(groupInfo);
    connect(edit,SIGNAL(evt_saveInfo()),this,SLOT(on_editGroup()));
    edit->show();
}

void DIRNodesGroupWidget::on__addGroupForTree()
{
    //无需释放资源 已封装
    EditGroupWidget* edit = new EditGroupWidget;
    edit->getParams(&m_params);
    CsClientGroup groupInfo = m_groupTreeShow->getGroupByUuid(m_params.value("x_uuid").toString());
    groupInfo.setSupUuid(m_params.value("x_uuid").toString());
    groupInfo.setName("");
    groupInfo.setDescription("");
    groupInfo.setState(1);
    edit->setShowGroupInfo(groupInfo);
    connect(edit,SIGNAL(evt_saveInfo()),this,SLOT(on_addGroup()));
    edit->show();
}

void DIRNodesGroupWidget::on_addNodeForTree()
{
    DirNodeServerWidget* dirNode = new DirNodeServerWidget;
    //获取要添加的参数列表
    dirNode->setParamsInfo(&m_paramsForAddNode,&m_paramsForDelNode);
    //展示现有的服务节点信息
    QStringList uuids = m_groupTreeShow->getChildNode(m_xItem);
    dirNode->setExistedNodeList(uuids);
    connect(dirNode,SIGNAL(evt_ok()),this,SLOT(on_addNode()));
    dirNode->show();
}

void DIRNodesGroupWidget::on_showMenu(QTreeWidgetItem *item, int column)
{
    if(qApp->mouseButtons() == Qt::LeftButton) {
        return;
    }

    m_params.clear();

    if(m_groupTreeShow->isGroup(item)) {
        m_groupTreeShow->showGroupMenu();
        m_groupTreeShow->setparamsX(m_params,item);
        m_groupType = Group_GROUP;
    }
    else {
        m_groupTreeShow->showNodeMenu();
        m_groupTreeShow->setparamsX(m_params,item);
        m_groupType = Group_NODE;
    }
    m_xItem = item;
}

void DIRNodesGroupWidget::on_moveXToY(const QTreeWidgetItem *x, const QTreeWidgetItem *y)
{
    QTreeWidgetItem* itemX = const_cast<QTreeWidgetItem*>(x) ;
    QTreeWidgetItem* itemY  = const_cast<QTreeWidgetItem*>(y);

    if(m_groupTreeShow->isGroup(itemX)) {
        m_groupTreeShow->setGroupParams(m_params,itemY);
        m_groupTreeShow->setparamsX(m_params,itemX);
        if(x->parent() == y) {
            m_params["y_sequence"] = (qint32)(m_params.value("y_seuquence").toInt() - 1);
        }
        m_params["opera_type"] = 4;
    }
    else {
        m_groupTreeShow->setNodeParams(m_params,itemY);
        if(itemX->parent() == itemY)  {
            qint32 sequence = m_params.value("y_sequence").toInt();
            m_params["y_sequence"] = (qint32)( sequence - 1);
        }
        m_groupTreeShow->setparamsX(m_params,itemX);
        m_params["opera_type"] = 2;
    }
    UIHelper::showLoading(this,tr("正在移动"));
    MoveGroupSequenceRunnable* move = new MoveGroupSequenceRunnable(this);

    move->setMoveInfo(m_params);
    QThreadPool::globalInstance()->start(move);
    m_params.clear();

}

void DIRNodesGroupWidget::on_itemtaskCallback(const qint32 msgId, const QString &msg)
{
    if(msgId != CallbackStatus::Basal::_0) {
        UIHelper::ShowMessageBoxError(msg);
        return;
    }
    m_groupTreeShow->clearNodeList();
    setGroup();
    //    setGroupAssoc();
}

void DIRNodesGroupWidget::initWindow()
{
    m_paramsForAddNode.clear();
    m_pageNum = 0;
    m_groupTreeShow = new GroupTree(this);
    m_groupTreeShow->setParent(this);
    m_groupTreeShow->setDragDropMode(QAbstractItemView::InternalMove);
    m_groupTreeShow->setDragEnabled(true);
    m_groupTreeShow->setAcceptDrops(true);
    m_groupTreeShow->setMouseTracking(true);
    m_groupTreeShow->setDropIndicatorShown(true);
    m_groupTreeShow->viewport()->setAcceptDrops(true);

    QHBoxLayout* hlay = new QHBoxLayout;
    hlay->addWidget(m_groupTreeShow);
    this->setLayout(hlay);
    connect(m_groupTreeShow,SIGNAL(itemPressed(QTreeWidgetItem*,int)),this,SLOT(on_showMenu(QTreeWidgetItem*,int)));
    connect(m_groupTreeShow,SIGNAL(evt_moveXToY(const QTreeWidgetItem*,const QTreeWidgetItem*)),this,SLOT(on_moveXToY(const QTreeWidgetItem*,const QTreeWidgetItem*)));
}

void DIRNodesGroupWidget::showEvent(QShowEvent *event)
{
    m_groupTreeShow->clearNodeList();
    setGroup();
}
QVariantMap DIRNodesGroupWidget::params() const
{
    return m_params;
}

void DIRNodesGroupWidget::setParams(const QVariantMap &params)
{
    m_params = params;
}



void DIRNodesGroupWidget::on_itemtaskCallback(const qint32 msgId, const QString &msg, const QList<CsClientGroup> &groupList)
{
    if(msgId != CallbackStatus::Basal::_0)
    {
        UIHelper::hideLoading(this);
        UIHelper::ShowMessageBoxError(msg);
        return;
    }
    m_groupTreeShow->setGroupList(groupList);
    if(groupList.size() == Environment::TreePage::PAGE_NUM - 1) {
        m_pageNum ++;
        setGroup();
    }
    m_pageNum = 0;
    UIHelper::showLoading(this,tr("正在加载节点"));
    setGroupAssoc();
}

void DIRNodesGroupWidget::on_itemtaskCallback(const qint32 msgId, const QString &msg, const QList<VCsClientGroupAssoc> &nodeList)
{
    if(msgId != CallbackStatus::Basal::_0)
    {
        UIHelper::hideLoading(this);
        UIHelper::ShowMessageBoxError(msg);
        return;
    }
    m_groupTreeShow->setGroupAssocList(nodeList);
    if(nodeList.size() == Environment::TreePage::PAGE_NUM - 1) {
        m_pageNum ++;
        setGroupAssoc();
    }
    m_pageNum = 0;
    UIHelper::hideLoading(this);
}
