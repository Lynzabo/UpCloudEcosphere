#ifndef DICTTREE_H
#define DICTTREE_H
#include <QtCore>
#include <QTreeWidget>
#include "../../UpCloud-Service-Center/BusinessIServer/BasalIServer/bean/csdict.h"
#include "../FrontBusinessIRemoteUI/BasalOperaIRemoteUI/ldictrunnable.h"

class DictTree : public QTreeWidget
{
    Q_OBJECT
public:
    DictTree(QWidget* widget = 0);
signals:
    void evt_itemClicked(const QString &uuid,const QString &name);
private slots:
    void on_reload();
    void on_addNode(const CsDict &dict);
    void on_delNode(const QList<QString> &uuids);
    void on_doubleClieked(QTreeWidgetItem *item, int column);
    void on_itemClicked(QTreeWidgetItem *item, int column);
    void on_itemtaskCallback(const qint32 msgId, const QString &msg, const QList<CsDict> &taskList);
private:
    void initTree();
    void showEvent(QShowEvent* event);
    void loadTree();
    void loadDatas();
    void loadTreeNode(const CsDict &dict);
private:
    QList<CsDict> m_dictList;
    QWidget* m_parent;
    QHash<QModelIndex,QString> m_indexToUUid;
    QHash<QString,QModelIndex> m_uuidToIndex;
    QHash<QString,CsDict> m_uuidToBean;
    //是不是第一次加载
    bool isFirstLoad;
};

#endif // DICTTREE_H
