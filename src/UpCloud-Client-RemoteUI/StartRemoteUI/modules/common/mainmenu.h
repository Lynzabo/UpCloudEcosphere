#ifndef MAINMENU_H
#define MAINMENU_H

#include <QMenu>
#include <QDesktopServices>
#include <QUrl>

class MainMenu : public QMenu
{
    Q_OBJECT
public:
    explicit MainMenu(QWidget *parent = 0);
private:
    /**
     * @brief createActions 创建动作
     */
    void createActions();
private:
    //设置
    QAction *action_setting;
    //新版特性
    QAction *action_new_character;
    //检查更新
    QAction *action_check_update;
    //切换为企业版
    QAction *action_change_company;
    //在线帮助
    QAction *action_help_online;
    //论坛求助
    QAction *action_platform_help;
    //360网站
    QAction *action_login_home;
    //隐私保护
    QAction *action_protect;
    //关于我们
    QAction *action_about_us;
signals:
    void showSettingDialog();
    void showNewCharacter();
    void showAboutUs();

public slots:

private slots:
    void showPage();
};

#endif // MAINMENU_H
