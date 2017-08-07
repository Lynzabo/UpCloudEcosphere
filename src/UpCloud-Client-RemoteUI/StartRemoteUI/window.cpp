#include "window.h"
#include "ui_window.h"
#include "avro.h"
#include "duplex.h"
#include "structoperairemoteui.h"
#include "unstructoperairemoteui.h"
#include "basaloperairemoteui.h"
#include "baseiremote.h"
#include <QMessageBox>
using namespace Environment::Datagram::UI_Ctrl::Opera_Type;
using QtJson::JsonObject;
using QtJson::JsonArray;
using namespace Environment::Duplex_Interaction;
using namespace RemoteUIEnvironment;

Window::Window(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Window)
{
    ui->setupUi(this);
    //初始化界面
    initViews();
    //填充初始化数据
    initDatas();
    startupScheduler();
}

Window::~Window()
{
    delete ui;
}



void Window::startToWork()
{
    //开启任务调度器工作线程,任务调度器开始工作
    remoteUIWorkThread->start();
    //阻塞调度器线程10ms,让给CPU 10ms时间去更新UI
    remoteUIWorkThread->wait(10);
}


void Window::closeEvent(QCloseEvent *closeEvent)
{
    emit
    destoryApp();
}
void Window::initViews()
{



}

void Window::initDatas()
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
    remoteUIWorkThread = new QThread(this);
    connect(remoteUIWorkThread,&QThread::started,taskScheduler,&RemoteUITaskScheduler::startup);
    connect(remoteUIWorkThread,&QThread::finished,taskScheduler,&RemoteUITaskScheduler::deleteLater);
    //任务调度器与UI绑定广播

    taskScheduler->moveToThread(remoteUIWorkThread);
    //remoteUIWorkThread->start(QThread::HighPriority);
}

void Window::startupScheduler()
{
    //准备就绪,远程UI准备工作
    ucout(tr("Init UI"));
    //延时10ms开启任务调取器
    QTimer::singleShot(10, this, SLOT(startToWork()));
}

void Window::ucout(const QString str)
{
    ui->textBrowser->append(str);
}


void Window::on_pushButton_clicked()
{
    ui->textBrowser->clear();
}

void Window::on_pushButton_2_clicked()
{
    //查询所有任务
    ucout(tr("Select All tasks"));
    /*
    class DirUnstructTaskRunnable : public QRunnable
    {
    public:
        void run()
        {
            JsonObject objJson;
            objJson["name"] = trs("aa");
            QString params = QtJson::serialize(objJson);

            //1.生成一个消息发送端
            DPSender *sender = UpCloudDuplexFactory::getInstance().createDPSender();
            //2.准备请求数据
            if(!sender)
                return;
            sender->setExecType(Control_Module::Unstruct_listTask);
            sender->setParams(params);
//            sender->setMsg();
            //3.配置额外参数
            //设置该请求5s过期,当过期时,doSendBySync返回0
//            sender->setExpiredTime(5);
            //4.获得结果集
            DPResult *resultSet = sender->doSendBySync(DeplexDefs::Priority::HighPriority);
            if(!resultSet)
                return;

            //5.使用结构集处理响应
            quint8 rState = resultSet->getRState();
            QString result = resultSet->getRContent();
            //访问地址无效
            if(rState == Data_Authority::_2)
            {
                qDebug() << Data_Authority::_2_DESC_AddrIsInvalid;
            }
            //未授权访问地址
            else if(rState == Data_Authority::_1)
            {
                qDebug() << Data_Authority::_1_DESC_Unauthorized;
            }
            //
            else if(rState == Data_Authority::_0)
            {
                //qDebug() << "响应的反序列化";
                bool ok;
                JsonObject resultObj = QtJson::parse(result, ok).toMap();
                if (!ok) {
                    qDebug("解析出错");
                }

                qDebug() << "taskNum:" << resultObj["taskNum"].toInt();
                qDebug() << "taskString:" << resultObj["taskString"].toString();
                qDebug() << "taskBool:" << resultObj["use_space"].toBool();
            }

            //6.销毁消息发送端,注意,该动作不能省略,并且释放完了后不需要delete sender指针
            sender->destory();
        }
    };*/
    //
    QThreadPool::globalInstance()->start(new DirUnstructTaskRunnable);
}

void Window::on_pushButton_4_clicked()
{
   ListUnstructAddrRunnable* list = new ListUnstructAddrRunnable;
   QString taskuuid;
   taskuuid = "";
   list->setTaskUUID(taskuuid);
   QThreadPool::globalInstance()->start(list);
}
void Window::on_ReceiveMsg()
{
    qDebug() << "on_ReceiveMsg";
}

void Window::on_itemtaskCallback(const qint32 msgId, const QString &msg, const QList<CsRStructSendFiles> &taskList)
{
    int i = 0 ;
    for(i = 0;i < taskList.size(); ++i) {
       on_itemtaskCallback(msgId,msg,taskList.at(i));
    }
}

void Window::on_itemtaskCallback(const qint32 msgId, const QString &msg, const CsRStructSendFiles &task)
{
    if(msgId != CallbackStatus::Struct::_0){
        QString error = QObject::trUtf8(qPrintable(msg));
        QMessageBox::warning(this,tr("Waring"),error,QMessageBox::Ok);
    }
    else {
        ucout(task.getUuid());
        ucout(task.getFileName());
        ucout(task.getDownUrl());
        ucout(task.getFileDestName());
        ucout(task.getSaveAbst());
        ucout(QString::number(task.getSequence()));
        ucout(task.getTaskUuid());
    }
}

void Window::on_itemtaskCallback(const qint32 msgId, const QString &msg, const QList<CsRStructSendAddr> &taskList)
{

    int i = 0 ;
    for(i = 0;i < taskList.size(); ++i) {
       on_itemtaskCallback(msgId,msg,taskList.at(i));
    }
}

void Window::on_itemtaskCallback(const qint32 msgId, const QString &msg, const CsRStructSendAddr &task)
{
    if(msgId != CallbackStatus::Struct::_0){
        QString error = QObject::trUtf8(qPrintable(msg));
        QMessageBox::warning(this,tr("Waring"),error,QMessageBox::Ok);
    }
    else {
        QString str = task.getError();
        if(str.isEmpty()) {
            str = "normal";
        }
        ucout(task.getUuid());
        ucout(task.getClientUuid());
        ucout(QString::number(task.getState()));
        ucout(str);
        ucout(task.getTaskUuid());
    }
}

void Window::on_itemtaskCallback(const qint32 msgId, const QString &msg, const CsRStructTask &task)
{
    if(msgId != CallbackStatus::Struct::_0){
        QString error = QObject::trUtf8(qPrintable(msg));
        QMessageBox::warning(this,tr("Waring"),error,QMessageBox::Ok);
    }
    else {
        ucout(task.getUuid());
        ucout(task.getTaskName());
        ucout(QString::number(task.getTaskNum()));
        ucout(task.getDescription());
        ucout(task.getSendTime());
        ucout(task.getExecTime());
        ucout(QString::number(task.getStrategy()));
        ucout(QString::number(task.getState()));
        ucout(task.getInsertor());
        ucout(task.getInsertTime());
        ucout(task.getOperater());
        ucout(task.getOperaTime());

    }
}

void Window::on_itemtaskCallback(const qint32 msgId, const QString &msg, const QList<CsRStructTask> &taskList)
{

        int i = 0 ;
        for(i = 0;i < taskList.size(); ++i) {
           on_itemtaskCallback(msgId,msg,taskList.at(i));
        }

}

void Window::on_itemtaskCallback(const qint32 msgId, const QString &msg, const QList<CsClientGroupAssoc> &taskList)
{
    if(msgId != CallbackStatus::Basal::_0) {
        QString error = QObject::trUtf8(qPrintable(msg));
        QMessageBox::warning(this,tr("Warning"),error,QMessageBox::Ok);
    }
    else {

        CsClientGroupAssoc task;
        for(QList<CsClientGroupAssoc>::const_iterator item = taskList.begin();item != taskList.end();++item) {
            task = *item;
            ucout("新的信息如下");
            ucout(task.getUuid());
            ucout(task.getClientUuid());
            ucout(task.getGroupUuid());
            ucout(task.getInsertor());
            ucout(task.getInsertTime());
        }
    }
}

void Window::on_itemtaskCallback(const qint32 msgId, const QString &msg, const QList<CsClientGroup> &taskList)
{
    if(msgId != CallbackStatus::Basal::_0) {
        QString error = QObject::trUtf8(qPrintable(msg));
        QMessageBox::warning(this,tr("Warning"),error,QMessageBox::Ok);
    }
    else {

        CsClientGroup task;
        for(QList<CsClientGroup>::const_iterator item = taskList.begin();item != taskList.end();++item) {
            task = *item;
            ucout("新的信息如下");
            ucout(task.getUuid());
            ucout(task.getName());
            ucout(task.getDescription());
            ucout(task.getSupUuid());
            ucout(QString::number(task.getSequence()));
            ucout(QString::number(task.getState()));
            ucout(task.getInsertor());
            ucout(task.getInsertTime());
            ucout(task.getOperater());
            ucout(task.getOperatTime());
        }
    }
}

void Window::on_itemtaskCallback(const qint32 msgId, const QString &msg, const QList<CsDict> &taskList)
{
    if(msgId != CallbackStatus::Basal::_0) {
        QString error = QObject::trUtf8(qPrintable(msg));
        QMessageBox::warning(this,tr("Warning"),error,QMessageBox::Ok);
    }
    else {
        CsDict task;
        for(QList<CsDict>::const_iterator item = taskList.begin();item != taskList.end();++item) {
            task = *item;
            ucout(QObject::trUtf8("新的信息如下"));
            ucout(task.getUuid());
            ucout(task.getCode());
            ucout(task.getName());
            ucout(task.getDescription());
            ucout(QString::number(task.getSequence()));
            ucout(task.getSupUuid());
            ucout(QString::number(task.getState()));
            ucout(task.getInsertor());
            ucout(task.getInsertTime());
            ucout(task.getOperater());
            ucout(task.getOperaTime());
        }
    }
}

void Window::on_itemtaskCallback(const qint32 msgId, const QString &msg, const CsRUnstructSendFiles &task)
{
    //如果出错,提示出错信息
    if(msgId != CallbackStatus::Unstruct::_0){
        QString error = QObject::trUtf8(qPrintable(msg));
        QMessageBox::warning(this,tr("Warning"),error,QMessageBox::Ok);
    }
    else {
        ucout(task.getUuid());
        ucout(task.getTaskUuid());
        ucout(task.getDownUrl());
        ucout(task.getFileDestName());
        ucout(task.getFileName());
        ucout(task.getSaveAbst());
    }
}

void Window::on_itemtaskCallback(const qint32 msgId, const QString &msg, const QList<CsRUnstructSendFiles> &taskList)
{
    int i =0;
    for(i = 0;i < taskList.size(); ++i) {
        on_itemtaskCallback(msgId,msg,taskList.at(i));
    }
}

void Window::on_itemtaskCallback(const qint32 msgId, const QString &msg, const CsRUnstructSendAddr &task)
{
    //如果出错,提示出错信息
    if(msgId != CallbackStatus::Unstruct::_0)
    {
        QString error = QObject::trUtf8(qPrintable(msg));
        QMessageBox::warning(this,tr("Warning"),error,QMessageBox::Ok);
    }
    else {
//        ucout(task.getClientUuid());
//        ucout(task.getUuid());
//        ucout(QString::number(task.getState()));
//        ucout(task.getTaskUuid());

    }

}

void Window::on_itemtaskCallback(const qint32 msgId, const QString &msg, const QList<CsRUnstructSendAddr> &taskList)
{
    int i =0;
    for(i = 0;i < taskList.size(); ++i) {
        on_itemtaskCallback(msgId,msg,taskList.at(i));
    }
}

void Window::on_itemtaskCallback(const qint32 msgId, const QString &msg, const CsRUnstructTask &task)
{
    //如果出错,提示出错信息
    if(msgId != CallbackStatus::Unstruct::_0)
    {
        QString error = QObject::trUtf8(qPrintable(msg));
        QMessageBox::warning(this,tr("Warning"),error,QMessageBox::Ok);
    }
    else
    {
        //ucout(msg);
        //ucout(task.getInsertTime());
        ucout(task.getUuid());
        ucout(task.getTaskName());
        ucout(task.getInsertor());
        ucout(task.getInsertTime());
        ucout(task.getDescription());
        ucout(task.getOperater());
        ucout(task.getOperaTime());
        ucout(QString::number(task.getState()));
        ucout(QString::number(task.getStrategy()));
        ucout(task.getSendTime());

    }
}

void Window::on_itemtaskCallback(const qint32 msgId, const QString &msg, const QList<CsRUnstructTask> &taskList)
{
    int i =0;
    for(i = 0;i < taskList.size(); ++i) {
        on_itemtaskCallback(msgId,msg,taskList.at(i));
    }
}

void Window::on_pushButton_3_clicked()
{
    //FATAL 修改任务
    ucout("look at all task");
    class ListUnstructTaskRunnable:public QRunnable
    {
    public:
        void run() {
            JsonObject json;
            //            json["name"] = trs("all");
            QString params = QtJson::serialize(json);

            //生成一个消息发送端
            DPSender* sender = UpCloudDuplexFactory::getInstance().createDPSender();
            if(!sender) {
                return;
            }
            //请求数据
            sender->setExecType(Control_Module::Unstruct_listTask);
            sender->setParams(params);

            //设置请求超时时间
            //Asender->setExpiredTime(20);

            //获得结果集
            DPResult* resultSet = sender->doSendBySync(DeplexDefs::Priority::HighPriority);
            quint8 rState =resultSet->getRState();
            QString result = resultSet->getRContent();
            if(rState == Data_Authority::_2) {
                qDebug() << Data_Authority::_2_DESC_AddrIsInvalid;
            }
            else if(rState == Data_Authority::_1) {

                qDebug() << Data_Authority::_1_DESC_Unauthorized;
            }
            else if(rState == Data_Authority::_0) {
                qDebug() << Data_Authority::_0_DESC_Success;
                //反序列化
                bool ok;
                JsonObject jsonObject = QtJson::parse(result,ok).toMap();
                if(!ok) {
                    qDebug() << trs("解析出错!");
                }

            }
            sender->destory();

        }

    };
    QThreadPool::globalInstance()->start(new ListUnstructTaskRunnable);
}

void Window::on_pushButton_5_clicked()
{
    class DelUnstructTaskRunnable:public QRunnable
    {
    public:
        void run() {
            JsonObject json;
            json["uuid"] = trs("fdsfdsfsdfsdfsdfsd");
            QString params = QtJson::serialize(json);
            //1.生成一个消息发送端
            DPSender* asender = UpCloudDuplexFactory::getInstance().createDPSender();
            if(!asender) {
                return;
            }
            //2.请求数据
            asender->setExecType(Control_Module::Unstruct_delTask);
            asender->setParams(params);
            //3.获得结果集
            DPResult* aresult = asender->doSendBySync(DeplexDefs::Priority::HighPriority);
            quint8 rState = aresult->getRState();
            QString result = aresult->getRContent();
            //请求地址无效
            if(rState == Data_Authority::_2) {
                qDebug() << Data_Authority::_2_DESC_AddrIsInvalid;
            }
            //未授权操作
            else if(rState == Data_Authority::_1) {
                qDebug() << Data_Authority::_1_DESC_Unauthorized;
            }
            //未授权操作
            else if(rState == Data_Authority::_5) {
                qDebug() << Data_Authority::_5_DESC_ParamParseError;
            }
            //数据库操作失败
            else if(rState == Data_Authority::_4) {
                qDebug() << Data_Authority::_4_DESC_DatabaseError;
            }
            else if(rState == Data_Authority::_0) {
                qDebug() << Data_Authority::_0_DESC_Success;
                //反序列化

                bool ok;
                JsonObject jsonObject = QtJson::parse(result,ok).toMap();
                if(!ok) {

                    qDebug() << trs("解析出错!");
                }
                QString _uuid = jsonObject["uuid"].toString();
                bool status = jsonObject["status"].toBool();
                qDebug() << "uuid" << _uuid;
                qDebug() << "state" << status;
            }
            asender->destory();
        }
    };

    QThreadPool::globalInstance()->start(new DelUnstructTaskRunnable);
}

void Window::on_pushButton_8_clicked()
{

    ucout(tr("查询可下发节点服务器"));
    class ListSevUnstructTaskRunnable:public QRunnable{
    public:
        void run(){
            JsonObject json;
            json["name"] = trs("node sever");
            QString params = QtJson::serialize(json);

            //1.准备消息发送端
            DPSender* sender = UpCloudDuplexFactory::getInstance().createDPSender();
            if(!sender) {
                return;
            }
            //2.请求数据
            sender->setExecType(Control_Module::Unstruct_listNodeTask);
            sender->setParams(params);
            //3.准备结果集
            DPResult* resultSet = sender->doSendBySync();
            if(!resultSet) {
                return;
            }
            quint8 rState = resultSet->getRState();
            QString result = resultSet->getRContent();
            //地址无效
            if(rState == Data_Authority::_2) {
                qDebug() << Data_Authority::_2_DESC_AddrIsInvalid;

            }
            //未授权访问
            else if(rState == Data_Authority::_1) {
                qDebug() << Data_Authority::_1_DESC_Unauthorized;
            }
            //数据库操作失败
            else if(rState == Data_Authority::_4) {
                qDebug() << Data_Authority::_4_DESC_DatabaseError;
            }
            //解析参数失败
            else if(rState == Data_Authority::_5) {
                qDebug() << Data_Authority::_5_DESC_ParamParseError;
            }
            //没有可下发的节点服务器
            else if(rState == Data_Authority::_6) {
                qDebug() << Data_Authority::_6_DESC_NoderIsNull;

            }
            //操作
            //FATAL
            //反序列化处理可能不全面
            else if(rState == Data_Authority::_0) {
                bool ok;
                JsonArray jsonarray = QtJson::parse(result,ok).toList();
                int size = jsonarray.size();
                while(size --  > 0) {
                    QVariantMap resultmap = jsonarray.at(size).toMap();
                    qDebug() << "uuid: \t " << resultmap["uuid"].toString() << resultmap["state"].toString();

                }
            }
            sender->destory();
        }

    };
    QThreadPool::globalInstance()->start(new ListSevUnstructTaskRunnable);
}



void Window::on_pushButton_17_clicked()
{
    //TODO
//    DelUnstructTaskFileRunnable* del = new DelUnstructTaskFileRunnable(this);
//    QString taskUuid = "1001";
//    QList<CsRUnstructSendFiles> taskList;taskList.clear();
//    CsRUnstructSendFiles task;
//    task.setUuid("444e29154dfa45ec976db79a809fb90d");
//    taskList.push_back(task);
//    task.setUuid("c087c9b657c1450193f54dd655a25e68");
//    taskList.push_back(task);
//    del->setFileUuids(taskUuid,taskList);
//    QThreadPool::globalInstance()->start(del);
}

void Window::on_pushButton_16_clicked()
{
    //TODO
    DelUnstructTaskRunnable* del  =  new DelUnstructTaskRunnable(this);
    JsonArray params;
    params = JsonArray() << "1002" << "124";
    del->setTaskUuids(params);
    QThreadPool::globalInstance()->start(del);
}

void Window::on_pushButton_15_clicked()
{
    //TODO
    DelUnstructTaskAddrRunnable* del = new DelUnstructTaskAddrRunnable(this);
    JsonArray params;
    params = JsonArray() << "1002" << "1003";
    QString taskUuid = "1001";
    del->setAddrUuids(params,taskUuid);
    QThreadPool::globalInstance()->start(del);
}

void Window::on_btn_itemtask_clicked()
{
    QThreadPool::globalInstance()->start(new ItemUnstructTaskRunnable(this));
}

void Window::on_btn_itemtask_2_clicked()
{
    //TODO
    ucout(tr("修改后的信息"));
    QThreadPool::globalInstance()->start(new UpdateUnstructTaskRunnable(this));
}

void Window::on_btn_itemtask_3_clicked()
{
    ////添加SUPCODE为0/UNSTRUCT_TASK的字典
    QThreadPool::globalInstance()->start(new AddDictRunable(this));
}

void Window::on_btn_itemtask_4_clicked()
{
    ////查询SUPCODE为0/UNSTRUCT_TASK的所有字典
    ListDictRunnable *lsit = new ListDictRunnable(this);
    QVariantMap map;map.clear();
    map.insert("supcode",trs("UNSTRUCT_TASK"));
    lsit->setSelectCondition(map);
    QThreadPool::globalInstance()->start(lsit);
}

void Window::on_btn_itemtask_5_clicked()
{
    ////查询CODE为USABLE，SUPCODE为UNSTRUCT_TASK的字典信息
    ListDictRunnable *lsit = new ListDictRunnable(this);
    QVariantMap map;map.clear();
    map.insert("supcode",trs("UNSTRUCT_TASK"));
    map.insert("code",trs("USABLE"));
    lsit->setSelectCondition(map);
    QThreadPool::globalInstance()->start(lsit);
}

void Window::on_btn_itemtask_9_clicked()
{
    ////删除编码为STRUCT_TASK以及SUPCODE为STRUCT_TASK的所有字典
    QThreadPool::globalInstance()->start(new DelDictRunnable(this));
}

void Window::on_btn_itemtask_8_clicked()
{
    ////修改编码为UNSTRUCT_TASK的字典信息（不可以修改字典编码）
    QThreadPool::globalInstance()->start(new UpdateDictRunnable(this));
}

void Window::on_btn_itemtask_6_clicked()
{
    QThreadPool::globalInstance()->start(new AddCsClientGroupRunnable(this));
}

void Window::on_btn_itemtask_7_clicked()
{
 QThreadPool::globalInstance()->start(new UpdateClientGroupRunnable(this));
}

void Window::on_btn_itemtask_11_clicked()
{
//    ListClientGroupRunnable* list = new ListClientGroupRunnable(this);
//    JsonArray params;
//    params = JsonArray() << "1" ;
//    list->setGroupInfo(params);
//    QThreadPool::globalInstance()->start(list);
}

void Window::on_btn_itemtask_13_clicked()
{
//    AddClientGroupAssocRunnable* add = new AddClientGroupAssocRunnable(this);
//    JsonArray nodes;
//    QString groupuuid = trs("e345d59bd91d47bc9cd9fbc9f1664436");
//    nodes = JsonArray() << "1" << "3" << "6";
//    add->setAddCondition(nodes,groupuuid);
//    QThreadPool::globalInstance()->start(add);
}

void Window::on_btn_itemtask_10_clicked()
{
//    DelClientGroupAssocRunnable* add = new DelClientGroupAssocRunnable(this);
//    JsonArray nodes;
//    QString groupuuid = trs("9eb12c5b24de4034b5cd1ff625904003");
//    nodes = JsonArray() << "1" << "3";
//    add->setDelCondition(nodes,groupuuid);
//    QThreadPool::globalInstance()->start(add);
}

void Window::on_btn_itemtask_14_clicked()
{
   ListClientGroupAssocRunnable* list = new ListClientGroupAssocRunnable(this);
   QString sup;
   sup = "1";
   list->setGroupAssocUuid(sup);
   QThreadPool::globalInstance()->start(list);
}

void Window::on_btn_itemtask_12_clicked()
{
//    DelClientGroupAssocRunnable* add = new DelClientGroupAssocRunnable(this);
//    JsonArray nodes;
//    QString groupuuid = trs("e345d59bd91d47bc9cd9fbc9f1664436");
//    nodes = JsonArray() << "all";
//    add->setDelCondition(nodes,groupuuid);
//    QThreadPool::globalInstance()->start(add);
}

void Window::on_btn_listStructTask_clicked()
{
    ListStructTaskRunnable* list = new ListStructTaskRunnable(this);
    QVariantMap params;
    params["uuid"] = "";
    params["tasknum"] = 23;
    params["description"] = "";
    params["sendtime"] ="";
    params["strategy"] = "";
    params["exectime"] = "";
    params["state"] = 6;
    list->setTaskInfo(params);
    QThreadPool::globalInstance()->start(list);
}

void Window::on_btn_delStructTask_clicked()
{
    DelStructTaskRunnable* del  =  new DelStructTaskRunnable(this);
    JsonArray params;
    params = JsonArray() << "123" << "124";
    del->setTaskInfo(params);
    QThreadPool::globalInstance()->start(del);
}

void Window::on_btn_addStructAddrTask_clicked()
{
//    AddStructTaskAddrRunnable* add = new AddStructTaskAddrRunnable(this);
//    JsonArray params;
//    params = JsonArray() << "1002" << "1003";
//    QString taskUuid = "1001";
//    add->setAddCondition(params,taskUuid);
//    QThreadPool::globalInstance()->start(add);
}

void Window::on_btn_delStructAddrTask_clicked()
{
    DelStructTaskAddrRunnable* del = new DelStructTaskAddrRunnable(this);
    JsonArray params;
    params = JsonArray() << "1002" << "1003";
    QString taskUuid = "1001";
    del->setAddrInfo(params,taskUuid);
    QThreadPool::globalInstance()->start(del);
}

void Window::on_btn_addStructFileTask_clicked()
{
    AddStructTaskFileRunnable* add =  new  AddStructTaskFileRunnable(this);
    QString taskUuid = "1001";
    QList<CsRStructSendFiles> taskList;taskList.clear();
    CsRStructSendFiles task;
    task.setFileName("test2.xml");
    task.setFileDestName("test2.xml.copy");
    task.setDownUrl("ftp://10.0.0.110/test2.xml");
    task.setSaveAbst("E:\Test\upcloud\struct");
    task.setSequence(2);
    taskList.push_back(task);
    task.setFileName("test3.xml");
    task.setFileDestName("test3.xml.copy");
    task.setDownUrl("ftp://10.0.0.110/test3.xml");
    task.setSaveAbst("E:\Test\upcloud\struct");
    task.setSequence(3);
    taskList.push_back(task);
    add->setAddCondition(taskUuid,taskList);
    QThreadPool::globalInstance()->start(add);
}

void Window::on_btn_delStructFileTask_clicked()
{
//    DelStructTaskFileRunnable* del = new DelStructTaskFileRunnable(this);
//    QString taskUuid = "1001";
//    QList<CsRStructSendFiles> taskList;taskList.clear();
//    CsRStructSendFiles task;
//    task.setUuid("444e29154dfa45ec976db79a809fb90d");
//    taskList.push_back(task);
//    task.setUuid("c087c9b657c1450193f54dd655a25e68");
//    taskList.push_back(task);
//    del->setFileInfo(taskUuid,taskList);
//    QThreadPool::globalInstance()->start(del);
}


void Window::on_btn_addtask_clicked()
{
    AddUnstructTaskRunnable* add = new AddUnstructTaskRunnable(this);
    CsRUnstructTask task;
    QString curTime;curTime.clear();
    task.setTaskName("测试任务");
    task.setDescription("测试任务描述");
    TimerUtil::toString(curTime);
    task.setSendTime(curTime);
    task.setStrategy(3);
    task.setState(1);
    add->setAddCondition(task);
    QThreadPool::globalInstance()->start(add);
}

void Window::on_btn_addtaskfile_clicked()
{
    AddUnstructTaskFileRunnable* add = new AddUnstructTaskFileRunnable(this);
    QString taskUuid = "1001";
    QList<CsRUnstructSendFiles> taskList;taskList.clear();
    CsRUnstructSendFiles task;
    task.setFileName("test2.xml");
    task.setFileDestName("test2.xml.copy");
    task.setDownUrl("ftp://10.0.0.110/test2.xml");
    task.setSaveAbst("E:\Test\upcloud\unstruct");
    taskList.push_back(task);
    task.setFileName("test3.xml");
    task.setFileDestName("test3.xml.copy");
    task.setDownUrl("ftp://10.0.0.110/test3.xml");
    task.setSaveAbst("E:\Test\upcloud\unstruct");
    taskList.push_back(task);
    add->setAddCondition(taskUuid,taskList);
    QThreadPool::globalInstance()->start(add);
}

void Window::on_btn_addtasknode_clicked()
{
//    AddUnstructTaskAddrRunnable* add = new AddUnstructTaskAddrRunnable(this);
//    JsonArray params;
//    params = JsonArray() << "1002" << "1003";
//    QString taskUuid = "1001";
//    add->setAddCondition(params,taskUuid);
//    QThreadPool::globalInstance()->start(add);
}

void Window::on_btn_addStructTask_clicked()
{
    AddStructTaskRunnable* add  = new AddStructTaskRunnable(this);
    CsRStructTask task;
    QString curTime;curTime.clear();
    task.setTaskName("测试任务");
    task.setDescription("测试任务描述");
    TimerUtil::toString(curTime);
    task.setSendTime(curTime);
    task.setExecTime(curTime);
    task.setStrategy(3);
    task.setState(1);
    add->setAddCondition(task);
    QThreadPool::globalInstance()->start(add);
}

void Window::on_btn_itemStructTask_clicked()
{
    ListStructTaskRunnable* list = new ListStructTaskRunnable(this);
    QVariantMap params;
    params["uuid"] = "82019eedc95c43ee901c79e26c9fb498";
    params["tasknum"] = (quint32)0;
    params["description"] = "";
    params["sendtime"] ="";
    params["strategy"] = (quint16)0;
    params["exectime"] = "";
    params["state"] = (quint8)0;
    list->setTaskInfo(params);
    QThreadPool::globalInstance()->start(list);
}

void Window::on_btn_updateStructTask_clicked()
{
//    UpdateStructTaskRunnable * update = new UpdateStructTaskRunnable(this);
//    QVariantMap params;
//    QString curTime;
//    TimerUtil::toString(curTime);
//    params["uuid"] = "2d4d8c7e06834109867eae2e152991f2";
//    params["taskname"] = "update";
//    params["tasknum"] = (quint32)1234;
//    params["description"] = "修改测试";
//    params["sendtime"] = curTime;
//    params["strategy"] = (quint16)4;
//    params["exectime"] = curTime;
//    params["state"] = (quint8)0;
//    update->setTaskList(params);
//    QThreadPool::globalInstance()->start(update);
}
