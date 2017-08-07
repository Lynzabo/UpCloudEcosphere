#ifndef GROUPTREEWIDGET_H
#define GROUPTREEWIDGET_H

#include <QtCore>
#include <QMouseEvent>
#include "tree.h"
#include "../../UpCloud-Service-Center/BusinessIServer/BasalIServer/bean/cscgroup.h"
#include "../../UpCloud-Service-Center/BusinessIServer/BasalIServer/bean/vcscgroupassoc.h"
namespace Ui {
class GroupTreeWidget;
}

class GroupTreeWidget : public QWidget
{
    Q_OBJECT

public:
    explicit GroupTreeWidget(QWidget *parent = 0);
    ~GroupTreeWidget();
    void setParamsForClientUuid(QStringList * params,QStringList* description);
signals:
    void evt_ok();
protected:
    void mouseMoveEvent(QMouseEvent *e);
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *);
private slots:
    void on_itemtaskCallback(const qint32 msgId, const QString &msg, const QList<CsClientGroup> &groupList);
    void on_itemtaskCallback(const qint32 msgId, const QString &msg, const QList<VCsClientGroupAssoc> &nodeList);
    void on_btn_ok_clicked();

    void on_btn_quit_clicked();

    void on_btn_menu_cancel_clicked();

private:
    void layout();
    void initWindow();
    void showEvent(QShowEvent* event);

    void loadGroup();
    void loadGroupAssoc();
    //映射为基类标准实体
     void mapGroupToTreeNode(QList<TreeNode> &list, const QList<CsClientGroup> &groupList);
    void mapGroupAssocToTreeNode(QList<TreeNode> &list,const QList<VCsClientGroupAssoc> &groupAssocList);
private:
    Ui::GroupTreeWidget *ui;
    QList<CsClientGroup> m_groupList;
    QHash<QString,CsClientGroup> m_uuidToGroupHash;

    QList<VCsClientGroupAssoc> m_groupAssocList;
    QHash<QString,VCsClientGroupAssoc> m_uuidToGroupAssocHash;
    Tree* m_tree;
    quint32 m_pageNum;
    //节点服务器的固定码（标识符）
    QStringList* m_paramsForUuids;
    //选中的节点服务器所属群组的描述列表
    QStringList* m_descriptionForGroup;

    bool mousePressed;
    QPoint mousePoint;
};

#endif // GROUPTREEWIDGET_H
