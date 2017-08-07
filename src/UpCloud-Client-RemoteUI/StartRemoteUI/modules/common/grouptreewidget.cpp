#include "grouptreewidget.h"
#include <QVBoxLayout>
#include "ui_grouptreewidget.h"
#include "modules/common/uihelper.h"
#include "modules/common/loading.h"
#include "../FrontBusinessIRemoteUI/BasalOperaIRemoteUI/basaloperairemoteui.h"
#include "../../UpCloud-Service-Center/BusinessIServer/BasalIServer/bean/cscgroup.h"
#include "../../UpCloud-Service-Center/BusinessIServer/BasalIServer/bean/cscextendinfo.h"
using namespace RemoteUIEnvironment;
using namespace Environment;
GroupTreeWidget::GroupTreeWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GroupTreeWidget)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_ShowModal,true);
    this->setAttribute(Qt::WA_DeleteOnClose);
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowMinMaxButtonsHint);

}

GroupTreeWidget::~GroupTreeWidget()
{
    delete ui;
}

void GroupTreeWidget::setParamsForClientUuid(QStringList *params, QStringList *description)
{
    m_paramsForUuids = params;
    m_descriptionForGroup = description;
}

void GroupTreeWidget::on_itemtaskCallback(const qint32 msgId, const QString &msg, const QList<CsClientGroup> &groupList)
{
    if(msgId != CallbackStatus::Basal::_0)
    {
        UIHelper::hideLoading(this);
        UIHelper::ShowMessageBoxError(msg);
        return;
    }
    QList<TreeNode> temList;
    mapGroupToTreeNode(temList,groupList);
    m_tree->setNodeList(temList);
    if(groupList.size() == Environment::TreePage::PAGE_NUM - 1) {
        m_pageNum ++;
        loadGroup();
    }
    m_pageNum = 0;
    UIHelper::showLoading(this,tr("正在加载节点"));
    loadGroupAssoc();
}

void GroupTreeWidget::on_itemtaskCallback(const qint32 msgId, const QString &msg, const QList<VCsClientGroupAssoc> &nodeList)
{
    if(msgId != CallbackStatus::Basal::_0)
    {
        UIHelper::hideLoading(this);
        UIHelper::ShowMessageBoxError(msg);
        return;
    }
    QList<TreeNode> temList;
    mapGroupAssocToTreeNode(temList,nodeList);
    m_tree->setNodeList(temList);
    if(nodeList.size() == Environment::TreePage::PAGE_NUM - 1) {
        m_pageNum ++;
        loadGroupAssoc();
    }
    m_pageNum = 0;
    UIHelper::hideLoading(this);

}

void GroupTreeWidget::layout()
{
    QVBoxLayout* lay = new QVBoxLayout;
    lay->addWidget(ui->w_header);
    lay->addWidget(m_tree);\
    QVBoxLayout* hlay = new QVBoxLayout;
    hlay->setSizeConstraint(QLayout::SetDefaultConstraint);
    hlay->setContentsMargins(0, 0, 0, 0);
    QSpacerItem* verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Maximum);

    hlay->addItem(verticalSpacer);

    QHBoxLayout* hl_btn = new QHBoxLayout();
    QSpacerItem* horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
    hl_btn->addItem(horizontalSpacer);

    hl_btn->addWidget(ui->btn_ok);

    QSpacerItem* horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    hl_btn->addItem(horizontalSpacer_2);
    hl_btn->addWidget(ui->btn_quit);

    QSpacerItem* horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    hl_btn->addItem(horizontalSpacer_3);


    hlay->addLayout(hl_btn);

    QSpacerItem*  verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Maximum);

    hlay->addItem(verticalSpacer_2);


    lay->addLayout(hlay);
    lay->setContentsMargins(0, 0, 0, 0);
    this->setLayout(lay);
}

void GroupTreeWidget::initWindow()
{
    m_uuidToGroupAssocHash.clear();
    m_uuidToGroupHash.clear();
    m_groupAssocList.clear();
    m_groupList.clear();
    m_pageNum = 0;
    m_tree = new Tree(this);
    m_tree->setEnableCheckBox(true);
    QStringList listText;
    listText << QObject::tr("节点服务器组") << QObject::tr("备注");
    m_tree->setHeadTextList(listText);
//    m_tree->setStylePath("D:/Users/zhoujunying/test/tree/style.css");
    layout();
    m_tree->initTree();

}

void GroupTreeWidget::showEvent(QShowEvent *event)
{
    initWindow();
    loadGroup();
}

void GroupTreeWidget::loadGroup()
{
    UIHelper::showLoading(this,tr("加载群组"));
    ListClientGroupRunnable* group = new ListClientGroupRunnable(this);
    QStringList list;
    list << "-1";
    group->setGroupInfo(list,m_pageNum);
    QThreadPool::globalInstance()->start(group);
}

void GroupTreeWidget::loadGroupAssoc()
{
    UIHelper::showLoading(this,tr("加载节点"));
    ListClientGroupAssocRunnable* node = new ListClientGroupAssocRunnable(this);
    node->setGroupAssocUuid("",m_pageNum);
    QThreadPool::globalInstance()->start(node);
}

void GroupTreeWidget::mapGroupToTreeNode(QList<TreeNode> &list, const QList<CsClientGroup> &groupList)
{
    list.clear();
    foreach(const CsClientGroup &group,groupList)
    {
        TreeNode node;
        node.setUuid(group.getUuid().append("group"));
        node.setName(group.getName());
        node.setDescription(group.getDescription());
        node.setIsGroup(true);
        node.setIsParent(true);
        node.setSequence(group.getSequence());
        if("-1" == group.getSupUuid()) {
            node.setParentUuid("");
        }
        else {
            node.setParentUuid(group.getSupUuid().append("group"));
        }
        list.append(node);
        m_uuidToGroupHash.insert(group.getUuid(),group);
    }
}

void GroupTreeWidget::mapGroupAssocToTreeNode(QList<TreeNode> &list, const QList<VCsClientGroupAssoc> &groupAssocList)
{
    list.clear();
    foreach(const VCsClientGroupAssoc &groupAssoc,groupAssocList)
    {
        TreeNode node;
        node.setUuid(groupAssoc.getUuid().append("nodes"));
        node.setName(groupAssoc.getClientUuid());
        node.setDescription(groupAssoc.getDescription());
        node.setIsGroup(false);
        node.setIsParent(false);
        node.setSequence(groupAssoc.getSequence());
        node.setParentUuid(groupAssoc.getGroupUuid().append("group"));
        list.append(node);
        m_uuidToGroupAssocHash.insert(groupAssoc.getUuid(),groupAssoc);
    }
}

void GroupTreeWidget::on_btn_ok_clicked()
{
    QStringList uuids =  m_tree->getCheckNodeServerUuid();
    QVariantMap desMap;
    (*m_paramsForUuids).clear();
    (*m_descriptionForGroup).clear();
    foreach(const QString &uuid,uuids) {
        //要获取节点服务器的固定码  而非UUID
        QString clientUuid = m_uuidToGroupAssocHash.value(uuid).getClientUuid();
        QString groupUuid = m_uuidToGroupAssocHash.value(uuid).getGroupUuid();
        QString decription = m_uuidToGroupHash.value(groupUuid).getDescription();
        //取出所有的节点服务器所属群组的描述集合，并用逗号隔开
        if(!(*m_paramsForUuids).contains(clientUuid)) {
            (*m_paramsForUuids).append(clientUuid);
            desMap[clientUuid] = decription;
        }
        else {
            QString desStr = desMap.value(clientUuid).toString();
            desStr.append(",").append(decription);
            desMap[clientUuid] = desStr;
        }
    }
    //保证节点服务器固定码与所属群组的描述集合 一一对应
    foreach(const QString &uuid,(*m_paramsForUuids)) {
        QString desStr = desMap.value(uuid).toString();
        (*m_descriptionForGroup).append(desStr);
    }
    emit evt_ok();
    this->deleteLater();
}

void GroupTreeWidget::on_btn_quit_clicked()
{
    this->deleteLater();
}
void GroupTreeWidget::mouseMoveEvent(QMouseEvent *e)
{
    if (mousePressed && (e->buttons() && Qt::LeftButton)) {
        this->move(e->globalPos() - mousePoint);
        e->accept();
    }
}

void GroupTreeWidget::mousePressEvent(QMouseEvent *e)
{
    if (e->button() == Qt::LeftButton) {
        mousePressed = true;
        mousePoint = e->globalPos() - this->pos();
        e->accept();
    }
}

void GroupTreeWidget::mouseReleaseEvent(QMouseEvent *)
{
    mousePressed = false;
}
void GroupTreeWidget::on_btn_menu_cancel_clicked()
{
    this->deleteLater();
}
