#ifndef DIRNODESGROUPWIDGET_H
#define DIRNODESGROUPWIDGET_H

#include <QWidget>
#include <QEvent>
#include "base.h"
#include "avro.h"
#include "duplex.h"
#include "baseiremote.h"
#include "grouptree.h"
#include "editgroupwidget.h"
#include "../../UpCloud-Service-Center/BusinessIServer/BasalIServer/bean/cscgroup.h"
#include "../../UpCloud-Service-Center/BusinessIServer/BasalIServer/bean/cscextendinfo.h"
#include "../../UpCloud-Service-Center/BusinessIServer/BasalIServer/bean/vcscgroupassoc.h"
namespace Ui {
class DIRNodesGroupWidget;
}

class DIRNodesGroupWidget : public QWidget
{
    Q_OBJECT

public:
    enum GroupType{
        Group_GROUP,
        Group_NODE
    };
    explicit DIRNodesGroupWidget(QWidget *parent = 0);
    ~DIRNodesGroupWidget();
    //添加群组的树形数据
    void setGroup();
    //添加节点服务器的树形数据
    void setGroupAssoc();


    QVariantMap params() const;
    void setParams(const QVariantMap &params);
private slots:
    //菜单槽函数--------------------begin
    void on_moveNode();
    void on_setUseNode();
    void on_delNode();

    void on_addGroup();
    void on_editGroup();
    void on_setUseGroup();
    void on_moveGroup();
    void on_delGroup();
    void on_addNode();
    void on_delAllNodes();
    //菜单槽函数--------------------end
    ////下列函数为菜单槽函数中转槽函数
    //菜单移动节点
    void on_moveNodeForTree();
    //菜单移动组
    void on_moveGroupForTree();
    //菜单编辑组
    void on_editGroupForTree();
    //菜单增加组
    void on__addGroupForTree();
    //菜单增加节点服务器
    void on_addNodeForTree();
    //显示菜单
    void on_showMenu(QTreeWidgetItem* item,int column);

    //拖拽槽函数
    void on_moveXToY(const QTreeWidgetItem* x,const QTreeWidgetItem* y);
    void on_itemtaskCallback(const qint32 msgId, const QString &msg);
    void on_itemtaskCallback(const qint32 msgId, const QString &msg, const QList<CsClientGroup> &groupList);
    void on_itemtaskCallback(const qint32 msgId, const QString &msg, const QList<VCsClientGroupAssoc> &nodeList);
private:
    void initWindow();
    void showEvent(QShowEvent * event);

private:
    Ui::DIRNodesGroupWidget *ui;
    //所有节点的树形展示
    GroupTree* m_groupTreeShow;
    //移动节点的树形展示界面
    GroupTree* m_groupTreeSelect;
    //编辑群组的界面
    QWidget* m_editGroup;
    //菜单参数
    QVariantMap m_params;
    //保存菜单参数X的值
    QTreeWidgetItem* m_xItem;
    //移动节点的操作类型
    GroupType m_groupType;
    //保存增加节点服务器的参数 此参数用来保存要增加节点服务器的UUID
    QStringList m_paramsForAddNode;
    //保存删除节点服务器的参数 此参数用来保存要删除节点服务器的UUID
    QStringList m_paramsForDelNode;
    //从数据库中要获取的批次
    quint32 m_pageNum;
};

#endif // DIRNODESGROUPWIDGET_H
