#ifndef TREE_H
#define TREE_H

#include <QtCore>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHash>
#include <QMouseEvent>
#include <QDropEvent>
#include <QMimeData>
#include <QPixmap>
#include <QPainter>
#include <QDrag>
#include "treeglobal.h"
#include <QTreeWidgetItem>
#include "treenode.h"


class TreeItemMimeData:public QMimeData
{
    Q_OBJECT
public:
    TreeItemMimeData():QMimeData()
    {
        m_pDragItem = NULL;
    }

    ~TreeItemMimeData()
    {

    }

    void SetDragData(QString mimeType , QTreeWidgetItem *pItem)
    {
        m_format<<mimeType;
        m_pDragItem = pItem;
    }



    QStringList formats() const
    {
        return m_format;
    }

    const QTreeWidgetItem* DragItemData() const
    {
        return m_pDragItem;
    }


protected:

    QVariant retrieveData(const QString &mimetype, QVariant::Type preferredType) const
    {
        if (mimetype == "ItemMimeData")
        {
            return m_pDragItem;
        }
        else
        {
            return QMimeData::retrieveData(mimetype, preferredType);
        }
    }
private:
    const QTreeWidgetItem   *m_pDragItem;
    QStringList              m_format;
};

class Tree : public QTreeWidget
{
    Q_OBJECT
public:
    enum GROUP_TYPE{
        GROUP_GROUP,
        GROUP_NODE
    };
    Tree(QWidget* object = 0);
    ~Tree();

    QList<TreeNode> nodeList() const;
    //向上递归
    virtual void changeStateTop(QTreeWidgetItem* item);
    //向下递归
    virtual void changeStateBottom(QTreeWidgetItem* item);
    //加载所有实体信息
    void setNodeList( QList<TreeNode> &nodeList);
    //清空实体信息
    void clearNodeList();
    QList<TreeNode> getNodeList()const;
    //加载树节点
    void loadTreeNode(TreeNode &node);
    //加载树
    void loadTree();
    //初始化树
    void initTree();
    //设置节点图标
    virtual QString iconFile(const TreeNode &node);
    //全选
    void allSelect();
    //反选
    void invertSelect();
    //加载默认选中信息
    void setDefaultSelect(QList<TreeNode> &list);
    //获取所有的叶子节点信息
    virtual void getNoChild(QTreeWidgetItem* item);
    //加复选框标志
    void setEnableCheckBox(bool flg = false);
    //设置表头
    void setHeadTextList(const QStringList &headTextList);
    //获取组内同类型最后一个孩子
    virtual QTreeWidgetItem* getGroupLastChild(const QTreeWidgetItem *item, GROUP_TYPE flg);
    //判断是否是群组
    bool isGroup(QTreeWidgetItem* item);
    //判断Y是否是X的子节点
    bool isInvalid(const QTreeWidgetItem* itemX, QTreeWidgetItem *itemY);
    QString getStylePath() const;
    void setStylePath(const QString &stylePath);

    QList<QModelIndex> getCheckList() const;
    QTreeWidgetItem* getItemFromUuid(const QString &uuid);
    QList<QTreeWidgetItem *> getGroupList() const;
    void setGroupList(const QList<QTreeWidgetItem *> &groupList);

    bool getSignalOnlyOne() const;
    void setSignalOnlyOne(bool signalOnlyOne);

    //获取选择的节点服务器列表UUID
    QStringList getCheckNodeServerUuid();

    QRect getItemRect(QTreeWidgetItem* item);
signals:
    void evt_checkBoxChanged();
    void evt_moveXToY(const QTreeWidgetItem* x,const QTreeWidgetItem* y);
protected:
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void dropEvent(QDropEvent *event);
    void dragEnterEvent(QDragEnterEvent *event);
    void dragMoveEvent(QDragMoveEvent *event);
    void startDropAndDrag();
    void timerEvent(QTimerEvent *event);
private slots:

    //获取选中的UUID
    void getCheckUuid();
    void resizeEvent(QResizeEvent* event);
    //复选框的状态改变检测判断其他复选框
    void treeItemChanged(QTreeWidgetItem* item,int column);
protected:
    QWidget* m_parent;
    QHash<QModelIndex,QString> m_uuidHash;
    QHash<QString,TreeNode> m_uuidToBeanHash;
    QList<QTreeWidgetItem*> m_topList;
    //存所有树的成员
    QList<QTreeWidgetItem*> m_allItem;
private:
    QList<QModelIndex> m_checkList;
    //树标准实体表
    QList<TreeNode> m_nodeList;
    //群组实体表（包含没有节点服务器的组）
    QList<QTreeWidgetItem*> m_groupList;
    QStringList m_checkUuid;
    QStringList m_headTextList;
    QList<int> m_current;
    //样式路径
    QString m_stylePath;
    bool m_checkBoxFlg;
    //只是触发一次itemChange信号
    bool m_signalOnlyOne;
    //保存更改前的鼠标设置
    QCursor m_oldCur;
    //保存不能移动鼠标的设置
    QCursor m_newCur;

    //开始拖拽时鼠标的位置
    QPoint m_startDragPoint;
    //拖拽信息的图片
    QPixmap m_pixMap;
    //拖拽时鼠标与拖拽信息的的相对位置
    QPoint m_dis;
};

#endif // TREE_H
