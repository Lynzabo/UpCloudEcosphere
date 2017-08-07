#include "taskexecmanager.h"
using namespace Environment::Datagram::Sche_Data_Trans::Req_Info_Plan_Back;
using QtJson::JsonObject;
using QtJson::JsonArray;

TaskExecManager::TaskExecManager()
{
    m_taskName.clear();
    m_taskInJson.clear();
    m_result.clear();
    m_taskOutJson.clear();
    m_process = NULL;

}

TaskExecManager::~TaskExecManager()
{
    m_taskName.clear();
    m_taskInJson.clear();
    m_result.clear();
    m_taskOutJson.clear();
    if(m_process != NULL)
    {
        delete m_process;
        m_process = NULL;
    }
}
void TaskExecManager::taskExec()
{
    this->run();
}

void TaskExecManager::init(const QString &taskName)
{
    m_taskName = taskName;
}

void TaskExecManager::run()
{
    //发送解析开始信号
    emit evt_execBegin(m_taskName);

    //变量初始化 for goto语句
    bool ok = false;
    JsonObject result;

    //[1]开始解析TaskInJson
    if(m_taskName.isEmpty())
    {
        m_taskOutJson.setState(false);
        //m_taskOutJson.setResult("Task data is null!");
        m_taskOutJson.setResult(_9_DESC_ParseJsonNull);
        goto end;
    }
    result = QtJson::parse(m_taskName, ok).toMap();
    if (!ok)
    {
        qDebug() << "Parse Task data error!";
        m_taskOutJson.setState(false);
        m_taskOutJson.setResult(_A_DESC_ParseJsonError);
        goto end;
    }
    else
    {
        QString program = result["program"].toString();
        m_taskInJson.setProgram(program);


        QStringList arguments;
        arguments.clear();
        JsonArray argumentsArray = result["arguments"].toList();
        foreach(QVariant argument, argumentsArray) {
            arguments.append(argument.toString());
        }
        m_taskInJson.setArguments(arguments);

        qDebug() << "program:" << m_taskInJson.program();
        qDebug() << "arguments:" << m_taskInJson.arguments();
    }

    //[2]起进程执行任务
    m_process = new QProcess();
    //起进程
    m_process->start(m_taskInJson.program(), m_taskInJson.arguments());
    //关闭写通道（未使用）
    m_process->closeWriteChannel();
    //是否启动成功（阻塞执行，时间默认3S）
    if(!m_process->waitForStarted())
    {
        qDebug() << "start fail!" ;
        m_taskOutJson.setState(false);
        m_taskOutJson.setResult(_B_DESC_ExecStartError);
        goto end;
    }
    //等待执行结束（阻塞执行）
    while(false == m_process->waitForFinished())
    {
        ;
    }
    if(m_process->exitStatus() == QProcess::NormalExit)
    {
        m_taskOutJson.setState(true);
        m_taskOutJson.setResult(QString(m_process->readAllStandardOutput()));
    }
    else
    {
        m_taskOutJson.setState(false);
        m_taskOutJson.setResult(QString(m_process->readAllStandardError()));
    }
    goto end;

    //[3]生成反馈JSON，并返回
end:
    JsonObject objJson;
    objJson["state"] = m_taskOutJson.state();
    objJson["result"] = m_taskOutJson.result();
    m_result = QtJson::serializeStr(objJson);

    emit evt_execEnd(m_taskName, m_result);
    return;
}







