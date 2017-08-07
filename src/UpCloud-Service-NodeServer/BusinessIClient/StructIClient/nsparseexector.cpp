#include "nsparseexector.h"

using namespace Environment::Task_Status::Noder::Stru;
using namespace Environment::Datagram::Stru_Data_Trans;

QMutex NoderStructParseExector::mutex;
NoderStructParseExector::NoderStructParseExector()
{
    this->clear();
    qDeleteAll(m_reqEntitys);
    m_reqEntitys.clear();

    m_errors.clear();
}

NoderStructParseExector::~NoderStructParseExector()
{
    m_centerSocks.clear();
    m_errors.clear();
}

void NoderStructParseExector::doExecute(QMap<QTcpSocket *, quint64> &socks, PushContext *context)
{
    mutex.lock();
    qDebug() << trs("Struct parse exector ready to work");
    m_centerSocks = socks;
    m_pushContext = context;
    ////扫描结构化可解析任务表,查找所有可解析任务
    QString curTime;
    TimerUtil::toString(curTime);

    m_usableStructParseTasks = NsStructDao::dirRTaskByStatus(Task_State::PARSEABLE,curTime);
    ////可用解析任务列表是否不为空
    if(m_usableStructParseTasks.size() <= 0)
    {
//        qDebug() << trs("Struct parse exector exit,task is null");
        mutex.unlock();
        return;
    }

    ////遍历可用解析任务列表 修改当前任务状态为“正在解析”
    for(NsRStructTask task : m_usableStructParseTasks)
    {
        //获取结构化可解析任务UUID
        QString currentTaskUUID = task.getUuid();
        ////修改当前任务状态为“正在解析”
        NsStructDao::updateRTaskState(currentTaskUUID,Task_State::PARSING);
    }
    ////遍历可用解析任务列表
    for(NsRStructTask task : m_usableStructParseTasks)
    {
        //获取结构化可解析任务UUID
        QString currentTaskUUID = task.getUuid();
        //修改当前任务所对应的文件列表中状态为“PARSEABLE”的文件，修改其状态为“PARSING”
        NsStructDao::updateRSendFilesState(currentTaskUUID, SendFiles_State::PARSEABLE, SendFiles_State::PARSING);
        ////得到当前任务所对应的解析文件列表
        QList<NsRStructSendFiles> nsRStructSendFiles = NsStructDao::dirRSendFilesByTaskUUID(currentTaskUUID,SendFiles_State::PARSING);

        ////构建文件解析器
        ParseSDPool* pool = new ParseSDPoolImpl();
        connect(pool, SIGNAL(evt_parseBegin()),this, SLOT(on_parseBegin()), Qt::QueuedConnection);
        connect(pool, SIGNAL(evt_parseEnd()), this, SLOT(on_parseEnd()), Qt::QueuedConnection);
        connect(pool, SIGNAL(evt_parseError(QString,QString)), this, SLOT(on_parseError(QString,QString)), Qt::QueuedConnection);
        connect(pool, SIGNAL(evt_parseOneFileEnd(QString)), this, SLOT(on_parseOneFileEnd(QString)), Qt::QueuedConnection);
        connect(pool, SIGNAL(evt_parseProcess(quint32)), this, SLOT(on_parseProcess(quint32)), Qt::QueuedConnection);
        ////生成文件解析列表
        QList<QString> fileList;
        fileList.clear();
        for(NsRStructSendFiles sendfile : nsRStructSendFiles)
        {
            ////得到要解析的文件名字
            QString fileName = sendfile.getFileAbst();
            ////插入文件解析列表
            fileList.append(fileName);
        }
        ////插入解析池映射表
        m_pools.insert(currentTaskUUID, pool);
        ////开始执行解析
        QEventLoop *loop = new QEventLoop;
        connect(this, SIGNAL(endLoop()), loop, SLOT(quit()));
        pool->parse(fileList, false, 3, false, 5);
        loop->exec(QEventLoop::ExcludeUserInputEvents);
        delete loop;
        loop = NULL;
    }
    qDebug() << trs("Struct parse exector download complete");
    mutex.unlock();
}

void NoderStructParseExector::doSetArgs(QMap<QTcpSocket *, quint64> &socks)
{
    m_socks = socks;
}

void NoderStructParseExector::doExecute()
{
    PushContext *context = new PushContext;
    this->doExecute(m_socks, context);
}


//private slots
//一个任务解析开始
void NoderStructParseExector::on_parseBegin()
{

}
//一个任务解析完成
void NoderStructParseExector::on_parseEnd()
{
    //得到taskUUID
    ParseSDPoolImpl* pool = (ParseSDPoolImpl*)this->sender();
    QString taskUUID = m_pools.key(pool);
    //获取任务状态
    quint8 taskState = 0;
    QList<NsRStructSendFiles> nsRStructSendFiles = NsStructDao::dirRSendFilesByTaskUUID(taskUUID,SendFiles_State::PARSEERROR);
    if(nsRStructSendFiles.size() == 0)
    {
        taskState = Task_State::PARSESUCCESS;
    }
    else
    {
        taskState = Task_State::PARSEERROR;
    }
    //修改数据库任务状态
    NsStructDao::updateRTaskState(taskUUID, taskState);
    //准备发送反馈报文给中心服务器
    ReqStructTaskExecStatus* reqEntity = new ReqStructTaskExecStatus;
    m_reqEntitys.append(reqEntity);
    //设置反馈报文属性
    NsRStructTask task = NsStructDao::getRTaskByUUID(taskUUID);
    reqEntity->State = taskState;
    reqEntity->TaskUUID = task.getTaskNum();
    reqEntity->Strategy = task.getStrategy();
    if(m_errors.contains(taskUUID))
    {
        reqEntity->resultInfo = m_errors.value(taskUUID);
    }
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
    //结束当前任务事件循环
    emit  endLoop();
    //检查是否所有任务都完成
    this->checkFinished();
}
//一个任务解析进度
void NoderStructParseExector::on_parseProcess(quint32 parsedCount)
{

}
//一个文件解析完成
void NoderStructParseExector::on_parseOneFileEnd(const QString &fileName)
{
    //得到taskUUID
    ParseSDPoolImpl* pool = (ParseSDPoolImpl*)this->sender();
    QString taskUUID = m_pools.key(pool);
    //一个文件解析成功完成，更改SendFiles表中对应taskUUID fileName 的文件为解析成功
    NsStructDao::updateRSendFilesStateByAbst(taskUUID, fileName, SendFiles_State::PARSESUCCESS, "");
}
//一个文件解析出错
void NoderStructParseExector::on_parseError(const QString &fileName, const QString &errMsg)
{
    try{
    //得到taskUUID
    ParseSDPoolImpl* pool = (ParseSDPoolImpl*)this->sender();
    QString taskUUID = m_pools.key(pool);
    //在错误表中添加出错信息
    Result* error = new Result;
    error->DownloadURLs = fileName;
    error->backMsg = errMsg;
    if(m_errors.contains(taskUUID))
    {

        m_errors.value(taskUUID)->results.append(error);
    }
    else
    {
        ResultInfo* errorinfo = new ResultInfo;
        errorinfo->results.append(error);
        m_errors.insert(taskUUID, errorinfo);
    }
    //更改结构化数据库SendFiles表中对应taskUUID fileName 的文件为解析失败， 失败信息为errMsg
    NsStructDao::updateRSendFilesStateByAbst(taskUUID, fileName, SendFiles_State::PARSEERROR, errMsg);
    }
    catch(DBException ex)
    {
        qDebug()<<ex.getType()<<ex.getText()<<ex.getTypeDesc();
    }
}

//检查是否所有任务都完成
void NoderStructParseExector::checkFinished()
{
    bool isAllDone = true;
    for(int i=0; i<m_usableStructParseTasks.size(); i++)
    {
        quint8 state = 0;
        NsStructDao::getRTaskStateByTaskUUID(m_usableStructParseTasks.at(i).getUuid(), state);
        if(state == Task_State::PARSING)
        {
            isAllDone = false;
            break;
        }
    }
    if(isAllDone)
    {
        isAllDone = true;
        //所有任务完成 则清理本次解析的所有任务的资源
        this->clear();
    }

}

void NoderStructParseExector::clear()
{
    //本次扫描的所有可用任务列表
    m_usableStructParseTasks.clear();
    //本次扫描任务映射表<taskUUID, 解析线程池>，一个任务对应一个解析线程池
    qDeleteAll(m_pools);
    m_pools.clear();
}



