#include "funcsmenu.h"

FuncsMenu::FuncsMenu(QWidget *parent) : QMenu(parent)
{
    this->setObjectName("funcMenu");
    this->createActions();
}

void FuncsMenu::createActions()
{
    //创建菜单项
    action_sgroup = new QAction(this);
    action_sgroup->setObjectName("a_nodergroup");
    action_sgroup->setText(tr("节点服务群组管理"));
    action_sdict = new QAction(this);
    action_sdict->setObjectName("a_dict");
    action_sdict->setText(tr("字典维护管理"));

    //添加菜单项
    this->addAction(action_sgroup);
    this->addSeparator();
    this->addAction(action_sdict);
}
