#include "nscparseexector.h"

using QtJson::JsonObject;
using QtJson::JsonArray;

using namespace Environment::Task_Status::Noder::Sche;
using namespace Environment::Datagram::Sche_Data_Trans;

NoderScheduleParseExector::NoderScheduleParseExector()
{
    this->clear();    


    qDeleteAll(m_reqEntitys);
    m_reqEntitys.clear();

    m_results.clear();
}

NoderScheduleParseExector::~NoderScheduleParseExector()
{    
    //以下资源是发送给中心服务器的，在任务结束时候不能清理，
    //有可能正在使用中（evt_write(m_pushContext)），
    //因此在析构函数中释放

    //【1】反馈报文对象列表
//    qDeleteAll(m_reqEntitys);
//    m_reqEntitys.clear();

    //【2】本次扫描的任务执行结果映射表<taskUUID, 任务执行结果>，一个任务对应一个任务执行结果
    m_results.clear();
}

void NoderScheduleParseExector::doExecute(QMap<QTcpSocket *, quint64> &socks, PushContext *context)
{
    m_centerSocks = socks;
    m_pushContext = context;
    ////扫描控制传输可执行任务表,查找所有可执行任务
    QString curTime;
    TimerUtil::toString(curTime);

    m_usableScheduleExecTasks = NSScheduleDao::dirRTaskByStatus(Task_State::EXECABLE,curTime);
    ////控制传输可执行任务表是否不为空
    if(m_usableScheduleExecTasks.size() <= 0)
        return;

    ////遍历可用执行任务列表 修改当前任务状态为“正在执行”
    for(NsRScheduleTask task : m_usableScheduleExecTasks)
    {
        //获取结构化可解析任务UUID
        QString currentTaskUUID = task.getUuid();       
        ////修改当前任务状态为“EXECABLE”的文件列表修改为“正在执行”
        NSScheduleDao::updateRTaskState(currentTaskUUID,Task_State::EXECING);
    }
    ////遍历可执行任务表
    for(NsRScheduleTask task : m_usableScheduleExecTasks)
    {
        //获取结构化可执行任务UUID
        QString currentTaskUUID = task.getUuid();
        //修改当前任务所对应的文件列表中状态为“EXECABLE”的文件，修改其状态为“EXECING”
        NSScheduleDao::updateRSendFilesState(currentTaskUUID, SendFiles_State::EXECABLE, SendFiles_State::EXECING);
        ////构建任务执行器
        TaskExecPool* pool = new TaskExecPoolImpl;
        QString taskName = task.getSaveAbst();
        pool->init(taskName);
        connect(pool, SIGNAL(evt_execBegin(QString)),this, SLOT(on_execBegin(QString)));
        connect(pool, SIGNAL(evt_execEnd(QString,QString)), this, SLOT(on_execEnd(QString,QString)));

        ////插入执行池映射表
        m_pools.insert(currentTaskUUID, pool);
    }
    //开始执行任务
    for(int i=0; i<m_pools.size(); i++)
    {
//        QEventLoop *loop = new QEventLoop;
//        connect(this, SIGNAL(endLoop()), loop, SLOT(quit()));
       m_pools.values().at(i)->taskExec();
//        loop->exec(QEventLoop::ExcludeUserInputEvents);
//        delete loop;
//        loop = NULL;
    }
}

void NoderScheduleParseExector::doSetArgs(QMap<QTcpSocket *, quint64> &socks)
{
    m_socks = socks;
}

void NoderScheduleParseExector::doExecute()
{
    PushContext *context = new PushContext;
    this->doExecute(m_socks, context);
}

void NoderScheduleParseExector::on_RemoteHostClosed(const QString &clientUUID)
{
    //TODO修改任务状态
}

//一个任务开始执行
void NoderScheduleParseExector::on_execBegin(const QString &taskName)
{
    qDebug() << taskName << "exec begin!";
}
//一个任务执行结束
void NoderScheduleParseExector::on_execEnd(const QString &taskName, const QString &result)
{
    //得到taskUUID
    TaskExecPoolImpl* pool = (TaskExecPoolImpl*)this->sender();
    QString taskUUID = m_pools.key(pool);
    //执行任务结果
    bool execState = false;
    QString execResult = QString();
    //数据库状态
    quint8 currentTaskState = 0;
    quint8 currentSendFileState = 0;
    //解析Json
    bool ok = false;
    JsonObject resultObj;
    if(result.isEmpty())
    {
        execState = false;
        execResult = Req_Info_Plan_Back::_C_DESC_ReturnJsonNull;
        goto sendDatagram;
    }
    resultObj = QtJson::parse(result, ok).toMap();
    if (!ok)
    {        
        execState = false;
        execResult = Req_Info_Plan_Back::_D_DESC_ReturnJsonError;
        goto sendDatagram;
    }
    else
    {
        execState = resultObj["state"].toBool();
        execResult = resultObj["result"].toString();
    }

sendDatagram:
    //任务执行结果映射表添加结果
    Result* taskResult = new Result;
    taskResult->DownloadURLs = taskName;
    taskResult->backMsg = execResult;

    QVector<Result*>* taskResults = new QVector<Result*>;
    taskResults->append(taskResult);

    ResultInfo* resultInfo = new ResultInfo;
    for(int i=0; i<taskResults->size(); i++)
    {
        resultInfo->results.append(taskResults->at(i));
    }
    m_results.insert(taskUUID, resultInfo);

    //根据任务执行结果修改数据库状态    
    if(execState == true)
    {
        currentTaskState = Task_State::EXECSUCCESS;
        currentSendFileState = SendFiles_State::EXECSUCCESS;
    }
    else
    {
        currentTaskState = Task_State::EXECERROR;
        currentSendFileState = SendFiles_State::EXECERROR;
    }
    NSScheduleDao::updateRTaskAndSendFilesStateByUUID(taskUUID, currentTaskState, currentSendFileState);

    //准备发送反馈报文给中心服务器
    ReqScheduleTaskExecStatus* reqEntity = new ReqScheduleTaskExecStatus;
    m_reqEntitys.append(reqEntity);

    //设置反馈报文属性
    NsRScheduleTask task = NSScheduleDao::getRTaskByUUID(taskUUID);
    reqEntity->State = currentTaskState;
    reqEntity->TaskUUID = task.getTaskNum();
    reqEntity->Strategy = task.getStrategy();
    reqEntity->resultInfo = m_results.value(taskUUID);

    //发送反馈报文对象给中心服务器
    QList<quint64> socks= m_centerSocks.values();
    if(socks.size()==1)
    {
        quint64 serverUUID = socks.at(0);
        QVector<quint64> server;
        server.append(serverUUID);
        m_pushContext->setSocks(server);
        m_pushContext->setMessage(reqEntity);
        emit
        evt_write(m_pushContext);
    }
    //结束本次执行事件循环
    emit
    endLoop();
    //检查是否所有任务都完成
    this->checkFinished();
}

void NoderScheduleParseExector::checkFinished()
{
    bool isAllDone = true;
    for(int i=0; i<m_usableScheduleExecTasks.size(); i++)
    {
        quint8 state = 0;
        NSScheduleDao::getRTaskStateByTaskUUID(m_usableScheduleExecTasks.at(i).getUuid(), state);
        if(state == Task_State::EXECING)
        {
            isAllDone = false;
            break;
        }
    }
    if(isAllDone)
    {
        isAllDone = true;
        //所有任务完成 则清理本次执行的所有任务的资源
        this->clear();
    }
}

void NoderScheduleParseExector::clear()
{
    //本次扫描的所有可用任务列表
    m_usableScheduleExecTasks.clear();
    //本次扫描任务映射表<taskUUID, 任务执行池>，一个任务对应一个任务执行池
    qDeleteAll(m_pools);
    m_pools.clear();
}

