#ifndef REMOTEUIFRAMEWORK_H
#define REMOTEUIFRAMEWORK_H

#include <QtCore>
#include <QDialog>
#include <QAxBindable>
#include "netiremoteui.h"
#include "modules/common/mainmenu.h"
#include "modules/common/uihelper.h"
#include "ddmimoduleui.h"
#include "ommimoduleui.h"
namespace Ui {
class RemoteUIFrameWork;
}

class RemoteUIFrameWork : public QDialog, public QAxBindable
{
    Q_OBJECT
    Q_PROPERTY(QString userUUID READ getUserUUID WRITE setUserUUID )
public:
    /**
     * @brief The Modules enum  模块类型
     */
    enum Modules
    {
        DDMI,
        OMMI
    };
    explicit RemoteUIFrameWork(QWidget *parent = 0);
    ~RemoteUIFrameWork();
    QString getUserUUID() const
    {
        return this->curUserUUID;
    }
signals:
    //销毁客户端
    void destoryApp();
protected:
    void closeEvent(QCloseEvent *closeEvent);
    bool eventFilter(QObject *obj, QEvent *event);
    void mouseMoveEvent(QMouseEvent *e);
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *);
private slots:
    void on_btn_menu_min_clicked();

    void on_btn_menu_max_clicked();

    void on_btn_menu_close_clicked();
    /**
     * @brief startToWork  让任务调度器开始工作
     */
    void startToWork();
    /**
     * @brief on_btn_menu_set_clicked   显示主菜单
     */
    void on_btn_menu_set_clicked();
    /**
     * @brief on_destoryApp 销毁App
     */
    void on_destoryApp();
    /**
     * @brief doModulesClick   模块区按钮点击
     * @param btnname
     */
    void doModulesClick(const QString & btnname);
    //Escript接口定义
public slots:
    void setUserUUID(const QString &userID )
    {
        if ( !requestPropertyChange( "userUUID" ) )
            return;
        curUserUUID = userID;
        propertyChanged( "userUUID" );
    }
    /**
     * @brief seeDDMIStatus 查看下发状态
     * @param unstructTaskUUID
     * @param structTaskUUID
     */
    void seeDDMIStatus(const QString &unstructTaskUUID,const QString &structTaskUUID);
    /**
     * @brief closeRemoteUI 关闭客户端
     */
    void closeRemoteUI();


public slots:

    /**
     * @brief on_connectToServerSuccess 连接中心服务成功
     */
    void on_connectToServerSuccess();
    /**
     * @brief on_connectToServerInit    连接服务
     * @param ip
     * @param port
     */
    void on_connectToServerInit(const QString &ip,const quint16 &port);
#ifdef STYLE_DEBUG
    /**
     * @brief on_reloadStyle 重新加载样式文件
     */
    void on_reloadStyle(const QString &path);
#endif
private:
    /**
     * @brief initApp   初始化系统
     */
    void initApp();
    /**
     * @brief initWindow    初始化窗口基本数据
     */
    void initWindow();
    /**
     * @brief readSettings  读取窗口设置
     */
    void readSettings();
    /**
     * @brief writeSettings 写入窗口设置
     */
    void writeSettings();
    /**
     * @brief initToWork    准备工作
     */
    void initToWork();
    /**
     * @brief startupScheduler   开始任务调取器
     */
    void startupScheduler();
    /**
     * @brief openToolFunc  打开工具
     */
    void openToolFunc(RemoteUIFrameWork::Modules module);
private:
    Ui::RemoteUIFrameWork *ui;

    QPoint mousePoint;
    bool mousePressed;
    bool max;
    QRect location;
    RemoteUITaskScheduler *taskScheduler;
    QThread *remoteUIWorkThread;
    //主菜单
    MainMenu *main_menu;
    //功能按钮信号处理映射器
    QSignalMapper *signalMapper;
    //当前用户UUID
    QString curUserUUID;
    QString seeUnstructTaskUUID,seeStructTaskUUID;
    QFileSystemWatcher* qssWatcher;
    QButtonGroup *bg_toolsFuncs;
};

#endif // REMOTEUIFRAMEWORK_H
