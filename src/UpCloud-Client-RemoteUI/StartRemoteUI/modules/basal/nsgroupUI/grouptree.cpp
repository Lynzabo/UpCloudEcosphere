#include "grouptree.h"
#include <QApplication>
#include <QCursor>

GroupTree::GroupTree(QWidget *widget):Tree(widget)
{
    initGroupTree();

}

GroupTree::~GroupTree()
{

}
QList<CsClientGroup> GroupTree::groupList() const
{
    return m_groupList;
}

void GroupTree::setGroupList(const QList<CsClientGroup> &groupList)
{
    m_groupList.append(groupList);
    QList<TreeNode> list;
    mapGroupToTreeNode(list,groupList);
    this->setNodeList(list);
}

CsClientGroup GroupTree::getGroupByUuid(const QString &uuid)
{
    return m_uuidToGroupHash.value(uuid);
}


QList<VCsClientGroupAssoc> GroupTree::groupAssocList() const
{
    return m_groupAssocList;
}

void GroupTree::setGroupAssocList(const QList<VCsClientGroupAssoc> &groupAssocList)
{
    m_groupAssocList.append(groupAssocList);
    QList<TreeNode> list;
    mapGroupAssocToTreeNode(list,groupAssocList);
    this->setNodeList(list);
}

VCsClientGroupAssoc GroupTree::getGroupAssocByUuid(const QString &uuid)
{
    return m_uuidToGroupAssocHash.value(uuid);
}

void GroupTree::initGroupTree()
{

    QStringList listText;
    listText << QObject::tr("节点服务器组") << QObject::tr("备注");
    setHeadTextList(listText);
    setStylePath("D:/Users/zhoujunying/test/tree/style.css");
    loadMenu();
    initTree();

}

void GroupTree::showNodeMenu()
{
    node_menu->exec(QCursor::pos());
}

void GroupTree::showGroupMenu()
{
    group_menu->exec(QCursor::pos());
}



QString GroupTree::getUuid(QTreeWidgetItem *item)
{

    QModelIndex index =indexFromItem(item);
    return m_uuidHash.value(index);
}

int GroupTree::getChildCount(QTreeWidgetItem *item)
{
    return item->childCount();
}

int GroupTree::getChildGroupCount(QTreeWidgetItem *item)
{
    if(item->childCount() < 1) {
        return 0;
    }
    int count = 0;
    for(int i = 0;i < item->childCount(); ++i) {
        QString uuid = getUuid(item->child(i));
        if("group" ==  uuid.right(5)) {
            count++;
        }
    }
    return count;
}



QStringList GroupTree::getChildNode(QTreeWidgetItem *item)
{
    QStringList uuids;
    for(int i = 0;i < item->childCount(); ++i) {
        QModelIndex index = indexFromItem(item->child(i));
        QString clientUuid = m_uuidHash.value(index);
        if(clientUuid.right(5) == "nodes") {
            clientUuid.resize(clientUuid.size() - 5);
            VCsClientGroupAssoc groupAssoc = m_uuidToGroupAssocHash.value(clientUuid);
            uuids.append(groupAssoc.getClientUuid());
        }
    }
    return uuids;
}

void GroupTree::setparamsX(QVariantMap &paramsMap, QTreeWidgetItem *item)
{
    QModelIndex index = indexFromItem(item);
    QString x_uuid = m_uuidHash.value(index);
    TreeNode node = m_uuidToBeanHash.value(x_uuid);
    x_uuid.resize(x_uuid.size() - 5);
    paramsMap["x_uuid"] = x_uuid;
    QString x_groupUuid = node.getParentUuid();
    x_groupUuid.resize(x_groupUuid.size() - 5);
    paramsMap["x_groupUuid"] = x_groupUuid;
    paramsMap["x_sequence"] = node.getSequence();
}

void GroupTree::setNodeParams(QVariantMap &params, QTreeWidgetItem *item)
{
    QString groupUuid = getUuid(item);
    groupUuid.resize(groupUuid.size() - 5);
    params["y_groupUuid"] = groupUuid;
    params["y_uuid"] = "";
    int total = getChildCount(item);
    int nodeCount = total - getChildGroupCount(item);
    params["y_sequence"] = nodeCount + 1;
}

QTreeWidgetItem *GroupTree::getItemfromIndex(const QModelIndex index)
{
    return itemFromIndex(index);
}

void GroupTree::setGroupParams(QVariantMap &params, QTreeWidgetItem *item)
{
    params["y_uuid"] = "";
    QString groupUuid = getUuid(item);
    groupUuid.resize(groupUuid.size() - 5);
    params["y_groupUuid"] = groupUuid;
    int groupCount = getChildGroupCount(item);
    params["y_sequence"] =(qint32) (groupCount + 1);
}

void GroupTree::setParamsY(QVariantMap &paramsMap, QTreeWidgetItem *item)
{

    QModelIndex index = indexFromItem(item);
    QString y_uuid = m_uuidHash.value(index);
    TreeNode node = m_uuidToBeanHash.value(y_uuid);
    y_uuid.resize(y_uuid.size() - 5);
    paramsMap["y_uuid"] = y_uuid;
    QString y_groupUuid = node.getParentUuid();
    y_groupUuid.resize(y_groupUuid.size() - 5);
    paramsMap["y_groupUuid"] = y_groupUuid;
    paramsMap["y_sequence"] = node.getSequence();
}

void GroupTree::loadMenu()
{
    node_menu = new QMenu(this);

    node_setUse = new QAction(tr("设置可用"),this);
    node_setUse->setIcon(QIcon(":/basal/nsgroup/imgs/SET_USE"));
    connect(node_setUse,SIGNAL(triggered()),m_parent,SLOT(on_setUseNode()),Qt::QueuedConnection);
    node_menu->addAction(node_setUse);

    node_move = new QAction(tr("移动"),this);
    node_move->setIcon(QIcon(":/basal/nsgroup/imgs/MOVE"));
    connect(node_move,SIGNAL(triggered()),m_parent,SLOT(on_moveNodeForTree()),Qt::QueuedConnection);
    node_menu->addAction(node_move);

    node_del = new QAction(tr("删除"),this);
    node_del->setIcon(QIcon(":/basal/nsgroup/imgs/DELETE"));
    connect(node_del,SIGNAL(triggered()),m_parent,SLOT(on_delNode()),Qt::QueuedConnection);
    node_menu->addAction(node_del);

    group_menu = new QMenu(this);

    group_addGroup = new QAction(tr("增加群组"),this);
    group_addGroup->setIcon(QIcon(":/basal/nsgroup/imgs/ADD_GROUP"));
    connect(group_addGroup,SIGNAL(triggered()),m_parent,SLOT(on__addGroupForTree()),Qt::QueuedConnection);
    group_menu->addAction(group_addGroup);

    group_editGroup = new QAction(tr("编辑群组"),this);
    group_editGroup->setIcon(QIcon(":/basal/nsgroup/imgs/EDIT_GROUP"));
    connect(group_editGroup,SIGNAL(triggered()),m_parent,SLOT(on_editGroupForTree()),Qt::QueuedConnection);
    group_menu->addAction(group_editGroup);

    group_setUse = new QAction(tr("设置可用"),this);
    group_setUse->setIcon(QIcon(":/basal/nsgroup/imgs/SET_USE"));
    connect(group_setUse,SIGNAL(triggered()),m_parent,SLOT(on_setUseGroup()),Qt::QueuedConnection);
    group_menu->addAction(group_setUse);

    group_move = new QAction(tr("移动"),this);
    group_move->setIcon(QIcon(":/basal/nsgroup/imgs/MOVE"));
    connect(group_move,SIGNAL(triggered()),m_parent,SLOT(on_moveGroupForTree()),Qt::QueuedConnection);
    group_menu->addAction(group_move);

    group_delGroup = new QAction(tr("删除"),this);
    group_delGroup->setIcon(QIcon(":/basal/nsgroup/imgs/DELETE"));
    connect(group_delGroup,SIGNAL(triggered()),m_parent,SLOT(on_delGroup()),Qt::QueuedConnection);
    group_menu->addAction(group_delGroup);

    group_addNode = new QAction(tr("addNodes"),this);
    group_addNode->setIcon(QIcon(":/basal/nsgroup/imgs/ADD_NODE"));
    connect(group_addNode,SIGNAL(triggered()),m_parent,SLOT(on_addNodeForTree()),Qt::QueuedConnection);
    group_menu->addAction(group_addNode);

    group_delAllNodes = new QAction(tr("deleteAllNodes"),this);
    group_delAllNodes->setIcon(QIcon(":/basal/nsgroup/imgs/DELETE_ALL"));
    connect(group_delAllNodes,SIGNAL(triggered()),m_parent,SLOT(on_delAllNodes()),Qt::QueuedConnection);
    group_menu->addAction(group_delAllNodes);
}

void GroupTree::mapGroupToTreeNode(QList<TreeNode> &list,const QList<CsClientGroup> &groupList)
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

void GroupTree::mapGroupAssocToTreeNode(QList<TreeNode> &list,const QList<VCsClientGroupAssoc> &groupAssocList)
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





