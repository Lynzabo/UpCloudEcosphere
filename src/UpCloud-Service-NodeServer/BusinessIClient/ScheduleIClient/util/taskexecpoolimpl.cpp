#include "taskexecpoolimpl.h"

TaskExecPoolImpl::TaskExecPoolImpl()
{
    m_taskExecManager = NULL;
}

TaskExecPoolImpl::~TaskExecPoolImpl()
{
    if(m_taskExecManager != NULL)
    {
        delete m_taskExecManager;
        m_taskExecManager = NULL;
    }
}

void TaskExecPoolImpl::init(const QString &taskName)
{
    m_taskExecManager = new TaskExecManager;
    m_taskExecManager->init(taskName);
    connect(m_taskExecManager, SIGNAL(evt_execBegin(QString)), this, SLOT(on_execBegin(QString)));
    connect(m_taskExecManager, SIGNAL(evt_execEnd(QString,QString)), this, SLOT(on_execEnd(QString,QString)));
}

void TaskExecPoolImpl::taskExec(void)
{
    m_taskExecManager->taskExec();
}

void TaskExecPoolImpl::on_execBegin(const QString &taskName)
{
    qDebug() << "execBegin";
    //执行开始
    emit evt_execBegin(taskName);
}

void TaskExecPoolImpl::on_execEnd(const QString &taskName, const QString &result)
{
    qDebug() << "execEnd";
    //执行结束
    emit evt_execEnd(taskName, result);
}


