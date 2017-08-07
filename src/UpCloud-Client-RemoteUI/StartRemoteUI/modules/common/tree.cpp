
#include "tree.h"
#include "uihelper.h"
Tree::Tree(QWidget* object):m_parent(object)
{
    m_nodeList.clear();
    m_checkList.clear();
    m_groupList.clear();
    m_uuidToBeanHash.clear();
    m_uuidHash.clear();
    m_checkUuid.clear();
    m_topList.clear();
    m_oldCur = this->cursor();
    m_newCur = QCursor(Qt::ForbiddenCursor);
    m_checkBoxFlg = false;
    m_signalOnlyOne = false;
    //TODO 暂时在构选函数中开启鼠标设置刷新，如果以后做成点击菜单后才能拖拽，这个可以在菜单槽函数执行
    startTimer(1000);
    qRegisterMetaType<QList<QTreeWidgetItem> >("QList<QTreeWidgetItem>");
    qRegisterMetaType<QList<TreeNode> >("QList<TreeNode>");
    connect(this,SIGNAL(itemChanged(QTreeWidgetItem*,int)),this,SLOT(treeItemChanged(QTreeWidgetItem*,int)));
}

Tree::~Tree()
{

}


QList<TreeNode> Tree::nodeList() const
{
    return m_nodeList;
}

void Tree::changeStateTop(QTreeWidgetItem *item)
{

    if(!item->parent()) {
        return;
    }
    int cur = 1;
    QTreeWidgetItem* tem = item->parent();
    int i;
    for(i= 0;i < tem->childCount(); ++i) {
        if(item == tem->child(i)) {
            continue;
        }
        if(item->checkState(0) != tem->child(i)->checkState(0)) {
            if(tem->checkState(0) != Qt::PartiallyChecked) {
                m_current.push_back(cur);

                tem->setCheckState(0,Qt::PartiallyChecked);
            }
            return;
        }
    }
    if(tem->checkState(0) == item->checkState(0)) {
        return;
    }

    m_current.push_back(cur);
    tem->setCheckState(0,item->checkState(0));
}

void Tree::changeStateBottom(QTreeWidgetItem *item)
{


    if(!item->childCount()) {
        return;
    }
    int cur =0;
    int i = 0;
    for(i= 0;i < item->childCount(); ++i) {
        QTreeWidgetItem* tem = item->child(i);
        if(tem->checkState(0) == item->checkState(0)) {
            continue;
        }
        m_current.push_back(cur);
        tem->setCheckState(0,item->checkState(0));
    }
}

void Tree::setNodeList(QList<TreeNode> &nodeList)
{
    m_nodeList.append(nodeList);
    for(QList<TreeNode>::iterator it = nodeList.begin(); it != nodeList.end(); ++it) {
        loadTreeNode(*it);
    }
    this->expandToDepth(1);
}

void Tree::clearNodeList()
{
    this->clear();
    m_nodeList.clear();
    m_topList.clear();
    m_uuidHash.clear();
    m_allItem.clear();
    m_uuidToBeanHash.clear();
    m_groupList.clear();
}

QList<TreeNode> Tree::getNodeList() const
{
    return m_nodeList;
}


void Tree::loadTreeNode(TreeNode &node)
{
    if(node.getParentUuid().isEmpty()) {
        QStringList list;
        list << node.getName() << node.getDescription();
        QTreeWidgetItem* item = new QTreeWidgetItem(this,list);
        if(m_checkBoxFlg)
        {
            item->setCheckState(0,Qt::Unchecked);
        }
        item->setIcon(0,QIcon(iconFile(node)));
        node.setIndex(this->indexFromItem(item,0));
        item->setTextAlignment(1,Qt::AlignCenter);
        m_groupList.append(item);
        m_topList.append(item);
        m_uuidToBeanHash.insert(node.getUuid(),node);
        //TODO
        m_uuidHash.insert(this->indexFromItem(item),node.getUuid());
        m_allItem.append(item);

    }
    else if(node.getIsGroup()) {
        QStringList list;
        list << node.getName() << node.getDescription();
        QTreeWidgetItem* item = new QTreeWidgetItem(list);
        if(m_checkBoxFlg)
        {
            item->setCheckState(0,Qt::Unchecked);
        }
        item->setIcon(0,QIcon(iconFile(node)));
        node.setIndex(this->indexFromItem(item,0));
        item->setTextAlignment(1,Qt::AlignCenter);
        QTreeWidgetItem* parent = this->itemFromIndex(m_uuidToBeanHash.value(node.getParentUuid()).getIndex());
        item->setExpanded(true);
        parent->addChild(item);
        node.setIndex(this->indexFromItem(item));
        m_groupList.append(item);
        m_uuidToBeanHash.insert(node.getUuid(),node);
        //TODO
        m_uuidHash.insert(this->indexFromItem(item),node.getUuid());
        m_allItem.append(item);
    }
    else {
        QStringList list;
        list << node.getName() << node.getDescription();
        QTreeWidgetItem* item = new QTreeWidgetItem(list);
        if(m_checkBoxFlg)
        {
            item->setCheckState(0,Qt::Unchecked);
        }
        item->setIcon(0,QIcon(iconFile(node)));
        node.setIndex(this->indexFromItem(item,0));
        item->setTextAlignment(1,Qt::AlignCenter);
        QTreeWidgetItem* parent = this->itemFromIndex(m_uuidToBeanHash.value(node.getParentUuid()).getIndex());
        parent->addChild(item);
        node.setIndex(this->indexFromItem(item));
        m_uuidToBeanHash.insert(node.getUuid(),node);
        //TODO
        m_uuidHash.insert(this->indexFromItem(item),node.getUuid());
        m_allItem.append(item);
    }
}

void Tree::loadTree()
{
    this->clear();
    m_topList.clear();
    m_uuidHash.clear();
    m_allItem.clear();
    m_uuidToBeanHash.clear();
    m_groupList.clear();
    for(QList<TreeNode>::iterator it = m_nodeList.begin(); it != m_nodeList.end(); ++it) {
        loadTreeNode(*it);
    }
}

void Tree::initTree()
{
    this->setParent(m_parent);
    //TODO 释放资源
    QVBoxLayout* layout = new QVBoxLayout;
    if(m_parent) {
        QSize size = m_parent->size();
        this->resize(size);
    }
    else {
        this->resize(400,500);
    }
    //获取真实的宽度
    int treeWidth = this->width();
    this->setColumnWidth(0,(int)treeWidth/2);
    layout->addStretch(1);
    QTreeWidgetItem* item = new QTreeWidgetItem(m_headTextList);
    for(int i =0;i < m_headTextList.size(); ++i)
    {
        item->setTextAlignment(i,Qt::AlignCenter);
    }
    this->setHeaderItem(item);
    loadTree();

    //       this->insertTopLevelItems(1,m_topList);
    //   this->allSelect();
    //TODO 要修改成相对路径
    //    QFile file(m_stylePath);
    //    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)){}
    //    QTextStream stream(&file);
    //    QString strText = stream.readAll();
    //    file.close();
    //    this->setStyleSheet(strText);
    this->setLayout(layout);

}

QString Tree::iconFile(const TreeNode &node)
{
    if(!node.getIsGroup()) {
        return ":/basal/nsgroup/imgs/SERVER";
    }
    else if(node.getIsParent()) {
        return ":/basal/nsgroup/imgs/PARENT";
    }
    else {
        return ":/basal/nsgroup/imgs/CHILD";
    }
}

void Tree::invertSelect()
{
    m_groupList.clear();
    foreach(QTreeWidgetItem* item,m_topList) {
        getNoChild(item);
    }
    for(QList<QTreeWidgetItem*>::iterator item = m_groupList.begin();item != m_groupList.end();++item) {
        if((*item)->checkState(0) == Qt::Checked) {
            (*item)->setCheckState(0,Qt::Unchecked);
        }
        else {
            (*item)->setCheckState(0,Qt::Checked);
        }
    }
}

void Tree::setDefaultSelect(QList<TreeNode> &list)
{
    foreach(const TreeNode &node,list) {
        TreeNode info = m_uuidToBeanHash.value(node.getUuid());
        QTreeWidgetItem* item = this->itemFromIndex(info.getIndex());
        item->setCheckState(0,Qt::Checked);


    }
}

void Tree::getCheckUuid()
{

    foreach(const TreeNode &node,m_nodeList) {
        if(m_checkList.contains(node.getIndex())) {
            m_checkUuid.push_back(node.getUuid());
        }
    }

}

void Tree::resizeEvent(QResizeEvent *event)
{
    int treeWidth = this->width();
    this->setColumnWidth(0,(int)treeWidth/2);
}

void Tree::treeItemChanged(QTreeWidgetItem *item, int column)
{

    if(column) {
        return;
    }
    if(m_checkList.contains(this->indexFromItem(item))) {
        m_checkList.removeOne(this->indexFromItem(item));
    }
    else if(!m_checkList.contains(this->indexFromItem(item))) {
        m_checkList.append(this->indexFromItem(item));

        emit evt_checkBoxChanged();
        if(m_signalOnlyOne) {
            return;
        }
        //TODO
        //       TreeNode& node = m_uuidHash.value(QString("%1").arg(this->indexFromItem(item)));
        //       m_checkUuid.append(node.getUuid());

    }
    else {
        return;
    }
    int cur;
    if(!m_current.isEmpty()) {
        cur = m_current.last();
        m_current.pop_back();
    }
    else {
        cur = 3;//起初开始可以上下检索
    }
    if(0 == cur) {//向下检索
        changeStateBottom(item);
    }
    else if(1 == cur) {//向上检索
        changeStateTop(item);
    }
    else {
        changeStateTop(item);
        changeStateBottom(item);
    }

}
bool Tree::getSignalOnlyOne() const
{
    return m_signalOnlyOne;
}

void Tree::setSignalOnlyOne(bool signalOnlyOne)
{
    m_signalOnlyOne = signalOnlyOne;
}

QStringList Tree::getCheckNodeServerUuid()
{
    foreach(const QModelIndex &index,m_checkList)
    {
        QString uuid = m_uuidHash.value(index);
        if(uuid.right(5) != "nodes")
        {
            continue;
        }
        uuid.resize(uuid.size() - 5);
        m_checkUuid.append(uuid);
    }
    return m_checkUuid;
}

QRect Tree::getItemRect(QTreeWidgetItem *item)
{
    return this->visualItemRect(item);
}

QList<QTreeWidgetItem *> Tree::getGroupList() const
{
    return m_groupList;
}

void Tree::setGroupList(const QList<QTreeWidgetItem *> &groupList)
{
    m_groupList = groupList;
}

QList<QModelIndex> Tree::getCheckList() const
{
    return m_checkList;
}

QTreeWidgetItem *Tree::getItemFromUuid(const QString &uuid)
{
    foreach(const QModelIndex &index,m_uuidHash.keys())
    {
        if(m_uuidHash.value(index) == uuid) {
            return itemFromIndex(index);
        }
    }
}



QString Tree::getStylePath() const
{
    return m_stylePath;
}

void Tree::setStylePath(const QString &stylePath)
{
    m_stylePath = stylePath;
}

void Tree::setHeadTextList(const QStringList &headTextList)
{
    m_headTextList = headTextList;
}

QTreeWidgetItem *Tree::getGroupLastChild(const QTreeWidgetItem* item, GROUP_TYPE flg)
{
    int i;
    for( i = item->childCount() - 1 ;i >= 0; --i) {
        QTreeWidgetItem* childItem = item->child(i);
        if(!m_groupList.contains(childItem) && flg == GROUP_NODE) {
            return childItem;
        }
        else if(m_groupList.contains(childItem) && flg == GROUP_GROUP) {
            return childItem;
        }
        else {
            continue;
        }
    }
    if(i == -1) {
        return 0;
    }
}

bool Tree::isGroup(QTreeWidgetItem *item)
{

    QModelIndex index =indexFromItem(item);
    QString x_uuid = m_uuidHash.value(index);
    return m_uuidToBeanHash.value(x_uuid).getIsGroup();

}

bool Tree::isInvalid(const QTreeWidgetItem *itemX, QTreeWidgetItem *itemY)
{
    QTreeWidgetItem* parent = itemY;

    while(parent) {
        if(itemX == parent ) {
            return true;
        }
        if(m_topList.contains(itemY)) {
            break;
        }
        parent = parent->parent();
    }
    return false;
}


void Tree::getNoChild(QTreeWidgetItem *item)
{
    if(!item->childCount()) {
        m_groupList.push_back(item);
        return;
    }
    for(int i = 0;i < item->childCount(); ++i) {
        QTreeWidgetItem* child = item->child(i);
        getNoChild(child);
    }
}

void Tree::setEnableCheckBox(bool flg)
{
    m_checkBoxFlg = flg;
}
void Tree::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton)
    {
        int dragDistance = (event->pos() - m_startDragPoint).manhattanLength();
        //采用非标准情况，极小的移动就算是拖拽（标准的是四个像素） 后期如果抖动现像严重，可以把值改大一点
        if (dragDistance > 2)
        {
            startDropAndDrag();
        }


    }

    QTreeWidget::mouseMoveEvent(event);
}

void Tree::mousePressEvent(QMouseEvent *event)
{
    m_startDragPoint = event->pos();

    QTreeWidget::mousePressEvent(event);
}

void Tree::mouseReleaseEvent(QMouseEvent *event)
{
    //qDebug() << "------------------mouseReleaseEvent---------------------";
    QTreeWidget::mouseReleaseEvent(event);
}

void Tree::dropEvent(QDropEvent *event)
{

    this->setCursor(m_oldCur);
    qDebug() << "dropEvent----------------------------";
    QWidget *source =  qobject_cast<Tree *>(event->source());
    const TreeItemMimeData *pMimeData = (const TreeItemMimeData *)(event->mimeData());
    if (source == this )
    {
        const QTreeWidgetItem *item = pMimeData->DragItemData();
        int i = 0 ;
        QTreeWidgetItem *currentItem = this->itemAt(event->pos());

        if(!m_allItem.contains(currentItem)) {
            return;
        }
        //检测放入目标是否有效(父不能放入子内)
        if(isInvalid(item,currentItem)) {
            return;
        }

        //检测是否是群组
        if(!isGroup(currentItem))  {
            return;
        }
        //判断是否存在目标来源
        for(i = 0;i < m_allItem.size(); ++i) {
            QTreeWidgetItem* temItem = m_allItem.at(i);
            if(temItem == item) {
                break;
            }
        }
        if(i >= m_allItem.size()) {
            return;
        }
        int flg = UIHelper::ShowMessageBoxQuesion(tr("你确定要进行此移动操作吗?"));
        if(flg) {
            evt_moveXToY(item,currentItem);
        }
        else {
            event->ignore();
            return;
        }
        QTreeWidgetItem *pItem = item->clone();

        if (currentItem && (currentItem != item))
        {
            currentItem->addChild(pItem);
        }
        else
        {
            //暂时还没开启可以产生一级的项目，也就是不可以单独移出一颗树。后期如果要允许这样做，把来源过滤去掉就可以了（在前面的代码中）
            this->addTopLevelItem(pItem);
        }


        event->setDropAction(Qt::MoveAction);
        //        qDebug() << "dropEvent"<< event->pos();
        event->accept();
    }
    else {
        return;
    }
    QTreeWidget::dropEvent(event);
}

void Tree::dragEnterEvent(QDragEnterEvent *event)
{
    //拖拽进行事件
    //    qDebug() << "dragEnterEvent"<< event->pos();
    QWidget *source =  qobject_cast<Tree *>(event->source());

    if (source == this/* 这个不允许拖到另一个控件上*/ )
    {

        event->setDropAction(Qt::MoveAction);
        event->accept();
    }
}

void Tree::dragMoveEvent(QDragMoveEvent *event)
{
    //    qDebug() << "dragMoveEvent";

    QWidget *source =  qobject_cast<Tree *>(event->source());
    if (source == this )
    {
        const TreeItemMimeData *pMimeData = (const TreeItemMimeData *)(event->mimeData());
        const QTreeWidgetItem *item = pMimeData->DragItemData();
        QTreeWidgetItem *currentItem = this->itemAt(event->pos());
        QTreeWidgetItem* isItem = this->itemAt(m_startDragPoint);
        //TODO 暂时允许可以在一级下移动，如果不允许可以把下边注释打开
        {
            //移动与移动目标都不能是根
            //            int i = 0;
            //            for(i = 0;i < m_topList.size(); ++i) {
            //                QTreeWidgetItem* temItem = m_topList.at(i);
            //                if(temItem == item || temItem == currentItem) {
            //                    break;
            //                }
            //            }
        }
        if(!isItem) {
            event->ignore();
            qDebug() << "!isItem----------------------------";
            this->setCursor(m_newCur);

        }/*一级树下禁止移动的判断
        else if(i < m_topList.size()) {
            event->ignore();
            qDebug() << "!m_topList.size()----------------------------";
            this->setCursor(m_newCur);
        }*/
        else if(!currentItem) {
            event->ignore();
            qDebug() << "!currentItem----------------------------";
            this->setCursor(m_newCur);
        }
        //检测放入目标是否有效
        else if(isInvalid(item,currentItem)) {
            event->ignore();

            qDebug() << "isInvalid(item,currentItem----------------------------";
            this->setCursor(m_newCur);
        }
        //检测是否是群组
        else if(!isGroup(currentItem)) {
            event->ignore();
            qDebug() << "isGroup(currentItem----------------------------";
            this->setCursor(m_newCur);
        }
        else if (currentItem == item )           //不允许拖回到原来的item
        {
            event->ignore();
            qDebug() << "currentItem == item ----------------------------";
            this->setCursor(m_newCur);
        }
        else
        {
            setCurrentItem(currentItem);
            event->setDropAction(Qt::MoveAction);
            qDebug() << "else----------------------------";
            //            this->setCursor(m_oldCur);
            event->accept();
        }

    }
}

void Tree::startDropAndDrag()
{
    QTreeWidgetItem *item = currentItem();

    if (item)
    {
        TreeItemMimeData *mimeData = new TreeItemMimeData;
        mimeData->SetDragData("ItemMimeData",item);

        QDrag *drag = new QDrag(this);
        drag->setMimeData(mimeData);
        QRect rect = getItemRect(item);
        m_dis.setX(m_startDragPoint.x() - rect.x());
        m_dis.setY(m_startDragPoint.y() - rect.y());
        QRect moveRect = rect;
        //TODO 因为主界面不是标准标题栏，所以坐标有偏差，如果标题栏的高度改变，这个必须要随时改
        //这个主要是计算鼠标位置相对于拖拽项目的位置，保持相对差
        moveRect.setY(rect.y() + 27);
        moveRect.setHeight(rect.height());
        m_pixMap =  this->grab(moveRect);
        //要检测来源是否有效
        QTreeWidgetItem* isItem = this->itemAt(m_startDragPoint);
        if(!isItem) {
            return;
        }
        drag->setHotSpot(m_dis);
        drag->setPixmap(m_pixMap);
        //drag->exec(Qt::MoveAction);
        //这里保证不会移出控件外面，不会删除
        if (drag->exec(Qt::MoveAction) == Qt::MoveAction) {
            delete item;
        }
    }
}

void Tree::timerEvent(QTimerEvent *event)
{
    //为了解决不及时刷新鼠标的问题，后期效率上再认真思考一下算法
    this->setCursor(m_oldCur);
}

