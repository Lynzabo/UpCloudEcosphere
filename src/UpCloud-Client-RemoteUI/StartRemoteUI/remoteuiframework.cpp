#include "remoteuiframework.h"
#include "ui_remoteuiframework.h"
#include <QCloseEvent>
#include <QDesktopWidget>
#include "actionregistry.h"
#include "baseiremote.h"
RemoteUIFrameWork::RemoteUIFrameWork(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RemoteUIFrameWork)
{
    ui->setupUi(this);
    //设置在子窗口关闭时销毁这个类的对象
    setAttribute(Qt::WA_DeleteOnClose);
    //初始化应用程序
    initApp();
    //初始窗口时读取窗口设置信息
    readSettings();
    //初始化窗口基本数据
    initWindow();
    //准备工作
    initToWork();
    startupScheduler();
}

RemoteUIFrameWork::~RemoteUIFrameWork()
{
    delete ui;
#ifdef STYLE_DEBUG
    qssWatcher->deleteLater();
#endif
}

void RemoteUIFrameWork::closeEvent(QCloseEvent *closeEvent)
{
    if(false)
    {
        closeEvent->ignore();
    }
    else
    {
        //在关闭前写入窗口设置
        writeSettings();
        remoteUIWorkThread->deleteLater();
        emit
        destoryApp();
    }
    //done(1);
    this->deleteLater();
}

bool RemoteUIFrameWork::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::MouseButtonDblClick) {
        this->on_btn_menu_max_clicked();
        return true;
    }
    return QObject::eventFilter(obj, event);
}

void RemoteUIFrameWork::mouseMoveEvent(QMouseEvent *e)
{
    if (mousePressed && (e->buttons() && Qt::LeftButton) && !max) {
        this->move(e->globalPos() - mousePoint);
        e->accept();
    }
}

void RemoteUIFrameWork::mousePressEvent(QMouseEvent *e)
{
    if (e->button() == Qt::LeftButton) {
        mousePressed = true;
        mousePoint = e->globalPos() - this->pos();
        e->accept();
    }
}

void RemoteUIFrameWork::mouseReleaseEvent(QMouseEvent *)
{
    mousePressed = false;
}

void RemoteUIFrameWork::initWindow()
{
    //设置窗体标题栏隐藏
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowMinMaxButtonsHint);
    max = false;
    location = this->geometry();
    max = false;
    mousePressed = false;

    //安装事件监听器,让标题栏识别鼠标双击
    ui->label_title->installEventFilter(this);
    //安装事件监听器,让标题栏识别鼠标双击
    ui->w_header->installEventFilter(this);

    //设置菜单
    main_menu = new MainMenu();
    //  connect(main_menu, SIGNAL(showSettingDialog()), this, SLOT(showSettingDialog()));
    //	connect(main_menu, SIGNAL(showNewCharacter()), this, SLOT(showNewCharacter()));
    //	connect(main_menu, SIGNAL(showAboutUs()), this, SLOT(showAboutUs()));

    //工具栏
    QStringList string_list;
    string_list<<":/core/imgs/imgs/ddmi"<<":/core/imgs/imgs/ommi";
    ui->clb_ddmi->setBtnPixmap(string_list.at(0));
    ui->clb_ddmi->setText(tr("数据分发"));
    ui->clb_ommi->setBtnPixmap(string_list.at(1));
    ui->clb_ommi->setText(tr("运维监控"));
    signalMapper = new QSignalMapper(this);
    connect(ui->clb_ddmi, SIGNAL(clicked()), signalMapper, SLOT(map ()));
    signalMapper->setMapping (ui->clb_ddmi, ui->clb_ddmi->objectName());
    connect(this->ui->clb_ommi, SIGNAL(clicked()), signalMapper, SLOT(map ()));
    signalMapper->setMapping (ui->clb_ommi, ui->clb_ommi->objectName());
    connect(signalMapper, SIGNAL(mapped (const QString &)), this, SLOT(doModulesClick(const QString &)));
    //功能单选设置
    bg_toolsFuncs = new QButtonGroup(this);
    ui->clb_ddmi->setCheckable(true);
    bg_toolsFuncs->addButton(ui->clb_ddmi);
    ui->clb_ommi->setCheckable(true);
    bg_toolsFuncs->addButton(ui->clb_ommi);
}

void RemoteUIFrameWork::readSettings()
{
    QSettings *settings = new QSettings;
    QPoint pos = settings->value("pos", QPoint(500, 100)).toPoint();
    //QSize size = settings->value("size", QSize(1024, 600)).toSize();
    move(pos);
    resize(QSize(1024, 600));
    settings->deleteLater();
}

void RemoteUIFrameWork::writeSettings()
{
    QSettings *settings = new QSettings;
    //写入位置信息
    settings->setValue("pos", pos());
    //写入大小信息
    settings->setValue("size", size());
    settings->deleteLater();
}

void RemoteUIFrameWork::initToWork()
{
    //防止后面代码执行时间过长,界面出现假死现象
    QElapsedTimer et;
    et.start();
    while(et.elapsed()<300)
    {
        //告诉Qt先处理那些还没有被处理的各类事件，然后再把控制权返还给调用者
        QCoreApplication::processEvents();
    }
    //调取器
    //初始化任务调度器,移交调度器到线程中工作
    taskScheduler = new RemoteUITaskScheduler;
    //准备连接中心服务器
    connect(taskScheduler,&RemoteUITaskScheduler::evt_connectToServerInit,this,&RemoteUIFrameWork::on_connectToServerInit);
    //连接中心服务成功
    connect(taskScheduler,&RemoteUITaskScheduler::evt_connectToServerSuccess,this,&RemoteUIFrameWork::on_connectToServerSuccess);
    remoteUIWorkThread = new QThread(this);
    connect(remoteUIWorkThread,&QThread::started,taskScheduler,&RemoteUITaskScheduler::startup);
    connect(remoteUIWorkThread,&QThread::finished,taskScheduler,&RemoteUITaskScheduler::deleteLater);
    //任务调度器与UI绑定广播

    taskScheduler->moveToThread(remoteUIWorkThread);
    //remoteUIWorkThread->start(QThread::HighPriority);
}

void RemoteUIFrameWork::startupScheduler()
{
    UIHelper::showLoading(ui->sw_module_content,tr("准备网络环境"));
    //延时10ms开启任务调取器
    QTimer::singleShot(10, this, SLOT(startToWork()));
}

void RemoteUIFrameWork::openToolFunc(RemoteUIFrameWork::Modules module)
{
    if(module == RemoteUIFrameWork::DDMI)
    {
        emit
            ui->clb_ddmi->click();
    }
    else if(module == RemoteUIFrameWork::OMMI)
    {
        emit
            ui->clb_ommi->click();
    }
}
#ifdef STYLE_DEBUG
void RemoteUIFrameWork::on_reloadStyle(const QString &path)
{
    QFile file(path);
    bool ok = file.open(QIODevice::ReadOnly);
    if(!ok) {
        qDebug() <<trs("读取样式文件失败");
        return;
    }
    QString sheet = QLatin1String(file.readAll());
    qApp->setStyleSheet(sheet);
}
#endif
void RemoteUIFrameWork::startToWork()
{
    //开启任务调度器工作线程,任务调度器开始工作
    remoteUIWorkThread->start();
    //阻塞调度器线程10ms,让给CPU 10ms时间去更新UI
    remoteUIWorkThread->wait(10);
}

void RemoteUIFrameWork::on_btn_menu_min_clicked()
{
    this->showMinimized();
}

void RemoteUIFrameWork::on_btn_menu_max_clicked()
{
    if (max) {
        this->setGeometry(location);
        ui->btn_menu_max->setIcon(QIcon(":/core/imgs/imgs/window_max"));
        ui->btn_menu_max->setToolTip(tr("最大化"));
    } else {
        location = this->geometry();
        this->setGeometry(qApp->desktop()->availableGeometry());
        ui->btn_menu_max->setIcon(QIcon(":/core/imgs/imgs/window_red"));
        ui->btn_menu_max->setToolTip(tr("还原"));
    }
    max = !max;
}

void RemoteUIFrameWork::on_btn_menu_close_clicked()
{
    QCloseEvent *event = new QCloseEvent;
    qApp->postEvent(this,event);
    qApp->exit();
}

void RemoteUIFrameWork::on_btn_menu_set_clicked()
{
    //设置主菜单出现的位置
    QPoint p = rect().topRight();
    p.setX(p.x() - ui->w_opera->width());
    p.setY(p.y() + ui->btn_menu_set->height());
    main_menu->exec(this->mapToGlobal(p));
}

void RemoteUIFrameWork::on_destoryApp()
{
    //释放远程UI全双工工作工厂
    RemoteUIRegistry::releaseDuplexFactory();
    //释放全局对象
    RemoteUIRegistry::releaseGlobalObject();
    qDebug() << trs("Exit Application");
    //    this->close();
}

void RemoteUIFrameWork::doModulesClick(const QString &btnname)
{
    if(btnname.isEmpty())
    {
        return;
    }
    //数据分发
    if(btnname==ui->clb_ddmi->objectName())
    {
        ui->clb_ddmi->setChecked(true);
        //打开非结构化任务列表
        UIHelper::OpenInTop(this,new DDMIModuleUI(this),QString("sw_module_content"));
    }
    //运维监控
    if(btnname==ui->clb_ommi->objectName())
    {
        ui->clb_ommi->setChecked(true);
        //打开非结构化任务列表
        UIHelper::OpenInTop(this,new OMMIModuleUI(this),QString("sw_module_content"));
    }
}

void RemoteUIFrameWork::seeDDMIStatus(const QString &unstructTaskUUID, const QString &structTaskUUID)
{
    /*ui->btn_unstruct->hide();
    ui->btn_struct->hide();
    ui->btn_schedule->hide();
    ui->btn_sysmanagement->hide();
    QPushButton *btn_unstructTaskDetail = new QPushButton(ui->w_funcs);
    btn_unstructTaskDetail->setObjectName(QStringLiteral("btn_unstructTaskDetail"));
    btn_unstructTaskDetail->setCheckable(false);
    btn_unstructTaskDetail->setChecked(false);
    btn_unstructTaskDetail->setFlat(true);
    btn_unstructTaskDetail->setText(tr("非结构化任务信息"));
    ui->hl_funcs->insertWidget(0,btn_unstructTaskDetail);
    connect(btn_unstructTaskDetail, SIGNAL(clicked()), signalMapper, SLOT(map ()));
    signalMapper->setMapping (btn_unstructTaskDetail, btn_unstructTaskDetail->objectName());
    seeUnstructTaskUUID = unstructTaskUUID;

    QPushButton *btn_structTaskDetail = new QPushButton(ui->w_funcs);
    btn_structTaskDetail->setObjectName(QStringLiteral("btn_structTaskDetail"));
    btn_structTaskDetail->setCheckable(false);
    btn_structTaskDetail->setChecked(false);
    btn_structTaskDetail->setFlat(true);
    btn_structTaskDetail->setText(tr("结构任务信息"));
    ui->hl_funcs->insertWidget(1,btn_structTaskDetail);
    connect(btn_structTaskDetail, SIGNAL(clicked()), signalMapper, SLOT(map ()));
    signalMapper->setMapping (btn_structTaskDetail, btn_unstructTaskDetail->objectName());
    seeStructTaskUUID = structTaskUUID;
    EditUnstructWidget *eUWidget = new EditUnstructWidget(this);
    eUWidget->setTaskUUID(seeUnstructTaskUUID);
    EditStructWidget *eSWidget = new EditStructWidget(this);
    eSWidget->setTaskUUID(seeStructTaskUUID);
    //TODO 这个有必要在这加吗？
    DIRNodesGroupWidget* dgWidget  = new DIRNodesGroupWidget(this);
    DirDictWidget* dDwidget = new DirDictWidget(this);
    //UIHelper::OpenInSelf(this,eUWidget);
    ui->sw_content->addWidget(eUWidget);
    ui->sw_content->addWidget(eSWidget);
    //TODO 这个有必要在这加吗？
    ui->sw_content->addWidget(dgWidget);
    ui->sw_content->addWidget(dDwidget);
    ui->sw_content->setCurrentWidget(eUWidget);*/
}

void RemoteUIFrameWork::closeRemoteUI()
{
    QCloseEvent *event = new QCloseEvent;
    qApp->postEvent(this,event);
    delete this;
}

void RemoteUIFrameWork::on_connectToServerSuccess()
{
    UIHelper::showLoading(ui->sw_module_content,tr("连接服务器成功!"));
    UIHelper::hideLoading(ui->sw_module_content);
    //默认打开非结构化任务列表
//    ui->btn_unstruct->setChecked(true);
//    UIHelper::OpenInSelf(this,new DirUnstructWidget(this));
    //设置默认打开数据分发模块
    openToolFunc(RemoteUIFrameWork::DDMI);
}

void RemoteUIFrameWork::on_connectToServerInit(const QString &ip, const quint16 &port)
{
    UIHelper::showLoading(ui->sw_module_content,tr("连接服务:[IP:%1,Port:%2]...").arg(ip).arg(port));
}

void RemoteUIFrameWork::initApp()
{
    //初始化设置应用目录
    RUAbstPath::getInstance().setApplicationRootDir(QString("c:/UpCloud-package/RemoteUI"));
    //注册系统日志自定义格式监听器
    RemoteUIRegistry::registerSystemLogger();
    //动态注册请求响应
    RemoteUIRegistry::registerActions();
    //动态注册定时主推服务
    RemoteUIRegistry::registerTimers();
    //注册远程UI客户端线程池控制服务
    RemoteUIRegistry::registerGlobalThreadsPool();
    //注册远程UI全双工工作工厂
    RemoteUIRegistry::registerDuplexFactory();

    //    QCoreApplication::addLibraryPath(QCoreApplication::applicationDirPath());
    //    QCoreApplication::addLibraryPath(QString("platforms"));
    qApp->setOrganizationName(QString(UPCLOUD_REMOTEUI_ORGANIZATIONNAME));
    qApp->setOrganizationDomain(QString(UPCLOUD_REMOTEUI_ORGANIZATIONDOMAIN));
    qApp->setApplicationName(QString(UPCLOUD_REMOTEUI_APPLICATIONNAME));
    qApp->setApplicationVersion(QString(UPCLOUD_REMOTEUI_APPLICATIONVERSION));


    //    QIcon icon;
    //    icon.addPixmap(QPixmap(":/logo_16.png"));
    //    icon.addPixmap(QPixmap(":/logo_32.png"));
    //    icon.addPixmap(QPixmap(":/logo_48.png"));
    //    icon.addPixmap(QPixmap(":/logo_64.png"));
    //    icon.addPixmap(QPixmap(":/logo_128.png"));
    //    icon.addPixmap(QPixmap(":/logo_256.png"));
    //    QApplication::setWindowIcon(icon);
    //    QFontDatabase::addApplicationFont("://DejaVuSans.ttf");
    QFont font;
    if (QLocale::system().country() == QLocale::China)
        font.setFamily(QString("Microsoft Yahei"));
    else
        font.setFamily(QString("Segoe UI"));
    font.setPointSize(96);//DPI
    font.setPixelSize(24);//font size
    qApp->setFont(font);
    //设置Application主题
    QFile *cssFile = new QFile(":/core/qss/qss/core");
    cssFile->open(QFile::ReadOnly);
    qApp->setStyleSheet(QLatin1String(cssFile->readAll()));
    delete cssFile;
    //设置应用整体调色板颜色
    qApp->setPalette(QPalette(QColor("#F0F0F0")));

    try
    {
        //初始化本机固定码
        TerminalUUIDUtil::getInstance().init();

        //初始化报文工具
        DatagramUtil::getInstance().init();
    }
    catch(QString &error)
    {
        this->close();
        UIHelper::ShowMessageBoxError(QObject::tr("启动失败,%1").arg(error));
    }
#ifdef STYLE_DEBUG
    //监控样式文件变化
    qssWatcher = new QFileSystemWatcher(this);
    qssWatcher->addPath("D:/UpCloudEcosphere_2/UpCloud-Client-RemoteUI/StartRemoteUI/common/qss/core.css");
    //监控样式文件修改
    connect(qssWatcher,SIGNAL(fileChanged(QString)),this,SLOT(on_reloadStyle(QString)));
#endif
    connect(this,&RemoteUIFrameWork::destoryApp,this,&RemoteUIFrameWork::on_destoryApp);
}
