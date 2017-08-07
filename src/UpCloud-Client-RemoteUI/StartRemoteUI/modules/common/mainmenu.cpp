#include "mainmenu.h"

MainMenu::MainMenu(QWidget *parent) : QMenu(parent)
{
    this->setObjectName("menu");
    this->createActions();
}

void MainMenu::createActions()
{
    //创建菜单项
    action_setting = new QAction(this);
    action_setting->setText(tr("设置"));

    action_new_character = new QAction(this);
    action_new_character->setText(tr("新的功能"));

    action_check_update = new QAction(this);
    action_check_update->setText(tr("更新"));

    action_about_us = new QAction(this);
    action_about_us->setText(tr("关于我们"));

    //添加菜单项
    this->addAction(action_setting);
    this->addAction(action_new_character);
    this->addAction(action_check_update);
    this->addSeparator();
    this->addAction(action_about_us);


    //设置信号连接
    connect(action_setting, SIGNAL(triggered()), this, SIGNAL(showSettingDialog()));
    connect(action_new_character, SIGNAL(triggered()), this, SIGNAL(showNewCharacter()));
    connect(action_about_us, SIGNAL(triggered()), this, SIGNAL(showAboutUs()));

}
void MainMenu::showPage()
{
    QObject *object = QObject::sender();
    QAction *action = qobject_cast<QAction *>(object);
    QString object_name = action->objectName();
    int index = object_name.toInt();
    QString page;
    switch(index)
    {
    case 1:
        page = QString("http://bbs.360.cn/cms/guide.html");
        break;

    case 2:
        page = QString("http://bbs.360safe.com/forum.php?mod=forumdisplay&fid=100");
        break;

    case 3:
        page = QString("http://www.360.cn/");
        break;

    case 4:
        page = QString("http://www.360.cn/privacy/v2/index.html");
        break;

    default:
        break;
    }

     QUrl url(page);
     QDesktopServices::openUrl(url);
}
