#ifndef GROUPTREE_H
#define GROUPTREE_H
#include <QtCore>
#include "modules/common/tree.h"
#include "../../UpCloud-Service-Center/BusinessIServer/BasalIServer/bean/cscgroup.h"
#include "../../UpCloud-Service-Center/BusinessIServer/BasalIServer/bean/vcscgroupassoc.h"
#include <QMenu>
#include <QAction>
#include <QComboBox>


class GroupTree : public Tree
{
    Q_OBJECT
public:
    GroupTree(QWidget* widget = 0);
    ~GroupTree();
    //加载实体信息并转化基类的标准实体
    QList<CsClientGroup> groupList() const;
    void setGroupList(const QList<CsClientGroup> &groupList);
     CsClientGroup getGroupByUuid(const QString &uuid);

    QList<VCsClientGroupAssoc> groupAssocList() const;
    void setGroupAssocList(const QList<VCsClientGroupAssoc> &groupAssocList);
    VCsClientGroupAssoc getGroupAssocByUuid(const QString &uuid);

    //初始化树
    void initGroupTree();
    //显示菜单
    void showNodeMenu();
    void showGroupMenu();

    QString getUuid(QTreeWidgetItem* item);
    //获取子节点的个数
    int getChildCount(QTreeWidgetItem* item);
    //获取子节点中子组的个数
    int getChildGroupCount(QTreeWidgetItem* item);

    // 获取子节点中所有的节点服务器UUID（不包含孙子辈，只在所有儿子中判断）
    QStringList getChildNode(QTreeWidgetItem* item);
    //获取实体对象
    void setparamsX(QVariantMap &paramsMap,QTreeWidgetItem* item);
    void setNodeParams(QVariantMap &params, QTreeWidgetItem* item);
    QTreeWidgetItem* getItemfromIndex(QModelIndex index);
    void setGroupParams(QVariantMap &params,QTreeWidgetItem* item);
    void setParamsY(QVariantMap &paramsMap,QTreeWidgetItem* item);

private:
    //加载所有的菜单信息
    void loadMenu();
    //映射为基类标准实体
     void mapGroupToTreeNode(QList<TreeNode> &list,const QList<CsClientGroup> &groupList);
    void mapGroupAssocToTreeNode(QList<TreeNode> &list, const QList<VCsClientGroupAssoc> &groupAssocList);
private:
    QList<CsClientGroup> m_groupList;
    QHash<QString,CsClientGroup> m_uuidToGroupHash;

    QList<VCsClientGroupAssoc> m_groupAssocList;
    QHash<QString,VCsClientGroupAssoc> m_uuidToGroupAssocHash;
    //节点操作菜单
    QMenu* node_menu;
    QAction* node_move;
    QAction* node_del;
    QAction* node_setUse;

    //组（父节点）操作菜单
    QMenu* group_menu;
    QAction* group_addGroup;
    QAction* group_editGroup;
    QAction* group_setUse;
    QAction* group_delGroup;
    QAction* group_move;
    QAction* group_addNode;
    QAction* group_delAllNodes;


};

#endif // GROUPTREE_H
