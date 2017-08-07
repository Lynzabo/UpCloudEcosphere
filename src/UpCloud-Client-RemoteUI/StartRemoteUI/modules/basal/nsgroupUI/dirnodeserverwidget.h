#ifndef DIRNODESERVERWIDGET_H
#define DIRNODESERVERWIDGET_H

#include <QWidget>
#include <QMouseEvent>
#include <QtCore>
#include <QListView>
#include <QStandardItemModel>
#include "../FrontBusinessIRemoteUI/BasalOperaIRemoteUI/lcextendinforunnable.h"
#include "../../UpCloud-Service-Center/BusinessIServer/BasalIServer/bean/cscextendinfo.h"

namespace Ui {
class DirNodeServerWidget;
}

class DirNodeServerWidget : public QWidget
{
    Q_OBJECT

public:
    explicit DirNodeServerWidget(QWidget *parent = 0);
    ~DirNodeServerWidget();
    //加载数据到树
    void loadItem(QListView* view,const QList<CsClientExtendInfo> &exList);

    void moveItemToRight();
    void moveItemToLeft();
    void setParamsInfo(QStringList * paramsForAdd, QStringList *paramsForDel);
    void setExistedNodeList(const QStringList &nodeList);
signals:
    void evt_ok();
protected:
    void mouseMoveEvent(QMouseEvent *e);
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *);
private slots:
    void on_btn_right_move_clicked();

    void on_btn_right_moveAll_clicked();

    void on_btn_ok_clicked();

    void on_btn_quit_clicked();
    //模糊查询节点服务器列表
    void on_l_left_find_textChanged(const QString &arg1);

    void on_itemtaskCallback(const qint32 msgId, const QString &msg, const QList<CsClientExtendInfo> &exList);
    void on_l_right_find_textChanged(const QString &arg1);

    void on_btn_left_move_clicked();

    void on_btn_left_allMove_clicked();

    void on_btn_menu_cancel_clicked();

private:
    void showEvent(QShowEvent *event);
    void initWindow();
private:
    Ui::DirNodeServerWidget *ui;
    QList<CsClientExtendInfo> m_exList;
    //节点服务器列表
    QList<QString> m_clientList;
    //右移的节点服务器
    QList<QString> m_checkedList;
    //右边要添加的节点列表
    QList<QString> m_addViewList;

    QHash<QString,CsClientExtendInfo> m_hashForBean;
    //保存信息
    QStringList* m_paramsForAdd;
    QStringList* m_paramsForDel;
    //已有节点服务器信息
    QStringList m_oldNodeList;
    QStringList m_newNodeList;
    //右边过虑器设置信息
    QStringListModel* right_strListModel;
    QSortFilterProxyModel* right_proxyModel;
    //左边过虑器设置信息
    QStringListModel* left_strListModel;
    QSortFilterProxyModel* left_proxyModel;

    bool mousePressed;
    QPoint mousePoint;
};

#endif // DIRNODESERVERWIDGET_H
