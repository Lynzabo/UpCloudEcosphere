#ifndef FUNCSMENU_H
#define FUNCSMENU_H

#include <QMenu>
#include <QPushButton>
class FuncsMenu : public QMenu
{
    Q_OBJECT
public:
    explicit FuncsMenu(QWidget *parent = 0);
private:
    /**
     * @brief createActions 创建动作
     */
    void createActions();
public:
    //节点服务器群组维护
    QAction *action_sgroup;
    //字典维护
    QAction *action_sdict;
signals:

public slots:
};

#endif // FUNCSMENU_H
