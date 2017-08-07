#include "dicttree.h"
#include "modules/common/loading.h"
#include "modules/common/uihelper.h"
#include "baseiremote.h"
using namespace RemoteUIEnvironment::CallbackStatus;
DictTree::DictTree(QWidget *widget):m_parent(widget)
{
    this->setHeaderHidden(true);
    isFirstLoad = true;
    connect(this,SIGNAL(itemDoubleClicked(QTreeWidgetItem*,int)),this,SLOT(on_doubleClieked(QTreeWidgetItem*,int)));
    initTree();

}



void DictTree::on_reload()
{
    this->clear();
    loadDatas();
}

void DictTree::on_addNode(const CsDict &dict)
{
    QTreeWidgetItem* item = new QTreeWidgetItem;
    item->setFlags(item->flags() & ~Qt::ItemIsEditable);
    item->setText(0,dict.getName());
    QModelIndex index = m_uuidToIndex.value(dict.getSupUuid());
    QTreeWidgetItem* parent = itemFromIndex(index);
    parent->addChild(item);
    index = indexFromItem(item);
    m_indexToUUid.insert(index,dict.getUuid());
    m_uuidToIndex.insert(dict.getUuid(),index);
}

void DictTree::on_delNode(const QList<QString> &uuids)
{
    for(int i = 0;i < uuids.size();++i) {
        QString uuid = uuids.at(i);
        QModelIndex index = m_uuidToIndex.value(uuid);
        QTreeWidgetItem* item = itemFromIndex(index);
        QTreeWidgetItem* parent = item->parent();
        parent->removeChild(item);
        delete item;
        m_uuidToBean.remove(uuid);
        m_uuidToIndex.remove(uuid);
        m_indexToUUid.remove(index);
        // TODO 实体链表需要删除需要后期再商定
    }
}

void DictTree::on_doubleClieked(QTreeWidgetItem *item, int column)
{

    Q_UNUSED(column)
    //如果没有子节点则不会展示
//    if(item->childCount() <= 0) {
//        item = item->parent();
//    }

//    QModelIndex index = indexFromItem(item);
//    QString uuid = m_indexToUUid.value(index);
//    QString name = m_uuidToBean.value(uuid).getName();
//    emit
//    evt_itemClicked(uuid,name);
}

void DictTree::on_itemClicked(QTreeWidgetItem *item, int column)
{
    QModelIndex index = indexFromItem(item);
    QString uuid = m_indexToUUid.value(index);
    QString name = m_uuidToBean.value(uuid).getName();
    emit
    evt_itemClicked(uuid,name);
}



void DictTree::on_itemtaskCallback(const qint32 msgId, const QString &msg, const QList<CsDict> &taskList)
{
    if(msgId != Basal::_0 ) {
        UIHelper::hideLoading(this);
        UIHelper::ShowMessageBoxError(msg);
        return;
    }
    m_dictList.append(taskList);
    loadTree();
    UIHelper::hideLoading(this);
    //第一次
    if(m_dictList.size() < 1 && isFirstLoad) {
        return;
    }
    CsDict dict = m_dictList.at(0);
    QString uuid = dict.getUuid();
    QString name = dict.getName();
    emit
    evt_itemClicked(uuid,name);
    isFirstLoad = false;
}

void DictTree::initTree()
{
    if(!m_parent) {
        return;
    }
    this->setParent(m_parent);
    QSize size = m_parent->size();
    this->resize(size);
    connect(this,SIGNAL(itemClicked(QTreeWidgetItem*,int)),this,SLOT(on_itemClicked(QTreeWidgetItem*,int)));
}



void DictTree::showEvent(QShowEvent *event)
{
    Q_UNUSED(event)
    this->clear();
    UIHelper::showLoading(this,tr("正在加载数据"));
    loadDatas();
}

void DictTree::loadTree()
{
    m_indexToUUid.clear();
    m_uuidToIndex.clear();
    m_uuidToBean.clear();
    foreach(const CsDict &dict,m_dictList)
    {
        loadTreeNode(dict);
        m_uuidToBean.insert(dict.getUuid(),dict);
    }
    this->expandToDepth(1);
}

void DictTree::loadDatas()
{

    m_dictList.clear();
    ListDictRunnable* dict  = new ListDictRunnable(this);
    QVariantMap params;params.clear();
    dict->setSelectCondition(params);
    dict->setFilterUnused();
    QThreadPool::globalInstance()->start(dict);
}

void DictTree::loadTreeNode(const CsDict &dict)
{
    if(dict.getSupUuid() == "-1") {
        QTreeWidgetItem* item = new QTreeWidgetItem(this);
        item->setFlags(item->flags() & ~Qt::ItemIsEditable);
        item->setText(0,dict.getName());
        QModelIndex index = indexFromItem(item);
        m_indexToUUid.insert(index,dict.getUuid());
        m_uuidToIndex.insert(dict.getUuid(),index);
    }
    else {
        QTreeWidgetItem* item = new QTreeWidgetItem;
        item->setFlags(item->flags() & ~Qt::ItemIsEditable);
        item->setText(0,dict.getName());
        QModelIndex index = m_uuidToIndex.value(dict.getSupUuid());
        QTreeWidgetItem* parent = itemFromIndex(index);
        parent->addChild(item);
        index = indexFromItem(item);
        m_indexToUUid.insert(index,dict.getUuid());
        m_uuidToIndex.insert(dict.getUuid(),index);
    }
}

